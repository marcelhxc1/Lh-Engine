#include "stdafx.h"
// FxIceBlot.cpp: implementation of the CFxIceBlot class.
//
//////////////////////////////////////////////////////////////////////

#define D3D_OVERLOADS

#include <d3d.h>
#include <time.h>
#include <assert.h>
#include "FxSet.h"
#include "main.h"
#include "D3DMath.h"
#include "D3DUtil.h"
#include "sfxUtil.h"
#include "SFXBaseShape.h"
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
#include "FxIceBlot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFxIceBlot::CFxIceBlot()
{
	m_pLolo = NULL;
}

CFxIceBlot::~CFxIceBlot()
{
	SAFE_DELETE(m_pLolo);
}

void CFxIceBlot::LoadRes()
{
	PFILE *fpLolo = NULL;

	if (!m_pLolo)
	{
		m_pLolo = new CLolos;
		m_pLolo->SetIndexedTexture( g_pCapsyongTexture );
		m_pLolo->Read("data/effect/lolos/k_icebolt.LOL");
	}



}

void CFxIceBlot::DeleteRes()
{}

void CFxIceBlot::Render(EffectSort &effect_sort)
{
	if( !GET_D3DDEVICE() )
		return;

	if( !effect_sort.pNkChaFrom )
		return;

	if( !effect_sort.pNkChaTo && !effect_sort.pMobTo )
		return;

	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_LIGHTING, FALSE);
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_SRCBLEND,   D3DBLEND_SRCALPHA );
	GET_D3DDEVICE()->SetRenderState( D3DRENDERSTATE_DESTBLEND,  D3DBLEND_ONE);

	DWORD  dwTextureState[3];

	GET_D3DDEVICE()->GetTextureStageState( 0, D3DTSS_ALPHAARG1, &dwTextureState[0] );
	GET_D3DDEVICE()->GetTextureStageState( 0, D3DTSS_ALPHAARG2, &dwTextureState[1] );
	GET_D3DDEVICE()->GetTextureStageState( 0, D3DTSS_ALPHAOP,   &dwTextureState[2] );

	GET_D3DDEVICE()->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	GET_D3DDEVICE()->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	GET_D3DDEVICE()->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );

	D3DMATRIX matTrans, matRotate, matWorld, matS;
	LPDIRECTDRAWSURFACE7 lpSurface = NULL;

	D3DUtil_SetRotateYMatrix(matRotate, -effect_sort.pNkChaFrom->m_dir);
	if (effect_sort.pMobTo)
		D3DUtil_SetTranslateMatrix( matTrans, effect_sort.pMobTo->m_wx, effect_sort.pMobTo->m_wy + 20.0f, effect_sort.pMobTo->m_wz);
	else if (effect_sort.pNkChaTo)
		D3DUtil_SetTranslateMatrix( matTrans, effect_sort.pNkChaTo->m_wx, effect_sort.pNkChaTo->m_wy + 20.0f, effect_sort.pNkChaTo->m_wz);

	D3DUtil_SetScaleMatrix( matS, 6.5f,6.5f, 6.5f );
	D3DMath_MatrixMultiply( matWorld, matRotate, matTrans );
	D3DMath_MatrixMultiply( matWorld, matS, matWorld );
	GET_D3DDEVICE()->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld );
	if( m_pLolo && effect_sort.nCurFrame > 17 )
		m_pLolo->Render(GET_D3DDEVICE(), effect_sort.nCurFrame, FALSE, FALSE);

	GET_D3DDEVICE()->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwTextureState[0] );
	GET_D3DDEVICE()->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwTextureState[1] );
	GET_D3DDEVICE()->SetTextureStageState( 0, D3DTSS_ALPHAOP,   dwTextureState[2] );
}