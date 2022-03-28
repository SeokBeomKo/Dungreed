#pragma once
#include "CGameObject.h"

class CD2DImage;

class CTile : public CGameObject
{

private:
	
	CD2DImage* m_pImg;
	int m_iX;
	int m_iY;
	int m_iIdx;			// 텍스쳐 인덱스

	GROUP_TILE m_group;
	bool m_bIsPlat;

	//// 충돌체 변수
	//float tiletop, tilebottom, tileright, tileleft;
	//float playertop, playerbottom, playerright, playerleft;
	//float fInterRight, fInterLeft, fInterTop, fInterBottom;
	//float fInterH, fInterW;

public:
	const static int SIZE_TILE = 32;

	CTile();
	virtual ~CTile();

	virtual CTile* Clone();

	virtual void update();
	virtual void render();

	void SetD2DImage(CD2DImage* pTex);
	void SetImgIdx(UINT idx);
	void SetX(int x);
	void SetY(int y);
	void SetGroup(GROUP_TILE group);

	int GetIdx();
	int GetX();
	int GetY();
	GROUP_TILE GetGroup();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollision(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
};