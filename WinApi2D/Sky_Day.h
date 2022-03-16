#pragma once
#include "CGameObject.h"
class Sky_Day :
    public CGameObject
{
public:
	CD2DImage* pimg;

	Sky_Day();
	~Sky_Day();

	virtual Sky_Day* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

