#include "framework.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CPlayerAttack.h"

#include "CMonster.h"
#include "CMonsterFX.h"

#include "AI.h"

// 플라이몹 스테이트
#include "CIdleStateF.h"
#include "CTraceStateF.h"
#include "CAwayStateF.h"

// 그라운드몹 스테이트
#include "CIdleStateG.h"
#include "CTraceStateG.h"

// 보스몹 스테이트
#include "CIdleStateB.h"



CMonster::CMonster()
{
	m_tInfo.fSpeed			= 0.f;
	m_tInfo.fHP				= 0.f;
	m_tInfo.fRecogRange		= 0.f;
	m_tInfo.fAttRange		= 0.f;
	m_tInfo.fAtt			= 0.f;

	m_pAI		= nullptr;
	m_pImg		= nullptr;
	pFX			= new CMonsterFX;

	SetName(L"Monster");
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
	case MON_TYPE::BAT:
	{
		pMon = new CMonster;
		pMon->SetResource(MON_TYPE::BAT);
		pMon->SetPos(pos);
		pMon->Spawn();

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 10.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleStateF(STATE_MON::IDLE));
		pAI->AddState(new CTraceStateF(STATE_MON::TRACE));
		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::BAT_RED:
		break;

	case MON_TYPE::BOSS:
	{
		pMon = new CMonster;
		pMon->SetResource(MON_TYPE::BOSS);
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 1000.f;
		info.fHP = 100.f;
		info.fSpeed = 0.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleStateB(STATE_MON::IDLE));
		// pAI->AddState(new CTraceStateF(STATE_MON::ATTACK));
		pAI->SetCurState(STATE_MON::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
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

void CMonster::Spawn()
{
	pFX->PlayFX(this, L"Spawn");
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

void CMonster::SetResource(MON_TYPE type)
{
	switch (type)
	{
	case MON_TYPE::BAT:
	{
		CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Bat", L"texture\\monster\\Bat.png");
		SetScale(fPoint(31.f * 4.f, 19.f * 4.f));

		CreateCollider();
		GetCollider()->SetScale(GetScale() - fPoint(20.f, 20.f));

		CreateAnimator();
		GetAnimator()->CreateAnimation(L"Bat", m_pImg, fPoint(0.f, 0.f), fPoint(31.f, 19.f), fPoint(31.f, 0.f), 0.08f, 6);
		GetAnimator()->Play(L"Bat");
	}
	break;
	case MON_TYPE::BAT_RED:
		break;
	case MON_TYPE::BOSS:
	{
		CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SkellBossIdle", L"texture\\monster\\SkellBossIdle.png");
		SetScale(fPoint(71.f * 4.f, 97.f * 4.f));

		CreateCollider();
		GetCollider()->SetScale(GetScale() - fPoint(64.f, 64.f));
		GetCollider()->SetOffsetPos(fPoint(32.f, 32.f));

		CreateAnimator();
		GetAnimator()->CreateAnimation(L"SkellBossIdle", m_pImg, fPoint(0.f, 0.f), fPoint(71.f, 97.f), fPoint(71.f, 0.f), 0.08f, 10);
		GetAnimator()->Play(L"SkellBossIdle");
	}
	default:
		break;
	}
	
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetObjGroup() == GROUP_GAMEOBJ::PLAYER_ATTACK)
	{
		CPlayerAttack* pAttack = (CPlayerAttack*)pOther->GetObj();
		m_tInfo.fHP -= pAttack->GetDamage();
		CSoundManager::getInst()->Play(L"MonsterHit");
		if (m_tInfo.fHP <= 0)
		{
			pFX->PlayFX(this, L"Die");
			DeleteObj(this);
		}
			
	}
}