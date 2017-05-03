#pragma once
#include <atomic>		// atomic
#include <boost/optional.hpp>
#include <deque>		// deque
#include <functional>	// function
#include <future>		// future, packaged_task
#include <memory>		// shared_ptr
#include <mutex>		// mutex
#include <thread>		// thread

class ICancelable;

class WorkerThreadManager
{
	using task_type = std::packaged_task<bool()>;

	/// <summary>処理実行中に実行したい内容</summary>
	boost::optional<std::function<void()>> m_sub_action;

	/// <summary>スレッド終了時に実行したい内容</summary>
	boost::optional<std::function<void()>> m_post_action;

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

public:
	WorkerThreadManager() = delete;
	explicit WorkerThreadManager(boost::optional<std::function<void()>> sub_action, boost::optional<std::function<void()>> post_action);
	~WorkerThreadManager();

	void push_back(std::shared_ptr<ICancelable> process);
	bool get_result() const;

private:
	bool generate_task(std::shared_ptr<ICancelable> process);
};

