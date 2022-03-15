#pragma once
#include "CGameObject.h"
class MainLogo :
    public CGameObject
{
public:
	CD2DImage* pimg;

	MainLogo();
	~MainLogo();

	virtual MainLogo* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

