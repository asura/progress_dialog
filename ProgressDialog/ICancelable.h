#pragma once

class ICancelable
{
public:
	virtual ~ICancelable() = default;

	virtual void Cancel() = 0;
};