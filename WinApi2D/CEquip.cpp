#include "framework.h"
#include "CEquip.h"
#include "CD2DImage.h"

CEquip::CEquip()
{
    m_Img = CResourceManager::getInst()->LoadD2DImage(L"Short_Sword", L"texture\\weapon\\ShortSword.png");
    SetScale(fPoint(m_Img->GetWidth() * 4.f, m_Img->GetHeight() * 4.f));
    //SetPos(m_Owner->GetPos());
    SetPos(fPoint(100.f, 100.f));
    SetName(L"Short_Sword");
    SetObjGroup(GROUP_GAMEOBJ::PAYER_WEAPON);

    // TODO
}

CEquip::~CEquip()
{
}

void CEquip::render()
{
    fPoint pos = GetPos();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    fPoint scale = GetScale();
    
    CRenderManager::getInst()->RenderImage(
        m_Img,
        renderpos.x - scale.x / 2.f,
        renderpos.y - scale.y / 2.f,
        renderpos.x + scale.x / 2.f,
        renderpos.y + scale.y / 2.f, true
    );

    //CRenderManager::getInst()->GetRenderTarget()->SetTransform();
    // TODO : 마우스 좌표따라 회전
    component_render();

}

void CEquip::update()
{
    fPoint pos = m_Owner->GetPos();
    pos.x += 50.f;
    
    // TODO : 마우스 좌표따라 회전

    SetPos(pos);
}

void CEquip::SetOwner(CGameObject* Obj)
{
    m_Owner = Obj;
}

CGameObject* CEquip::GetOwner()
{
    return m_Owner;
}
