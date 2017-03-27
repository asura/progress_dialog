#pragma once
#include "stdafx.h"
#include "CancelableProcessBase.h"

CancelableProcessBase::CancelableProcessBase()
	: m_should_cancel(false)
{
}

void CancelableProcessBase::Cancel()
{
	m_should_cancel = true;
}

bool CancelableProcessBase::Do()
{
	ResetCancel();
	return DoImpl();
}

void CancelableProcessBase::ResetCancel()
{
	m_should_cancel = false;
}

bool CancelableProcessBase::ShouldCancel() const
{
	return m_should_cancel;
}
