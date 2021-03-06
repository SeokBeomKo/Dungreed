#include "framework.h"
#include "CTile.h"
#include "CGameObject.h"
#include "CD2DImage.h"

#include "CCollider.h"
#include "CGravity.h"

#include "CPlayer.h"
CTile::CTile()
{
	m_pImg = nullptr;
	m_iX = 0;
	m_iY = 0;
	m_iIdx = 0;
	m_group = GROUP_TILE::NONE;
	m_bIsPlat = false;
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
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM ||
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::MONSTER) &&
		(this->GetTileGroup() == GROUP_TILE::GROUND ||
			this->GetTileGroup() == GROUP_TILE::PLATFORM ||
			this->GetTileGroup() == GROUP_TILE::WALL ||
			this->GetTileGroup() == GROUP_TILE::TOPANGLE ||
			this->GetTileGroup() == GROUP_TILE::BOTANGLE ||
			this->GetTileGroup() == GROUP_TILE::RIGHTSLOPE ||
			this->GetTileGroup() == GROUP_TILE::LEFTSLOPE))
	{
		float tiletop, tilebottom, tileright, tileleft;
		tiletop = GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2.f;
		tilebottom = GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2.f;
		tileleft = GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2.f;
		tileright = GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2.f;

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
		else if (playerright > tileleft && playerright < tileright)
		{
			fInterRight = playerright;
			fInterLeft = tileleft;
		}
		else if (playerleft > tileleft && playerleft < tileright)
		{
			fInterRight = tileright;
			fInterLeft = playerleft;
		}
		fInterW = fInterRight - fInterLeft;

		fPoint pos = pOther->GetObj()->GetPos();
		fPoint scale = pOther->GetObj()->GetScale();

		float slopeW;
		float slopeH;
		// TODO : ?????? ?????? ???????? ???? ?????? ?????? ???????? ?????????? ????
		if (pOther->GetObj()->GetDiag())
		{
			if (this->GetTileGroup() == GROUP_TILE::RIGHTSLOPE)		// ???? ?????? ???? ????
			{
				if (playerleft > tileleft && playerleft < tileright)
				{
					slopeW = tileright - playerleft;
					slopeH = tilebottom - playerbottom;
					if (slopeW > slopeH)
						pos.y -= slopeW - slopeH;
					else
						pos.y += slopeH - slopeW;
					pOther->GetObj()->GetGravity()->OnOffGravity(false);
					pOther->GetObj()->SetPos(pos);
					pOther->GetObj()->SetJumpCount();
				}
			}
			if (this->GetTileGroup() == GROUP_TILE::LEFTSLOPE)		// ???? ?????? ???? ????
			{
				if (playerright < tileright && playerright > tileleft)
				{
					slopeW = playerright - tileleft;
					slopeH = tilebottom - playerbottom;
					if (slopeW > slopeH)
						pos.y -= slopeW - slopeH;
					else
						pos.y += slopeH - slopeW;
					pOther->GetObj()->GetGravity()->OnOffGravity(false);
					pOther->GetObj()->SetPos(pos);
					pOther->GetObj()->SetJumpCount();
				}
			}
		}

		if (fInterW >= fInterH)												// ???????? ????????
		{
			if (this->GetTileGroup() == GROUP_TILE::GROUND ||
				this->GetTileGroup() == GROUP_TILE::PLATFORM ||
				this->GetTileGroup() == GROUP_TILE::TOPANGLE ||
				this->GetTileGroup() == GROUP_TILE::BOTANGLE)				// ?????????? ?????? ?????? ?????? ????
			{
				if (this->GetTileGroup() == GROUP_TILE::GROUND ||
					this->GetTileGroup() == GROUP_TILE::PLATFORM ||
					this->GetTileGroup() == GROUP_TILE::TOPANGLE)
				{
					if (fInterTop == tiletop ||
						(playerright == tileright && playerleft == tileleft))	// ?? ????
					{
						CPlayer* pPlayer = (CPlayer*)pOther->GetObj();
						pPlayer->SetFallJump(true);
						if (fInterH > 1.f)
							pos.y -= fInterH;
						pOther->GetObj()->GetGravity()->OnOffGravity(false);
						pOther->GetObj()->SetJumpCount();
						m_bIsPlat = true;
					}
				}
				else if (this->GetTileGroup() == GROUP_TILE::GROUND ||		// ???????? ?????? ????????
					this->GetTileGroup() == GROUP_TILE::BOTANGLE)
				{
					if (fInterBottom == tilebottom)						// ???? ????
					{
						pOther->GetObj()->SetJump(false);
						pOther->GetObj()->SetDash(false);
						pOther->GetObj()->GetGravity()->OnOffGravity(true);
						pos.y += fInterH;
					}
				}
				pOther->GetObj()->SetPos(pos);
			}
		}
		if (this->GetTileGroup() == GROUP_TILE::WALL)
		{
			if (pOther->GetObj()->GetGravity()->CheckGravity() == false)
				pOther->GetObj()->GetGravity()->OnOffGravity(true);
			if (fInterLeft == tileleft)									// ???? ???? ?? ????
			{
				pOther->GetObj()->SetMove(0, 1);
			}
			else if (fInterRight == tileright)							// ???? ???? ?? ????
			{
				pOther->GetObj()->SetMove(1, 0);
			}
		}
		if (this->GetTileGroup() == GROUP_TILE::TOPANGLE)
		{
			if ((fInterLeft == tileleft || fInterRight == tileright) && fInterW + 1.f < fInterH || playertop < tilebottom && playertop > tiletop)
			{
				if (pOther->GetObj()->GetGravity()->CheckGravity() == false) // TODO : ???????? ?
					pOther->GetObj()->GetGravity()->OnOffGravity(true);
				if (fInterLeft == tileleft)									// ???? ???? ?? ????
				{
					pOther->GetObj()->SetMove(0, 1);
				}
				else if (fInterRight == tileright)							// ???? ???? ?? ????
				{
					pOther->GetObj()->SetMove(1, 0);
				}
			}
		}
		if (this->GetTileGroup() == GROUP_TILE::BOTANGLE)
		{
			if ((fInterLeft == tileleft || fInterRight == tileright) && fInterW + 1.f < fInterH)
			{
				if (pOther->GetObj()->GetGravity()->CheckGravity() == false) // TODO : ???????? ?
					pOther->GetObj()->GetGravity()->OnOffGravity(true);
				if (fInterLeft == tileleft)									// ???? ???? ?? ????
				{
					pOther->GetObj()->SetMove(0, 1);
				}
				else if (fInterRight == tileright)							// ???? ???? ?? ????
				{
					pOther->GetObj()->SetMove(1, 0);
				}
			}
		}
	}
}

