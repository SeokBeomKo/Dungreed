#include "framework.h"
#include "CMainButtonUI.h"
#include "CD2DImage.h"

CMainButtonUI::CMainButtonUI()
{
	pimg = nullptr;

	m_strOnKey	 = L"";
	m_strOnPath	 = L"";
	m_strOffKey	 = L"";
	m_strOffPath = L"";
}

CMainButtonUI::~CMainButtonUI()
{
}

void CMainButtonUI::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	if (IsMouseOn())
	{
		pimg = CResourceManager::getInst()->LoadD2DImage(m_strOnKey, m_strOnPath);
		CRenderManager::getInst()->RenderImage(
			pimg,
			pos.x,
			pos.y,
			pos.x + scale.x,
			pos.y + scale.y
		);
	}
	else
	{
		pimg = CResourceManager::getInst()->LoadD2DImage(m_strOffKey, m_strOffPath);
		CRenderManager::getInst()->RenderImage(
			pimg,
			pos.x,
			pos.y,
			pos.x + scale.x,
			pos.y + scale.y
		);
	}
}

void CMainButtonUI::Load(wstring strOffKey, wstring strOffPath, wstring strOnKey, wstring strOnPath)
{
	m_strOffKey = strOffKey;
	m_strOffPath = strOffPath;
	m_strOnKey = strOnKey;
	m_strOnPath = strOnPath;

	pimg = CResourceManager::getInst()->LoadD2DImage(strOffKey, strOffPath);
	SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
