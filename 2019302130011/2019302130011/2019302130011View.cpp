﻿
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

#include "CSetCharDlg.h"
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
	ON_COMMAND(ID_SET_CHAR, &CMy2019302130011View::OnSetChar)
	ON_COMMAND(ID_TRANS_MOVE, &CMy2019302130011View::OnTransMove)
	ON_COMMAND(ID_TRANS_SYMMETRY, &CMy2019302130011View::OnTransSymmetry)
	ON_COMMAND(ID_FILL_SEED, &CMy2019302130011View::OnFillSeed)
	ON_COMMAND(ID_FILL_EDGE, &CMy2019302130011View::OnFillEdge)
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

	/*以下三句未添加的可能没用*/
	OnPrepareDC(&ht);
	ht.DPtoLP(&point);
	ht.SetROP2(R2_NOT); //设置异或方式

	
	if (MenuID == 1) { //DDA直线
		if (PressNum == 0) { //第一次按键将第一点保留在文档类数组中
			pDoc->group[PressNum] = point;
			mPointOrign = point; 
			mPointOld = point;;//记录第一点
			PressNum++;
			SetCapture(); //强行滞留鼠标，滞留的鼠标只能画点；
		}
		else if (PressNum == 1) { //第二次按键保留第二点，用文档类画线
			//下面两句可能要到时候重写个橡皮条函数
			ht.MoveTo(mPointOrign);
			ht.LineTo(mPointOld);//擦旧线


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
			ht.SelectStockObject(NULL_BRUSH);//画空心圆
			int r = (int)sqrt((1.0 * mPointOrign.x - mPointOld.x) * (1.0 * mPointOrign.x - mPointOld.x) + (mPointOrign.y - mPointOld.y) * (mPointOrign.y - mPointOld.y));
			ht.Ellipse(mPointOrign.x - r, mPointOrign.y - r, mPointOrign.x + r, mPointOrign.y + r);//擦旧圆
			PressNum = 0;
			pDoc->BCircle(&ht, mPointOrign, point);
			ReleaseCapture();
		}

		else if (PressNum == 1 && MenuID == 4) {//第二次按键调用画圆程序画图
			ht.SelectStockObject(NULL_BRUSH);//画空心圆
			int r = (int)sqrt((1.0 * mPointOrign.x - mPointOld.x) * (1.0 * mPointOrign.x - mPointOld.x) + (mPointOrign.y - mPointOld.y) * (mPointOrign.y - mPointOld.y));
			ht.Ellipse(mPointOrign.x - r, mPointOrign.y - r, mPointOrign.x + r, mPointOrign.y + r);//擦旧圆
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


	if (MenuID == 11) {//平移
		if (PressNum == 0) {
			PressNum++;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			SetCapture();
		}
		else if (PressNum == 1) { //根据两点间距计算平移量
			for (int i = 0; i < pDoc->PointNum; i++)//根据平移量计算新图形坐标
			{
				pDoc->group[i].x += point.x - mPointOrign.x;
				pDoc->group[i].y += point.y - mPointOrign.y; 
			}
			ht.MoveTo(mPointOrign);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->DrawGraph(&ht);//生成新图形
			ReleaseCapture();
			PressNum = 0;
		}
	}

	if (MenuID == 15) {//对称变换
		if (PressNum == 0) {
			PressNum++;
			mPointOrign = point;
			mPointOld = point;//记录第一点
			SetCapture();
		}
		else if (PressNum == 1) {
			pDoc->Symmetry(mPointOrign, point);//进行对称变换
			pDoc->DrawGraph(&ht);//生成新图形
			ReleaseCapture();
			PressNum = 0;
		}
	}


	if (MenuID == 20) {//种子填充:画边界
		if (PressNum == 0) {
			mPointOrign = point;
			mPointOld = point;
			mPointOld1 = point;//记录第一点
			PressNum++;
			SetCapture();
		}
		else {
			ht.MoveTo(mPointOrign);//擦除橡皮筋
			ht.LineTo(point);
			pDoc->group[0] = mPointOrign;//借助DDA直线函数画边界
			pDoc->group[1] = point;
			pDoc->DDALine(&ht);
			mPointOrign = point;
			mPointOld = point;
			PressNum++;
		}
	}

	if (MenuID == 21) {//确定种子点，填充
		pDoc->SeedFill(&ht, point);
		PressNum = 0; 
		MenuID = 20;//设置决定顶点操作方式
	}

	if (MenuID == 22) {//边缘填充选顶点
		pDoc->group[PressNum++] = point;
		pDoc->PointNum ++;
		mPointOrign = point;
		mPointOld = point;
		SetCapture();
	}



	CView::OnLButtonDown(nFlags, point);
}


void CMy2019302130011View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMy2019302130011Doc* pDoc = GetDocument();//获得文档类指针
	CClientDC ht(this); //定义当前绘图设备
	OnPrepareDC(&ht);
	ht.DPtoLP(&point);

	ht.SetROP2(R2_NOT);  //改成异或画法

	if (MenuID == 5 && pDoc->PointNum > 3) {
		pDoc->Bezier(&ht, 1);//绘制Bezier函数
		MenuID = 6; //将下面的操作改为修改控制点位置
		PressNum = 0;
	}
	if (MenuID == 6 && PressNum == 1) {
		PressNum = 0;
	}


	if (MenuID == 20 && PressNum > 0) {//种子填充
		ht.MoveTo(mPointOrign);//擦除橡皮筋
		ht.LineTo(point);

		pDoc->group[0] = mPointOld1;//封闭多边形
		pDoc->group[1] = mPointOrign;
		pDoc->DDALine(&ht);  //最后一条线
		PressNum = 0; 
		MenuID = 21;//改变操作方式为种子点选取
		ReleaseCapture();
	}

	if (MenuID == 22) {//边缘填充选点结束
		ht.MoveTo(mPointOrign);//擦除橡皮筋
		ht.LineTo(point);

		pDoc->group[PressNum] = pDoc->group[0];
		pDoc->PointNum ++;
		ht.MoveTo(pDoc->group[PressNum - 1]);
		ht.LineTo(pDoc->group[0]);  //画出最后一条线（黑色默认）
		
		for (int i = 0; i < PressNum; i++) //擦除了所有的线
			ht.LineTo(pDoc->group[i + 1]);

		pDoc->EdgeFill(&ht);
		PressNum = 0;
		pDoc->PointNum = 0;
		ReleaseCapture();
	}




	CView::OnRButtonDown(nFlags, point);
}


