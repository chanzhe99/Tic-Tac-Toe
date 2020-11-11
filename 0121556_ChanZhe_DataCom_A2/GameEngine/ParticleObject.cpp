#include "ParticleObject.h"

ParticleObject::ParticleObject()
{
	Velocity = Acceleration = Vector2();
	CurrentLifetime = MaxLifetime = 0;
}

ParticleObject::ParticleObject(Sprite* DesiredSprite, const Vector2& DesiredVelocity, float DesiredLifetime)
	: GameObject(DesiredSprite)
{
	Velocity = DesiredVelocity;
	MaxLifetime = DesiredLifetime;
	CurrentLifetime = 0.f;
}

ParticleObject::~ParticleObject()
{
}

void ParticleObject::Update(float DeltaTime)
{
	// Apply acceleration (if any)
	Velocity = Velocity + (Acceleration * DeltaTime);

	// Update the position
	Vector2 NewPosition = GetPosition() + (Velocity * DeltaTime);
	SetPosition(NewPosition);

	// Decrease the lifetime of particle every update
	CurrentLifetime += DeltaTime;
}
