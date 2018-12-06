#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Vector2D.h"

namespace Giresun {

    class Particle
    {

    public:

    protected:
        
        real inverseMass;

        real damping;

        Vector2D position;
   
        Vector2D velocity;

        Vector2D forceAccum;
 
        Vector2D acceleration;

    public:

        void integrate(real duration);

        void setMass(const real mass);

        real getMass() const;

        void setInverseMass(const real inverseMass);

        real getInverseMass() const;

        bool hasFiniteMass() const;


        void setDamping(const real damping);

         real getDamping() const;

         void setPosition(const Vector2D &position);

        void setPosition(const real x, const real y);

        void getPosition(Vector2D *position) const;

        Vector2D getPosition() const;
    

        void setVelocity(const Vector2D &velocity);

        void setVelocity(const real x, const real y);

        void getVelocity(Vector2D *velocity) const;

        Vector2D getVelocity() const;

        void setAcceleration(const Vector2D &acceleration);

         void setAcceleration(const real x, const real y);

        void getAcceleration(Vector2D *acceleration) const;

        Vector2D getAcceleration() const;

        void clearAccumulator();

        void addForce(const Vector2D &force);

    };

}

#endif 
