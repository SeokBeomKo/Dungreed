#pragma once
#include "CGameObject.h"
class Back_Ground_Layer :
    public CGameObject
{
private:
	CD2DImage* m_pImg;

	fPoint m_fptPos;
	float m_fSpeed;

public:
	Back_Ground_Layer();
	~Back_Ground_Layer();

	virtual Back_Ground_Layer* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath, fPoint pos, float speed);
};

