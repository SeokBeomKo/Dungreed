#include "framework.h"
#include "CShort_Sword.h"
#include "CD2DImage.h"

#include "CCollider.h"

CShort_Sword::CShort_Sword()
{
	m_Img = CResourceManager::getInst()->LoadD2DImage(L"Short_Sword", L"texture\\weapon\\ShortSword.png");
    SetScale(fPoint(m_Img->GetWidth() * 4.f, m_Img->GetHeight() * 4.f));
    SetPos(fPoint(1200.f, 550.f));
    SetName(L"Short_Sword");
    SetItemCode(1);
    SetObjGroup(GROUP_GAMEOBJ::WEAPON);

    CreateCollider();
    GetCollider()->SetScale(GetScale());
    GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));
}

CShort_Sword::~CShort_Sword()
{
}

void CShort_Sword::render()
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

void CShort_Sword::update()
{
}


