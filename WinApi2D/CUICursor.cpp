#include "framework.h"
#include "CUICursor.h"
#include "CD2DImage.h"

CUICursor::CUICursor()
{
    m_pImg = nullptr;
}

CUICursor::~CUICursor()
{
}

void CUICursor::update()
{
    fPoint m_fMousePos = MousePos();

    SetPos(m_fMousePos);
}

void CUICursor::render()
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

void CUICursor::Load(wstring strKey, wstring strPath)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(m_pImg->GetWidth() * 3.5f, m_pImg->GetHeight() * 3.5f));
}
