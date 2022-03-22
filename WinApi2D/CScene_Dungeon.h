#pragma once
#include "CScene.h"
class CScene_Dungeon :
    public CScene
{
public:
	CScene_Dungeon();
	virtual ~CScene_Dungeon();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

