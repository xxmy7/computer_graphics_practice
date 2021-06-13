#pragma once
#include"CPoint3d.h"
#include<vector>

class CPolygon3d
{
public:
	std::vector<CPoint3d*> m_polygon{};
	bool visible = true;
	COLORREF color = RGB(0, 0, 0);
	CPolygon3d(){}
	CPolygon3d(std::vector<CPoint3d*>&);
	//CPolygon3d(const CPolygon3d& m) {
	//	m_polygon.assign(m.m_polygon.begin(), m.m_polygon.end());
	//	visible = m.visible;
	//}
	~CPolygon3d();

public:
	CPoint3d  getNormalVector()const;
};

