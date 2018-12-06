#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include "precision.h"

namespace Giresun{

class Vector2D
{
    public:
       
        real m_x;
        real m_y;
 
    public:

        Vector2D();

        Vector2D(const real a_x, const real a_y);

        void invert();

        real squareMagnitude()const;

        void  normalise();

        real magnitude() const;
     
        void operator*=(const real a_value)
        {
            m_x *= a_value;
            m_y *= a_value;
        }
		void operator=(const Vector2D& a_v)
        {
        m_x = a_v.m_x;
        m_y = a_v.m_y;
        }
			

        Vector2D operator*(const real a_value) const
        {
                return Vector2D(m_x*a_value, m_y*a_value);
        }

        void operator+=(const Vector2D& a_v)
        {
        m_x += a_v.m_x;
        m_y += a_v.m_y;
        }

        Vector2D operator+(const Vector2D& a_v) const
        {
         return Vector2D(m_x+a_v.m_x, m_y+a_v.m_y);
        }

        void operator-=(const Vector2D& a_v)
        {
            m_x -= a_v.m_x;
            m_y -= a_v.m_y;

        }

        Vector2D operator-(const Vector2D& a_v) const
        {
            return Vector2D(m_x-a_v.m_x, m_y-a_v.m_y);
        }

        void addScaledVector(const Vector2D& a_vector, real a_scale); 

        Vector2D componentProduct(const Vector2D &a_vector) const;

        void componentProductUpdate(const Vector2D &a_vector);

        real scalarProduct(const Vector2D &a_vector) const;

        real operator *(const Vector2D &a_vector) const
        {
        return m_x*a_vector.m_x + m_y*a_vector.m_y ;
        }

        Vector2D vectorProduct(const Vector2D &a_vector) const;

        void operator %=(const Vector2D &a_vector)
        {
             *this = vectorProduct(a_vector);
        }

        Vector2D operator%(const Vector2D &a_vector) const
        {
        return Vector2D(  m_x*a_vector.m_y,-m_y*a_vector.m_x);
        }
		void clear();
};
}
#endif
