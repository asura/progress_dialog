
// ProgressDialogDlg.cpp : �����t�@�C��
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


// CProgressDialogDlg �_�C�A���O



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


// CProgressDialogDlg ���b�Z�[�W �n���h���[

BOOL CProgressDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CProgressDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CProgressDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CProgressDialogDlg::OnBnClickedBtnProcess()
{
	LOGI << "CProgressDialog����";
	auto process = std::make_shared<ConcreteProcess>();
	auto cancel_func = std::bind(&CancelableProcessBase::Cancel, process);
	auto do_func = std::bind(&CancelableProcessBase::Do, process);
	CProgressDialog dlg(this, do_func, cancel_func);

	LOGI << "CProgressDialog::DoModal�Ăяo��";
	auto result = dlg.DoModal();

	if (result != IDOK) {
		AfxMessageBox(L"�����͐���I�����܂���ł���", MB_ICONEXCLAMATION | MB_OK);
	}
	else {
		AfxMessageBox(L"�����͐���ɏI�����܂���", MB_ICONINFORMATION | MB_OK);
	}
}
