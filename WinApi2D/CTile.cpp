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
	if ((pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER ||
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM) &&
		this->GetTileGroup() == GROUP_TILE::GROUND)											// 그라운드 와 플레이어 , 무기
	{
		//float tiletop, tilebottom, tileright, tileleft;
		//tiletop = GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2.f;
		//tilebottom = GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2.f;
		//tileright = GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2.f;
		//tileleft = GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2.f;
		//
		//// 플레이어
		//float playertop, playerbottom, playerright, playerleft;
		//playertop = pOther->GetFinalPos().y - pOther->GetScale().y / 2.f;
		//playerbottom = pOther->GetFinalPos().y + pOther->GetScale().y / 2.f;
		//playerright = pOther->GetFinalPos().x - pOther->GetScale().x / 2.f;
		//playerleft = pOther->GetFinalPos().x + pOther->GetScale().x / 2.f;
		//
		//fPoint pos = pOther->GetObj()->GetPos();
		//
		//fPoint vPlayerPos = pOther->GetFinalPos();
		//fPoint vPlayerScale = pOther->GetScale();
		//
		//fPoint vTilePos = GetCollider()->GetFinalPos();
		//fPoint vTileScale = GetCollider()->GetScale();
		//
		//char test = ' ';
		//
		//
		//if (playerbottom - tiletop < 8.f || tilebottom - playertop < 8.f) // 위아래 기준
		//{
		//	pOther->GetObj()->GetGravity()->OnOffGravity(false);
		//	float fLen = abs(vPlayerPos.y - vTilePos.y);
		//	float fValue = (vPlayerScale.y / 2.f + vTileScale.y / 2.f) - fLen;
		//	if (tiletop < playerbottom && playerbottom < tilebottom)		// 위
		//	{
		//		test = 'up';
		//		if (fValue > 1.f)
		//			pos.y -= fValue;
		//	}
		//	else															// 아래
		//	{
		//		if (fValue > 1.f)
		//		{
		//			pos.y+= fValue;
		//			pOther->GetObj()->SetJump(false);
		//			pOther->GetObj()->SetDash(false);
		//			pOther->GetObj()->GetGravity()->OnOffGravity(true);
		//		}
		//		test = 'down';
		//	}
		//}
		//else																// 왼쪽오른쪽
		//{
		//	float fLen = abs(vPlayerPos.x - vTilePos.x);
		//	float fValue = (vPlayerScale.x / 2.f + vTileScale.x / 2.f) - fLen;
		//	if (playerright < tileright && playerleft > tileright)		// 타일 기준 왼쪽 충돌
		//	{
		//		test = 'left';
		//		if (fValue > 1.f)
		//			pos.x -= fValue;
		//	}
		//	else		// 타일 기준 오른쪽 충돌
		//	{
		//		test = 'righ';
		//		if (fValue > 1.f)
		//			pos.x += fValue;
		//	}
		//	
		//}
		//pOther->GetObj()->SetPos(pos);

		//pOther->GetObj()->GetGravity()->OnOffGravity(false);
		//if (pOther->GetFinalPos().y + pOther->GetScale().y / 2.f > GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2.f)
		//{
		//	fPoint pos = pOther->GetObj()->GetPos();
		//
		//	fPoint vPlayerPos = pOther->GetFinalPos();
		//	fPoint vPlayerScale = pOther->GetScale();
		//
		//	fPoint vTilePos = GetCollider()->GetFinalPos();
		//	fPoint vTileScale = GetCollider()->GetScale();
		//
		//	float fLen = abs(vPlayerPos.y - vTilePos.y);
		//	float fValue = (vPlayerScale.y / 2.f + vTileScale.y / 2.f) - fLen;
		//	if (vPlayerPos.y > vTilePos.y)
		//	{
		//		if (fValue > 1.f)
		//		{
		//			pos.y += fValue;
		//			pOther->GetObj()->SetJump(false);
		//			pOther->GetObj()->SetDash(false);
		//			pOther->GetObj()->GetGravity()->OnOffGravity(true);
		//		}
		//			
		//	}
		//	else
		//	{
		//		if (fValue > 1.f)
		//			pos.y -= fValue;
		//	}
		//
		//	
		//}
	}
}

