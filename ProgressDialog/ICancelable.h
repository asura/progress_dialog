#pragma once

/// <summary>�L�����Z��(���f)�\�ȏ����̃C���^�t�F�[�X</summary>
/// <remarks>
/// ��������������N���X�A����ѓ���̏�����K�v�Ƃ���ӏ��ȊO�ł�
/// �{�N���X�Ɉˑ������Ă��������B
/// </remarks>
class ICancelable
{
public:
	virtual ~ICancelable() = default;

	/// <summary>�����{��</summary>
	/// <returns>
	/// ����I�������ꍇ��true��Ԃ��B
	/// �L�����Z�����ꂽ�ꍇ�܂��ُ͈�I�������ꍇ��false��Ԃ��B
	/// </returns>
	/// <remarks>
	/// �h���N���X�Ŏ������Ă��������B
	/// �������̓K�؂ȃL�����Z���|�C���g��ShouldCancel���Ăяo���A
	/// �L�����Z���v�����o����Ă���Ώ����𒆒f���Ă��������B
	/// </remarks>
	virtual bool Do() = 0;

	/// <summary>�L�����Z���v�����o��</summary>
	/// <remarks>
	/// �{���\�b�h�͗v�����o�������ŁA
	/// ������(Do)�œK�؂ɗv�����������Ă��Ȃ��ƒ��f����Ȃ��B
	/// </remarks>
	virtual void Cancel() = 0;
};