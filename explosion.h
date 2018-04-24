//=============================================================================
//
// 入力処理 [explosion.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene2D.h"

//=============================================================================
// クラス
//=============================================================================
class CExplosion:public CScene2D
{
public:
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);
	static void Unlock(void);
	static CExplosion *Create( D3DXVECTOR3 pos );

	HRESULT Init (D3DXVECTOR3 pos );
	void Update(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
	int m_nLife;
	float m_fMx;
	float m_fMy;
	int m_nSpan;
	float m_fMoveX;
	float m_fMoveY;
};
#endif