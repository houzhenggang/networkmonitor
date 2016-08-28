#pragma once 

//#include "../stdafx.h"


#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����

#include <afxdtctl.h>		// Internet Explorer 4 �����ؼ��� MFC ֧��
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows �����ؼ��� MFC ֧��
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "../resource.h"

/************************************************************************/
/* 

  ��͸������

*/
/************************************************************************/

// ������
int IniGetInt(  char *strFile, char *lpAppName, char *lpKeyName );
CString IniGetString(  char *strFile, char *lpAppName, char *lpKeyName );

void GetBITMAPInfo(HBITMAP h,int& width,int& height);
void GetBITMAPInfo2(HBITMAP h,int& width,int& height);
void GetBITMAPInfo(CBitmap b,int& width,int& height);

class CFloatWnd : public CDialog
{
// Construction
public:
	CFloatWnd(CWnd* pParent = NULL);   // standard constructor

private:

// Dialog Data
	//{{AFX_DATA(CFloatWnd)
	enum { IDD = IDD_FLOATDLG1 };
 
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloatWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBitmap m_Bitmap;
	int width;
	int height;
	
	BOOL PreTranslateMessage(MSG* pMsg);
	CToolTipCtrl m_openToolTip; 

	HFONT m_hFont;
	void CreateFont();
	void Paint();

	virtual void OnPaint();

	// Generated message map functions
	//{{AFX_MSG(CFloatWnd)
	virtual BOOL OnInitDialog();
 
	afx_msg UINT OnNcHitTest(CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnExit();
	afx_msg void OnShow();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnNcLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//����ڹرհ�ť����?
	bool mouseOnCloseBtnRect();
	char msg[200];

	CStatic m_CloseBtnPicCtrl;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
 

	void OnUpdateTransparent(int iTransparent);

	void SetMsg(char* d);

	void SetToolTipText(char* );
	afx_msg void On32776();
};
 