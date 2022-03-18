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

	float m_fTime;
	float m_fGravity;

	float m_fVelocity = 300;

	float m_fSpeed = 0;

	float jump = 100.f;

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
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
	

	void Load(wstring strKey, wstring strPath);
};

