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
#include "CShort_Sword.h"
#include "CPowerKatana.h"

CScene_Dungeon01::CScene_Dungeon01()
{
}

CScene_Dungeon01::~CScene_Dungeon01()
{
}

void CScene_Dungeon01::update()
{
	CScene::update();

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

	// 씬 이동
	CDoor* pNextDoorLeft = new CDoor;
	pNextDoorLeft->SetNextScene(GROUP_SCENE::DUNGEON);
	pNextDoorLeft->Setting(fPoint(16.f, 450.f), fPoint(32.f, 256.f));
	AddObject(pNextDoorLeft, GROUP_GAMEOBJ::TILE);
	CDoor* pNextDoorRight = new CDoor;
	pNextDoorRight->SetNextScene(GROUP_SCENE::DUNGEONBOSS);
	pNextDoorRight->Setting(fPoint(2415.f, 450.f), fPoint(32.f, 256.f));
	AddObject(pNextDoorRight, GROUP_GAMEOBJ::TILE);

	// 플레이어
	CPlayer* pPlayer = new CPlayer;
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	pPlayer->RegisterPlayer();
	pPlayer->SetPos(fPoint(570.f, 500.f));
	pPlayer->SaveData(sPlayer->LoadData());

	// 아이템
	CItem* pShort_Sword = new CShort_Sword;
	AddObject(pShort_Sword, GROUP_GAMEOBJ::ITEM);
	CItem* pPowerKatana = new CPowerKatana;
	AddObject(pPowerKatana, GROUP_GAMEOBJ::ITEM);

	// 배경

	// 맵
	CMap* enterDG = new CMap;
	enterDG->Load(L"DG01", L"texture\\dungeon\\DG01.png");
	AddObject(enterDG, GROUP_GAMEOBJ::MAP);

	// 몬스터
	CMonster* pMon =CMonster::Create(MON_TYPE::BAT, fPoint(500.f, 500.f));
	AddObject(pMon, GROUP_GAMEOBJ::MONSTER);

	CMonster* pMon2 = CMonster::Create(MON_TYPE::BAT, fPoint(550.f, 600.f));
	AddObject(pMon2, GROUP_GAMEOBJ::MONSTER);

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
