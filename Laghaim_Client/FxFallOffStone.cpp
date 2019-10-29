#include "stdafx.h"
#define D3D_OVERLOADS

#include <d3d.h>
#include <time.h>
#include <assert.h>
#include "FxSet.h"
#include "sfx.h"
#include "FxHorn.h"
#include "main.h"
#include "D3DMath.h"
#include "D3DUtil.h"
#include "IndexedTexture.h"
#include "ShadowRect.h"
#include "WeatherMgr.h"
#include "DirtSnd.h"
#include "LoadEffectSound.h"
#include "ImageDefine.h"
#include "CapSyong.h"
#include "GUtil.h"
#include "Capsyong.h"
#include "NkCharacter.h"
#include "NkMob.h"




//////////////////////////////////////////////////////////////////////
// 드레곤 링 구현.
//////////////////////////////////////////////////////////////////////
CFxFallOffStone::CFxFallOffStone()
{
	m_pCapsyong = NULL;
	m_pBpd = NULL;
}

CFxFallOffStone::~CFxFallOffStone()
{
	SAFE_DELETE(m_pCapsyong);
	SAFE_DELETE(m_pBpd);
}

// nate 2004 - 8 ImageManager
void CFxFallOffStone::LoadRes()
{
	SAFE_DELETE(m_pCapsyong);
	SAFE_DELETE(m_pBpd);

	m_pCapsyong = new CCapsyong(g_pCapsyongTexture);
	if( VF_ERR_NONE > m_pCapsyong->Read("data/effect/csy/nw_mop_001_fx.CSY") )
	{
		SAFE_DELETE(m_pCapsyong);
		return;
	}

	m_pBpd = new CBiped;
	if( VF_ERR_NONE > m_pBpd->Read("data/effect/bpd/nw_mop_001_fx.BPD") )
	{
		SAFE_DELETE(m_pBpd);
		return;
	}

}

void CFxFallOffStone::DeleteRes()
{}

BOOL CFxFallOffStone::Render(EffectSort &effect_sort)
{
	if( !GET_D3DDEVICE() )
		return true;

	BOOL bFinished = FALSE;
	D3DMATRIX matWorld, matTrans, matView;
	DWORD dwLighting, dwZWrite;

	GET_D3DDEVICE()->GetRenderState( D3DRENDERSTATE_LIGHTING, &dwLighting);
	GET_D3DDEVICE()->GetRenderState( D3DRENDERSTATE_ZWRITEENABLE, &dwZWrite);

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, FALSE);

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_SRCBLEND,   D3DBLEND_SRCALPHA );
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_DESTBLEND,  D3DBLEND_INVSRCALPHA );

	if (m_pCapsyong && m_pBpd)
	{
		D3DUtil_SetIdentityMatrix( matTrans );
		D3DUtil_SetTranslateMatrix( matTrans, effect_sort.vPos.x, effect_sort.vPos.y, effect_sort.vPos.z);
		pCMyApp->SetViewMatrix(matView);
		GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matTrans );
		GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_VIEW, &matView);
		m_pCapsyong->Animate(m_pBpd, effect_sort.nCurFrame, TRUE, LINE_EFF_NONE,
							 &matWorld, &matView);
		m_pCapsyong->Render(GET_D3DDEVICE(), -1, FALSE, FALSE, NULL, effect_sort.nCurFrame);
	}

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, dwLighting);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, dwZWrite);

	return bFinished;
}


//////////////////////////////////////////////////////////////////////
// 데빌 링 구현
//////////////////////////////////////////////////////////////////////
CFxDevil::CFxDevil()
{
	m_pCapsyong = NULL;
	m_pBpd = NULL;

	ring = NULL;
	ring = new CCylinderPlane;
	if( ring )
		ring->Create( 8.0f, 8.0f, 15.0f, 20.0f, 0.0f, TRUE, 2.0f);

	ground_corona = NULL;
	ground_corona = new CRectPlane;
	if( ground_corona )
		ground_corona->Create( 10.0f, 10.0f, FALSE );

	OriginalVertexPtr1 = NULL; // 참조만 하는 포인터.
	OriginalVertexPtr2 = NULL; // 참조만 하는 포인터.
	m_GreenDevilVertexSet1 = NULL; // 색상 변환용 버택스 셋 ///컨버젼무기
	m_GreenDevilVertexSet2 = NULL; // 색상 변환용 버택스 셋
	m_RedDevilVertexSet1 = NULL; // 색상 변환용 버택스 셋
	m_RedDevilVertexSet2 = NULL; // 색상 변환용 버택스 셋
}

