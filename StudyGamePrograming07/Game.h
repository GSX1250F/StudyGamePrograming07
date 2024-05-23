#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"
#include "CameraActor.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() { return mRenderer; }
	class AudioSystem* GetAudioSystem() { return mAudioSystem; }

	void SetRunning(bool isrunning) { mIsRunning = isrunning; }

	//�Q�[���E�B���h�E�̑傫��
	int mWindowWidth;
	int mWindowHeight;

	// Game-specific
	class CameraActor* GetCamera() { return mCameraActor; }

private:
	void ProcessInput();
	void HandleKeyPress(int key);
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// ���ׂẴA�N�^�[
	std::vector<class Actor*> mActors;
	// ���ׂĂ̑҂��A�N�^�[
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;

	Uint32 mTicksCount;
	bool mIsRunning;
	// �A�N�^�[���X�V����
	bool mUpdatingActors;

	// Game-specific
	class CameraActor* mCameraActor;
	SoundEvent mMusicEvent;
	SoundEvent mReverbSnap;
	class Actor* mSphere;
};