// CMsgDlg.cpp : implementation file
//

#include "pch.h"
#include "Dialogs.h"
#include "afxdialogex.h"
#include "CMsgdlg.h"



// CMsgDlg dialog

IMPLEMENT_DYNAMIC(CMsgDlg, CDialogEx)

CMsgDlg::CMsgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MESSAGEDLG, pParent)
	, m_sMessage(_T(""))
	, m_iOption(0)
{

}

CMsgDlg::~CMsgDlg()
{
}

void CMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MESSAGE, m_sMessage);
	DDX_Radio(pDX, IDC_OPTION1, m_iOption);
}


BEGIN_MESSAGE_MAP(CMsgDlg, CDialogEx)
END_MESSAGE_MAP()


// CMsgDlg message handlers
