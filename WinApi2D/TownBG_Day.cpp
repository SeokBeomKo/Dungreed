#include "framework.h"
#include "TownBG_Day.h"
#include "CD2DImage.h"

TownBG_Day::TownBG_Day()
{
	m_pImg = new CD2DImage;
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"TownBG_Day", L"texture\\background\\TownBG_Day.png");
}

TownBG_Day::~TownBG_Day()
{
}

TownBG_Day* TownBG_Day::Clone()
{
    return new TownBG_Day(*this);
}

void TownBG_Day::update()
{
}

void TownBG_Day::render()
{
    fPoint pos = fPoint(WINSIZEX / 2, WINSIZEY / 2 + 38.f);
    fPoint scale = GetScale();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    renderpos = pos + (renderpos - pos) / 7;

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderpos.x - scale.x / 2.f,
        renderpos.y - scale.y / 2.f,
        renderpos.x + scale.x / 2.f,
        renderpos.y + scale.y / 2.f
    );
}

void TownBG_Day::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}
