#include "framework.h"
#include "CTile.h"
#include "CGameObject.h"
#include "CD2DImage.h"

#include "CCollider.h"
#include "CGravity.h"

CTile::CTile()
{
	m_pImg = nullptr;
	m_iX = 0;
	m_iY = 0;
	m_iIdx = 0;
	m_group = GROUP_TILE::NONE;
	SetScale(fPoint(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}

CTile* CTile::Clone()
{
	return new CTile(*this);
}

void CTile::update()
{
}

void CTile::render()
{
	if (nullptr == m_pImg)
	{
		return;
	}

	UINT iWidth = m_pImg->GetWidth();
	UINT iHeight = m_pImg->GetHeight();

	UINT iMaxRow = iHeight / SIZE_TILE;
	UINT iMaxCol = iWidth / SIZE_TILE;

	UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
	UINT iCurCol = (m_iIdx % iMaxCol);

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos());
	fPoint fptScale = GetScale();

	if (0 != m_iIdx)
	{
		CRenderManager::getInst()->RenderFrame(
			m_pImg,
			fptRenderPos.x,
			fptRenderPos.y,
			fptRenderPos.x + fptScale.x,
			fptRenderPos.y + fptScale.y,
			iCurCol * fptScale.x,
			iCurRow * fptScale.y,
			(iCurCol + 1) * fptScale.x,
			(iCurRow + 1) * fptScale.y
		);
	}

	component_render();
}

void CTile::SetD2DImage(CD2DImage* pImg)
{
	m_pImg = pImg;
}

void CTile::SetImgIdx(UINT idx)
{
	m_iIdx = idx;
}

void CTile::SetX(int x)
{
	m_iX = x;
}

void CTile::SetY(int y)
{
	m_iY = y;
}

void CTile::SetGroup(GROUP_TILE group)
{
	m_group = group;
}

int CTile::GetIdx()
{
	return m_iIdx;
}

int CTile::GetX()
{
	return m_iX;
}

int CTile::GetY()
{
	return m_iY;
}

GROUP_TILE CTile::GetGroup()
{
	return m_group;
}

void CTile::Save(FILE* pFile)
{
	fwrite(&m_iX, sizeof(int), 1, pFile);
	fwrite(&m_iY, sizeof(int), 1, pFile);
	fwrite(&m_iIdx, sizeof(int), 1, pFile);

	int group = (int)m_group;
	fwrite(&group, sizeof(int), 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_iX, sizeof(int), 1, pFile);
	fread(&m_iY, sizeof(int), 1, pFile);
	fread(&m_iIdx, sizeof(int), 1, pFile);

	int group;
	fread(&group, sizeof(int), 1, pFile);
	m_group = (GROUP_TILE)group;
}

void CTile::OnCollisionEnter(CCollider* pOther)
{
	if (pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER)
	{
		pOther->GetObj()->GetGravity();

		fPoint pos = pOther->GetObj()->GetPos();

		fPoint vPlayerPos = pOther->GetObj()->GetCollider()->GetFinalPos();
		fPoint vPlayerScale = pOther->GetObj()->GetCollider()->GetScale();

		fPoint vTilePos = GetCollider()->GetFinalPos();
		fPoint vTileScale = GetCollider()->GetScale();

		float fLen = abs(vPlayerPos.y - vTilePos.y);
		float fValue = (vPlayerScale.y / 2.f + vTileScale.y / 2.f) - fLen;

		pos.y -= fValue;

		pOther->GetObj()->SetPos(pos);
	}
}

void CTile::OnCollision(CCollider* pOther)
{
	if (pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER || 
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PAYER_WEAPON)
	{
		pOther->GetObj()->GetGravity();
		
		fPoint pos = pOther->GetObj()->GetPos();

		fPoint vPlayerPos = pOther->GetObj()->GetCollider()->GetFinalPos();
		fPoint vPlayerScale = pOther->GetObj()->GetCollider()->GetScale();

		fPoint vTilePos = GetCollider()->GetFinalPos();
		fPoint vTileScale = GetCollider()->GetScale();

		float fLen = abs(vPlayerPos.y - vTilePos.y);
		float fValue = (vPlayerScale.y / 2.f + vTileScale.y / 2.f) - fLen;

		pos.y -= fValue;

		pOther->GetObj()->SetPos(pos);
	}
}

void CTile::OnCollisionExit(CCollider* pOther)
{
}
