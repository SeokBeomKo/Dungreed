#pragma once
#include "CGameObject.h"
class CEquip :
    public CGameObject
{
public:
    CGameObject* m_Owner;
    CD2DImage* m_pImg;

    CEquip();
    ~CEquip();

    virtual void render();
    virtual void update();

    void SetOwner(CGameObject* Obj);

    CGameObject* GetOwner();

    void Load(wstring strKey, wstring strPath);
};

