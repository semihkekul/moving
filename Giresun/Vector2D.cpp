#include "Vector2D.h"
namespace Giresun {
/******************************************************************************/
Vector2D::Vector2D() : m_x(0), m_y(0){}
/******************************************************************************/
Vector2D::Vector2D(const real a_x, const real a_y)
: m_x(a_x), m_y(a_y) {}
/******************************************************************************/
void Vector2D::invert()
{
    m_x = -m_x;
    m_y = -m_y;
}
/******************************************************************************/
real Vector2D::squareMagnitude() const
{
return m_x*m_x+m_y*m_y;
}
/******************************************************************************/
void Vector2D::normalise()
{
 real n = magnitude();
 if (n > 0)
 {
  (*this)*=((real)1)/n;
 }
}
/******************************************************************************/
real Vector2D::magnitude() const
{
     return real_sqrt(m_x*m_x+m_y*m_y);
}
/******************************************************************************/
void Vector2D::addScaledVector(const Vector2D& a_vector, real a_scale)
{
    m_x += a_vector.m_x * a_scale;
    m_y += a_vector.m_y * a_scale;
}
/******************************************************************************/
/******************************************************************************/
void Vector2D::componentProductUpdate(const Vector2D &a_vector){
    m_x *= a_vector.m_x;
    m_y *= a_vector.m_y;
}       
/******************************************************************************/
real Vector2D::scalarProduct(const Vector2D &a_vector) const
        {
         return m_x*a_vector.m_x + m_y*a_vector.m_y ;
        }
/******************************************************************************/
Vector2D Vector2D::vectorProduct(const Vector2D &a_vector) const
        {
            return Vector2D(a_vector.m_y, -m_y*a_vector.m_x);
        }
/******************************************************************************/
void Vector2D::clear()
	{
		m_x = m_y = .0f;
	}
}
