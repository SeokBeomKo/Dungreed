#pragma once
#include "CState.h"

class CIdleStateF : public CState
{
public:
	CIdleStateF(STATE_MON state);
	virtual ~CIdleStateF();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
