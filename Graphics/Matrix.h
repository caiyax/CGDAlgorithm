#if !defined(AFX_MATRIX_H__595A2606_4663_4DB8_A017_ED861A397733__INCLUDED_)
#define AFX_MATRIX_H__595A2606_4663_4DB8_A017_ED861A397733__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Matrix  //二维变换矩阵类 
{
friend class CGraphicsView;       //设置CGraphicsView 为Matrix类的友类 
public:
	Matrix (int , int);    //二维坐标阵
	
	Matrix (int, int, bool);     //二维平移阵
	Matrix (float, float); //二维放缩阵
	Matrix (float);       //二维旋转阵

	int getx () { return int( matrix[0][0] ); } //得到x坐标
	int gety () { return int( matrix[1][0] ); } //得到y坐标

	virtual ~Matrix();		
	Matrix  operator * ( Matrix& );	 //重载"*"操作符
private:
	int m,n; //维数
	double matrix[3][3];

};

#endif // !defined(AFX_MATRIX_H__595A2606_4663_4DB8_A017_ED861A397733__INCLUDED_)
