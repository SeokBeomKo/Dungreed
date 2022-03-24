#include "framework.h"
#include "CEquip.h"
#include "CD2DImage.h"

#include "CCollider.h"

CEquip::CEquip()
{
    CreateCollider();
    GetCollider()->SetScale(fPoint(32.f, 64.f));
    GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));
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
        m_pImg,
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

void CEquip::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}
