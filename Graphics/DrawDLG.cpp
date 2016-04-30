// DrawDLG.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "Graphics.h"
#include "DrawDLG.h"
#include "math.h"

#define  DU 3.14159/180

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawDLG dialog


CDrawDLG::CDrawDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDrawDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawDLG)
	DDX_Control(pDX, IDC_SCROLLBAR3, m_scroll3);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_scroll2);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scroll1);
	DDX_Control(pDX, IDC_SCROLLBAR4, m_scroll4);
	DDX_Control(pDX, IDC_SCROLLBAR5, m_scroll5);
	DDX_Control(pDX, IDC_SCROLLBAR6, m_scroll6);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDrawDLG, CDialog)
	//{{AFX_MSG_MAP(CDrawDLG)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnColor1)
	ON_BN_CLICKED(IDC_BUTTON12, OnColor2)
	ON_BN_CLICKED(IDC_BUTTON13, OnColor3)
	ON_BN_CLICKED(IDC_BUTTON14, OnColor4)
	ON_BN_CLICKED(IDC_BUTTON15, OnColor5)
	ON_BN_CLICKED(IDC_BUTTON16, OnColor6)
	ON_BN_CLICKED(IDC_BGColor, OnBGColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDLG message handlers
void CDrawDLG::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
//	CDC *PDC=pWnd->GetDC();
	Draw();
	
}

void CDrawDLG::Draw()
{	
	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
	CDC *pDC=pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(rect);

	D v[8]={
		{-fs,-fs,fs},{-fs,fs,fs},{fs,fs,fs},{fs,-fs,fs},{-fs,-fs,-fs},{-fs,fs,-fs},{fs,fs,-fs},{fs,-fs,-fs}
	},d[8];
	
	POINT p0[4],p1[4],p2[4],p3[4],p4[4],p5[4],w[8];
	int z[8];
	
	for (int i=0; i<8; i++)
	{		

		d[i].x=v[i].x;
		d[i].y=(int)(v[i].y*cos(a*DU)-v[i].z*sin(a*DU));
		d[i].z=(int)(v[i].y*sin(a*DU)+v[i].z*cos(a*DU));

		v[i].x=(int)(d[i].x*cos(b*DU)+d[i].z*sin(b*DU));
  	    v[i].y=d[i].y;
		v[i].z=(int)(d[i].z*cos(b*DU)-d[i].x*sin(b*DU));
		
		d[i].x=(int)(v[i].x*cos(c*DU)-v[i].y*sin(c*DU));
	    d[i].y=(int)(v[i].x*sin(c*DU)+v[i].y*cos(c*DU));
		d[i].z=v[i].z;
		
		w[i].x=d[i].x+cx;
		w[i].y=d[i].y+cy;
		z[i]=d[i].z;
	}

	p0[0]=w[0];p0[1]=w[1];p0[2]=w[2];p0[3]=w[3];
	p1[0]=w[4];p1[1]=w[5];p1[2]=w[6];p1[3]=w[7];
    p2[0]=w[0];p2[1]=w[1];p2[2]=w[5];p2[3]=w[4];
	p3[0]=w[1];p3[1]=w[2];p3[2]=w[6];p3[3]=w[5];
	p4[0]=w[2];p4[1]=w[3];p4[2]=w[7];p4[3]=w[6];
	p5[0]=w[0];p5[1]=w[3];p5[2]=w[7];p5[3]=w[4];
	switch (Maxnum(z,7))
	{
		case 0:fill(p0,p2,p5,0,2,5);break;
		case 1:fill(p0,p2,p3,0,2,3);break;
		case 2:fill(p0,p3,p4,0,3,4);break;
		case 3:fill(p0,p4,p5,0,4,5);break;
		case 4:fill(p1,p2,p5,1,2,5);break;
		case 5:fill(p1,p2,p3,1,2,3);break;
		case 6:fill(p1,p3,p4,1,3,4);break;
		case 7:fill(p1,p4,p5,1,4,5);break;
	}

}

