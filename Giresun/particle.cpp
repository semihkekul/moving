#include <assert.h>
#include "particle.h"
using namespace Giresun;
void Particle::integrate(real duration)
{
	// We don't integrate things with zero mass.
	if (inverseMass <= 0.0f) return;

    assert(duration > 0.0);

    // Update linear position.
    position.addScaledVector(velocity, duration);

    // Work out the acceleration from the force
    Vector2D resultingAcc = acceleration;
    resultingAcc.addScaledVector(forceAccum, inverseMass);
    
    // Update linear velocity from the acceleration.
    velocity.addScaledVector(resultingAcc, duration);

    // Impose drag.
    velocity *= real_pow(damping, duration);

    // Clear the forces.
    clearAccumulator();

}



void Particle::setMass(const real mass)
{
    assert(mass != 0);
    Particle::inverseMass = ((real)1.0)/mass;
}

real Particle::getMass() const
{
    if (inverseMass == 0) {
        return REAL_MAX;
    } else {
        return ((real)1.0)/inverseMass;
    }
}

void Particle::setInverseMass(const real inverseMass)
{
    Particle::inverseMass = inverseMass;
}

real Particle::getInverseMass() const
{
    return inverseMass;
}

bool Particle::hasFiniteMass() const
{
    return inverseMass >= 0.0f;
}

void Particle::setDamping(const real damping)
{
    Particle::damping = damping;
}

real Particle::getDamping() const
{
    return damping;
}

void Particle::setPosition(const Vector2D &position)
{
    Particle::position = position;
}

void Particle::setPosition(const real x, const real y)
{
    position.m_x = x;
    position.m_y = y;
}

void Particle::getPosition(Vector2D *position) const
{
    *position = Particle::position;
}

Vector2D Particle::getPosition() const
{
    return position;
}

void Particle::setVelocity(const Vector2D &velocity)
{
    Particle::velocity = velocity;
}

void Particle::setVelocity(const real x, const real y)
{
    velocity.m_x = x;
    velocity.m_y = y;
}

void Particle::getVelocity(Vector2D *velocity) const
{
    *velocity = Particle::velocity;
}

Vector2D Particle::getVelocity() const
{
    return velocity;
}

void Particle::setAcceleration(const Vector2D &acceleration)
{
    Particle::acceleration = acceleration;
}

void Particle::setAcceleration(const real x, const real y)
{
    acceleration.m_x = x;
    acceleration.m_y = y;
}

void Particle::getAcceleration(Vector2D *acceleration) const
{
    *acceleration = Particle::acceleration;
}

Vector2D Particle::getAcceleration() const
{
    return acceleration;
}

///>ParticleAccum
void Particle::clearAccumulator()
{
    forceAccum.clear();
}
///<ParticleAccum

///>ParticleAddForce
void Particle::addForce(const Vector2D &force)
{
    forceAccum += force;
}
///<ParticleAddForce




