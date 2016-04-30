
#include "stdafx.h"
#include "Graphics.h"
#include "Vertex_Count.h"
#include "GraphicsDoc.h"
#include "GraphicsView.h"
#include "DrawDLG.h"
#include "math.h"
#include "time.h"
#define R 100
#define rd 5
#define PI 3.1415926

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGraphicsView

IMPLEMENT_DYNCREATE(CGraphicsView, CView)

BEGIN_MESSAGE_MAP(CGraphicsView, CView)
	//{{AFX_MSG_MAP(CGraphicsView)
	ON_COMMAND(ID_COLOR, OnColor)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_COMMAND(ID_INTERSECTION, OnIntersection)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_BEZIER, OnBezier)
	ON_COMMAND(ID_BEZIER_CLEAR, OnBezierClear)
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BEZIER_ADD, OnBezierAdd)
	ON_COMMAND(ID_BEZIER_MOVE, OnBezierMove)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DDA_LINE, OnDdaLine)
	ON_UPDATE_COMMAND_UI(ID_DDA_LINE, OnUpdateDdaLine)
	ON_COMMAND(ID_CHANGE, OnChange)
	ON_UPDATE_COMMAND_UI(ID_CHANGE, OnUpdateChange)
	ON_COMMAND(ID_FOUR_FILL, OnFourFill)
	ON_UPDATE_COMMAND_UI(ID_FOUR_FILL, OnUpdateFourFill)
	ON_COMMAND(ID_SCAN_FILL, OnScanFill)
	ON_UPDATE_COMMAND_UI(ID_SCAN_FILL, OnUpdateScanFill)
	ON_UPDATE_COMMAND_UI(ID_LINE_CUT, OnUpdateLineCut)
	ON_UPDATE_COMMAND_UI(ID_LIANG_CUT, OnUpdateLiangCut)
	ON_COMMAND(ID_HS_CUT, OnHsCut)
	ON_UPDATE_COMMAND_UI(ID_HS_CUT, OnUpdateHsCut)
	ON_UPDATE_COMMAND_UI(ID_TRANSLATE, OnUpdateTranslate)
	ON_COMMAND(ID_SCALE, OnScale)
	ON_UPDATE_COMMAND_UI(ID_SCALE, OnUpdateScale)
	ON_COMMAND(ID_CLOCK, OnClock)
	ON_UPDATE_COMMAND_UI(ID_CLOCK, OnUpdateClock)
	ON_COMMAND(ID_AODUOMIANTI, OnAoduomianti)
	ON_UPDATE_COMMAND_UI(ID_AODUOMIANTI, OnUpdateAoduomianti)
	ON_COMMAND(ID_PROJECTION, OnProjection)
	ON_UPDATE_COMMAND_UI(ID_PROJECTION, OnUpdateProjection)
	ON_COMMAND(ID_YINCANGMIAN, OnYincangmian)
	ON_UPDATE_COMMAND_UI(ID_YINCANGMIAN, OnUpdateYincangmian)
	ON_COMMAND(ID_THREE_MOVE, OnThreeMove)
	ON_UPDATE_COMMAND_UI(ID_THREE_MOVE, OnUpdateThreeMove)
	ON_COMMAND(ID_THREE_XUANZHUAN, OnThreeXuanzhuan)
	ON_UPDATE_COMMAND_UI(ID_THREE_XUANZHUAN, OnUpdateThreeXuanzhuan)
	ON_COMMAND(ID_THREE_SCALE, OnThreeScale)
	ON_UPDATE_COMMAND_UI(ID_THREE_SCALE, OnUpdateThreeScale)
	ON_UPDATE_COMMAND_UI(ID_BEZIER, OnUpdateBezier)
	ON_UPDATE_COMMAND_UI(ID_BEZIER_MOVE, OnUpdateBezierMove)
	ON_WM_PAINT()
	ON_COMMAND(ID_DLine, OnDLine)
	ON_COMMAND(ID_DrawCutWin, OnDrawCutWin)
	ON_COMMAND(ID_CSLINECLIP, OnCslineclip)
	ON_COMMAND(ID_LBLINECLIP, OnLblineclip)
	ON_COMMAND(ID_DrawDuoBX, OnDrawDuoBX)
	ON_COMMAND(ID_CutDuoBX, OnCutDuoBX)
	ON_COMMAND(ID_shengcheng, Onshengcheng)
	ON_COMMAND(ID_twodimbianhuan, Ontwodimbianhuan)
	ON_COMMAND(fill_youxiaobianbiao, Onyouxiaobianbiao)
	ON_COMMAND(fill_bianyuantianchong, Onbianyuantianchong)
	ON_COMMAND(fill_fourlinjieseeds, Onfourlinjieseeds)
	ON_COMMAND(fill_soamiaoxianseed, Onsoamiaoxianseed)
	ON_COMMAND(touying_sanshitu, Onsanshitu)
	ON_COMMAND(touying_toushi, Ontoushi)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

//静态变量初始化
int CGraphicsView::VPSize=20;  //像素边长为20
CRect CGraphicsView::RectGrid=CRect(10,14,810,614);  //绘图区域

// CGraphicsView construction/destruction
CGraphicsView::CGraphicsView()
{
	// TODO: add construction code here
	
    WHAT_TO_DO=-1;
	/////Bezier曲线初始化
//------------------------------------------//
	n = -1;
	current2 = -1;
	current = -1;
	AddorMove =1;

//---------------------------------------//
	COLOR = RGB(0,255,255);
	fillcolor = RGB(255,0,255);
	time =5;
//	clip = false;
	count=0;
	
	int i;
	for(i=0;i<800;i++)
		ET[i]=NULL;
	for(i=0;i<100;i++)
		spanStack[i]=NULL;
	top=0;
	
	point1.x=0;
	point1.y=0;
	point2.x=0;
	point2.y=0;
	rect.left=0;
	rect.right=0;
	rect.bottom=0;
	rect.top=0;
	IsAccept=FALSE;
	inLength=0;
	outLength=0;
	VertexTotal=0;
	p1[0].x=0;
	p1[0].y=0;
	p1[1].x=0;
	p1[1].y=0;
	p2[0].x=0;
	p2[0].y=0;
	p2[1].x=0;
	p2[1].y=0;
	nline=0;
	start=0;
	stop=TRUE;
	spoint.x=0;
	spoint.y=0;
	n=-1;
	delta=10;
}

CGraphicsView::~CGraphicsView()
{
}

BOOL CGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView drawing

void CGraphicsView::OnDraw(CDC* pDC)
{
	CGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
/*	Vertex_Count dlg;
	if(dlg.DoModal()==IDOK)
	{
		MessageBox("输入顶点数过大");
	}*/
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView printing

BOOL CGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView diagnostics

#ifdef _DEBUG
void CGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsDoc* CGraphicsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsDoc)));
	return (CGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsView message handlers

void CGraphicsView::OnColor() 
{
	// TODO: Add your command handler code here
	DColor.DoModal();
	COLOR=DColor.GetColor( );
}

void CGraphicsView::OnClear() 
{
	// TODO: Add your command handler code here
	Invalidate();
}

void CGraphicsView::OnIntersection() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_INTERSECTION;
}

void CGraphicsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	a.x=point.x;
	a.y=point.y;
   switch(WHAT_TO_DO)
   {
    case ID_BEZIER:
	   {	
		   if(AddorMove == 1)
			{
				if(n>=9) 
				{
					AfxMessageBox("Too many points.");
					return;
				}
				n++;
				points[n].x = point.x;
				points[n].y = point.y;
				RedrawWindow();
			}
		else if(AddorMove == -1)
		{
			double x, y;
			current = -1;
			double t=50;
			for(int i = 0; i <= n; i++)
			{
				x = points[i].x - point.x, y = points[i].y - point.y;
				x*=x; y*=y;
				if(x + y < t)
				{	current = i;	t=x+y;	}

				}
		}
		break;
	 }
	  case ID_SCAN_FILL:
		   {
			  x0=point.x;
			  y0=point.y;
				CClientDC dc(this);
					CDC* pDC=&dc;
					int oldColor = RGB(255,0,255);
		if (x0 > 100 && x0 < 400 && y0 > 150 && y0 < 400)
			ScanLineFill(pDC,200,200,oldColor,COLOR);
		else
			MessageBox("The point is outside");
		break;
	
	 }
	case ID_DLine:
	{
		CDC *pDC=GetDC();
		CPen pen(PS_SOLID,2,RGB(255,255,255));
		CPen *pOldpen=pDC->SelectObject(&pen);
		pDC->MoveTo(point1);
		pDC->LineTo(point2);
		pDC->SelectObject(pOldpen);
		ReleaseDC(pDC);
		point1=point;
		break;
	}
	case ID_DrawCutWin:
	{
		CDC *pDC=GetDC();
		CPen pen(PS_SOLID,2,RGB(255,255,255));
		CPen *pOldpen=pDC->SelectObject(&pen);
		pDC->MoveTo(rect.left,rect.top);
		pDC->LineTo(rect.right,rect.top);
		pDC->LineTo(rect.right,rect.bottom);
		pDC->LineTo(rect.left,rect.bottom);
		pDC->LineTo(rect.left,rect.top);
		pDC->SelectObject(pOldpen);
		ReleaseDC(pDC);
		point3=point;
		break;
	}
	case ID_DrawDuoBX:
	{
		if(inLength>=VertexTotal)
			return;
		CDC *pDC=GetDC();
		if(inLength==0)
			prepoint=point;
		else
		{
			pDC->MoveTo(prepoint);
			pDC->LineTo(point.x,point.y);
			prepoint=point;
		}
		inVertexArray[inLength].x=(float)point.x;
		inVertexArray[inLength].y=(float)point.y;
		inLength++;
		if(inLength==VertexTotal)
		{
			pDC->LineTo((int)inVertexArray[0].x,(int)inVertexArray[0].y);
			VertexTotal=0;
		}
		ReleaseDC(pDC);
		break;
	}
	case ID_FOUR_FILL:
		   {
			  time=0;
				int boundaryColor,fillColor;
					CClientDC dc(this);
					CDC* pDC=&dc;
				x0=point.x;
				y0=point.y;
			boundaryColor = RGB(0,0,0);
			fillColor = RGB(0,255,255);
			   if (x0 > 100 && x0 < 200 && y0 > 200 && y0 < 250)
			SeedFill(pDC,x0,y0,boundaryColor,fillColor);
		else
			MessageBox("The point is outside");
		time=5;
		break;
		   }
	   default: break;
   }
	CView::OnLButtonDown(nFlags, point);
}

void CGraphicsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	b.x=point.x;
	b.y=point.y;
	CClientDC dc(this);
	CDC* pDC=&dc;
	CView::OnLButtonUp(nFlags, point);
	
	switch(WHAT_TO_DO)
	{
	case ID_BEZIER:
		{
			current = -1;
		
            break;
		}
	
	case ID_INTERSECTION:
	{	
		break;
	
	}
	case ID_DDA_LINE:
		{
			DDALine(pDC,a.x,a.y,b.x,b.y,COLOR);
			break;
		}
	
	case ID_CHANGE:
		{	
			time=0;
			Change(pDC,a.x,a.y,b.x,b.y,fillcolor);
			time=5;
			break;
		}
	case ID_DLine:
		{
			point2=point;
			CDC *pDC=GetDC();
			pDC->MoveTo(point1);
			pDC->LineTo(point2);
			ReleaseDC(pDC);
			break;
		}
	case ID_DrawCutWin:
		{
			
		pointe=point;
		CDC *pDC=GetDC();
		pDC->MoveTo(point3);
		pDC->LineTo(pointe.x,point3.y);
		pDC->LineTo(pointe);
		pDC->LineTo(point3.x,pointe.y);
		pDC->LineTo(point3);
		if(point3.x<pointe.x)
		{
			rect.left=point3.x;
			rect.right=pointe.x;
		}
		else
		{
			rect.left=pointe.x;
			rect.right=point3.x;
		}
		if(point3.y<pointe.y)
		{
			rect.top=point3.y;
			rect.bottom=pointe.y;
		}
		else
		{
			rect.top=pointe.y;
			rect.bottom=point3.y;
		}
		ReleaseDC(pDC);
		break;
		}

	default:

		break;
	}
    
}



void CGraphicsView::OnBezier() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_BEZIER;
	CDC *p=GetDC ();
		p->TextOut (10, 20, "PS:鼠标左键添加曲线,鼠标右键修改曲线.");
		ReleaseDC (p);
}

void CGraphicsView::OnBezierClear() 
{
	// TODO: Add your command handler code here
	n = -1;
	RedrawWindow();
}

void CGraphicsView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	current2 = -1;
	CView::OnRButtonUp(nFlags, point);
}

void CGraphicsView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch(WHAT_TO_DO)
	{
	case ID_BEZIER:
		{
		if(AddorMove == -1)
	{
		if(n>=99) 
		{
			AfxMessageBox("Too many points.");
			return;
		}
		n++;
		points[n].x = point.x;
		points[n].y = point.y;
		RedrawWindow();
	}
	else if(AddorMove == 1)
	{
		double x, y;
		double t=50;
		current2 = -1;
		for(int i = 0; i <= n; i++)
		{
			x = points[i].x - point.x, y = points[i].y - point.y;
			x*=x; y*=y;
			if(x + y < t) {current2 = i; t=x+y;}
		}
	}
	break;
		}
	default:
		break;
	}
	CView::OnRButtonDown(nFlags, point);
}

HCURSOR CGraphicsView::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CGraphicsView::DrawBezier(DPOINT *p)
{
	if (n <= 0) return;
	if((p[n].x < p[0].x+1) && (p[n].x > p[0].x-1) && (p[n].y < p[0].y+1) && (p[n].y > p[0].y-1))
	{
		pDC->SetPixel(p[0].x, p[0].y, COLOR);
		return;
	}
	DPOINT *p1;
	p1 = new DPOINT[n+1];
	int i, j;
	p1[0] = p[0];
	for(i=1; i<=n; i++)
	{
		for(j=0; j<=n-i;j++)
		{
			p[j].x = (p[j].x + p[j+1].x)/2;
			p[j].y = (p[j].y + p[j+1].y)/2;
		}
		p1[i] = p[0];
	}
	DrawBezier(p);
	DrawBezier(p1);
	delete p1;

}


