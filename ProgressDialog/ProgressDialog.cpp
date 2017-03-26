// ProgressDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ProgressDialog.h"
#include "afxdialogex.h"


// CProgressDialog ダイアログ

IMPLEMENT_DYNAMIC(CProgressDialog, CDialogEx)

CProgressDialog::CProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgressDialog::IDD, pParent)
{

}

CProgressDialog::~CProgressDialog()
{
}

void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRG_STATE, m_prg_state);
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialogEx)
END_MESSAGE_MAP()


// CProgressDialog メッセージ ハンドラー


BOOL CProgressDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_prg_state.SetMarquee(TRUE, 20);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
