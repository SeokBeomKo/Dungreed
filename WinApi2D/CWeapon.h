#pragma once
#include "CItem.h"
class CWeapon :
    public CItem
{
public:

    CD2DImage* m_Img;

    CWeapon();
    ~CWeapon();

    virtual void render();
    virtual void update();



    virtual void OnCollisionEnter(CCollider* pOther);
};

