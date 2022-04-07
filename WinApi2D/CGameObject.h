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

	// 컴포넌트
	CCollider*		m_pCollider;		// 충돌체
	CAnimator*		m_pAnimator;		// 애니메이션
	CGravity*		m_pGravity;			// 중력

	bool m_bAlive;
	void SetDead();

	// 무기 코드
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

	virtual void update() = 0;			// 반드시 상속받은 객체가 update를 구현하도록 순수가상함수로 선언
	virtual void finalupdate();			// 상속받는 클래스가 오버라이딩 할 수 없게 막는 final 키워드
	virtual void render();
	virtual void component_render();	// 컴포넌트들의 영역을 표시하기 위해

	virtual void SetMove(int right, int left) {};
	virtual void SetAllMove(int right, int left) {};
	virtual void SetJump(bool set)	{};
	virtual void SetJumpCount()		{};
	virtual void SetDash(bool set)	{};
	virtual void SetGR(bool set)	{};

	virtual int GetMoveRight()	{ return 0; };
	virtual int GetMoveLeft()	{ return 0; };
	virtual bool GetDiag()		{ return true; };

	CCollider* GetCollider();				// 충돌체 반환
	void CreateCollider();					// 충돌체 생성
	void DeleteCollider();

	CAnimator* GetAnimator();				// 애니메이터 반환
	void CreateAnimator();					// 애니메이터 생성

	CGravity* GetGravity();					// 중력 반환
	void CreateGravity();					// 중력 생성

	virtual void OnCollision(CCollider* _pOther) {}			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther) {}		// 재정의용 탈충돌 가상함수

	
};

