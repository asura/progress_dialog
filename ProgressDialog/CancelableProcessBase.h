#pragma once
#include "ICancelable.h"

/// <summary>�e�폈���̃x�[�X�N���X</summary>
/// <remarks>
/// �{�N���X�ł́A�h���N���X�ł̎����p��
/// DoImpl()�AShouldCancel()��񋟂��܂��B
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
	/// �h���N���X�Ŏ������Ă�������
	/// </remarks>
	virtual bool DoImpl() = 0;

	/// <summary>�L�����Z���������ׂ����ǂ�����Ԃ�</summary>
	bool ShouldCancel() const;

private:
	void ResetCancel();
};