CFxDevil::~CFxDevil()
{
	// 캡숑을 지우기 전에 캡숑안에 포인터를 엉켜놓은걸 정상화해줘야한다.
	int i;
	CCsyObj *pCsy = NULL;

	i = 1;
	pCsy = &(m_pCapsyong->m_Csy[i]);
	if( pCsy )
	{
		pCsy->m_Vertices = OriginalVertexPtr1; // 원본의 참조포인터로 돌려준다.
	}

	i = 2;
	pCsy = &(m_pCapsyong->m_Csy[i]);
	if( pCsy )
	{
		pCsy->m_Vertices = OriginalVertexPtr2; // 원본의 참조포인터로 돌려준다.
	}


	SAFE_DELETE(m_pCapsyong);
	SAFE_DELETE(m_pBpd);
	SAFE_DELETE(ring);
	SAFE_DELETE(ground_corona);

	SAFE_DELETE(m_GreenDevilVertexSet1); ///컨버젼무기
	SAFE_DELETE(m_GreenDevilVertexSet2);
	SAFE_DELETE(m_RedDevilVertexSet1);
	SAFE_DELETE(m_RedDevilVertexSet2);
}

void CFxDevil::LoadRes()
{
	SAFE_DELETE(m_pCapsyong);
	SAFE_DELETE(m_pBpd);

	m_pCapsyong = new CCapsyong(g_pCapsyongTexture);
	if( VF_ERR_NONE > m_pCapsyong->Read("data/Npc/csy/sky_mop3.CSY") )
	{
		SAFE_DELETE(m_pCapsyong);
		return;
	}


	int i;
	CCsyObj *pCsy = NULL;

	i = 1;
	pCsy = &(m_pCapsyong->m_Csy[i]);
	if( pCsy )
	{
		m_GreenDevilVertexSet1 = new LAGVERTEX[ pCsy->m_VertexCount ];
		if( m_GreenDevilVertexSet1 )
			memcpy( m_GreenDevilVertexSet1, pCsy->m_Vertices, sizeof(LAGVERTEX)*pCsy->m_VertexCount );

		m_RedDevilVertexSet1   = new LAGVERTEX[ pCsy->m_VertexCount ];
		if( m_RedDevilVertexSet1 )
		{
			memcpy( m_RedDevilVertexSet1, pCsy->m_Vertices, sizeof(LAGVERTEX)*pCsy->m_VertexCount );
			for( i = 0; i < pCsy->m_VertexCount; i++) // 레드의 경우 색 변경.(그린은 원본대로 놔두면 된다.)
			{
				m_RedDevilVertexSet1[i].diffuse = 0x00ff0000;
			}
		}

		OriginalVertexPtr1 = pCsy->m_Vertices; // 원본의 참조포인터를 얻어둔다.
	}

	i = 2;
	pCsy = &(m_pCapsyong->m_Csy[i]);
	if( pCsy )
	{
		m_GreenDevilVertexSet2 = new LAGVERTEX[ pCsy->m_VertexCount ];
		if( m_GreenDevilVertexSet2 )
			memcpy( m_GreenDevilVertexSet2, pCsy->m_Vertices, sizeof(LAGVERTEX)*pCsy->m_VertexCount );

		m_RedDevilVertexSet2   = new LAGVERTEX[ pCsy->m_VertexCount ];
		if( m_RedDevilVertexSet2 )
		{
			memcpy( m_RedDevilVertexSet2, pCsy->m_Vertices, sizeof(LAGVERTEX)*pCsy->m_VertexCount );
			for( i = 0; i < pCsy->m_VertexCount; i++) // 레드의 경우 색 변경.(그린은 원본대로 놔두면 된다.)
			{
				m_RedDevilVertexSet2[i].diffuse = 0x00ff0000;
			}
		}

		OriginalVertexPtr2 = pCsy->m_Vertices; // 원본의 참조포인터를 얻어둔다.
	}


	m_pBpd = new CBiped;
	if( VF_ERR_NONE > m_pBpd->Read("data/Npc/bpd/sky_mop3_att.BPD") )
	{
		SAFE_DELETE(m_pBpd);
		return;
	}
}

void CFxDevil::DeleteRes()
{}

