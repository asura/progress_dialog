#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "WorkerThereadManager.h"

class ICancelable;

// CProgressDialog �_�C�A���O

class CProgressDialog : public CDialogEx
{
	using task_type = std::packaged_task<bool()>;

	std::shared_ptr<ICancelable> m_process;
	std::deque<task_type> m_tasks;

	/// <summary>���������s����X���b�h</summary>
	/// <remarks>
	/// deque(m_tasks)���Ď����A�����^�X�N���o�^���ꂽ����s����B
	/// �^�X�N���o�^����ĂȂ����100�~���b�ҋ@����B
	/// �^�X�N���Ŏ��s���t���O(m_processing)��false�ɂ���邩
	/// �^�X�N�̎��s���ʂ�false�̏ꍇ�ɃX���b�h���I�����A�_�C�A���O�����B
	/// </remarks>
	std::unique_ptr<std::thread> m_thread_pool;
	std::mutex m_tasks_mutex;

	/// <summary>���s���t���O</summary>
	/// <remarks>
	/// ���̒l��false�ɂȂ�ƃX���b�h���~����
	/// </remarks>
	std::atomic<bool> m_processing;

	/// <summary>�^�X�N���s����</summary>
	/// <remarks>
	/// ���̒l��false���ƃX���b�h���~����
	/// </remarks>
	bool m_task_result;

	WorkerThereadManager m_task_manager;

	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent, std::shared_ptr<ICancelable> process);
	virtual ~CProgressDialog();

private:
	void SetupThread();

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
