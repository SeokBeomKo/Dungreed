#include "framework.h"
#include "CPlayerAttack.h"
#include "CD2DImage.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CSound.h"

CPlayerAttack::CPlayerAttack()
{
	m_Owner			= nullptr;
	m_pImg			= nullptr;

	m_EffectCode	= 0;
	time			= 0;
	dashdir			= fPoint(0,0);
	m_iRange		= 0;			
}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::EnterAttack()
{
	CreateAnimator();
	CreateCollider();
	CSoundManager::getInst()->AddSound(L"katana", L"sound\\katana.wav", false);
	CSoundManager::getInst()->AddSound(L"swing", L"sound\\swing.wav", false);
	if (m_EffectCode == 1)
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"ShortSwordFX", L"texture\\weapon\\effect\\ShortSwordFX.png");
		GetAnimator()->CreateAnimation(L"Attack", m_pImg, fPoint(0.f, 0.f), fPoint(40.f, 28.f), fPoint(40.f, 0.f), 0.134f, 3);
		SetScale(fPoint(40.f, 28.f) * 4.f);
		GetCollider()->SetScale(fPoint(40.f, 28.f) * 4.f);
		m_iRange = 50;
		CSoundManager::getInst()->Play(L"swing");
	}
	else if (m_EffectCode == 2)
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"EXPowerKatanaSwingPlusFX", L"texture\\weapon\\effect\\EXPowerKatanaSwingPlusFX.png");
		GetAnimator()->CreateAnimation(L"Attack", m_pImg, fPoint(0.f, 0.f), fPoint(164.f, 138.f), fPoint(164.f, 0.f), 0.0333f, 12);
		SetScale(fPoint(164.f, 138.f) *1.5f);
		GetCollider()->SetScale(fPoint(164.f, 138.f)* 1.5f);
		m_iRange = 100;
		CSoundManager::getInst()->Play(L"katana");
	}

	GetAnimator()->Play(L"Attack");
	SetObjGroup(GROUP_GAMEOBJ::PLAYER_ATTACK);

	fPoint finalpos = GetPos();
	fPoint pos = m_Owner->GetPos();
	fPoint realpos;
	realpos = CCameraManager::getInst()->GetRenderPos(pos);

	dashdir.x = MousePos().x - realpos.x;
	dashdir.y = MousePos().y - realpos.y;

	finalpos.x = finalpos.x + dashdir.normalize().x * m_iRange;
	finalpos.y = finalpos.y + dashdir.normalize().y * m_iRange;

	SetPos(finalpos);

	GetCollider()->SetFinalPos(m_Owner->GetPos());
}

void CPlayerAttack::update()
{
	time += fDT;

	if (time >= 0.4f)
	DeleteObj(this);

	GetAnimator()->update();
}

void CPlayerAttack::render()
{
	component_render();
}

void CPlayerAttack::SetOwner(CGameObject* Obj)
{
	m_Owner = Obj;
}

void CPlayerAttack::SetCode(int code)
{
	m_EffectCode = code;
}

CGameObject* CPlayerAttack::GetOwner()
{
	return m_Owner;
}

void CPlayerAttack::OnCollisionEnter(CCollider* pOther)
{
}
