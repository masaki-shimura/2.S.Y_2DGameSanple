//=============================================================================
//
// バレット処理 [.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	TEXTURE_FILENAME_EXPLOSION	"data/TEXTURE/explosion000.png"	// 読み込むテクスチャファイル名

#define EXPLOSION_POS_X (300.0f)		//ポリゴンの表示位置X
#define EXPLOSION_POS_Y (180.0f)		//ポリゴンの表示位置Y
#define EXPLOSION_POS_WIDTH (150.0f)	//ポリゴンの幅
#define EXPLOSION_POS_HEIGHT (180.0f)	//ポリゴンの高さ

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// 静的変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;		//テクスチャのデータ保存

//=============================================================================
// クラス
//=============================================================================
CExplosion::CExplosion()
{
	//変数の初期化
	m_nLife = 0;

	//属性
	CExplosion::SetObjType(OBJTYPE_EXPLOSION);
}

//=============================================================================
// 
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// 
//=============================================================================
HRESULT CExplosion::Load( void )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	if( m_pTexture == NULL )
	{
		//テクスチャ読み込み
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME_EXPLOSION , &m_pTexture)))
		 {
			return E_FAIL;
		 }
	}
	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CExplosion::Unlock(void)
{
	if( m_pTexture != NULL )
	{
		//テクスチャの破棄
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CExplosion *CExplosion::Create( D3DXVECTOR3 pos )//座標
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CExplosion *pExplosion;
	pExplosion = new CExplosion;
	//pBullet->m
	pExplosion->Init( pos );				//引数の数が人によって変わる

	return pExplosion;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャのバインド
	BindTexture( m_pTexture);

	//初期位置の設定
	m_pos = pos;

	//体力
	m_nLife = 100;
	m_nSpan = 10;

	//頂点バッファを生成
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		return E_FAIL;
	}

	//色情報の設定
	SetVtxColor(255,255,255,255);
	
	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CExplosion::Update(void)
{
	bool bTest = false;

	//頂点の設置
	bTest = CExplosion::SetVtx(0.125f,0.0f,3);

	//false処理
	if( bTest == true )
	{
		m_nLife = 0;
		CExplosion::Release();
	}
}