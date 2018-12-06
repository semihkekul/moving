#ifndef _BALLISTIC_TEST_
#define _BALLISTIC_TEST_
#include "../Giresun/particle.h"
using namespace Giresun;
typedef enum {UNUSED=0,PISTOL,ARTILLERY,FIREBALL,LASER} ShotType;
void setFire(ShotType currentShotType, Particle* particle){
	switch(currentShotType)
	{
	case PISTOL:
		particle->setMass(2.0f); // 2.0kg
		particle->setVelocity(-35.0f, .0f); // 35m/s
		particle->setAcceleration(0.0f, 1.0f);
		particle->setDamping(0.99f);
		break;

	case ARTILLERY:
		particle->setMass(200.0f); // 200.0kg
		particle->setVelocity(-40.0f, -30.0f); // 50m/s
		particle->setAcceleration(0.0f, 20.0f);
		particle->setDamping(0.99f);
		break;

	case FIREBALL:
		particle->setMass(1.0f); // 1.0kg - mostly blast damage
		particle->setVelocity(-10.0f, -10.0f); // 5m/s
		particle->setAcceleration(0.0f, -0.6f); // Floats up
		particle->setDamping(0.9f);
		break;

	case LASER:
		// Note that this is the kind of laser bolt seen in films,
		// not a realistic laser beam!
		particle->setMass(0.1f); // 0.1kg - almost no weight
		particle->setVelocity(-100.0f, .0f); // 100m/s
		particle->setAcceleration(0.0f, 0.0f); // No gravity
		particle->setDamping(0.99f);
		break;
		}
	
		// Clear the force accumulators
		particle->clearAccumulator();
}

#endif

