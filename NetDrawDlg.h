/* 
===============================================================================
The MIT License


Copyright (C) 1994-2015 simawei<simawei@qq.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

===============================================================================
*/



#pragma once

#include "CurveDraw.h"

// CNetDrawDlg �Ի���
/************************************************************************/
/* 

  ��������ͼ�Ի���

*/
/************************************************************************/


class CNetDrawDlg : public CDialog
{
	DECLARE_DYNAMIC(CNetDrawDlg)

public:
	CNetDrawDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetDrawDlg();

// �Ի�������
	enum { IDD = IDD_NETDRAWDLG };

	BOOL OnInitDialog();
	void CNetDrawDlg::Draw();

	void Check();
	void CNetDrawDlg::CBitmapToHDC(HDC hdc,HBITMAP hbmp,int pic_x,int pic_y);
	BOOL PreTranslateMessage(MSG* pMsg) ;

	int height;//����100kb/s ��λ�߶�

	CCurveDraw m_download;
	CCurveDraw m_up;

	int up_R;
	int up_G;
	int up_B;
	int download_R;
	int download_G;
	int download_B;

	HBITMAP hBitmap;
	int m_width,m_height;



	DWORD in_speed;//����
	DWORD out_speed;//����
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public: 
};
