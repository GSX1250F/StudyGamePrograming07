#include "AudioComponent.h"
#include "Actor.h"
#include "Game.h"
#include "AudioSystem.h"

AudioComponent::AudioComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}

AudioComponent::~AudioComponent()
{
	StopAllEvents();
}

void AudioComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	// mEvents2D�̖����ɂȂ����C�x���g���폜����
	auto iter = mEvents2D.begin();
	while (iter != mEvents2D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents2D.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// mEvents3D�̖����ɂȂ����C�x���g���폜����
	iter = mEvents3D.begin();
	while (iter != mEvents3D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents3D.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void AudioComponent::OnUpdateWorldTransform()
{
	// Update 3D events' world transforms
	Matrix4 world = mOwner->GetWorldTransform();

	// Practice �R�l�̃��X�i�[�Ή��B���z�|�W�V�������v�Z����
	// ���z�|�W�V���� = |�v���C���[�ƃT�E���h�̋���|/|�J�����ƃT�E���h�̋���|*�J��������T�E���h�̃x�N�g��
	Vector3 soundpos = mOwner->GetPosition();	//�T�E���h�̈ʒu
	Vector3 camerapos = mOwner->GetGame()->GetCamera()->GetCameraPosition();
	Vector3 playerpos = mOwner->GetGame()->GetCamera()->GetPosition();
	Vector3 virtualpos = (playerpos - soundpos).Length() / (camerapos - soundpos).Length() * (soundpos - camerapos);
	world = Matrix4::CreateScale(mOwner->GetScale());
	world *= Matrix4::CreateTranslation(virtualpos);


	for (auto& event : mEvents3D)
	{
		if (event.IsValid())
		{
			event.Set3DAttributes(world);
		}
	}
}

SoundEvent AudioComponent::PlayEvent(const std::string& name)
{
	SoundEvent e = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
	// 2D or 3D?
	if (e.Is3D())
	{
		mEvents3D.emplace_back(e);
		// 3D������������
		e.Set3DAttributes(mOwner->GetWorldTransform());
	}
	else
	{
		mEvents2D.emplace_back(e);
	}
	return e;
}

void AudioComponent::StopAllEvents()
{
	// ���ׂẴT�E���h���X�g�b�v
	for (auto& e : mEvents2D)
	{
		e.Stop();
	}
	for (auto& e : mEvents3D)
	{
		e.Stop();
	}
	// �C�x���g���N���A
	mEvents2D.clear();
	mEvents3D.clear();
}
