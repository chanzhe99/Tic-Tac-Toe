#pragma once
#include <cstdlib>
#include "Vector2.h"


//! ParticleEmitter class
class ParticleEmitter
{
protected:
	Vector2 NewPosition;
	//! Returns a random float based on the given parameters
	float RandomFloat(float MinRandomValue, float MaxRandomValue)
	{ return ((float)rand() / RAND_MAX) * (MaxRandomValue - MinRandomValue) + MinRandomValue; }

public:
	//! Instantiates a ParticleEmitter with default values
	ParticleEmitter() { NewPosition = Vector2(); }
	//! Returns a Vector2 of the new Particle spawn position
	virtual Vector2 GetParticleEmissionPosition(Vector2* ParticleSystemPosition) = 0;
};


//! ParticleEmitterBox class, child of ParticleEmitter class
class ParticleEmitterBox : ParticleEmitter
{
private:
	Vector2 BoxSize;

public:
	//! Instantiates a ParticleEmitterBox with default values
	ParticleEmitterBox() { BoxSize = Vector2(1, 1); };
	//! Takes in a Vector2 reference and sets the ParticleEmitterBox's size
	void SetBoxSize(const Vector2& DesiredBoxSize) { BoxSize = DesiredBoxSize; BoxSize = BoxSize * 0.5f; }
	//! Returns a Vector2 of the new Particle spawn position
	virtual Vector2 GetParticleEmissionPosition(Vector2* ParticleSystemPosition) override;
};


//! ParticleEmitterCircle class, child of ParticleEmitter class
class ParticleEmitterCircle : ParticleEmitter
{
private:
	float Radius;

public:
	//! Instantiates a ParticleEmitterCircle with default values
	ParticleEmitterCircle() { Radius = 1; }
	//! Takes in a float and sets the ParticleEmitterCircle's radius
	void SetCircleRadius(float DesiredRadius) { Radius = DesiredRadius; }
	//! Returns a Vector2 of the new Particle spawn position
	virtual Vector2 GetParticleEmissionPosition(Vector2* ParticleSystemPosition) override;
};


//! ParticleEmitterRing class, child of ParticleEmitter class
class ParticleEmitterRing : ParticleEmitter
{
private:
	float InnerRadius, OuterRadius;

public:
	//! Instantiates a ParticleEmitterRing with default values
	ParticleEmitterRing() { InnerRadius = OuterRadius = 1; }
	//! Takes in 2 floats and sets the ParticleEmitterRing's inner & outer radius
	void SetRingRadius(float DesiredInnerRadius, float DesiredOuterRadius);
	//! Returns a Vector2 of the new Particle spawn position
	virtual Vector2 GetParticleEmissionPosition(Vector2* ParticleSystemPosition) override;
};