void CTile::OnCollision(CCollider* pOther)
{
	if ((pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER ||		// ???????? ?? ???????? , ????
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM ||
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::MONSTER) &&
		(this->GetTileGroup() == GROUP_TILE::GROUND ||
			this->GetTileGroup() == GROUP_TILE::PLATFORM ||
			this->GetTileGroup() == GROUP_TILE::WALL ||
			this->GetTileGroup() == GROUP_TILE::TOPANGLE ||
			this->GetTileGroup() == GROUP_TILE::BOTANGLE ||
			this->GetTileGroup() == GROUP_TILE::RIGHTSLOPE ||
			this->GetTileGroup() == GROUP_TILE::LEFTSLOPE))
	{
		pOther->GetObj()->SetGR(false);

		float tiletop, tilebottom, tileright, tileleft;
		tiletop = GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2.f;
		tilebottom = GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2.f;
		tileleft = GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2.f;
		tileright = GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2.f;

		// ????????
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
		else if (playerright > tileleft && playerright < tileright)
		{
			fInterRight = playerright;
			fInterLeft = tileleft;
		}
		else if (playerleft > tileleft && playerleft < tileright)
		{
			fInterRight = tileright;
			fInterLeft = playerleft;
		}
		fInterW = fInterRight - fInterLeft;

		fPoint pos = pOther->GetObj()->GetPos();
		fPoint scale = pOther->GetObj()->GetScale();

		float slopeW;
		float slopeH;

		if (pOther->GetObj()->GetDiag())
		{
			if (this->GetTileGroup() == GROUP_TILE::RIGHTSLOPE)		// ???? ?????? ???? ????
			{
				if (playerleft > tileleft && playerleft < tileright)
				{
					slopeW = tileright - playerleft;
					slopeH = tilebottom - playerbottom;
					if (slopeW > slopeH)
						pos.y -= slopeW - slopeH;
					else
						pos.y += slopeH - slopeW;
					pOther->GetObj()->GetGravity()->OnOffGravity(false);
					pOther->GetObj()->SetPos(pos);
				}
			}
			if (this->GetTileGroup() == GROUP_TILE::LEFTSLOPE)		// ???? ?????? ???? ????
			{
				if (playerright < tileright && playerright > tileleft)
				{
					slopeW = playerright - tileleft;
					slopeH = tilebottom - playerbottom;
					if (slopeW > slopeH)
						pos.y -= slopeW - slopeH;
					else
						pos.y += slopeH - slopeW;
					pOther->GetObj()->GetGravity()->OnOffGravity(false);
					pOther->GetObj()->SetPos(pos);
				}
			}
		}

		if (fInterW >= fInterH)													// ???? ???? ???? ????
		{
			if (this->GetTileGroup() == GROUP_TILE::GROUND ||
				this->GetTileGroup() == GROUP_TILE::PLATFORM ||
				this->GetTileGroup() == GROUP_TILE::TOPANGLE ||
				this->GetTileGroup() == GROUP_TILE::BOTANGLE)					// ?????????? ?????? ?????? ???? ????
			{
				if (this->GetTileGroup() == GROUP_TILE::GROUND ||
					this->GetTileGroup() == GROUP_TILE::PLATFORM ||
					this->GetTileGroup() == GROUP_TILE::TOPANGLE)
				{
					if (fInterTop == tiletop ||
						(playerright == tileright && playerleft == tileleft))		// ?? ????
					{
						if (this->GetTileGroup() == GROUP_TILE::GROUND ||
							this->GetTileGroup() == GROUP_TILE::TOPANGLE)				// ???????? ???? ?? ???? ?? ????
						{
							if (fInterH > 0.8f)
								pos.y -= fInterH;
							pOther->GetObj()->GetGravity()->OnOffGravity(false);
						}
						else if (this->GetTileGroup() == GROUP_TILE::PLATFORM)		// ?????? ?????? ???? ?? ????
						{
							if (fInterH < 0.8f)
								pOther->GetObj()->GetGravity()->OnOffGravity(false);
							if (m_bIsPlat)
							{
								if (fInterH > 0.5f)
									pos.y -= fInterH;
								m_bIsPlat = false;
							}
						}
					}
				}
				if (this->GetTileGroup() == GROUP_TILE::GROUND ||
					this->GetTileGroup() == GROUP_TILE::BOTANGLE)
				{
					if (fInterBottom == tilebottom)						// ???????? ?????? ???? ????
					{
						pOther->GetObj()->SetJump(false);
						pOther->GetObj()->SetDash(false);
						pOther->GetObj()->GetGravity()->OnOffGravity(true);
						pos.y += fInterH;
					}
				}
				pOther->GetObj()->SetPos(pos);
			}
		}
	}
}

