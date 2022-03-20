#pragma once
#include "CGameObject.h"
class CItem :
    public CGameObject
{
private:

public:
    CItem();
    virtual ~CItem();

	virtual CItem* Clone();

	
};

