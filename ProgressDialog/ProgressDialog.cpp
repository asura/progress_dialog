// ProgressDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ICancelable.h"
#include "ProgressDialog.h"
#include "afxdialogex.h"
#include "plog/Log.h"
#include <thread>


// CProgressDialog �_�C�A���O

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
	// �X���b�h�I�����Ƀ_�C�A���O���������
	// ��UI�X���b�h����EndDialog�𔭍s����̂�MFC�̂���@�Ƃ���NG�B
	// �E�B���h�E�n���h�����g���ďI�����b�Z�[�W�𓊂�
	// ���b�Z�[�W�n���h������EndDialog������B
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


// CProgressDialog ���b�Z�[�W �n���h���[


BOOL CProgressDialog::OnInitDialog()
{
	LOGI << "CProgressDialog::OnInitDialog";
	CDialogEx::OnInitDialog();

	// �v���O���X�o�[�𓮂���
	m_prg_state.SetMarquee(TRUE, 20);

	// �񓯊��������J�n
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

	// �v���O���X�o�[���~�߂�
	m_prg_state.SetMarquee(FALSE, 0);

	try
	{
		// �����ɗ����Ƃ������Ƃ́A�񓯊������͊������Ă���͂�
		// �Ȃ̂�get()�͑҂��Ȃ��Ŏ��s�����͂�
		LOGI << "get�J�n";
		auto result = m_task.get();
		LOGI << "get�I��";

		EndDialog(result ? IDOK : IDCANCEL);
	}
	catch(...)
	{
		// �񓯊��������ŗ�O����
		// (CancelableProcessBase::Do()����catch���Ă���̂ŁA�����ɂ͗��Ȃ��͂�����)
		LOGE << "��O����";
		EndDialog(IDCANCEL);
	}

	return 0;
}
