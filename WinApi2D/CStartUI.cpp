#include "framework.h"
#include "CStartUI.h"
#include "CD2DImage.h"

CStartUI::CStartUI()
{
	pimg = new CD2DImage;
}

CStartUI::~CStartUI()
{
}

void CStartUI::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	if (IsMouseOn())
	{
		pimg = CResourceManager::getInst()->LoadD2DImage(L"PlayOn_Kor", L"texture\\ui\\PlayOn_Kor.png");
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
		pimg = CResourceManager::getInst()->LoadD2DImage(L"PlayOff_Kor", L"texture\\ui\\PlayOff_Kor.png");
		CRenderManager::getInst()->RenderImage(
			pimg,
			pos.x,
			pos.y,
			pos.x + scale.x,
			pos.y + scale.y
		);
	}
}

void CStartUI::Load(wstring strKey, wstring strPath)
{
	pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(pimg->GetWidth() * 4, pimg->GetHeight() * 4));
}
