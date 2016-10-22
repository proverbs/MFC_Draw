
// DrawView.cpp : CDrawView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_COMMAND(ID_DRAW_LINE, &CDrawView::OnDrawLine)
ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CDrawView::OnUpdateDrawLine)
ON_COMMAND(ID_DRAW_RECT, &CDrawView::OnDrawRect)
ON_COMMAND(ID_DRAW_RDRECT, &CDrawView::OnDrawRdrect)
ON_COMMAND(ID_DRAW_ELLIPSE, &CDrawView::OnDrawEllipse)
ON_COMMAND(ID_PS_SOLID, &CDrawView::OnPsSolid)
ON_COMMAND(ID_PS_DASH, &CDrawView::OnPsDash)
ON_COMMAND(ID_PS_DOT, &CDrawView::OnPsDot)
ON_COMMAND(ID_PS_DASHDOT, &CDrawView::OnPsDashdot)
ON_COMMAND(ID_PEN_BLACK, &CDrawView::OnPenBlack)
ON_COMMAND(ID_PEN_WHITE, &CDrawView::OnPenWhite)
ON_COMMAND(ID_PEN_RED, &CDrawView::OnPenRed)
ON_COMMAND(ID_PEN_GREEN, &CDrawView::OnPenGreen)
ON_COMMAND(ID_PEN_BLUE, &CDrawView::OnPenBlue)
ON_COMMAND(ID_HS_HOLLOW, &CDrawView::OnHsHollow)
ON_COMMAND(ID_BRUSH_BLACK, &CDrawView::OnBrushBlack)
ON_COMMAND(ID_BRUSH_WHITE, &CDrawView::OnBrushWhite)
ON_COMMAND(ID_BRUSH_RED, &CDrawView::OnBrushRed)
ON_COMMAND(ID_BRUSH_GREEN, &CDrawView::OnBrushGreen)
ON_COMMAND(ID_BRUSH_BLUE, &CDrawView::OnBrushBlue)
ON_COMMAND(ID_HS_HORIZONTAL, &CDrawView::OnHsHorizontal)
ON_COMMAND(ID_HS_VERTICAL, &CDrawView::OnHsVertical)
ON_COMMAND(ID_HS_FDIAGONAL, &CDrawView::OnHsFdiagonal)
ON_COMMAND(ID_HS_BDIAGONAL, &CDrawView::OnHsBdiagonal)
ON_COMMAND(ID_HS_PATTERN, &CDrawView::OnHsPattern)
ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &CDrawView::OnUpdateDrawRect)
ON_UPDATE_COMMAND_UI(ID_DRAW_RDRECT, &CDrawView::OnUpdateDrawRdrect)
ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &CDrawView::OnUpdateDrawEllipse)
ON_UPDATE_COMMAND_UI(ID_PS_SOLID, &CDrawView::OnUpdatePsSolid)
ON_UPDATE_COMMAND_UI(ID_PS_DASH, &CDrawView::OnUpdatePsDash)
ON_UPDATE_COMMAND_UI(ID_PS_DOT, &CDrawView::OnUpdatePsDot)
ON_UPDATE_COMMAND_UI(ID_PS_DASHDOT, &CDrawView::OnUpdatePsDashdot)
ON_UPDATE_COMMAND_UI(ID_HS_HOLLOW, &CDrawView::OnUpdateHsHollow)
ON_UPDATE_COMMAND_UI(ID_PEN_BLACK, &CDrawView::OnUpdatePenBlack)
ON_UPDATE_COMMAND_UI(ID_PEN_WHITE, &CDrawView::OnUpdatePenWhite)
ON_UPDATE_COMMAND_UI(ID_PEN_RED, &CDrawView::OnUpdatePenRed)
ON_UPDATE_COMMAND_UI(ID_PEN_GREEN, &CDrawView::OnUpdatePenGreen)
ON_UPDATE_COMMAND_UI(ID_PEN_BLUE, &CDrawView::OnUpdatePenBlue)
ON_UPDATE_COMMAND_UI(ID_BRUSH_BLACK, &CDrawView::OnUpdateBrushBlack)
ON_UPDATE_COMMAND_UI(ID_BRUSH_WHITE, &CDrawView::OnUpdateBrushWhite)
ON_UPDATE_COMMAND_UI(ID_BRUSH_RED, &CDrawView::OnUpdateBrushRed)
ON_UPDATE_COMMAND_UI(ID_BRUSH_GREEN, &CDrawView::OnUpdateBrushGreen)
ON_UPDATE_COMMAND_UI(ID_BRUSH_BLUE, &CDrawView::OnUpdateBrushBlue)
ON_UPDATE_COMMAND_UI(ID_HS_HORIZONTAL, &CDrawView::OnUpdateHsHorizontal)
ON_UPDATE_COMMAND_UI(ID_HS_VERTICAL, &CDrawView::OnUpdateHsVertical)
ON_UPDATE_COMMAND_UI(ID_HS_FDIAGONAL, &CDrawView::OnUpdateHsFdiagonal)
ON_UPDATE_COMMAND_UI(ID_HS_BDIAGONAL, &CDrawView::OnUpdateHsBdiagonal)
ON_UPDATE_COMMAND_UI(ID_HS_PATTERN, &CDrawView::OnUpdateHsPattern)
ON_COMMAND(ID_BRUSH_OTHERC, &CDrawView::OnBrushOtherc)
ON_UPDATE_COMMAND_UI(ID_BRUSH_OTHERC, &CDrawView::OnUpdateBrushOtherc)
ON_COMMAND(ID_PEN_OTHERC, &CDrawView::OnPenOtherc)
ON_UPDATE_COMMAND_UI(ID_PEN_OTHERC, &CDrawView::OnUpdatePenOtherc)
END_MESSAGE_MAP()

