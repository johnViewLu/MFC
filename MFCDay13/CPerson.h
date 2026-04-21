#pragma once
#include <afx.h>


enum class sex { Female, Male };

class CPerson :
    public CObject
{
	DECLARE_SERIAL(CPerson)
public:
    CPerson();
   ~CPerson();

private:
    bool m_bEmployed;
    int m_iAge;
	CString m_strName;
    int m_iMaritalStatus;
    sex m_iSex;
public:
    void SetSex(sex iSex)
    {
		m_iSex = iSex;// TODO: Add your implementation code here.
    }
    void SetEmployed(BOOL bEmployed)
    {
        m_bEmployed = bEmployed;// TODO: Add your implementation code here.
    }
    BOOL IsEmployed() const
    {
        return m_bEmployed;// TODO: Add your implementation code here.
	}
    void SetAge(int iAge)
    {
        m_iAge = iAge;// TODO: Add your implementation code here.
    }
    int GetAge() const
    {
        return m_iAge;// TODO: Add your implementation code here.
    }
    void SetName(LPCTSTR lpszName)
    {
        m_strName = lpszName;// TODO: Add your implementation code here.
    }

    sex GetSex() const
    {
        return m_iSex;// TODO: Add your implementation code here.
	}

    CString GetName() const
    {
        return m_strName;// TODO: Add your implementation code here.
    }
    void SetMaritalStatus(int iMaritalStatus)
    {
        m_iMaritalStatus = iMaritalStatus;// TODO: Add your implementation code here.
    }
    int GetMaritalStatus() const
    {
        return m_iMaritalStatus;// TODO: Add your implementation code here.
	}
    virtual void Serialize(CArchive& ar);
};

