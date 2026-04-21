#include "pch.h"
#include "CPerson.h"
#include <iostream>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif //

IMPLEMENT_SERIAL(CPerson, CObject, 1)



CPerson::CPerson():
m_iMaritalStatus(0),
m_iAge(0),
m_bEmployed(false),
m_strName(""),
m_iSex(sex::Female)
{
};


void CPerson::Serialize(CArchive& ar)
{
	// TODO: Add your implementation code here.
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_strName;
		ar << m_iAge;
		ar << m_bEmployed;
		ar << m_iMaritalStatus;
		ar << static_cast<int>(m_iSex);
	}
	else
	{
		ar >> m_strName;
		ar >> m_iAge;
		ar >> m_bEmployed;
		ar >> m_iMaritalStatus;
		int vTemp;
		ar >> vTemp;
		m_iSex = static_cast<sex> (vTemp);
		
	}
}


CPerson::~CPerson() {
	std::cout << "CPerson destroyed\n";
}