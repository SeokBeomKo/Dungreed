#pragma once

#include "CGameObject.h"
#include "CEquip.h"
#include "CPlayerFX.h"

class CD2DImage;

// 함수포인터를 위한 타입정의
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);


struct PlayerSave
{
	// 상태
	int hp;
	int att;
	float attackspeed;
	int gold;
	int m_EquipCode;
};

class CPlayer : public CGameObject
{
private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

	CD2DImage* m_pImg;
	
	// 플레이어 이동
	float m_fVelocity;
	float m_fSpeed;
	float m_fRun;
	bool IsJump;
	bool Isright;
	int m_iMoveRight;
	int m_iMoveLeft;

	// 플레이어 점프횟수
	int m_jumpCount;

	// 플레이어 대쉬
	bool IsDash;
	bool IsDashLow;
	fVec2 dashdir;
	float m_fTimex;
	float time;
	bool timer;
	bool timer2;

	// 중력 구현
	bool GR;
	float m_fTime;
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
	virtual void SetJump(bool set);
	virtual void SetDash(bool set);
	virtual void SetJumpCount();
	virtual void SetGR(bool set);

	virtual void update();

	void MoveUpdate();
	void AniUpdate();
	void Equip(int code);

	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);

	void SetSteppedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);

	void SaveData(PlayerSave data);
	PlayerSave LoadData();
};

