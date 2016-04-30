// Download by http://www.codefans.net
#include "stdafx.h"
#include "Graphics.h"
#include "Matrix.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Matrix::Matrix(int a,int b)
{
	m=3;
	n=1;
	matrix[0][0]=a;
	matrix[1][0]=b;
	matrix[2][0]=1;

}

Matrix::~Matrix()
{

}
Matrix  Matrix::operator * (Matrix &c){//重载"*"操作符
		Matrix temp(0,0,true);
		temp.m=this->m;
		temp.n=c.n;
		int i,j,k;
		for (i=0;i<this->m;i++)
			for (j=0;j<c.n;j++){
				temp.matrix[i][j]=0;
				for (k=0;k<c.m;k++)
					temp.matrix[i][j]+=(this->matrix[i][k]*c.matrix[k][j]);
			}
		return temp;
}

	
Matrix::Matrix(int tx, int ty, bool t){    //二维平移阵
	int i,j;
	m=3;
	n=3;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++){
			matrix[i][j]=0.0;
			if (i==j)
				matrix[i][j]=1.0;
		}
	matrix[0][2]=tx;
	matrix[1][2]=ty;

}
Matrix::Matrix(float sx, float sy){ //二维放缩阵
	int i,j;
	m=3;
	n=3;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++){
			matrix[i][j]=0;
		}
	matrix[0][0]=sx;
	matrix[1][1]=sy;
	matrix[2][2]=1.0;
}
Matrix::Matrix(float r){      //二维旋转阵
	int i;
	m=3;
	n=3;
	for (i=0;i<2;i++){
			matrix[i][2]=0;
			matrix[2][i]=0;
		}
	matrix[0][0]=cos( r );
	matrix[1][0]=sin( r );
	matrix[0][1]=-matrix[1][0];
	matrix[1][1]=matrix[0][0];
	matrix[2][2]=1.0;
			
}


