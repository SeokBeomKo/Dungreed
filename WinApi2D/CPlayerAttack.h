#pragma once
#include "CGameObject.h"

class CPlayerAttack : public CGameObject
{
private:
	CGameObject*		m_Owner;
	CD2DImage*			m_pImg;

	int					m_EffectCode;		// ���� �ڵ�
	int					m_iDamage;			// ���� ������
	int					m_iRange;			// ���� �����Ÿ�
	float				m_fTimeFX;			// ���� ����Ʈ ������� �ð�
	fPoint				m_fptDirFX;			// ����Ʈ ��ġ������ ���� ����
	
public:
	CPlayerAttack();
	~CPlayerAttack();

	void EnterAttack();

	virtual void update();
	virtual void render();

	void SetOwner(CGameObject* Obj);
	void SetCode(int code);

	int GetDamage();

	CGameObject* GetOwner();

	void OnCollisionEnter(CCollider* pOther);
};

