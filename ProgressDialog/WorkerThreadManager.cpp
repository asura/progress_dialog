#include "stdafx.h"
#include "ICancelable.h"
#include "WorkerThreadManager.h"
#include "plog/Log.h"

WorkerThreadManager::WorkerThreadManager(
	boost::optional<std::function<void()>> sub_action,
	boost::optional<std::function<void()>> post_action)
{
	m_sub_action = sub_action;
	m_post_action = post_action;

	m_processing = true;
	m_task_result = true;

	m_thread_pool = std::make_unique<std::thread>([&]() {
		LOGI << "processing start";
		while (m_processing) {
			std::unique_lock<std::mutex> lock(m_tasks_mutex);
			while (!m_tasks.empty()) {
				// �擪�̃^�X�N�����o��
				LOGI << "task exporting";
				auto task(std::move(m_tasks.front()));
				m_tasks.pop_front();
				LOGI << "task exported";

				// �^�X�N���s���̓��b�N���������Ă���
				lock.unlock();

				// �^�X�N���s
				LOGI << "task start";
				task();	// ��������(�I���܂ő҂�)
				LOGI << "task end";

				lock.lock();

				m_task_result = task.get_future().get();
				if (!m_task_result) {
					break;
				}
			}
			// �^�X�N�̎��s����
			if (!m_task_result) {
				break;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		LOGI << "processing end";

		if (m_post_action)
		{
			(*m_post_action)();
		}
	});
}

WorkerThreadManager::~WorkerThreadManager()
{
	if (m_thread_pool != nullptr) {
		LOGI << "join";
		m_thread_pool->join();
		LOGI << "waited";
	}
}

void WorkerThreadManager::push_back(std::shared_ptr<ICancelable> process)
{
	assert(process);

	std::unique_lock<std::mutex> lock(m_tasks_mutex);
	LOGI << "�^�X�N����";
	m_tasks.push_back(task_type([&, process]() -> bool {
		return generate_task(process);
	}));
}

bool WorkerThreadManager::get_result() const
{
	return m_task_result;
}

bool WorkerThreadManager::generate_task(std::shared_ptr<ICancelable> process)
{
	LOGI << "actual process start";
	auto result = process->Do();
	LOGI << "actual process end";

	if (m_sub_action)
	{
		(*m_sub_action)();
	}
	m_processing = false;

	return result;
}
