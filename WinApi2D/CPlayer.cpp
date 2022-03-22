#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"

// 컴포넌트
#include "CCollider.h"
#include "CAnimator.h"
#include "CGravity.h"

#include "CTile.h"
#include "CD2DImage.h"
#include "CEquip.h"

#define GR_POWER 2000
#define GR_TIME 1000
#define DS_SEC	0.15

CPlayer::CPlayer()
{
	m_pImg  = CResourceManager::getInst()->LoadD2DImage(L"PlayerIdle", L"texture\\player\\PlayerIdle.png");
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"PlayerRun", L"texture\\player\\PlayerRun.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\player\\PlayerJump.png");
	m_pImg4 = CResourceManager::getInst()->LoadD2DImage(L"PlayerDead", L"texture\\player\\PlayerDead.png");

	SetName(L"Player");
	SetScale(fPoint(32.f *4, 32.f*4));
	SetObjGroup(GROUP_GAMEOBJ::PLAYER);

	CreateCollider();
	GetCollider()->SetScale(fPoint(32.f, 64.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerIdleright",		m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"PlayerIdleleft",		m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 5, true);
	GetAnimator()->CreateAnimation(L"PlayerRunright",		m_pImg2, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 8);
	GetAnimator()->CreateAnimation(L"PlayerRunleft",		m_pImg2, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 8, true);
	GetAnimator()->CreateAnimation(L"PlayerJumpright",		m_pImg3, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 1);
	GetAnimator()->CreateAnimation(L"PlayerJumpleft",		m_pImg3, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 1, true);
	
	CreateGravity();
}

CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	MoveUpdate();
	AniUpdate();
}

void CPlayer::MoveUpdate()
{
	fPoint pos = GetPos();
	fPoint realpos;
	realpos = CCameraManager::getInst()->GetRenderPos(pos);

	if (MousePos().x <= realpos.x)
	{
		Isright = false;
	}
	else
	{
		Isright = true;
	}

	if (KeyDown(VK_LBUTTON))
	{
		// 공격
	}

	if (KeyDown(VK_RBUTTON))
	{
		IsDash = true;
		IsJump = false;
		mousePos = MousePos();
		playerPos = realpos;
		dashdir.x = mousePos.x - playerPos.x;
		dashdir.y = mousePos.y - playerPos.y;

		if (mousePos.y > playerPos.y)
		{
			IsDashLow = true;
		}

		m_fTime = GR_TIME * 2.5;
		m_fTimex = GR_TIME * 2;
	}
	
	if (KeyDown(VK_SPACE) || KeyDown('W'))
	{
		if (!(m_jumpCount == 0))
		{
			--m_jumpCount;
			IsJump = true;
			m_fTime = GR_TIME;
		}
	}
	if (IsDash)
	{
		GR = true;
		GetGravity()->OnOffGravity(false);
		if (!IsDashLow)
		{
			if (m_fTimex <= 0.f && m_fTime <= 0.f)
			{
				IsDash = false;
				IsDashLow = false;
				//m_fTime = 0.f;
				GetGravity()->OnOffGravity(true, m_fTime);
			}
			else
			{
				m_fTime -= 7500 * fDT;
			}
		}
		else
		{
			if (m_fTimex < 50.f)
			{
				IsDash = false;
				IsDashLow = false;
				m_fTime = 500.f;
				GetGravity()->OnOffGravity(true, m_fTime);
			}
			else
			{
				m_fTime -= 2500 * fDT;
			}
		}
		if (m_fTimex > 0)
		{
			m_fTimex -= 6000 * fDT;
		}

		pos.x += m_fTimex * dashdir.normalize().x * fDT;
		pos.y += m_fTime * dashdir.normalize().y * fDT;
	}
	else if (IsJump)
	{
		GR = true;
		GetGravity()->OnOffGravity(false);
		m_fTime -= 2000 * fDT;
		pos.y -= m_fTime * fDT;
		if (m_fTime <= 0.f)
		{
			IsJump = false;
			m_fTime = 0.f;
			GetGravity()->OnOffGravity(true, m_fTime);
		}
	}

	if (Key('D'))
	{
		pos.x += m_fVelocity * fDT;
		m_fSpeed = m_fVelocity;
	}
	else if (Key('A'))
	{
		pos.x -= m_fVelocity * fDT;
		m_fSpeed = m_fVelocity;
	}
	else if (Key('S'))
	{
		pos.y += m_fVelocity * fDT;
	}
	else
	{
		m_fSpeed = 0;
	}

	SetPos(pos);
}

void CPlayer::AniUpdate()
{
	if (Isright)
	{
		if (GR)
		{
			GetAnimator()->Play(L"PlayerJumpright");
		}
		else if (m_fSpeed > 0)
		{
			GetAnimator()->Play(L"PlayerRunright");
		}
		else
		{
			GetAnimator()->Play(L"PlayerIdleright");
		}
	}
	else
	{
		if (GR)
		{
			GetAnimator()->Play(L"PlayerJumpleft");
		}
		else if (m_fSpeed > 0)
		{
			GetAnimator()->Play(L"PlayerRunleft");
		}
		else
		{
			GetAnimator()->Play(L"PlayerIdleleft");
		}
	}

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::OnCollisionEnter(CCollider* pOther)
{
	if (pOther->GetObj()->GetTileGroup() == GROUP_TILE::GROUND)		// GROUND 타일과 충돌 했을 때
	{
		GR = false;
		m_jumpCount = 2;
	}
	
	if (pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PAYER_WEAPON)
	{
		Equip();
	}
}

void CPlayer::OnCollision(CCollider* pOther)
{
	if (pOther->GetObj()->GetTileGroup() == GROUP_TILE::GROUND)
	{
		GR = false;
	}
}

void CPlayer::OnCollisionExit(CCollider* pOther)
{
	if (pOther->GetObj()->GetTileGroup() == GROUP_TILE::GROUND)
	{
		GR = false;
		GetGravity()->OnOffGravity(true);
	}
}

void CPlayer::Load(wstring strKey, wstring strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}

void CPlayer::Equip()
{
	CEquip* pEquip = new CEquip;
	pEquip->SetOwner(this);
	pEquip->SetPos(this->GetPos()+fPoint(50.f, 0));

	CreateObj(pEquip, GROUP_GAMEOBJ::PAYER_WEAPON);
}



