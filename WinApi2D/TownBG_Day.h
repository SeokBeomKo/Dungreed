#pragma once
#include "CGameObject.h"
class TownBG_Day :
    public CGameObject
{
public:
	CD2DImage* m_pImg;

	TownBG_Day();
	~TownBG_Day();

	virtual TownBG_Day* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

