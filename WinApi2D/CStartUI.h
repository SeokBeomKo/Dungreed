#pragma once
#include "CButtonUI.h"
class CStartUI :
    public CButtonUI
{
public:
	CD2DImage* pimg;

	CStartUI();
	~CStartUI();

	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

