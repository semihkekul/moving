#include "pfgen.h"
#include <pspdebug.h>
using namespace Giresun;


void ParticleForceRegistry::updateForces(real duration)
{
    Registry::iterator it = registrations.begin();
	
 for (;  it != registrations.end(); it++)
   {
		  it->fg->updateForce(it->particle, duration);
   }
   
  
}

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator *fg)
{
	ParticleForceRegistry::ParticleForceRegistration registration;
	registration.particle = particle;
	registration.fg = fg;
	registrations.push_back(registration);
}


ParticleGravity::ParticleGravity(const Vector2D& gravity)
: gravity(gravity)
{
}


void ParticleGravity::updateForce(Particle* particle, real duration)
{
    // Check that we do not have infinite mass
    if (!particle->hasFiniteMass()) return;

    // Apply the mass-scaled force to the particle
    particle->addForce(gravity * particle->getMass());
}


ParticleDrag::ParticleDrag(real k1, real k2)
: k1(k1), k2(k2)
{
}


void ParticleDrag::updateForce(Particle* particle, real duration)
{
    Vector2D force;
    particle->getVelocity(&force);

    // Calculate the total drag coefficient
    real dragCoeff = force.magnitude();
    dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

    // Calculate the final force and apply it
    force.normalise();
    force *= -dragCoeff;
    particle->addForce(force);
}


ParticleSpring::ParticleSpring(Particle *other, real sc, real rl)
: other(other), springConstant(sc), restLength(rl)
{
}


void ParticleSpring::updateForce(Particle* particle, real duration)
{
    // Calculate the vector of the spring
    Vector2D force;
    particle->getPosition(&force);
    force -= other->getPosition();

    // Calculate the magnitude of the force
    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude - restLength);
    magnitude *= springConstant;

    // Calculate the final force and apply it
    force.normalise();
    force *= -magnitude;
    particle->addForce(force);
}


ParticleBuoyancy::ParticleBuoyancy(real maxDepth, 
                                 real volume, 
                                 real waterHeight,
                                 real liquidDensity)
: 
maxDepth(maxDepth), volume(volume), 
waterHeight(waterHeight), liquidDensity(liquidDensity)
{
}


void ParticleBuoyancy::updateForce(Particle* particle, real duration)
{
    // Calculate the submersion depth
    real depth = particle->getPosition().m_y;
   
    // Check if we're out of the water
    if (depth >= waterHeight + maxDepth) return;
    Vector2D force(0,0);

    // Check if we're at maximum depth
    if (depth <= waterHeight - maxDepth)
    {
        force.m_y = liquidDensity * volume;
        particle->addForce(force);
        return;
    }

    // Otherwise we are partly submerged
    force.m_y = liquidDensity * volume * 
        (depth - maxDepth - waterHeight) / 2 * maxDepth;
    particle->addForce(force);
}


ParticleBungee::ParticleBungee(Particle *other, real sc, real rl)
: other(other), springConstant(sc), restLength(rl)
{
}


void ParticleBungee::updateForce(Particle* particle, real duration)
{
    // Calculate the vector of the spring
    Vector2D force;
    particle->getPosition(&force);
    force -= other->getPosition();

    // Check if the bungee is compressed
    real magnitude = force.magnitude();
    if (magnitude <= restLength) return;

    // Calculate the magnitude of the force
    magnitude = springConstant * (restLength - magnitude);

    // Calculate the final force and apply it
    force.normalise();
    force *= -magnitude;
    particle->addForce(force);
}


ParticleFakeSpring::ParticleFakeSpring(Vector2D *anchor, real sc, real d)
: anchor(anchor), springConstant(sc), damping(d)
{
}


void ParticleFakeSpring::updateForce(Particle* particle, real duration)
{
    // Check that we do not have infinite mass
    if (!particle->hasFiniteMass()) return;

    // Calculate the relative position of the particle to the anchor
    Vector2D position;
    particle->getPosition(&position);
    position -= *anchor;

    // Calculate the constants and check they are in bounds.
    real gamma = 0.5f * real_sqrt(4 * springConstant - damping*damping);
    if (gamma == 0.0f) return;
    Vector2D c = position * (damping / (2.0f * gamma)) + 
        particle->getVelocity() * (1.0f / gamma);

    // Calculate the target position
    Vector2D target = position * real_cos(gamma * duration) + 
        c * real_sin(gamma * duration);
    target *= real_exp(-0.5f * duration * damping);

    // Calculate the resulting acceleration and therefore the force
    Vector2D accel = (target - position) * (1.0f / duration*duration) - 
        particle->getVelocity() * duration;
    particle->addForce(accel * particle->getMass());
}


ParticleAnchoredSpring::ParticleAnchoredSpring()
{
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector2D *anchor, 
											   real sc, real rl)
: anchor(anchor), springConstant(sc), restLength(rl)
{
}

void ParticleAnchoredSpring::init(Vector2D *anchor, real springConstant, 
								  real restLength)
{
	ParticleAnchoredSpring::anchor = anchor;
	ParticleAnchoredSpring::springConstant = springConstant;
	ParticleAnchoredSpring::restLength = restLength;
}


void ParticleAnchoredBungee::updateForce(Particle* particle, real duration)
{
	// Calculate the vector of the spring
	Vector2D force;
	particle->getPosition(&force);
	force -= *anchor;

	// Calculate the magnitude of the force
	real magnitude = force.magnitude();
	if (magnitude < restLength) return;

	magnitude = magnitude - restLength;
	magnitude *= springConstant;

	// Calculate the final force and apply it
	force.normalise();
	force *= -magnitude;
	particle->addForce(force);
}

void ParticleAnchoredSpring::updateForce(Particle* particle, real duration)
{
    // Calculate the vector of the spring
    Vector2D force;
    particle->getPosition(&force);
    force -= *anchor;

    // Calculate the magnitude of the force
    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude - restLength);
    magnitude *= springConstant;

    // Calculate the final force and apply it
    force.normalise();
    force *= -magnitude;
    particle->addForce(force);
}


