#pragma once

class CCollider;
class CAnimator;
class CGravity;
class CPlayer;


class CGameObject
{
	friend class CEventManager;

private:
	wstring			m_strName;
	fPoint			m_fptPos;
	fPoint			m_fptScale;

	GROUP_GAMEOBJ	m_Group;
	GROUP_TILE		m_TileGroup;

	// ������Ʈ
	CCollider*		m_pCollider;		// �浹ü
	CAnimator*		m_pAnimator;		// �ִϸ��̼�
	CGravity*		m_pGravity;			// �߷�

	bool m_bAlive;
	void SetDead();

	// ���� �ڵ�
	int m_ItemCode = 0;

public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual ~CGameObject();
	virtual CGameObject* Clone() { return nullptr; };

	void SetPos(fPoint pos);
	void SetPosX(float x);
	void SetPosY(float y);
	void SetScale(fPoint scale);
	void SetName(wstring name);
	void SetObjGroup(GROUP_GAMEOBJ group);
	void SetTileGroup(GROUP_TILE group);
	void SetItemCode(int code);

	fPoint GetPos();
	fPoint GetScale();
	wstring GetName();
	GROUP_GAMEOBJ GetObjGroup();
	GROUP_TILE GetTileGroup();
	int GetItemCode();

	bool isDead();

	virtual void update() = 0;			// �ݵ�� ��ӹ��� ��ü�� update�� �����ϵ��� ���������Լ��� ����
	virtual void finalupdate();			// ��ӹ޴� Ŭ������ �������̵� �� �� ���� ���� final Ű����
	virtual void render();
	virtual void component_render();	// ������Ʈ���� ������ ǥ���ϱ� ����

	virtual void SetMove(int right, int left) {};
	virtual void SetAllMove(int right, int left) {};
	virtual void SetJump(bool set)	{};
	virtual void SetJumpCount()		{};
	virtual void SetDash(bool set)	{};
	virtual void SetGR(bool set)	{};

	virtual int GetMoveRight()	{ return 0; };
	virtual int GetMoveLeft()	{ return 0; };
	virtual bool GetDiag()		{ return true; };

	CCollider* GetCollider();				// �浹ü ��ȯ
	void CreateCollider();					// �浹ü ����
	void DeleteCollider();

	CAnimator* GetAnimator();				// �ִϸ����� ��ȯ
	void CreateAnimator();					// �ִϸ����� ����

	CGravity* GetGravity();					// �߷� ��ȯ
	void CreateGravity();					// �߷� ����

	virtual void OnCollision(CCollider* _pOther) {}			// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther) {}		// �����ǿ� Ż�浹 �����Լ�

	
};

