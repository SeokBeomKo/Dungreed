#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"

// 컴포넌트
#include "CCollider.h"
#include "CAnimator.h"
#include "CGravity.h"

#include "CTile.h"
#include "CD2DImage.h"

#include "CEquip.h"
#include "CPlayerAttack.h"
#include "CPlayerFX.h"

#define GR_POWER 2000
#define GR_TIME 1000
#define DS_SEC	0.15

class CEquip* pEquip;
CPlayer* CPlayer::instance = nullptr;

CPlayer::CPlayer()
{
	m_fVelocity = 350;
	IsDash = false;
	IsDashLow = false;
	m_bIsGravity = true;
	m_fSpeed = 0.f;
	IsJump = false;
	Isright = true;
	pEquip = new CEquip;
	pFX = new CPlayerFX;
	m_fDashTime = 0.f;
	m_bTimer = true;
	m_bTimer2 = true;
	m_fRunFX = 0.3f;
	m_fRunSound = 0.3f;
	m_iMoveRight = 0, m_iMoveLeft = 0;
	IsEquip = false;
	m_bIsFallJump = true;

	m_Savedata.hp = 100;

	SetName(L"Player");
	SetScale(fPoint(32.f * 4, 32.f * 4));
	SetObjGroup(GROUP_GAMEOBJ::PLAYER);

	// 플레이어 애니메이션
	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerIdle", L"texture\\player\\PlayerIdle.png");
	GetAnimator()->CreateAnimation(L"PlayerIdleright", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"PlayerIdleleft", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 5, true);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerRun", L"texture\\player\\PlayerRun.png");
	GetAnimator()->CreateAnimation(L"PlayerRunright", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 8);
	GetAnimator()->CreateAnimation(L"PlayerRunleft", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 8, true);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\player\\PlayerJump.png");
	GetAnimator()->CreateAnimation(L"PlayerJumpright", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 1.f, 1);
	GetAnimator()->CreateAnimation(L"PlayerJumpleft", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 1.f, 1, true);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerDead", L"texture\\player\\PlayerDead.png");
	GetAnimator()->CreateAnimation(L"PlayerDead", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 1.f, 1);
	
	// 플레이어 사운드
	CSoundManager::getInst()->AddSound(L"dash", L"sound\\dash.wav", false);
	CSoundManager::getInst()->AddSound(L"jumping", L"sound\\jumping.wav", false);
	CSoundManager::getInst()->AddSound(L"step1", L"sound\\step1.wav", false);
	CSoundManager::getInst()->AddSound(L"equip", L"sound\\equip.wav", false);

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

void CPlayer::SetMove(int right, int left)
{
	m_iMoveRight += right;
	m_iMoveLeft += left;
}

void CPlayer::SetAllMove(int right, int left)
{
	m_iMoveRight = right;
	m_iMoveLeft = left;
}

void CPlayer::SetFallJump(bool set)
{
	m_bIsFallJump = set;
}

void CPlayer::SetJump(bool set)
{
	IsJump = set;
}

void CPlayer::SetDash(bool set)
{
	IsDash = set;
}

void CPlayer::SetJumpCount()
{
	m_jumpCount = 2;
}

void CPlayer::SetGR(bool set)
{
	m_bIsGravity = set;
}


int CPlayer::GetMoveRight()
{
	return m_iMoveRight;
}

int CPlayer::GetMoveLeft()
{
	return m_iMoveLeft;
}

void CPlayer::RegisterPlayer()
{
	instance = this;
}

void CPlayer::update()
{
	MoveUpdate();
	AniUpdate();
}

CPlayer* CPlayer::GetPlayer()
{
	return instance;
}

void CPlayer::MoveUpdate()
{
	fPoint pos = GetPos();
	fPoint realpos;
	realpos = CCameraManager::getInst()->GetRenderPos(pos);

	if (pos.x <= 16.f)	// 맵 밖으로 못감
		pos.x = 16.f;
	if (pos.y <= 32.f)
		pos.y = 32.f;

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
		if (pEquip->GetOwner() != nullptr)
			pEquip->PlayerAttack(m_Savedata.m_EquipCode);
	}

	if (KeyDown(VK_RBUTTON))
	{
		if (MousePos().y > realpos.y)
		{
			IsDashLow = true;
		}
		m_fptMousePos = MousePos() - realpos;
		dashdir.x = MousePos().x - realpos.x;
		dashdir.y = MousePos().y - realpos.y;
		m_fDashTime = 0.f, m_bTimer = true, m_bTimer2 = true;
		IsDash = true;
		IsJump = false;
		m_fTime = GR_TIME * 1.9;
		m_fTimex = GR_TIME * 1.6;
		CSoundManager::getInst()->Play(L"dash");
	}

	if (IsDash)
	{
		m_fDashTime += fDT;
		if (m_fDashTime > 0.05f && m_bTimer)
		{
			pFX->PlayFX(this, L"dash");
			m_bTimer = false;
		}
		if (m_fDashTime > 0.08f && m_bTimer2)
		{
			pFX->PlayFX(this, L"dash");
			m_bTimer2 = false;
		}

		m_bIsGravity = true;
		GetGravity()->OnOffGravity(false);
		
		if (m_fTimex <= 0.f && m_fTime <= 0.f)
		{
			IsDash = false;
			if (!IsDashLow)
			{
				m_fTime = 0.f;
				GetGravity()->OnOffGravity(true, m_fTime);
			}
			else
			{
				m_fTime = 200.f;
				GetGravity()->OnOffGravity(true, m_fTime);
			}
			IsDashLow = false;
		}
		else
		{
			m_fTime -= 7500 * fDT;
			if (m_fTimex > 0)
			{
				m_fTimex -= 6000 * fDT;
			}
		}
		if (m_fptMousePos.x > 0)
		{
			if (m_iMoveLeft == 0)
			{
				pos.x += m_fTimex * dashdir.normalize().x * fDT;
				pos.y += m_fTime * dashdir.normalize().y * fDT;
			}
			else
			{
				pos.x += 0 * dashdir.normalize().x * fDT;
				pos.y += m_fTime * dashdir.normalize().y * fDT;
			}
		}
		else
		{
			if (m_iMoveRight == 0)
			{
				pos.x += m_fTimex * dashdir.normalize().x * fDT;
				pos.y += m_fTime * dashdir.normalize().y * fDT;
			}
			else
			{
				pos.x += 0 * dashdir.normalize().x * fDT;
				pos.y += m_fTime * dashdir.normalize().y * fDT;
			}
		}
	}
	else if(KeyDown(VK_SPACE) || KeyDown('W'))
	{	
		if (Key('S'))
		{
			if (m_bIsFallJump)
			{
				GetGravity()->OnOffGravity(true);
				pos.y += 5.f;
				m_bIsFallJump = false;
			}
		}
		else
		{
			if (m_jumpCount != 0)
			{
				if (m_jumpCount == 2)
					pFX->PlayFX(this, L"jump");
				else
					pFX->PlayFX(this, L"djump");
				--m_jumpCount;
				IsJump = true;
				m_fTime = GR_TIME;
			}
		}
	}
	else if (IsJump)
	{
		m_bIsGravity = true;
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

	if (Key('A'))
	{
		if (m_iMoveRight == 0)
			pos.x -= m_fVelocity * fDT;
		m_fSpeed = m_fVelocity;
	}
	else if (Key('D'))
	{
		if (m_iMoveLeft == 0)
			pos.x += m_fVelocity * fDT;
		m_fSpeed = m_fVelocity;
	}
	else
	{
		m_fSpeed = 0;
	}

	if (m_fSpeed > 0 && !m_bIsGravity)
	{
		m_fRunFX -= fDT;
		if (m_fRunFX < 0)
		{
			pFX->PlayFX(this, L"run");
			m_fRunFX = 0.3f;
		}
		m_fRunSound -= fDT;
		if (m_fRunSound < 0)
		{
			CSoundManager::getInst()->Play(L"step1");
			m_fRunSound = 0.3f;
		}
	}

	SetPos(pos);
}

void CPlayer::AniUpdate()
{
	if (Isright)
	{
		if (GetGravity()->CheckGravity() || m_bIsGravity)
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
		if (GetGravity()->CheckGravity() || m_bIsGravity)
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

	if (pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM)				// 플레이어와 장비
	{
		switch (pOther->GetObj()->GetItemCode())
		{
		case 1:
			Equip(pOther->GetObj()->GetItemCode());
			m_Savedata.m_EquipCode = 1;
			CSoundManager::getInst()->Play(L"equip");
			break;
		case 2:
			Equip(pOther->GetObj()->GetItemCode());
			m_Savedata.m_EquipCode = 2;
			CSoundManager::getInst()->Play(L"equip");
			break;
		default:
			break;
		}
	}
}

void CPlayer::OnCollision(CCollider* pOther)
{
}

void CPlayer::OnCollisionExit(CCollider* pOther)
{
}

void CPlayer::Equip(int code)
{
	wstring Key, Path;
	switch (code)
	{
	case 1:
		Key = L"Short_Sword"; Path = L"texture\\weapon\\ShortSword.png";			// 무기 경로
		break;
	case 2:
		Key = L"PowerKatana"; Path = L"texture\\weapon\\PowerKatana.png";
		break;
	default:
		return;
	}
	if (IsEquip)
	{
		DeleteObj(pEquip);
		IsEquip = false;
		pEquip = new CEquip;
	}

	pEquip->SetOwner(this);
	pEquip->Load(Key, Path);
	CreateObj(pEquip, GROUP_GAMEOBJ::PLAYER_WEAPON);
	IsEquip = true;
}

void CPlayer::SaveData(PlayerSave data)
{
	m_Savedata = data;
	Equip(m_Savedata.m_EquipCode);
}

PlayerSave CPlayer::LoadData()
{
	return m_Savedata;
}

