
// 2019302130011Doc.cpp: CMy2019302130011Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "2019302130011.h"
#endif

#include "2019302130011Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy2019302130011Doc

IMPLEMENT_DYNCREATE(CMy2019302130011Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy2019302130011Doc, CDocument)
END_MESSAGE_MAP()


// CMy2019302130011Doc 构造/析构

CMy2019302130011Doc::CMy2019302130011Doc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CMy2019302130011Doc::~CMy2019302130011Doc()
{
}

void CMy2019302130011Doc::DDALine(CClientDC* DCPoint)
{
	int x, x0, y0, x1, y1, flag;
	float m, y;
	DCPoint->SetROP2(R2_COPYPEN);//绘图方法为直接画
	//直线端点由鼠标确定后存放在group[0]、group[1]
	x0 = group[0].x; y0 = group[0].y;
	x1 = group[1].x; y1 = group[1].y;
	if (x0 == x1 && y0 == y1) return;
	if (x0 == x1)//垂直线
	{
		if (y0 > y1)
		{
			x = y0; y0 = y1; y1 = x;
		}
		for (x = y0; x <= y1; x++)
		{
			DCPoint->SetPixel(x0, x, RGB(255, 0, 0));
		}
		return;
	}
	if (y0 == y1)//水平线
	{
		if (x0 > x1)
		{
			x = x0; x0 = x1; x1 = x;
		}
		for (x = x0; x <= x1; x++)
		{
			DCPoint->SetPixel(x, y0, RGB(255, 0, 0));
		}
		return;
	}
	if (x0 > x1)
	{
		x = x0; x0 = x1; x1 = x;//交换起始、终止点
		x = y0; y0 = y1; y1 = x;
	}
	flag = 0;
	if (x1 - x0 > y1 - y0 && y1 - y0 > 0) flag = 1;
	if (x1 - x0 > y0 - y1 && y0 - y1 > 0)
	{
		flag = 2; y0 = -y0; y1 = -y1;
	}
	if (y1 - y0 > x1 - x0)
	{
		flag = 3; x = x0; x0 = y0; y0 = x; x = x1; x1 = y1; y1 = x;
	}
	if (y0 - y1 > x1 - x0)
	{
		flag = 4; x = x0; x0 = -y0; y0 = x; x = x1; x1 = -y1; y1 = x;
	}
	m = (float)(y1 - y0) / (float)(x1 - x0);
	for (x = x0, y = (float)y0; x <= x1; x++, y = y + m)
	{
		if (flag == 1) DCPoint->SetPixel(x, int(y), RGB(255, 0, 0));
		if (flag == 2) DCPoint->SetPixel(x, -int(y), RGB(255, 0, 0));
		if (flag == 3) DCPoint->SetPixel(int(y), x, RGB(255, 0, 0));
		if (flag == 4) DCPoint->SetPixel(int(y), -x, RGB(255, 0, 0));
	}
}

void CMy2019302130011Doc::BCircle(CClientDC* DCPoint, CPoint p1, CPoint p2)
{
	int r, d, x, y, x0, y0;
	DCPoint->SetROP2(R2_COPYPEN);//绘图方法为直接画
	r = (int)sqrt(((1.0 * p1.x - p2.x) * (1.0 * p1.x - p2.x) + (1.0 * p1.y - p2.y) * (1.0 * p1.y - p2.y)));
	x = 0; y = r; d = 3 - 2 * r; x0 = p1.x; y0 = p1.y;
	while (x < y || x == y)
	{
		DCPoint->SetPixel(x + x0, y + y0, RGB(255, 0, 0));
		DCPoint->SetPixel(-x + x0, y + y0, RGB(255, 0, 0));
		DCPoint->SetPixel(x + x0, -y + y0, RGB(255, 0, 0));
		DCPoint->SetPixel(-x + x0, -y + y0, RGB(255, 0, 0));
		DCPoint->SetPixel(y + x0, x + y0, RGB(255, 0, 0));
		DCPoint->SetPixel(-y + x0, x + y0, RGB(255, 0, 0));
		DCPoint->SetPixel(y + x0, -x + y0, RGB(255, 0, 0));
		DCPoint->SetPixel(-y + x0, -x + y0, RGB(255, 0, 0));
		x = x + 1;
		if (d < 0 || d == 0)
		{
			d = d + 4 * x + 6;
		}
		else
		{
			y = y - 1; d = d + 4 * (x - y) + 10;
		}
	}
}

