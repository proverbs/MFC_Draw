
// DrawView.h : CDrawView 类的接口
//

#pragma once


class CDrawView : public CView
{
protected: // 仅从序列化创建
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

public:
	enum MYGRAPH {LINE = 1, RECTANGLE, RDRECTANGLE, ELLIPSE, OUTWORD, OUTPICTURE};// 设置图形
	enum MYGRAPH jGraph;// 图形
	

// 特性
public:
	CDrawDoc* GetDocument() const;
	// 定义若干类变量：
	BOOL m_bLButtonDown, // 判断是否按下左鼠标键
		m_bErase; // 是否需要擦除图形
	CPoint p0, pm; // 记录直线起点和动态终点
	CPen *pGrayPen;// 定义灰色笔的对象指针，用于动态画图时的边框显示
	CBrush *pHollowBrush; // 空刷，用于封闭图形动态画图

	CPen *pNowPen;//用户设定笔
	int PenStyle;
	COLORREF PenColor;
	bool penColorSelected;// 自定义颜色
	
	CBrush *pNowBrush;//用户设定刷
	int BrushType;// 0空刷，1单色刷，2风格刷，3图片刷
	int BrushStyle;// 风格刷类型
	COLORREF BrushColor;
	bool brushColorSelected;// 自定义颜色

	CBitmap *pBitmap;// 图片刷

	// 字体相关
	CFont m_font;// 字体
	LOGFONT m_logFont;// 逻辑字体结构
	wchar_t m_fontName[LF_FACESIZE];// 字体名称
	int m_iFontSize;// 字体大小
	COLORREF m_textColor;// 字体颜色
	BOOL m_bItalic, m_bBold, m_bUnderline, m_bStrikeOut;// 斜体，粗体，下划线，删除线

	// 绘制图片
	CImage *pImg;


// 操作
public:
	BOOL SetMyFont(CDC *pDC, LPCTSTR faceName, int size, COLORREF col = RGB(0, 0, 0), int angle = 0,
		BOOL italic = FALSE, BOOL bold = FALSE, BOOL underline = FALSE, BOOL strikeOut = FALSE);// 设置字体



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
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);
	afx_msg void OnDrawRect();
	afx_msg void OnDrawRdrect();
	afx_msg void OnDrawEllipse();
	afx_msg void OnPsSolid();
	afx_msg void OnPsDash();
	afx_msg void OnPsDot();
	afx_msg void OnPsDashdot();
	afx_msg void OnPenBlack();
	afx_msg void OnPenWhite();
	afx_msg void OnPenRed();
	afx_msg void OnPenGreen();
	afx_msg void OnPenBlue();
	afx_msg void OnHsHollow();
	afx_msg void OnBrushBlack();
	afx_msg void OnBrushWhite();
	afx_msg void OnBrushRed();
	afx_msg void OnBrushGreen();
	afx_msg void OnBrushBlue();
	afx_msg void OnHsHorizontal();
	afx_msg void OnHsVertical();
	afx_msg void OnHsFdiagonal();
	afx_msg void OnHsBdiagonal();
	afx_msg void OnHsPattern();
	afx_msg void OnUpdateDrawRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawRdrect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsSolid(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsDash(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsDot(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePsDashdot(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHsHollow(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenWhite(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrushBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrushWhite(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrushRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrushGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBrushBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHsHorizontal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHsVertical(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHsFdiagonal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHsBdiagonal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHsPattern(CCmdUI *pCmdUI);
	afx_msg void OnBrushOtherc();
	afx_msg void OnUpdateBrushOtherc(CCmdUI *pCmdUI);
	afx_msg void OnPenOtherc();
	afx_msg void OnUpdatePenOtherc(CCmdUI *pCmdUI);
	afx_msg void OnDrawWord();
	afx_msg void OnUpdateDrawWord(CCmdUI *pCmdUI);
	afx_msg void OnDrawPicture();
	afx_msg void OnUpdateDrawPicture(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // DrawView.cpp 中的调试版本
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }
#endif

