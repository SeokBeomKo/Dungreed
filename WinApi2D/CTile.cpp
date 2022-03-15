#include "framework.h"
#include "CTile.h"
#include "CD2DImage.h"

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
	if (m_group == GROUP_TILE::GROUND)
	{
		CRenderManager::getInst()->RenderEllipse(
			fptRenderPos.x + fptScale.x / 2.f,
			fptRenderPos.y + fptScale.y / 2.f,
			fptScale.x / 2.f,
			fptScale.y / 2.f,
			RGB(255, 0, 0)
		);
	}
	else if (m_group == GROUP_TILE::WALL)
	{
		CRenderManager::getInst()->RenderEllipse(
			fptRenderPos.x + fptScale.x / 2.f,
			fptRenderPos.y + fptScale.y / 2.f,
			fptScale.x / 2.f,
			fptScale.y / 2.f,
			RGB(0, 0, 255)
		);
	}
}
void CTile::SetTexture(CD2DImage* pImg)
{
	m_pImg = pImg;
}
void CTile::SetImgIdx(UINT idx)
{
	m_iIdx = idx;
}

int CTile::GetX()
{
	return m_iX;
}

int CTile::GetY()
{
	return m_iY;
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