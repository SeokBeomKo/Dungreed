#pragma once
#include "CGameObject.h"

class Back_Ground :
    public CGameObject
{
public:
	CD2DImage* m_pImg;

	Back_Ground();
	~Back_Ground();

	virtual Back_Ground* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};


