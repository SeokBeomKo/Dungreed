#pragma once

#include "CGameObject.h"
#include "CEquip.h"

class CD2DImage;

// 함수포인터를 위한 타입정의
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CPlayer : public CGameObject
{
private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

	CD2DImage* m_pImg;
	
	// 플레이어 이동속도
	float m_fVelocity;

	// 플레이어 점프횟수
	int m_jumpCount;

	// 플레이어 대쉬
	bool IsDash;
	bool IsDashLow;
	fVec2 mousePos;
	fPoint playerPos;
	fVec2 dashdir;
	float m_fTimex;

	// 중력 구현
	bool GR;
	float m_fTime;
	float m_fGravity;

	// MoveUpdate
	float m_fSpeed;
	bool IsJump;
	bool Isright;

	// 무기
	CEquip* pEquip;
	bool IsEquip;

	// 상태
	int hp;

	// 저장
	CPlayer* m_data;

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();

	void MoveUpdate();
	void AniUpdate();
	void Equip(wstring strKey = nullptr, wstring strPath = nullptr);

	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);

	void SetSteppedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);

	void SaveData(CPlayer* data);
	CPlayer* LoadData();
};

