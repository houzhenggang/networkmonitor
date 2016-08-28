// FloatWnd.cpp : implementation file
//

//#include "stdafx.h"

#include "FloatWnd.h"
 

// ������
int IniGetInt(  char *strFile, char *lpAppName, char *lpKeyName )
{
	char inBuf[255];
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //��
	if(ret==0){
		//MessageBox(0,"ini��intʧ��!","",0);
		return -1;
	}else{
		ret=atoi(inBuf);
		return ret;
	}

}

CString IniGetString(  char *strFile, char *lpAppName, char *lpKeyName )
{
	CString str;

	char inBuf[255];
	DWORD ret=GetPrivateProfileString (lpAppName,lpKeyName, NULL, inBuf, 255, strFile);  //��
	if(ret==0)
	{
		//MessageBox(0,"ini��intʧ��!","",0);
	}else{
		str=inBuf; 
	}

	return str;
}
void GetBITMAPInfo(HBITMAP h,int& width,int& height)
{
	BITMAP bitmap ;
	::GetObject (h, sizeof (BITMAP), &bitmap) ;
	width=bitmap.bmWidth;
	height=bitmap.bmHeight;
}

void GetBITMAPInfo2(HBITMAP h,int& width,int& height)
{
	CBitmap b;
	b.Attach(h);
	BITMAP bmp;
	b.GetBitmap(&bmp);

	width = bmp.bmWidth;
	height = bmp.bmHeight;
}

void GetBITMAPInfo(CBitmap b,int& width,int& height)
{
	BITMAP bmp;
	b.GetBitmap(&bmp);
	width = bmp.bmWidth;
	height = bmp.bmHeight;
}
 


/////////////////////////////////////////////////////////////////////////////
// CFloatWnd dialog


CFloatWnd::CFloatWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CFloatWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFloatWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	AfxMessageBox("c");
	Create(CFloatWnd::IDD,pParent);
	ShowWindow(SW_SHOW);


	OnUpdateTransparent(255);

}


void CFloatWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFloatWnd)
	//DDX_Control(pDX, IDC_LOGO, m_Logo);
	//}}AFX_DATA_MAP
//	DDX_Control(pDX, IDC_CloseBtn, m_CloseBtnPicCtrl);
}


BEGIN_MESSAGE_MAP(CFloatWnd, CDialog)
	//{{AFX_MSG_MAP(CFloatWnd)	
	ON_WM_PAINT()
 
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_32776, On32776)
	ON_COMMAND(ID_SELECT, OnShow)
	ON_WM_NCLBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
	 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd message handlers

BOOL CFloatWnd::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message) 
	{ 
	case WM_LBUTTONDOWN: 
	case WM_LBUTTONUP: 
	case WM_MOUSEMOVE: 
		m_openToolTip.RelayEvent(pMsg); 
	} 

	return CDialog::PreTranslateMessage(pMsg);
} 

 

#include "../NetStat.h"

char FilePath[255]=".\\config.ini"; 
extern CNetStat cnet;
BOOL CFloatWnd::OnInitDialog() 
{
	CDialog::OnInitDialog();
 
	m_openToolTip.Create(this);  
	m_openToolTip.AddTool( this , "" ); 
	m_openToolTip.SetDelayTime(200); 
	m_openToolTip.SetTipTextColor( RGB(0,0,255) ); 
	m_openToolTip.SetTipBkColor( RGB(255,255,255)); 
	m_openToolTip.Activate(TRUE); 
	m_openToolTip.SetMaxTipWidth(250);  

	 

	SetMsg("��ʼ����...");//ǧǧ����

	// TODO: Add extra initialization here
	
	//�����ļ���ָ������index
	int AdapterIndex=IniGetInt(FilePath,"network","AdapterIndex");
	//˵��û�����ļ���.
	if (AdapterIndex==-1)
	{
		//ɶҲ����..
	}else{
		cnet.SetAdapterIndex(AdapterIndex);
	}



	//�����ļ�������xy
	int last_x=IniGetInt(FilePath,"window","pos_x");
	int last_y=IniGetInt(FilePath,"window","pos_y");
	 
	
	CString bgimg=IniGetString(FilePath,"window","bkimg");


	//����ı���ͼ
	HBITMAP hBitmap;// = m_Logo.GetBitmap();
	//����ָ��bmp,ʹ��bmpĬ�Ͽ��
	hBitmap = (HBITMAP)::LoadImage(NULL,bgimg,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE);
	if(hBitmap==NULL)
	{
		//AfxMessageBox("er");
		//�������ļ�����ʧ��,��exe��Ĭ����Դ����
		hBitmap  = ::LoadBitmap (::GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1)) ;;// m_Logo.GetBitmap();
	}

	m_Bitmap.Attach(hBitmap);
	  
	GetBITMAPInfo(m_Bitmap,width,height);

 
	//�����ƶ�xy������
	MoveWindow(last_x,last_y, width,  height );
	//static�ؼ��ƶ�������
	//m_Logo.MoveWindow(last_x,last_y, width , height);

	//�������ļ�.���Ծ;��а�
	if (last_x==-1 && last_y==-1 )
	{
		CenterWindow();
	}
	 
	//top������
	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

  
	
	//����WS_EX_LAYERED��չ����
	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	
	//��Ҫ��gdi����
	CreateFont();
 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//ʵ��������������������
UINT CFloatWnd::OnNcHitTest(CPoint pt)
{
	UINT nHitTest = CDialog::OnNcHitTest(pt);


	//�����x�رհ�ť����
	//if (mouseOnCloseBtnRect())
	//{
	//	return nHitTest;
	//}


	//HTCLIENT  ��ʾ�ͻ����������,�����hack����������������������¼������޸ĳɵ�����������¼�,�Ӷ�ʵ����������,����һ������¼�����Ҫ����������
	if (nHitTest == HTCLIENT &&
				::GetAsyncKeyState(MK_LBUTTON) < 0) // ������������£�GetAsyncKeyState�����ķ���ֵС��0

		nHitTest = HTCAPTION;

	return nHitTest;
}


void CFloatWnd::OnOK()
{
	// TODO: Add extra cleanup here

	//OnOK();
}

void CFloatWnd::OnCancel() 
{
	// TODO: Add extra cleanup here

	//	CDialog::OnCancel();
}

//�Ҽ�����.�����˵�
void CFloatWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu m_Right;
	m_Right.LoadMenu(IDR_MENU1);
	CMenu *pSub = m_Right.GetSubMenu(0);

	ClientToScreen(&point);
	pSub->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this,NULL);
	
	CDialog::OnRButtonUp(nFlags, point);
}

//�˳��˵�
void CFloatWnd::OnExit() 
{

	CRect rect;
	this->GetWindowRect(&rect);	//�õ���������
	CString msg;


	msg.Format("%d",rect.left);
	WritePrivateProfileString ("window","pos_x", msg  ,  FilePath); 
	
	msg.Format("%d",rect.top);
	WritePrivateProfileString ("window","pos_y", msg ,  FilePath); 


	msg.Format("%d", cnet.GetCurrAdapterIndex() );
	WritePrivateProfileString ("network","AdapterIndex", msg ,  FilePath); 


	// TODO: Add your command handler code here
	//֪ͨ�������˳�
	CWnd *pParent = GetParent();
	ASSERT(pParent);

	pParent->PostMessage(WM_QUIT,0,0);
}

#include "../NetWorkAdapterSetDlg.h"
#include ".\floatwnd.h"
void CFloatWnd::OnShow() 
{
	CNetWorkAdapterSetDlg dlg;
	dlg.DoModal();

}

//0-255
void CFloatWnd::OnUpdateTransparent(int iTransparent)
{
 
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	if(hInst)
	{
		typedef BOOL (WINAPI *SLWA)(HWND,COLORREF,BYTE,DWORD);
		SLWA pFun = NULL;
		//ȡ��SetLayeredWindowAttributes����ָ�� 
		pFun = (SLWA)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if(pFun)
		{
			//SetLayeredWindowAttributes( RGB(255,0,255),iTransparent,ULW_COLORKEY|LWA_ALPHA);//LWA_ALPHA
			//RGB(255,0,255)
					
			pFun(m_hWnd,RGB(255,0,255),iTransparent,1|2);//ULW_COLORKEY 1��ʾҪ��͸��ɫ��ָ��ɫ����ʾ,LWA_ALPHA 2��ʾҪ���ư�͸��
		}
		FreeLibrary(hInst); 
	}
}

