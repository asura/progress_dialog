#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "WorkerThreadManager.h"

class ICancelable;

// CProgressDialog �_�C�A���O

class CProgressDialog : public CDialogEx
{
	WorkerThreadManager m_task_manager;
	std::shared_ptr<ICancelable> m_process;

	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent, std::shared_ptr<ICancelable> process);
	virtual ~CProgressDialog();

	void ActionWhenThreadEnds();
	void ActionWhenProcessExecutes();

private:
	using action_type = void(CProgressDialog::*)();

	boost::optional<std::function<void()>> generate_action(action_type action);

public:
// �_�C�A���O �f�[�^
	enum { IDD = IDD_PROGRESS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	afx_msg LRESULT OnCloseProgressDialog(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CProgressCtrl m_prg_state;
public:
	afx_msg void OnBnClickedCancel();
};
