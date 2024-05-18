#include "InputComponent.h"
#include "Actor.h"

//OpenGL用の座標系に修正

InputComponent::InputComponent(Actor* owner, int updateOrder) 
	: MoveComponent(owner)
	, mForwardKey(0)
	, mBackwardKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	//古典物理学でMoveComponentのための計算
	//MoveComponentには前進か回転方向の力の最大値だけを渡す
	float forwardforce = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardforce += mMaxForwardForce;
	}
	else if (keyState[mBackwardKey])
	{
		forwardforce -= mMaxForwardForce;
	}
	SetMoveForce(forwardforce * mOwner->GetForward());
	
	float rotforce = 0.0f;
	if (keyState[mClockwiseKey])
	{
		rotforce -= mMaxRotForce;		//角度の＋方向はCCW
	}
	else if (keyState[mCounterClockwiseKey])
	{
		rotforce += mMaxRotForce;		//角度の＋方向はCCW
	}
	SetRotForce(rotforce);

}

