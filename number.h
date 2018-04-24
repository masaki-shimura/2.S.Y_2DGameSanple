//=============================================================================
//
// 入力処理 [number.cpp]
// Author : MASAKI SHIMURA
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// クラス
//=============================================================================
class CNumber{
public:
	CNumber();
	~CNumber();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber *Create(D3DXVECTOR3 pos);		//人によっては引数が変わる
	static HRESULT Load(void);
	static void Unload(void);
	void SetNumber(int nNumber);

	void SetVtx(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9  m_pVtxBuff;

	//ひとによっては
	D3DXVECTOR3		m_pos;

	//追記
	float m_fAngle;
	float m_fRot;
	float m_fLength;

	int FpsCnt;
	float m_fMx;
	float m_fMy;
};
#endif