// ProgressDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ProgressDialog.h"
#include "afxdialogex.h"


// CProgressDialog �_�C�A���O

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


// CProgressDialog ���b�Z�[�W �n���h���[


BOOL CProgressDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_prg_state.SetMarquee(TRUE, 20);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
