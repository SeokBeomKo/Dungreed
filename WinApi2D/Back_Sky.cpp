#include "framework.h"
#include "Back_Sky.h"
#include "CD2DImage.h"

Back_Sky::Back_Sky()
{
	pimg = new CD2DImage;
	pimg = CResourceManager::getInst()->LoadD2DImage(L"Back_Sky", L"texture\\background\\BackSky.png");
}

Back_Sky::~Back_Sky()
{
}

Back_Sky* Back_Sky::Clone()
{
    return nullptr;
}

void Back_Sky::update()
{
}

void Back_Sky::render()
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

void Back_Sky::Load(wstring strKey, wstring strPath)
{
    pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
