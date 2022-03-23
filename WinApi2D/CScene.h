#pragma once

// ���� ���� : �ش� Ŭ������ ������ ������ ����� �� �ְ� ����.
// 1. ��������� ������ ȣ��Ǿ� #pragma�� ���� ����θ� Ȯ�� �Ұ��� ���� �ذ�
// 2. ������ �ӵ��� ����
class CGameObject;
class CPlayer;

class CScene
{
private:
	vector<CGameObject*> m_arrObj[(int)GROUP_GAMEOBJ::SIZE];
	wstring m_strName;

	vector<CGameObject*> m_arrObjClone[(int)GROUP_GAMEOBJ::SIZE];
	CPlayer* m_data;
public:
	CScene();
	virtual ~CScene();

	virtual void update();
	virtual void finalupdate();
	virtual void render();

	void render_tile();

	virtual void Enter() = 0;	// �ش� ���� ���Խ� ȣ��
	virtual void Exit() = 0;	// �ش� ���� Ż��� ȣ��

	void SetName(const wstring& strName);
	wstring GetName();

	const vector<CGameObject*>& GetGroupObject(GROUP_GAMEOBJ group);
	vector<CGameObject*>& GetUIGroup();		// UI�� ������ ������ �����ؾ� �ϱ� ������ ������ ���� / ���� �ʿ�!
	void AddObject(CGameObject* pObj, GROUP_GAMEOBJ group);
	void DeleteGroup(GROUP_GAMEOBJ group);
	void DeleteAll();

	void LoadTile(const wstring& strPath);

	void SaveData(CGameObject* pObj, GROUP_GAMEOBJ group);
	void LoadData(GROUP_GAMEOBJ group);
};