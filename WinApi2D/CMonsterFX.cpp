#include "framework.h"
#include "CMonsterFX.h"

#include "CD2DImage.h"
#include "CAnimator.h"
#include "CSound.h"


CMonsterFX::CMonsterFX()
{
	m_Owner		= nullptr;
	m_pImg		= nullptr;

	limit		= 0;
	time		= 0;
}

CMonsterFX::~CMonsterFX()
{
}

void CMonsterFX::CreateFX(CGameObject* Obj, wstring state)
{
	m_Owner = Obj;
	CreateAnimator();
	fPoint pos = m_Owner->GetPos();
	fPoint Scale = m_Owner->GetScale();

	if (state == L"Spawn")
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterSpawn", L"texture\\monster\\MonsterSpawn.png");
		GetAnimator()->CreateAnimation(state, m_pImg, fPoint(0.f, 0.f), fPoint(31.f,31.f), fPoint(31.f, 0), 0.1f, 15);
		CSoundManager::getInst()->Play(L"MonsterSpawn");
		limit = 1.5f;
	}
	else if (state == L"Die")
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterDie", L"texture\\monster\\MonsterDie.png");
		GetAnimator()->CreateAnimation(state, m_pImg, fPoint(0.f, 0.f), fPoint(40.f,40.f), fPoint(40, 0), 0.05f, 11);
		CSoundManager::getInst()->Play(L"MonsterDie");
		limit = 0.55f;
	}
	float ReSizeScale = (Scale.x + Scale.y) / 2.f;
	GetAnimator()->Play(state);
	SetObjGroup(GROUP_GAMEOBJ::MONSTER_FX);
	SetScale(fPoint(ReSizeScale, ReSizeScale));
	SetPos(pos);
}

void CMonsterFX::PlayFX(CGameObject* Obj, wstring state)
{
	CMonsterFX* fx = new CMonsterFX;
	fx->CreateFX(Obj, state);
	CreateObj(fx, GROUP_GAMEOBJ::MONSTER_FX);
}

void CMonsterFX::update()
{
	time += fDT;
	
	if (time >= limit)
		DeleteObj(this);

	GetAnimator()->update();
}

void CMonsterFX::render()
{

	component_render();
}
