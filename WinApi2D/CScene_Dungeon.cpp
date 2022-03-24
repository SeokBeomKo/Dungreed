#include "framework.h"
#include "CScene_Dungeon.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "TownLayer_Day.h"

#include "CShort_Sword.h"
#include "CMuramasa.h"

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

	CPlayer* pPlayer = new CPlayer;
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	pPlayer->SaveData(sPlayer->LoadData());
	//pPlayer->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	
	CShort_Sword* pShort_Sword = new CShort_Sword;
	AddObject(pShort_Sword, GROUP_GAMEOBJ::ITEM);

	CMuramasa* pMuramasa = new CMuramasa;
	AddObject(pMuramasa, GROUP_GAMEOBJ::ITEM);

	
	TownLayer_Day* dungeonlayer = new TownLayer_Day;
	dungeonlayer->Load(L"SubBG", L"texture\\dungeon\\SubBG.png");
	AddObject(dungeonlayer, GROUP_GAMEOBJ::BACKGROUND);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::TILE, GROUP_GAMEOBJ::ITEM);

	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Dungeon::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Duneon_bgm");
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
