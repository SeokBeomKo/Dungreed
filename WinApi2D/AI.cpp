#include "framework.h"
#include "AI.h"
#include "CState.h"

AI::AI()
{
	m_pOwner = nullptr;
	m_pCurState = nullptr;
}

AI::~AI()
{
	for (map<STATE_MON, CState*>::iterator iter = m_mapState.begin(); iter != m_mapState.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapState.clear();
}

void AI::update()
{
	m_pCurState->update();
}

CState* AI::GetState(STATE_MON state)
{
	map<STATE_MON, CState*>::iterator iter = m_mapState.find(state);
	if (m_mapState.end() == iter)
	{
		return nullptr;
	}
	return iter->second;
}

CMonster* AI::GetOwnerAI()
{
	return m_pOwner;
}

void AI::SetCurState(STATE_MON state)
{
	m_pCurState = GetState(state);
	assert(m_pCurState);
}

void AI::AddState(CState* state)
{
	CState* pState = GetState(state->GetType());
	assert(!pState);

	m_mapState.insert(make_pair(state->GetType(), state));
	state->m_pOwnerAI = this;
}

void AI::ChangeState(STATE_MON nextState)
{
	CState* pNextState = GetState(nextState);
	assert(m_pCurState != pNextState);

	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();
}
