#pragma once
#include "CGameObject.h"
class CEquip : public CGameObject
{
private:
    CGameObject* m_Owner;
    CD2DImage* m_pImg;

    wstring KeyAttack, PathAttack;

public:

    CEquip();
    ~CEquip();

    virtual void render();
    virtual void update();

    void SetOwner(CGameObject* Obj);
    void SetAttackLoad(wstring strKey, wstring strPath);

    CGameObject* GetOwner();

    void Load(wstring strKey, wstring strPath);

    void PlayerAttack(int code);
};

