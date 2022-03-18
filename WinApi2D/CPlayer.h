#pragma once

#include "CGameObject.h"

class CD2DImage;

class CPlayer : public CGameObject
{
private:
	CD2DImage* m_pImg;
	CD2DImage* m_pImg2;
	CD2DImage* m_pImg3;
	CD2DImage* m_pImg4;

	float m_fTime = 0.f;

	float m_fVelocity = 300;

	float m_fSpeed = 0;
	bool IsJump = false;
	bool Isright = true;

	bool GR = true;

	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();

	void MoveUpdate();
	void AniUpdate();
	
	virtual void render();
	virtual void OnCollision(CCollider* pOther);
	

	void Load(wstring strKey, wstring strPath);
};

