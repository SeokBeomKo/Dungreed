#pragma once
#include "CButtonUI.h"
class CStartUI :
    public CButtonUI
{
private:
	bool m_pMouseon;

public:
	CD2DImage* pimg;

	CStartUI();
	~CStartUI();

	virtual void render();

	void MouseOnCheck();

	void Load(wstring strKey, wstring strPath);
};

