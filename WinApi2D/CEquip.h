#pragma once
#include "CGameObject.h"
class CEquip :
    public CGameObject
{
public:
    CGameObject* m_Owner;
    CD2DImage* m_Img;

    CEquip();
    ~CEquip();

    virtual void render();
    virtual void update();

    void SetOwner(CGameObject* Obj);

    CGameObject* GetOwner();
};

