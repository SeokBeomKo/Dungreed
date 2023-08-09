#pragma once
#include "CGameObject.h"
#include "CItem.h"

class CWeapon :
    public CItem
{
private:

public:
    WeaponInfo info;

    CWeapon();
    CWeapon(wstring _key, wstring _path, WeaponInfo _info);
    virtual CWeapon* Clone() { return nullptr; };
    virtual ~CWeapon();

    virtual CWeapon* GetWeapon() { return this; }

    virtual wstring GetKey();
    virtual wstring GetPath();

    virtual void update();
    virtual void render();

    virtual void OnCollisionEnter(CCollider* pOther);
    virtual void OnCollision(CCollider* pOther);
    virtual void OnCollisionExit(CCollider* pOther);

    virtual void SetMove(int right, int left);
    virtual void SetAllMove(int right, int left);
    virtual void SetJump(bool set);
    virtual void SetDash(bool set);
    virtual void SetJumpCount();
    virtual void SetGR(bool set);

    virtual int GetMoveRight();
    virtual int GetMoveLeft();
    virtual bool GetDiag();
};

