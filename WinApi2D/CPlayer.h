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

	// 플레이어 이동속도
	float m_fVelocity = 300;

	// 플레이어 점프횟수
	int m_jumpCount;

	// 플레이어 대쉬
	bool IsDash = false;
	bool IsDashOff = true;
	float m_dashDis = 0.f;
	fVec2 mousePos;
	fPoint playerPos;
	fVec2 dashdir;
	float m_fTimex;

	// 중력 구현
	bool GR = true;
	float m_fTime;
	float m_fGravity;

	// MoveUpdate
	float m_fSpeed = 0.f;
	bool IsJump = false;
	bool Isright = true;

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