BOOL CFxDevil::Render(EffectSort &effect_sort)
{
	if( !GET_D3DDEVICE() )
		return true;

	if(!effect_sort.pNkChaTo
			&& !effect_sort.pMobTo)
		return TRUE;

	BOOL bFinished = FALSE;
	D3DMATRIX matWorld, matTrans, matView;
	DWORD dwLighting, dwZWrite;

	GET_D3DDEVICE()->GetRenderState( D3DRENDERSTATE_LIGHTING, &dwLighting);
	GET_D3DDEVICE()->GetRenderState( D3DRENDERSTATE_ZWRITEENABLE, &dwZWrite);

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, FALSE);

	int i; ///컨버젼무기
	CCsyObj *pCsy;

	if( effect_sort.num == 1 ) // 진 데빌링이면.. ///컨버젼무기
	{
		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCCOLOR  );
		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_DESTCOLOR  );

		i = 1;
		pCsy = &(m_pCapsyong->m_Csy[i]);
		if( pCsy && m_RedDevilVertexSet1 )
			pCsy->m_Vertices = m_RedDevilVertexSet1; // 포인터를 바꿔치기 한다.

		i = 2;
		pCsy = &(m_pCapsyong->m_Csy[i]);
		if( pCsy && m_RedDevilVertexSet2 )
			pCsy->m_Vertices = m_RedDevilVertexSet2; // 포인터를 바꿔치기 한다.
	}
	else
	{
		GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_SRCBLEND,   D3DBLEND_ONE );
		GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_DESTBLEND,  D3DBLEND_ONE );

		i = 1;
		pCsy = &(m_pCapsyong->m_Csy[i]);
		if( pCsy && m_GreenDevilVertexSet1 )
			pCsy->m_Vertices = m_GreenDevilVertexSet1; // 포인터를 바꿔치기 한다.

		i = 2;
		pCsy = &(m_pCapsyong->m_Csy[i]);
		if( pCsy && m_GreenDevilVertexSet2 )
			pCsy->m_Vertices = m_GreenDevilVertexSet2; // 포인터를 바꿔치기 한다.
	}


	if (m_pCapsyong && m_pBpd)
	{
		D3DUtil_SetIdentityMatrix( matTrans );
		D3DUtil_SetTranslateMatrix( matTrans, effect_sort.vPos.x, effect_sort.vPos.y, effect_sort.vPos.z);
		pCMyApp->SetViewMatrix(matView);
		GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matTrans );
		GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_VIEW, &matView);
		m_pCapsyong->Animate(m_pBpd, effect_sort.nCurFrame, TRUE, LINE_EFF_NONE,
							 &matWorld, &matView);
		m_pCapsyong->Render(GET_D3DDEVICE(), -1, FALSE, FALSE, NULL, effect_sort.nCurFrame);
	}

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE);

//-------------------------------------------------------------------
	float maxScale, m_fScale, m_fFade;
	maxScale = 3.0f;
	m_fScale = (maxScale * effect_sort.nCurFrame) / FX_DEVILRING_FRAMECOUNT;
	m_fFade = 1.0f - (m_fScale * 0.3f);

	D3DVECTOR vDrawPos;
	vDrawPos = effect_sort.vPos;

	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
	if( g_pCapsyongTexture )
		GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_RING ] ) );

	float red, green, blue;
	red = green = blue = 0.0f;

	if( effect_sort.num == 1 ) // 진 데빌링이면.. ///컨버젼무기
	{
		red = 0.35f - (0.35f * m_fScale * 0.15f);
		green = 0.35f - (0.35f * m_fScale * 0.15f);
		blue = 0.35f - (0.35f * m_fScale * 0.15f);
	}
	else
	{
		red = 0.15f - (0.15f * m_fScale * 0.15f);
		green = 0.15f - (0.15f * m_fScale * 0.15f);
		blue = 0.4f - (0.4f * m_fScale * 0.15f);
	}

	if( ring )
	{
		ring->SetColor(red, green, blue, m_fFade);
		ring->SetRotationY( g_PI );
		ring->RotateY( m_fScale * 20.0f );
		ring->Scale( 3.5f, 10.0f, 3.5f );
		ring->SetTranslationXYZ(vDrawPos.x, vDrawPos.y, vDrawPos.z);
		ring->Render();
	}

	D3DVECTOR	vViewVec;
	vViewVec = pCMyApp->GetEyeDirection();

	if( effect_sort.num == 1 ) // 진 데빌링이면.. ///컨버젼무기
	{
		red = 0.45f - (0.45f * m_fScale * 0.15f);
		green = 0.45f - (0.45f * m_fScale * 0.15f);
		blue = 0.45f - (0.45f * m_fScale * 0.15f);
	}
	else
	{
		red = 0.25f - (0.25f * m_fScale * 0.15f);
		green = 0.25f - (0.25f * m_fScale * 0.15f);
		blue = 0.75f - (0.75f * m_fScale * 0.15f);
	}

	GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_SHIELD ] ) );
	if( ground_corona )
	{
		ground_corona->SetColor(red*0.5f, green*0.5f, blue*0.5f, m_fFade*0.5f);
		ground_corona->SetRotationX( g_PI * 0.5f );
		ground_corona->Scale( m_fScale*1.5f, m_fScale*1.5f, m_fScale*1.5f );
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + m_fScale*3.0f, vDrawPos.z);
		ground_corona->Render();

		ground_corona->Scale( 1.5f, 1.5f, 1.5f );
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + m_fScale*2.5f, vDrawPos.z);
		ground_corona->Render();

		GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_CORONA ] ) );
		ground_corona->SetColor(red, green, blue, m_fFade);
		ground_corona->ReCreate(m_fScale * 0.25f);
		ground_corona->SetBillBoard(vViewVec, FALSE, 0.0f);
		ground_corona->Scale(m_fScale, m_fScale, 0.0f);
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + 12.0f, vDrawPos.z);
		ground_corona->Render();
	}

	if (effect_sort.nCurFrame >= 6 && effect_sort.nCurFrame < 8)
	{
		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));

		ef_sort.nType = FX_HORNBOOM;
		ef_sort.vPos = D3DVECTOR( effect_sort.vPos.x, effect_sort.vPos.y + 12.0f, effect_sort.vPos.z );
		ef_sort.Index = HIT_DRAGON;

		if (effect_sort.pMobTo)
			effect_sort.pMobTo->Attacked();
		else if (effect_sort.pNkChaTo)
			effect_sort.pNkChaTo->Attacked();

		g_pRoh->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
	}

