#pragma once
#include "Actor.h"
class Sphere : public Actor
{
public:
	Sphere(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keys) override;

private:
	class MoveComponent* mMoveComp;
	class AudioComponent* mAudioComp;
};

