#include "framework.h"
#include "Sky_Day.h"
#include "CD2DImage.h"

Sky_Day::Sky_Day()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"Sky_Day", L"texture\\background\\Sky_Day.png");
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}

Sky_Day::~Sky_Day()
{
}

Sky_Day* Sky_Day::Clone()
{
    return nullptr;
}

void Sky_Day::update()
{
}

void Sky_Day::render()
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

void Sky_Day::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}