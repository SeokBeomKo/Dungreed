#include "framework.h"
#include "CMap.h"
#include "CD2DImage.h"

CMap::CMap()
{
}

CMap::~CMap()
{
}

void CMap::update()
{
}

void CMap::render()
{
    fPoint pos = fPoint(0, 0);
    fPoint scale = GetScale();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    renderpos = pos + (renderpos - pos);

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderpos.x,
        renderpos.y,
        renderpos.x + scale.x ,
        renderpos.y + scale.y 
    );
}

void CMap::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}
