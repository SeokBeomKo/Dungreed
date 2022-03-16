#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

// BackGround
#include "Back_Cloud00.h"
#include "Back_Cloud01.h"
#include "Back_Sky.h"

// UI
#include "MainLogo.h"
#include "CStartUI.h"
#include "COptionUI.h"
#include "CExitUI.h"

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
		CSoundManager::getInst()->Stop(L"CScene_Start_bgm");
	}
} 

void StartCheck(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TOWN);
	CSoundManager::getInst()->Stop(L"CScene_Start_bgm");
}

void OptionCheck(DWORD_PTR, DWORD_PTR)
{
	// TODO : 가능하다면 볼륨 조정
}

void ExitCheck(DWORD_PTR, DWORD_PTR)
{
	// 윈도우 종료 함수
	PostQuitMessage(0);
}

void CScene_Start::Enter()
{
	CSoundManager::getInst()->AddSound(L"CScene_Start_bgm", L"sound\\Skies Are Blue.mp3", false);
	CSoundManager::getInst()->AddSound(L"CScene_Town_bgm", L"sound\\Towngreed.mp3", false);
	CSoundManager::getInst()->Play(L"CScene_Start_bgm");

	// 타일 로딩
	//wstring path = CPathManager::getInst()->GetContentPath();
	//path += L"tile\\Start.tile";
	//LoadTile(path);

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

	CStartUI* pStartUI = new CStartUI();
	pStartUI->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2 + 100.f));
	pStartUI->Load(L"PlayOff_Kor", L"texture\\ui\\PlayOff_Kor.png");
	pStartUI->SetClickedCallBack(StartCheck, 0, 0);
	AddObject(pStartUI, GROUP_GAMEOBJ::UI);

	COptionUI* pOptiontUI = new COptionUI();
	pOptiontUI->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2 + 150.f));
	pOptiontUI->Load(L"OptionOff_Kor", L"texture\\ui\\OptionOff_Kor.png");
	AddObject(pOptiontUI, GROUP_GAMEOBJ::UI);

	CExitUI* pExitUI = new CExitUI();
	pExitUI->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2 + 200.f));
	pExitUI->Load(L"ExitOff_Kor", L"texture\\ui\\ExitOff_Kor.png");
	pExitUI->SetClickedCallBack(ExitCheck, 0, 0);
	AddObject(pExitUI, GROUP_GAMEOBJ::UI);

	// 윈도우 종료 함수 PostQuitMessage(0);

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
