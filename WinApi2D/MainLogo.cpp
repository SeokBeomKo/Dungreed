#include "framework.h"
#include "MainLogo.h"
#include "CD2DImage.h"

MainLogo::MainLogo()
{
    pimg = nullptr;
}

MainLogo::~MainLogo()
{
}

MainLogo* MainLogo::Clone()
{
	return nullptr;
}

void MainLogo::update()
{
}

void MainLogo::render()
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

void MainLogo::Load(wstring strKey, wstring strPath)
{
    pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
