// Myclass.h: interface for the CMyclass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCLASS_H__31B8FFA2_D8E1_46F7_95C3_941B494C670C__INCLUDED_)
#define AFX_MYCLASS_H__31B8FFA2_D8E1_46F7_95C3_941B494C670C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//typedef double array[24];

class CMyclass  
{
public:
	double Rol,Theta,Phi,DE;
	double XProj,YProj,Aux1,Aux2,Aux3,Aux4,Aux5,Aux6,Aux7,Aux8;
	double XP[30],YP[30],ZP[30],CP[30];
public:
	CMyclass();
	virtual ~CMyclass();
	void ReadCube();
	void Project(double x,double y,double z);
	void DrawPers();
	void WLineTo(double x,double y,double z,CDC *pDC,int MaxX,int MaxY);
	void WMoveTo(double x,double y,double z,CDC *pDC,int MaxX,int MaxY);
    void DrawCube();


};

#endif // !defined(AFX_MYCLASS_H__31B8FFA2_D8E1_46F7_95C3_941B494C670C__INCLUDED_)
