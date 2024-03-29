#pragma once
#include "CGameObject.h"

class CWeapon;

class CItem :
    public CGameObject
{
private:

public:
    CD2DImage* m_Img;

    wstring m_strKey;
    wstring m_strPath;

    CItem();
    CItem(wstring _key, wstring _path);
    virtual CItem* Clone() { return nullptr; };
    virtual ~CItem();

    virtual CWeapon* GetWeapon() { return nullptr; }

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

