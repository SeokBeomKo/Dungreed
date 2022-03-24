#include "framework.h"
#include "CItem.h"
#include "CCollider.h"

CItem::CItem()
{
    CreateGravity();
}

CItem::~CItem()
{
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
