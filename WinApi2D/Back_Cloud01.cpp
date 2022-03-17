#include "framework.h"
#include "Back_Cloud01.h"
#include "CD2DImage.h"

Back_Cloud01::Back_Cloud01()
{
    m_pImg = new CD2DImage;
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"BackCloud01", L"texture\\background\\BackCloud01.png");
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
        m_pImg,
        pos.x - scale.x / 2.f,
        pos.y - scale.y / 2.f,
        pos.x + scale.x / 2.f,
        pos.y + scale.y / 2.f
    );
}

void Back_Cloud01::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}
