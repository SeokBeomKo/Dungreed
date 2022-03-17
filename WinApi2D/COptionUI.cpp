#include "framework.h"
#include "COptionUI.h"
#include "CD2DImage.h"

COptionUI::COptionUI()
{
	pimg = new CD2DImage;
}

COptionUI::~COptionUI()
{
}

void COptionUI::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	if (IsMouseOn())
	{
		pimg = CResourceManager::getInst()->LoadD2DImage(L"OptionOn_Kor", L"texture\\ui\\OptionOn_Kor.png");
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
		pimg = CResourceManager::getInst()->LoadD2DImage(L"OptionOff_Kor", L"texture\\ui\\OptionOff_Kor.png");
		CRenderManager::getInst()->RenderImage(
			pimg,
			pos.x,
			pos.y,
			pos.x + scale.x,
			pos.y + scale.y
		);
	}
}

void COptionUI::Load(wstring strKey, wstring strPath)
{
	pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
