// ProgressDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ProgressDialog.h"
#include "afxdialogex.h"
#include "plog/Log.h"


// CProgressDialog ダイアログ

IMPLEMENT_DYNAMIC(CProgressDialog, CDialogEx)

CProgressDialog::CProgressDialog(
	CWnd* pParent,
	std::function<bool()> process,
	std::function<void()> canceler)
	: CDialogEx(CProgressDialog::IDD, pParent)
	, m_process(process)
	, m_canceler(canceler)
{
	SetupThread();
}

CProgressDialog::~CProgressDialog()
{
	if (m_thread_pool != nullptr) {
		LOGI << "join";
		m_thread_pool->join();
		LOGI << "waited";
	}
}

void CProgressDialog::SetupThread()
{
	m_processing = true;
	m_task_result = true;

	m_thread_pool = std::make_unique<std::thread>([&]() {
		LOGI << "processing start";
		while (m_processing) {
			std::unique_lock<std::mutex> lock(m_tasks_mutex);
			while (! m_tasks.empty()) {
				// 先頭のタスクを取り出す
				LOGI << "task exporting";
				auto task(std::move(m_tasks.front()));
				m_tasks.pop_front();
				LOGI << "task exported";

				// タスク実行中はロックを解除しておく
				lock.unlock();

				// タスク実行
				LOGI << "task start";
				task();	// 同期処理(終了まで待つ)
				LOGI << "task end";

				lock.lock();

				m_task_result = task.get_future().get();
				if (! m_task_result) {
					break;
				}
			}
			// タスクの失敗判定
			if (! m_task_result) {
				break;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		LOGI << "processing end";

		// スレッド終了時にダイアログを閉じたいが
		// 非UIスレッドからEndDialogを発行するのはMFCのお作法としてNG。
		// ウィンドウハンドルを使って終了メッセージを投げ
		// メッセージハンドラ内で終了させる。
		::PostMessage(m_hWnd, WM_CLOSE_PROGRESS_DIALOG, 0, 0);
	});
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


// CProgressDialog メッセージ ハンドラー


BOOL CProgressDialog::OnInitDialog()
{
	LOGI << "CProgressDialog::OnInitDialog";
	CDialogEx::OnInitDialog();

	m_prg_state.SetMarquee(TRUE, 20);

	std::unique_lock<std::mutex> lock(m_tasks_mutex);
	LOGI << "タスク投入";
	m_tasks.push_back(task_type([&]() -> bool {
		LOGI << "actual process start";
		auto result = m_process();
		LOGI << "actual process end";

		m_prg_state.SetMarquee(FALSE, 0);
		m_processing = false;

		return result;
	}));

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CProgressDialog::OnBnClickedCancel()
{
	m_canceler();
}

LRESULT CProgressDialog::OnCloseProgressDialog(WPARAM wParam, LPARAM lParam)
{
	EndDialog(m_task_result ? IDOK : IDCANCEL);

	return 0;
}
