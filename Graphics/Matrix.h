#if !defined(AFX_MATRIX_H__595A2606_4663_4DB8_A017_ED861A397733__INCLUDED_)
#define AFX_MATRIX_H__595A2606_4663_4DB8_A017_ED861A397733__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Matrix  //��ά�任������ 
{
friend class CGraphicsView;       //����CGraphicsView ΪMatrix������� 
public:
	Matrix (int , int);    //��ά������
	
	Matrix (int, int, bool);     //��άƽ����
	Matrix (float, float); //��ά������
	Matrix (float);       //��ά��ת��

	int getx () { return int( matrix[0][0] ); } //�õ�x����
	int gety () { return int( matrix[1][0] ); } //�õ�y����

	virtual ~Matrix();		
	Matrix  operator * ( Matrix& );	 //����"*"������
private:
	int m,n; //ά��
	double matrix[3][3];

};

#endif // !defined(AFX_MATRIX_H__595A2606_4663_4DB8_A017_ED861A397733__INCLUDED_)
