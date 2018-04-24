//=============================================================================
//
// 入力処理 [input.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene2D.h"

//============================================================================
// クラス
//=============================================================================
class CBullet:public CScene2D
{
public:
	CBullet();
	~CBullet();
	static HRESULT Load(void);
	static void Unlock(void);
	static CBullet *Create( D3DXVECTOR3 pos , float moveY);

	HRESULT Init (D3DXVECTOR3 pos , float moveY);
	void Update(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
	D3DXVECTOR3 m_move;							//移動量
	int mnLife;
};

#endif