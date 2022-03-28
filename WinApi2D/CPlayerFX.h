#pragma once
#include "CGameObject.h"
#include <wincrypt.h>
class CPlayerFX :
    public CGameObject
{
private:
    
    CD2DImage*      m_pImg;

    float           time;       // 재생시간 재기
    float           limit;      // 재생시간 한도

protected:
    CGameObject*    m_Owner;

    void CreateFX(CGameObject* Obj, wstring state);

public:
    CPlayerFX();
    ~CPlayerFX();
   
    void PlayFX(CGameObject* Obj, wstring state);

    virtual void update();
    virtual void render();
};

