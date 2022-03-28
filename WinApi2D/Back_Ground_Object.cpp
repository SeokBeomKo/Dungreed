#include "framework.h"
#include "Back_Ground_Object.h"
#include "CD2DImage.h"

Back_Ground_Object::Back_Ground_Object()
{
    m_pImg          = nullptr;
    m_fVelocity     = 0.f;

    m_fSetReturn    = 0.f;
    m_fGetReturn    = 0.f;
}

Back_Ground_Object::~Back_Ground_Object()
{
}

Back_Ground_Object* Back_Ground_Object::Clone()
{
    return new Back_Ground_Object(*this);
}

void Back_Ground_Object::update()
{
    fPoint pos = GetPos();

    pos.x += m_fVelocity * m_fvDir.x * fDT;
    pos.y += m_fVelocity * m_fvDir.y * fDT;

    SetPos(pos);

    if (pos.x < m_fSetReturn)
    {
        SetPos(fPoint(WINSIZEX / 2 + m_fGetReturn, WINSIZEY / 2));
    }
}

void Back_Ground_Object::render()
{
    fPoint pos = GetPos();
    fPoint scale = GetScale();

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        pos.x - scale.x / 2.f,
        pos.y - scale.y / 2.f,
        pos.x + scale.x / 2.f,
        pos.y + scale.y / 2.f
    );
}

void Back_Ground_Object::Load(wstring strKey, wstring strPath, float velo, float setre, float getre)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
    m_fVelocity = velo;
    m_fSetReturn = setre;
    m_fGetReturn = getre;
}
