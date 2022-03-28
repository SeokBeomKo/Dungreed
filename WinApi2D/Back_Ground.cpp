#include "framework.h"
#include "Back_Ground.h"
#include "CD2DImage.h"

Back_Ground::Back_Ground()
{
}

Back_Ground::~Back_Ground()
{
}

Back_Ground* Back_Ground::Clone()
{
    return nullptr;
}

void Back_Ground::update()
{
}

void Back_Ground::render()
{
    fPoint pos = fPoint(WINSIZEX / 2, WINSIZEY / 2);
    fPoint scale = GetScale();

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        pos.x - scale.x / 2.f,
        pos.y - scale.y / 2.f,
        pos.x + scale.x / 2.f,
        pos.y + scale.y / 2.f
    );
}

void Back_Ground::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}
