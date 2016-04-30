
#include "stdafx.h"
#include "Graphics.h"
#include "Matrix2.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Matrix2::Matrix2 (int a, int b, int c){
	m=4;
	n=1;
	matrix[0][0]=a;
	matrix[1][0]=b;
	matrix[2][0]=c;
	matrix[3][0]=1;

} 

Matrix2::~Matrix2()
{

}

Matrix2::Matrix2 (int tx, int ty, int tz, bool s){     //��άƽ����
	int i,j;
	m=4;
	n=4;
	for (i=0;i<4;i++)
		for (j=0;j<3;j++){
			if (i==j)
				matrix[i][j]=1.0;
			else 
				matrix[i][j]=0.0;
		}
	matrix[0][3]=tx;
	matrix[1][3]=ty;
	matrix[2][3]=tz;
	matrix[3][3]=1.0;
}

Matrix2::Matrix2 (float sx, float sy, float sz){ //��ά������
	int i,j;
	m=4;
	n=4;
	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
				matrix[i][j]=0.0;
	matrix[0][0]=sx;
	matrix[1][1]=sy;
	matrix[2][2]=sz;
	matrix[3][3]=1.0;
}

Matrix2::Matrix2 (int flag, float r){      //��ά��ת��
	int i,j;
	m=4;
	n=4;
	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
				matrix[i][j]=0.0;
	if (flag == 1){	
		matrix[0][0]=1.0;
		matrix[1][1]=cos( r );
		matrix[2][1]=sin( r );
		matrix[1][2]=-matrix[2][1];
		matrix[2][2]=matrix[1][1];
		matrix[3][3]=1.0;	
	}
	else if (flag == 2){
		matrix[1][1]=1.0;
		matrix[0][0]=cos( r );
		matrix[0][2]=sin( r );
		matrix[2][0]=-matrix[0][2];
		matrix[2][2]=matrix[0][0];
		matrix[3][3]=1.0;	
	}
	else {
		matrix[2][2]=1.0;
		matrix[0][0]=cos( r );
		matrix[1][0]=sin( r );
		matrix[0][1]=-matrix[1][0];
		matrix[1][1]=matrix[0][0];
		matrix[3][3]=1.0;	
	}
}

Matrix2::Matrix2 ( int d){//͸��ͶӰ�任����,ͶӰƽ��n=0,ͶӰ�ο���Ϊ(0, 0, d)
	int i,j;
	m=4;
	n=4;
	for (i=0;i<4;i++)
		for (j=0;j<4;j++){
			if (i==j)
				matrix[i][j]=1.0;
			else 
				matrix[i][j]=0.0;
		}
	matrix[2][2]=0.0;
	matrix[3][2]=-1.0/d;
}

Matrix2  Matrix2::operator * (Matrix2 &c){//����"*"������
		Matrix2 temp(0,0,0,true);
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
