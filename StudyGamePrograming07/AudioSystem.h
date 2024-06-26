#pragma once
#include <unordered_map>
#include <string>
#include "SoundEvent.h"
#include "Math.h"

// FMODヘッダーの前方宣言
namespace FMOD
{
	class System;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};
};

class AudioSystem
{
public:
	AudioSystem(class Game* game);
	~AudioSystem();

	bool Initialize();
	void Shutdown();

	// バンクのロード／アンロード
	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();

	SoundEvent PlayEvent(const std::string& name);

	void Update(float deltaTime);

	// 3Dポジショナルオーディオのための関数
	void SetListener(const Matrix4& viewMatrix);
	// Bus制御
	float GetBusVolume(const std::string& name) const;
	bool GetBusPaused(const std::string& name) const;
	void SetBusVolume(const std::string& name, float volume);
	void SetBusPaused(const std::string& name, bool pause);
protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
private:
	// Tracks the next ID to use for event instances
	static unsigned int sNextID;

	class Game* mGame;
	// ロードされたバンクの連想配列。バンクのファイル名をキーとする。
	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	// イベント名からEventDescriptionへの連想配列。FMODがイベントに割り当てた名前（パス形式）とする。
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	// 符号なし整数からイベントインスタンスへの連想配列
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;
	// Busの連想配列
	std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;
	// FMOD studio system
	FMOD::Studio::System* mSystem;
	// FMOD Low-level system (必要時のために)
	FMOD::System* mLowLevelSystem;
};