// CDrawView 构造/析构

CDrawView::CDrawView()
{
	// TODO: 在此处添加构造代码
	jGraph = LINE;// 默认画直线

	m_bLButtonDown = FALSE; // 设左鼠标键按下为假
	m_bErase = FALSE; // 设需要擦除为假
	pGrayPen = new CPen(PS_DOT, 0, RGB(128, 128, 128)); // 创建灰色点线笔
	
	PenStyle = PS_SOLID;// 初始化实线笔
	PenColor = RGB(0, 0, 0);// 初始化黑色笔
	pNowPen = new CPen(PenStyle, 1, PenColor);// 初始化黑色实线笔
	
	BrushType = 1;// 初始化单色刷
	BrushColor = RGB(255, 255, 255);
	pNowBrush = new CBrush();// 初始化为白色单色刷
	
	pHollowBrush = new CBrush();
	pHollowBrush->CreateStockObject(NULL_BRUSH);//空刷

	pBitmap = new CBitmap();

	brushColorSelected = false;
	penColorSelected = false;
}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawView 绘制

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDrawView 打印

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawView 诊断

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView 消息处理程序


//void CDrawView::OnMButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CView::OnMButtonDown(nFlags, point);
//}


void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 绘制直线
	if (jGraph == LINE) {
		ReleaseCapture(); // 释放鼠标捕获
		if (m_bLButtonDown) { // 左鼠标键按下为真
			CDC* pDC = GetDC(); // 获取设备上下文
			pDC->SelectObject(pGrayPen); // 选入灰色点线笔
			pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
			pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
			pDC->MoveTo(p0); pDC->LineTo(pm); // 擦除原直线
			pDC->SelectObject(pNowPen); // 选择当前设置的笔
			pDC->SetROP2(R2_COPYPEN); // 设置为覆盖绘图方式
			pDC->MoveTo(p0); pDC->LineTo(point); // 绘制最终的直线
			m_bLButtonDown = FALSE; // 重设左鼠标键按下为假
			m_bErase = FALSE; // 重需要擦除为假
			ReleaseDC(pDC); // 释放设备上下文
		}
	}
	// 绘制矩形
	else if (jGraph == RECTANGLE) {
		ReleaseCapture();
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pNowBrush);//设置填充
			pDC->Rectangle(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));

			pDC->SelectObject(pNowPen);
			pDC->SetROP2(R2_COPYPEN);
			pDC->Rectangle(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));

			//还原参数
			m_bLButtonDown = FALSE;
			m_bErase = FALSE;
			ReleaseDC(pDC);
		}
	}
	// 绘制圆角矩形
	else if (jGraph == RDRECTANGLE) {
		ReleaseCapture();
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pNowBrush);//设置填充
			int d;
			d = min(abs(p0.x - pm.x), p0.y - pm.y) / 4;
			pDC->RoundRect(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y), d, d);

			pDC->SelectObject(pNowPen);
			pDC->SetROP2(R2_COPYPEN);
			d = min(abs(p0.x - pm.x), p0.y - pm.y) / 4;
			pDC->RoundRect(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y), d, d);

			//还原参数
			m_bLButtonDown = FALSE;
			m_bErase = FALSE;
			ReleaseDC(pDC);
		}
	}
	// 绘制椭圆
	else if (jGraph == ELLIPSE) {
		ReleaseCapture();
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pNowBrush);//设置填充
			pDC->Ellipse(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));

			pDC->SelectObject(pNowPen);
			pDC->SetROP2(R2_COPYPEN);
			pDC->Ellipse(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));

			//还原参数
			m_bLButtonDown = FALSE;
			m_bErase = FALSE;
			ReleaseDC(pDC);
		}
	}

	CView::OnLButtonUp(nFlags, point);
}


