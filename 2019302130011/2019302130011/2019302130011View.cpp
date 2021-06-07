
// 2019302130011View.cpp: CMy2019302130011View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "2019302130011.h"
#endif

#include "2019302130011Doc.h"
#include "2019302130011View.h"

#include<atlbase.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CStatusBar m_wndStatusBar;

// CMy2019302130011View

IMPLEMENT_DYNCREATE(CMy2019302130011View, CView)

BEGIN_MESSAGE_MAP(CMy2019302130011View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_DDALINE, &CMy2019302130011View::OnDrawDdaline)
	ON_COMMAND(ID_DRAW_BCIRCLE, &CMy2019302130011View::OnDrawBcircle)
	ON_COMMAND(ID_DRAW_PNCIRCLE, &CMy2019302130011View::OnDrawPncircle)
	ON_COMMAND(ID_CURVE_BEZIER, &CMy2019302130011View::OnCurveBezier)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CMy2019302130011View 构造/析构

CMy2019302130011View::CMy2019302130011View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMy2019302130011View::~CMy2019302130011View()
{
}

BOOL CMy2019302130011View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy2019302130011View 绘图

void CMy2019302130011View::OnDraw(CDC* /*pDC*/)
{
	CMy2019302130011Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy2019302130011View 打印

BOOL CMy2019302130011View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy2019302130011View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy2019302130011View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy2019302130011View 诊断

#ifdef _DEBUG
void CMy2019302130011View::AssertValid() const
{
	CView::AssertValid();
}

void CMy2019302130011View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2019302130011Doc* CMy2019302130011View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2019302130011Doc)));
	return (CMy2019302130011Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2019302130011View 消息处理程序


void CMy2019302130011View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMy2019302130011Doc* pDoc = GetDocument(); //获得文档类指针
	CClientDC ht(this); //定义当前绘图设备
	if (MenuID == 1) { //DDA直线
		if (PressNum == 0) { //第一次按键将第一点保留在文档类数组中
			pDoc->group[PressNum] = point;
			mPointOrign = point; mPointOld = point;;//记录第一点
			PressNum++;
			SetCapture(); //强行滞留鼠标，滞留的鼠标只能画点；
		}
		else if (PressNum == 1) { //第二次按键保留第二点，用文档类画线
			pDoc->group[PressNum] = point;
			PressNum = 0; //程序画图
			pDoc->DDALine(&ht);
			ReleaseCapture(); //释放鼠标，鼠标可以继续画点，也可以点击菜单。

		}
	}

	if (MenuID == 3 || MenuID == 4) {//Bresenham圆 和 正负法圆
		if (PressNum == 0) {//第一次按键将第一点保留在mPointOrign
			pDoc->group[PressNum] = point;
			PressNum++;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			SetCapture();
		}

		else if (PressNum == 1 && MenuID == 3) {//第二次按键调用文档类画圆程序画图
			PressNum = 0;
			pDoc->BCircle(&ht, mPointOrign, point);
			ReleaseCapture();
		}
		else if (PressNum == 1 && MenuID == 4) {//第二次按键调用画圆程序画图
			PressNum = 0;
			pDoc->PNCircle(&ht, mPointOrign, point); 
			ReleaseCapture();
		}

	}

	if (MenuID == 5) {//Bezier曲线选点并做十字标志
		ht.MoveTo(point.x, point.y);
		pDoc->group[pDoc->PointNum++] = point;
		ht.MoveTo(point.x - 5, point.y);
		ht.LineTo(point.x + 5, point.y);
		ht.MoveTo(point.x, point.y - 5);
		ht.LineTo(point.x, point.y + 5);
		SetCapture(); 
		PressNum = 1;
	}

	if (MenuID == 6 && PressNum == 0) {//在控制点数组中，逐个寻找
		for (int i = 0; i < pDoc->PointNum; i ++)
		{
			if ((point.x >= pDoc->group[i].x - 5) && (point.x <= pDoc->group[i].x + 5)
				&& (point.y >= pDoc->group[i].y - 5) && (point.y <= pDoc->group[i].y + 5))
			{
				SaveNumber = i;
				PressNum = 1;
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy2019302130011View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMy2019302130011Doc* pDoc = GetDocument();//获得文档类指针
	CClientDC ht(this); //定义当前绘图设备
	OnPrepareDC(&ht);
	ht.DPtoLP(&point);

	if (MenuID == 5 && pDoc->PointNum > 3) {
		pDoc->Bezier(&ht, 1);//绘制Bezier函数
		MenuID = 6; //将下面的操作改为修改控制点位置
		PressNum = 0;
	}
	if (MenuID == 6 && PressNum == 1) {
		PressNum = 0;
	}

	CView::OnRButtonDown(nFlags, point);
}


//鼠标移动时的响应函数
void CMy2019302130011View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMy2019302130011Doc* pDoc = GetDocument();//获得文档类指针
	int xx, yy, r;
	char p1[20];

	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDC.DPtoLP(&point);
	pDC.SetROP2(R2_NOT);//设置异或方式 

	xx=point.x; yy = point.y; //取出坐标信息
	sprintf_s(p1, "%4d", xx); //转化为字符串
	m_wndStatusBar.SetPaneText(2, CString(p1), TRUE); //在第2个区域显示x坐标
	sprintf_s(p1, "%4d", yy); //转化为字符串
	m_wndStatusBar.SetPaneText(3, CString(p1), TRUE); //在第3个区域显示y坐标
	
	//CPen pen(0, 0, RGB(255, 255, 0));//定义一支新笔
	//CPen* pOldPen = pDC.SelectObject(&pen);//绘图设备选新笔，
	////同时保留旧笔

	if (MenuID == 1 && PressNum == 1) {
		if (mPointOld != point) {
			pDC.MoveTo(mPointOrign); 
			pDC.LineTo(mPointOld);//擦旧线
			pDC.MoveTo(mPointOrign);
			pDC.LineTo(point);//画新线
			mPointOld = point;
		}
	}

	if ((MenuID == 3 || MenuID == 4) && PressNum == 1) {
		pDC.SelectStockObject(NULL_BRUSH);//画空心圆
		if (mPointOld != point) {
			r = (int)sqrt((1.0*mPointOrign.x - mPointOld.x) * (1.0 * mPointOrign.x - mPointOld.x) + (mPointOrign.y - mPointOld.y) * (mPointOrign.y-mPointOld.y));
			pDC.Ellipse(mPointOrign.x - r, mPointOrign.y - r, mPointOrign.x + r, mPointOrign.y + r);//擦旧圆
			r = (int)sqrt((1.0 * mPointOrign.x - point.x) * (1.0 * mPointOrign.x - 1.0 * point.x) +
				(1.0 * mPointOrign.y - 1.0 * point.y) * (1.0 * mPointOrign.y - point.y));
			pDC.Ellipse(mPointOrign.x - r, mPointOrign.y - r, mPointOrign.x + r, mPointOrign.y + r);//画新圆
			mPointOld = point;
		}
	}

	if (MenuID == 6 && PressNum > 0) {
		if (pDoc->group[SaveNumber] != point)
		{
			pDC.MoveTo(pDoc->group[SaveNumber].x - 5, pDoc->group[SaveNumber].y);
			pDC.LineTo(pDoc->group[SaveNumber].x + 5, pDoc->group[SaveNumber].y);
			pDC.MoveTo(pDoc->group[SaveNumber].x, pDoc->group[SaveNumber].y - 5);
			pDC.LineTo(pDoc->group[SaveNumber].x, pDoc->group[SaveNumber].y + 5);
			pDoc->Bezier(&pDC, 1);//擦除十字标志和旧线
			pDC.MoveTo(point.x - 5, point.y);
			pDC.LineTo(point.x + 5, point.y);
			pDC.MoveTo(point.x, point.y - 5);
			pDC.LineTo(point.x, point.y + 5);
			pDoc->group[SaveNumber] = point;//记录新控制点
			pDoc->Bezier(&pDC, 1);//画十字标志和新曲线
		}
	}




	//pDC.SelectObject(pOldPen);//恢复旧笔
	CView::OnMouseMove(nFlags, point);
}

void CMy2019302130011View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMy2019302130011Doc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDC.DPtoLP(&point);
	pDC.SetROP2(R2_NOT);//设置异或方式
	if (MenuID == 6) {
		for (int i = 0; i < pDoc->PointNum; i++) {//消除所有光标
			pDC.MoveTo(pDoc->group[i].x - 5, pDoc->group[i].y);
			pDC.LineTo(pDoc->group[i].x + 5, pDoc->group[i].y);
			pDC.MoveTo(pDoc->group[i].x, pDoc->group[i].y - 5);
			pDC.LineTo(pDoc->group[i].x, pDoc->group[i].y + 5);
		}
		pDoc->Bezier(&pDC, 0);//绘制Bezier函数
		MenuID = 5; //将下面的操作改回Bezier曲线方式
		PressNum = 0;
		pDoc->PointNum = 0;
		ReleaseCapture();
	}

	CView::OnLButtonDblClk(nFlags, point);
}


void CMy2019302130011View::OnDrawDdaline()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0; MenuID = 1;
}


void CMy2019302130011View::OnDrawBcircle()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0; MenuID = 3;
}


void CMy2019302130011View::OnDrawPncircle()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0; MenuID = 4;
}


void CMy2019302130011View::OnCurveBezier()
{
	// TODO: 在此添加命令处理程序代码
	CMy2019302130011Doc* pDoc = GetDocument();//获得文档类指针
	pDoc->PointNum = 0;//初始化
	PressNum = 0; MenuID = 5;
}



