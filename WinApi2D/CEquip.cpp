#include "framework.h"
#include "CEquip.h"
#include "CD2DImage.h"

#include "CPlayerAttack.h"

CEquip::CEquip()
{
    m_Owner = nullptr;
    m_pImg = nullptr;
}

CEquip::~CEquip()
{
}

void CEquip::render()
{
    fPoint pos = GetPos();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    fPoint scale = GetScale();

    fPoint mousepos = MousePos();
    fVec2 d;
    d.x = (mousepos.x - renderpos.x);
    d.y = (mousepos.y - renderpos.y);

    float rotateDegree = atan2(d.y, d.x) * 180 / 3.141592;

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderpos.x - scale.x / 2.f,
        renderpos.y - scale.y / 2.f,
        renderpos.x + scale.x / 2.f,
        renderpos.y + scale.y / 2.f, true,
        renderpos - fPoint(40.f,0.f),
        rotateDegree
    );

    // TODO : 마우스 좌표따라 회전
    component_render();

}

void CEquip::update()
{
    fPoint pos = m_Owner->GetPos();
    fPoint realpos = CCameraManager::getInst()->GetRenderPos(pos);
    if (MousePos().x > realpos.x)
        pos.x += 50.f;
    else
        pos.x += 30.f;
    pos.y += 10.f;
    
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

void CEquip::PlayerAttack(CWeapon* _weapon)
{
    CPlayerAttack* attack = new CPlayerAttack;
    attack->SetOwner(m_Owner);
    attack->SetPos(m_Owner->GetPos());
    attack->Set(_weapon);
    attack->EnterAttack();
    CreateObj(attack, GROUP_GAMEOBJ::PLAYER_ATTACK);
}