void CGraphicsView::OnBezierAdd() 
{
	// TODO: Add your command handler code here
	AddorMove = 1;	
}

void CGraphicsView::OnBezierMove() 
{
	// TODO: Add your command handler code here
	AddorMove = -1;
}

void CGraphicsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch(WHAT_TO_DO)
	{
	case ID_BEZIER:
		{	
			if(current >= 0 ) 
		{
		points[current].x = point.x;
		points[current].y = point.y;
		RedrawWindow();
		}
	if(current2 >= 0 ) 
	{
		points[current2].x = point.x;
		points[current2].y = point.y;
		RedrawWindow();
	}
	
	break;
		}
	default:break;
	}
	CView::OnMouseMove(nFlags, point);
}

void CGraphicsView::OnDdaLine() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_DDA_LINE;
}

void CGraphicsView::OnUpdateDdaLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
		pCmdUI->SetCheck(WHAT_TO_DO==ID_DDA_LINE);
}




void CGraphicsView::OnChange() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_CHANGE;
	
}

void CGraphicsView::OnUpdateChange(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_CHANGE);
}

void CGraphicsView::OnFourFill() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_FOUR_FILL;
	time=0;
	CClientDC dc(this);
	CDC* pDC=&dc;
	
	int boundaryColor,fillColor;
	int x,y;

	boundaryColor = RGB(0,0,0);
	fillColor = RGB(0,255,255);

	x = 40;
	y = 80;
	Rect(pDC,100,200,200,250,boundaryColor);
	time=5;
}

void CGraphicsView::OnUpdateFourFill(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_FOUR_FILL);
}

void CGraphicsView::OnScanFill() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_SCAN_FILL;
	time=0;
	WHAT_TO_DO=ID_SCAN_FILL;
		int oldColor,newColor;
	CClientDC dc(this);
	CDC* pDC=&dc;
	
	oldColor = RGB(255,0,255);
	newColor = RGB(255,255,0);
	Rect(pDC,100,150,400,400,oldColor);
	time=5;
}

void CGraphicsView::OnUpdateScanFill(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_SCAN_FILL);
}


void CGraphicsView::OnUpdateLineCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_LINE_CUT);
}


void CGraphicsView::OnUpdateLiangCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_LIANG_CUT);
}

void CGraphicsView::OnHsCut() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_HS_CUT;

}

void CGraphicsView::OnUpdateHsCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(WHAT_TO_DO==ID_HS_CUT);
}



void CGraphicsView::OnUpdateTranslate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_TRANSLATE);
}



void CGraphicsView::OnScale() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_SCALE;
		OnClear();
	CClientDC dc(this);
	CDC* pDC=&dc;
		time=0;
	int i,white=RGB(255,255,255), point[4][2]={{300,250},{400,250},{300,300},{400,300}};
	float sx=0.9,sy=0.85;
	int midx=(point[0][0]+point[3][0])/2,midy=(point[0][1]+point[3][1])/2;
	Matrix s1 (sx,sy),s2 (1/sx,1/sy);
	Matrix t1 (midx, midy,true), t2 (-midx, -midy,true); 
	Matrix a (point[0][0],point[0][1]), b (point[1][0],point[1][1]);
	Matrix c (point[2][0],point[2][1]), d (point[3][0],point[3][1]);
	Matrix temp (midx, midy,true);
	temp = t1*s1*t2;
	DDALine (pDC,a.getx(),a.gety(),b.getx(),b.gety(),COLOR);
	DDALine (pDC,a.getx(),a.gety(),c.getx(),c.gety(),COLOR);
	DDALine (pDC,c.getx(),c.gety(),d.getx(),d.gety(),COLOR);
	DDALine (pDC,d.getx(),d.gety(),b.getx(),b.gety(),COLOR);
	for(i=0;i<20;i++){
		::Sleep (30);
		DDALine (pDC,a.getx(),a.gety(),b.getx(),b.gety(),white);
		DDALine (pDC,a.getx(),a.gety(),c.getx(),c.gety(),white);
		DDALine (pDC,c.getx(),c.gety(),d.getx(),d.gety(),white);
		DDALine (pDC,d.getx(),d.gety(),b.getx(),b.gety(),white);	
		a=temp*a;
		b=temp*b;
		c=temp*c;
		d=temp*d;
		DDALine (pDC,a.getx(),a.gety(),b.getx(),b.gety(),COLOR);
		DDALine (pDC,a.getx(),a.gety(),c.getx(),c.gety(),COLOR);
		DDALine (pDC,c.getx(),c.gety(),d.getx(),d.gety(),COLOR);
		DDALine (pDC,d.getx(),d.gety(),b.getx(),b.gety(),COLOR);
	}
	temp = t1*s2*t2;
	for(i=0;i<20;i++){
		::Sleep (30);
		DDALine (pDC,a.getx(),a.gety(),b.getx(),b.gety(),white);
		DDALine (pDC,a.getx(),a.gety(),c.getx(),c.gety(),white);
		DDALine (pDC,c.getx(),c.gety(),d.getx(),d.gety(),white);
		DDALine (pDC,d.getx(),d.gety(),b.getx(),b.gety(),white);
		a=temp*a;
		b=temp*b;
		c=temp*c;
		d=temp*d;
		DDALine (pDC,a.getx(),a.gety(),b.getx(),b.gety(),COLOR);
		DDALine (pDC,a.getx(),a.gety(),c.getx(),c.gety(),COLOR);
		DDALine (pDC,c.getx(),c.gety(),d.getx(),d.gety(),COLOR);
		DDALine (pDC,d.getx(),d.gety(),b.getx(),b.gety(),COLOR);
	}
	time=5;
}

void CGraphicsView::OnUpdateScale(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_SCALE);
}

void CGraphicsView::OnClock() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_CLOCK;
        clean();
	int xx = 450, yy = 300, r = 150,d = 5;
	int i, white = RGB (255,255,255);
	mile (xx, yy, r, COLOR);
	Matrix m (xx, 240), s (xx, 200);
	Matrix t1 (xx, yy, true), t2 (-xx, -yy, true), mr ( PI/1800 ), sr ( PI/30 );
	mile (m.getx (), m.gety (), d+1, COLOR);
	mile (s.getx (), s.gety (), d, COLOR);
	dne ( m.getx (), m.gety (), xx, yy, COLOR );
	dne ( s.getx (), s.gety (), xx, yy, COLOR );	
	for (i=0;i<120;i++){
		::Sleep (80);
		mile (m.getx (), m.gety (), d+1, white);
		mile (s.getx (), s.gety (), d, white);
		dne ( m.getx (), m.gety (), xx, yy, white );
		dne ( s.getx (), s.gety (), xx, yy, white );
		m = t1*mr*t2*m;
		s = t1*sr*t2*s;
		mile (m.getx (), m.gety (), d+1, COLOR);
		mile (s.getx (), s.gety (),d, COLOR);
		dne ( m.getx (), m.gety (), xx, yy, COLOR );
		dne ( s.getx (), s.gety (), xx, yy, COLOR );
	}

}

void CGraphicsView::OnUpdateClock(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_CLOCK);
}


void CGraphicsView::OnAoduomianti() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_AODUOMIANTI;
	CDrawDLG dlg1;
	dlg1.DoModal();
}

