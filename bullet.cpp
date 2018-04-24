//=============================================================================
//
// バレット処理 [.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	TEXTURE_FILENAME_BULLET	"data/TEXTURE/billboard.png"	// 読み込むテクスチャファイル名

#define BULLET_POS_X (300.0f)   //ポリゴンの表示位置X
#define BULLET_POS_Y (180.0f)   //ポリゴンの表示位置Y
#define BULLET_POS_WIDTH (10.0f)//ポリゴンの幅
#define BULLET_POS_HEIGHT (10.0f)//ポリゴンの高さ

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
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;		//テクスチャのデータ保存


//=============================================================================
// クラス
//=============================================================================
CBullet::CBullet()
{
	//変数の初期化
	m_move.x =
	m_move.y =
	m_move.z = 0;

	//属性
	CBullet::SetObjType(OBJTYPE_BULLET);
}

//=============================================================================
// 
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// 
//=============================================================================
HRESULT CBullet::Load( void )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	if( m_pTexture == NULL )
	{
		//テクスチャ読み込み
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME_BULLET , &m_pTexture)))
		 {
			return E_FAIL;
		 }
	}
	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CBullet::Unlock(void)
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
CBullet *CBullet::Create( D3DXVECTOR3 pos , float moveY)//座標、速度
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CBullet *pBullet;
	pBullet = new CBullet;
	//pBullet->m

	pBullet->Init( pos , moveY);				//引数の数が人によって変わる

	//移動量の受け渡し
	//m_move.y = moveY;


	return pBullet;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos , float moveY)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャのバインド
	BindTexture( m_pTexture);

	//初期位置の設定
	m_pos = pos;
	m_move.y = moveY;

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
void CBullet::Update(void)
{
	//頂点の設置
	CBullet::SetVtx();

	//移動量の更新
	m_pos.y -= m_move.y;
	
	//フィールド外の削除処理
	if( m_pos.y < 0 )
	{
		CExplosion::Create(m_pos);
		CBullet::Release();
		CExplosion::Create(m_pos);
	}
	
	//敵との当り判定
	for( int nCntScene = 0 ; nCntScene < MAX_SCENE ; nCntScene++ )
	{
		
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);
	
		if( pScene != NULL )
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();
	
			if(objType == CScene::OBJTYPE_ENEMY)
			{
				D3DXVECTOR3 posEnemy;
				float		lengthEnemy;

				posEnemy = pScene->GetPosition();
				lengthEnemy = pScene->GetLength();

				//弾と敵が重なった時
				//左側_右側
				if( posEnemy.x - lengthEnemy <= m_pos.x && posEnemy.x + lengthEnemy >= m_pos.x )
				{
					//上側と下側
					if( posEnemy.y - lengthEnemy <= m_pos.y && posEnemy.y + lengthEnemy >= m_pos.y )
					{
 						CExplosion::Create(m_pos);		//爆発の生成
						//pScene->Uninit();			//エネミーリリース
						pScene->Hit(1);

						Release();			//バレット
						
					}
				}
			}
		}
		
	}

}