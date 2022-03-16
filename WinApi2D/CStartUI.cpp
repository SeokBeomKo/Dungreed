#include "framework.h"
#include "CStartUI.h"
#include "CD2DImage.h"

CStartUI::CStartUI()
	: CUI(false)
{
	m_pFunc = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;

	pimg = new CD2DImage;
	pimg = CResourceManager::getInst()->LoadD2DImage(L"PlayOff_Kor", L"texture\\ui\\PlayOff_Kor.png");
}

CStartUI::~CStartUI()
{
}

CStartUI* CStartUI::Clone()
{
	return new CStartUI(*this);
}

void CStartUI::render()
{
	fPoint pos = fPoint(WINSIZEX / 2, WINSIZEY / 2 + 100.f);
	fPoint scale = GetScale();

	CRenderManager::getInst()->RenderImage(
		pimg,
		pos.x - scale.x / 2.f,
		pos.y - scale.y / 2.f,
		pos.x + scale.x / 2.f,
		pos.y + scale.y / 2.f
	);
	
}

void CStartUI::MouseOn()
{
}

void CStartUI::MouseLbtnDown()
{
}

void CStartUI::MouseLbtnUp()
{
}

void CStartUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

void CStartUI::SetClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}

void CStartUI::Load(wstring strKey, wstring strPath)
{
	pimg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
