#pragma once
#include<vector>
#include<Eigen/dense>

class CPoint3d
{
public:
	double x = 0;
	double y = 0;
	double z = 0;

public:
	CPoint3d() {}
	CPoint3d(const CPoint3d& pt);
	CPoint3d(double x, double y, double z);
	~CPoint3d();


	Eigen::Vector4d toHomoPoint()const;
	double dot(const CPoint3d& pt);
	double norm()const;
	Eigen::Matrix3d toSkewSymMatrix() const;

	CPoint3d& operator+=(const CPoint3d&);
	CPoint3d& operator-=(const CPoint3d&);
	CPoint3d& operator*=(double);
};

CPoint3d operator+(const CPoint3d&, const CPoint3d&);
CPoint3d operator-(const CPoint3d&,const CPoint3d&);
CPoint3d operator*(const CPoint3d&, double);
CPoint3d operator*(double, const CPoint3d&);