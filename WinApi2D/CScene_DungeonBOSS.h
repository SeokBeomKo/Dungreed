#pragma once
#include "CScene.h"

struct RoundBoss
{
	bool m_bClear;

	int m_ICheckRound;

	bool m_bRound01;
};

class CScene_DungeonBOSS :
    public CScene
{
private:

	RoundBoss m_Round;

public:
	CScene_DungeonBOSS();
	virtual ~CScene_DungeonBOSS();

	virtual void update();

	virtual void Enter();
	virtual void Exit();

	void RoundMaster();
	void Round01();

	void SettingDoor();
};

