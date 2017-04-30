#pragma once
#include "ICancelable.h"

/// <summary>各種処理のベースクラス</summary>
/// <remarks>
/// 本クラスでは、派生クラスでの実装用に
/// DoImpl()、ShouldCancel()を提供します。
/// </remarks>
class CancelableProcessBase : public ICancelable
{
	bool m_should_cancel;

public:
	CancelableProcessBase();
	virtual ~CancelableProcessBase() = default;

	bool Do();
	void Cancel();

protected:
	/// <remarks>
	/// 派生クラスで実装してください
	/// </remarks>
	virtual bool DoImpl() = 0;

	/// <summary>キャンセル処理すべきかどうかを返す</summary>
	bool ShouldCancel() const;

private:
	void ResetCancel();
};