#include "framework.h"
#include "CMuramasa.h"
#include "CD2DImage.h"

#include "CCollider.h"

CMuramasa::CMuramasa()
{
    m_Img = CResourceManager::getInst()->LoadD2DImage(L"Muramasa", L"texture\\weapon\\Muramasa.png");
    SetScale(fPoint(m_Img->GetWidth() * 4.f, m_Img->GetHeight() * 4.f));
    SetPos(fPoint(800.f, 550.f));
    SetName(L"Muramasa");
    SetItemCode(2);
    SetObjGroup(GROUP_GAMEOBJ::ITEM);

    CreateCollider();
    GetCollider()->SetScale(GetScale());
    GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));
}

CMuramasa::~CMuramasa()
{
}

void CMuramasa::render()
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

void CMuramasa::update()
{
}
