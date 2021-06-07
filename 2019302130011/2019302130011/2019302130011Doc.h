
// 2019302130011Doc.h: CMy2019302130011Doc 类的接口
//


#pragma once


class CMy2019302130011Doc : public CDocument
{
protected: // 仅从序列化创建
	CMy2019302130011Doc() noexcept;
	DECLARE_DYNCREATE(CMy2019302130011Doc)

// 特性
public:
	CPoint group[100]; //定义数组
	int PointNum;

// 操作
public:
	void DDALine(CClientDC* DCPoint);
	void BCircle(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void PNCircle(CClientDC* DCPoint, CPoint p1, CPoint p2);
	void Bezier(CClientDC* DCPoint, int mode);
	void Bezier_4(CClientDC* pDC, int mode, CPoint p1, CPoint p2, CPoint p3, CPoint p4);
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
};
