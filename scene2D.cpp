//=============================================================================
//
// 2Dオブジェクトの処理 [scene2D.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	TEXTURE_FILENAME		"data/TEXTURE/enemy000.png"	// 読み込むテクスチャファイル名

//追記
#define POLYGON_POS_X (300.0f)//ポリゴンの表示位置X
#define POLYGON_POS_Y (180.0f)//ポリゴンの表示位置Y
#define POLYGON_POS_WIDTH (50.0f)//ポリゴンの幅
#define POLYGON_POS_HEIGHT (50.0f)//ポリゴンの高さ

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


//=============================================================================
// CScene2D生成
// ポリゴンを只描画したい時に使用する
//=============================================================================
CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene2D;

	// CScene2Dの生成
	pScene2D = new CScene2D;
	pScene2D->Init();

	//テクスチャの読み込み
	//pScene2D->LoadTexture();

	return pScene2D;
}

//=============================================================================
// 
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//NULLチェックを入れない
	m_pTexture = pTexture;
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
void CScene2D::LoadTexture( )
{
	//m_bLoadTextureがtrueになったかどうかチェックする
	if( m_pTexture == NULL )
	{
		//デバイス取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// 初期テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME , &m_pTexture);

		//テクスチャの読み込み
		m_bLoadTexture = true;
		
	}
}

//=============================================================================
// オーバーロード::テクスチャ読み込み
//=============================================================================
void CScene2D::LoadTexture( const char TexPass[] )
{
	//m_bLoadTextureがtrueになったかどうかチェックする
	if( m_pTexture == NULL )
	{
		//デバイス取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//テクスチャのデータ呼び出し
		D3DXCreateTextureFromFile( pDevice , &TexPass[0] , &m_pTexture);

		//テクスチャの読み込み
		m_bLoadTexture = true;
		
	}
}
//=============================================================================
// CScene2Dコンストラクタ
//=============================================================================
CScene2D::CScene2D()
{
	//バッファの初期化
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	//座標の初期化
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	
	//幅、高さの初期化
	m_fWidth = POLYGON_POS_WIDTH;
	m_fHeight = POLYGON_POS_HEIGHT;
	
	//半径取得
	m_fLength = sqrt( m_fWidth * m_fWidth + m_fHeight * m_fHeight );

	//頂点の角度
	m_fAngle = atan2( m_fWidth , m_fHeight );

	m_fRot = 0.0f;

	m_fMx = 0.0f;
	m_fMy = 0.0f;

	FpsCnt = 0;
}

//=============================================================================
// CScene2Dデストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init( void )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの位置を設定
	//m_pos = pos;

	// 頂点バッファを生成
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		//return E_FAIL;
	}

	CScene2D::BindTexture(m_pTexture);

	CScene2D::SetVtx();
	SetVtxColor(255,255,255,255);

	return S_OK;
}

//=============================================================================
// 初期化処理 オーバーロード
//=============================================================================
HRESULT CScene2D::Init( D3DXVECTOR3 pos )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの位置を設定
	m_pos = pos;

	// テクスチャの読み込み
	//D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME , &m_pTexture);

	// 頂点バッファを生成
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		//return E_FAIL;
	}

	CScene2D::SetVtx();
	SetVtxColor(255,255,255,255);

	return S_OK;
}

//=============================================================================
// 初期化処理 オーバーロード
//=============================================================================
HRESULT CScene2D::Init( D3DXVECTOR3 pos , float fWidth , float fHeight )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ポリゴンの位置を設定
	m_pos = pos;
	m_fWidth  = fWidth;	
	m_fHeight = fHeight;

	//半径取得
	m_fLength = sqrt( m_fWidth * m_fWidth + m_fHeight * m_fHeight );

	//頂点の角度
	m_fAngle = atan2( m_fWidth , m_fHeight );

	// テクスチャの読み込み
	//D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME , &m_pTexture);

	// 頂点バッファを生成
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		//return E_FAIL;
	}

	//CScene2D::SetVtx();
	SetVtxColor(255,255,255,255);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene2D::Uninit(void)
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

	// オブジェクトの破棄
	CScene::Release();

	//テクスチャの破棄
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2D::Update(void)
{
	// ポリゴンの更新処理


}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2D::Draw(void)
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
// 描画処理
//=============================================================================
void CScene2D::Draw(LPDIRECT3DTEXTURE9 pTexture , int i)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// ポリゴンの描画処理

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource( 0 , m_pVtxBuff , 0 , sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_2D );

	// テクスチャの設定
	pDevice->SetTexture(0,pTexture);
	
	// ポリゴンの描画
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// ポジションセット関数
//=============================================================================
void CScene2D::SetPosition( D3DXVECTOR3 pos )
{
	m_pos = pos;
}

