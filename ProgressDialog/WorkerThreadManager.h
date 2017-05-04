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

	/// <summary>�������s���Ɏ��s���������e</summary>
	boost::optional<std::function<void()>> m_sub_action;

	/// <summary>�X���b�h�I�����Ɏ��s���������e</summary>
	boost::optional<std::function<void()>> m_post_action;

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

public:
	WorkerThreadManager() = delete;
	explicit WorkerThreadManager(boost::optional<std::function<void()>> sub_action, boost::optional<std::function<void()>> post_action);
	~WorkerThreadManager();

	void push_back(std::shared_ptr<ICancelable> process);
	bool get_result() const;

private:
	bool generate_task(std::shared_ptr<ICancelable> process);
};

