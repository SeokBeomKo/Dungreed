#include "framework.h"
#include "CScene_Dungeon01.h"
#include "CMap.h"
#include "CUICursor.h"

#include "CDoor.h"

// 오브젝트
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

// 아이템
#include "CWeapon.h"

CScene_Dungeon01::CScene_Dungeon01()
{
	m_Round.m_bClear = false;
	m_Round.m_ICheckRound = 1;
	m_Round.m_bRound01 = true;
	m_Round.m_bRound02 = false;
	m_Round.m_bRound03 = false;
}

CScene_Dungeon01::~CScene_Dungeon01()
{
}

void CScene_Dungeon01::update()
{
	CScene::update();
	RoundMaster();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::START);
	}
}

void CScene_Dungeon01::Enter()
{
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\DG01.tile";
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
	pPlayer->SetPos(fPoint(570.f, 500.f));
	pPlayer->SaveData(sPlayer->LoadData());

	// 아이템
	/*CItem* pPowerKatana= new CWeapon(L"PowerKatana", L"texture\\weapon\\PowerKatana.png");
	pPowerKatana->SetPos(fPoint(800.f, 550.f));
	AddObject(pPowerKatana, GROUP_GAMEOBJ::ITEM);

	CItem* pShort_Sword = new CWeapon(L"Short_Sword", L"texture\\weapon\\ShortSword.png");
	pShort_Sword->SetPos(fPoint(1200.f, 550.f));
	AddObject(pShort_Sword, GROUP_GAMEOBJ::ITEM);*/

	// 배경

	// 맵
	CMap* enterDG = new CMap;
	enterDG->Load(L"DG01", L"texture\\dungeon\\DG01.png");
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
	CCameraManager::getInst()->SetRange(fPoint(616.f, 320.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Dungeon01::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Duneon_bgm");
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}

void CScene_Dungeon01::RoundMaster()
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
			m_Round.m_bRound02 = true;
			m_Round.m_ICheckRound++;
		}
		break;
	case 2:
		if (m_Round.m_bRound02)
		{
			Round02();
			m_Round.m_bRound02 = false;
		}
		else if (GetObjectSize(GROUP_GAMEOBJ::MONSTER) == 0)
		{
			m_Round.m_bRound03 = true;
			m_Round.m_ICheckRound++;
		}
		break;
	case 3:
		if (m_Round.m_bRound03)
		{
			Round03();
			m_Round.m_bRound03 = false;
		}
		else if (GetObjectSize(GROUP_GAMEOBJ::MONSTER) == 0)
		{
			m_Round.m_ICheckRound++;
		}
		break;
	case 4:
		SettingDoor();
		m_Round.m_ICheckRound++;
		m_Round.m_bClear = true;
		break;
	default:
		return;
	}
	
}

void CScene_Dungeon01::Round01()
{
	CSoundManager::getInst()->Play(L"MonsterSpawn");
	CMonster* pMon = CMonster::Create(MON_TYPE::BAT, fPoint(500.f, 500.f));
	AddObject(pMon, GROUP_GAMEOBJ::MONSTER);

	CMonster* pMon2 = CMonster::Create(MON_TYPE::BAT, fPoint(550.f, 600.f));
	AddObject(pMon2, GROUP_GAMEOBJ::MONSTER);
}

void CScene_Dungeon01::Round02()
{
	CSoundManager::getInst()->Play(L"MonsterSpawn");
	CMonster* pMon3 = CMonster::Create(MON_TYPE::BAT, fPoint(1200.f, 500.f));
	AddObject(pMon3, GROUP_GAMEOBJ::MONSTER);

	CMonster* pMon4 = CMonster::Create(MON_TYPE::BAT, fPoint(1200.f, 600.f));
	AddObject(pMon4, GROUP_GAMEOBJ::MONSTER);
}

void CScene_Dungeon01::Round03()
{
	CSoundManager::getInst()->Play(L"MonsterSpawn");
	CMonster* pMon5 = CMonster::Create(MON_TYPE::BAT, fPoint(1000.f, 100.f));
	AddObject(pMon5, GROUP_GAMEOBJ::MONSTER);

	CMonster* pMon6 = CMonster::Create(MON_TYPE::BAT, fPoint(1000.f, 200.f));
	AddObject(pMon6, GROUP_GAMEOBJ::MONSTER);
}

void CScene_Dungeon01::SettingDoor()
{
	// 씬 이동
	CDoor* pNextDoorLeft = new CDoor;
	pNextDoorLeft->SetNextScene(GROUP_SCENE::DUNGEON);
	pNextDoorLeft->Setting(fPoint(16.f, 450.f), fPoint(32.f, 256.f));
	AddObject(pNextDoorLeft, GROUP_GAMEOBJ::TILE);
	CDoor* pNextDoorRight = new CDoor;
	pNextDoorRight->SetNextScene(GROUP_SCENE::DUNGEONBOSS);
	pNextDoorRight->Setting(fPoint(2415.f, 450.f), fPoint(32.f, 256.f));
	AddObject(pNextDoorRight, GROUP_GAMEOBJ::TILE);
}
