#pragma once
#include "resource.h"
#include "afxcmn.h"

// CProgressDialog �_�C�A���O

class CProgressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CProgressDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PROGRESS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CProgressCtrl m_prg_state;
};
