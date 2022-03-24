#include "framework.h"
#include "CScene_Dungeon.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "TownLayer_Day.h"

CScene_Dungeon::CScene_Dungeon()
{
}

CScene_Dungeon::~CScene_Dungeon()
{
}

void CScene_Dungeon::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::START);
	}
}

void CScene_Dungeon::Enter()
{
	CSoundManager::getInst()->Play(L"CScene_Duneon_bgm");

	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\test2.tile";
	LoadTile(path);

	CPlayer* pPlayer = nullptr;
	pPlayer = sPlayer->LoadData();

	if (!(CheckGroup(GROUP_GAMEOBJ::PLAYER)))
	{
		AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	}
	
	TownLayer_Day* dungeonlayer = new TownLayer_Day;
	dungeonlayer->Load(L"SubBG", L"texture\\dungeon\\SubBG.png");
	AddObject(dungeonlayer, GROUP_GAMEOBJ::BACKGROUND);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);

	// CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Dungeon::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Duneon_bgm");
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