//-------------------------------------------------------------------
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, dwLighting);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, dwZWrite);

	return bFinished;
}

//////////////////////////////////////////////////////////////////////////
// [12/3/2008 Theodoric] 사릉가 이펙트
//////////////////////////////////////////////////////////////////////////

CFxSarngaMouel::CFxSarngaMouel()
{
	m_pCapsyong = NULL;
	m_pBpd = NULL;

	ring = NULL;
	ring = new CCylinderPlane;
	if( ring )
		ring->Create( 8.0f, 8.0f, 15.0f, 20.0f, 0.0f, TRUE, 2.0f);

	ground_corona = NULL;
	ground_corona = new CRectPlane;
	if( ground_corona )
		ground_corona->Create( 10.0f, 10.0f, FALSE );

	OriginalVertexPtr = NULL; // 참조만 하는 포인터.
	m_GreenMouelVertexSet = NULL; // 색상 변환용 버택스 셋 ///컨버젼무기
	m_RedMouelVertexSet = NULL; // 색상 변환용 버택스 셋
}

CFxSarngaMouel::~CFxSarngaMouel()
{
	// 캡숑을 지우기 전에 캡숑안에 포인터를 엉켜놓은걸 정상화해줘야한다.
	CCsyObj *pCsy = NULL;

	pCsy = m_pCapsyong->m_Csy;
	if( pCsy )
		pCsy->m_Vertices = OriginalVertexPtr; // 원본의 참조포인터로 돌려준다.

	SAFE_DELETE(m_pCapsyong);
	SAFE_DELETE(m_pBpd);
	SAFE_DELETE(ring);
	SAFE_DELETE(ground_corona);

	SAFE_DELETE(m_GreenMouelVertexSet); ///컨버젼무기
	SAFE_DELETE(m_RedMouelVertexSet);
}

void CFxSarngaMouel::LoadRes()
{
	SAFE_DELETE(m_pCapsyong);
	SAFE_DELETE(m_pBpd);

	m_pCapsyong = new CCapsyong(g_pCapsyongTexture);
	if( VF_ERR_NONE > m_pCapsyong->Read("data/Npc/csy/2005_m_mu.CSY") )
	{
		SAFE_DELETE(m_pCapsyong);
		return;
	}


	// 진 데빌링과 일반 데빌링의 색 변경을 위한 버택스 셋의 생성. ///컨버젼무기
	CCsyObj *pCsy = NULL;
	pCsy = m_pCapsyong->m_Csy;
	if( pCsy )
	{
		m_GreenMouelVertexSet = new LAGVERTEX[ pCsy->m_VertexCount ];
		if( m_GreenMouelVertexSet )
			memcpy( m_GreenMouelVertexSet, pCsy->m_Vertices, sizeof(LAGVERTEX)*pCsy->m_VertexCount );

		m_RedMouelVertexSet   = new LAGVERTEX[ pCsy->m_VertexCount ];
		if( m_RedMouelVertexSet )
		{
			memcpy( m_RedMouelVertexSet, pCsy->m_Vertices, sizeof(LAGVERTEX)*pCsy->m_VertexCount );
			for(int i = 0; i < pCsy->m_VertexCount; i++) // 레드의 경우 색 변경.(그린은 원본대로 놔두면 된다.)
			{
				m_RedMouelVertexSet[i].diffuse = 0x00FFFF00;
			}
		}

		OriginalVertexPtr = pCsy->m_Vertices; // 원본의 참조포인터를 얻어둔다.
	}

	m_pBpd = new CBiped;
	if( m_pBpd->Read("data/Npc/bpd/2005_m_mu_att.BPD") )
	{
		SAFE_DELETE(m_pBpd);
		return;
	}
}