void CFloatWnd::OnNcLButtonDblClk(UINT nFlags, CPoint point) 
{
 
	// TODO: Add your message handler code here and/or call default	
	//CWnd *pParent = GetParent();
	//ASSERT(pParent);
 //
	//if(!pParent->IsWindowVisible())
	//{
 // 
	////	pParent->ShowWindow(SW_SHOW);
	////	pParent->SetForegroundWindow();
	//}else{
	//	pParent->ShowWindow(SW_HIDE);
	//	 
	//}
	// 

	CDialog::OnNcLButtonDblClk(nFlags, point);
}

void CFloatWnd::CreateFont()
{
	/** �������� */
	m_hFont = ::CreateFont(12,   /**< ����߶� */
		0,						/**< ������ */
		0,						/**< �������ת�Ƕ�  */
		0,						/**< ������ߵ���ת�Ƕ� */
		FW_NORMAL,				/**< ��������� */
		FALSE,					/**< �Ƿ�ʹ��б�� */
		FALSE,					/**< �Ƿ�ʹ���»��� */
		FALSE,					/**< �Ƿ�ʹ��ɾ���� */
		GB2312_CHARSET,			/**< �����ַ��� */
		OUT_TT_PRECIS,			/**< ������� */
		CLIP_DEFAULT_PRECIS,	/**< �ü����� */
		ANTIALIASED_QUALITY,	/**< ������� */
		FF_DONTCARE|DEFAULT_PITCH,		/**< Family And Pitch */
		"����");				/**< �������� */

}

//��begin��end֮�����صĺ���
float RandNum(float  begin,float end,float vlaue)
{
	static float yrot=begin;
	static bool a=true;
	if(a==true)  yrot+=vlaue;
	if(a==false) yrot-=vlaue;
	if(yrot>=end) 
	{
		a=false;
	}
	else if(yrot<=begin)
	{
		a=true;
	}
	printf("%3.1f\r",yrot);
	return yrot;
} 


void TextOutToHDC(HDC hdc,int x,int y,char* msg,HFONT m_hFont , COLORREF fontColor)
{
	//�ڴ�dcѡ��λͼ
	HGDIOBJ h=SelectObject(hdc,m_hFont);

	SetBkColor(hdc, RGB(0,0,0));//��ɫ����
	SetTextColor(hdc, fontColor );      /**< ������ɫ */

	//SetBkMode(hdc, OPAQUE);                     /**< �õ�ǰ�ı�����ɫ��䱳�� */
	SetBkMode(hdc,TRANSPARENT);

	TextOut(hdc,x, y, msg, strlen(msg));	   /**< ������ֵ��ݴ�hDC */

	SelectObject(hdc,h);

}

/*
void TextOutToHDC(HDC hdc,int x,int y,char* msg,HFONT m_hFont , COLORREF fontColor)
{
	//���������豸���ڴ�dc	
	HDC hdcMem  = CreateCompatibleDC (0) ;

	//�ڴ�dcѡ��λͼ
	SelectObject(hdcMem,m_hFont);

	SIZE size;
	// ��ȡ�ַ�λͼ��С 
	::GetTextExtentPoint32(hdcMem, msg, strlen(msg), &size);

	HBITMAP hBitmap = CreateCompatibleBitmap(hdcMem,size.cx, size.cy);

	HGDIOBJ hOldBmp=SelectObject(hdcMem,hBitmap);

	SetBkColor(hdcMem, RGB(0,0,0));//��ɫ����
	SetTextColor(hdcMem, fontColor );      //������ɫ 

	SetBkMode(hdcMem, OPAQUE);                     //�õ�ǰ�ı�����ɫ��䱳��
	//SetBkMode(hdcMem,TRANSPARENT);

	TextOut(hdcMem,x, y, msg, strlen(msg));	  // ������ֵ��ݴ�hDC 

	//�ָ�ԭ�����ڴ�dc�豸
	hBitmap = (HBITMAP)SelectObject(hdcMem, hOldBmp);

	//�ڴ�dcѡ��λͼ
	SelectObject(hdcMem,hBitmap);
	BitBlt(hdc, x, y,
		size.cx,size.cy,  //bmp���
		hdcMem, 0,0,  //hdcMem��xy,������������ϽǸ���ͼƬ���ڴ�dc
		SRCCOPY); //����Ļͼ��copy



	//ɾ���ڴ�dc
	DeleteDC(hdcMem);


	DeleteObject(hBitmap);
}
*/


