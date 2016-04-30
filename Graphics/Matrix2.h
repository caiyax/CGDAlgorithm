
#if !defined(AFX_MATRIX2_H__A6A02735_4473_49FE_AC2B_66DF5D114FCE__INCLUDED_)
#define AFX_MATRIX2_H__A6A02735_4473_49FE_AC2B_66DF5D114FCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Matrix2   //三维变换矩阵类 
{
friend class CMyView;
public:
	Matrix2 (int, int, int);  //三维点阵
	virtual ~Matrix2();

	Matrix2 (int, int, int, bool);  //三维平移阵
	Matrix2 (float, float, float);	//三维放缩阵
	Matrix2 (int, float);			//三维旋转阵
	Matrix2 (int);				//透视投影变换矩阵,投影平面为z=0

	int getx () { return int( matrix[0][0]/matrix[3][0] ); } //返回投影后的屏幕坐标
	int gety () { return int( matrix[1][0]/matrix[3][0] ); }
	int getz () { return int( matrix[2][0]/matrix[3][0] ); }
	double getr () { return  matrix[3][0]; } //得到齐次坐标的"第四维",在投影时要用到
	Matrix2  operator * ( Matrix2& );	 //重载"*"操作符
private:
	int m,n; //维数
	double matrix[4][4];

};

#endif // !defined(AFX_MATRIX2_H__A6A02735_4473_49FE_AC2B_66DF5D114FCE__INCLUDED_)
