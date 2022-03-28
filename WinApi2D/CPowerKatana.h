#pragma once
#include "CItem.h"
class CPowerKatana :
    public CItem
{
public:
    CD2DImage* m_Img;

    CPowerKatana();
    ~CPowerKatana();

    virtual void render();
    virtual void update();
};
