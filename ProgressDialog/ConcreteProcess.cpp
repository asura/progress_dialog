#include "stdafx.h"
#include "ConcreteProcess.h"
#include "plog/Log.h"

bool ConcreteProcess::operator()()
{
	m_cancel = false;

	LOGI << "detailed process start";
	int i = 0;
	for (i = 0; i < 1000000000; i++) {
		if (m_cancel) {
			LOGI << "canceled";
			return false;
		}
	}
	LOGI << "detailed process end";

	return true;
}

void ConcreteProcess::Cancel()
{
	m_cancel = true;
}
