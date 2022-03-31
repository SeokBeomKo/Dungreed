#pragma once

#include "CGameObject.h"
#include "CEquip.h"
#include "CPlayerFX.h"

class CD2DImage;


struct PlayerSave
{
	// �÷��̾� ����
	int hp;				// ü��
	int gold;			// ���
	int m_EquipCode;	// �����ϰ��ִ� ����
};

struct PlayerMove
{
	// �÷��̾� �̵�
	float m_fVelocity;			// �÷��̾� �̵��ӵ�
	float m_fRunFX;				// �޸��� ����Ʈ ����
	float m_fRunSound;			// �޸��� ���� ����
	bool m_bIsMove;				// �÷��̾� �̵�������
	bool m_bIsJump;				// �÷��̾� ����������
	bool m_bIsRight;			// �ٶ󺸴� ����
	bool m_bIsFallJump;			// �Ʒ� ����
	int m_iMoveRight;			// ��Ÿ�� �������̵�
	int m_iMoveLeft;			// ��Ÿ�� �����̵�
	int m_iJumpCount;			// �÷��̾� ����Ƚ��
};

struct PlayerDash
{
	// �÷��̾� �뽬
	bool m_bIsDash;
	bool m_bDashLow;
	fVec2 m_fVDashdir;			// �뽬 ���� �̵��� ����
	fPoint m_fptMousePos;		// �뽬 �Է� ��� ���콺 ��ǥ
	float m_fDashTime;
	bool m_bTimer;				// �뽬 FX �� Ÿ�̸�
	bool m_bTimer2;				// �뽬 FX �� Ÿ�̸�
};

struct Gravity
{
	// �߷� ����
	bool m_bIsGravity;			// �߷� ���� �޴�����
	float m_fTimeY;
	float m_fTimeX;
	float m_fGravity;
};

class CPlayer : public CGameObject
{
private:
	static CPlayer* instance;

	CD2DImage* m_pImg;

	// ����
	CEquip* pEquip;
	bool m_bIsEquip;

	// �÷��̾� ����Ʈ
	CPlayerFX* pFX;

	// ����
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