BOOL CDrawDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_scroll1.SetScrollRange(-180,180);
	m_scroll1.SetScrollPos(0);
	m_scroll2.SetScrollRange(-180,180);
	m_scroll2.SetScrollPos(0);
	m_scroll3.SetScrollRange(-180,180);
	m_scroll3.SetScrollPos(0);
	m_scroll4.SetScrollRange(0,350);
	m_scroll4.SetScrollPos(200);
	m_scroll5.SetScrollRange(0,300);
	m_scroll5.SetScrollPos(115);
	m_scroll6.SetScrollRange(0.00,300.00);
	m_scroll6.SetScrollPos(50.00);
	a=b=c=0;
	fs=50.00;
	SetTimer(1,100,NULL);	
	Ctrl=0;
	cx=200;
	cy=115;
	COLOR1=RGB(123,234,43);
	COLOR2=RGB(123,123,0);
	COLOR3=RGB(123,24,235);
	COLOR4=RGB(0,123,95);
	COLOR5=RGB(23,234,34);
	COLOR6=RGB(234,124,0);
	COLOR7=RGB(0,43,98);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDrawDLG::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int nID=pScrollBar->GetDlgCtrlID();
	switch(nID)
	{
		case IDC_SCROLLBAR1: a=pScrollBar->GetScrollPos();
						 switch (nSBCode)
						 {
							case SB_LINELEFT: a--;break;
							case SB_LINERIGHT: a++;break;
							case SB_PAGELEFT: a-=10;break;
							case SB_PAGERIGHT: a+=10;break;
							case SB_THUMBTRACK: a=nPos;break;
						 }
						 if (a<-180)a=180;
						 if (a>180)a=-180;
						 pScrollBar->SetScrollPos(a);
						 break;
		case IDC_SCROLLBAR2: b=pScrollBar->GetScrollPos();
						 switch (nSBCode)
						 {
							case SB_LINELEFT: b--;break;
							case SB_LINERIGHT: b++;break;
							case SB_PAGELEFT: b-=10;break;
							case SB_PAGERIGHT: b+=10;break;
							case SB_THUMBTRACK: b=nPos;break;
						 }
						 if (b<-180)b=180;
						 if (b>180)b=-180;
						 pScrollBar->SetScrollPos(b);
						 break;
		case IDC_SCROLLBAR3: c=pScrollBar->GetScrollPos();
						 switch (nSBCode)
						 {
							case SB_LINELEFT: c--;break;
							case SB_LINERIGHT: c++;break;
							case SB_PAGELEFT: c-=10;break;
							case SB_PAGERIGHT: c+=10;break;
							case SB_THUMBTRACK: c=nPos;break;
						 }
						 if (c<-180)c=180;
						 if (c>180)c=-180;
						 pScrollBar->SetScrollPos(c);
						 break;
		case IDC_SCROLLBAR4: cx=pScrollBar->GetScrollPos();
						 switch (nSBCode)
						 {
							case SB_LINELEFT: cx--;break;
							case SB_LINERIGHT: cx++;break;
							case SB_PAGELEFT: cx-=10;break;
							case SB_PAGERIGHT: cx+=10;break;
							case SB_THUMBTRACK: cx=nPos;break;
						 }
						 if (cx<0)cx=200;
						 if (cx>350)cx=200;
						 pScrollBar->SetScrollPos(cx);
						 break;
		case IDC_SCROLLBAR5: cy=pScrollBar->GetScrollPos();
						 switch (nSBCode)
						 {
							case SB_LINELEFT: cy--;break;
							case SB_LINERIGHT: cy++;break;
							case SB_PAGELEFT: cy-=10;break;
							case SB_PAGERIGHT: cy+=10;break;
							case SB_THUMBTRACK: cy=nPos;break;
						 }
						 if (cy<0)cy=300;
						 if (cy>300)cy=0;
						 pScrollBar->SetScrollPos(cy);
						 break;
		case IDC_SCROLLBAR6: fs=pScrollBar->GetScrollPos();
						 switch (nSBCode)
						 {
							case SB_LINELEFT: fs--;break;
							case SB_LINERIGHT: fs++;break;
							case SB_PAGELEFT: fs-=0.55;break;
							case SB_PAGERIGHT: fs+=0.55;break;
							case SB_THUMBTRACK: fs=nPos;break;
						 }
						 if (fs<0)fs=50;
						 if (fs>300)fs=50;
						 pScrollBar->SetScrollPos(fs);
						 break;
//	UpdateData(FALSE);
	}
//	Invalidate();
	Draw();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDrawDLG::OnOK() 
{
	// TODO: Add extra validation here
	KillTimer(1);	
	CDialog::OnOK();
}


int CDrawDLG::Maxnum(int *p, int n)
{
	int max=p[0];
	int x;
	for (int i=0; i<=n;i++)
	{		
		if (max<=p[i])
		{	
			max=p[i];
			x=i;
		}
	}
	return x;
}

