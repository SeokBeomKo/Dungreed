#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CTile.h"
#include "CCollider.h"
#include "CPlayer.h"

CScene::CScene()
{
    m_strName = L"";
}

CScene::~CScene()
{
    // 씬이 가진 모든 게임오브젝트 삭제
    for (int i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            delete m_arrObj[i][j];
        }
    }
}

void CScene::update()
{
    // 씬이 가진 모든 오브젝트 업데이트
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            if (!m_arrObj[i][j]->isDead())
                m_arrObj[i][j]->update();
        }
    }
}

void CScene::finalupdate()
{
    // 씬이 가진 모든 오브젝트 finalupdate
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            m_arrObj[i][j]->finalupdate();
        }
    }
}

void CScene::render()
{
    // 씬이 가진 모든 오브젝트 render
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        if ((UINT)GROUP_GAMEOBJ::TILE == i)
        {
            render_tile();
            continue;
        }
        for (vector<CGameObject*>::iterator iter = m_arrObj[i].begin();
            iter != m_arrObj[i].end(); )
        {
            if (!(*iter)->isDead())
            {
                (*iter)->render();
                iter++;
            }
            else
            {
                iter = m_arrObj[i].erase(iter);
            }
        }
    }
}

void CScene::render_tile()
{
    const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);
    for (UINT i = 0; i < vecTile.size(); i++)
    {
        vecTile[i]->render();
    }
}

const vector<CGameObject*>& CScene::GetGroupObject(GROUP_GAMEOBJ group)
{
    return m_arrObj[(UINT)group];
}

vector<CGameObject*>& CScene::GetUIGroup()
{
    return m_arrObj[(UINT)GROUP_GAMEOBJ::UI];
}

void CScene::SetName(const wstring& strName)
{
    m_strName = strName;
}

wstring CScene::GetName()
{
    return m_strName;
}

int CScene::GetObjectSize(GROUP_GAMEOBJ group)
{
    return m_arrObj[(UINT)group].size();
}

void CScene::AddObject(CGameObject* pObj, GROUP_GAMEOBJ type)
{
    m_arrObj[(int)type].push_back(pObj);
}

void CScene::DeleteGroup(GROUP_GAMEOBJ group)
{
    for (int i = 0; i < m_arrObj[(UINT)group].size(); i++)
    {
        delete m_arrObj[(UINT)group][i];
    }
    m_arrObj[(UINT)group].clear();
}

void CScene::DeleteAll()
{
    for (int i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; i++)
    {

        DeleteGroup((GROUP_GAMEOBJ)i);
    }
}

bool CScene::CheckGroup(GROUP_GAMEOBJ group)
{
    if (m_arrObj[(UINT)group].size() != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void CScene::LoadTile(const wstring& strPath)
{
    DeleteGroup(GROUP_GAMEOBJ::TILE);

    FILE* pFile = nullptr;

    _wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
    assert(pFile);

    UINT xCount = 0;
    UINT yCount = 0;
    UINT tileCount = 0;

    fread(&xCount, sizeof(UINT), 1, pFile);
    fread(&yCount, sizeof(UINT), 1, pFile);
    fread(&tileCount, sizeof(UINT), 1, pFile);

    CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");

    for (UINT i = 0; i < tileCount; i++)
    {
        CTile* newTile = new CTile;
        newTile->Load(pFile);
        newTile->SetD2DImage(pImg);
        newTile->SetPos(fPoint((float)(newTile->GetX() * CTile::SIZE_TILE), (float)(newTile->GetY() * CTile::SIZE_TILE)));

        if (GROUP_TILE::GROUND == newTile->GetGroup())
        {
            newTile->CreateCollider();
            newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
            newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
            newTile->SetName(L"GROUND");
            newTile->SetTileGroup(GROUP_TILE::GROUND);
        }
        else if (GROUP_TILE::PLATFORM == newTile->GetGroup())
        {
            newTile->CreateCollider();
            newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
            newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
            newTile->SetName(L"PLATFORM");
            newTile->SetTileGroup(GROUP_TILE::PLATFORM);
        }
        else if (GROUP_TILE::WALL == newTile->GetGroup())
        {
            newTile->CreateCollider();
            newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
            newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
            newTile->SetName(L"WALL");
            newTile->SetTileGroup(GROUP_TILE::WALL);
        }
        else if (GROUP_TILE::TOPANGLE == newTile->GetGroup())
        {
            newTile->CreateCollider();
            newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
            newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
            newTile->SetName(L"TOPANGLE");
            newTile->SetTileGroup(GROUP_TILE::TOPANGLE);
        }
        else if (GROUP_TILE::BOTANGLE == newTile->GetGroup())
        {
            newTile->CreateCollider();
            newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
            newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
            newTile->SetName(L"BOTANGLE");
            newTile->SetTileGroup(GROUP_TILE::BOTANGLE);
        }
        else if (GROUP_TILE::RIGHTSLOPE == newTile->GetGroup())
        {
            newTile->CreateCollider();
            newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
            newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
            newTile->SetName(L"RIGHTSLOPE");
            newTile->SetTileGroup(GROUP_TILE::RIGHTSLOPE);
        }
        else if (GROUP_TILE::LEFTSLOPE == newTile->GetGroup())
        {
            newTile->CreateCollider();
            newTile->GetCollider()->SetScale(fPoint(CTile::SIZE_TILE, CTile::SIZE_TILE));
            newTile->GetCollider()->SetOffsetPos(fPoint(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
            newTile->SetName(L"LEFTSLOPE");
            newTile->SetTileGroup(GROUP_TILE::LEFTSLOPE);
        }


        AddObject(newTile, GROUP_GAMEOBJ::TILE);
    }

    fclose(pFile);
}


