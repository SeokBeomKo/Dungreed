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
void StartDungeon(DWORD_PTR, DWORD_PTR)
{
	// Enter 2 번 호출.... : 타일 2개 밟으면 2번호출
	ChangeScn(GROUP_SCENE::DUNGEON);
}

void CScene_Town::Enter()
{
	CCameraManager::getInst()->FadeIn(1.f);
	// TODO : 브금
	CSoundManager::getInst()->AddSound(L"CScene_Town_bgm", L"sound\\0.Town.wav", false);
	CSoundManager::getInst()->Play(L"CScene_Town_bgm");

	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Town.tile";
	LoadTile(path);

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(3500.f, 650.f));
	pPlayer->SetSteppedCallBack(StartDungeon, 0, 0);
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	//CItem* pShort_Sword = new CShort_Sword;
	//pShort_Sword->SetPos(fPoint(3700.f, 600.f));
	//AddObject(pShort_Sword, GROUP_GAMEOBJ::ITEM);
	//CItem* pPowerKatana = new CPowerKatana;
	//pPowerKatana->SetPos(fPoint(3900.f, 600.f));
	//AddObject(pPowerKatana, GROUP_GAMEOBJ::ITEM);
	//CItem* pPowerKatana2 = new CPowerKatana;
	//pPowerKatana2->SetPos(fPoint(3300.f, 600.f));
	//AddObject(pPowerKatana2, GROUP_GAMEOBJ::ITEM);

	CMap* town = new CMap;
	town->Load(L"Town", L"texture\\map\\Town.png");
	AddObject(town, GROUP_GAMEOBJ::MAP);

	Back_Ground* skyday = new Back_Ground;
	skyday->Load(L"Sky_Day", L"texture\\background\\Sky_Day.png");
	AddObject(skyday, GROUP_GAMEOBJ::BACKGROUND);
	Back_Ground_Layer* townBG_day = new Back_Ground_Layer;
	townBG_day->Load(L"TownBG_Day", L"texture\\background\\TownBG_Day.png", fPoint(0.f,160.f), 7.f);
	AddObject(townBG_day, GROUP_GAMEOBJ::BACKGROUND);
	Back_Ground_Layer* townLayer_day = new Back_Ground_Layer;
	townLayer_day->Load(L"TownLayer_Day", L"texture\\background\\TownLayer_Day.png", fPoint(0.f,550.f), 3.f);
	AddObject(townLayer_day, GROUP_GAMEOBJ::BACKGROUND);

	CUICursor* pCursortown = new CUICursor;
	pCursortown->Load(L"ShootingCursor", L"texture\\ui\\ShootingCursor.png");
	AddObject(pCursortown, GROUP_GAMEOBJ::CURSOR);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::TILE, GROUP_GAMEOBJ::ITEM);

	// Camera Look 
	CCameraManager::getInst()->SetRange(fPoint(7616.f, 1536.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Town::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Town_bgm");


	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
