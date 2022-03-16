#include "framework.h"
#include "CScene_Town.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "Sky_Day.h"

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
	// TODO : 브금전환...
	CSoundManager::getInst()->Play(L"CScene_Town_bgm");

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	
	Sky_Day* skyday = new Sky_Day;
	skyday->Load(L"Sky_Day", L"texture\\background\\Sky_Day.png");
	AddObject(skyday, GROUP_GAMEOBJ::BACKGROUND);
	

	// Camera Look 지정
	//CCameraManager::getInst()->SetLookAt(pPlayer->GetPos());
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Town::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
