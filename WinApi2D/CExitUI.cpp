#include "framework.h"
#include "CExitUI.h"
#include "CD2DImage.h"

CExitUI::CExitUI()
{
	pimg = new CD2DImage;
}

CExitUI::~CExitUI()
{
}

void CExitUI::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	if (IsMouseOn())
	{
		pimg = CResourceManager::getInst()->LoadD2DImage(L"ExitOn_Kor", L"texture\\ui\\ExitOn_Kor.png");
		CRenderManager::getInst()->RenderImage(
			pimg,
			pos.x - scale.x / 2.f,
			pos.y - scale.y / 2.f,
			pos.x + scale.x / 2.f,
			pos.y + scale.y / 2.f
		);
	}
	else
	{
		pimg = CResourceManager::getInst()->LoadD2DImage(L"ExitOff_Kor", L"texture\\ui\\ExitOff_Kor.png");
		CRenderManager::getInst()->RenderImage(
			pimg,
			pos.x - scale.x / 2.f,
			pos.y - scale.y / 2.f,
			pos.x + scale.x / 2.f,
			pos.y + scale.y / 2.f
		);
	}
}

void CExitUI::Load(wstring strKey, wstring strPath)
{
	pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
