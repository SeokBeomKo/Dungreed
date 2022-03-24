#pragma once
#include "CItem.h"
class CMuramasa :
    public CItem
{
public:
    CD2DImage* m_Img;

    CMuramasa();
    ~CMuramasa();

    virtual void render();
    virtual void update();
};