void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 绘制直线
	if (jGraph == LINE) {
		SetCursor(LoadCursor(NULL, IDC_CROSS)); // 设置鼠标为十字
		if (m_bLButtonDown) { // 左鼠标键按下为真（拖动画图）
			CDC* pDC = GetDC(); // 获取设备上下文
			pDC->SelectObject(pGrayPen); // 选取灰色点线笔
			pDC->SetROP2(R2_XORPEN); // 设置为异或绘图方式
			pDC->SetBkMode(TRANSPARENT); // 设置透明背景模式
										 //pDC->SelectStockObject(NULL_BRUSH); // 选入空刷
										 // 用于动态画封闭图形（如矩形、椭圆等）
			if (m_bErase) { // 需要擦除为真
				pDC->MoveTo(p0); pDC->LineTo(pm); // 擦除原直线
			}
			else // 需要擦除为假
				m_bErase = TRUE; // 设需要擦除为真
			pDC->MoveTo(p0); pDC->LineTo(point); // 绘制新直线
			pm = point; // 更新老终点
			ReleaseDC(pDC); // 释放设备上下文
		}
	}
	// 绘制矩形
	else if (jGraph == RECTANGLE) {
		SetCursor(LoadCursor(NULL, IDC_CROSS));
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pHollowBrush);//设置空刷填充
			if (m_bErase) {
				pDC->Rectangle(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
			}
			else {
				m_bErase = TRUE;
			}
			pDC->Rectangle(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));
			pm = point;
			ReleaseDC(pDC);//对应GetDC
		}
	}
	// 绘制圆角矩形
	else if (jGraph == RDRECTANGLE) {
		SetCursor(LoadCursor(NULL, IDC_CROSS));
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pHollowBrush);//设置空刷填充
			int d;
			if (m_bErase) {
				d = min(abs(p0.x - pm.x), p0.y - pm.y) / 4;
				pDC->RoundRect(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y), d, d);
			}
			else {
				m_bErase = TRUE;
			}
			d = min(abs(p0.x - point.x), p0.y - point.y) / 4;
			pDC->RoundRect(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y), d, d);
			pm = point;
			ReleaseDC(pDC);//对应GetDC
		}
	}
	// 绘制椭圆
	else if (jGraph == ELLIPSE) {
		SetCursor(LoadCursor(NULL, IDC_CROSS));
		if (m_bLButtonDown) {
			CDC* pDC = GetDC();
			pDC->SelectObject(pGrayPen);
			pDC->SetROP2(R2_XORPEN);
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(pHollowBrush);//设置空刷填充
			if (m_bErase) {
				pDC->Ellipse(min(p0.x, pm.x), min(p0.y, pm.y), max(p0.x, pm.x), max(p0.y, pm.y));
			}
			else {
				m_bErase = TRUE;
			}
			pDC->Ellipse(min(p0.x, point.x), min(p0.y, point.y), max(p0.x, point.x), max(p0.y, point.y));
			pm = point;
			ReleaseDC(pDC);//对应GetDC
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 绘制直线
	if (jGraph == LINE) {
		SetCapture(); // 设置鼠标捕获
		m_bLButtonDown = TRUE; // 设左鼠标键按下为真
		p0 = point; // 保存直线的起点
		pm = p0; // 让直线的终点等于起点
	}
	// 绘制矩形
	else if (jGraph == RECTANGLE) {
		SetCapture();
		m_bLButtonDown = TRUE;
		p0 = point;// 矩形对角线一点
		pm = p0;// 矩形对角线另一点
	}
	// 绘制矩形
	else if (jGraph == RDRECTANGLE) {
		SetCapture();
		m_bLButtonDown = TRUE;
		p0 = point;// 矩形对角线一点
		pm = p0;// 矩形对角线另一点
	}
	// 绘制椭圆
	else if (jGraph == ELLIPSE) {
		SetCapture();
		m_bLButtonDown = TRUE;
		p0 = point;// 椭圆对角线一点
		pm = p0;// 椭圆对角线另一点
	}

	CView::OnLButtonDown(nFlags, point);
}


void CDrawView::OnDrawLine()//画直线
{
	// TODO: 在此添加命令处理程序代码
	jGraph = LINE;
}

void CDrawView::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (jGraph == LINE) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}

