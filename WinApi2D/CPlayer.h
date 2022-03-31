#pragma once

#include "CGameObject.h"
#include "CEquip.h"
#include "CPlayerFX.h"

class CD2DImage;


struct PlayerSave
{
	// 플레이어 정보
	int hp;				// 체력
	int gold;			// 골드
	int m_EquipCode;	// 장착하고있는 무기
};

struct PlayerMove
{
	// 플레이어 이동
	float m_fVelocity;			// 플레이어 이동속도
	float m_fRunFX;				// 달리기 이펙트 간격
	float m_fRunSound;			// 달리기 사운드 간격
	bool m_bIsMove;				// 플레이어 이동중인지
	bool m_bIsJump;				// 플레이어 점프중인지
	bool m_bIsRight;			// 바라보는 방향
	bool m_bIsFallJump;			// 아래 점프
	int m_iMoveRight;			// 벽타일 오른쪽이동
	int m_iMoveLeft;			// 벽타일 왼쪽이동
	int m_iJumpCount;			// 플레이어 점프횟수
};

struct PlayerDash
{
	// 플레이어 대쉬
	bool m_bIsDash;
	bool m_bDashLow;
	fVec2 m_fVDashdir;			// 대쉬 사용시 이동할 방향
	fPoint m_fptMousePos;		// 대쉬 입력 당시 마우스 좌표
	float m_fDashTime;
	bool m_bTimer;				// 대쉬 FX 용 타이머
	bool m_bTimer2;				// 대쉬 FX 용 타이머
};

struct Gravity
{
	// 중력 구현
	bool m_bIsGravity;			// 중력 영향 받는중지
	float m_fTimeY;
	float m_fTimeX;
	float m_fGravity;
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;

	CD2DImage* m_pImg;

	// 무기
	CEquip* pEquip;
	bool m_bIsEquip;

	// 플레이어 이펙트
	CPlayerFX* pFX;

	// 저장
	PlayerSave	m_Savedata;
	PlayerMove	m_Move;
	PlayerDash	m_Dash;
	Gravity		m_Gravity;

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
	void SetFallJump(bool set);

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

