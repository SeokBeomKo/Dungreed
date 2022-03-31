#include "framework.h"
#include "CScene_DungeonBOSS.h"
#include "CMap.h"
#include "CUICursor.h"

// 오브젝트
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CDoor.h"

// 아이템
#include "CShort_Sword.h"
#include "CPowerKatana.h"

CScene_DungeonBOSS::CScene_DungeonBOSS()
{
	m_Round.m_bClear = false;
	m_Round.m_ICheckRound = 1;
	m_Round.m_bRound01 = true;
}

CScene_DungeonBOSS::~CScene_DungeonBOSS()
{
}

void CScene_DungeonBOSS::update()
{
	CScene::update();
	RoundMaster();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::START);
	}
}

void CScene_DungeonBOSS::Enter()
{
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\DGBOSS.tile";
	LoadTile(path);

	// 클리어
	if (m_Round.m_bClear)	// 클리어 했다면
	{
		SettingDoor();	// 출입구 열어줌
	}

	// 플레이어
	CPlayer* pPlayer = new CPlayer;
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	pPlayer->RegisterPlayer();
	pPlayer->SetPos(fPoint(570.f, 600.f));
	pPlayer->SaveData(sPlayer->LoadData());

	// 아이템
	CItem* pShort_Sword = new CShort_Sword;
	AddObject(pShort_Sword, GROUP_GAMEOBJ::ITEM);
	CItem* pPowerKatana = new CPowerKatana;
	AddObject(pPowerKatana, GROUP_GAMEOBJ::ITEM);

	// 배경

	// 맵
	CMap* enterDG = new CMap;
	enterDG->Load(L"DGBOSS", L"texture\\dungeon\\DGBOSS.png");
	AddObject(enterDG, GROUP_GAMEOBJ::MAP);

	// 몬스터

	CUICursor* pCursortown = new CUICursor;
	pCursortown->Load(L"ShootingCursor", L"texture\\ui\\ShootingCursor.png");
	AddObject(pCursortown, GROUP_GAMEOBJ::CURSOR);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER_ATTACK, GROUP_GAMEOBJ::MONSTER);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::TILE, GROUP_GAMEOBJ::ITEM);

	// Camera Look 
	CCameraManager::getInst()->SetRange(fPoint(352.f, 312.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_DungeonBOSS::Exit()
{
	CSoundManager::getInst()->Stop(L"BossBgm");
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}

void CScene_DungeonBOSS::RoundMaster()
{
	switch (m_Round.m_ICheckRound)
	{
	case 1:
		if (m_Round.m_bRound01)
		{
			Round01();
			m_Round.m_bRound01 = false;
		}
		else if (GetObjectSize(GROUP_GAMEOBJ::MONSTER) == 0)
		{
			m_Round.m_ICheckRound++;
		}
		break;
	case 2:
		SettingDoor();
		m_Round.m_ICheckRound++;
		m_Round.m_bClear = true;
		break;
	default:
		return;
	}
}

void CScene_DungeonBOSS::Round01()
{
	CSoundManager::getInst()->Stop(L"CScene_Duneon_bgm");
	CSoundManager::getInst()->AddSound(L"BossBgm", L"sound\\BossBgm.wav", false);
	CSoundManager::getInst()->Play(L"BossBgm");
	CSoundManager::getInst()->AddSound(L"BossEnter", L"sound\\BossEnter.wav", false);
	CSoundManager::getInst()->Play(L"BossEnter");
	CMonster* pMon = CMonster::Create(MON_TYPE::BOSS, fPoint(678.f, 595.f));
	AddObject(pMon, GROUP_GAMEOBJ::MONSTER);
}

void CScene_DungeonBOSS::SettingDoor()
{
	// 씬 이동
	CDoor* pNextDoorLeft = new CDoor;
	pNextDoorLeft->SetNextScene(GROUP_SCENE::DUNGEON01);
	pNextDoorLeft->Setting(fPoint(16.f, 966.f), fPoint(32.f, 256.f));
	AddObject(pNextDoorLeft, GROUP_GAMEOBJ::TILE);
	CDoor* pNextDoorRight = new CDoor;
	pNextDoorRight->SetNextScene(GROUP_SCENE::TOWN);
	pNextDoorRight->Setting(fPoint(1360.f, 966.f), fPoint(32.f, 256.f));
	AddObject(pNextDoorRight, GROUP_GAMEOBJ::TILE);
}
