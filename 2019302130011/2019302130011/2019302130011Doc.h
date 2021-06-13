
// 2019302130011Doc.h: CMy2019302130011Doc 类的接口
//


#pragma once
#include"CPoint3d.h"
#include"CPolygon3d.h"

class CMy2019302130011Doc : public CDocument
{
protected: // 仅从序列化创建
	CMy2019302130011Doc() noexcept;
	DECLARE_DYNCREATE(CMy2019302130011Doc)

// 特性
public:
	CPoint group[100]{}; //定义数组
	int PointNum = 0;
	COLORREF m_crColor = RGB(255, 0, 0);;//保存图形颜色
	double result[4][2];//保存矩阵结果
	CPoint3d mRotVec{};
	std::vector<CPoint3d> mVertVec{}; 
	std::vector<CPolygon3d> mFaceVec{};
	bool doshadow = false;

// 操作
public:
	void DDALine(CClientDC* DCPoint);
	void MidLine(CClientDC* DCPoint);

	void BCircle(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void BCircle(CClientDC* DCPoint, CRect* rc, CPoint p1, CPoint p2); //裁剪所用判断
	void PNCircle(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void Bezier(CClientDC* DCPoint, int mode);
	void Bezier_4(CClientDC* pDC, int mode, CPoint p1, CPoint p2, CPoint p3, CPoint p4);
	void BSample (CClientDC* DCPoint, int mode);
	void BSample_4(CClientDC* pDC, int mode, CPoint p1, CPoint p2, CPoint p3, CPoint p4);
	void Hermite(CClientDC* DCPoint, int mode);
	void Hermite_4(CClientDC* pDC, int mode, CPoint p1, CPoint p2, CPoint p3, CPoint p4);
	void Caculate(double a[4][4], double b[4][2]);

	void GenerateGraph(CClientDC* DCPoint);
	void DrawGraph(CClientDC* DCPoint);

	void Rotate(CPoint p1, CPoint p2);
	void Symmetry(CPoint p1, CPoint p2);
	
	void SeedFill(CClientDC* DCPoint, CPoint seedpoint);
	void EdgeFill(CClientDC* pDC);
	
	//CohenSuthreland算法用
	void DrawWindow(CClientDC* DCPoint);
	void CohenSutherland(CClientDC* DCPoint, CPoint p1, CPoint p2);
	int encode(int x, int y);

	void PolygonCut(CClientDC* DCPoint);
	void EdgeClipping(int linecode);

	void CircleCut(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void CutMiddle(CClientDC* pDC, CPoint p1, CPoint p2);//定义中点裁剪函数
	//中点裁剪配套判断函数
	bool LineIsOutOfWindow(int x1, int y1, int x2, int y2);
	bool PointIsOutOfWindow(int x, int y);
	POINT FindNearestPoint(int x1, int y1, int x2, int y2);

	void CutLiang(CClientDC* pDC, CPoint p1, CPoint p2);

	
	
	//以下用于消隐与光照
	void initcube();
	void inittri_pyramid();
	

	//构造立方体
	static std::vector<CPoint3d> generateCubeVert(); //构造立方体顶点
	static std::vector<CPolygon3d> generateCubeFace(std::vector<CPoint3d>& vertVec);//构造立方体表面

	//构造三棱锥
	static std::vector<CPoint3d> generatetriVert(); //构造三棱锥顶点
	static std::vector<CPolygon3d> generatetriFace(std::vector<CPoint3d>& vertVec);//构造三棱锥表面

	//自消隐判断
	static bool surfaceVisble(const CPolygon3d& polygon, const CPoint3d& sightVector);

	//正投影（z = 0平面上，归一化到单位立方体内）
	static std::vector<CPoint3d> project_Points(const std::vector<CPoint3d>& pointtVec, double _left, double _right
		, double _buttom, double _top, double _near, double _far);

	static std::vector<CPoint3d> rotate3d(const std::vector<CPoint3d>& ptVec, const CPoint3d& rotateVector);
	static std::vector<CPoint3d> setFit(const std::vector<CPoint3d>&ptVec);
	
	static COLORREF phongLighting(const CPolygon3d& polygon, CPoint3d lightVector, COLORREF lightcolor,
		const CPoint3d param);//暂时只有漫反射光

	//画多面体
	void drawPolyhedron(CClientDC* pDC, std::vector<CPolygon3d>& faceVec, bool doshadow = false)const;

	void rotateAndDrawCube(CClientDC* pDC, const CPoint3d& rotVec, bool doshadow);
	void rotateAndDrawTri(CClientDC* pDC, const CPoint3d& rotVec, bool doshadow);


	// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMy2019302130011Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	afx_msg void OnSetColor();
};
