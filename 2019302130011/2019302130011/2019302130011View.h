
// 2019302130011View.h: CMy2019302130011View 类的接口
//

#pragma once

#include"CPoint3d.h"
class CMy2019302130011View : public CView
{
protected: // 仅从序列化创建
	int MenuID, PressNum; //用于判断是哪种命令
	int SaveNumber;
	CPoint mPointOrigin, mPointOld;
	CPoint mPointOld1; //用于种子填充保留第一个顶点
	CPoint3d mrotVec{};


	CMy2019302130011View() noexcept;
	DECLARE_DYNCREATE(CMy2019302130011View)

// 特性
public:
	CMy2019302130011Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMy2019302130011View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawDdaline();
	afx_msg void OnDrawBcircle();
	afx_msg void OnDrawPncircle();
	afx_msg void OnCurveBezier();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSetChar();
	afx_msg void OnTransMove();
	afx_msg void OnTransSymmetry();
	afx_msg void OnFillSeed();
	afx_msg void OnFillEdge();
	afx_msg void OnFillScanline();
	afx_msg void OnCutCs();
	afx_msg void OnCutPolygon();
	afx_msg void OnCutCircle();
	afx_msg void OnDrawMidline();
	afx_msg void OnCurveBsample();
	afx_msg void OnCurveHermite();
	afx_msg void OnTransRotate();
	afx_msg void OnTransZoom();
	afx_msg void OnCutMiddle();
	afx_msg void OnCutLiang();
//	afx_msg void OnBlanking();
	afx_msg void OnShadow();
	afx_msg void OnDelete();
	afx_msg void OnCube();
	afx_msg void OnTriPyramid();
};

#ifndef _DEBUG  // 2019302130011View.cpp 中的调试版本
inline CMy2019302130011Doc* CMy2019302130011View::GetDocument() const
   { return reinterpret_cast<CMy2019302130011Doc*>(m_pDocument); }
#endif