void CGraphicsView::OnUpdateAoduomianti(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_AODUOMIANTI);
}

void CGraphicsView::OnProjection() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_PROJECTION;
}

void CGraphicsView::OnUpdateProjection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_PROJECTION);
}

void CGraphicsView::OnYincangmian() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_YINCANGMIAN;
}

void CGraphicsView::OnUpdateYincangmian(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_YINCANGMIAN);
}

void CGraphicsView::OnThreeMove() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_THREE_MOVE;
}

void CGraphicsView::OnUpdateThreeMove(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(WHAT_TO_DO==ID_THREE_MOVE);
}

void CGraphicsView::OnThreeXuanzhuan() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_THREE_XUANZHUAN;
}

void CGraphicsView::OnUpdateThreeXuanzhuan(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(WHAT_TO_DO==ID_THREE_XUANZHUAN);
}

void CGraphicsView::OnThreeScale() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_THREE_SCALE;
}

void CGraphicsView::OnUpdateThreeScale(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(WHAT_TO_DO==ID_THREE_SCALE);
}

void CGraphicsView::OnUpdateBezier(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_BEZIER);
}





void CGraphicsView::DDALine(CDC *pdc, int x0, int y0, int x1, int y1, int color)
{
   	int xx,yy,s,s1,s2,di;
	float dx,dy,k,x,y;

	dx=x1-x0;
	if(dx>=0)
		s1=1;
	else
		s1=-1;
		
	dy=y1-y0;
	if(dy>=0)
		s2=1;
	else
		s2=-1;
	dx=abs(dx);
	dy=abs(dy);
	if(dx>=dy)
	{
		s=0;
		di=(int)dx;
		k=dy/dx*s2;
	}
	else
	{
		s=1;
		di=(int)dy;
		k=dx/dy*s1;
	}
	x=x0;
	y=y0;
	for(int i=0;i<=di;i++)
	{
		if(s==0)
		{
			xx=(int)x;
			yy=(int)(y+0.5);
			::Sleep(time);
			pdc->SetPixel(xx,yy,color);
			x+=s1;
			y+=k;
		}
		else
		{
			xx=(int)(x+0.5);
			yy=(int)y;
			::Sleep(time);
			pdc->SetPixel(xx,yy,color);
			y+=s2;
			x+=k;
		}
	}
}




void CGraphicsView::Change(CDC *pDC,int x0,int x1,int y0,int y1, int fillColor)
{
	int backgroundColor;
	int y;
	

	backgroundColor = RGB(255,255,255);
	
	Rect(pDC,200,200,400,400,fillColor);
	for (y = 200; y <= 400; y++)  {
			DDALine(pDC,400,y,2000,y,fillColor);
	}
	
	for (y = 200; y <= 400; y++)   {
		DDALine(pDC,200,y,400,y,fillColor);
		DDALine(pDC,400,y,2000,y,backgroundColor);
	}
}

void CGraphicsView::Rect(CDC *pdc, int x0, int y0, int x1, int y1, int color)  //画矩形
{
	DDALine(pdc,x0,y0,x1,y0,color);
	DDALine(pdc,x0,y0,x0,y1,color);
	DDALine(pdc,x1,y0,x1,y1,color);
	DDALine(pdc,x0,y1,x1,y1,color);

}


void CGraphicsView::OnUpdateBezierMove(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(WHAT_TO_DO==ID_BEZIER_MOVE);
}

void CGraphicsView::OnPaint() 
{

		if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		pDC = new CPaintDC(this);
		if(n>=0) 
		{
			pDC->MoveTo(points[0].x, points[0].y);
			for(int i = 0; i<=n; i++)
			{
				CPen penStroke(PS_SOLID,1,0x007700);
				CPen *ppenPrevious=pDC->SelectObject(&penStroke);
				pDC->LineTo(points[i].x,points[i].y);
				pDC->SelectObject(ppenPrevious);
		    	CPen penStroke2(PS_SOLID,1,0xff0000);
				CPen *ppenPrevious2=pDC->SelectObject(&penStroke2);
				pDC->Rectangle(points[i].x - 5, points[i].y -5 ,points[i].x + 5 ,points[i].y + 5);
				pDC->SelectObject(ppenPrevious2);
			}
			DPOINT p[11];
			memcpy(p, points, sizeof(p));
			DrawBezier(p);
		}
		CView::OnPaint();
		delete pDC;
	}
	
}
/*裁剪算法*/
void CGraphicsView::CohenSutherlandLineClip(float x0, float y0, float x1, float y1, const RECT *rect)
{
	BOOL accept,done;
	OutCode outCode0,outCode1,*outCodeOut;
	float x,y;
	accept=FALSE;
	done=FALSE;
	CompOutCode(x0,y0,rect,&outCode0);
	CompOutCode(x1,y1,rect,&outCode1);
	do
	{
		if((outCode0.all|outCode1.all)==0)  //简取，在裁剪窗口内
		{
			accept=TRUE;
			done=TRUE;
		}
		else
			if((outCode0.all&outCode1.all)!=0)  //间弃，在裁剪窗口外
				done=TRUE;
			else
			{
				if(outCode0.all!=0) //确保outCodeOut一定在裁剪窗口外
					outCodeOut=&outCode0;
				else
					outCodeOut=&outCode1;
				if(outCodeOut->left)
				{
					y=y0+(y1-y0)*((float)(rect->left)-x0)/(x1-x0);
					x=(float)rect->left;
				}
				else
					if(outCodeOut->top)
					{
						x=x0+(x1-x0)*((float)(rect->bottom)-y0)/(y1-y0);
						y=(float)rect->bottom;
					}
					else
						if(outCodeOut->right)
						{
							y=y0+(y1-y0)*((float)(rect->right)-x0)/(x1-x0);
							x=(float)rect->right;
						}
						else  //bottom
						{
							x=x0+(x1-x0)*((float)(rect->top)-y0)/(y1-y0);
							y=(float)rect->top;
						}
				if(outCodeOut->all==outCode0.all)
				{
					x0=x;
					y0=y;
					CClientDC   dc(this);
			    	CPen   pen(PS_GEOMETRIC,1,RGB(0,0,0));
			    	CPen   *pOldPen=dc.SelectObject(&pen); 
					CDC *pDC=GetDC();
					pDC->SelectObject(&pen);
					pDC->MoveTo((int)(x0+0.5),(int)(y0+0.5));
					pDC->LineTo((int)(x1+0.5),(int)(y1+0.5));
					ReleaseDC(pDC);
					dc.SelectObject(pOldPen); 
					
					//是为了能够将每一步裁剪演示出来
					Sleep(1000);
					CClientDC   dc2(this);
			    	CPen   pen2(PS_GEOMETRIC,1,RGB(255,255,255));  //将之前画的线用白色覆盖
			    	CPen   *pOldPen2=dc2.SelectObject(&pen2); 
					
					pDC->SelectObject(&pen2);
					pDC->MoveTo((int)(x0+0.5),(int)(y0+0.5));
					pDC->LineTo((int)(x1+0.5),(int)(y1+0.5));
					ReleaseDC(pDC);
					dc.SelectObject(pOldPen2); 
					CompOutCode(x0,y0,rect,&outCode0);
				}
				else
				{
					x1=x;
					y1=y;
					CClientDC   dc(this);
			    	CPen   pen(PS_GEOMETRIC,1,RGB(0,0,0));
			    	CPen   *pOldPen=dc.SelectObject(&pen); 
					CDC *pDC=GetDC();
					pDC->MoveTo((int)(x0+0.5),(int)(y0+0.5));
					pDC->LineTo((int)(x1+0.5),(int)(y1+0.5));
					ReleaseDC(pDC);
					dc.SelectObject(pOldPen); 


					Sleep(1000);
					CClientDC   dc2(this);
			    	CPen   pen2(PS_GEOMETRIC,1,RGB(255,255,255));
			    	CPen   *pOldPen2=dc2.SelectObject(&pen2); 
					
					pDC->SelectObject(&pen2);
					pDC->MoveTo((int)(x0+0.5),(int)(y0+0.5));
					pDC->LineTo((int)(x1+0.5),(int)(y1+0.5));
					ReleaseDC(pDC);
					dc.SelectObject(pOldPen2); 
					CompOutCode(x1,y1,rect,&outCode1);
				}
			}
	}
	while(!done);
	if(accept)
	{
		IsAccept=TRUE;
		point1.x=(int)(x0+0.5);
		point1.y=(int)(y0+0.5);
		point2.x=(int)(x1+0.5);
		point2.y=(int)(y1+0.5);
		CDC *pDC=GetDC();
		
		pDC->MoveTo((int)(x0+0.5),(int)(y0+0.5));
		pDC->LineTo((int)(x1+0.5),(int)(y1+0.5));
		ReleaseDC(pDC);
	}
}



