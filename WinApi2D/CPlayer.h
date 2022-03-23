#pragma once

#include "CGameObject.h"
#include "CEquip.h"

class CD2DImage;

// �Լ������͸� ���� Ÿ������
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CPlayer : public CGameObject
{
private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

	CD2DImage* m_pImg;
	
	// �÷��̾� �̵��ӵ�
	float m_fVelocity = 300;

	// �÷��̾� ����Ƚ��
	int m_jumpCount;

	// �÷��̾� �뽬
	bool IsDash = false;
	bool IsDashLow = false;
	fVec2 mousePos;
	fPoint playerPos;
	fVec2 dashdir;
	float m_fTimex;

	// �߷� ����
	bool GR = true;
	float m_fTime;
	float m_fGravity;

	// MoveUpdate
	float m_fSpeed = 0.f;
	bool IsJump = false;
	bool Isright = true;

	// ����
	CEquip* pEquip;
	bool IsEquip = false;
	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();

	void SetPlayer();

	void MoveUpdate();
	void AniUpdate();
	void Equip();

	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);

	void Load(wstring strKey, wstring strPath);

	void SetSteppedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);

};

