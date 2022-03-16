#include "framework.h"
#include "Sky_Day.h"
#include "CD2DImage.h"

Sky_Day::Sky_Day()
{
    pimg = new CD2DImage;
    pimg = CResourceManager::getInst()->LoadD2DImage(L"Sky_Day", L"texture\\background\\Sky_Day.png");
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
        pimg,
        pos.x - scale.x / 2.f,
        pos.y - scale.y / 2.f,
        pos.x + scale.x / 2.f,
        pos.y + scale.y / 2.f
    );
}

void Sky_Day::Load(wstring strKey, wstring strPath)
{
    pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}