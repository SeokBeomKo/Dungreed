#pragma once
#include "CGameObject.h"
#include "CMonsterFX.h"

class CD2DImage;
class AI;

struct tMonInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttRange;
	float fAtt;
};

enum class MON_TYPE
{
	BAT,
	BAT_RED,

	BOSS,

	SIZE,
};

class CMonster : public CGameObject
{
private:
	tMonInfo	m_tInfo;
	AI*			m_pAI;
	CD2DImage*	m_pImg;

	CMonsterFX* pFX;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);

	virtual void render();
	virtual void update();

	float GetSpeed();
	const tMonInfo& GetMonInfo();

	void Spawn();

	void SetSpeed(float speed);
	void SetAI(AI* ai);
	void SetMonInfo(const tMonInfo& info);
	void SetResource(MON_TYPE type);

	void OnCollisionEnter(CCollider* pOther);
};

