#pragma once
#include "CState.h"
class CIdleState : public CState
{
public:
	CIdleState(STATE_MON state);
	virtual ~CIdleState();

	virtual void update();
	virtual void Enter();
	virtual void Exit();


};
