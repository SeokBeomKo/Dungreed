#include "framework.h"
#include "Back_Ground_Layer.h"
#include "CD2DImage.h"

Back_Ground_Layer::Back_Ground_Layer()
{
    m_pImg      = nullptr;
    m_fptPos    = fPoint(0, 0);
    m_fSpeed    = 0.f;
}

Back_Ground_Layer::~Back_Ground_Layer()
{
}

Back_Ground_Layer* Back_Ground_Layer::Clone()
{
	return nullptr;
}

void Back_Ground_Layer::update()
{
}

void Back_Ground_Layer::render()
{
    fPoint pos = fPoint(m_fptPos.x, m_fptPos.y);
    fPoint scale = GetScale();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    renderpos = pos + (renderpos - pos) / m_fSpeed;

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderpos.x,
        renderpos.y,
        renderpos.x + scale.x,
        renderpos.y + scale.y
    );
}

void Back_Ground_Layer::Load(wstring strKey, wstring strPath, fPoint pos, float speed)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
    m_fptPos = pos;
    m_fSpeed = speed;
}

