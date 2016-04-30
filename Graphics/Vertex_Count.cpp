// Vertex_Count.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "Graphics.h"
#include "Vertex_Count.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Vertex_Count dialog


Vertex_Count::Vertex_Count(CWnd* pParent /*=NULL*/)
	: CDialog(Vertex_Count::IDD, pParent)
{
	//{{AFX_DATA_INIT(Vertex_Count)
	m_vertex_count = 0;
	//}}AFX_DATA_INIT
}


void Vertex_Count::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Vertex_Count)
	DDX_Text(pDX, IDC_EDIT1, m_vertex_count);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Vertex_Count, CDialog)
	//{{AFX_MSG_MAP(Vertex_Count)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Vertex_Count message handlers

void Vertex_Count::OnCancel() 
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void Vertex_Count::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
