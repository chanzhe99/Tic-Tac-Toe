#pragma once
#include <list>
#include "ParticleObject.h"
#include "ParticleAffector.h"
#include "ParticleEmitter.h"

//! EmitterShape enumerator
enum class EmitterShape
{
	Point,
	Box,
	Circle,
	Ring
};

//! ParticleSystem class
class ParticleSystem
{
private:
	Vector2 Position;
	float EmissionCount, EmissionRate, EmissionCooldown;
	float ParticleSystemMaxLifetime, ParticleSystemCurrentLifetime;
	
	Sprite* ParticleSprite;
	float ParticleRotation;
	Vector2 ParticleScale;
	Color ParticleColor;
	Vector2 ParticleGravity;
	Vector2 ParticleVelocity;
	float ParticleLifetime;
	bool IsRandomVelocity;

	std::list<ParticleObject*> ParticleList;
	std::list<ParticleAffector*> AffectorList;

	ParticleAffectorColor* ColorAffector;
	ParticleAffectorScale* ScaleAffector;
	ParticleAffectorRotation* RotationAffector;
	ParticleAffectorGravity* GravityAffector;

	EmitterShape ParticleEmitterShape;
	ParticleEmitterBox* BoxEmitter = new ParticleEmitterBox();
	ParticleEmitterCircle* CircleEmitter = new ParticleEmitterCircle();
	ParticleEmitterRing* RingEmitter = new ParticleEmitterRing();

public:
	//! Initialises a ParticleSystem instance with default values
	ParticleSystem();
	//! Initialises a ParticleSystem instance that takes in a Sprite pointer and a Vector2 reference for position
	ParticleSystem(Sprite* DesiredSprite, const Vector2& DesiredPosition);
	~ParticleSystem();

	//! Returns a float of the ParticleSystem's max lifetime
	float GetParticleSystemMaxLifetime() { return ParticleSystemMaxLifetime; }
	//! Returns a float of the ParticleSystem's current lifetime
	float GetParticleSystemCurrentLifetime() { return ParticleSystemCurrentLifetime; }

	//! Takes in a Vector2 reference and sets the ParticleSystem's position
	void SetPosition(const Vector2& DesiredPosition) { Position = DesiredPosition; }
	//! Takes in a float and sets the ParticleSystem's EmissionCount
	void SetEmissionCount(float DesiredCount) { EmissionCount = DesiredCount; }
	//! Takes in a float and sets the ParticleSystem's EmissionRate
	void SetEmissionRate(float DesiredRate) { EmissionRate = 1 / DesiredRate; EmissionCooldown = EmissionRate; }
	//! Takes in a float and sets the ParticleSystem's MaxLifetime
	void SetMaxLifetime(float DesiredMaxLifetime) { ParticleSystemMaxLifetime = DesiredMaxLifetime; }

	//! Takes in a Sprite pointer and sets the Particles' Sprite
	void SetParticleSprite(Sprite* DesiredSprite) { ParticleSprite = DesiredSprite; }
	//! Takes in a float and sets the Particles' rotation in degrees
	void SetParticleRotation(float DesiredRotation) { ParticleRotation = DesiredRotation; }
	//! Takes in a Vector2 reference and sets the Particles' size
	void SetParticleScale(const Vector2& DesiredScale) { ParticleScale = DesiredScale; }
	//! Takes in a Color reference and sets the Particles' Color
	void SetParticleColor(const Color& DesiredColor) { ParticleColor = DesiredColor; }
	//! Takes in a bool and sets whether or not the Particles' will have random velocity at spawn
	void SetParticleRandomVelocity(bool IsRandom) { IsRandomVelocity = IsRandom; }
	//! Takes in a Vector2 reference and sets the Particles' velocity
	void SetParticleVelocity(const Vector2& DesiredVelocity) { IsRandomVelocity = false; ParticleVelocity = DesiredVelocity; }
	//! Takes in a Vector2 reference and sets the Particles' gravity/acceleration
	void SetParticleGravity(const Vector2& DesiredGravity) { ParticleGravity = DesiredGravity; }
	//! Takes in a Vector2 reference and sets the Particles' max lifetime
	void SetParticleLifetime(float DesiredLifetime) { ParticleLifetime = DesiredLifetime; }

	//! Takes in a float and sets the RotationAffector's end rotation
	void SetAffectorRotation(float EndRotation);
	//! Takes in a Vector2 reference and sets the ParticleAffector's end size
	void SetAffectorScale(const Vector2& EndScale);
	//! Takes in a Color reference and sets the ParticleAffector's end Color
	void SetAffectorColor(const Color& EndColor);
	//! Takes in a Vector2 reference and sets the ParticleAffector's end gravity
	void SetAffectorGravity(const Vector2& EndGravity);

	//! Sets the ParticleSystem's EmitterShape to point emitter
	void SetEmitterPoint() { ParticleEmitterShape = EmitterShape::Point; }
	//! Takes in a Vector2 reference and sets the ParticleSystem's EmitterShape to box emitter, setting the box size
	void SetEmitterBox(const Vector2& DesiredBoxSize);
	//! Takes in a float and sets the ParticleSystem's EmitterShape to circle emitter, setting the circle radius
	void SetEmitterCircle(float DesiredRadius);
	//! Takes in 2 floats and sets the ParticleSystem's EmitterShape to ring emitter, setting the inner & outer radius
	void SetEmitterRing(float DesiredInnerRadius, float DesiredOuterRadius);

	//! Updates the ParticleSystem
	void Update(float DeltaTime);
	//! Draws the ParticleSystem
	void Draw();
};