#pragma once
#include "CGameObject.h"

class Back_Ground :
    public CGameObject
{
private:
	CD2DImage* m_pImg;

public:
	Back_Ground();
	~Back_Ground();

	virtual Back_Ground* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};


