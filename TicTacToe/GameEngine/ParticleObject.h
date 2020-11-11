#pragma once
#include "GameObject.h"

//! ParticleObject class, child of GameObject
class ParticleObject : public GameObject
{
private:
	Vector2 Velocity, Acceleration;
	float MaxLifetime, CurrentLifetime;

public:
	//! Initialises a ParticleObject instance with default values
	ParticleObject();
	//! Initialises a ParticleObject instance that takes in Sprite pointer, Vector2 reference for velocity, and float for max lifetime
	ParticleObject(Sprite* DesiredSprite, const Vector2& DesiredVelocity, float DesiredLifetime);
	~ParticleObject();
	//! Returns a Vector2 of the ParticleObject's velocity
	Vector2 GetVelocity() { return Velocity; }
	//! Returns a Vector2 of the ParticleObject's acceleration
	Vector2 GetAcceleration() { return Acceleration; }
	//! Returns a float of the ParticleObject's max lifetime
	float GetMaxLifetime() { return MaxLifetime; }
	//! Returns a float of the ParticleObject's current lifetime
	float GetCurrentLifetime() { return CurrentLifetime; }
	//! Takes in a Vector2 reference and sets the ParticleObject's velocity
	void SetVelocity(const Vector2& DesiredVelocity) { Velocity = DesiredVelocity; }
	//! Takes in a Vector2 reference and sets the ParticleObject's acceleration
	void SetAcceleration(const Vector2& DesiredAcceleration) { Acceleration = DesiredAcceleration; }
	//! Takes in a float and sets the ParticleObject's max lifetime
	void SetMaxLifetime(float DesiredMaxLifetime) { MaxLifetime = DesiredMaxLifetime; }
	//! Takes in a float and sets the ParticleObject's current lifetime
	void SetCurrentLifetime(float DesiredCurrentLifetime) { CurrentLifetime = DesiredCurrentLifetime; }

	//! Updates the ParticleObject
	void Update(float DeltaTime);
};