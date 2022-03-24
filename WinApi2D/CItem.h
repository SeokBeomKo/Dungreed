#pragma once
#include "CGameObject.h"

class CItem :
    public CGameObject
{
private:

public:
    CD2DImage* m_Img;

    CItem();
    ~CItem();

	virtual CItem* Clone();

    virtual void update();
    virtual void render();

    virtual void OnCollisionEnter(CCollider* pOther);
};

