
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
	ON_COMMAND(ID_SET_COLOR, &CMy2019302130011Doc::OnSetColor)
END_MESSAGE_MAP()


// CMy2019302130011Doc 构造/析构

CMy2019302130011Doc::CMy2019302130011Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	m_crColor = RGB(0, 0, 255);
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
			DCPoint->SetPixel(x0, x, m_crColor);
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
			DCPoint->SetPixel(x, y0, m_crColor);
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
		if (flag == 1) DCPoint->SetPixel(x, int(y), m_crColor);
		if (flag == 2) DCPoint->SetPixel(x, -int(y), m_crColor);
		if (flag == 3) DCPoint->SetPixel(int(y), x, m_crColor);
		if (flag == 4) DCPoint->SetPixel(int(y), -x, m_crColor);
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
		DCPoint->SetPixel(x + x0, y + y0, m_crColor);
		DCPoint->SetPixel(-x + x0, y + y0, m_crColor);
		DCPoint->SetPixel(x + x0, -y + y0, m_crColor);
		DCPoint->SetPixel(-x + x0, -y + y0, m_crColor);
		DCPoint->SetPixel(y + x0, x + y0, m_crColor);
		DCPoint->SetPixel(-y + x0, x + y0, m_crColor);
		DCPoint->SetPixel(y + x0, -x + y0, m_crColor);
		DCPoint->SetPixel(-y + x0, -x + y0, m_crColor);
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
		DCPoint->SetPixel(x, y, m_crColor);
		DCPoint->SetPixel(-x + 2 * x0, y, m_crColor);
		DCPoint->SetPixel(x, -y + 2 * y0, m_crColor);
		DCPoint->SetPixel(-x + 2 * x0, -y + 2 * y0, m_crColor);
		if (d < 0)
		{
			x ++; 
			d = d + 2 * (x - x0) + 1;
		}
		else
		{
			y --;
			d = d - 2 * (y - y0) + 1;
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
		pen.CreatePen(PS_SOLID, 1, m_crColor);
	}
	else //mode=0时，画红色的正式曲线
	{
		DCPoint->SetROP2(R2_COPYPEN);
		pen.CreatePen(PS_SOLID, 1, m_crColor);
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

void CMy2019302130011Doc::GenerateGraph(CClientDC* DCPoint)
{
	group[0].x = 100; group[0].y = 100;//图形数据准备
	group[1].x = 200; group[1].y = 100;
	group[2].x = 200; group[2].y = 200;
	group[3].x = 100; group[3].y = 200;
	group[4].x = 100; group[4].y = 100;
	PointNum = 5;
	DrawGraph(DCPoint);//画图形
}

void CMy2019302130011Doc::DrawGraph(CClientDC* DCPoint)
{
	int i;
	CPen pen, * pOldPen;
	DCPoint->SetROP2(R2_COPYPEN);
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	pOldPen = DCPoint->SelectObject(&pen);
	DCPoint->MoveTo(group[0]);
	for (i = 1; i < PointNum; i++)
		DCPoint->LineTo(group[i]);
	DCPoint->SelectObject(pOldPen);

}

void CMy2019302130011Doc::Symmetry(CPoint p1, CPoint p2)
{
	float a[3][3], b[3][3], c[3][3] = { NULL };
	float sa, ca, x, y;
	int i;
	ca = (p2.x - p1.x) / sqrt(((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));//cosα 
	sa = (p2.y - p1.y) / sqrt(((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));//sinα
	c[0][0] = 1; c[0][1] = 0; c[0][2] = -p1.x;//矩阵1
	c[1][0] = 0; c[1][1] = 1; c[1][2] = -p1.y;
	c[2][0] = 0; c[2][1] = 0; c[2][2] = 1;
	b[0][0] = ca; b[0][1] = sa; b[0][2] = 0;//矩阵2
	b[1][0] = -sa; b[1][1] = ca; b[1][2] = 0;
	b[2][0] = 0; b[2][1] = 0; b[2][2] = 1;
	a[0][0] = b[0][0] * c[0][0] + b[0][1] * c[1][0] + b[0][2] * c[2][0];//矩阵1、2合并
	a[0][1] = b[0][0] * c[0][1] + b[0][1] * c[1][1] + b[0][2] * c[2][1];
	a[0][2] = b[0][0] * c[0][2] + b[0][1] * c[1][2] + b[0][2] * c[2][2];
	a[1][0] = b[1][0] * c[0][0] + b[1][1] * c[1][0] + b[1][2] * c[2][0];
	a[1][1] = b[1][0] * c[0][1] + b[1][1] * c[1][1] + b[1][2] * c[2][1];
	a[1][2] = b[1][0] * c[0][2] + b[1][1] * c[1][2] + b[1][2] * c[2][2];
	a[2][0] = b[2][0] * c[0][0] + b[2][1] * c[1][0] + b[2][2] * c[2][0];
	a[2][1] = b[2][0] * c[0][1] + b[2][1] * c[1][1] + b[2][2] * c[2][1];
	a[2][2] = b[2][0] * c[0][2] + b[2][1] * c[1][2] + b[2][2] * c[2][2];
	b[0][0] = 1; b[0][1] = 0; b[0][2] = 0;//矩阵3
	b[1][0] = 0; b[1][1] = -1; b[1][2] = 0;
	b[2][0] = 0; b[2][1] = 0; b[2][2] = 1;
	c[0][0] = b[0][0] * a[0][0] + b[0][1] * a[1][0] + b[0][2] * a[2][0];//矩阵1、2、3 合并
	c[0][1] = b[0][0] * a[0][1] + b[0][1] * a[1][1] + b[0][2] * a[2][1];
	c[0][2] = b[0][0] * a[0][2] + b[0][1] * a[1][2] + b[0][2] * a[2][2];
	c[1][0] = b[1][0] * a[0][0] + b[1][1] * a[1][0] + b[1][2] * a[2][0];
	c[1][1] = b[1][0] * a[0][1] + b[1][1] * a[1][1] + b[1][2] * a[2][1];
	c[1][2] = b[1][0] * a[0][2] + b[1][1] * a[1][2] + b[1][2] * a[2][2];
	c[2][0] = b[2][0] * a[0][0] + b[2][1] * a[1][0] + b[2][2] * a[2][0];
	c[2][1] = b[2][0] * a[0][1] + b[2][1] * a[1][1] + b[2][2] * a[2][1];
	c[2][2] = b[2][0] * a[0][2] + b[2][1] * a[1][2] + b[2][2] * a[2][2];
	b[0][0] = ca; b[0][1] = -sa; b[0][2] = 0;//矩阵4
	b[1][0] = sa; b[1][1] = ca; b[1][2] = 0;
	b[2][0] = 0; b[2][1] = 0; b[2][2] = 1;
	a[0][0] = b[0][0] * c[0][0] + b[0][1] * c[1][0] + b[0][2] * c[2][0];//矩阵1、2、3、4合并
	a[0][1] = b[0][0] * c[0][1] + b[0][1] * c[1][1] + b[0][2] * c[2][1];
	a[0][2] = b[0][0] * c[0][2] + b[0][1] * c[1][2] + b[0][2] * c[2][2];
	a[1][0] = b[1][0] * c[0][0] + b[1][1] * c[1][0] + b[1][2] * c[2][0];
	a[1][1] = b[1][0] * c[0][1] + b[1][1] * c[1][1] + b[1][2] * c[2][1];
	a[1][2] = b[1][0] * c[0][2] + b[1][1] * c[1][2] + b[1][2] * c[2][2];
	a[2][0] = b[2][0] * c[0][0] + b[2][1] * c[1][0] + b[2][2] * c[2][0];
	a[2][1] = b[2][0] * c[0][1] + b[2][1] * c[1][1] + b[2][2] * c[2][1];
	a[2][2] = b[2][0] * c[0][2] + b[2][1] * c[1][2] + b[2][2] * c[2][2];
	b[0][0] = 1; b[0][1] = 0; b[0][2] = p1.x;//矩阵5
	b[1][0] = 0; b[1][1] = 1; b[1][2] = p1.y;
	b[2][0] = 0; b[2][1] = 0; b[2][2] = 1;
	c[0][0] = b[0][0] * a[0][0] + b[0][1] * a[1][0] + b[0][2] * a[2][0];//所有矩阵合并
	c[0][1] = b[0][0] * a[0][1] + b[0][1] * a[1][1] + b[0][2] * a[2][1];
	c[0][2] = b[0][0] * a[0][2] + b[0][1] * a[1][2] + b[0][2] * a[2][2];
	c[1][0] = b[1][0] * a[0][0] + b[1][1] * a[1][0] + b[1][2] * a[2][0];
	c[1][1] = b[1][0] * a[0][1] + b[1][1] * a[1][1] + b[1][2] * a[2][1];
	c[1][2] = b[1][0] * a[0][2] + b[1][1] * a[1][2] + b[1][2] * a[2][2];
	c[2][0] = b[2][0] * a[0][0] + b[2][1] * a[1][0] + b[2][2] * a[2][0];
	c[2][1] = b[2][0] * a[0][1] + b[2][1] * a[1][1] + b[2][2] * a[2][1];
	c[2][2] = b[2][0] * a[0][2] + b[2][1] * a[1][2] + b[2][2] * a[2][2];
	for (i = 0; i < PointNum; i++)//利用复合矩阵对所有图形点坐标进行变换
	{
		x = c[0][0] * group[i].x + c[0][1] * group[i].y + c[0][2];
		y = c[1][0] * group[i].x + c[1][1] * group[i].y + c[1][2];
		group[i].x = x; group[i].y = y;
	}

}

void CMy2019302130011Doc::SeedFill(CClientDC* pDC, CPoint seedpoint)
{
	int savex, xleft, xright, pflag, x, y, num;  
	CPoint stack_ptr[200];// 堆栈
	pDC->SetROP2(R2_COPYPEN);// 绘图方法为直接画
	num = 0;//num 为堆栈中的种子数
	stack_ptr[num++] = seedpoint;
	while (num > 0) {
		x = stack_ptr[--num].x; y = stack_ptr[num].y;
		pDC->SetPixel(x, y, m_crColor);
		savex = x; x++;
		while (pDC->GetPixel(x, y) != m_crColor)// 向右填充，直到边界
		{
			pDC->SetPixel(x++, y, m_crColor);
		};
		xright = x - 1; x = savex - 1;
		while (pDC->GetPixel(x, y) != m_crColor)// 向左填充，直到边界
		{
			pDC->SetPixel(x--, y, m_crColor);
		};
		xleft = x + 1; x = xleft; y++;// 在扫描线下一行搜索未填充区域
		pflag = 1;
		while (x < xright) {
			if (pDC->GetPixel(x, y) != m_crColor && pflag == 1)
			{// 边界后的第一个未填充区域像素
				stack_ptr[num].x = x; stack_ptr[num++].y = y; x++;
			}
			if (pDC->GetPixel(x, y) == m_crColor)
				pflag = 1;//pflag=1 表示填充区域或边界
			else
				pflag = 0;//pflag=0 表示未填充区域
			x++;
		}
		x = xleft; y -= 2; pflag = 1;// 在扫描线上一行搜索未填充区域
		while (x < xright) {
			if (pDC->GetPixel(x, y) != m_crColor && pflag == 1)
			{
				stack_ptr[num].x = x; stack_ptr[num++].y = y; x++;
			}
			if (pDC->GetPixel(x, y) == m_crColor)
				pflag = 1;
			else
				pflag = 0;
			x++;
		}
	}
}

void CMy2019302130011Doc::EdgeFill(CClientDC* pDC)
{
	int i, xr, x1, y1, x2, y2, y;
	float m, x;
	CPen pen;
	pen.CreatePen(PS_SOLID, 1,RGB(0,255,255));//确定填充颜色，由该颜色与背景色异或混合而成
	pDC->SetROP2(R2_XORPEN);//绘图方法为异或
	CPen* pOldPen = pDC->SelectObject(&pen);
	xr = 0;
	for (i = 0; i < PointNum; i++)//找出边界盒右边界参数
	{         
		if (xr < group[i].x)
			xr = group[i].x;
	}
	for (i = 0; i < PointNum - 1; i++)
	{
		x1 = group[i].x; x2 = group[i + 1].x;//取一条边
		y1 = group[i].y; y2 = group[i + 1].y;
		if (y1 != y2)
		{
			if (y1 > y2)//确保（x1,y1）为下端点
			{
				y = y1; y1 = y2; y2 = y;
				y = x1; x1 = x2; x2 = y;
			}
			m = (float)(x2 - x1) / (float)(y2 - y1); x = x1;//m为相邻扫描线之间边的x增量
			for (y = y1 + 1; y <= y2; y++)
			{
				x += m;//确定边缘点
				pDC->MoveTo((int)x, y);//从边缘点一直画到边界盒右端
				pDC->LineTo(xr, y);
			}
		}
	}
	pDC->SelectObject(pOldPen);
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


void CMy2019302130011Doc::OnSetColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg(m_crColor);//创建对话框对象，并让其默认颜色为上一次选择的颜色
	if (dlg.DoModal() == IDOK)
		m_crColor = dlg.GetColor();
}