void CDrawView::OnDrawRect()
{
	// TODO: 在此添加命令处理程序代码
	jGraph = RECTANGLE;
}


void CDrawView::OnUpdateDrawRect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (jGraph == RECTANGLE) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnDrawRdrect()
{
	// TODO: 在此添加命令处理程序代码
	jGraph = RDRECTANGLE;
}


void CDrawView::OnUpdateDrawRdrect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (jGraph == RDRECTANGLE) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnDrawEllipse()
{
	// TODO: 在此添加命令处理程序代码
	jGraph = ELLIPSE;
}


void CDrawView::OnUpdateDrawEllipse(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (jGraph == ELLIPSE) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPsSolid()
{
	// TODO: 在此添加命令处理程序代码
	PenStyle = PS_SOLID;
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePsSolid(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenStyle == PS_SOLID) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPsDash()
{
	// TODO: 在此添加命令处理程序代码
	PenStyle = PS_DASH;
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePsDash(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenStyle == PS_DASH) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPsDot()
{
	// TODO: 在此添加命令处理程序代码
	PenStyle = PS_DOT;
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePsDot(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenStyle == PS_DOT) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPsDashdot()
{
	// TODO: 在此添加命令处理程序代码
	PenStyle = PS_DASHDOT;
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePsDashdot(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenStyle == PS_DASHDOT) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPenBlack()
{
	// TODO: 在此添加命令处理程序代码
	penColorSelected = false;
	PenColor = RGB(0, 0, 0);
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePenBlack(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenColor == RGB(0, 0, 0)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPenWhite()
{
	// TODO: 在此添加命令处理程序代码
	penColorSelected = false;
	PenColor = RGB(255, 255, 255);
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePenWhite(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenColor == RGB(255, 255, 255)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPenRed()
{
	// TODO: 在此添加命令处理程序代码
	penColorSelected = false;
	PenColor = RGB(255, 0, 0);
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePenRed(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenColor == RGB(255, 0, 0)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPenGreen()
{
	// TODO: 在此添加命令处理程序代码
	penColorSelected = false;
	PenColor = RGB(0, 255, 0);
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePenGreen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenColor == RGB(0, 255, 0)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPenBlue()
{
	// TODO: 在此添加命令处理程序代码
	penColorSelected = false;
	PenColor = RGB(0, 0, 255);
	delete pNowPen;
	pNowPen = new CPen(PenStyle, 1, PenColor);
}


void CDrawView::OnUpdatePenBlue(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (PenColor == RGB(0, 0, 255)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnPenOtherc()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog colDlg(PenColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		PenColor = colDlg.GetColor();
		MessageBox(L"载入成功", L"Color");
		penColorSelected = true;
		delete pNowPen;
		pNowPen = new CPen(PenStyle, 1, PenColor);
	}
	else {
		MessageBox(L"载入失败", L"Color");
	}
}


void CDrawView::OnUpdatePenOtherc(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (penColorSelected == true) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnHsHollow()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 0;// 空刷
	delete pNowBrush;
	pNowBrush = new CBrush();
	pNowBrush->CreateStockObject(NULL_BRUSH);
}


void CDrawView::OnUpdateHsHollow(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 0) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnBrushBlack()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 1;// 单色刷
	brushColorSelected = false;
	BrushColor = RGB(0, 0, 0);
	delete pNowBrush;
	pNowBrush = new CBrush(BrushColor);
}


void CDrawView::OnUpdateBrushBlack(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 1 && BrushColor == RGB(0, 0, 0)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnBrushWhite()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 1;// 单色刷
	brushColorSelected = false;
	BrushColor = RGB(255, 255, 255);
	delete pNowBrush;
	pNowBrush = new CBrush(BrushColor);
}


void CDrawView::OnUpdateBrushWhite(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 1 && BrushColor == RGB(255, 255, 255)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnBrushRed()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 1;// 单色刷
	brushColorSelected = false;
	BrushColor = RGB(255, 0, 0);
	delete pNowBrush;
	pNowBrush = new CBrush(BrushColor);
}

void CDrawView::OnUpdateBrushRed(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 1 && BrushColor == RGB(255, 0, 0)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnBrushGreen()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 1;// 单色刷
	brushColorSelected = false;
	BrushColor = RGB(0, 255, 0);
	delete pNowBrush;
	pNowBrush = new CBrush(BrushColor);
}


void CDrawView::OnUpdateBrushGreen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 1 && BrushColor == RGB(0, 255, 0)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnBrushBlue()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 1;// 单色刷
	brushColorSelected = false;
	BrushColor = RGB(0, 0, 255);
	delete pNowBrush;
	pNowBrush = new CBrush(BrushColor);
	
}


void CDrawView::OnUpdateBrushBlue(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 1 && BrushColor == RGB(0, 0, 255)) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnBrushOtherc()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog colDlg(BrushColor, CC_FULLOPEN);
	if (colDlg.DoModal() == IDOK) {
		BrushColor = colDlg.GetColor();
		MessageBox(L"载入成功", L"Color");
		BrushType = 1;
		brushColorSelected = true;
		delete pNowBrush;
		pNowBrush = new CBrush(BrushColor);
	}
	else {
		MessageBox(L"载入失败", L"Color");
	}
}


void CDrawView::OnUpdateBrushOtherc(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 1 && brushColorSelected == true) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnHsHorizontal()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 2;// 风格刷
	BrushStyle = HS_HORIZONTAL;
	delete pNowBrush;
	pNowBrush = new CBrush(BrushStyle, BrushColor);
}


void CDrawView::OnUpdateHsHorizontal(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 2 && BrushStyle == HS_HORIZONTAL) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnHsVertical()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 2;// 风格刷
	BrushStyle = HS_VERTICAL;
	delete pNowBrush;
	pNowBrush = new CBrush(BrushStyle, BrushColor);
}


void CDrawView::OnUpdateHsVertical(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 2 && BrushStyle == HS_VERTICAL) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnHsFdiagonal()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 2;// 风格刷
	BrushStyle = HS_FDIAGONAL;
	delete pNowBrush;
	pNowBrush = new CBrush(BrushStyle, BrushColor);
}


void CDrawView::OnUpdateHsFdiagonal(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 2 && BrushStyle == HS_FDIAGONAL) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnHsBdiagonal()
{
	// TODO: 在此添加命令处理程序代码
	BrushType = 2;// 风格刷
	BrushStyle = HS_BDIAGONAL;
	delete pNowBrush;
	pNowBrush = new CBrush(BrushStyle, BrushColor);
}


void CDrawView::OnUpdateHsBdiagonal(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 2 && BrushStyle == HS_BDIAGONAL) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


void CDrawView::OnHsPattern()
{
	// TODO: 在此添加命令处理程序代码
	wchar_t *filters = L"位图文件(*.bmp)|*.bmp";
	CFileDialog fileDlg(TRUE, L"bmp", L"*.bmp", OFN_HIDEREADONLY, filters);
	CString sPath;
	if (fileDlg.DoModal() == IDOK) {
		sPath = fileDlg.GetPathName();
		MessageBox(sPath, L"载入成功");
		
		hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), sPath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		delete pBitmap;
		pBitmap = new CBitmap();
		pBitmap->Attach(hBitmap);

		delete pNowBrush;
		pNowBrush = new CBrush(pBitmap);
		
		BrushType = 3;//图片刷
	}
	else {
		MessageBox(sPath, L"载入失败");
	}
}


void CDrawView::OnUpdateHsPattern(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (BrushType == 3) pCmdUI->SetCheck(true);
	else pCmdUI->SetCheck(false);
}


