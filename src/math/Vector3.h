#pragma once
#include <glm\glm.hpp>
#include <iostream>
struct Vector3
{
	float x, y, z;
	Vector3();
	Vector3(float _x,float _y, float _z);
	Vector3(const Vector3& other);
	~Vector3();
	
	static Vector3 zero;
	static Vector3 one;
	static Vector3 right;
	static Vector3 up;
	static Vector3 forward;
	
	static Vector3 CrossProduct(const Vector3& a, const Vector3& b);
	static float DotProduct(const Vector3& a, const Vector3& b);
	static void Slerp(Vector3& value, const Vector3& target, float t);

	//methods
	Vector3& add(const Vector3& v);
	Vector3& subtract(const Vector3& v);
	Vector3& divide(float k);
	Vector3& multiply(float k);
	//desc : normalize this instance and return a reference to this
	Vector3& normalize();
	//desc : return a normalized copy 
	Vector3 normalized() const; 
	float magnitude() const;
	float sqrdMagnitude() const;

	glm::vec3 toVec3() const;
	Vector3 Copy() const;

	//operators
	friend Vector3 operator+(const Vector3& a, const Vector3& b);
	friend Vector3 operator-(const Vector3& a, const Vector3& b);
	friend Vector3 operator*(const Vector3& a, float k);
	friend Vector3 operator/(const Vector3& a, float k);

	friend Vector3& operator+=(Vector3& a, const Vector3& b);
	friend Vector3& operator-=(Vector3& a, const Vector3& b);
	friend Vector3& operator*=(Vector3& a, float k);
	friend Vector3& operator/=(Vector3& a, float k);

	friend std::ostream& operator<<(std::ostream& stream, const Vector3& v);
};

