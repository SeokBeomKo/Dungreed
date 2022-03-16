#include "framework.h"
#include "CScene_Town.h"

#include "CGameObject.h"
#include "CPlayer.h"

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
	CGameObject* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200, 200));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	

	// Camera Look 지정
	CCameraManager::getInst()->SetLookAt(pPlayer->GetPos());
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Town::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
