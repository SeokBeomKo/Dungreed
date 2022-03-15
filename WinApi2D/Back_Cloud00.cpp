#include "framework.h"
#include "Back_Cloud00.h"
#include "CD2DImage.h"

Back_Cloud00::Back_Cloud00()
{
    pimg = new CD2DImage;
    pimg = CResourceManager::getInst()->LoadD2DImage(L"BackCloud00", L"texture\\background\\BackCloud00.png");
}

Back_Cloud00::~Back_Cloud00()
{
}

Back_Cloud00* Back_Cloud00::Clone()
{
    return new Back_Cloud00(*this);
}

void Back_Cloud00::update()
{
    fPoint pos = GetPos();

    pos.x += m_fVelocity * m_fvDir.x * fDT;
    pos.y += m_fVelocity * m_fvDir.y * fDT;

    SetPos(pos);

    SetPos(pos);

    if (pos.x < -1900.f)
    {
        SetPos(fPoint(WINSIZEX / 2 + 2500.f, WINSIZEY / 2));
    }
}

void Back_Cloud00::render()
{
    fPoint pos = GetPos();
    fPoint scale = GetScale();

    CRenderManager::getInst()->RenderImage(
        pimg,
        pos.x - scale.x / 2.f,
        pos.y - scale.y / 2.f,
        pos.x + scale.x / 2.f,
        pos.y + scale.y / 2.f
    );
}

void Back_Cloud00::Load(wstring strKey, wstring strPath)
{
    pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
