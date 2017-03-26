#pragma once
#include "resource.h"
#include "afxcmn.h"

// CProgressDialog ダイアログ

class CProgressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CProgressDialog();

// ダイアログ データ
	enum { IDD = IDD_PROGRESS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CProgressCtrl m_prg_state;
};
