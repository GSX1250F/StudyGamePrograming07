#include "Sphere.h"
#include "MoveComponent.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "AudioSystem.h"
#include "Game.h"
#include "AudioComponent.h"
#include "MeshComponent.h"

Sphere::Sphere(Game* game)
	:Actor(game)
{
	SetPosition(Vector3(500.0f, -75.0f, 0.0f));
	SetScale(1.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
	AudioComponent* ac = new AudioComponent(this);
	ac->PlayEvent("event:/FireLoop");

	mMoveComp = new MoveComponent(this);
	mAudioComp = new AudioComponent(this);

	mMoveComp->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
}

void Sphere::UpdateActor(float deltaTime)
{
	if (GetPosition().x > 1000.0f)
	{
		SetPosition(Vector3(-1000.0f, -75.0f, 0.0f));
	}
}

void Sphere::ActorInput(const uint8_t* keys)
{
}
