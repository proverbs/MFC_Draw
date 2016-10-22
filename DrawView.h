
// DrawView.h : CDrawView ��Ľӿ�
//

#pragma once


class CDrawView : public CView
{
protected: // �������л�����
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

public:
	enum MYGRAPH {LINE = 1, RECTANGLE, RDRECTANGLE, ELLIPSE, OUTWORD, OUTPICTURE};// ����ͼ��
	enum MYGRAPH jGraph;// ͼ��
	

// ����
public:
	CDrawDoc* GetDocument() const;
	// ���������������
	BOOL m_bLButtonDown, // �ж��Ƿ���������
		m_bErase; // �Ƿ���Ҫ����ͼ��
	CPoint p0, pm; // ��¼ֱ�����Ͷ�̬�յ�
	CPen *pGrayPen;// �����ɫ�ʵĶ���ָ�룬���ڶ�̬��ͼʱ�ı߿���ʾ
	CBrush *pHollowBrush; // ��ˢ�����ڷ��ͼ�ζ�̬��ͼ

	CPen *pNowPen;//�û��趨��
	int PenStyle;
	COLORREF PenColor;
	bool penColorSelected;// �Զ�����ɫ
	
	CBrush *pNowBrush;//�û��趨ˢ
	int BrushType;// 0��ˢ��1��ɫˢ��2���ˢ��3ͼƬˢ
	int BrushStyle;// ���ˢ����
	COLORREF BrushColor;
	bool brushColorSelected;// �Զ�����ɫ

	CBitmap *pBitmap;// ͼƬˢ

	// �������
	CFont m_font;// ����
	LOGFONT m_logFont;// �߼�����ṹ
	wchar_t m_fontName[LF_FACESIZE];// ��������
	int m_iFontSize;// �����С
	COLORREF m_textColor;// ������ɫ
	BOOL m_bItalic, m_bBold, m_bUnderline, m_bStrikeOut;// б�壬���壬�»��ߣ�ɾ����

	// ����ͼƬ
	CImage *pImg;


// ����
public:
	BOOL SetMyFont(CDC *pDC, LPCTSTR faceName, int size, COLORREF col = RGB(0, 0, 0), int angle = 0,
		BOOL italic = FALSE, BOOL bold = FALSE, BOOL underline = FALSE, BOOL strikeOut = FALSE);// ��������



// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // DrawView.cpp �еĵ��԰汾
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }
#endif

