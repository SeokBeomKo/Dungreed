#pragma once

class CMonster;
class CState;

class AI
{
	friend class CMonster;

private:
	map<STATE_MON, CState*> m_mapState;
	CMonster* m_pOwner;
	CState* m_pCurState;

public:
	AI();
	~AI();

	CMonster* GetOwnerAI();
	CState* GetState(STATE_MON state);
	void SetCurState(STATE_MON state);

	void update();

	void AddState(CState* state);
	void ChangeState(STATE_MON nextState);

};