void CFxSarngaMouel::DeleteRes()
{}

BOOL CFxSarngaMouel::Render(EffectSort &effect_sort)
{
	if( !GET_D3DDEVICE() )
		return true;

	if(!effect_sort.pNkChaTo
			&& !effect_sort.pMobTo)
		return TRUE;

	BOOL bFinished = FALSE;
	D3DMATRIX matWorld, matTrans, matView;
	DWORD dwLighting, dwZWrite;

	GET_D3DDEVICE()->GetRenderState( D3DRENDERSTATE_LIGHTING, &dwLighting);
	GET_D3DDEVICE()->GetRenderState( D3DRENDERSTATE_ZWRITEENABLE, &dwZWrite);

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, FALSE);

	CCsyObj *pCsy;

	if( effect_sort.num == 1 ) // 진 데빌링이면.. ///컨버젼무기
	{
		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCCOLOR  );
		GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_DESTCOLOR  );

		pCsy = m_pCapsyong->m_Csy;
		if( pCsy && m_RedMouelVertexSet )
			pCsy->m_Vertices = m_RedMouelVertexSet; // 포인터를 바꿔치기 한다.
	}
	else
	{
		GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_SRCBLEND,   D3DBLEND_ONE );
		GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_DESTBLEND,  D3DBLEND_ONE );

		pCsy = m_pCapsyong->m_Csy;
		if( pCsy && m_GreenMouelVertexSet )
			pCsy->m_Vertices = m_GreenMouelVertexSet; // 포인터를 바꿔치기 한다.
	}

	if (m_pCapsyong && m_pBpd)
	{
		D3DMATRIX matRotate, matWorld;
		D3DUtil_SetIdentityMatrix( matTrans );
		D3DUtil_SetIdentityMatrix( matRotate );
		D3DUtil_SetIdentityMatrix( matWorld );
		pCMyApp->SetViewMatrix(matView);

		D3DUtil_SetTranslateMatrix( matTrans, effect_sort.vPos.x, effect_sort.vPos.y, effect_sort.vPos.z);
		Nk3DUtil_SetRotateCCWYMatrix( matRotate, effect_sort.vCurPos.x);
		D3DMath_MatrixMultiply(matWorld, matRotate, matTrans);

		GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld );
		GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_VIEW, &matView);
		m_pCapsyong->Animate(m_pBpd, effect_sort.nCurFrame, TRUE, LINE_EFF_NONE,
							 &matWorld, &matView);
		m_pCapsyong->Render(GET_D3DDEVICE(), -1, FALSE, FALSE, NULL, effect_sort.nCurFrame);
	}

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE);

