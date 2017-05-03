// ProgressDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ICancelable.h"
#include "ProgressDialog.h"
#include "afxdialogex.h"
#include "plog/Log.h"


// CProgressDialog ダイアログ

IMPLEMENT_DYNAMIC(CProgressDialog, CDialogEx)

CProgressDialog::CProgressDialog(
	CWnd* pParent,
	std::shared_ptr<ICancelable> process)
	: CDialogEx(CProgressDialog::IDD, pParent)
	, m_process(process)
	, m_task_manager(
		generate_action(&CProgressDialog::ActionWhenProcessExecutes),
		generate_action(&CProgressDialog::ActionWhenThreadEnds)
	  )
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
	// メッセージハンドラ内で終了させる。
	::PostMessage(m_hWnd, WM_CLOSE_PROGRESS_DIALOG, 0, 0);
}

void CProgressDialog::ActionWhenProcessExecutes()
{
	m_prg_state.SetMarquee(FALSE, 0);
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

	m_prg_state.SetMarquee(TRUE, 20);
	m_task_manager.push_back(m_process);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CProgressDialog::OnBnClickedCancel()
{
	m_process->Cancel();
}

LRESULT CProgressDialog::OnCloseProgressDialog(WPARAM wParam, LPARAM lParam)
{
	EndDialog(m_task_manager.get_result() ? IDOK : IDCANCEL);

	return 0;
}

boost::optional<std::function<void()>> CProgressDialog::generate_action(action_type action)
{
	return boost::optional<std::function<void()>>(std::bind(action, this));
}
