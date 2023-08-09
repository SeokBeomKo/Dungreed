#include "framework.h"
#include "CItem.h"

#include "CGameObject.h"

#include "CD2DImage.h"
#include "CCollider.h"

CItem::CItem()
{
    m_Img = nullptr;
    m_strKey = L"";
    m_strPath = L"";

    CreateGravity();
}

CItem::CItem(wstring _key, wstring _path)
{
    m_strKey = _key;
    m_strPath = _path;

    CreateGravity();
}

CItem::~CItem()
{
}

wstring CItem::GetKey()
{
    return m_strKey;
}

wstring CItem::GetPath()
{
    return m_strPath;
}

CItem* CItem::Clone()
{
	return new CItem(*this);
}

void CItem::update()
{
}

void CItem::render()
{
}

void CItem::OnCollisionEnter(CCollider* pOther)
{
    if (pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER)
    {
        DeleteObj(this);
    }
}

void CItem::OnCollision(CCollider* pOther)
{
}

void CItem::OnCollisionExit(CCollider* pOther)
{
}

void CItem::SetMove(int right, int left)
{
}

void CItem::SetAllMove(int right, int left)
{
}

void CItem::SetJump(bool set)
{
}

void CItem::SetDash(bool set)
{
}

void CItem::SetJumpCount()
{
}

void CItem::SetGR(bool set)
{
}

int CItem::GetMoveRight()
{
    return 0;
}

int CItem::GetMoveLeft()
{
    return 0;
}

bool CItem::GetDiag()
{
    return false;
}
