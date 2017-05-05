#pragma once
#include "resource.h"
#include "afxcmn.h"
#include <future>
#include <memory>

class ICancelable;

// CProgressDialog ダイアログ

class CProgressDialog : public CDialogEx
{
	/// <summary>非同期処理させたい処理内容</summary>
	std::shared_ptr<ICancelable> m_process;

	/// <summary>非同期処理の結果を格納</summary>
	std::future<bool> m_task;

	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent, std::shared_ptr<ICancelable> process);
	virtual ~CProgressDialog();

	void ActionWhenThreadEnds();

public:
// ダイアログ データ
	enum { IDD = IDD_PROGRESS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	afx_msg LRESULT OnCloseProgressDialog(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CProgressCtrl m_prg_state;
public:
	afx_msg void OnBnClickedCancel();
};
