#include "framework.h"
#include "MainLogo.h"
#include "CD2DImage.h"

MainLogo::MainLogo()
{
	pimg = new CD2DImage;
	pimg = CResourceManager::getInst()->LoadD2DImage(L"MainLogo", L"texture\\background\\MainLogo.png");
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
    fPoint pos = fPoint(WINSIZEX / 2, WINSIZEY / 2 - 125.f);
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
