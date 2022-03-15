#pragma once
#include "CGameObject.h"

class CD2DImage;

class Back_Cloud00 : public CGameObject
{
private:
	fVec2 m_fvDir = fVec2(-1, 0);
	float m_fVelocity = 15.f;

public:
	CD2DImage* pimg;

	Back_Cloud00();
	~Back_Cloud00();

	virtual Back_Cloud00* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

