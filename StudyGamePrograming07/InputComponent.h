#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	//コンストラクタ。Update Orderは早め。
	InputComponent(class Actor* owner, int updateOrder = 10);
	~InputComponent();

	// 入力処理（オーバーライド）
	void ProcessInput(const uint8_t* keyState) override;

	// プライベート関数のゲッター・セッター
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackwardKey(int key) { mBackwardKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

	int GetForwardKey() { return mForwardKey; }
	int GetBackwardKey() { return mBackwardKey; }
	int GetClockwiseKey() { return mClockwiseKey; }
	int GetCounterClockwiseKey() { return mCounterClockwiseKey; }

	void SetMaxForwardForce(float power) { mMaxForwardForce = power; }
	void SetMaxRotForce(float power) { mMaxRotForce = power; }
	float GetMaxForwardForce() { return mMaxForwardForce; }
	float GetMaxRotForce() { return mMaxRotForce; }


private:
	// 前進・後退のためのキー
	int mForwardKey;
	int mBackwardKey;

	//回転運動のキー
	int mClockwiseKey;
	int mCounterClockwiseKey;
	
	// 前進・回転方向の力の最大値
	float mMaxForwardForce;
	float mMaxRotForce;
};

