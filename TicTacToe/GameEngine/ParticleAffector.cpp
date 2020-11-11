#include "ParticleAffector.h"

ParticleAffectorColor::ParticleAffectorColor(const Color& Start, const Color& End)
{
	StartColor = Start;
	EndColor = End;
}
void ParticleAffectorColor::AffectParticleUpdate(ParticleObject* Particle)
{
	ParticleLerpPercent = Particle->GetCurrentLifetime() / Particle->GetMaxLifetime();

	NewColor.R = Lerp(StartColor.R, EndColor.R, ParticleLerpPercent);
	NewColor.G = Lerp(StartColor.G, EndColor.G, ParticleLerpPercent);
	NewColor.B = Lerp(StartColor.B, EndColor.B, ParticleLerpPercent);
	NewColor.A = Lerp(StartColor.A, EndColor.A, ParticleLerpPercent);

	Particle->SetColor(NewColor);
}



ParticleAffectorScale::ParticleAffectorScale(const Vector2& Start, const Vector2& End)
{
	StartScale = Start;
	EndScale = End;
}
void ParticleAffectorScale::AffectParticleUpdate(ParticleObject* Particle)
{
	ParticleLerpPercent = Particle->GetCurrentLifetime() / Particle->GetMaxLifetime();

	NewScale.X = Lerp(StartScale.X, EndScale.X, ParticleLerpPercent);
	NewScale.Y = Lerp(StartScale.Y, EndScale.Y, ParticleLerpPercent);

	Particle->SetScale(NewScale);
}



ParticleAffectorRotation::ParticleAffectorRotation(float Start, float End)
{
	StartRotation = Start;
	EndRotation = End;
}
void ParticleAffectorRotation::AffectParticleUpdate(ParticleObject* Particle)
{
	ParticleLerpPercent = Particle->GetCurrentLifetime() / Particle->GetMaxLifetime();

	NewRotation = Lerp(StartRotation, EndRotation, ParticleLerpPercent);

	Particle->SetRotation(NewRotation);
}



ParticleAffectorGravity::ParticleAffectorGravity(const Vector2& Start, const Vector2& End)
{
	StartGravity = Start;
	EndGravity = End;
}
void ParticleAffectorGravity::AffectParticleUpdate(ParticleObject* Particle)
{
	ParticleLerpPercent = Particle->GetCurrentLifetime() / Particle->GetMaxLifetime();

	NewGravity.X = Lerp(StartGravity.X, EndGravity.X, ParticleLerpPercent);
	NewGravity.Y = Lerp(StartGravity.Y, EndGravity.Y, ParticleLerpPercent);

	Particle->SetAcceleration(NewGravity);
}