void CGraphicsView::CompOutCode(float x, float y,  const RECT *rect, OutCode *outCode)//计算点(x,y)的编码,用于CS直线裁剪算法
{
	outCode->all=0;
	outCode->top=outCode->bottom=0;
	if(y>(float)(rect->bottom))
	{
		outCode->top=1;
		outCode->all+=8;
	}
	else
		if(y<(float)(rect->top))
		{
			outCode->bottom=1;
			outCode->all+=4;
		}
	outCode->right=outCode->left=0;
	if(x>(float)(rect->right))
	{
		outCode->right=1;
		outCode->all+=2;
	}
	else
		if(x<(float)(rect->left))
		{
			outCode->left=1;
			outCode->all+=1;
		}
}

/*裁剪算法*/
void CGraphicsView::LiangBarskyLineClip(float x0, float y0, float x1, float y1, RECT *rect)
{
	float deltax,deltay,t0,t1;
	t0=0;
	t1=1;
	deltax=x1-x0;
	if(ClipT(-deltax,x0-rect->left,&t0,&t1))
		if(ClipT(deltax,rect->right-x0,&t0,&t1))
		{
			deltay=y1-y0;
			if(ClipT(-deltay,y0-rect->top,&t0,&t1))
				if(ClipT(deltay,rect->bottom-y0,&t0,&t1))
				{
					IsAccept=TRUE;
					point1.x=(int)(x0+t0*deltax+0.5);
					point1.y=(int)(y0+t0*deltay+0.5);
					point2.x=(int)(x0+t1*deltax+0.5);
					point2.y=(int)(y0+t1*deltay+0.5);
					CDC *pDC=GetDC();
					pDC->MoveTo((int)(x0+t0*deltax+0.5),(int)(y0+t0*deltay+0.5));
					pDC->LineTo((int)(x0+t1*deltax+0.5),(int)(y0+t1*deltay+0.5));
					return;
				}
		}
}



bool CGraphicsView::ClipT(float q, float d, float *t0, float *t1)
{
	float r;
	if(q<0)
	{
		r=d/q;
		if (r>*t1)
			return (FALSE);
		else if (r>*t0)
		{ 
			*t0=r;
		    return (TRUE);
		}
	}
	else if (q>0){
		r=d/q;
		if (r<*t0)
			return(FALSE);
		else if (r<*t1)
		{
			*t1=r;
			return(TRUE);
		}
	}
	else if (d<0)
		return (FALSE);
	return(TRUE);
}



void CGraphicsView::OnDLine() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_DLine;
}

void CGraphicsView::OnDrawCutWin() 
{
	// TODO: Add your command handler code here
	WHAT_TO_DO=ID_DrawCutWin;
}

void CGraphicsView::OnCslineclip()  //cs裁剪控制函数
{
	// TODO: Add your command handler code here
	if(point1.x==0&&point1.y==0&&point2.x==0&&point2.y==0||rect.left==0&&rect.right==0&&rect.top==0&&rect.bottom==0)
		return;
	CDC *pDC=GetDC();
	CPen pen(PS_SOLID,2,RGB(255,255,255));
	CPen *pOldpen=pDC->SelectObject(&pen);
//	int OldType=pDC->SetROP2(R2_XORPEN);
	pDC->MoveTo(point1);
	pDC->LineTo(point2);
	
	pDC->MoveTo(100,200);
	pDC->LineTo(200,300);
	pDC->SelectObject(pOldpen);
//	pDC->SetROP2(OldType);
	
	CohenSutherlandLineClip((float) point1.x, (float) point1.y, (float) point2.x, (float) point2.y, &rect);
	
	if(!IsAccept)
	{
		point1.x=0;
		point1.y=0;
		point2.x=0;
		point2.y=0;
	}
	else
		IsAccept=FALSE;	
}

void CGraphicsView::OnLblineclip() 
{
	// TODO: Add your command handler code here
	if(point1.x==0&&point1.y==0&&point2.x==0&&point2.y==0||rect.left==0&&rect.right==0&&rect.top==0&&rect.bottom==0)
	return;
	CDC *pDC=GetDC();
	CPen pen(PS_SOLID,2,RGB(255,255,255));
	CPen *pOldpen=pDC->SelectObject(&pen);
	pDC->MoveTo(point1);
	pDC->LineTo(point2);
	pDC->SelectObject(pOldpen);
	ReleaseDC(pDC);
	LiangBarskyLineClip((float) point1.x, (float) point1.y, (float) point2.x, (float) point2.y, &rect);
	if(!IsAccept)
	{
		point1.x=0;
		point1.y=0;
		point2.x=0;
		point2.y=0;
	}
	else
		IsAccept=FALSE;
}

void CGraphicsView::OnDrawDuoBX()    //画多边形
{
	// TODO: Add your command handler code here
	Vertex_Count dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_vertex_count>MAX)
		{
			MessageBox("输入顶点数过大");
			return;
		}
		VertexTotal=dlg.m_vertex_count;
		CDC *pDC=GetDC();
		CPen pen(PS_SOLID,2,RGB(255,255,255));
		CPen *pOldpen=pDC->SelectObject(&pen);
		pDC->MoveTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
		int i;
		for(i=1;i<inLength;i++)
			pDC->LineTo((int)(inVertexArray[i].x+0.5),(int)(inVertexArray[i].y+0.5));
		pDC->LineTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
		pDC->SelectObject(pOldpen);
		ReleaseDC(pDC);
		inLength=0;
		outLength=0;
		WHAT_TO_DO=ID_DrawDuoBX;
	}
}

