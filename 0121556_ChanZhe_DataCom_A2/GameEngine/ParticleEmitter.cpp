#include "ParticleEmitter.h"
#include "Matrix.h"

Vector2 ParticleEmitterBox::GetParticleEmissionPosition(Vector2* ParticleSystemPosition)
{
	NewPosition.X = RandomFloat(-BoxSize.X, BoxSize.X);
	NewPosition.Y = RandomFloat(-BoxSize.Y, BoxSize.Y);

	return NewPosition + *ParticleSystemPosition;
}



Vector2 ParticleEmitterCircle::GetParticleEmissionPosition(Vector2* ParticleSystemPosition)
{
	// Converts random degree (0 - 360) to Radian
	float RandomRadian = RandomFloat(0, 360) * M_PI / 180;
	float RandomRadius = RandomFloat(0, Radius);
	
	NewPosition = Vector2(cos(RandomRadian), sin(RandomRadian)) * RandomRadius;

	return NewPosition + *ParticleSystemPosition;
}



void ParticleEmitterRing::SetRingRadius(float DesiredInnerRadius, float DesiredOuterRadius)
{
	InnerRadius = DesiredInnerRadius;
	OuterRadius = DesiredOuterRadius;
}
Vector2 ParticleEmitterRing::GetParticleEmissionPosition(Vector2* ParticleSystemPosition)
{
	// Converts random degree (0 - 360) to Radian
	float RandomRadian = RandomFloat(0, 360) * M_PI / 180;
	float RandomRadius = RandomFloat(InnerRadius, OuterRadius);

	NewPosition = Vector2(cos(RandomRadian), sin(RandomRadian)) * RandomRadius;

	return NewPosition + *ParticleSystemPosition;
}
