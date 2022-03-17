#pragma once
#include "CGameObject.h"
class TownLayer_Day :
    public CGameObject
{
public:
	CD2DImage* m_pImg;

	TownLayer_Day();
	~TownLayer_Day();

	virtual TownLayer_Day* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

