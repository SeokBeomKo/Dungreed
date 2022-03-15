#pragma once
#include "CGameObject.h"

class CD2DImage;

class Back_Cloud01 : public CGameObject
{
private:
	fVec2 m_fvDir = fVec2(-1, 0);
	float m_fVelocity = 80.f;

public:
	CD2DImage* pimg;

	Back_Cloud01();
	~Back_Cloud01();

	virtual Back_Cloud01* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};