#include "pch.h"
#include "CPoint3d.h"

CPoint3d::CPoint3d(const CPoint3d& pt):x(pt.x),y(pt.y),z(pt.z)
{
}

CPoint3d::CPoint3d(double x, double y, double z) :x(x), y(y), z(z) {

}

CPoint3d::~CPoint3d()
{
}

Eigen::Vector4d CPoint3d::toHomoPoint() const{
	return Eigen::Vector4d(x, y, z, 1);
}

double CPoint3d::dot(const CPoint3d& pt)
{
	return x * pt.x + y * pt.y + z * pt.z;
}

double CPoint3d::norm()const
{
	return sqrt(x * x + y * y + z * z);
}

Eigen::Matrix3d CPoint3d::toSkewSymMatrix() const
{
	Eigen::Matrix3d mat;
	mat <<
		0, -z, y,
		z, 0, -x,
		-y, x, 0;
	return mat;
}


CPoint3d& CPoint3d::operator+=(const CPoint3d& pt)
{
	x += pt.x;
	y += pt.y;
	z += pt.z;
	return *this;
}

CPoint3d& CPoint3d::operator-=(const CPoint3d& pt)
{
	x -= pt.x;
	y -= pt.y;
	z -= pt.z;
	return *this;
}

CPoint3d& CPoint3d::operator*=(double n)
{
	x *= n;
	y *= n;
	z *= n;
	return *this;
	// TODO: 在此处插入 return 语句
}

CPoint3d operator+(const CPoint3d& a, const CPoint3d& b)
{
	CPoint3d tmp(a);
	return (tmp += b);
}

CPoint3d operator-(const CPoint3d& a, const CPoint3d& b)
{
	CPoint3d tmp(a);
	return (tmp -= b);
}

CPoint3d operator*(const CPoint3d& pt, double n)
{
	return (n * pt);
}

CPoint3d operator*(double n, const CPoint3d& pt)
{
	CPoint3d tmp(pt);
	return (tmp *= n);
}