/*
*					 鼠标移动
*/
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
	

	// 直线的橡皮条
	if ((MenuID == 1  || //DDA
		 MenuID == 11 || //平移
		 MenuID == 15 || //对称
		 MenuID == 20 || //种子填充
		 MenuID == 22 || //边缘填充
		 MenuID == 23) &&  //扫描线填充
		 PressNum > 0) //对于种子填充上面的其实PressNum==1
	{
		if (mPointOld != point) {
			pDC.MoveTo(mPointOrign); 
			pDC.LineTo(mPointOld);//擦旧线
			pDC.MoveTo(mPointOrign);
			pDC.LineTo(point);//画新线
			mPointOld = point;
		}
	}

	//对于圆的橡皮条
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




	CView::OnMouseMove(nFlags, point);
}


/*
*					 鼠标左键双击
*/
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





void CMy2019302130011View::OnSetChar()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = GetDC();
	CSetCharDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CFont* pfntOld = pDC->SelectObject(&dlg.m_fnt);//保存旧字体
		pDC->SetTextColor(dlg.m_clrText);//设置颜色
		pDC->TextOut(dlg.m_nX, dlg.m_nY, dlg.m_strString);//画到屏幕上
		pDC->SelectObject(pfntOld);//还原旧字体
	}
	ReleaseDC(pDC);
}


void CMy2019302130011View::OnTransMove()
{
	// TODO: 在此添加命令处理程序代码
	CMy2019302130011Doc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC);
	pDoc->GenerateGraph(&pDC);//调用文档类函数在屏幕上生成图形
	PressNum = 0; MenuID = 11;
}


void CMy2019302130011View::OnTransSymmetry()
{
	// TODO: 在此添加命令处理程序代码
	CMy2019302130011Doc* pDoc = GetDocument();//获得文档类指针
	CClientDC pDC(this);
	OnPrepareDC(&pDC); 
	pDoc->GenerateGraph(&pDC);
	PressNum = 0; MenuID = 15;
}


void CMy2019302130011View::OnFillSeed()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0; MenuID = 20;
}


void CMy2019302130011View::OnFillEdge()
{
	// TODO: 在此添加命令处理程序代码
	PressNum = 0; MenuID = 22;
}
