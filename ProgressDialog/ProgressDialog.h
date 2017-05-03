#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "WorkerThereadManager.h"

class ICancelable;

// CProgressDialog ダイアログ

class CProgressDialog : public CDialogEx
{
	using task_type = std::packaged_task<bool()>;

	std::shared_ptr<ICancelable> m_process;
	std::deque<task_type> m_tasks;

	/// <summary>処理を実行するスレッド</summary>
	/// <remarks>
	/// deque(m_tasks)を監視し、もしタスクが登録されたら実行する。
	/// タスクが登録されてなければ100ミリ秒待機する。
	/// タスク側で実行中フラグ(m_processing)がfalseにされるか
	/// タスクの実行結果がfalseの場合にスレッドを終了し、ダイアログを閉じる。
	/// </remarks>
	std::unique_ptr<std::thread> m_thread_pool;
	std::mutex m_tasks_mutex;

	/// <summary>実行中フラグ</summary>
	/// <remarks>
	/// この値がfalseになるとスレッドを停止する
	/// </remarks>
	std::atomic<bool> m_processing;

	/// <summary>タスク実行結果</summary>
	/// <remarks>
	/// この値がfalseだとスレッドを停止する
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