void CMy2019302130011Doc::PNCircle(CClientDC* DCPoint, CPoint p1, CPoint p2)
{
	int r, d, x, y, x0, y0;
	DCPoint->SetROP2(R2_COPYPEN);//绘图方法为直接画
	r = (int)sqrt(((1.0 * p1.x - p2.x) * (1.0 * p1.x - p2.x) + (1.0 * p1.y - p2.y) * (1.0 * p1.y - p2.y)) * 1.0);
	d = 0; x0 = p1.x; y0 = p1.y; x = x0; y = y0 + r;
	while (y > y0)
	{
		DCPoint->SetPixel(x, y, RGB(255, 0, 0));
		DCPoint->SetPixel(-x + 2 * x0, y, RGB(255, 0, 0));
		DCPoint->SetPixel(x, -y + 2 * y0, RGB(255, 0, 0));
		DCPoint->SetPixel(-x + 2 * x0, -y + 2 * y0, RGB(255, 0, 0));
		if (d < 0)
		{
			x++; d = d + 2 * (x - x0) + 1;
		}
		else
		{
			y--; d = d - 2 * (y - y0) + 1;
		}
	}
}

void CMy2019302130011Doc::Bezier(CClientDC* DCPoint, int mode)
{
	CPoint p[1000];//设置一个数组存储完整的Bezier曲线控制点
	int i, j;
	i = 0, j = 0;
	p[i ++] = group[j ++];//先将第1，2号点存入数组
	p[i ++] = group[j ++];
	while (j <= PointNum - 2)//存入奇、偶号点，生成并存入插入点
	{
		p[i++] = group[j++];
		p[i].x = (group[j].x + group[j - 1].x) / 2;
		p[i++].y = (group[j].y + group[j - 1].y) / 2; 
		p[i++] = group[j++];
	};
	for (j = 0; j < i - 3; j += 3)//控制点分组，分别生成各段曲线
	{
		Bezier_4(DCPoint, mode, p[j], p[j + 1], p[j + 2], p[j + 3]);
	}
}

void CMy2019302130011Doc::Bezier_4(CClientDC* DCPoint, int mode, CPoint p1, CPoint p2, CPoint p3, CPoint p4)
{
	int i, n;
	CPoint p;
	double t1, t2, t3, t4, dt;
	CPen pen;
	n = 10;
	if (mode) //mode=1时，以异或方式画可擦除的黑色曲线，用于调整形状
	{
		DCPoint->SetROP2(R2_NOT);
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	}
	else //mode=0时，画红色的正式曲线
	{
		DCPoint->SetROP2(R2_COPYPEN);
		pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	}

	CPen* pOldPen = DCPoint->SelectObject(&pen);
	dt = 1.0 / n; //参数t的间隔，分10段，即用10段直线表示一段曲线
	DCPoint->MoveTo(p1); //移到起点
	for (i = 1; i <= n; i ++) //用Bezier参数方程计算曲线上等间隔的10个点
	{
		t1 = (1.0 - i * dt) * (1.0 - i * dt) * (1.0 - i * dt); //计算(1-t)3
		t2 = i * dt * (1.0 - i * dt) * (1.0 - i * dt); //计算t(1-t)2
		t3 = i * dt * i * dt * (1.0 - i * dt); //计算t2(1-t)
		t4 = i * dt * i * dt * i * dt; //计算t3
		p.x = (int)(t1 * p1.x + 3 * t2 * p2.x + 3 * t3 * p3.x + t4 * p4.x);
		p.y = (int)(t1 * p1.y + 3 * t2 * p2.y + 3 * t3 * p3.y + t4 * p4.y); 
		DCPoint->LineTo(p);
	}
	DCPoint->SelectObject(pOldPen);
}

BOOL CMy2019302130011Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMy2019302130011Doc 序列化

void CMy2019302130011Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMy2019302130011Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMy2019302130011Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMy2019302130011Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy2019302130011Doc 诊断

#ifdef _DEBUG
void CMy2019302130011Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2019302130011Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2019302130011Doc 命令
