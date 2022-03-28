#pragma once
#include "CButtonUI.h"
class CMainButtonUI :
    public CButtonUI
{
private:
	CD2DImage* pimg;
	wstring m_strOnKey, m_strOnPath;		// ���콺�� �÷����� ��� ���
	wstring m_strOffKey, m_strOffPath;		// ���콺�� �÷����� �ʾ��� ��� ���
public:
	CMainButtonUI();
	~CMainButtonUI();

	virtual void render();

	void Load(wstring strOffKey, wstring strOffPath, wstring strOnKey, wstring strOnPath);
};

