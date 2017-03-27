
// ProgressDialogDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CProgressDialogApp.h"
#include "ConcreteProcess.h"
#include "ProgressDialogDlg.h"
#include "ProgressDialog.h"
#include "afxdialogex.h"
#include "plog/Log.h"
#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProgressDialogDlg ダイアログ



CProgressDialogDlg::CProgressDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgressDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProgressDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CProgressDialogDlg::OnBnClickedBtnProcess)
END_MESSAGE_MAP()


// CProgressDialogDlg メッセージ ハンドラー

BOOL CProgressDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CProgressDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CProgressDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CProgressDialogDlg::OnBnClickedBtnProcess()
{
	LOGI << "CProgressDialog生成";
	auto process = std::make_shared<ConcreteProcess>();
	auto cancel_func = std::bind(&CancelableProcessBase::Cancel, process);
	auto do_func = std::bind(&CancelableProcessBase::Do, process);
	CProgressDialog dlg(this, do_func, cancel_func);

	LOGI << "CProgressDialog::DoModal呼び出し";
	auto result = dlg.DoModal();

	if (result != IDOK) {
		AfxMessageBox(L"処理は正常終了しませんでした", MB_ICONEXCLAMATION | MB_OK);
	}
	else {
		AfxMessageBox(L"処理は正常に終了しました", MB_ICONINFORMATION | MB_OK);
	}
}
