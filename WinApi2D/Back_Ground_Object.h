#pragma once
#include "CGameObject.h"

class CD2DImage;

class Back_Ground_Object : public CGameObject
{
private:
	fVec2 m_fvDir = fVec2(-1, 0);	// 움직이는 방향
	float m_fVelocity;				// 움직이는 속도

	float m_fSetReturn;				// 리턴 시작할 위치
	float m_fGetReturn;				// 리턴 할 위치

public:
	CD2DImage* m_pImg;

	Back_Ground_Object();
	~Back_Ground_Object();

	virtual Back_Ground_Object* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath, float velo, float setre, float getre);
};

