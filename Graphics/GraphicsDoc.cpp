// GraphicsDoc.cpp : implementation of the CGraphicsDoc class
// Download by http://www.codefans.net

#include "stdafx.h"
#include "Graphics.h"

#include "GraphicsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc

IMPLEMENT_DYNCREATE(CGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphicsDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphicsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc construction/destruction

CGraphicsDoc::CGraphicsDoc()
{
	// TODO: add one-time construction code here

}

CGraphicsDoc::~CGraphicsDoc()
{
}

BOOL CGraphicsDoc::OnNewDocument()
{
	SetTitle(_T("hello"));
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	SetTitle(_T("���Ա���"));

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc serialization

void CGraphicsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc diagnostics

#ifdef _DEBUG
void CGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicsDoc commands

void CGraphicsDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle(_T("hello"));
}
