#pragma once
#include "CState.h"
class CIdleStateB :
    public CState
{
public:
	CIdleStateB(STATE_MON state);
	virtual ~CIdleStateB();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

