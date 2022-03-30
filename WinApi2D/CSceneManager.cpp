#include "framework.h"
#include "CSceneManager.h"

#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_Town.h"
#include "CScene_Dungeon.h"
#include "CScene_Dungeon01.h"
#include "CScene_DungeonBOSS.h"

CSceneManager::CSceneManager()
{
	// 씬 목록 초기화
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		m_arrScene[i] = nullptr;
	}
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	// 씬 목록 삭제
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneManager::ChangeScene(GROUP_SCENE scene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)scene];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneManager::render()
{
	m_pCurScene->render();
}

void CSceneManager::init()
{
	m_arrScene[(size_t)GROUP_SCENE::START] = new CScene_Start;
	m_arrScene[(size_t)GROUP_SCENE::START]->SetName(L"Start_Scene");

	m_arrScene[(size_t)GROUP_SCENE::TOOL] = new CScene_Tool;
	m_arrScene[(size_t)GROUP_SCENE::TOOL]->SetName(L"Tool_Scene");

	m_arrScene[(size_t)GROUP_SCENE::TOWN] = new CScene_Town;
	m_arrScene[(size_t)GROUP_SCENE::TOWN]->SetName(L"Town_Scene");

	m_arrScene[(size_t)GROUP_SCENE::DUNGEON] = new CScene_Dungeon;
	m_arrScene[(size_t)GROUP_SCENE::DUNGEON]->SetName(L"Dungeon_Scene");

	m_arrScene[(size_t)GROUP_SCENE::DUNGEON01] = new CScene_Dungeon01;
	m_arrScene[(size_t)GROUP_SCENE::DUNGEON01]->SetName(L"Dungeon_Scene01");

	m_arrScene[(size_t)GROUP_SCENE::DUNGEONBOSS] = new CScene_DungeonBOSS;
	m_arrScene[(size_t)GROUP_SCENE::DUNGEONBOSS]->SetName(L"CScene_DungeonBOSS");

	m_pCurScene = m_arrScene[(size_t)GROUP_SCENE::START];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
