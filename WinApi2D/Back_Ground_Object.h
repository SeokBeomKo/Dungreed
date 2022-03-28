#pragma once
#include "CGameObject.h"

class CD2DImage;

class Back_Ground_Object : public CGameObject
{
private:
	fVec2 m_fvDir = fVec2(-1, 0);	// �����̴� ����
	float m_fVelocity;				// �����̴� �ӵ�

	float m_fSetReturn;				// ���� ������ ��ġ
	float m_fGetReturn;				// ���� �� ��ġ

public:
	CD2DImage* m_pImg;

	Back_Ground_Object();
	~Back_Ground_Object();

	virtual Back_Ground_Object* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath, float velo, float setre, float getre);
};

