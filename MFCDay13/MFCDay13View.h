
// MFCDay13View.h : interface of the CMFCDay13View class
//

#pragma once
#include "CPerson.h"

enum class  ClsMaritalStatus { eSingle = 0, eMarried, eDivorced, eWidow };


class CMFCDay13View : public CFormView
{
protected: // create from serialization only
	CMFCDay13View() noexcept;
	DECLARE_DYNCREATE(CMFCDay13View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFCDAY13_FORM };
#endif
	CMFCDay13Doc* GetDocument() const;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void NewDataSet();
	virtual ~CMFCDay13View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnEnChangeEname();
	afx_msg void OnEnChangeEage();
	void OnBfirst();
	void PopulateView();
	void OnCbemployed();
	afx_msg void OnClickedCemployed();
	afx_msg void OnClickedFirst();
	afx_msg void OnClickedPrevious();
	afx_msg void OnClickedNext();
	afx_msg void OnClickedLast();

	afx_msg void OnClickedRsingle();
	afx_msg void OnRmarried();
	afx_msg void OnRdivorced();
	afx_msg void OnRwidow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	DECLARE_MESSAGE_MAP()
private:
	
	void RadioButtonCheck(ClsMaritalStatus iMaritalStatus);

	CString m_sPosition;
	CPerson* m_pCurPerson;
	int m_iAge;
	CString m_strName;
	int m_bEmployed;
	int m_iMaritalStatus;
	int m_iSex;
public:
	afx_msg void OnClickedFemale();
	afx_msg void OnMale();
};

#ifndef _DEBUG  // debug version in MFCDay13View.cpp
inline CMFCDay13Doc* CMFCDay13View::GetDocument() const
   { return reinterpret_cast<CMFCDay13Doc*>(m_pDocument); }
#endif

