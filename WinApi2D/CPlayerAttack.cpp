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
	m_iDamage 		= 0;
	m_iRange		= 0;
	m_fTimeFX		= 0.f;
	m_fptDirFX		= fPoint(0,0);		
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
		m_iDamage = 10;
		CSoundManager::getInst()->Play(L"swing");
	}
	else if (m_EffectCode == 2)
	{
		m_pImg = CResourceManager::getInst()->LoadD2DImage(L"EXPowerKatanaSwingPlusFX", L"texture\\weapon\\effect\\EXPowerKatanaSwingPlusFX.png");
		GetAnimator()->CreateAnimation(L"Attack", m_pImg, fPoint(0.f, 0.f), fPoint(164.f, 138.f), fPoint(164.f, 0.f), 0.0333f, 12);
		SetScale(fPoint(164.f, 138.f) *1.5f);
		GetCollider()->SetScale(fPoint(164.f, 138.f)* 1.5f);
		m_iRange = 100;
		m_iDamage = 15;
		CSoundManager::getInst()->Play(L"katana");
	}
	SetObjGroup(GROUP_GAMEOBJ::PLAYER_ATTACK);

	fPoint finalpos = GetPos();
	fPoint pos = m_Owner->GetPos();
	fPoint realpos;
	realpos = CCameraManager::getInst()->GetRenderPos(pos);

	m_fptDirFX.x = MousePos().x - realpos.x;
	m_fptDirFX.y = MousePos().y - realpos.y;

	finalpos.x = finalpos.x + m_fptDirFX.normalize().x * m_iRange;
	finalpos.y = finalpos.y + m_fptDirFX.normalize().y * m_iRange;

	SetPos(finalpos);
	GetCollider()->SetFinalPos(m_Owner->GetPos());
}

void CPlayerAttack::update()
{
	m_fTimeFX += fDT;

	if (m_fTimeFX >= 0.4f)
		DeleteObj(this);

	GetAnimator()->update();
}

void CPlayerAttack::render()
{
	GetAnimator()->Play(L"Attack");

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

int CPlayerAttack::GetDamage()
{
	return m_iDamage;
}

CGameObject* CPlayerAttack::GetOwner()
{
	return m_Owner;
}

void CPlayerAttack::OnCollisionEnter(CCollider* pOther)
{
}
