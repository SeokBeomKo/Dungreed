#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"

class CUICursor : public CGameObject
{
private:
    CD2DImage* m_pImg;

public:

    CUICursor();
    ~CUICursor();

    void update();
    void render();

    void Load(wstring strKey, wstring strPath);
};

