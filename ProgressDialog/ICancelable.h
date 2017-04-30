#pragma once

/// <summary>キャンセル(中断)可能な処理のインタフェース</summary>
/// <remarks>
/// 処理を実装するクラス、および特定の処理を必要とする箇所以外では
/// 本クラスに依存させてください。
/// </remarks>
class ICancelable
{
public:
	virtual ~ICancelable() = default;

	/// <summary>処理本体</summary>
	/// <returns>
	/// 正常終了した場合はtrueを返す。
	/// キャンセルされた場合または異常終了した場合はfalseを返す。
	/// </returns>
	/// <remarks>
	/// 派生クラスで実装してください。
	/// 処理中の適切なキャンセルポイントでShouldCancelを呼び出し、
	/// キャンセル要求が出されていれば処理を中断してください。
	/// </remarks>
	virtual bool Do() = 0;

	/// <summary>キャンセル要求を出す</summary>
	/// <remarks>
	/// 本メソッドは要求を出すだけで、
	/// 処理側(Do)で適切に要求を処理していないと中断されない。
	/// </remarks>
	virtual void Cancel() = 0;
};