#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"

// 컴포넌트
#include "CCollider.h"
#include "CAnimator.h"
#include "CGravity.h"

#include "CTile.h"
#include "CD2DImage.h"
#include "CTexture.h"

#include "CEquip.h"
#include "CMissile.h"

#define GR_POWER 2000
#define GR_TIME 1000
#define DS_SEC	0.15

class CEquip* pEquip;

CPlayer::CPlayer()
{
	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerIdle", L"texture\\player\\PlayerIdle.png");
	GetAnimator()->CreateAnimation(L"PlayerIdleright", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"PlayerIdleleft", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 5, true);

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerRun", L"texture\\player\\PlayerRun.png");
	GetAnimator()->CreateAnimation(L"PlayerRunright", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 8);
	GetAnimator()->CreateAnimation(L"PlayerRunleft", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 8, true);

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\player\\PlayerJump.png");
	GetAnimator()->CreateAnimation(L"PlayerJumpright", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 1);
	GetAnimator()->CreateAnimation(L"PlayerJumpleft", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 1, true);

	//m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerDead", L"texture\\player\\PlayerDead.png");
	m_fVelocity = 300;
	IsDash = false;
	IsDashLow = false;
	GR = true;
	m_fSpeed = 0.f;
	IsJump = false;
	Isright = true;
	IsEquip = false;
	pEquip = new CEquip;

	SetName(L"Player");
	SetScale(fPoint(32.f * 4, 32.f * 4));
	SetObjGroup(GROUP_GAMEOBJ::PLAYER);

	CreateCollider();
	GetCollider()->SetScale(fPoint(32.f, 64.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

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
	if (pOther->GetObj()->GetTileGroup() == GROUP_TILE::GROUND)				// GROUND 타일과 충돌 했을 때
	{
		GR = false;
		m_jumpCount = 2;
	}
	
	if (pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM)				// 플레이어와 장비
	{
		switch (pOther->GetObj()->GetItemCode())
		{
		case 1:
			Equip(L"Short_Sword", L"texture\\weapon\\ShortSword.png");
			break;
		case 2:
			Equip(L"Muramasa", L"texture\\weapon\\Muramasa.png");
			break;
		default:
			break;
		}
	}
	if (pOther->GetObj()->GetTileGroup() == GROUP_TILE::DOOR)				// 플레이어와 던전 입구
	{
		if (nullptr != m_pFunc)
		{
			m_pFunc(m_pParam1, m_pParam2);
		}
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
	}
}

void CPlayer::Equip(wstring strKey, wstring strPath)
{
	if (IsEquip)
	{
		DeleteObj(pEquip, GROUP_GAMEOBJ::PAYER_WEAPON);
		IsEquip = false;
		pEquip = new CEquip;
	}

	pEquip->SetOwner(this);
	pEquip->SetPos(this->GetPos() + fPoint(50.f, 0));
	pEquip->Load(strKey, strPath);
	CreateObj(pEquip, GROUP_GAMEOBJ::PAYER_WEAPON);

	IsEquip = true;
}

void CPlayer::SetSteppedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}

void CPlayer::SaveData(CPlayer* data)
{
	m_data = data;
}

CPlayer* CPlayer::LoadData()
{
	return m_data;
}


