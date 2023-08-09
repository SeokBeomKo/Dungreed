#include "framework.h"
#include "CIdleStateF.h"
#include "CPlayer.h"
#include "CMonster.h"


CIdleStateF::CIdleStateF(STATE_MON state)
	: CState(state)
{
}

CIdleStateF::~CIdleStateF()
{
}

void CIdleStateF::update()
{
	CPlayer* pPlayer = CPlayer::GetPlayer();
	if (nullptr == pPlayer)
		return;

	fPoint fptPlayerPos = pPlayer->GetPos();

	CMonster* pMonster = GetMonster();
	fPoint fptMonsterPos = pMonster->GetPos();

	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	float fLen = fvDiff.Length();
	if (fLen < pMonster->GetMonInfo().fRecogRange)
	{
		ChangeAIState(GetOwnerAI(), STATE_MON::TRACE);
	}

}

void CIdleStateF::Enter()
{
}

void CIdleStateF::Exit()
{
}
