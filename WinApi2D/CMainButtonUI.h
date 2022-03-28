#pragma once
#include "CButtonUI.h"
class CMainButtonUI :
    public CButtonUI
{
private:
	CD2DImage* pimg;
	wstring m_strOnKey, m_strOnPath;		// 마우스가 올려졌을 경우 경로
	wstring m_strOffKey, m_strOffPath;		// 마우스가 올려지지 않았을 경우 경로
public:
	CMainButtonUI();
	~CMainButtonUI();

	virtual void render();

	void Load(wstring strOffKey, wstring strOffPath, wstring strOnKey, wstring strOnPath);
};

