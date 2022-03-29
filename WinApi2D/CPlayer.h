#pragma once

#include "CGameObject.h"
#include "CEquip.h"
#include "CPlayerFX.h"

class CD2DImage;


struct PlayerSave
{
	// 상태
	int hp;
	int gold;
	int m_EquipCode;
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;

	CD2DImage* m_pImg;
	
	// 플레이어 이동
	float m_fVelocity;
	float m_fSpeed;
	float m_fRunFX;				// 달리기 이펙트
	float m_fRunSound;			// 달리기 사운드
	bool IsJump;
	bool Isright;
	int m_iMoveRight;
	int m_iMoveLeft;

	// 플레이어 점프횟수
	int m_jumpCount;

	// 플레이어 대쉬
	bool IsDash;
	bool IsDashLow;			
	fVec2 dashdir;				// 대쉬 사용시 이동할 방향
	fPoint m_fptMousePos;		// 대쉬 입력 당시 마우스 좌표
	float m_fDashTime;
	bool m_bTimer;
	bool m_bTimer2;

	// 중력 구현
	bool m_bIsGravity;
	bool m_bIsPlat;
	float m_fTime;				
	float m_fTimex;
	float m_fGravity;

	// 무기
	CEquip* pEquip;
	bool IsEquip;

	CPlayerFX* pFX;

	// 저장
	PlayerSave m_Savedata;

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void SetMove(int right, int left);
	virtual void SetAllMove(int right, int left);
	virtual void SetJump(bool set);
	virtual void SetDash(bool set);
	virtual void SetJumpCount();
	virtual void SetGR(bool set);

	void RegisterPlayer();
	static CPlayer* GetPlayer();

	virtual int GetMoveRight();
	virtual int GetMoveLeft();

	virtual void update();

	void MoveUpdate();
	void AniUpdate();
	void Equip(int code);

	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);

	void SaveData(PlayerSave data);
	PlayerSave LoadData();
};

