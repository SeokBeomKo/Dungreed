#pragma once

#include "CGameObject.h"
#include "CEquip.h"

class CD2DImage;

// �Լ������͸� ���� Ÿ������
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);


struct PlayerSave
{
	// ����
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
	
	// �÷��̾� �̵��ӵ�
	float m_fVelocity;

	// �÷��̾� ����Ƚ��
	int m_jumpCount;

	// �÷��̾� �뽬
	bool IsDash;
	bool IsDashLow;
	fVec2 mousePos;
	fPoint playerPos;
	fVec2 dashdir;
	float m_fTimex;

	// �߷� ����
	bool GR;
	float m_fTime;
	float m_fGravity;

	// MoveUpdate
	float m_fSpeed;
	bool IsJump;
	bool Isright;

	// ����
	CEquip* pEquip;
	bool IsEquip;
	
	PlayerSave m_Savedata;

	// ����
	CPlayer* m_data;

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void SetJump(bool set);
	virtual void SetDash(bool set);
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

