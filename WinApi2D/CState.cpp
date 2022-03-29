#include "framework.h"
#include "CState.h"
#include "AI.h"
#include "CMonster.h"

CState::CState(STATE_MON state)
{
	m_pOwnerAI = nullptr;
	m_eState = state;
}

CState::~CState()
{
}

AI* CState::GetOwnerAI()
{
	return m_pOwnerAI;
}

STATE_MON CState::GetType()
{
	return m_eState;
}

CMonster* CState::GetMonster()
{
	return m_pOwnerAI->GetOwnerAI();
}