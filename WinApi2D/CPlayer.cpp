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

CPlayer::CPlayer()
{
	m_fVelocity = 350;
	IsDash = false;
	IsDashLow = false;
	GR = true;
	m_fSpeed = 0.f;
	IsJump = false;
	Isright = true;
	pEquip = new CEquip;
	pFX = new CPlayerFX;
	time = 0.f;
	timer = true;
	timer2 = true;
	m_fRunFX = 0.3f;
	m_fRunSound = 0.3f;
	m_iMoveRight = 0, m_iMoveLeft = 0;
	IsEquip = false;

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
	GR = set;
}


int CPlayer::GetMoveRight()
{
	return m_iMoveRight;
}

int CPlayer::GetMoveLeft()
{
	return m_iMoveLeft;
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
		dashdir.x = MousePos().x - realpos.x;
		dashdir.y = MousePos().y - realpos.y;
		time = 0.f, timer = true, timer2 = true;
		IsDash = true;
		IsJump = false;
		m_fTime = GR_TIME * 2;
		m_fTimex = GR_TIME * 1.7;
		CSoundManager::getInst()->Play(L"dash");
	}

	if (IsDash)
	{
		time += fDT;
		if (time > 0.05f && timer)
		{
			pFX->PlayFX(this, L"dash");
			timer = false;
		}
		if (time > 0.08f && timer2)
		{
			pFX->PlayFX(this, L"dash");
			timer2 = false;
		}

		GR = true;
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
		if (MousePos().x - CCameraManager::getInst()->GetRenderPos(pos).x > 0)
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

	if (KeyDown('S'))
	{
		GetGravity()->OnOffGravity(true);
		pos.y += 5.f;
	}
	else if (Key('A'))
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

	if (m_fSpeed > 0 && !GR)
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
		if (GetGravity()->CheckGravity() || GR)
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
		if (GetGravity()->CheckGravity() || GR)
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
			break;
		case 2:
			Equip(pOther->GetObj()->GetItemCode());
			m_Savedata.m_EquipCode = 2;
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
			sPlayer = new CPlayer;
			sPlayer->SaveData(this->LoadData());
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
	CSoundManager::getInst()->Play(L"equip");
	IsEquip = true;
}

void CPlayer::SetSteppedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
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

