#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CD2DImage.h"

CPlayer::CPlayer()
{
	m_pImg  = CResourceManager::getInst()->LoadD2DImage(L"PlayerIdle", L"texture\\player\\PlayerIdle.png");
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"PlayerRun", L"texture\\player\\PlayerRun.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\player\\PlayerJump.png");
	m_pImg4 = CResourceManager::getInst()->LoadD2DImage(L"PlayerDead", L"texture\\player\\PlayerDead.png");

	SetName(L"Player");
	SetScale(fPoint(32.f *4, 32.f*4));


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

	//CAnimation* pAni;
	//pAni = GetAnimator()->FindAnimation(L"LeftMove");
	//pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	//pAni = GetAnimator()->FindAnimation(L"RightMove");
	//pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
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
	fPoint pos = GetPos();
	fPoint realpos;
	realpos = CCameraManager::getInst()->GetRenderPos(pos);

	if (GR == true)
	{
		pos.y = (0.9f * 0.5f * m_fTime * m_fTime) + (-20.f * m_fTime) + WINSIZEY / 2;
		m_fTime += fDT * 20;
	}

	if (Key(VK_SPACE) || Key('W'))
	{
		if (MousePos().x <= realpos.x)
		{
			GetAnimator()->Play(L"PlayerJumpleft");
		}
		else
		{
			GetAnimator()->Play(L"PlayerJumpright");
		}
		pos.y -= 500 * fDT;
	}
	else if (Key('D'))
	{
		pos.x += m_fVelocity * fDT;
		if (MousePos().x <= realpos.x)
		{
			GetAnimator()->Play(L"PlayerRunleft");
		}
		else
		{
			GetAnimator()->Play(L"PlayerRunright");
		}
	}
	else if (Key('A'))
	{
	pos.x -= m_fVelocity * fDT;
	if (MousePos().x <= realpos.x)
	{
		GetAnimator()->Play(L"PlayerRunleft");
	}
	else
	{
		GetAnimator()->Play(L"PlayerRunright");
	}
	}
	else if (Key('S'))
	{
		pos.y += m_fVelocity * fDT;
	}
	
	else
	{
		if (MousePos().x <= realpos.x)
		{
			GetAnimator()->Play(L"PlayerIdleleft");
		}
		else
		{
			GetAnimator()->Play(L"PlayerIdleright");
		}
	}

	SetPos(pos);


	if (KeyDown('B'))
	{
		CreateMissile();
		GetAnimator()->Play(L"PlayerIdleright");
	}

	GetAnimator()->update();
}

void CPlayer::render()
{

	component_render();
}

void CPlayer::OnCollision(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"")
	{
		GR = false;
	}
}

void CPlayer::CreateMissile()
{
 	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	pMissile->SetDir(fVec2(1, 0));

	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}

void CPlayer::Load(wstring strKey, wstring strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}