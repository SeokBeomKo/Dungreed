#include "framework.h"
#include "CWeapon.h"
#include "CD2DImage.h"

#include "CCollider.h"

CWeapon::CWeapon()
{
	m_Img = CResourceManager::getInst()->LoadD2DImage(L"Short_Sword", L"texture\\weapon\\ShortSword.png");
    SetScale(fPoint(m_Img->GetWidth() * 4.f, m_Img->GetHeight() * 4.f));
    SetPos(fPoint(1200.f, 550.f));
    SetName(L"Short_Sword");
    SetObjGroup(GROUP_GAMEOBJ::PAYER_WEAPON);

    CreateCollider();
    GetCollider()->SetScale(GetScale());
    GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));

    CreateGravity();
}

CWeapon::~CWeapon()
{
}

void CWeapon::render()
{
    fPoint pos = GetPos();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    fPoint scale = GetScale();

    CRenderManager::getInst()->RenderImage(
        m_Img,
        renderpos.x - scale.x / 2.f,
        renderpos.y - scale.y / 2.f,
        renderpos.x + scale.x / 2.f,
        renderpos.y + scale.y / 2.f
    );

    component_render();
}

void CWeapon::update()
{
}

void CWeapon::OnCollisionEnter(CCollider* pOther)
{
    if (pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER)
    {
        DeleteObj(this);
    }
}