//=============================================================================
// ポジションセット関数
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// 半径取得
//=============================================================================
float CScene2D::GetLength(void)
{
	return m_fLength;
}

//=============================================================================
// 位置のみ
//=============================================================================
void CScene2D::SetVtxPos (void)
{
		// 頂点情報を設定
	VERTEX_2D* pVtx ={ NULL};				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳
		pVtx[ 0 ].pos = D3DXVECTOR3( cos( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//左↑
	pVtx[ 1 ].pos = D3DXVECTOR3( cos( -m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//左↑
	pVtx[ 2 ].pos = D3DXVECTOR3( cos( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//左↑
	pVtx[ 3 ].pos = D3DXVECTOR3( cos( m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//左↑
	m_pVtxBuff->Unlock();
}

void CScene2D::SetVtxUV(float x , float y)
{
	m_fMx += x;
	m_fMy += y;
	// 頂点情報を設定
	VERTEX_2D* pVtx ={ NULL};				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳

	//頂点データへUVデータの追加/テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f + m_fMx , 0.0f + m_fMy);//左↑
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f + m_fMx , 0.0f + m_fMy);//右↑
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f + m_fMx , 1.0f + m_fMy);//左下
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f + m_fMx , 1.0f + m_fMy);//右↓

	m_pVtxBuff->Unlock();
}

void CScene2D::SetVtxUVMulti(float x , float y , int i)
{
	m_fMxMulti[i] += x;
	m_fMyMulti[i] += y;

	// 頂点情報を設定
	VERTEX_2D* pVtx ={ NULL};				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳

	//頂点データへUVデータの追加/テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f + m_fMxMulti[i] , 0.0f + m_fMyMulti[i]);//左↑
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f + m_fMxMulti[i] , 0.0f + m_fMyMulti[i]);//右↑
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f + m_fMxMulti[i] , 1.0f + m_fMyMulti[i]);//左下
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f + m_fMxMulti[i] , 1.0f + m_fMyMulti[i]);//右↓

	m_pVtxBuff->Unlock();
}
//=============================================================================
// 頂点参照用関数 
// 説明
// 縦、横
//=============================================================================
void CScene2D::SetVtxWidthHeight(void)
{
	// 頂点情報を設定
	VERTEX_2D* pVtx ={ NULL};				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳
	//位置
	pVtx[ 0 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y, 0.0f );//左↑
	pVtx[ 1 ].pos = D3DXVECTOR3( m_pos.x + m_fWidth , m_pos.y , 0.0f );//右↑
	pVtx[ 2 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y + m_fHeight, 0.0f );//左↓
	pVtx[ 3 ].pos = D3DXVECTOR3( m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f );//右下

	// rhwの設定（必ず1.0f）
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	//頂点データへUVデータの追加/テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f , 0.0f );//左↑
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f , 0.0f );//右↑
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f , 1.0f );//左下
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f , 1.0f );//右↓
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 頂点参照用関数 
// 説明
// プレイヤーやエネミーなどで、頂点を動かしたいやつにせっとする。
//=============================================================================
void CScene2D::SetVtx (void)
{
	
	// 頂点情報を設定
	VERTEX_2D* pVtx ={ NULL};				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳
#if 0
	pVtx[ 0 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y, 0.0f );//左↑
	pVtx[ 1 ].pos = D3DXVECTOR3( m_pos.x + POLYGON_POS_WIDTH , m_pos.y , 0.0f );//右↑
	pVtx[ 2 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y + POLYGON_POS_HEIGHT, 0.0f );//左↓
	pVtx[ 3 ].pos = D3DXVECTOR3( m_pos.x + POLYGON_POS_WIDTH, m_pos.y + POLYGON_POS_HEIGHT, 0.0f );//右下
#else
	
	pVtx[ 0 ].pos = D3DXVECTOR3( cos( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//左↑
	pVtx[ 1 ].pos = D3DXVECTOR3( cos( -m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//左↑
	pVtx[ 2 ].pos = D3DXVECTOR3( cos( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//左↑
	pVtx[ 3 ].pos = D3DXVECTOR3( cos( m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//左↑
#endif

	// rhwの設定（必ず1.0f）
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	// 頂点カラーの設定（0～255の整数値）
	//pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	//頂点データへUVデータの追加/テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f , 0.0f );//左↑
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f , 0.0f );//右↑
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f , 1.0f );//左下
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f , 1.0f );//右↓
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 頂点参照用関数 
// 説明
// プレイヤーやエネミーなどで、頂点を動かしたいやつにせっとする。
// テクスチャアニメーション
//=============================================================================
BOOL CScene2D::SetVtx ( float UVmoveX , float UVmoveY , int nSpan)
{
	
	// 頂点情報を設定
	VERTEX_2D* pVtx ={ NULL};				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳
#if 0
	pVtx[ 0 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y, 0.0f );//左↑
	pVtx[ 1 ].pos = D3DXVECTOR3( m_pos.x + POLYGON_POS_WIDTH , m_pos.y , 0.0f );//右↑
	pVtx[ 2 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y + POLYGON_POS_HEIGHT, 0.0f );//左↓
	pVtx[ 3 ].pos = D3DXVECTOR3( m_pos.x + POLYGON_POS_WIDTH, m_pos.y + POLYGON_POS_HEIGHT, 0.0f );//右下
#else

	pVtx[ 0 ].pos = D3DXVECTOR3( cos( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//左↑
	pVtx[ 1 ].pos = D3DXVECTOR3( cos( -m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//左↑
	pVtx[ 2 ].pos = D3DXVECTOR3( cos( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//左↑
	pVtx[ 3 ].pos = D3DXVECTOR3( cos( m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//左↑
#endif

	// rhwの設定（必ず1.0f）
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	// 頂点カラーの設定（0～255の整数値）
	//pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		
	pVtx[ 0 ].tex = D3DXVECTOR2( m_fMx + 0 , 0 );								//左↑0~
	pVtx[ 1 ].tex = D3DXVECTOR2( m_fMx + 0 + 0.125f , 0 );							//右↑
	pVtx[ 2 ].tex = D3DXVECTOR2( m_fMx + 0 , 1 );							//左下
	pVtx[ 3 ].tex = D3DXVECTOR2( m_fMx + 0 + 0.125f , 1 );				//右↓

	m_pVtxBuff->Unlock();

	FpsCnt++;

	//テクスチャアニメーション
	m_fMx = m_fMx + UVmoveX * ( FpsCnt % nSpan == 0 );
	m_fMy = m_fMx + UVmoveY * ( FpsCnt % ( nSpan * 5 ) == 0 );

	if(m_fMx >= 1.0f)
	{
		return true;
	}

	//float修正
	m_fMx = m_fMx - m_fMx * ( m_fMx >= 1.0f );

	return false;
}

void CScene2D::SetVtxColor(int r,int g,int b,int a)
{
	// 頂点情報を設定
	VERTEX_2D* pVtx ={ NULL};				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳
	// 頂点カラーの設定（0～255の整数値）
	pVtx[ 0 ].col = D3DCOLOR_RGBA( r, g, b, a );
	pVtx[ 1 ].col = D3DCOLOR_RGBA( r, g, b, a );
	pVtx[ 2 ].col = D3DCOLOR_RGBA( r, g, b, a );
	pVtx[ 3 ].col = D3DCOLOR_RGBA( r, g, b, a );
	m_pVtxBuff->Unlock();
}

void CScene2D::SetWidthHeight( float fWidth , float fHeight )
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//半径取得
	m_fLength = sqrt( m_fWidth * m_fWidth + m_fHeight * m_fHeight );
	//頂点の角度
	m_fAngle = atan2( m_fWidth , m_fHeight );
}