#include "framework.h"
#include "CScene_Start.h"

#include "CGameObject.h"

// BackGround
#include "Back_Ground_Object.h"
#include "Back_Ground.h"

// UI
#include "MainLogo.h"
#include "CMainButtonUI.h"
#include "CUICursor.h"

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
	}
} 

void StartCheck(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TOWN);
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
	CSoundManager::getInst()->AddSound(L"CScene_Start_bgm", L"sound\\title.wav", false);
	CSoundManager::getInst()->Play(L"CScene_Start_bgm");

	Back_Ground* backsky = new Back_Ground;
	backsky->Load(L"Back_Sky", L"texture\\background\\BackSky.png");
	AddObject(backsky, GROUP_GAMEOBJ::BACKGROUND);

	Back_Ground_Object* cloud00 = new Back_Ground_Object;
	cloud00->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	cloud00->Load(L"BackCloud00", L"texture\\background\\BackCloud00.png", 15.f, -1900.f, 2500.f);
	AddObject(cloud00, GROUP_GAMEOBJ::BACKGROUND);
	Back_Ground_Object* cloud00clone = cloud00->Clone();
	cloud00clone->SetPos(fPoint(WINSIZEX / 2.f + 2500.f, WINSIZEY / 2.f));
	AddObject(cloud00clone, GROUP_GAMEOBJ::BACKGROUND);

	Back_Ground_Object* cloud01 = new Back_Ground_Object;
	cloud01->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	cloud01->Load(L"BackCloud01", L"texture\\background\\BackCloud01.png", 80.f, -2300.f, 2500.f);
	AddObject(cloud01, GROUP_GAMEOBJ::BACKGROUND);
	Back_Ground_Object* cloud01clone = cloud01->Clone();
	cloud01clone->SetPos(fPoint(WINSIZEX/ 2.f + 2500.f, WINSIZEY / 2.f));
	AddObject(cloud01clone, GROUP_GAMEOBJ::BACKGROUND);

	MainLogo* logo = new MainLogo;
	logo->Load(L"MainLogo", L"texture\\background\\MainLogo.png");
	logo->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2 - 125.f));
	AddObject(logo, GROUP_GAMEOBJ::BACKGROUND);

	MainLogo* copy = new MainLogo;
	copy->Load(L"Copyright", L"texture\\background\\Copyright.png");
	copy->SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2 + 310.f));
	AddObject(copy, GROUP_GAMEOBJ::BACKGROUND);

	CMainButtonUI* pStartUI = new CMainButtonUI();
	pStartUI->Load(L"PlayOff_Kor", L"texture\\ui\\PlayOff_Kor.png", L"PlayOn_Kor", L"texture\\ui\\PlayOn_Kor.png");
	pStartUI->SetPos(fPoint(WINSIZEX / 2 - pStartUI->GetScale().x /2, WINSIZEY / 2 + 100.f - pStartUI->GetScale().y / 2));
	pStartUI->SetClickedCallBack(StartCheck, 0, 0);
	AddObject(pStartUI, GROUP_GAMEOBJ::UI);

	CMainButtonUI* pOptiontUI = new CMainButtonUI();
	pOptiontUI->Load(L"OptionOff_Kor", L"texture\\ui\\OptionOff_Kor.png", L"OptionOn_Kor", L"texture\\ui\\OptionOn_Kor.png");
	pOptiontUI->SetPos(fPoint(WINSIZEX / 2 - pOptiontUI->GetScale().x / 2, WINSIZEY / 2 + 150.f - pOptiontUI->GetScale().y / 2));
	AddObject(pOptiontUI, GROUP_GAMEOBJ::UI);

	CMainButtonUI* pExitUI = new CMainButtonUI();
	pExitUI->Load(L"ExitOff_Kor", L"texture\\ui\\ExitOff_Kor.png", L"ExitOn_Kor", L"texture\\ui\\ExitOn_Kor.png");
	pExitUI->SetPos(fPoint(WINSIZEX / 2 - pExitUI->GetScale().x / 2, WINSIZEY / 2 + 200.f - pExitUI->GetScale().y / 2));
	pExitUI->SetClickedCallBack(ExitCheck, 0, 0);
	AddObject(pExitUI, GROUP_GAMEOBJ::UI);

	CUICursor* pCursor = new CUICursor;
	pCursor->Load(L"BasicCursor", L"texture\\ui\\BasicCursor.png");
	AddObject(pCursor, GROUP_GAMEOBJ::CURSOR);

	// Camera Look 지정
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}


void CScene_Start::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Start_bgm");
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