void CTile::OnCollisionExit(CCollider* pOther)
{
	if ((pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::PLAYER ||		// ???????? ?? ???????? , ????
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::ITEM ||
		pOther->GetObj()->GetObjGroup() == GROUP_GAMEOBJ::MONSTER) &&
		(this->GetTileGroup() == GROUP_TILE::GROUND ||
			this->GetTileGroup() == GROUP_TILE::PLATFORM ||
			this->GetTileGroup() == GROUP_TILE::WALL ||
			this->GetTileGroup() == GROUP_TILE::TOPANGLE ||
			this->GetTileGroup() == GROUP_TILE::BOTANGLE ||
			this->GetTileGroup() == GROUP_TILE::RIGHTSLOPE ||
			this->GetTileGroup() == GROUP_TILE::LEFTSLOPE))
	{
		pOther->GetObj()->SetGR(false);

		float tiletop, tilebottom, tileright, tileleft;
		tiletop = GetCollider()->GetFinalPos().y - GetCollider()->GetScale().y / 2.f;
		tilebottom = GetCollider()->GetFinalPos().y + GetCollider()->GetScale().y / 2.f;
		tileleft = GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x / 2.f;
		tileright = GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x / 2.f;

		// ????????
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
		else if (playerright + 10.f > tileleft && playerright < tileright)
		{
			fInterRight = playerright + 10.f;
			fInterLeft = tileleft;
		}
		else if (playerleft > tileleft && playerleft - 10.f < tileright)
		{
			fInterRight = tileright;
			fInterLeft = playerleft - 10.f;
		}
		fInterW = fInterRight - fInterLeft;

		if (this->GetTileGroup() == GROUP_TILE::PLATFORM)
		{
			pOther->GetObj()->GetGravity()->OnOffGravity(true, pOther->GetObj()->GetGravity()->GetTime());
		}
		if (this->GetTileGroup() == GROUP_TILE::GROUND ||
			this->GetTileGroup() == GROUP_TILE::RIGHTSLOPE ||
			this->GetTileGroup() == GROUP_TILE::LEFTSLOPE)
		{
			pOther->GetObj()->GetGravity()->OnOffGravity(true);
			if (this->GetTileGroup() == GROUP_TILE::RIGHTSLOPE)
			{
				if (fInterH > fInterW) // ???????? ?????? ???????? ????
				{
					fPoint pos = pOther->GetObj()->GetPos();
					pos.y += 2.f;		// ?????????? ???? ???????????? ???? ??????
					pos.x += 2.f;		// ?????????? ???? ???????????? ???? ??????
					pOther->GetObj()->SetPos(pos);
				}
			}
			if (this->GetTileGroup() == GROUP_TILE::LEFTSLOPE);
			{
				if (fInterH > fInterW) // ???????? ?????? ???????? ????
				{
					fPoint pos = pOther->GetObj()->GetPos();
					pos.y += 2.f;		// ?????????? ???? ???????????? ???? ??????
					pos.x -= 2.f;		// ?????????? ???? ???????????? ???? ??????
					pOther->GetObj()->SetPos(pos);
				}
			}
		}

		if (this->GetTileGroup() == GROUP_TILE::WALL)
		{
			if (fInterLeft == tileleft)									// ?? ????
			{
				pOther->GetObj()->SetMove(0, -1);
			}
			else if (fInterRight == tileright)							// ???? ???? ?????? ????
			{
				pOther->GetObj()->SetMove(-1, 0);
			}

		}
		if (this->GetTileGroup() == GROUP_TILE::TOPANGLE)
		{
			if (!(pOther->GetObj()->GetGravity()->CheckGravity()))
				pOther->GetObj()->GetGravity()->OnOffGravity(true);
			//if (fInterW <= fInterH && !(fInterW < 1.f || fInterH < 1.f))
			if (fInterH - fInterW >= 1.f)
			{
				if (fInterLeft == tileleft)									// ???? ???? ???? ????
				{
					if (pOther->GetObj()->GetMoveLeft() != 0)
						pOther->GetObj()->SetMove(0, -1);
				}
				else if (fInterRight == tileright)							// ???? ???? ?????? ????
				{
					if (pOther->GetObj()->GetMoveRight() != 0)
						pOther->GetObj()->SetMove(-1, 0);
				}
			}
			else
			{
				if (fInterLeft == tileleft)									// ???? ???? ???? ????
				{
					if (pOther->GetObj()->GetMoveLeft() != 0)
						pOther->GetObj()->SetMove(0, -1);
				}
				else if (fInterRight == tileright)							// ???? ???? ?????? ????
				{
					if (pOther->GetObj()->GetMoveRight() != 0)
						pOther->GetObj()->SetMove(-1, 0);
				}
			}

		}
		if (this->GetTileGroup() == GROUP_TILE::BOTANGLE)
		{
			//if (playerbottom >= tiletop)
			{
				if (fInterLeft == tileleft)									// ???? ???? ???? ????
				{
					if (pOther->GetObj()->GetMoveLeft() != 0)
						pOther->GetObj()->SetMove(0, -1);
				}
				else if (fInterRight == tileright)							// ???? ???? ?????? ????
				{
					if (pOther->GetObj()->GetMoveRight() != 0)
						pOther->GetObj()->SetMove(-1, 0);
				}
			}
		}
	}
}
