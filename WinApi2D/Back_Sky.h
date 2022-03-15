#pragma once
#include "CGameObject.h"

class Back_Sky :
    public CGameObject
{
public:
	CD2DImage* pimg;

	Back_Sky();
	~Back_Sky();

	virtual Back_Sky* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};


