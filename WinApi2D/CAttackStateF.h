#pragma once
#include "CState.h"
class CAttackStateF :
    public CState
{
public:
	CAttackStateF(STATE_MON state);
	virtual ~CAttackStateF();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