void CGraphicsView::OnCutDuoBX()   //多边形裁剪
{
	// TODO: Add your command handler code here
   LeftCut();
   ::Sleep (500);
   TopCut();
   ::Sleep (500);
   RightCut();
   ::Sleep (500);
   ButtomCut();
 

}

void CGraphicsView::LeftCut()
{
	clipBoundary[0].x=(float)rect.left;
	clipBoundary[0].y=(float)rect.bottom;
	clipBoundary[1].x=(float)rect.left;
	clipBoundary[1].y=(float)rect.top;
	SutherlandHodgmanPolygonClip(inLength, inVertexArray, &outLength, outVertexArray, clipBoundary);
	CDC *pDC=GetDC();
	CPen pen(PS_SOLID,2,RGB(255,255,255));
	CPen *pOldpen=pDC->SelectObject(&pen);
	pDC->MoveTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
	int i;
	for(i=1;i<inLength;i++)
		pDC->LineTo((int)(inVertexArray[i].x+0.5),(int)(inVertexArray[i].y+0.5));
	pDC->LineTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
	CPen Drawpen(PS_SOLID,1,RGB(255,0,0));
	pDC->SelectObject(&Drawpen);
	pDC->MoveTo((int)(outVertexArray[0].x+0.5),(int)(outVertexArray[0].y+0.5));
	for(i=1;i<outLength;i++)
		pDC->LineTo((int)(outVertexArray[i].x+0.5),(int)(outVertexArray[i].y+0.5));
	pDC->LineTo((int)(outVertexArray[0].x+0.5),(int)(outVertexArray[0].y+0.5));
	pDC->SelectObject(pOldpen);
	ReleaseDC(pDC);
	for(i=0;i<outLength;i++)
		inVertexArray[i]=outVertexArray[i];
	inLength=outLength;
	
}

void CGraphicsView::SutherlandHodgmanPolygonClip(int inLength, VertexArray inVertexArray, int *outLength, VertexArray outVertexArray, Edg clipBoundary)
{

	Vertex *s,*p,I;
	int j;
	*outLength=0;
	s=&(inVertexArray[inLength-1]);
	for(j=0;j<inLength;j++)
	{
		p=&(inVertexArray[j]);
		if(Inside(p,clipBoundary))
			if(Inside(s,clipBoundary))
				Output(p,outLength,outVertexArray);
			else
			{
				Intersect(s,p,clipBoundary,&I);
				Output(&I,outLength,outVertexArray);
				Output(p,outLength,outVertexArray);
			}
		else
			if(Inside(s,clipBoundary))
			{
				Intersect(s,p,clipBoundary,&I);
				Output(&I,outLength,outVertexArray);
			}
		s=p;
	}
}

bool CGraphicsView::Inside(Vertex *testVertex, Edg clipBoundary)  //判断点是否在边界内
{
	if(clipBoundary[1].x>clipBoundary[0].x)
	{
		if(testVertex->y>=clipBoundary[0].y)
			return true;
	}
	else
		if(clipBoundary[1].x<clipBoundary[0].x)
		{
			if(testVertex->y<=clipBoundary[0].y)
				return true;
		}
		else
			if(clipBoundary[1].y>clipBoundary[0].y)
			{
				if(testVertex->x<=clipBoundary[0].x)
					return true;
			}
			else
				if(clipBoundary[1].y<clipBoundary[0].y)
				{
					if(testVertex->x>=clipBoundary[0].x)
						return true;
				}
	return FALSE;
}

void CGraphicsView::Output(Vertex *newVertex, int *outLength, VertexArray outVertexArray)
{
	outVertexArray[*outLength].x=newVertex->x;
	outVertexArray[*outLength].y=newVertex->y;
	(*outLength)++;
}

void CGraphicsView::Intersect(Vertex *s, Vertex *p, Edg clipBoundary, Vertex *I)
{
	if(clipBoundary[0].y==clipBoundary[1].y)
	{
		I->y=clipBoundary[0].y;
		I->x=s->x+(clipBoundary[0].y-s->y)*(p->x-s->x)/(p->y-s->y);
	}
	else
	{
		I->x=clipBoundary[0].x;
		I->y=s->y+(clipBoundary[0].x-s->x)*(p->y-s->y)/(p->x-s->x);
	}
}

void CGraphicsView::TopCut()
{
clipBoundary[0].x=(float)rect.left;
	clipBoundary[0].y=(float)rect.top;
	clipBoundary[1].x=(float)rect.right;
	clipBoundary[1].y=(float)rect.top;
	SutherlandHodgmanPolygonClip(inLength, inVertexArray, &outLength, outVertexArray, clipBoundary);
	CDC *pDC=GetDC();
	CPen pen(PS_SOLID,2,RGB(255,255,255));
	CPen *pOldpen=pDC->SelectObject(&pen);
	pDC->MoveTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
	int i;
	for(i=1;i<inLength;i++)
		pDC->LineTo((int)(inVertexArray[i].x+0.5),(int)(inVertexArray[i].y+0.5));
	pDC->LineTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
	CPen Drawpen(PS_SOLID,1,RGB(255,0,0));
	pDC->SelectObject(&Drawpen);
	pDC->MoveTo((int)(outVertexArray[0].x+0.5),(int)(outVertexArray[0].y+0.5));
	for(i=1;i<outLength;i++)
		pDC->LineTo((int)(outVertexArray[i].x+0.5),(int)(outVertexArray[i].y+0.5));
	pDC->LineTo((int)(outVertexArray[0].x+0.5),(int)(outVertexArray[0].y+0.5));
	pDC->SelectObject(pOldpen);
	ReleaseDC(pDC);
	for(i=0;i<outLength;i++)
		inVertexArray[i]=outVertexArray[i];
	inLength=outLength;
}

void CGraphicsView::RightCut()
{
	clipBoundary[0].x=(float)rect.right;
	clipBoundary[0].y=(float)rect.top;
	clipBoundary[1].x=(float)rect.right;
	clipBoundary[1].y=(float)rect.bottom;
	SutherlandHodgmanPolygonClip(inLength, inVertexArray, &outLength, outVertexArray, clipBoundary);
	CDC *pDC=GetDC();
	CPen pen(PS_SOLID,2,RGB(255,255,255));
	CPen *pOldpen=pDC->SelectObject(&pen);
	pDC->MoveTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
	int i;
	for(i=1;i<inLength;i++)
		pDC->LineTo((int)(inVertexArray[i].x+0.5),(int)(inVertexArray[i].y+0.5));
	pDC->LineTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
	CPen Drawpen(PS_SOLID,1,RGB(255,0,0));
	pDC->SelectObject(&Drawpen);
	pDC->MoveTo((int)(outVertexArray[0].x+0.5),(int)(outVertexArray[0].y+0.5));
	for(i=1;i<outLength;i++)
		pDC->LineTo((int)(outVertexArray[i].x+0.5),(int)(outVertexArray[i].y+0.5));
	pDC->LineTo((int)(outVertexArray[0].x+0.5),(int)(outVertexArray[0].y+0.5));
	pDC->SelectObject(pOldpen);
	ReleaseDC(pDC);
	for(i=0;i<outLength;i++)
		inVertexArray[i]=outVertexArray[i];
	inLength=outLength;
}

