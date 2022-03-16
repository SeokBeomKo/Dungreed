#pragma once
#include "CScene.h"

class CScene_Town : public CScene
{
public:
	CScene_Town();
	virtual ~CScene_Town();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

