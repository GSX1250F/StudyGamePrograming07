#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	: Component(owner),
	mVelocity(Vector3::Zero),			// �d�S�ړ����x
	mRotSpeed(0.0f),	// ��]���x
	mMass(1.0f),						// ����
	mMoveForce(Vector3::Zero),			// �d�S�ɂ������
	mMoveAccel(Vector3::Zero),			// �d�S�����x	=�d�S�ɂ������ / ����
	mRotForce(0.0f),	// ��]�����̗�F +������CCW
	mRotAccel(0.0f),	// ��]�����x
	mMoveResist(0.0f),					// �d�S���x��R��(%)
	mRotResist(0.0f),					// ��]���x��R��(%)
	mTorque(0.0f),		// �g���N=��]�����̗� * ���a = �������[�����g * ��]�����x
	mImoment(0.0f)						// �������[�����g
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	// Actor�̈ʒu���X�V
	mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltatime);		//x = xo + vt
	// Actor�̕������X�V
	// Temporary +Z������̉�]�݂̂��s���B
	Quaternion rot = mOwner->GetRotation();
	float angle = mRotSpeed * deltatime;
	// ��]��ǉ�������N�H�[�^�j�I�����쐬
	Quaternion inc(Vector3::UnitZ, angle);
	// ���Ƃ�rot�Ƒ����̃N�H�[�^�j�I��������
	rot = Quaternion::Concatenate(rot, inc);
	mOwner->SetRotation(rot);
	
	// �d�S���x���X�V
	if (!Math::NearZero(mMass))
	{
		//�d�S�����x�̌v�Z�@F=ma  a=F*(1/m)
		mMoveAccel = mMoveForce * (1.0f / mMass);
		//��R�� = ����*��R�W��    ���� = -����*��R�W��/����
		Vector3 movedecel = mVelocity * mMoveResist * 0.01f * (1 / mMass);
		mMoveAccel -= movedecel;
	}
	else { mMoveAccel = Vector3::Zero; }
	mVelocity += mMoveAccel * deltatime;

	// ��]���x���X�V
	// Temporary +Z������̉�]�݂̂��s���B
	// �������[�����g�v�Z	 ��3�����ɂ����ẮA��l���x�̋��Ƃ���B I=0.4*����*���a^2
	mImoment = 0.4f * mMass * mOwner->GetRadius() * mOwner->GetRadius();
	if (!Math::NearZero(mImoment))
	{
		// �g���N�v�Z�@�@�g���N=��]�����̗� * ���a
		mTorque = mRotForce * mOwner->GetRadius();
		// ��]�����x�̌v�Z�@��]�����x = �g���N / �������[�����g
		mRotAccel = mTorque / mImoment;		//��]�����x�̌v�Z Fr=Ia  a=Fr/I
		//��R�� = ����*��R�W��    ���� = -����*��R�W��*���a/�������[�����g
		float rotdecel = mRotSpeed * mOwner->GetRadius() * mRotResist / mImoment;
		mRotAccel -= rotdecel;
	}
	else { mRotAccel = 0.0f; }
	mVelocity += mMoveAccel * deltatime;	//v = vo + at
	mRotSpeed += mRotAccel * deltatime;		//�� = ��o + bt
}
