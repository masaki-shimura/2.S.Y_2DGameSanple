//=============================================================================
//
// オブジェクトの処理 [player.cpp]
// Author :
//
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ENEMY_FILENAME000		"data/TEXTURE/enemy000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ENEMY_FILENAME001		"data/TEXTURE/enemy001.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_ENEMY_FILENAME002		"data/TEXTURE/enemy002.png"	// 読み込むテクスチャファイル名
#define MOVECNT (10)
#define MOVECNTTIME (10)
//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// 静的変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
int CEnemy::m_nEnemyCount = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy()
{
	//属性
	CEnemy::SetObjType(OBJTYPE_ENEMY);

	//エネミーの状態
	m_State = STATE_NOMAL;
	m_Type = TYPE_NONE;
	m_nEnemyCount++;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
	m_nEnemyCount--;
}

//=============================================================================
// 初期化
//=============================================================================
void CEnemy::Init(float fPosX , float fPosY)
{
	m_pos.x = fPosX;
	m_pos.y = fPosY;

	CScene2D::Init();

	//体力の設定
	m_nLife = 2;
	//テクスチャのバインド
	//BindTexture( m_pTexture);
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	//エネミーの状態
	switch(m_State)
	{
	case STATE_NOMAL:
		//エネミーの角度を変える
		FpsCnt++;
		if(FpsCnt > 0 && FpsCnt < 10)
			m_fRot += 0.01f;

		if(FpsCnt > 10 && FpsCnt < 20)
			m_fRot -= 0.01f;

		if(FpsCnt > 20 && FpsCnt < 30)
			m_fRot -= 0.01f;

		if(FpsCnt > 30 && FpsCnt < 40)
			m_fRot += 0.01f;

		if(FpsCnt > 40)
			FpsCnt = 0;
		break;
	case STATE_DAMAGE:

		//カウント開始
		m_nCounterState--;

		//体力がなくなったら
		if(m_nCounterState <= 0)
		{
			//ノーマル状態に戻す
			m_State = STATE_NOMAL;

			//色を戻す
			SetVtxColor(255,255,255,255);
		}
		break;
	}

	//エネミーの攻撃

	CEnemy::SetVtx();

	//バレット
	//if(  )
	//{
	//	CBullet::Create(CScene2D::m_pos , 1.0f );
	//}

	CEnemy::SetPosition( CScene2D::m_pos );
	
}

//=============================================================================
// 生成
//=============================================================================
CEnemy *CEnemy::Create( float fPosX , float fPosY , TYPE type)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;

	//初期化処理
	pEnemy->Init(fPosX,fPosY);

	//テクスチャーの画像適用
	switch(type)
	{
	case TYPE_EBI000:
		pEnemy->LoadTexture(TEXTURE_ENEMY_FILENAME000);
		break;
	case TYPE_IKA000:
		pEnemy->LoadTexture(TEXTURE_ENEMY_FILENAME001);
		break;
	case TYPE_KURO:
		pEnemy->LoadTexture(TEXTURE_ENEMY_FILENAME002);
		break;
	}

	//return S_OK;

	//終了処理
	//CScene2D::Uninit();

	return pEnemy;
}

HRESULT CEnemy::Load(void)
{
	if( m_pTexture == NULL )
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//テクスチャ読み込み
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , TEXTURE_ENEMY_FILENAME000 , &m_pTexture)))
		 {
			return E_FAIL;
		 }
	}
	return S_OK;
}

void CEnemy::UnLoad(void)
{
	if( m_pTexture != NULL )
	{
		//テクスチャの破棄
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// 当り判定
//=============================================================================
BOOL CEnemy::Hit(int nDamage)
{
	//人によっては処理コードを導入

	//ダメージ処理
	m_nLife -= nDamage;

	//もしも死んだら
	if(m_nLife <= 0)
	{
		//爆発エフェクト
		CExplosion::Create(m_pos);	//爆発の生成

		//サウンドエフェクト

		//スコアの加算
		CScore *pScore = CManager::GetScore();
		
		pScore->AddScore(10);

		//終了処理
		Uninit();

		//死んだフラグ
		return TRUE;
	}
	else
	{
		//状態の設定
		m_State = STATE_DAMAGE;

		//継続時間の設定
		m_nCounterState = 10;
	
		//色の設定
		SetVtxColor(255,0,0,255);

		return FALSE;
	}
}