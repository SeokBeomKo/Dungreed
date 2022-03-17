#include "framework.h"
#include "TownLayer_Day.h"
#include "CD2DImage.h"

TownLayer_Day::TownLayer_Day()
{
	m_pImg = new CD2DImage;
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"TownLayer_Day", L"texture\\background\\TownLayer_Day.png");
}

TownLayer_Day::~TownLayer_Day()
{
}

TownLayer_Day* TownLayer_Day::Clone()
{
	return nullptr;
}

void TownLayer_Day::update()
{
}

void TownLayer_Day::render()
{
    fPoint pos = fPoint(WINSIZEX / 2, WINSIZEY / 2 + 85.f);
    fPoint scale = GetScale();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    renderpos = pos + (renderpos - pos) / 2;

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderpos.x - scale.x / 2.f,
        renderpos.y - scale.y / 2.f,
        renderpos.x + scale.x / 2.f,
        renderpos.y + scale.y / 2.f
    );
}

void TownLayer_Day::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}
