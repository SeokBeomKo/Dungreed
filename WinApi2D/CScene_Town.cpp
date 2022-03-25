#include "framework.h"
#include "CScene_Town.h"
#include "CGameObject.h"
#include "CPlayer.h"
// BackGround
#include "Back_Ground.h"
#include "TownBG_Day.h"
#include "TownLayer_Day.h"
#include "CSound.h"
#include "CD2DImage.h"
#include "CShort_Sword.h"
#include "CMuramasa.h"


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
	ChangeScn(GROUP_SCENE::DUNGEON);

}

void CScene_Town::Enter()
{
	// TODO : 브금
	CSoundManager::getInst()->AddSound(L"CScene_Town_bgm", L"sound\\0.Town.wav", false);
	CSoundManager::getInst()->Play(L"CScene_Town_bgm");
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\test.tile";
	LoadTile(path);

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	pPlayer->SetSteppedCallBack(StartDungeon, 0, 0);
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);


	CShort_Sword* pShort_Sword = new CShort_Sword;
	//pWeapon->SetPos(fPoint(200.f, 1200.f));
	//pWeapon->Load(L"Short_Sword", L"texture\\weapon\\ShortSword.png");
	AddObject(pShort_Sword, GROUP_GAMEOBJ::ITEM);
	CMuramasa* pMuramasa = new CMuramasa;
	AddObject(pMuramasa, GROUP_GAMEOBJ::ITEM);
	CItem* pMuramasa2 = new CMuramasa;
	pMuramasa2->SetPos(fPoint(20.f, 600.f));
	AddObject(pMuramasa2, GROUP_GAMEOBJ::ITEM);

	Back_Ground* skyday = new Back_Ground;
	skyday->Load(L"Sky_Day", L"texture\\background\\Sky_Day.png");
	AddObject(skyday, GROUP_GAMEOBJ::BACKGROUND);
	TownBG_Day* townBG_day = new TownBG_Day;
	townBG_day->Load(L"TownBG_Day", L"texture\\background\\TownBG_Day.png");
	AddObject(townBG_day, GROUP_GAMEOBJ::BACKGROUND);
	TownLayer_Day* townLayer_day = new TownLayer_Day;
	townLayer_day->Load(L"TownLayer_Day", L"texture\\background\\TownLayer_Day.png");
	AddObject(townLayer_day, GROUP_GAMEOBJ::BACKGROUND);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::TILE, GROUP_GAMEOBJ::ITEM);

	// Camera Look 
	CCameraManager::getInst()->SetTargetObj(pPlayer);

}

void CScene_Town::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Town_bgm");


	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
