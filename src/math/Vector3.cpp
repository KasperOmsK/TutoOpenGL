#include "Vector3.h"
#include <math.h>
#include "math.h"

//static fields

Vector3 Vector3::zero = Vector3(0,0,0);
Vector3 Vector3::one = Vector3(1,1,1);
Vector3 Vector3::right = Vector3(1,0,0);
Vector3 Vector3::up = Vector3(0, 1,0);
Vector3 Vector3::forward = Vector3(0,0,1);

Vector3::Vector3()
{
	x = y = z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::Vector3(const Vector3 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3::~Vector3()
{
}

Vector3& Vector3::add(const Vector3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::subtract(const Vector3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::divide(float k)
{
	x /= k;
	y /= k;
	z /= k;
	return *this;
}

Vector3& Vector3::multiply(float k)
{
	x *= k;
	y *= k;
	z *= k;
	return *this;
}

Vector3 & Vector3::normalize()
{
	float l = length();
	if (l != 0) {
		divide(l);
	}
	return *this;
}

Vector3 Vector3::normalized() const
{
	return Vector3(*this).normalize();
}

float Vector3::length() const
{
	if (x==0 && y ==0 && z==0) {
		return 0;
	}
	return sqrtf(x*x + y*y + z*z);
}

glm::vec3 Vector3::toVec3() const
{
	return glm::vec3(x,y,z);
}

Vector3 Vector3::Copy() const
{
	return Vector3(*this);
}

Vector3 Vector3::CrossProduct(const Vector3 & a, const Vector3 & b)
{
	return Vector3(
		(a.y*b.z) - (a.z*b.y),
		(a.z*b.x) - (a.x*b.z),
		(a.x*b.y) - (a.y*b.x));
}

float Vector3::DotProduct(const Vector3 & a, const Vector3 & b)
{
	return a.x*b.x + a.y*b.y + a.z* b.z;
}

void Vector3::Slerp(Vector3 & value, const Vector3 & target, float t)
{
	//TODO: Implement SLERP
	std::cout << "NOT IMPLEMENTED YET !" << std::endl;
}

Vector3 operator+(const Vector3 & a, const Vector3 & b)
{
	return Vector3(a).add(b);
}

Vector3 operator-(const Vector3 & a, const Vector3 & b)
{
	return Vector3(a).subtract(b);
}

Vector3 operator*(const Vector3 & a, float k)
{
	return Vector3(a).multiply(k);
}

Vector3 operator/(const Vector3 & a, float k)
{
	return Vector3(a).divide(k);
}

Vector3 & operator+=(Vector3 & a, const Vector3 & b)
{
	return a.add(b);
}

Vector3 & operator-=(Vector3 & a, const Vector3 & b)
{
	return a.subtract(b);
}

Vector3 & operator*=(Vector3 & a, float k)
{
	return a.multiply(k);
}

Vector3 & operator/=(Vector3 & a, float k)
{
	return a.divide(k);
}

std::ostream & operator<<(std::ostream & stream, const Vector3 & v)
{
	return stream << "(" << v.x << "," << v.y << "," << v.z << ")";
}
