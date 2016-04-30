// Myclass.cpp: implementation of the CMyclass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphics.h"
#include "DrawDLG.h"
#include "Myclass.h"
#include "math.h"
#define PI 3.1415926

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyclass::CMyclass()
{

}

CMyclass::~CMyclass()
{

}
void CMyclass::DrawPers()
{
	double Th,Ph;
	Th=PI*Theta/180;
	Ph=PI*Phi/180;
	Aux1=sin(Th);
	Aux2=sin(Ph);
	Aux3=cos(Th);
	Aux4=cos(Ph);
	Aux5=Aux3*Aux2;
	Aux6=Aux1*Aux2;
	Aux7=Aux3*Aux4;
	Aux8=Aux1*Aux4;
	DrawCube();
}
void CMyclass::DrawCube()
{
	CWnd *pWnd=GetDlgItem(IDC_DRAW);
	pWnd->UpdateWindow();
	CDC *pDC=pWnd->GetDC();
	CRect rr;
	pWnd->GetClientRect(rr);
	ReadCube();
	
    for(int i=1;i<4;i++)
	{
		WMoveTo(XP[i],YP[i],ZP[i],pDC,rr.right,rr.bottom);
        WLineTo(XP[i+1],YP[i+1],ZP[i+1],pDC,rr.right,rr.bottom);
        WMoveTo(XP[i+4],YP[i+4],ZP[i+4],pDC,rr.right,rr.bottom);
        WLineTo(XP[i+5],YP[i+5],ZP[i+5],pDC,rr.right,rr.bottom);
    }
    WMoveTo(XP[4],YP[4],ZP[4],pDC,rr.right,rr.bottom);
    WLineTo(XP[1],YP[1],ZP[1],pDC,rr.right,rr.bottom);
    WMoveTo(XP[8],YP[8],ZP[8],pDC,rr.right,rr.bottom);
    WLineTo(XP[5],YP[5],ZP[5],pDC,rr.right,rr.bottom);
	for(i=1;i<=4;i++)
	{
		WMoveTo(XP[i],YP[i],ZP[i],pDC,rr.right,rr.bottom);
        WLineTo(XP[i+4],YP[i+4],ZP[i+4],pDC,rr.right,rr.bottom);
	}
	
	pWnd->ReleaseDC(pDC);
}
void CMyclass::ReadCube()
{   XP[1]=1;YP[1]=1;ZP[1]=1;CP[1]=1;
    XP[2]=0;YP[2]=1;ZP[2]=1;CP[2]=1;
	XP[3]=0;YP[3]=0;ZP[3]=1;CP[3]=1;
	XP[4]=1;YP[4]=0;ZP[4]=1;CP[4]=1;
	XP[5]=1;YP[5]=1;ZP[5]=0;CP[5]=1;
	XP[6]=0;YP[6]=1;ZP[6]=0;CP[6]=1;
	XP[7]=0;YP[7]=0;ZP[7]=0;CP[7]=1;
	XP[8]=1;YP[8]=0;ZP[8]=0;CP[8]=1;
}

void CMyclass::WLineTo(double x,double y,double z,CDC *pDC,int MaxX,int MaxY)
{
	int XScreen,YScreen;
	Project(x,y,z);
    XScreen=(int)floor(0.5+XProj+MaxX/2);
	YScreen=(int)floor(0.5+MaxY/2-YProj);
	pDC->LineTo(XScreen,YScreen);
}

void CMyclass::WMoveTo(double x,double y,double z,CDC *pDC,int MaxX,int MaxY)
{
	int XScreen,YScreen;
	Project(x,y,z);
	XScreen=(int)floor(0.5+XProj+MaxX/2);
	YScreen=(int)floor(0.5+MaxY/2-YProj);
	pDC->MoveTo(XScreen,YScreen);
}

void CMyclass::Project(double x,double y,double z)
{
	double xobs,yobs,zobs;
	xobs=-x*Aux1+y*Aux3;
	yobs=-x*Aux5-y*Aux6+z*Aux4;
	zobs=-x*Aux7-y*Aux8-z*Aux2+Rol;
	XProj=DE*xobs/zobs*20;
	YProj=DE*yobs/zobs*20;
}

	
