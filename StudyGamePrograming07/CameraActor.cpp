#include "CameraActor.h"
#include "MoveComponent.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "AudioSystem.h"
#include "Game.h"
#include "AudioComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"

CameraActor::CameraActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
	mAudioComp = new AudioComponent(this);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
	mLastFootstep = 0.0f;
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);
	mLengthFromActor = 500.0f;
	mHeightFromActor = 200.0f;
}

void CameraActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// Play the footstep if we're moving and haven't recently
	mLastFootstep -= deltaTime;
	if (!Math::NearZero(mMoveComp->GetVelocity().Length()) && mLastFootstep <= 0.0f)
	{
		mFootstep.SetPaused(false);
		mFootstep.Restart();
		mLastFootstep = 0.5f;
	}

	// Compute new camera from this actor
	mCameraPos = GetPosition() - GetForward() * mLengthFromActor + Vector3::UnitZ * mHeightFromActor;
	Vector3 target = GetPosition() + GetForward() * mLengthFromActor;
	Vector3 up = Vector3::UnitZ;
	Matrix4 view = Matrix4::CreateLookAt(mCameraPos, target, up);		//カメラからアクターへのベクトル＝見ている方向
	GetGame()->GetRenderer()->SetViewMatrix(view);
	GetGame()->GetAudioSystem()->SetListener(view);

}

void CameraActor::ActorInput(const uint8_t* keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// movement
	if (keys[SDL_SCANCODE_UP])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		forwardSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		angularSpeed -= Math::Pi;
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		angularSpeed += Math::Pi;
	}
	mMoveComp->SetVelocity(forwardSpeed * GetForward());
	mMoveComp->SetRotSpeed(angularSpeed);	
}

void CameraActor::SetFootstepSurface(float value)
{
	// Pause here because the way I setup the parameter in FMOD
	// changing it will play a footstep
	mFootstep.SetPaused(true);
	mFootstep.SetParameter("Surface", value);
}
