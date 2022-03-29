#include "framework.h"
#include "CPlayerFX.h"

#include "CD2DImage.h"
#include "CAnimator.h"
#include "CSound.h"

CPlayerFX::CPlayerFX()
{
	m_Owner = nullptr;
	m_pImg  = nullptr;

	limit	= 0;
	time	= 0;
}

CPlayerFX::~CPlayerFX()
{
}

void CPlayerFX::CreateFX(CGameObject* Obj, wstring state)
{
	m_Owner = Obj;
	CreateAnimator();
	fPoint pos = m_Owner->GetPos();

	if (state == L"run")
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"RunFX", L"texture\\player\\RunFX.png");
		if (CCameraManager::getInst()->GetRenderPos(m_Owner->GetPos()).x <= MousePos().x)
			GetAnimator()->CreateAnimation(state, m_pImg, fPoint(0.f, 0.f), fPoint(16.f, 16.f), fPoint(16.f, 0.f), 0.05f, 6);
		else
			GetAnimator()->CreateAnimation(state, m_pImg, fPoint(0.f, 0.f), fPoint(16.f, 16.f), fPoint(16.f, 0.f), 0.05f, 6, true);
		SetScale(fPoint(16.f,16.f) * 4.f);
		limit = 0.3f;
		pos.y += m_Owner->GetScale().y / 6.f;
	}
	else if (state == L"jump")
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"JumpFX", L"texture\\player\\JumpFX.png");
		GetAnimator()->CreateAnimation(state, m_pImg, fPoint(0.f, 0.f), fPoint(9.f, 10.f), fPoint(9.f, 0.f), 0.05f, 5);
		SetScale(fPoint(9.f, 10.f) * 4.f);
		limit = 0.05f * 5.f;
		pos.y += m_Owner->GetScale().y / 4.f;
		CSoundManager::getInst()->Play(L"jumping");
	}
	else if (state == L"djump")
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"DoubleJumpFX", L"texture\\player\\DoubleJumpFX.png");
		GetAnimator()->CreateAnimation(state, m_pImg, fPoint(0.f, 0.f), fPoint(9.f, 9.f), fPoint(9.f, 0.f), 0.04f, 6);
		SetScale(fPoint(9.f, 9.f) * 4.f);
		limit = 0.04f * 6.f;
		pos.y += m_Owner->GetScale().y / 4.f;
		CSoundManager::getInst()->Play(L"jumping");
	}
	else if (state == L"dash")
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"DashFX", L"texture\\player\\DashFX.png");
		if (CCameraManager::getInst()->GetRenderPos(m_Owner->GetPos()).x <= MousePos().x)
			GetAnimator()->CreateAnimation(state, m_pImg, fPoint(0.f, 0.f), fPoint(17.f, 21.f), fPoint(17.f, 0.f), 1.f, 1);
		else
			GetAnimator()->CreateAnimation(state, m_pImg, fPoint(0.f, 0.f), fPoint(17.f, 21.f), fPoint(17.f, 0.f), 1.f, 1, true);
		SetScale(fPoint(17.f, 21.f) * 4.f);
		limit = 0.25f;
	}
	GetAnimator()->Play(state);
	SetObjGroup(GROUP_GAMEOBJ::PLAYER_FX);

	

	SetPos(pos);
}

void CPlayerFX::PlayFX(CGameObject* Obj, wstring state)
{
	CPlayerFX* fx = new CPlayerFX;
	fx->CreateFX(Obj, state);
	CreateObj(fx, GROUP_GAMEOBJ::PLAYER_FX);
}

void CPlayerFX::update()
{
	time+= fDT;

	if (time >= limit)
		DeleteObj(this);

	GetAnimator()->update();
}

void CPlayerFX::render()
{
	component_render();
}
