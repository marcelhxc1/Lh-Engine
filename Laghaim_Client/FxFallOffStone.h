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

	LAGVERTEX *OriginalVertexPtr1; // ���� ������ �ּ�. �ؿ��� �־��ٰ� ��������Ѵ�. �׷��� �޸� ������ ������ ����.
	LAGVERTEX *OriginalVertexPtr2; // ���� ������ �ּ�. �ؿ��� �־��ٰ� ��������Ѵ�. �׷��� �޸� ������ ������ ����.
	LAGVERTEX *m_GreenDevilVertexSet1; // ���� ��ȯ�� ���ý� �� ///����������
	LAGVERTEX *m_GreenDevilVertexSet2; // ���� ��ȯ�� ���ý� ��
	LAGVERTEX *m_RedDevilVertexSet1; // ���� ��ȯ�� ���ý� ��
	LAGVERTEX *m_RedDevilVertexSet2; // ���� ��ȯ�� ���ý� ��

public:
	CFxDevil();
	virtual ~CFxDevil();
	void		LoadRes();
	void		DeleteRes();
	BOOL		Render(EffectSort &effect_sort);
};

class CFxSarngaMouel // [12/3/2008 Theodoric] ���̵�� �Ź��� �縪�� ���� ����Ʈ
{
	CCapsyong				*m_pCapsyong;
	CBiped					*m_pBpd;
	CCylinderPlane*			ring;
	CRectPlane*				ground_corona;

	LAGVERTEX *OriginalVertexPtr; // ���� ������ �ּ�. �ؿ��� �־��ٰ� ��������Ѵ�. �׷��� �޸� ������ ������ ����.
	LAGVERTEX *m_GreenMouelVertexSet; // ���� ��ȯ�� ���ý� �� ///����������
	LAGVERTEX *m_RedMouelVertexSet; // ���� ��ȯ�� ���ý� ��

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

	LAGVERTEX *OriginalVertexPtr; // ���� ������ �ּ�. �ؿ��� �־��ٰ� ��������Ѵ�. �׷��� �޸� ������ ������ ����.
	LAGVERTEX *m_GreenMouelVertexSet; // ���� ��ȯ�� ���ý� �� ///����������
	LAGVERTEX *m_RedMouelVertexSet; // ���� ��ȯ�� ���ý� ��

public:
	LHFX_GriffonRing();
	virtual ~LHFX_GriffonRing();
	void		LoadRes();
	void		DeleteRes();
	BOOL		Render(EffectSort &effect_sort);
};
#endif // _FX_FALLOFF_STONE_H_