//-------------------------------------------------------------------
	float maxScale, m_fScale, m_fFade;
	maxScale = 3.0f;
	m_fScale = (maxScale * effect_sort.nCurFrame) / FX_DEVILRING_FRAMECOUNT;
	m_fFade = 1.0f - (m_fScale * 0.3f);

	D3DVECTOR vDrawPos;
	vDrawPos = effect_sort.vPos;

	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
	if( g_pCapsyongTexture )
		GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_RING ] ) );

	float red, green, blue;
	red = green = blue = 0.0f;

	if( effect_sort.num == 1 ) // 진 데빌링이면.. ///컨버젼무기
	{
		red = 0.35f - (0.35f * m_fScale * 0.15f);
		green = 0.35f - (0.35f * m_fScale * 0.15f);
		blue = 0.35f - (0.35f * m_fScale * 0.15f);
	}
	else
	{
		red = 0.15f - (0.15f * m_fScale * 0.15f);
		green = 0.15f - (0.15f * m_fScale * 0.15f);
		blue = 0.4f - (0.4f * m_fScale * 0.15f);
	}

	if( ring )
	{
		ring->SetColor(red, green, blue, m_fFade);
		ring->SetRotationY( g_PI );
		ring->RotateY( m_fScale * 20.0f );
		ring->Scale( 3.5f, 10.0f, 3.5f );
		ring->SetTranslationXYZ(vDrawPos.x, vDrawPos.y, vDrawPos.z);
		ring->Render();
	}

	D3DVECTOR	vViewVec;
	vViewVec = pCMyApp->GetEyeDirection();

	if( effect_sort.num == 1 ) // 사릉가 신의 무기이면
	{
		red = 0.45f - (0.45f * m_fScale * 0.15f);
		green = 0.45f - (0.45f * m_fScale * 0.15f);
		blue = 0.45f - (0.45f * m_fScale * 0.15f);
	}
	else
	{
		red = 0.25f - (0.25f * m_fScale * 0.15f);
		green = 0.25f - (0.25f * m_fScale * 0.15f);
		blue = 0.75f - (0.75f * m_fScale * 0.15f);
	}

	GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_SHIELD ] ) );
	if( ground_corona )
	{
		ground_corona->SetColor(red*0.5f, green*0.5f, blue*0.5f, m_fFade*0.5f);
		ground_corona->SetRotationX( g_PI * 0.5f );
		ground_corona->Scale( m_fScale*1.5f, m_fScale*1.5f, m_fScale*1.5f );
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + m_fScale*3.0f, vDrawPos.z);
		ground_corona->Render();

		ground_corona->Scale( 1.5f, 1.5f, 1.5f );
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + m_fScale*2.5f, vDrawPos.z);
		ground_corona->Render();

		GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_CORONA ] ) );
		ground_corona->SetColor(red, green, blue, m_fFade);
		ground_corona->ReCreate(m_fScale * 0.25f);
		ground_corona->SetBillBoard(vViewVec, FALSE, 0.0f);
		ground_corona->Scale(m_fScale, m_fScale, 0.0f);
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + 12.0f, vDrawPos.z);
		ground_corona->Render();
	}

	if (effect_sort.nCurFrame >= 6 && effect_sort.nCurFrame < 8)
	{
		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));

		ef_sort.nType = FX_HORNBOOM;
		ef_sort.vPos = D3DVECTOR( effect_sort.vPos.x, effect_sort.vPos.y + 12.0f, effect_sort.vPos.z );
		ef_sort.Index = HIT_DRAGON;

		if (effect_sort.pMobTo)
			effect_sort.pMobTo->Attacked();
		else if (effect_sort.pNkChaTo)
			effect_sort.pNkChaTo->Attacked();

		g_pRoh->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
	}

//-------------------------------------------------------------------
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, dwLighting);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, dwZWrite);

	return bFinished;
}



void LHFX_GriffonRing::LoadRes()
{
	SAFE_DELETE(m_pCapsyong);
	SAFE_DELETE(m_pBpd);

	m_pCapsyong = new CCapsyong(g_pCapsyongTexture);
	if( VF_ERR_NONE > m_pCapsyong->Read("data/Npc/csy/legknock.CSY") )
	{
		SAFE_DELETE(m_pCapsyong);
		return;
	}


	// 진 데빌링과 일반 데빌링의 색 변경을 위한 버택스 셋의 생성. ///컨버젼무기
	CCsyObj *pCsy = NULL;
	pCsy = m_pCapsyong->m_Csy;
	if( pCsy )
	{
		m_GreenMouelVertexSet = new LAGVERTEX[ pCsy->m_VertexCount ];
		if( m_GreenMouelVertexSet )
			memcpy( m_GreenMouelVertexSet, pCsy->m_Vertices, sizeof(LAGVERTEX)*pCsy->m_VertexCount );

		m_RedMouelVertexSet   = new LAGVERTEX[ pCsy->m_VertexCount ];
		if( m_RedMouelVertexSet )
		{
			memcpy( m_RedMouelVertexSet, pCsy->m_Vertices, sizeof(LAGVERTEX)*pCsy->m_VertexCount );
			for(int i = 0; i < pCsy->m_VertexCount; i++) // 레드의 경우 색 변경.(그린은 원본대로 놔두면 된다.)
			{
				m_RedMouelVertexSet[i].diffuse = 0x00FFFF00;
			}
		}

		OriginalVertexPtr = pCsy->m_Vertices; // 원본의 참조포인터를 얻어둔다.
	}

	m_pBpd = new CBiped;
	if( m_pBpd->Read("data/Npc/bpd/legknock_attack.BPD") )
	{
		SAFE_DELETE(m_pBpd);
		return;
	}
}


