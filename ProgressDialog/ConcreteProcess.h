#pragma once
#include "ICancelable.h"

class ConcreteProcess : public ICancelable
{
	bool m_cancel;

public:
	ConcreteProcess() = default;
	~ConcreteProcess() = default;

	bool operator()();

	void Cancel();
};

