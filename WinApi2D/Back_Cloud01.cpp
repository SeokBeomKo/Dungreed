#include "framework.h"
#include "Back_Cloud01.h"
#include "CD2DImage.h"

Back_Cloud01::Back_Cloud01()
{
	pimg = new CD2DImage;
	pimg = CResourceManager::getInst()->LoadD2DImage(L"BackCloud01", L"texture\\background\\BackCloud01.png");
}

Back_Cloud01::~Back_Cloud01()
{
}

Back_Cloud01* Back_Cloud01::Clone()
{
	return new Back_Cloud01(*this);
}

void Back_Cloud01::update()
{
	fPoint pos = GetPos();

	pos.x += m_fVelocity * m_fvDir.x * fDT;
	pos.y += m_fVelocity * m_fvDir.y * fDT;

	SetPos(pos);

    if (pos.x < -2300.f)
    {
        SetPos(fPoint(WINSIZEX / 2 + 2500.f, WINSIZEY / 2));
    }
}

void Back_Cloud01::render()
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

void Back_Cloud01::Load(wstring strKey, wstring strPath)
{
    pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
