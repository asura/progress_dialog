// ProgressDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ICancelable.h"
#include "ProgressDialog.h"
#include "afxdialogex.h"
#include "plog/Log.h"
#include <thread>


// CProgressDialog ダイアログ

IMPLEMENT_DYNAMIC(CProgressDialog, CDialogEx)

CProgressDialog::CProgressDialog(
	CWnd* pParent,
	std::shared_ptr<ICancelable> process)
	: CDialogEx(CProgressDialog::IDD, pParent)
	, m_process(process)
{
}

CProgressDialog::~CProgressDialog()
{
}

void CProgressDialog::ActionWhenThreadEnds()
{
	// スレッド終了時にダイアログを閉じたいが
	// 非UIスレッドからEndDialogを発行するのはMFCのお作法としてNG。
	// ウィンドウハンドルを使って終了メッセージを投げ
	// メッセージハンドラ内でEndDialogさせる。
	::PostMessage(m_hWnd, WM_CLOSE_PROGRESS_DIALOG, 0, 0);
}

void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRG_STATE, m_prg_state);
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CProgressDialog::OnBnClickedCancel)
	ON_MESSAGE(WM_CLOSE_PROGRESS_DIALOG, OnCloseProgressDialog)
END_MESSAGE_MAP()


// CProgressDialog メッセージ ハンドラー


BOOL CProgressDialog::OnInitDialog()
{
	LOGI << "CProgressDialog::OnInitDialog";
	CDialogEx::OnInitDialog();

	// プログレスバーを動かす
	m_prg_state.SetMarquee(TRUE, 20);

	// 非同期処理を開始
	m_task = std::async(std::launch::async, [&]() -> bool
	{
		auto result = m_process->Do();
		this->ActionWhenThreadEnds();
		return result;
	});

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CProgressDialog::OnBnClickedCancel()
{
	m_process->Cancel();
}

LRESULT CProgressDialog::OnCloseProgressDialog(WPARAM wParam, LPARAM lParam)
{
	LOGI << "start";

	// プログレスバーを止める
	m_prg_state.SetMarquee(FALSE, 0);

	try
	{
		// ここに来たということは、非同期処理は完了しているはず
		// なのでget()は待ちなしで実行されるはず
		LOGI << "get開始";
		auto result = m_task.get();
		LOGI << "get終了";

		EndDialog(result ? IDOK : IDCANCEL);
	}
	catch(...)
	{
		// 非同期処理内で例外発生
		// (CancelableProcessBase::Do()内でcatchしてあるので、ここには来ないはずだが)
		LOGE << "例外発生";
		EndDialog(IDCANCEL);
	}

	return 0;
}
