#include "framework.h"
#include "CEquip.h"
#include "CD2DImage.h"

#include "CPlayerAttack.h"

CEquip::CEquip()
{
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

void CEquip::SetAttackLoad(wstring strKey, wstring strPath)
{
    KeyAttack = strKey;
    PathAttack = strPath;
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

void CEquip::PlayerAttack(int code)
{
    CPlayerAttack* attack = new CPlayerAttack;
    attack->SetOwner(m_Owner);
    attack->SetPos(m_Owner->GetPos());
    attack->SetCode(code);
    attack->EnterAttack();
    CreateObj(attack, GROUP_GAMEOBJ::PLAYER_FX);
}