void CGraphicsView::ButtomCut()
{
	clipBoundary[0].x=(float)rect.right;
	clipBoundary[0].y=(float)rect.bottom;
	clipBoundary[1].x=(float)rect.left;
	clipBoundary[1].y=(float)rect.bottom;
	SutherlandHodgmanPolygonClip(inLength, inVertexArray, &outLength, outVertexArray, clipBoundary);
	CDC *pDC=GetDC();
	CPen pen(PS_SOLID,2,RGB(255,255,255));
	CPen *pOldpen=pDC->SelectObject(&pen);
	pDC->MoveTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
	int i;
	for(i=1;i<inLength;i++)
		pDC->LineTo((int)(inVertexArray[i].x+0.5),(int)(inVertexArray[i].y+0.5));
	pDC->LineTo((int)(inVertexArray[0].x+0.5),(int)(inVertexArray[0].y+0.5));
	CPen Drawpen(PS_SOLID,1,RGB(255,0,0));
	pDC->SelectObject(&Drawpen);
	pDC->MoveTo((int)(outVertexArray[0].x+0.5),(int)(outVertexArray[0].y+0.5));
	for(i=1;i<outLength;i++)
		pDC->LineTo((int)(outVertexArray[i].x+0.5),(int)(outVertexArray[i].y+0.5));
	pDC->LineTo((int)(outVertexArray[0].x+0.5),(int)(outVertexArray[0].y+0.5));
	pDC->SelectObject(pOldpen);
	ReleaseDC(pDC);
	for(i=0;i<outLength;i++)
		inVertexArray[i]=outVertexArray[i];
	inLength=outLength;
}

void CGraphicsView::dne(int x0, int y0, int x1, int y1, int color)
{
	double dx, dy, x, y, m;
	dx = x1 - x0;
	dy = y1 - y0;

	if (sym)
		ache=0;

	if (dx == 0){
		for (int i = min(y0,y1), j = abs(y0-y1); j >=0; j-- )
			draw_point (x0, i+j, color);
	}
	else{
		if (dx < 0){
			int xBuf, yBuf;
			xBuf = x0; x0 = x1; x1 = xBuf;
			yBuf = y0; y0 = y1; y1 = yBuf;
			dx = -dx; dy = -dy;
		}

		if (dx >= (dy>0?dy:-dy)){
			m = dy / dx;
			y = y0;
			for (x = x0; x <= x1; x++){
				draw_point((int)x, (int)(y+0.5), color );
				y += m;
			}
		}
		else{
			m = dx / dy;
			if (m < 0)
				m = -m;
			x = x0;
			if (dy > 0){
				for (y = y0; y <= y1; y++){
					draw_point( (int)(x+0.5), (int)y, color);
					x += m;
				}
			}
			else{
				for (y = y0; y >= y1; y--){
				draw_point( (int)(x+0.5), (int)y, color);
					x += m;
				}
			}
		}
	}
}


void CGraphicsView::mine(int x0, int y0, int x1, int y1, int color)
{
	int a,b,delta1,delta2,d,x,y,dx,dy,i,s1,s2;
	a=y0-y1;
	b=x1-x0;

	x=x0;
	y=y0;
	draw_point(x,y,color);
	dx=abs(b);
	dy=abs(a);
	if(b>0)
		s1=1;
	else
		s1=-1;
	if(a<0)
		s2=1;
	else
		s2=-1;
	if(s1<0)
		a=-a;
	if(s2<0)
		b=-b;

	if(dy<=dx)
	{
		d=a+a+b;
		delta1=a+a;
		delta2=delta1+b+b;
		if(s1==s2)
		{
			for(i=0;i<dx;i++)
			{
				if(d<0)
				{
					x+=s1;
					y+=s2;
					d+=delta2;
				}
				else
				{
					x+=s1;
					d+=delta1;
				}
				draw_point(x,y,color);
			}
		}
		else
		{
			for(i=0;i<dx;i++)
			{
				if(d>=0)
				{
					x+=s1;
					y+=s2;
					d+=delta2;
				}
				else
				{
					x+=s1;
					d+=delta1;
				}
				draw_point(x,y,color);
			}
		}
	}
	else
	{
		d=a+b+b;
		delta1=b+b;
		delta2=delta1+a+a;
		if(s1==s2)
		{
			for(i=0;i<dy;i++)
			{
				if(d>0)
				{
					x+=s1;
					y+=s2;
					d+=delta2;
				}
				else
				{
					y+=s2;
					d+=delta1;
				}
				draw_point(x,y,color);
			}
		}
		else
		{
			for(i=0;i<dy;i++)
			{
				if(d<0)
				{
					x+=s1;
					y+=s2;
					d+=delta2;
				}
				else
				{
					y+=s2;     
					d+=delta1;
				}
				draw_point(x,y,color);
			}
		}
	}
}

void CGraphicsView::draw_point(int x, int y, int color)
{
	CDC* pDC=GetDC();
	int cc=pDC->GetPixel(x,y),white=RGB(255,255,255);
	if (cc!=white&&sym){//暂时保存点信息,以备刷新时恢复
		save[ache][0]=(int)(x+0.5);
		save[ache][1]=(int)y;
		save[ache][2]=cc;
		ache++;
	}
	pDC->SetPixel( x, y, color);
	ReleaseDC(pDC);
}


void CGraphicsView::mile(int xx, int yy, int r, int color)
{
  	int x=0,y=r;     
	float d;
	int add=0;//控制终止条件
	if (up)
		add=2;
	d=5.0/4-r;
	if(sym)
		ache=0;
	if (!up){
		draw (x,y,xx,yy,color);
		draw (y,x,xx,yy,color);
	}
	while (y>x+add){
		if (d<=0)
			d+=2.0*x+3;
		else{
			d+=2.0*(x-y)+5;
			y--;
		}
		x++;
		draw (x,y,xx,yy,color);
		draw (y,x,xx,yy,color);

	}
}

void CGraphicsView::draw(int x, int y, int xx, int yy, int c)
{
	CDC* pDC=GetDC();
	int cc,white=RGB(255,255,255);
	cc=pDC->GetPixel(x+xx,y+yy);
	if(cc!=white&&sym){ //暂时保存点信息,以备刷新时恢复
			save[ache][0]=x+xx;
			save[ache][1]=y+yy;
			save[ache][2]=cc;
			ache++;
	}
	pDC->SetPixel (x+xx,y+yy,c);

	cc=pDC->GetPixel(x+xx,-y+yy);
	if(cc!=white&&sym){
			save[ache][0]=x+xx;
			save[ache][1]=-y+yy;
			save[ache][2]=cc;
			ache++;
	}
	pDC->SetPixel (x+xx,-y+yy,c);

	cc=pDC->GetPixel(-x+xx,y+yy);
	if(cc!=white&&sym){
		save[ache][0]=-x+xx;
		save[ache][1]=y+yy;
		save[ache][2]=cc;
		ache++;
	}
	pDC->SetPixel (-x+xx,y+yy,c);

	cc=pDC->GetPixel(-x+xx,-y+yy);
	if(cc!=white&&sym){
		save[ache][0]=-x+xx;
		save[ache][1]=-y+yy;
		save[ache][2]=cc;
		ache++;
	}
	pDC->SetPixel (-x+xx,-y+yy,c);
	ReleaseDC(pDC);
}



