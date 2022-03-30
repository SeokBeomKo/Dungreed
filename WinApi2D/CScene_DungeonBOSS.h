#pragma once
#include "CScene.h"
class CScene_DungeonBOSS :
    public CScene
{
public:
	CScene_DungeonBOSS();
	virtual ~CScene_DungeonBOSS();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