LHFX_GriffonRing::LHFX_GriffonRing()
{
	m_pCapsyong = NULL;
	m_pBpd = NULL;

	ring = NULL;
	ring = new CCylinderPlane;
	if( ring )
		ring->Create( 8.0f, 8.0f, 15.0f, 20.0f, 0.0f, TRUE, 2.0f);

	ground_corona = NULL;
	ground_corona = new CRectPlane;
	if( ground_corona )
		ground_corona->Create( 10.0f, 10.0f, FALSE );

	OriginalVertexPtr = NULL; // 참조만 하는 포인터.
	m_GreenMouelVertexSet = NULL; // 색상 변환용 버택스 셋 ///컨버젼무기
	m_RedMouelVertexSet = NULL; // 색상 변환용 버택스 셋
}

LHFX_GriffonRing::~LHFX_GriffonRing()
{
	// 캡숑을 지우기 전에 캡숑안에 포인터를 엉켜놓은걸 정상화해줘야한다.
	CCsyObj *pCsy = NULL;

	pCsy = m_pCapsyong->m_Csy;
	if( pCsy )
		pCsy->m_Vertices = OriginalVertexPtr; // 원본의 참조포인터로 돌려준다.

	SAFE_DELETE(m_pCapsyong);
	SAFE_DELETE(m_pBpd);
	SAFE_DELETE(ring);
	SAFE_DELETE(ground_corona);

	SAFE_DELETE(m_GreenMouelVertexSet); ///컨버젼무기
	SAFE_DELETE(m_RedMouelVertexSet);
}

void LHFX_GriffonRing::DeleteRes()
{}

BOOL LHFX_GriffonRing::Render(EffectSort &effect_sort)
{
	if( !GET_D3DDEVICE() )
		return true;

	if(!effect_sort.pNkChaTo
			&& !effect_sort.pMobTo)
		return TRUE;

	BOOL bFinished = FALSE;
	D3DMATRIX matWorld, matTrans, matView;
	DWORD dwLighting, dwZWrite;

	GET_D3DDEVICE()->GetRenderState( D3DRENDERSTATE_LIGHTING, &dwLighting);
	GET_D3DDEVICE()->GetRenderState( D3DRENDERSTATE_ZWRITEENABLE, &dwZWrite);

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, FALSE);

	CCsyObj *pCsy;

// 	if( effect_sort.num == 1 ) // 진 데빌링이면.. ///컨버젼무기
// 	{
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCCOLOR  );
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_DESTCOLOR  );

	pCsy = m_pCapsyong->m_Csy;
	if( pCsy && m_RedMouelVertexSet )
		pCsy->m_Vertices = m_RedMouelVertexSet; // 포인터를 바꿔치기 한다.
// 	}
// 	else
// 	{
// 		GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_SRCBLEND,   D3DBLEND_ONE );
// 		GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_DESTBLEND,  D3DBLEND_ONE );
//
// 		pCsy = m_pCapsyong->m_Csy;
// 		if( pCsy && m_GreenMouelVertexSet )
// 			pCsy->m_Vertices = m_GreenMouelVertexSet; // 포인터를 바꿔치기 한다.
// 	}

	if (m_pCapsyong && m_pBpd)
	{
		float red, green, blue;
		red = green = blue = 0.9f;

		//m_pCapsyong->SetColor(red, green, blue, 0.2f);

		D3DMATRIX matRotate, matWorld;
		D3DUtil_SetIdentityMatrix( matTrans );
		D3DUtil_SetIdentityMatrix( matRotate );
		D3DUtil_SetIdentityMatrix( matWorld );
		pCMyApp->SetViewMatrix(matView);

		D3DUtil_SetScaleMatrix(matTrans, 0.7f,0.7f,0.7f);
		// D3DUtil_SetTranslateMatrix( matTrans, effect_sort.vPos.x, effect_sort.vPos.y, effect_sort.vPos.z);
		matTrans._41 = effect_sort.vPos.x;
		matTrans._42 = effect_sort.vPos.y;
		matTrans._43 = effect_sort.vPos.z;

		Nk3DUtil_SetRotateCCWYMatrix( matRotate, effect_sort.vCurPos.x);
		D3DMath_MatrixMultiply(matWorld, matRotate, matTrans);

		GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld );
		GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_VIEW, &matView);
		m_pCapsyong->Animate(m_pBpd, effect_sort.nCurFrame, TRUE, LINE_EFF_NONE,
							 &matWorld, &matView);
		m_pCapsyong->Render(GET_D3DDEVICE(), -1, FALSE, FALSE, NULL, effect_sort.nCurFrame);
	}

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE);

	//-------------------------------------------------------------------
	float maxScale, m_fScale, m_fFade;
	maxScale = 1.0f;
	m_fScale = (maxScale * effect_sort.nCurFrame) / FX_DEVILRING_FRAMECOUNT;
	m_fFade = 1.0f - (m_fScale * 0.3f);

	D3DVECTOR vDrawPos;
	vDrawPos = effect_sort.vPos;

	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
	GET_D3DDEVICE()->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
	if( g_pCapsyongTexture )
		GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_RING ] ) );

	float red, green, blue;
	red = green = blue = 0.0f;

