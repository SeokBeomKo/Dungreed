#pragma once
#include "CButtonUI.h"
class CExitUI :
    public CButtonUI
{
public:
	CD2DImage* pimg;

	CExitUI();
	~CExitUI();

	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

