#if !defined(AFX_VERTEX_COUNT_H__31C443A6_ADF0_4426_A70D_31F045313381__INCLUDED_)
#define AFX_VERTEX_COUNT_H__31C443A6_ADF0_4426_A70D_31F045313381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Vertex_Count.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Vertex_Count dialog

class Vertex_Count : public CDialog
{
// Construction
public:
	Vertex_Count(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Vertex_Count)
	enum { IDD = IDD_DIALOG1 };
	int		m_vertex_count;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Vertex_Count)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Vertex_Count)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERTEX_COUNT_H__31C443A6_ADF0_4426_A70D_31F045313381__INCLUDED_)