void CDrawDLG::fill(POINT *x, POINT *y, POINT *z, int i,int j,int q)
{
	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
	CDC  *pDC=pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(rect);

	CDC dcmem;
	dcmem.CreateCompatibleDC(pDC);
	CBitmap bmp,*oldbmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	oldbmp=dcmem.SelectObject(&bmp);

	CBrush brush[6];
	brush[0].CreateSolidBrush(COLOR1);
	brush[1].CreateSolidBrush(COLOR2);
	brush[2].CreateSolidBrush(COLOR3);
	brush[3].CreateSolidBrush(COLOR4);
	brush[4].CreateSolidBrush(COLOR5);
	brush[5].CreateSolidBrush(COLOR6);

	CBrush *oldbrush=dcmem.SelectObject(&brush[i]);
	dcmem.FillSolidRect(rect,COLOR7);
	dcmem.Polygon(x,4);
	dcmem.SelectObject(&brush[j]);
	dcmem.Polygon(y,4);
	dcmem.SelectObject(&brush[q]);
	dcmem.Polygon(z,4);
	dcmem.SelectObject(oldbrush);
	for (int b=0; b<6;b++)
	brush[b].DeleteObject();
	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),
	&dcmem,0,0,SRCCOPY);
	dcmem.SelectObject(oldbmp);
	bmp.DeleteObject();
	dcmem.DeleteDC();

}

void CDrawDLG::OnButton1() 
{
	Ctrl=1;
	// TODO: Add your control notification handler code here
	
}

void CDrawDLG::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (1==Ctrl)
	{
		CScrollBar *pscrolla=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR1);
		a--;
		if (a<-180)a=180;
		pscrolla->SetScrollPos(a);
	//		Invalidate();
		Draw();
	}
	if (2==Ctrl)
	{

		CScrollBar *pscrollb=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR2);
		b--;
		if (b<-180)b=180;
		pscrollb->SetScrollPos(b);
	//		Invalidate();
		Draw();
	}
	if (3==Ctrl)
	{
		CScrollBar *pscrollc=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR3);
		c--;
		if (c<-180)c=180;
		pscrollc->SetScrollPos(c);
	//		Invalidate();
		Draw();
	}
	if (6==Ctrl)
	{
		CScrollBar *pscrollc=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR4);
		cx--;
	//		Invalidate();
		Draw();
	}
	if (8==Ctrl)
	{
		CScrollBar *pscrollc=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR5);
		cy--;
	//		Invalidate();
		Draw();
	}
	if (5==Ctrl)
	{
		CScrollBar *pscrollc=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR4);
		cx++;
	//		Invalidate();
		Draw();
	}
	if (7==Ctrl)
	{
		CScrollBar *pscrollc=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR5);
		cy++;
	//		Invalidate();
		Draw();
	}
		if (9==Ctrl)
	{
		CScrollBar *pscrollc=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR6);
		fs--;
	//		Invalidate();
		Draw();
	}
		if (10==Ctrl)
	{
		CScrollBar *pscrollc=(CScrollBar *)GetDlgItem(IDC_SCROLLBAR6);
		fs++;
	//		Invalidate();
		Draw();
	}

	CDialog::OnTimer(nIDEvent);
}

void CDrawDLG::OnButton2() 
{
	// TODO: Add your control notification handler code here
	Ctrl=2;
	
}

void CDrawDLG::OnButton3() 
{
	// TODO: Add your control notification handler code here
	Ctrl=3;
	
}

void CDrawDLG::OnButton4() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
}

void CDrawDLG::OnButton5() 
{
   Ctrl=5;
}

void CDrawDLG::OnButton6() 
{
	// TODO: Add your control notification handler code here
   Ctrl=6;	
}

void CDrawDLG::OnButton7() 
{
	Ctrl=7;
	// TODO: Add your control notification handler code here
	
}

void CDrawDLG::OnButton8() 
{
	Ctrl=8;
	// TODO: Add your control notification handler code here
	
}

void CDrawDLG::OnButton9() 
{
	// TODO: Add your control notification handler code here
    Ctrl=9;
}

void CDrawDLG::OnButton10() 
{
	// TODO: Add your control notification handler code here
    Ctrl=10;
}

void CDrawDLG::OnColor1() 
{
	// TODO: Add your control notification handler code here
		DColor.DoModal();
	COLOR1=DColor.GetColor( );	
}

void CDrawDLG::OnColor2() 
{
	// TODO: Add your control notification handler code here
		DColor.DoModal();
	COLOR2=DColor.GetColor( );
}

void CDrawDLG::OnColor3() 
{
	// TODO: Add your control notification handler code here
		DColor.DoModal();
	COLOR3=DColor.GetColor( );	
}

void CDrawDLG::OnColor4() 
{
	// TODO: Add your control notification handler code here
		DColor.DoModal();
	COLOR4=DColor.GetColor( );	
}

void CDrawDLG::OnColor5() 
{
	// TODO: Add your control notification handler code here
		DColor.DoModal();
	COLOR5=DColor.GetColor( );	
}

void CDrawDLG::OnColor6() 
{
	// TODO: Add your control notification handler code here
		DColor.DoModal();
	COLOR6=DColor.GetColor( );	
}

void CDrawDLG::OnBGColor() 
{
	// TODO: Add your control notification handler code here
		DColor.DoModal();
	COLOR7=DColor.GetColor( );	
}
