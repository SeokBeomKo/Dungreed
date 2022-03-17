#include "framework.h"
#include "CScene_Town.h"

#include "CGameObject.h"
#include "CPlayer.h"

// BackGround
#include "Sky_Day.h"
#include "TownBG_Day.h"
#include "TownLayer_Day.h"

#include "CSound.h"
#include "CD2DImage.h"

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
		CSoundManager::getInst()->Stop(L"CScene_Town_bgm");
	}
}

void CScene_Town::Enter()
{
	// TODO : 브금 해결
	CSoundManager::getInst()->Play(L"CScene_Town_bgm");

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	
	Sky_Day* skyday = new Sky_Day;
	skyday->Load(L"Sky_Day", L"texture\\background\\Sky_Day.png");
	AddObject(skyday, GROUP_GAMEOBJ::BACKGROUND);

	TownBG_Day* townBG_day = new TownBG_Day;
	townBG_day->Load(L"TownBG_Day", L"texture\\background\\TownBG_Day.png");
	AddObject(townBG_day, GROUP_GAMEOBJ::BACKGROUND);

	TownLayer_Day* townLayer_day = new TownLayer_Day;
	townLayer_day->Load(L"TownLayer_Day", L"texture\\background\\TownLayer_Day.png");
	AddObject(townLayer_day, GROUP_GAMEOBJ::BACKGROUND);
	

	// Camera Look 지정
	//CCameraManager::getInst()->SetLookAt(pPlayer->GetPos());
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Town::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
