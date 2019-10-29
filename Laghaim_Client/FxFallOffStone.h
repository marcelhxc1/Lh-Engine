#ifndef _FX_FALLOFF_STONE_H_
#define _FX_FALLOFF_STONE_H_

#include "Config.h"

class CBiped;
class CCapsyong;
class IndexedTexture;

class CFxFallOffStone
{
	CCapsyong				*m_pCapsyong;
	CBiped					*m_pBpd;
	// nate 2004 - 7 - image
//	IndexedTexture		*m_pIndexedTexture;

	// nate 2004 - 8 ImageManager
//	DWORD					m_ringTexIdx;

public:
	CFxFallOffStone();
	virtual ~CFxFallOffStone();

	// nate 2004 - 8 ImageManager
//	void		LoadRes(IndexedTexture *pIndexedTexture);
	void		LoadRes();

	void		DeleteRes();

	BOOL		Render(EffectSort &effect_sort);
};

class CFxDevil
{
	CCapsyong				*m_pCapsyong;
	CBiped					*m_pBpd;
	CCylinderPlane*			ring;
	CRectPlane*				ground_corona;

	LAGVERTEX *OriginalVertexPtr1; // 원본 포인터 주소. 밑에꺼 넣었다가 돌려줘야한다. 그래야 메모리 해제시 문제가 없다.
	LAGVERTEX *OriginalVertexPtr2; // 원본 포인터 주소. 밑에꺼 넣었다가 돌려줘야한다. 그래야 메모리 해제시 문제가 없다.
	LAGVERTEX *m_GreenDevilVertexSet1; // 색상 변환용 버택스 셋 ///컨버젼무기
	LAGVERTEX *m_GreenDevilVertexSet2; // 색상 변환용 버택스 셋
	LAGVERTEX *m_RedDevilVertexSet1; // 색상 변환용 버택스 셋
	LAGVERTEX *m_RedDevilVertexSet2; // 색상 변환용 버택스 셋

public:
	CFxDevil();
	virtual ~CFxDevil();
	void		LoadRes();
	void		DeleteRes();
	BOOL		Render(EffectSort &effect_sort);
};

class CFxSarngaMouel // [12/3/2008 Theodoric] 에이디아 신무기 사릉가 공격 이펙트
{
	CCapsyong				*m_pCapsyong;
	CBiped					*m_pBpd;
	CCylinderPlane*			ring;
	CRectPlane*				ground_corona;

	LAGVERTEX *OriginalVertexPtr; // 원본 포인터 주소. 밑에꺼 넣었다가 돌려줘야한다. 그래야 메모리 해제시 문제가 없다.
	LAGVERTEX *m_GreenMouelVertexSet; // 색상 변환용 버택스 셋 ///컨버젼무기
	LAGVERTEX *m_RedMouelVertexSet; // 색상 변환용 버택스 셋

public:
	CFxSarngaMouel();
	virtual ~CFxSarngaMouel();
	void		LoadRes();
	void		DeleteRes();
	BOOL		Render(EffectSort &effect_sort);
};

class LHFX_GriffonRing
{
	CCapsyong				*m_pCapsyong;
	CBiped					*m_pBpd;
	CCylinderPlane*			ring;
	CRectPlane*				ground_corona;

	LAGVERTEX *OriginalVertexPtr; // 원본 포인터 주소. 밑에꺼 넣었다가 돌려줘야한다. 그래야 메모리 해제시 문제가 없다.
	LAGVERTEX *m_GreenMouelVertexSet; // 색상 변환용 버택스 셋 ///컨버젼무기
	LAGVERTEX *m_RedMouelVertexSet; // 색상 변환용 버택스 셋

public:
	LHFX_GriffonRing();
	virtual ~LHFX_GriffonRing();
	void		LoadRes();
	void		DeleteRes();
	BOOL		Render(EffectSort &effect_sort);
};
#endif // _FX_FALLOFF_STONE_H_
