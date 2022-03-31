#pragma once
#include "CScene.h"

struct Round
{
	bool m_bClear;

	int m_ICheckRound;

	bool m_bRound01;
	bool m_bRound02;
	bool m_bRound03;
};

class CScene_Dungeon01 :
	public CScene
{
private:

	Round m_Round;

public:
	CScene_Dungeon01();
	virtual ~CScene_Dungeon01();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
	
	void RoundMaster();
	void Round01();
	void Round02();
	void Round03();

	void SettingDoor();
};

