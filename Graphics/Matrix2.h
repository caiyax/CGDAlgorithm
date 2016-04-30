
#if !defined(AFX_MATRIX2_H__A6A02735_4473_49FE_AC2B_66DF5D114FCE__INCLUDED_)
#define AFX_MATRIX2_H__A6A02735_4473_49FE_AC2B_66DF5D114FCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Matrix2   //��ά�任������ 
{
friend class CMyView;
public:
	Matrix2 (int, int, int);  //��ά����
	virtual ~Matrix2();

	Matrix2 (int, int, int, bool);  //��άƽ����
	Matrix2 (float, float, float);	//��ά������
	Matrix2 (int, float);			//��ά��ת��
	Matrix2 (int);				//͸��ͶӰ�任����,ͶӰƽ��Ϊz=0

	int getx () { return int( matrix[0][0]/matrix[3][0] ); } //����ͶӰ�����Ļ����
	int gety () { return int( matrix[1][0]/matrix[3][0] ); }
	int getz () { return int( matrix[2][0]/matrix[3][0] ); }
	double getr () { return  matrix[3][0]; } //�õ���������"����ά",��ͶӰʱҪ�õ�
	Matrix2  operator * ( Matrix2& );	 //����"*"������
private:
	int m,n; //ά��
	double matrix[4][4];

};

#endif // !defined(AFX_MATRIX2_H__A6A02735_4473_49FE_AC2B_66DF5D114FCE__INCLUDED_)
