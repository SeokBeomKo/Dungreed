#pragma once
#include "CGameObject.h"

class CMonsterFX :
    public CGameObject
{
private:

    CD2DImage* m_pImg;

    float           time;       // 재생시간 재기
    float           limit;      // 재생시간 한도

protected:
    CGameObject* m_Owner;

    void CreateFX(CGameObject* Obj, wstring state);

public:
    CMonsterFX();
    ~CMonsterFX();

    void PlayFX(CGameObject* Obj, wstring state);

    virtual void update();
    virtual void render();
};

