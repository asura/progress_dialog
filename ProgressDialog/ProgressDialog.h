#pragma once
#include "resource.h"
#include "afxcmn.h"
#include <future>
#include <memory>

class ICancelable;

// CProgressDialog �_�C�A���O

class CProgressDialog : public CDialogEx
{
	/// <summary>�񓯊��������������������e</summary>
	std::shared_ptr<ICancelable> m_process;

	/// <summary>�񓯊������̌��ʂ��i�[</summary>
	std::future<bool> m_task;

	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent, std::shared_ptr<ICancelable> process);
	virtual ~CProgressDialog();

	void ActionWhenThreadEnds();

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
