#include "framework.h"
#include "CDoor.h"
#include "CPlayer.h"

#include "CCollider.h"

CPlayer* pPlayer = nullptr;

CDoor::CDoor()
{
	pScene = nullptr;
	SetScale(fPoint(1088.f, 32.f));

	CreateCollider();
	GetCollider()->SetScale(GetScale());
}

CDoor::~CDoor()
{
}

void CDoor::update()
{
}

void CDoor::SetNextScene(GROUP_SCENE next)
{
	pScene = new GROUP_SCENE;
	*pScene = next;
}

void CDoor::OnCollisionEnter(CCollider* pOther)
{
	pPlayer = (CPlayer*)pOther->GetObj();

	if (nullptr != pScene)
	{
		sPlayer = new CPlayer;
		sPlayer->SaveData(pPlayer->LoadData());
		ChangeScn(*pScene);
	}
}