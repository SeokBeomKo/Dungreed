#pragma once
#include "CGameObject.h"
    
class CMap : public CGameObject
{
private:
    CD2DImage* m_pImg;

public:
    CMap();
    ~CMap();

    virtual void update();
    virtual void render();

    void Load(wstring strKey, wstring strPath);

};