void CTile::OnCollision(CCollider* pOther)
{
	if ((pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER ||
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM) &&
		this->GetTileGroup() == GROUP_TILE::GROUND)											// 그라운드 와 플레이어 , 무기
	{
		// 타일
		float tiletop, tilebottom, tileright, tileleft;
		tiletop = GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2.f;
		tilebottom = GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2.f;
		tileleft = GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2.f;
		tileright = GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2.f;

		// 플레이어
		float playertop, playerbottom, playerright, playerleft;
		playertop = pOther->GetFinalPos().y - pOther->GetScale().y / 2.f;
		playerbottom = pOther->GetFinalPos().y + pOther->GetScale().y / 2.f;
		playerleft = pOther->GetFinalPos().x - pOther->GetScale().x / 2.f;
		playerright = pOther->GetFinalPos().x + pOther->GetScale().x / 2.f;

		float fInterH = 0.f;
		float fInterW = 0.f;
		float fInterRight, fInterLeft, fInterTop, fInterBottom;

		if (playerbottom > tilebottom && playertop < tiletop)
		{
			fInterH = tilebottom - tiletop;
			//fInterBottom = tilebottom;
			//fInterTop = tiletop;
		}
		else if (playerbottom < tilebottom)
		{
			fInterH = playerbottom - tiletop;
		}
		else if (playertop > tiletop)
		{
			fInterH = tilebottom - playertop;
		}

		if (playerright > tileright && playerleft < tileleft)
		{
			fInterW = tileright - tileleft;
		}
		else if (playerright < tileright)
		{
			fInterW = playerright - tileleft;
		}
		else if (playerleft > tileleft)
		{
			fInterW = tileright - playerleft;
		}

		fPoint pos = pOther->GetObj()->GetPos();

		fPoint vPlayerPos = pOther->GetFinalPos();
		fPoint vPlayerScale = pOther->GetScale();

		fPoint vTilePos = GetCollider()->GetFinalPos();
		fPoint vTileScale = GetCollider()->GetScale();

		char test = ' ';

		if (fInterW > fInterH) // 상하 인지 좌우 인지
		{

			float fLen = abs(vPlayerPos.y - vTilePos.y);
			float fValue = (vPlayerScale.y / 2.f + vTileScale.y / 2.f) - fLen;
			if (tiletop < playerbottom && playerbottom < tilebottom)		// 위
			{
				test = 'up';
				if (fValue > 1.f)
					pos.y -= fValue;
				pOther->GetObj()->GetGravity()->OnOffGravity(false);
			}
			else															// 아래
			{
				if (fValue > 1.f)
				{
					pos.y += fValue;
				}
				pOther->GetObj()->SetJump(false);
				pOther->GetObj()->SetDash(false);
				pOther->GetObj()->GetGravity()->OnOffGravity(true);
				test = 'down';
			}
		}
		else																// 왼쪽오른쪽
		{
			float fLen = abs(vPlayerPos.x - vTilePos.x);
			float fValue = (vPlayerScale.x / 2.f + vTileScale.x / 2.f) - fLen;
			if (playerright < tileright && playerleft < tileright)		// 타일 기준 왼쪽 충돌
			{
				test = 'left';
				pos.x -= fValue;
				pOther->GetObj()->GetGravity()->OnOffGravity(true);
			}
			else if (playerright > tileright && playerleft < tileright)			// 타일 기준 오른쪽 충돌
			{
				test = 'righ';
				pos.x += fValue;
				pOther->GetObj()->GetGravity()->OnOffGravity(true);
			}
		}
		pOther->GetObj()->SetPos(pos);

		/*if (fInterW > fInterH) // 상하 인지 좌우 인지
		{

			float fLen = abs(vPlayerPos.y - vTilePos.y);
			float fValue = (vPlayerScale.y / 2.f + vTileScale.y / 2.f) - fLen;
			if (tiletop < playerbottom && playerbottom < tilebottom)		// 위
			{
				test = 'up';
				if (fValue > 1.f)
					pos.y -= fValue;
				pOther->GetObj()->GetGravity()->OnOffGravity(false);
			}
			else															// 아래
			{
				if (fValue > 1.f)
				{
					pos.y += fValue;
				}
				pOther->GetObj()->SetJump(false);
				pOther->GetObj()->SetDash(false);
				pOther->GetObj()->GetGravity()->OnOffGravity(true);
				test = 'down';
			}
		}
		else																// 왼쪽오른쪽
		{
			float fLen = abs(vPlayerPos.x - vTilePos.x);
			float fValue = (vPlayerScale.x / 2.f + vTileScale.x / 2.f) - fLen;
			if (playerright < tileright && playerleft < tileright)		// 타일 기준 왼쪽 충돌
			{
				test = 'left';
				pos.x -= fValue;
				pOther->GetObj()->GetGravity()->OnOffGravity(true);
			}
			else if (playerright > tileright && playerleft < tileright)			// 타일 기준 오른쪽 충돌
			{
				test = 'righ';
				pos.x += fValue;
				pOther->GetObj()->GetGravity()->OnOffGravity(true);
			}
		}
		pOther->GetObj()->SetPos(pos);*/

		//if (pOther->GetFinalPos().y + pOther->GetScale().y / 2.f > GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y/2.f)
		//{
		//	fPoint pos = pOther->GetObj()->GetPos();
		//	pOther->GetObj()->GetGravity()->OnOffGravity(false);
		//
		//	fPoint vPlayerPos = pOther->GetFinalPos();
		//	fPoint vPlayerScale = pOther->GetScale();
		//
		//	fPoint vTilePos = GetCollider()->GetFinalPos();
		//	fPoint vTileScale = GetCollider()->GetScale();
		//
		//	float fLen = abs(vPlayerPos.y - vTilePos.y);
		//	float fValue = (vPlayerScale.y / 2.f + vTileScale.y / 2.f) - fLen;
		//
		//	if (vPlayerPos.y > vTilePos.y)
		//	{
		//		if (fValue > 1.f)
		//		{
		//			pos.y += fValue;
		//			pOther->GetObj()->SetJump(false);
		//			pOther->GetObj()->GetGravity()->OnOffGravity(true);
		//		}
		//	}
		//	else
		//	{
		//		if (fValue > 1.f)
		//			pos.y -= fValue;
		//	}
		//}
		//
		//pOther->GetObj()->SetPos(pos);

	}
}

void CTile::OnCollisionExit(CCollider* pOther)
{
	if ((pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER ||
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM) &&
		this->GetTileGroup() == GROUP_TILE::GROUND)											// 그라운드 와 플레이어 , 무기
	{
		pOther->GetObj()->GetGravity()->OnOffGravity(true);
	}

}
