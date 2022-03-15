#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "Back_Cloud00.h"
#include "Back_Cloud01.h"
#include "Back_Sky.h"
#include "MainLogo.h"

#include "CSound.h"
#include "CD2DImage.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

	if (KeyDown(VK_F3))
	{
		ChangeScn(GROUP_SCENE::TOOL);
		CSoundManager::getInst()->Stop(L"bgm");
	}
}

void CScene_Start::Enter()
{
	CSoundManager::getInst()->AddSound(L"bgm", L"sound\\Skies Are Blue.mp3", true);
	CSoundManager::getInst()->Play(L"bgm");

	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Start.tile";
	//LoadTile(path);

	// Player 추가
	CGameObject* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200, 200));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	Back_Sky* backsky = new Back_Sky;
	backsky->Load(L"Back_Sky", L"texture\\background\\BackSky.png");
	AddObject(backsky, GROUP_GAMEOBJ::BACKGROUND);

	Back_Cloud00* cloud00 = new Back_Cloud00;
	cloud00->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	cloud00->Load(L"BackCloud00", L"texture\\background\\BackCloud00.png");
	AddObject(cloud00, GROUP_GAMEOBJ::BACKGROUND);

	Back_Cloud00* cloud00clone = cloud00->Clone();
	cloud00clone->SetPos(fPoint(WINSIZEX / 2.f + 2500.f, WINSIZEY / 2.f));
	AddObject(cloud00clone, GROUP_GAMEOBJ::BACKGROUND);

	Back_Cloud01* cloud01 = new Back_Cloud01;
	cloud01->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	cloud01->Load(L"BackCloud01", L"texture\\background\\BackCloud01.png");
	AddObject(cloud01, GROUP_GAMEOBJ::BACKGROUND);
	
	Back_Cloud01* cloud01clone = cloud01->Clone();
	cloud01clone->SetPos(fPoint(WINSIZEX/ 2.f + 2500.f, WINSIZEY / 2.f));
	AddObject(cloud01clone, GROUP_GAMEOBJ::BACKGROUND);

	MainLogo* logo = new MainLogo;
	logo->Load(L"MainLogo", L"texture\\background\\MainLogo.png");
	AddObject(logo, GROUP_GAMEOBJ::BACKGROUND);

	// Monster 추가
	//CMonster* pMonster = new CMonster;
	//pMonster->SetPos(fPoint(1100, 350));
	//pMonster->SetCenterPos(pMonster->GetPos());
	//AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);

	// Camera Look 지정
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}


void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
