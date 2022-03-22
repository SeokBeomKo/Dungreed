#include "framework.h"
#include "CGravity.h"
#include "CGameObject.h"

CGravity::CGravity()
{
	m_pOwner = nullptr;
	IsGravity = true;
	m_fTimea = 0;
}

CGravity::~CGravity()
{
}

void CGravity::finalupdate()
{
	if (IsGravity)
	{
		fPoint pos = m_pOwner->GetPos();
		float m_fGravity = 2000.f;
		m_fTimea += m_fGravity * fDT;
		if (m_fTimea > 1200.f)
		{
			m_fTimea = 1200.f;
		}
		pos.y += m_fTimea * fDT;
		m_pOwner->SetPos(pos);
	}
}

void CGravity::OnOffGravity(bool set, float time)
{
	IsGravity = set;
	m_fTimea = time;
}

bool CGravity::CheckGravity()
{
	return IsGravity;
}




