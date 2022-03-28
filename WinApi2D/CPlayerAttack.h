#pragma once
#include "CGameObject.h"

class CPlayerAttack : public CGameObject
{
private:
	CGameObject*		m_Owner;
	CD2DImage*			m_pImg;

	int					m_EffectCode;
	float				time;
	fPoint				dashdir;
	int					m_iRange;			// 무기 사정거리
public:
	CPlayerAttack();
	~CPlayerAttack();

	void EnterAttack();

	virtual void update();
	virtual void render();

	void SetOwner(CGameObject* Obj);
	void SetCode(int code);

	CGameObject* GetOwner();

	void OnCollisionEnter(CCollider* pOther);
};

