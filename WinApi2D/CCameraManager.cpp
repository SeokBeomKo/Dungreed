#include "framework.h"
#include "CCameraManager.h"
#include "CGameObject.h"
#include "CTexture.h"

CCameraManager::CCameraManager()
{
	m_fptLookAt = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_fptCurLookAt = m_fptLookAt;
	m_fptPrevLookAt = m_fptLookAt;
	m_pTargetObj = nullptr;
	m_fAccTime = m_fTime;
	m_fSpeed = 0;
}

CCameraManager::~CCameraManager()
{

}

void CCameraManager::init()
{
}

void CCameraManager::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->isDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			SetLookAt(m_pTargetObj->GetPos());
		}
	}

	// 화면 중앙과 카메라 LookAt 좌표 사이의 차이 계산
	CalDiff();

	// tool씬 사용시 해제
	// CheckRange();
}

void CCameraManager::render()
{
	if (m_listCamEffect.empty())
	{
		return;
	}

	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDT;

	float fRatio = 0.f;
	fRatio = effect.fCurTime / effect.fDuration;
	if (fRatio < 0.f)
		fRatio = 0.f;
	else if (fRatio > 1.f)
		fRatio = 1.f;

	else if (CAM_EFFECT::FADE_IN == effect.m_eEffect)
		fRatio = 1.f - fRatio;

	CRenderManager::getInst()->RenderFillRectangle(0, 0, WINSIZEX, WINSIZEY, RGB(0, 0, 0), fRatio);

	if (effect.fDuration < effect.fCurTime)
	{
		m_listCamEffect.pop_front();
	}
}

void CCameraManager::CheckRange()
{
	if (m_fptCurLookAt.y < 360.f)	// 카메라가 기준보다 위로 가거나
	{	
		m_fptCurLookAt.y = 360.f;
	}
	if (m_fptCurLookAt.y > m_fptRange.y - 360.f)	// 카메라가 기준보다 아래로 가거나
	{ 
		m_fptCurLookAt.y = m_fptRange.y - 360.f;
	}
	if (m_fptCurLookAt.x < 640.f)		// 카메라가 기준보다 왼쪽으로 가거나
	{
		m_fptCurLookAt.x = 640.f;
	}
	if (m_fptCurLookAt.x > m_fptRange.x - 640.f)		// 카메라가 기준보다 오른쪽으로 가거나
	{
		m_fptCurLookAt.x = m_fptRange.x - 640.f;
	}

	m_fptDiff = m_fptCurLookAt - fPoint(WINSIZEX / 2,WINSIZEY /2 );
}

void CCameraManager::SetLookAt(fPoint lookAt)
{
	m_fptLookAt = lookAt;
	float fMoveDist = (m_fptLookAt - m_fptPrevLookAt).Length();

	m_fSpeed = fMoveDist / m_fTime;
	m_fAccTime = 0.f;
}

void CCameraManager::SetTargetObj(CGameObject* target)
{
	m_pTargetObj = target;
}

void CCameraManager::SetRange(fPoint range)
{
	m_fptRange = range * 4.f;
}

fPoint CCameraManager::GetLookAt()
{
	return m_fptCurLookAt;
}

fPoint CCameraManager::GetRenderPos(fPoint objPos)
{
	return objPos - m_fptDiff;
}

fPoint CCameraManager::GetRealPos(fPoint renderPos)
{
	// 렌더링 좌표에서 차이값만큼 더해주면 절대 좌표가 나옴.
	return renderPos + m_fptDiff;
}

void CCameraManager::FadeIn(float duration)
{
	tCamEffect ef = {};
	ef.m_eEffect = CAM_EFFECT::FADE_IN;
	ef.fDuration = duration;
	ef.fCurTime = 0.f;

	m_listCamEffect.push_back(ef);

	if (0.f == duration)
	{
		assert(nullptr);
	}
}

void CCameraManager::FadeOut(float duration)
{
	tCamEffect ef = {};
	ef.m_eEffect = CAM_EFFECT::FADE_OUT;
	ef.fDuration = duration;
	ef.fCurTime = 0.f;

	m_listCamEffect.push_back(ef);

	if (0.f == duration)
	{
		assert(nullptr);
	}
}

void CCameraManager::Scroll(fVec2 vec, float velocity)
{
	m_fptLookAt = m_fptLookAt + vec * velocity * fDT;
	m_fptCurLookAt = m_fptCurLookAt + vec * velocity * fDT;

	fPoint fptCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_fptDiff = m_fptCurLookAt - fptCenter;
}

void CCameraManager::CalDiff()
{
	m_fAccTime += fDT;

	// 시간이 지나면, 도착한것으로 간주
	if (m_fTime <= m_fAccTime)
	{
		m_fptCurLookAt = m_fptLookAt;
	}
	else
	{
		fPoint fptCenter = fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f);

		m_fptCurLookAt = m_fptPrevLookAt + (m_fptLookAt - m_fptPrevLookAt).normalize() * m_fSpeed * fDT;
		m_fptDiff = m_fptCurLookAt - fptCenter;
		m_fptPrevLookAt = m_fptCurLookAt;
	}
}
