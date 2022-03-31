#pragma once
#include "CState.h"
class CAwayStateF :
    public CState
{
public:
	CAwayStateF(STATE_MON state);
	virtual ~CAwayStateF();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

