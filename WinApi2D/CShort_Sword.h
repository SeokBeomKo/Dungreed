#pragma once
#include "CItem.h"
class CShort_Sword :
    public CItem
{
public:
    CD2DImage* m_Img;

    CShort_Sword();
    ~CShort_Sword();

    virtual void render();
    virtual void update();
};

