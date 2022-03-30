#include "framework.h"
#include "CScene_Dungeon.h"
#include "CMap.h"
#include "CUICursor.h"

#include "CDoor.h"

// ������Ʈ
#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

// ������
#include "CShort_Sword.h"
#include "CPowerKatana.h"

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
	CSoundManager::getInst()->AddSound(L"CScene_Duneon_bgm", L"sound\\1.JailField.wav", false);
	CSoundManager::getInst()->Play(L"CScene_Duneon_bgm");

	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\EnterDG.tile";
	LoadTile(path);

	// �� �̵�
	CDoor* pNextDoor = new CDoor;
	pNextDoor->SetNextScene(GROUP_SCENE::DUNGEON01);
	pNextDoor->Setting(fPoint(1744.f, 516.f), fPoint(32.f, 256.f));
	AddObject(pNextDoor, GROUP_GAMEOBJ::TILE);

	// �÷��̾�
	CPlayer* pPlayer = new CPlayer;
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	pPlayer->RegisterPlayer();
	pPlayer->SetPos(fPoint(570.f, 600.f));
	pPlayer->SaveData(sPlayer->LoadData());
	
	// ������
	CItem* pShort_Sword = new CShort_Sword;
	AddObject(pShort_Sword, GROUP_GAMEOBJ::ITEM);
	CItem* pPowerKatana = new CPowerKatana;
	AddObject(pPowerKatana, GROUP_GAMEOBJ::ITEM);

	// ���
	
	// ��
	CMap* enterDG = new CMap;
	enterDG->Load(L"EnterDG", L"texture\\dungeon\\EnterDG.png");
	AddObject(enterDG, GROUP_GAMEOBJ::MAP);

	CUICursor* pCursortown = new CUICursor;
	pCursortown->Load(L"ShootingCursor", L"texture\\ui\\ShootingCursor.png");
	AddObject(pCursortown, GROUP_GAMEOBJ::CURSOR);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER_ATTACK, GROUP_GAMEOBJ::MONSTER);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::TILE, GROUP_GAMEOBJ::ITEM);

	// Camera Look 
	CCameraManager::getInst()->SetRange(fPoint(448.f, 192.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Dungeon::Init()
{
}



void CScene_Dungeon::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
