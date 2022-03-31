#include "framework.h"
#include "CTraceStateF.h"
#include "CPlayer.h"
#include "CMonster.h"

CTraceStateF::CTraceStateF(STATE_MON state)
	: CState(state)
{
}

CTraceStateF::~CTraceStateF()
{
}

void CTraceStateF::update()
{
	CPlayer* pPlayer = CPlayer::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();
	if (fLen >= pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::IDLE);
	}

	fPoint pos = pMonster->GetPos();
	pos += fvDiff.normalize() * 100 * fDT;
	pMonster->SetPos(pos);
}

void CTraceStateF::Enter()
{
}

void CTraceStateF::Exit()
{
}