// 	if( effect_sort.num == 1 ) // 진 데빌링이면.. ///컨버젼무기
	{
		red = 0.35f - (0.35f * m_fScale * 0.15f);
		green = 0.35f - (0.35f * m_fScale * 0.15f);
		blue = 0.35f - (0.35f * m_fScale * 0.15f);
	}
// 	else
// 	{
// 		red = 0.15f - (0.15f * m_fScale * 0.15f);
// 		green = 0.15f - (0.15f * m_fScale * 0.15f);
// 		blue = 0.4f - (0.4f * m_fScale * 0.15f);
// 	}

	if( ring )
	{
		ring->SetColor(red, green, blue, m_fFade);
		ring->SetRotationY( g_PI );
		ring->RotateY( m_fScale * 20.0f );
		ring->Scale( 3.5f, 10.0f, 3.5f );
		ring->SetTranslationXYZ(vDrawPos.x, vDrawPos.y, vDrawPos.z);
		ring->Render();
	}

	D3DVECTOR	vViewVec;
	vViewVec = pCMyApp->GetEyeDirection();

// 	if( effect_sort.num == 1 ) // 사릉가 신의 무기이면
	{
		red = 0.45f - (0.45f * m_fScale * 0.15f);
		green = 0.45f - (0.45f * m_fScale * 0.15f);
		blue = 0.45f - (0.45f * m_fScale * 0.15f);
	}
// 	else
// 	{
// 		red = 0.25f - (0.25f * m_fScale * 0.15f);
// 		green = 0.25f - (0.25f * m_fScale * 0.15f);
// 		blue = 0.75f - (0.75f * m_fScale * 0.15f);
// 	}

	GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_SHIELD ] ) );
	if( ground_corona )
	{
		float csy_scale;
		csy_scale = 0.1f;

		ground_corona->SetColor(red*0.5f, green*0.5f, blue*0.5f, m_fFade*0.5f);
		ground_corona->SetRotationX( g_PI * 0.5f );
		ground_corona->Scale( m_fScale*csy_scale, m_fScale*csy_scale, m_fScale*csy_scale );
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + m_fScale*3.0f, vDrawPos.z);
		ground_corona->Render();

		ground_corona->Scale( csy_scale, csy_scale, csy_scale );
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + m_fScale*2.5f, vDrawPos.z);
		ground_corona->Render();

		GET_D3DDEVICE()->SetTexture(0, g_pCapsyongTexture->GetSurfaceByIdx( g_EffectTextr[ EFF_FX_DRAGON_CORONA ] ) );
		ground_corona->SetColor(red, green, blue, m_fFade);
		ground_corona->ReCreate(m_fScale * 0.05f);
		ground_corona->SetBillBoard(vViewVec, FALSE, 0.0f);
		ground_corona->Scale(m_fScale, m_fScale, 0.0f);
		ground_corona->SetTranslationXYZ(vDrawPos.x, vDrawPos.y + 12.0f, vDrawPos.z);
		ground_corona->Render();
	}

	if (effect_sort.nCurFrame >= 6 && effect_sort.nCurFrame < 8)
	{
		EffectSort ef_sort;
		ZeroMemory(&ef_sort, sizeof(EffectSort));

		ef_sort.nType = FX_HORNBOOM;
		ef_sort.vPos = D3DVECTOR( effect_sort.vPos.x, effect_sort.vPos.y + 12.0f, effect_sort.vPos.z );
		ef_sort.Index = HIT_DRAGON;

		if (effect_sort.pMobTo)
			effect_sort.pMobTo->Attacked();
		else if (effect_sort.pNkChaTo)
			effect_sort.pNkChaTo->Attacked();

		g_pRoh->InsertEffectNum(pCMyApp->m_pFxSet->InsertFxEffect(ef_sort));
	}

	//-------------------------------------------------------------------
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, dwLighting);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, dwZWrite);

	return bFinished;
}
