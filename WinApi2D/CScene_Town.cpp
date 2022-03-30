#include "framework.h"
#include "CScene_Town.h"
#include "CGameObject.h"
#include "CPlayer.h"

// BackGround
#include "Back_Ground.h"
#include "Back_Ground_Layer.h"
#include "CMap.h"
#include "CUICursor.h"

#include "CSound.h"
#include "CD2DImage.h"

#include "CDoor.h"

// 아이템
#include "CShort_Sword.h"
#include "CPowerKatana.h"

CScene_Town::CScene_Town()
{
}
CScene_Town::~CScene_Town()
{
}
void CScene_Town::update()
{
	CScene::update();
	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::START);
	}
}

void CScene_Town::Enter()
{
	CCameraManager::getInst()->FadeIn(2.f);
	CSoundManager::getInst()->AddSound(L"MonsterHit", L"sound\\MonsterHit.wav", false);
	CSoundManager::getInst()->AddSound(L"MonsterDie", L"sound\\MonsterDie.wav", false);
	CSoundManager::getInst()->AddSound(L"MonsterSpawn", L"sound\\MonsterSpawn.wav", false);

	// 브금
	CSoundManager::getInst()->AddSound(L"CScene_Town_bgm", L"sound\\0.Town.wav", false);
	CSoundManager::getInst()->Play(L"CScene_Town_bgm");

	// 맵 충돌체
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Town.tile";
	LoadTile(path);

	// 씬 이동
	CDoor* pNextDoor = new CDoor;
	pNextDoor->SetNextScene(GROUP_SCENE::DUNGEON);
	pNextDoor->Setting(fPoint(3872.f, 1360.f), fPoint(1088.f, 32.f));
	AddObject(pNextDoor, GROUP_GAMEOBJ::TILE);

	// 플레이어
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(3700.f, 650.f));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	// 아이템
	CItem* pShort_Sword = new CShort_Sword;
	pShort_Sword->SetPos(fPoint(4000.f, 600.f));
	AddObject(pShort_Sword, GROUP_GAMEOBJ::ITEM);
	CItem* pPowerKatana = new CPowerKatana;
	pPowerKatana->SetPos(fPoint(3900.f, 600.f));
	AddObject(pPowerKatana, GROUP_GAMEOBJ::ITEM);

	// 맵 이미지
	CMap* town = new CMap;
	town->Load(L"Town", L"texture\\map\\Town.png");
	AddObject(town, GROUP_GAMEOBJ::MAP);

	// 배경 이미지
	Back_Ground* skyday = new Back_Ground;
	skyday->Load(L"Sky_Day", L"texture\\background\\Sky_Day.png");
	AddObject(skyday, GROUP_GAMEOBJ::BACKGROUND);
	Back_Ground_Layer* townBG_day = new Back_Ground_Layer;
	townBG_day->Load(L"TownBG_Day", L"texture\\background\\TownBG_Day.png", fPoint(0.f,160.f), 7.f);
	AddObject(townBG_day, GROUP_GAMEOBJ::BACKGROUND);
	Back_Ground_Layer* townLayer_day = new Back_Ground_Layer;
	townLayer_day->Load(L"TownLayer_Day", L"texture\\background\\TownLayer_Day.png", fPoint(0.f,550.f), 3.f);
	AddObject(townLayer_day, GROUP_GAMEOBJ::BACKGROUND);

	// 마우스 커서 변경
	CUICursor* pCursortown = new CUICursor;
	pCursortown->Load(L"ShootingCursor", L"texture\\ui\\ShootingCursor.png");
	AddObject(pCursortown, GROUP_GAMEOBJ::CURSOR);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::TILE, GROUP_GAMEOBJ::ITEM);

	// Camera Look 
	CCameraManager::getInst()->SetRange(fPoint(1904.f, 384.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Town::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Town_bgm");


	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
