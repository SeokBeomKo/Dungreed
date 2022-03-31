#pragma once
#include "CGameObject.h"

class CMonsterFX :
    public CGameObject
{
private:

    CD2DImage* m_pImg;

    float           time;       // ����ð� ���
    float           limit;      // ����ð� �ѵ�

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