HBITMAP TextOutToBMP(int x,int y,char* msg,HFONT m_hFont , COLORREF fontColor )
{
	//���������豸���ڴ�dc	
	HDC hdcMem  = CreateCompatibleDC (0) ;

	//�ڴ�dcѡ��λͼ
	 SelectObject(hdcMem,m_hFont);

	SIZE size;
	/** ��ȡ�ַ�λͼ��С */
	::GetTextExtentPoint32(hdcMem, msg, strlen(msg), &size);
	
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcMem,size.cx, size.cy);

	HGDIOBJ hOldBmp=SelectObject(hdcMem,hBitmap);
	
	SetBkColor(hdcMem, RGB(0,0,0));//��ɫ����
	SetTextColor(hdcMem, fontColor );      /**< ������ɫ */

	SetBkMode(hdcMem, OPAQUE);                     /**< �õ�ǰ�ı�����ɫ��䱳�� */
	SetBkMode(hdcMem,TRANSPARENT);

	TextOut(hdcMem,x, y, msg, strlen(msg));	   /**< ������ֵ��ݴ�hDC */

	//�ָ�ԭ�����ڴ�dc�豸
	hBitmap = (HBITMAP)SelectObject(hdcMem, hOldBmp);

	//ɾ���ڴ�dc
	DeleteDC(hdcMem);

	return hBitmap;
}

void CBitmapToHDC(HDC hdc,CBitmap& hbmp,int pic_x,int pic_y)
{
	int nX;  
	int nY;
	GetBITMAPInfo(hbmp,nX,nY);

	//���������豸���ڴ�dc	
	HDC hdcMem  = CreateCompatibleDC (0) ;

	//�ڴ�dcѡ��λͼ
	SelectObject(hdcMem,hbmp);

	BitBlt(hdc,
		pic_x, pic_y, //ָ��hdc���Ͻ�
		nX,nY,  //bmp���
		hdcMem, 
		0,0,  //hdcMem��xy,������������ϽǸ���ͼƬ���ڴ�dc
		SRCCOPY); //����Ļͼ��copy
	//ɾ���ڴ�dc
	DeleteDC(hdcMem);
}

BYTE r=255;
BYTE g=255;
BYTE b=255;

void CFloatWnd::Paint()
{

	int nX;  
	int nY;
	GetBITMAPInfo(m_Bitmap,nX,nY);


	HDC hdc;  //����һ���豸������handle
	hdc=::GetDC(m_hWnd);  //�õ�handle


	//���Ʊ���ͼƬ
	CBitmapToHDC(hdc,m_Bitmap,0,0);

	//g=255;//RandNum(150,250,3);
	//g=230;
	//b=255;//(abs(g-50)<50?(b+5):abs(g-50)) ;

	//�����
	TextOutToHDC(hdc,
		10,  //�������x����
		nY/2/2, //�������y����
		msg,m_hFont,RGB(r,g,b));


	//SelectObject(hdc,h);
	::ReleaseDC(m_hWnd,hdc); //�ͷ�hdc
}

void CFloatWnd::OnPaint()
{
	 
	CDialog::OnPaint();
	
	Paint();

 
 
}

void CFloatWnd::SetMsg(char* d)
{
	strcpy(msg,d);
	 
	Paint();
//	Invalidate(1);
}

void CFloatWnd::SetToolTipText(char* m)
{
	m_openToolTip.UpdateTipText(m,this);
}

 
//����ڹرհ�ť����?
bool CFloatWnd::mouseOnCloseBtnRect()
{
	/*
	CRect   rect;   
	GetWindowRect(&rect);

	//�õ��������
	POINT   pt2; 
	GetCursorPos(&pt2);  //�õ����������겢������pt��

	BITMAP bmp;
	m_CloseBitmap.GetBitmap(&bmp);
	rect.left=rect.right-bmp.bmWidth;
	rect.bottom=rect.top+bmp.bmHeight;

	//�����x��ť��������?
	return rect.PtInRect(pt2);;
	*/
	return 0;
}

//����������
void CFloatWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	 ////����x�ر�
	 //if (mouseOnCloseBtnRect())
	 //{
		//// OnExit();
	 //}

	CDialog::OnLButtonUp(nFlags, point);
}

#include "../caboutdlg.h"

//��������
void CFloatWnd::On32776()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;
	dlg.DoModal();
}
