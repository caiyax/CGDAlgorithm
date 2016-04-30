#if !defined(AFX_DRAWDLG_H__39F57E19_326D_4C7A_8EC9_EDF473A27AC1__INCLUDED_)
#define AFX_DRAWDLG_H__39F57E19_326D_4C7A_8EC9_EDF473A27AC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawDLG dialog

class CDrawDLG : public CDialog
{
// Construction
public:
	int cy;
	int cx;
	void fill(POINT *x,POINT *y,POINT *z,int i,int j,int q);
	int Maxnum(int *p,int n);
//	void compare(int *p,int n);
	struct D
	{
		float x;
		float y;
		float z;
	};

	void Draw();
	int a,b,c;
	int Ctrl;
	float   fs;
	float   m_sx;
	float   m_sy;
	float   m_sz;
	int COLOR1;
	int COLOR2;
	int COLOR3;
	int COLOR4;
	int COLOR5;
	int COLOR6;
	int COLOR7;
	CColorDialog DColor;

	CDrawDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDrawDLG)
	enum { IDD = IDD_DRAWDLG };
	CScrollBar	m_scroll6;
	CScrollBar	m_scroll5;
	CScrollBar	m_scroll4;
	CScrollBar	m_scroll3;
	CScrollBar	m_scroll2;
	CScrollBar	m_scroll1;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDrawDLG)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
    afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnColor1();
	afx_msg void OnColor2();
	afx_msg void OnColor3();
	afx_msg void OnColor4();
	afx_msg void OnColor5();
	afx_msg void OnColor6();
	afx_msg void OnBGColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWDLG1_H__152B065C_268B_4EA2_965F_93FE8A1F158D__INCLUDED_)
