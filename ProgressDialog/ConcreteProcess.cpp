#include "stdafx.h"
#include "ConcreteProcess.h"
#include "plog/Log.h"

bool ConcreteProcess::Do()
{
	ResetCancel();

	LOGI << "detailed process start";
	int i = 0;
	for (i = 0; i < 1000000000; i++) {
		if (ShouldCancel()) {
			LOGI << "detailed process canceled";
			return false;
		}
	}
	LOGI << "detailed process end";

	return true;
}
