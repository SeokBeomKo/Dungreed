#pragma once
#include "CState.h"
class CTraceStateF : public CState
{
public:
	CTraceStateF(STATE_MON state);
	virtual ~CTraceStateF();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

