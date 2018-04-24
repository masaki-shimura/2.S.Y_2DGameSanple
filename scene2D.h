//=============================================================================
//
// 2Dオブジェクトの処理 [scene2D.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*********************************************************
// 2Dオブジェクトクラス
//*********************************************************
class CScene2D : public CScene
{
public:
	CScene2D();
	~CScene2D();

	static CScene2D *Create(void);

	virtual HRESULT Init( void );
	virtual HRESULT Init( D3DXVECTOR3 pos );
	virtual HRESULT Init( D3DXVECTOR3 pos , float fWidth , float fHeight );

	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Draw(LPDIRECT3DTEXTURE9 pTexture , int DrawCnt);
	

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void LoadTexture(  );//人によって引数が違う
	void LoadTexture( const char TexPass[] );

	void SetPosition ( D3DXVECTOR3 pos );
	void SetWidthHeight( float fWidth , float fHeight );
	D3DXVECTOR3 GetPosition ( void );
	float GetLength ( void );

	//頂点参照用関数
	void SetVtx( void );//中心座標
	void SetVtxUV(float x , float y);//UV操作用
	void SetVtxUVMulti(float x , float y ,int i);//UV操作用
	void SetVtxWidthHeight(void);
	BOOL CScene2D::SetVtx ( float UVmoveX , float UVmoveY , int nSpan);
	void SetVtxPos( void );
	void SetVtxColor(int r,int g,int b,int a);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	bool m_bLoadTexture;//テクスチャ読み込んだかどうか

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						// ポリゴンの位置

	//追記
	float m_fAngle;		//角度
	float m_fRot;		//回転率
	float m_fLength;	//半径
	int FpsCnt;			//アニメーション用カウント
	float m_fMx;		//texのuv値操作用
	float m_fMy;
	float m_fWidth;		//幅
	float m_fHeight;	//高さ

	float m_fMxMulti[3];		//texのuv値操作用
	float m_fMyMulti[3];
};

#endif
