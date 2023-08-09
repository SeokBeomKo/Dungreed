#pragma once
#include "CGameObject.h"

class CPlayerAttack : public CGameObject
{
private:
	CGameObject*		m_Owner;
	CD2DImage*			m_pImg;

	int					m_iDamage;			// 무기 데미지
	int					m_iRange;			// 무기 사정거리
	float				m_fTimeFX;			// 무기 이펙트 사라지는 시간
	fPoint				m_fptDirFX;			// 이펙트 위치조정을 위한 방향

	WeaponInfo			m_sInfo;
	
public:
	CPlayerAttack();
	~CPlayerAttack();

	void EnterAttack();

	virtual void update();
	virtual void render();

	void SetOwner(CGameObject* Obj);
	void Set(CWeapon* _weapon);

	int GetDamage();

	CGameObject* GetOwner();

	void OnCollisionEnter(CCollider* pOther);
};

