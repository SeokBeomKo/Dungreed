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
	bool m_bIsPlat = false;
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
		(this->GetTileGroup() == GROUP_TILE::GROUND ||
		this->GetTileGroup() == GROUP_TILE::PLATFORM||
		this->GetTileGroup() == GROUP_TILE::WALL))					// 그라운드 와 플레이어 , 무기
												
	{
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
		float fInterRight = 0.f, fInterLeft = 0.f, fInterTop = 0.f, fInterBottom = 0.f;

		if (playerbottom > tilebottom && playertop < tiletop)
		{
			fInterBottom = tilebottom;
			fInterTop = tiletop;
		}
		else if (playerbottom > tiletop)
		{
			fInterBottom = playerbottom;
			fInterTop = tiletop;
		}
		else if (playertop < tilebottom)
		{
			fInterBottom = tilebottom;
			fInterTop = playertop;
		}
		fInterH = fInterBottom - fInterTop;

		if (playerright >= tileright && playerleft <= tileleft)
		{
			fInterRight = tileright;
			fInterLeft = tileleft;
		}
		else if (playerright < tileright)
		{
			fInterRight = playerright;
			fInterLeft = tileleft;
		}
		else if (playerleft > tileleft)
		{
			fInterRight = tileright;
			fInterLeft = playerleft;
		}
		fInterW = fInterRight - fInterLeft;

		fPoint pos = pOther->GetObj()->GetPos();
		fPoint scale = pOther->GetObj()->GetScale();
		if (fInterW >= fInterH) // 상하 인지 좌우 인지
		{
			if (fInterTop == tiletop || (playerright == tileright && playerleft == tileleft))						// 위
			{
				if (fInterH > 1.f)
					pos.y -= fInterH;
				pOther->GetObj()->GetGravity()->OnOffGravity(false);
				pOther->GetObj()->SetJumpCount();
				m_bIsPlat = true;
			}
			else if (fInterBottom == tilebottom)				// 아래
			{
				if (this->GetTileGroup() == GROUP_TILE::GROUND)
				{
					pOther->GetObj()->SetJump(false);
					pOther->GetObj()->SetDash(false);
					pOther->GetObj()->GetGravity()->OnOffGravity(true);
					pos.y += fInterH;
				}
			}
			pOther->GetObj()->SetPos(pos);
		}
		//else																// 왼쪽오른쪽
		//{
		//	pOther->GetObj()->SetJump(false);
		//	pOther->GetObj()->SetDash(false);
		//	if (fInterLeft == tileleft)		// 타일 기준 왼쪽 충돌
		//	{
		//		pos.x -= fInterW;
		//		pOther->GetObj()->GetGravity()->OnOffGravity(true);
		//	}
		//	else if (fInterRight == tileright)			// 타일 기준 오른쪽 충돌
		//	{
		//		pos.x += fInterW;
		//		pOther->GetObj()->GetGravity()->OnOffGravity(true);
		//	}
		//	pOther->GetObj()->SetPosX(pos.x);
		//}
	}
}

void CTile::OnCollision(CCollider* pOther)
{
	if ((pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER ||
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM) &&
		(this->GetTileGroup() == GROUP_TILE::GROUND ||
		this->GetTileGroup() == GROUP_TILE::PLATFORM ||
		this->GetTileGroup() == GROUP_TILE::WALL))												// 그라운드 와 플레이어 , 무기
	{
		pOther->GetObj()->SetGR(false);

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
		float fInterRight = 0.f, fInterLeft = 0.f, fInterTop = 0.f, fInterBottom = 0.f;

		if (playerbottom > tilebottom && playertop < tiletop)
		{
			fInterBottom = tilebottom;
			fInterTop = tiletop;
		}
		else if (playerbottom > tiletop && playerbottom < tilebottom)
		{
			fInterBottom = playerbottom;
			fInterTop = tiletop;
		}
		else if (playertop < tilebottom && playertop > tiletop)
		{
			fInterBottom = tilebottom;
			fInterTop = playertop;
		}
		fInterH = fInterBottom - fInterTop;

		if (playerright >= tileright && playerleft <= tileleft)
		{
			fInterRight = tileright;
			fInterLeft = tileleft;
		}
		else if (playerright < tileright)
		{
			fInterRight = playerright;
			fInterLeft = tileleft;
		}
		else if (playerleft > tileleft)
		{
			fInterRight = tileright;
			fInterLeft = playerleft;
		}
		fInterW = fInterRight - fInterLeft;

		fPoint pos = pOther->GetObj()->GetPos();
		fPoint scale = pOther->GetObj()->GetScale();
		if (fInterW >= fInterH) // 상하 인지 좌우 인지
		{
			if (fInterTop == tiletop || (playerright == tileright && playerleft == tileleft))						// 위
			{
				if (this->GetTileGroup() == GROUP_TILE::GROUND)
				{
					if (fInterH > 1.f)
						pos.y -= fInterH;
					pOther->GetObj()->GetGravity()->OnOffGravity(false);
				 }
				else if (this->GetTileGroup() == GROUP_TILE::PLATFORM)
				{
					if (fInterH < 1.f)
						pOther->GetObj()->GetGravity()->OnOffGravity(false);
					if (m_bIsPlat)
					{
						if (fInterH > 1.f)
							pos.y -= fInterH;
						m_bIsPlat = false;
					}
				}
			}
			else if (fInterBottom == tilebottom)				// 아래
			{
				if (this->GetTileGroup() == GROUP_TILE::GROUND)
				{
					pOther->GetObj()->SetJump(false);
					pOther->GetObj()->SetDash(false);
					pOther->GetObj()->GetGravity()->OnOffGravity(true);
					pos.y += fInterH;
				}
			}
			pOther->GetObj()->SetPos(pos);
		}
		//else																// 왼쪽오른쪽
		//{
		//	if (fInterLeft == tileleft)		// 타일 기준 왼쪽 충돌
		//	{
		//		pos.x -= fInterW;
		//		pOther->GetObj()->GetGravity()->OnOffGravity(true);
		//	}
		//	else if (fInterRight == tileright)			// 타일 기준 오른쪽 충돌
		//	{
		//		pos.x += fInterW;
		//		pOther->GetObj()->GetGravity()->OnOffGravity(true);
		//	}
		//	pOther->GetObj()->SetPosX(pos.x);
		//}
	}
}

void CTile::OnCollisionExit(CCollider* pOther)
{
	if ((pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER ||
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM) &&
		(this->GetTileGroup() == GROUP_TILE::GROUND ||
		this->GetTileGroup() == GROUP_TILE::PLATFORM))											// 그라운드 와 플레이어 , 무기
	{
		if (this->GetTileGroup() == GROUP_TILE::PLATFORM)
			pOther->GetObj()->GetGravity()->OnOffGravity(true, pOther->GetObj()->GetGravity()->GetTime());
		else
			pOther->GetObj()->GetGravity()->OnOffGravity(true);
	}

}
