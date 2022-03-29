#pragma once
#include "CGameObject.h"
class CDoor :
    public CGameObject
{
private:
	GROUP_SCENE* pScene;

public:
	CDoor();
	virtual ~CDoor();

	virtual void update();

	void SetNextScene(GROUP_SCENE next);

	virtual void OnCollisionEnter(CCollider* pOther);	// 재정의용 충돌시 가상함수
};
