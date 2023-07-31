#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Laser::Laser(Game* game)
	:Actor(game)
	,mDeathTimer(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	mMove = new MoveComponent(this);
	//mMove->SetForwardSpeed(800.0f);
	mMove->SetMass(3.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		for (auto aster : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(aster->GetCircle())))
			{
				SetState(EDead);
				aster->SetState(EDead);
				break;
			}
		}
	}
}

