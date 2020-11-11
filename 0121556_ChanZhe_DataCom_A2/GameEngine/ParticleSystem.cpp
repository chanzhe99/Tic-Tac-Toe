#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	SetEmissionCount(5);
	SetEmissionRate(10);

	SetMaxLifetime(0);
	ParticleSystemCurrentLifetime = 0;

	SetParticleSprite(new Sprite());
	SetPosition(Vector2(320, 240));
	SetParticleRotation(0);
	SetParticleScale(Vector2(1, 1));
	SetParticleColor(Color::White);
	SetParticleGravity(Vector2());
	SetParticleRandomVelocity(true);
	SetParticleLifetime(5);
}

ParticleSystem::ParticleSystem(Sprite* DesiredSprite, const Vector2& DesiredPosition)
{
	SetEmissionCount(5);
	SetEmissionRate(10);

	SetMaxLifetime(0);
	ParticleSystemCurrentLifetime = 0;

	SetParticleSprite(DesiredSprite);
	SetPosition(DesiredPosition);
	SetParticleRotation(0);
	SetParticleScale(Vector2(1, 1));
	SetParticleColor(Color::White);
	SetParticleGravity(Vector2());
	SetParticleRandomVelocity(true);
	SetParticleLifetime(5);
}

ParticleSystem::~ParticleSystem()
{
}


void ParticleSystem::SetAffectorRotation(float EndRotation)
{
	RotationAffector = new ParticleAffectorRotation(0, EndRotation);
	AffectorList.push_back(RotationAffector);
}
void ParticleSystem::SetAffectorScale(const Vector2& EndScale)
{
	ScaleAffector = new ParticleAffectorScale(ParticleScale, EndScale);
	AffectorList.push_back(ScaleAffector);
}
void ParticleSystem::SetAffectorColor(const Color& EndColor)
{
	ColorAffector = new ParticleAffectorColor(ParticleColor, EndColor);
	AffectorList.push_back(ColorAffector);
}
void ParticleSystem::SetAffectorGravity(const Vector2& EndGravity)
{
	GravityAffector = new ParticleAffectorGravity(Vector2(), EndGravity);
	AffectorList.push_back(GravityAffector);
}


void ParticleSystem::SetEmitterBox(const Vector2& DesiredBoxSize)
{
	BoxEmitter->SetBoxSize(DesiredBoxSize);
	ParticleEmitterShape = EmitterShape::Box;
}
void ParticleSystem::SetEmitterCircle(float DesiredRadius)
{
	CircleEmitter->SetCircleRadius(DesiredRadius);
	ParticleEmitterShape = EmitterShape::Circle;
}
void ParticleSystem::SetEmitterRing(float DesiredInnerRadius, float DesiredOuterRadius)
{
	RingEmitter->SetRingRadius(DesiredInnerRadius, DesiredOuterRadius);
	ParticleEmitterShape = EmitterShape::Ring;
}


void ParticleSystem::Update(float DeltaTime)
{
	float RandLifetime;

	// Check if it needs to create a new particle
	if (EmissionCooldown >= EmissionRate)
	{
		for (int i = 0; i < EmissionCount; i++)
		{
			if (IsRandomVelocity)
				ParticleVelocity = Vector2(rand() % 200 - 100, rand() % 200 - 100);

			ParticleObject* NewParticle = new ParticleObject(ParticleSprite, ParticleVelocity, ParticleLifetime);
			NewParticle->SetScale(ParticleScale);
			NewParticle->SetRotation(ParticleRotation);
			NewParticle->SetColor(ParticleColor);
			NewParticle->SetBlendMode(BlendMode::Additive);
			NewParticle->SetAcceleration(ParticleGravity);

			switch (ParticleEmitterShape)
			{
			case EmitterShape::Point:
				NewParticle->SetPosition(Position);
				break;
			case EmitterShape::Box:
				NewParticle->SetPosition(BoxEmitter->GetParticleEmissionPosition(&Position));
				break;
			case EmitterShape::Circle:
				NewParticle->SetPosition(CircleEmitter->GetParticleEmissionPosition(&Position));
				break;
			case EmitterShape::Ring:
				NewParticle->SetPosition(RingEmitter->GetParticleEmissionPosition(&Position));
				break;
			}

			ParticleList.push_back(NewParticle);
		}
		EmissionCooldown = 0;
	}
	else EmissionCooldown += DeltaTime;

	
	// Update the particles' movement
	std::list<ParticleObject*>::iterator ParticleIterator = ParticleList.begin();
	while (ParticleIterator != ParticleList.end())
	{
		ParticleObject* TempParticle = *ParticleIterator;
		if (!AffectorList.empty())
		{
			std::list<ParticleAffector*>::iterator AffectorIterator = AffectorList.begin();
			while (AffectorIterator != AffectorList.end())
			{
				ParticleAffector* TempAffector = *AffectorIterator;
				TempAffector->AffectParticleUpdate(TempParticle);
				AffectorIterator++;
			}
		}
		TempParticle->Update(DeltaTime);

		if (TempParticle->GetCurrentLifetime() >= TempParticle->GetMaxLifetime())
		{
			delete TempParticle;
			ParticleIterator = ParticleList.erase(ParticleIterator);
		}
		else ParticleIterator++;
	}

	ParticleSystemCurrentLifetime += DeltaTime;
}

void ParticleSystem::Draw()
{
	std::list<ParticleObject*>::iterator ParticleIterator = ParticleList.begin();
	while (ParticleIterator != ParticleList.end())
	{
		ParticleObject* TempParticle = *ParticleIterator;
		TempParticle->Draw();
		ParticleIterator++;
	}
}
