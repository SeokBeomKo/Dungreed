#pragma once
#include "CGameObject.h"

class CMonster : public CGameObject
{
private:
	fPoint m_fptCenterPos;
	float m_fVelocity;
	float m_fDistance;
	bool m_bIsUPDir;

public:
	CMonster();
	~CMonster();
	virtual CMonster* Clone();

	virtual void update();

	void SetCenterPos(fPoint point);

	void OnCollisionEnter(CCollider* pOther);
};

