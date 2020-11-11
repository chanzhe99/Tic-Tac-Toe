#pragma once
#include "ParticleObject.h"


//! ParticleAffector class
class ParticleAffector
{
protected:
	float ParticleLerpPercent;
	//! Returns a linear interpolated float based on the given parameters
	float Lerp(float StartValue, float EndValue, float InterpolationValue)
	{ return StartValue + InterpolationValue * (EndValue - StartValue); }

public:
	//! Updates the ParticleAffector's effects
	virtual void AffectParticleUpdate(ParticleObject* Particle) = 0;
};


//! ParticleAffectorColor class, child of ParticleAffector class
class ParticleAffectorColor : public ParticleAffector
{
private:
	Color StartColor, EndColor, NewColor;

public:
	//! Takes in 2 Color references and sets the ParticleAffector's start Color and end Color
	ParticleAffectorColor(const Color& Start, const Color& End);
	//! Updates the ParticleAffector's effects
	void AffectParticleUpdate(ParticleObject* Particle) override;

};


//! ParticleAffectorScale class, child of ParticleAffector class
class ParticleAffectorScale : public ParticleAffector
{
private:
	Vector2 StartScale, EndScale, NewScale;

public:
	//! Takes in 2 Vector2 references and sets the ParticleAffector's start size and end size
	ParticleAffectorScale(const Vector2& Start, const Vector2& End);
	//! Updates the ParticleAffector's effects
	void AffectParticleUpdate(ParticleObject* Particle) override;
};


//! ParticleAffectorRotation class, child of ParticleAffector class
class ParticleAffectorRotation : public ParticleAffector
{
private:
	float StartRotation, EndRotation, NewRotation = 0;

public:
	//! Takes in 2 floats and sets the ParticleAffector's start rotation and end rotation in degrees
	ParticleAffectorRotation(float Start, float End);
	//! Updates the ParticleAffector's effects
	void AffectParticleUpdate(ParticleObject* Particle) override;

};


//! ParticleAffectorGravity class, child of ParticleAffector class
class ParticleAffectorGravity : public ParticleAffector
{
private:
	Vector2 StartGravity, EndGravity, NewGravity;

public:
	//! Takes in 2 Vector2 references and sets the ParticleAffector's start gravity and end gravity
	ParticleAffectorGravity(const Vector2& Start, const Vector2& End);
	//! Updates the ParticleAffector's effects
	void AffectParticleUpdate(ParticleObject* Particle) override;
};
