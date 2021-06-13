#include "pch.h"
#include "CPolygon3d.h"

CPolygon3d::CPolygon3d(std::vector<CPoint3d*>&vec)
{
	m_polygon.assign(vec.begin(), vec.end());
}

CPolygon3d::~CPolygon3d()
{
}

CPoint3d CPolygon3d::getNormalVector()const
{
	CPoint3d l1 = *m_polygon[2] - *m_polygon[0];
	CPoint3d l2 = *m_polygon[1] - *m_polygon[0];
	return CPoint3d(l1.z * l2.y - l1.y * l2.z, -(l1.z * l2.x - l1.x * l2.z), l1.y * l2.x - l1.x * l2.y);
}


