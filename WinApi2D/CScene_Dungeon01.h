#pragma once
#include "CScene.h"
class CScene_Dungeon01 :
	public CScene
{
public:
	CScene_Dungeon01();
	virtual ~CScene_Dungeon01();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

