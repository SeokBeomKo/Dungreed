#pragma once

#include "CGameObject.h"
#include "CEquip.h"

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
	bool IsDashLow = false;
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

	// 무기
	CEquip* pEquip;
	bool IsEquip = false;
	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();

	void MoveUpdate();
	void AniUpdate();
	void Equip();

	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
	

	void Load(wstring strKey, wstring strPath);
};