void CGraphicsView::clean()
{
	CDC* pDC=GetDC();
	CRect rc;
	GetWindowRect(rc);
	int W=rc.Width(),H=rc.Height();
	pDC->FillSolidRect(0,0,W,H,RGB(255,255,255));
	ReleaseDC (pDC);
}

void CGraphicsView::SeedFill(CDC *pdc, int x, int y, int boundaryColor, int fillColor)
{
	int color;
	color = pdc->GetPixel(x,y);

	if ((color != boundaryColor) && (color != fillColor)) {
		::Sleep(1);
		pdc->SetPixel(x,y,fillColor);
		SeedFill(pdc,x,y+1,boundaryColor,fillColor);
		SeedFill(pdc,x,y-1,boundaryColor,fillColor);
		SeedFill(pdc,x-1,y,boundaryColor,fillColor);
		SeedFill(pdc,x+1,y,boundaryColor,fillColor);
	}
}

void CGraphicsView::ScanLineFill(CDC *pdc, int seedx, int seedy, int color0, int fillcolor)
{
int clr,color;
	int x,y,x0,y0,xl,xr,flag,xnextspan;
	iStack=0;
	x=seedx;
	y=seedy;
	y0=y;
	push(x,y);
	color=pdc->SetPixel(x,y,color0);
	while(iStack >0)
	{
		pop(x,y);
		clr=pdc->SetPixel(x,y,fillcolor);
		x0=x+1;
		while(pdc->GetPixel(x0,y) !=color)
		{
			pdc->SetPixelV(x0,y,fillcolor);
			x0++;
		}
		xr=x0-1;	// 最右像素
		x0=x-1;
		while(pdc->GetPixel(x0,y) !=color)
		{
			pdc->SetPixelV(x0,y,fillcolor);
			x0--;
		}
		xl=x0+1;	// 最左像素
		//
		x0=xl;
		y=y+1;
		while(x0<=xr)
		{
			flag=0;
			while(pdc->GetPixel(x0,y) !=color && 
				  pdc->GetPixel(x0,y) !=clr &&  x0<xr)
			{
				if(flag==0) flag=1;
				x0++;
			}
			if(flag==1)
			{
				if(x0==xr && pdc->GetPixel(x0,y) !=color && 
						pdc->GetPixel(x0,y) !=clr)
					push(x0,y);
				else
					push(x0-1,y);
				flag=0;
			}
			xnextspan=x0;
			while(pdc->GetPixel(x0,y) ==color || 
				  pdc->GetPixel(x0,y) ==clr &&  x0<=xr)
				  x0++;
			if(xnextspan==x0) x0++;
		}
		//
		x0=xl;
		y=y-2;
		while(x0<=xr)
		{
			flag=0;
			while(pdc->GetPixel(x0,y) !=color && 
				  pdc->GetPixel(x0,y) !=clr &&  x0<xr)
			{
				if(flag==0) flag=1;
				x0++;
			}
			if(flag==1)
			{
				if(x0==xr && pdc->GetPixel(x0,y) !=color && 
						pdc->GetPixel(x0,y) !=clr)
					push(x0,y);
				else
					push(x0-1,y);
				flag=0;
			}
			xnextspan=x0;
			while(pdc->GetPixel(x0,y) ==color || 
				  pdc->GetPixel(x0,y) ==clr &&  x0<=xr)
				  x0++;
			if(xnextspan==x0) x0++;
		}
	}	
}

void CGraphicsView::push(int x, int y)
{
if(iStack>1000)
		return;
	else
	{
		iStack++;
		stackX[iStack]=x;
		stackY[iStack]=y;
	}

}

int CGraphicsView::pop(int &x, int &y)  
{
	if(iStack<=0) return -1;
	x=stackX[iStack];
	y=stackY[iStack];
	iStack--;
	return iStack;

}

void CGraphicsView::DrawGrid(CDC *pDC)   //画出网格，模拟像素点
{
	VPixel[0][0].x=RectGrid.left+VPSize/2;  //正方形像素中心坐标
	VPixel[0][0].y=RectGrid.top+VPSize/2;  //正方形像素中心坐标
    int i,j;
	for(i=0;i<40;i++)
	{
		for(j=0;j<30;j++)
		{
			VPixel[i][j].x=VPixel[0][0].x+VPSize*i;
			VPixel[i][j].y=VPixel[0][0].y+VPSize*j;
			pDC->Rectangle(&CRect(int(VPixel[i][j].x-VPSize/2),
								int(VPixel[i][j].y-VPSize/2),
								int(VPixel[i][j].x+VPSize/2),
								int(VPixel[i][j].y+VPSize/2)
				));
		}
	}
}
  
void CGraphicsView::FillVPixel(CDC *pDC, CPoint point, COLORREF color)  //将一个坐标的像素点填满，涂色
{
	int xGridStart=0,yGridStart=0;  //网格左上角坐标
	int xGridEnd=30,yGridEnd=30;    //网格右下角坐标
	BYTE r = GetRValue(color);
	BYTE g = GetGValue(color);
	BYTE b = GetBValue(color);
	if(xGridStart<=point.x&&xGridEnd>point.x&&
		yGridStart<=point.y&&yGridEnd>point.y)  //越界判断
	{
		int i=int(point.x),j=int(point.y);
		CBrush NewBrush,*pOldBrush;
		NewBrush.CreateSolidBrush(RGB(r,g,b));
		pOldBrush=pDC->SelectObject(&NewBrush);
		pDC->Rectangle(&CRect(int(VPixel[i][j].x-VPSize/2),
								int(VPixel[i][j].y-VPSize/2),
								int(VPixel[i][j].x+VPSize/2),
								int(VPixel[i][j].y+VPSize/2)
				));
		pDC->SelectObject(pOldBrush);
		NewBrush.DeleteObject();
	}
}

void CGraphicsView::Onshengcheng() 
{
	// TODO: Add your command handler code here
	WinExec( "drawgridtese01.exe ",SW_HIDE);
	
}

void CGraphicsView::Ontwodimbianhuan() 
{
	// TODO: Add your command handler code here
	WinExec( "case9.exe ",SW_HIDE);
	
}

void CGraphicsView::Onyouxiaobianbiao() 
{
	// TODO: Add your command handler code here
	WinExec( "填充算法\\有效边表填充.exe ",SW_HIDE);
	
}

void CGraphicsView::Onbianyuantianchong() 
{
	// TODO: Add your command handler code here
	WinExec( "填充算法\\边缘填充算法.exe ",SW_HIDE);
	
}

void CGraphicsView::Onfourlinjieseeds() 
{
	// TODO: Add your command handler code here
	WinExec( "填充算法\\区域四邻接种子填充.exe ",SW_HIDE);
	
}

void CGraphicsView::Onsoamiaoxianseed() 
{
	// TODO: Add your command handler code here
	WinExec( "填充算法\\扫描线种子填充.exe ",SW_HIDE);
	
}

void CGraphicsView::Onsanshitu() 
{
	// TODO: Add your command handler code here
	WinExec( "三维变换.exe ",SW_HIDE);
	
}

void CGraphicsView::Ontoushi() 
{
	// TODO: Add your command handler code here

	WinExec( "透视投影.exe ",SW_HIDE);
}
