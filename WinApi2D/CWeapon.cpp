#include "framework.h"
#include "CWeapon.h"

#include "CGameObject.h"
#include "CItem.h"

#include "CD2DImage.h"
#include "CCollider.h"

CWeapon::CWeapon()
{
    m_Img = nullptr;
    m_strKey = L"";
    m_strPath = L"";

    CreateGravity();
}

CWeapon::CWeapon(wstring _key, wstring _path, WeaponInfo _info)
{
	m_Img = CResourceManager::getInst()->LoadD2DImage(_key, _path);
    SetScale(fPoint(m_Img->GetWidth() * 4.f, m_Img->GetHeight() * 4.f));
    SetName(_key);

    SetObjGroup(GROUP_GAMEOBJ::WEAPON);

    info = _info;

    CreateCollider();
    GetCollider()->SetScale(GetScale());
    GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));

    CreateGravity();
}

CWeapon::~CWeapon()
{
}

wstring CWeapon::GetKey()
{
    return wstring();
}

wstring CWeapon::GetPath()
{
    return wstring();
}

void CWeapon::render()
{
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(GetPos());
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
}

void CWeapon::OnCollision(CCollider* pOther)
{
}

void CWeapon::OnCollisionExit(CCollider* pOther)
{
}

void CWeapon::SetMove(int right, int left)
{
}

void CWeapon::SetAllMove(int right, int left)
{
}

void CWeapon::SetJump(bool set)
{
}

void CWeapon::SetDash(bool set)
{
}

void CWeapon::SetJumpCount()
{
}

void CWeapon::SetGR(bool set)
{
}

int CWeapon::GetMoveRight()
{
    return 0;
}

int CWeapon::GetMoveLeft()
{
    return 0;
}

bool CWeapon::GetDiag()
{
    return false;
}
