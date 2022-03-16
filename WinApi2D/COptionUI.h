#pragma once
#include "CButtonUI.h"
class COptionUI :
    public CButtonUI
{
public:
	CD2DImage* pimg;

	COptionUI();
	~COptionUI();

	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

