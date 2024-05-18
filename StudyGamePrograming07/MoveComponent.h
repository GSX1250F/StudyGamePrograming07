#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	//�R���X�g���N�^�BUpdate Order�͑��߁B
	MoveComponent(class Actor* owner, int updateOrder = 10);
	~MoveComponent();

	//Update���I�[�o�[���C�h
	void Update(float deltatime) override;

	// �P���ɓ������̂ɕK�v�ȃp�����[�^�̃Z�b�^�[���Q�b�^�[
	// ���x
	Vector3 GetVelocity() { return mVelocity; }
	void SetVelocity(Vector3 vel) { mVelocity = vel; }
	// ��]���x
	float GetRotSpeed() const { return mRotSpeed; }
	void SetRotSpeed(float rotspeed) { mRotSpeed = rotspeed; }

	// �ÓT�����ɕK�v�ȃp�����[�^�̃Z�b�^�[���Q�b�^�[
	//�d�S�ɂ������
	Vector3 GetMoveForce() { return mMoveForce; }
	void SetMoveForce(Vector3 forceVector) { mMoveForce = forceVector; }
	//��]�����̗�
	float GetRotForce() { return mRotForce; }
	void SetRotForce(float force) { mRotForce = force; }
	//�d�S�ړ��̒�R��
	float GetMoveResist() { return mMoveResist; }
	void SetMoveResist(float resist) { mMoveResist = resist; }
	//��]�ړ��̒�R��
	float GetRotResist() { return mRotResist; }
	void SetRotResist(float resist) { mRotResist = resist; }
	// ����
	float GetMass() { return mMass; }
	void SetMass(float mass) { mMass = mass; }
	// �g���N
	float GetTorque() { return mTorque; }
	void SetTorque(float torque) { mTorque = torque; }
	// �������[�����g
	float GetImoment() { return mImoment; }
	void SetImoment(float imoment) { mImoment = imoment; }


private:
	// �P���ړ��p�����[�^
	Vector3 mVelocity;		// �d�S�ړ����x
	float mRotSpeed;		// ��]���x

	// �ÓT�����p�����[�^
	float mMass;			// ����
	Vector3 mMoveForce;		// �d�S�ɂ������
	float mRotForce;		// ��]�����̗�F +������CCW  ��temporary�@��]��z�����肾��
	float mTorque;			// �g���N=��]�����̗� * ���a = �������[�����g * ��]�����x  ��temporary�@��]��z�����肾��
	Vector3 mMoveAccel;		// �d�S�����x	=�d�S�ɂ������ / ����  
	float mRotAccel;		// ��]�����x  ��temporary�@��]��z�����肾��
	float mImoment;			// �������[�����g
	float mMoveResist;		// �d�S���x��R��(%)
	float mRotResist;		// ��]���x��R��(%)
};

