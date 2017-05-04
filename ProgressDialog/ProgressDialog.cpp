// ProgressDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ICancelable.h"
#include "ProgressDialog.h"
#include "afxdialogex.h"
#include "plog/Log.h"


// CProgressDialog �_�C�A���O

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
	// �X���b�h�I�����Ƀ_�C�A���O���������
	// ��UI�X���b�h����EndDialog�𔭍s����̂�MFC�̂���@�Ƃ���NG�B
	// �E�B���h�E�n���h�����g���ďI�����b�Z�[�W�𓊂�
	// ���b�Z�[�W�n���h�����ŏI��������B
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


// CProgressDialog ���b�Z�[�W �n���h���[


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
