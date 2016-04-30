// GraphicsView.h : interface of the CGraphicsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSVIEW_H__A96477C3_D26C_4B05_A7EE_62031788951C__INCLUDED_)
#define AFX_GRAPHICSVIEW_H__A96477C3_D26C_4B05_A7EE_62031788951C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Matrix.h"
#include "Matrix2.h"
#include <math.h>

#define MAX 1000
#define       Scale    1.35
#define       MaxSt    50
#define       MaxFc    30
#define       MaxAt    10
#define       IncAng   5
#define       IncRol   15
#define       IncSn    15
#define       IncS     1.5


typedef struct
{
	double x,y;
} DPOINT;

typedef struct{ unsigned all;
				unsigned left,right,top,bottom;
}OutCode;

typedef struct{ 
	double x, y;
}DCPoint;

typedef struct Edge{
	int ymax;
	float x,deltax;
	Edge *nextEdge;
}Edge;

typedef struct{
	int y,xLeft,xRight;
}Span;

typedef struct{
	float x,y;
}Vertex;


typedef Vertex Edg[2];

typedef Vertex VertexArray[MAX];

class CGraphicsView : public CView
{
protected: // create from serialization only
	CGraphicsView();
	DECLARE_DYNCREATE(CGraphicsView)
	CPaintDC * pDC;
	int n, current,current2;
	DPOINT points[100];
	HICON m_hIcon;
	
	

// Attributes
public:
	CGraphicsDoc* GetDocument();
	int AddorMove;
//	void MyDraw(DPOINT * p);
	


// Operations
public:
       
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void FillVPixel(CDC *pDC, CPoint point, COLORREF color);
	void DrawGrid(CDC *pDC);
	int pop(int &x, int &y);
	void push(int x, int y);
	void ScanLineFill(CDC *pdc, int seedx, int seedy, int color0, int fillcolor);
	void SeedFill(CDC *pdc, int x, int y, int boundaryColor, int fillColor);
	void clean();
	void draw(int x, int y, int xx, int yy, int c);
	void mile(int xx, int yy, int r, int color);
	void draw_point(int x, int y, int color);
	void mine(int x0, int y0, int x1, int y1, int color);
	void dne(int x0, int y0, int x1, int y1, int color);
	void ButtomCut();
	void RightCut();
	void TopCut();
	void Intersect(Vertex *s, Vertex *p, Edg clipBoundary, Vertex *I);
	void Output(Vertex *newVertex, int *outLength, VertexArray outVertexArray);
	bool Inside(Vertex *testVertex, Edg clipBoundary);
	void SutherlandHodgmanPolygonClip(int inLength, VertexArray inVertexArray, int *outLength, VertexArray outVertexArray, Edg clipBoundary);
	void LeftCut();
	bool ClipT(float q, float d, float *t0, float *t1);
	void LiangBarskyLineClip(float x0, float y0, float x1, float y1, RECT *rect);
	void CompOutCode(float x,float y,const RECT *rect,OutCode *outCode);
	void CohenSutherlandLineClip(float x0,float y0,float x1,float y1,const RECT *rect);
	void Rect(CDC *pdc, int x0, int y0, int x1, int y1, int color);
	void Change(CDC *pDC,int x0,int y0,int x1,int y1, int fillColor);
	
	void DDALine(CDC *pdc, int x0, int y0, int x1, int y1, int color);
	void DrawBezier(DPOINT * p);
 //   void LiangBarskyLineClip(float x0,float y0,float x1,float y1,const RECT *rect);
	virtual ~CGraphicsView();
   	VertexArray outVertexArray;
	VertexArray inVertexArray;
	RECT rect;
	Edg clipBoundary;
	Edge *ET[800];
	Span *spanStack[MAX];
	bool IsAccept;
	int outLength;
	int inLength;
	int top;
	int VertexTotal;
	POINT p2[2];
	POINT p1[2];
	CPoint prepoint;
	CPoint spoint;
	int nline;
	int start;
	bool stop;
	float delta;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicsView)
	afx_msg void OnColor();
	afx_msg void OnClear();
	afx_msg void OnIntersection();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBezier();
	afx_msg void OnBezierClear();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBezierAdd();
	afx_msg void OnBezierMove();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDdaLine();
	afx_msg void OnUpdateDdaLine(CCmdUI* pCmdUI);
	afx_msg void OnChange();
	afx_msg void OnUpdateChange(CCmdUI* pCmdUI);
	afx_msg void OnFourFill();
	afx_msg void OnUpdateFourFill(CCmdUI* pCmdUI);
	afx_msg void OnScanFill();
	afx_msg void OnUpdateScanFill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLiangCut(CCmdUI* pCmdUI);
	afx_msg void OnHsCut();
	afx_msg void OnUpdateHsCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTranslate(CCmdUI* pCmdUI);
	afx_msg void OnScale();
	afx_msg void OnUpdateScale(CCmdUI* pCmdUI);
	afx_msg void OnClock();
	afx_msg void OnUpdateClock(CCmdUI* pCmdUI);
	afx_msg void OnAoduomianti();
	afx_msg void OnUpdateAoduomianti(CCmdUI* pCmdUI);
	afx_msg void OnProjection();
	afx_msg void OnUpdateProjection(CCmdUI* pCmdUI);
	afx_msg void OnYincangmian();
	afx_msg void OnUpdateYincangmian(CCmdUI* pCmdUI);
	afx_msg void OnThreeMove();
	afx_msg void OnUpdateThreeMove(CCmdUI* pCmdUI);
	afx_msg void OnThreeXuanzhuan();
	afx_msg void OnUpdateThreeXuanzhuan(CCmdUI* pCmdUI);
	afx_msg void OnThreeScale();
	afx_msg void OnUpdateThreeScale(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBezier(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBezierMove(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnDLine();
	afx_msg void OnDrawCutWin();
	afx_msg void OnCslineclip();
	afx_msg void OnLblineclip();
	afx_msg void OnDrawDuoBX();
	afx_msg void OnCutDuoBX();
	afx_msg void Onshengcheng();
	afx_msg void Ontwodimbianhuan();
	afx_msg void Onyouxiaobianbiao();
	afx_msg void Onbianyuantianchong();
	afx_msg void Onfourlinjieseeds();
	afx_msg void Onsoamiaoxianseed();
	afx_msg void Onsanshitu();
	afx_msg void Ontoushi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int stackY[1000];
	int stackX[1000];
	int iStack;
	int fillcolor;
	int xx1,xx2,yy1,yy2,xxx2,yyy2; //记录鼠标坐标
	int time;
	int rrb;
	int rra;
	int yy0;
	int xx0;
	int y1;
	int y0;
	int x1;
	int x0;
	HCURSOR OnQueryDragIcon();
	int count;
	int WHAT_TO_DO;
	int COLOR;
	CColorDialog DColor;
	int save[10000][3],ache; 
  	bool up;   //鼠弹起
    bool sym;  //覆盖标记
	CPoint a,b;
	CPoint pointe;
	CPoint point3;
	CPoint point2;
	CPoint point1;
	CPoint P0;  //用于画椭圆，外接矩形左上角点
	CPoint P1;  //外接矩形右下角点
	CPoint VPixel[40][30];
	static CRect RectGrid;
	static int VPSize;
};

#ifndef _DEBUG  // debug version in GraphicsView.cpp
inline CGraphicsDoc* CGraphicsView::GetDocument()
   { return (CGraphicsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSVIEW_H__A96477C3_D26C_4B05_A7EE_62031788951C__INCLUDED_)
