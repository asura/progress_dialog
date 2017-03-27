#pragma once
#include "CancelableProcessBase.h"

class ConcreteProcess : public CancelableProcessBase
{
public:
	ConcreteProcess() = default;
	~ConcreteProcess() = default;

	bool Do();
};

