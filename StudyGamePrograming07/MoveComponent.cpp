#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	: Component(owner),
	mVelocity(Vector3::Zero),			// 重心移動速度
	mRotSpeed(0.0f),	// 回転速度
	mMass(1.0f),						// 質量
	mMoveForce(Vector3::Zero),			// 重心にかかる力
	mMoveAccel(Vector3::Zero),			// 重心加速度	=重心にかかる力 / 質量
	mRotForce(0.0f),	// 回転方向の力F +方向はCCW
	mRotAccel(0.0f),	// 回転加速度
	mMoveResist(0.0f),					// 重心速度抵抗率(%)
	mRotResist(0.0f),					// 回転速度抵抗率(%)
	mTorque(0.0f),		// トルク=回転方向の力 * 半径 = 慣性モーメント * 回転加速度
	mImoment(0.0f)						// 慣性モーメント
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	// Actorの位置を更新
	mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltatime);		//x = xo + vt
	// Actorの方向を更新
	// Temporary +Z軸周りの回転のみを行う。
	Quaternion rot = mOwner->GetRotation();
	float angle = mRotSpeed * deltatime;
	// 回転を追加させるクォータニオンを作成
	Quaternion inc(Vector3::UnitZ, angle);
	// もとのrotと増分のクォータニオンを結合
	rot = Quaternion::Concatenate(rot, inc);
	mOwner->SetRotation(rot);
	
	// 重心速度を更新
	if (!Math::NearZero(mMass))
	{
		//重心加速度の計算　F=ma  a=F*(1/m)
		mMoveAccel = mMoveForce * (1.0f / mMass);
		//抵抗力 = 速さ*抵抗係数    減速 = -速さ*抵抗係数/質量
		Vector3 movedecel = mVelocity * mMoveResist * 0.01f * (1 / mMass);
		mMoveAccel -= movedecel;
	}
	else { mMoveAccel = Vector3::Zero; }
	mVelocity += mMoveAccel * deltatime;

	// 回転速度を更新
	// Temporary +Z軸周りの回転のみを行う。
	// 慣性モーメント計算	 ※3次元においては、一様密度の球とする。 I=0.4*質量*半径^2
	mImoment = 0.4f * mMass * mOwner->GetRadius() * mOwner->GetRadius();
	if (!Math::NearZero(mImoment))
	{
		// トルク計算　　トルク=回転方向の力 * 半径
		mTorque = mRotForce * mOwner->GetRadius();
		// 回転加速度の計算　回転加速度 = トルク / 慣性モーメント
		mRotAccel = mTorque / mImoment;		//回転加速度の計算 Fr=Ia  a=Fr/I
		//抵抗力 = 速さ*抵抗係数    減速 = -速さ*抵抗係数*半径/慣性モーメント
		float rotdecel = mRotSpeed * mOwner->GetRadius() * mRotResist / mImoment;
		mRotAccel -= rotdecel;
	}
	else { mRotAccel = 0.0f; }
	mVelocity += mMoveAccel * deltatime;	//v = vo + at
	mRotSpeed += mRotAccel * deltatime;		//ω = ωo + bt
}
