; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGraphicsView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Graphics.h"
LastPage=0

ClassCount=7
Class1=CGraphicsApp
Class2=CGraphicsDoc
Class3=CGraphicsView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_DIALOG1
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=Vertex_Count
Resource3=IDR_MAINFRAME
Class7=CDrawDLG
Resource4=IDD_DRAWDLG

[CLS:CGraphicsApp]
Type=0
HeaderFile=Graphics.h
ImplementationFile=Graphics.cpp
Filter=N

[CLS:CGraphicsDoc]
Type=0
HeaderFile=GraphicsDoc.h
ImplementationFile=GraphicsDoc.cpp
Filter=N

[CLS:CGraphicsView]
Type=0
HeaderFile=GraphicsView.h
ImplementationFile=GraphicsView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CGraphicsView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=touying_toushi
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Graphics.cpp
ImplementationFile=Graphics.cpp
Filter=D
LastObject=ID_APP_ABOUT
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_shengcheng
Command2=ID_DLine
Command3=ID_DrawCutWin
Command4=ID_CSLINECLIP
Command5=ID_LBLINECLIP
Command6=ID_DrawDuoBX
Command7=ID_DrawCutWin
Command8=ID_CutDuoBX
Command9=fill_youxiaobianbiao
Command10=fill_bianyuantianchong
Command11=fill_fourlinjieseeds
Command12=fill_soamiaoxianseed
Command13=ID_twodimbianhuan
Command14=ID_AODUOMIANTI
Command15=touying_toushi
Command16=touying_sanshitu
Command17=touying_zhengjiao
Command18=ID_BEZIER
Command19=ID_BEZIER_MOVE
Command20=ID_BEZIER_CLEAR
Command21=ID_COLOR
Command22=ID_CLEAR
Command23=ID_APP_ABOUT
CommandCount=23

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=Vertex_Count
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:Vertex_Count]
Type=0
HeaderFile=Vertex_Count.h
ImplementationFile=Vertex_Count.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[DLG:IDD_DRAWDLG]
Type=1
Class=CDrawDLG
ControlCount=30
Control1=IDOK,button,1342242817
Control2=IDC_DRAW,static,1342308352
Control3=IDC_SCROLLBAR5,scrollbar,1342177280
Control4=IDC_SCROLLBAR4,scrollbar,1342177280
Control5=IDC_STATIC,button,1342177287
Control6=IDC_BUTTON8,button,1342242816
Control7=IDC_BUTTON6,button,1342242816
Control8=IDC_BUTTON7,button,1342242816
Control9=IDC_BUTTON5,button,1342242816
Control10=IDC_SCROLLBAR1,scrollbar,1342177280
Control11=IDC_SCROLLBAR2,scrollbar,1342177280
Control12=IDC_SCROLLBAR3,scrollbar,1342177280
Control13=IDC_BUTTON1,button,1342242816
Control14=IDC_BUTTON2,button,1342242816
Control15=IDC_BUTTON3,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_BUTTON4,button,1342242816
Control18=IDC_SCROLLBAR6,scrollbar,1342177280
Control19=IDC_BUTTON9,button,1342242816
Control20=IDC_STATIC,button,1342177287
Control21=IDC_BUTTON10,button,1342242816
Control22=IDC_STATIC,button,1342177287
Control23=IDC_BUTTON11,button,1342242816
Control24=IDC_BUTTON12,button,1342242816
Control25=IDC_BUTTON13,button,1342242816
Control26=IDC_BUTTON14,button,1342242816
Control27=IDC_BUTTON15,button,1342242816
Control28=IDC_BUTTON16,button,1342242816
Control29=IDC_STATIC,button,1342177287
Control30=IDC_BGColor,button,1342242816

[CLS:CDrawDLG]
Type=0
HeaderFile=DrawDLG.h
ImplementationFile=DrawDLG.cpp
BaseClass=CDialog
Filter=D
LastObject=CDrawDLG
VirtualFilter=dWC

