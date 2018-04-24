//=============================================================================
//
// オブジェクトの処理 [scene.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define TEXTURE_FILENAME_NUMBER "data/TEXTURE/score.png"
#define NUMBER_WIDTH  (50.0f)
#define NUMBER_HEIGHT (50.0f)
#define NUMBER_POS_WIDTH ( -30.0f)
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
LPDIRECT3DTEXTURE9 CNumber::m_pTexture;

//=============================================================================
// Numberコンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	
	//追記 中心座標
	//半径取得
	m_fLength = sqrt( NUMBER_WIDTH * NUMBER_WIDTH + NUMBER_HEIGHT * NUMBER_HEIGHT );

	//頂点の角度
	m_fAngle = atan2( NUMBER_WIDTH , NUMBER_HEIGHT );

	m_fRot = 0.0f;

	m_fMx = 0.0f;
	m_fMy = 0.0f;
	FpsCnt = 0;
}

//=============================================================================
// CSceneデストラクタ
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// 
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = pos;

	// 頂点バッファを生成
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CNumber::Uninit(void)
{
	// テクスチャの開放
	if( m_pTexture != NULL ){
		m_pTexture->Release();									// Direct3Dデバイス（インターフェース）の解放
		m_pTexture = NULL;
	}

	// 頂点バッファの開放
	if( m_pVtxBuff != NULL ){
		m_pVtxBuff->Release();									// Direct3Dデバイス（インターフェース）の解放
		m_pVtxBuff = NULL;
	}

	//オブジェクト破棄？
}

//=============================================================================
// 
//=============================================================================
void CNumber::Update(void)
{
	
}

//=============================================================================
// 
//=============================================================================
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// ポリゴンの描画処理

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource( 0 , m_pVtxBuff , 0 , sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_2D );

	// テクスチャの設定
	pDevice->SetTexture(0,m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// 
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos)
{
	//変数の宣言
	CNumber *pNumber;

	//生成
	pNumber = new CNumber;

	//初期化処理
	pNumber->Init(pos);

	//先頭アドレスを返す
	return pNumber;
}

//=============================================================================
// 
//=============================================================================
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャが読み込まれていない場合
	if( m_pTexture == NULL )
	{
		//テクスチャ読み込み
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME_NUMBER , &m_pTexture)))
		 {
			return E_FAIL;
		 }
	}

	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CNumber::Unload(void)
{
	if( m_pTexture != NULL )
	{
		//テクスチャの破棄
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// 
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	//変数の宣言
	float Value = 0;

	//計算処理
	Value = nNumber * 0.1f;

	// 頂点情報を設定
	VERTEX_2D* pVtx ={ NULL};				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳

	pVtx[ 0 ].pos = D3DXVECTOR3( cos( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//左↑

	pVtx[ 1 ].pos = D3DXVECTOR3( cos( -m_fAngle + m_fRot ) * m_fLength + m_pos.x + NUMBER_POS_WIDTH,
								 sin( -m_fAngle + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//左↑

	pVtx[ 2 ].pos = D3DXVECTOR3( cos( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//左↑

	pVtx[ 3 ].pos = D3DXVECTOR3( cos( m_fAngle + m_fRot ) * m_fLength + m_pos.x + NUMBER_POS_WIDTH,
								 sin( m_fAngle + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//左↑

	// rhwの設定（必ず1.0f）
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	// 頂点カラーの設定（0～255の整数値）
	pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	//頂点データへUVデータの追加/テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f + Value , 0.0f );//左↑
	pVtx[ 1 ].tex = D3DXVECTOR2( 0.1f + Value , 0.0f );//右↑
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f + Value , 1.0f );//左下
	pVtx[ 3 ].tex = D3DXVECTOR2( 0.1f + Value , 1.0f );//右↓
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 
//=============================================================================
void CNumber::SetVtx(void)
{

}

//=============================================================================
// 
//=============================================================================