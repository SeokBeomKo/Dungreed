#include "framework.h"
#include "CPlayerAttack.h"
#include "CD2DImage.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CSound.h"

#include "CWeapon.h"

CPlayerAttack::CPlayerAttack()
{
	m_Owner			= nullptr;
	m_pImg			= nullptr;

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
	CSoundManager::getInst()->AddSound(m_sInfo.m_wSoundName, m_sInfo.m_wSoundPath, false);

	fPoint finalpos = GetPos();
	fPoint pos = m_Owner->GetPos();
	fPoint realpos = CCameraManager::getInst()->GetRenderPos(pos);

	m_fptDirFX.x = MousePos().x - realpos.x;
	m_fptDirFX.y = MousePos().y - realpos.y;

	float rotateDegree = atan2(m_fptDirFX.y, m_fptDirFX.x) * 180 / 3.141592;


	m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sInfo.m_wImgName, m_sInfo.m_wImgPath);
	GetAnimator()->CreateAnimation(L"Attack", m_pImg, fPoint(0.f, 0.f), m_sInfo.slice, m_sInfo.step, m_sInfo.duration, m_sInfo.frmCount, false, true, rotateDegree);
	SetScale(m_sInfo.slice * 4.f);
	GetCollider()->SetScale(m_sInfo.slice * 4.f);

	m_iRange = 100;
	m_iDamage = 10;
	CSoundManager::getInst()->Play(m_sInfo.m_wSoundName);

	SetObjGroup(GROUP_GAMEOBJ::PLAYER_ATTACK);
	
	finalpos.x = finalpos.x + m_fptDirFX.normalize().x * m_iRange;
	finalpos.y = finalpos.y + m_fptDirFX.normalize().y * m_iRange;

	SetPos(finalpos);
	GetCollider()->SetFinalPos(m_Owner->GetPos());
}

void CPlayerAttack::update()
{
	m_fTimeFX += fDT;
	
	// TODO : 충돌체 제거 빠르게
	//if (GetCollider() != nullptr)
	//{
	//	if (m_fTimeFX >= 0.1f)
	//		DeleteCollider();
	//}
	
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

void CPlayerAttack::Set(CWeapon* _weapon)
{
	m_sInfo = _weapon->info;
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
