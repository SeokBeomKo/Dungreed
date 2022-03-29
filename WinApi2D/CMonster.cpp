#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CPlayerAttack.h"

CMonster::CMonster()
{
	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Bat", L"texture\\monster\\Bat.png");

	m_pAI = nullptr;

	SetName(L"Monster");
	SetScale(fPoint(31.f * 4.f, 19.f * 4.f));

	CreateCollider();
	GetCollider()->SetScale(GetScale() - fPoint(20.f,20.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Bat", m_pImg, fPoint(0.f, 0.f), fPoint(31.f, 19.f), fPoint(31.f, 0.f), 0.1f, 6);
	GetAnimator()->Play(L"Bat");
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CMonster* CMonster::Clone()
{
	CMonster* newMonster = new CMonster;
	if (nullptr != m_pAI)
	{
		newMonster->m_pAI = new AI;
	}
	return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
	CMonster* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(STATE_MON::IDLE));
		pAI->AddState(new CTraceState(STATE_MON::TRACE));
		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();
}

void CMonster::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();

}

float CMonster::GetSpeed()
{
	return m_tInfo.fSpeed;
}

const tMonInfo& CMonster::GetMonInfo()
{
	return m_tInfo;
}

void CMonster::SetSpeed(float speed)
{
	m_tInfo.fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetObjGroup() == GROUP_GAMEOBJ::PLAYER_ATTACK)
	{
		CPlayerAttack* pAttack = (CPlayerAttack*)pOther->GetObj();
		m_tInfo.fHP -= 10.f;
		if (m_tInfo.fHP <= 0)
			DeleteObj(this);
	}
}