//=============================================================================
//
// マネージャーの処理 [manager.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "background.h"
#include "multiBackground.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FILENAME		"data/TEXTURE/player000.png"	// 読み込むテクスチャファイル名
#define	BG_TEXTURE_FILENAME000		"data/TEXTURE/bg100.png"	// 読み込むテクスチャファイル名
#define	BG_TEXTURE_FILENAME001		"data/TEXTURE/bg101.png"	// 読み込むテクスチャファイル名
#define	BG_TEXTURE_FILENAME002		"data/TEXTURE/bg102.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// 静的変数
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;			// レンダラーへのポインタ
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CScore *CManager::m_pScore = {NULL};

//=============================================================================
// CManagerコンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// CManagerデストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// レンダラーの生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance,hWnd);

	//背景生成
	CBackground::Create(0,0,BG_TEXTURE_FILENAME002,BGTYPE_1);
	CBackground::Create(0,0,BG_TEXTURE_FILENAME001,BGTYPE_2);
	CBackground::Create(0,0,BG_TEXTURE_FILENAME000,BGTYPE_3);

	//一枚ポリゴンで複数描画
	//CMultiBackground::Create(0.0f,0.0f,CMultiBackground::BGTYPE_1,3);

	// オブジェクトの生成
	CPlayer::Create(400,400);		//プレイヤー

	//エネミー
	for(int i = 0; i < 3 ; i++)
	{
		CEnemy::Create(150.0f * i + 300.0f ,100.0f,CEnemy::TYPE_EBI000);
		CEnemy::Create(150.0f * i + 300.0f ,150.0f,CEnemy::TYPE_IKA000);
		CEnemy::Create(150.0f * i + 350.0f ,200.0f,CEnemy::TYPE_KURO);
		CEnemy::Create(150.0f * i + 350.0f ,250.0f,CEnemy::TYPE_IKA000);
	}

	//スコアの実体を生成したのちポインタをm_pScoreに取得する
	m_pScore = CScore::Create(D3DXVECTOR3(1200,100,0),00000000);
	//m_pScore = CScore::Create(D3DXVECTOR3(500,300,0),87654321);
	//m_pScore = CScore::Create(D3DXVECTOR3(500,600,0),87654321);

	//テクスチャ読み込み
	CBullet::Load();
	CExplosion::Load();
	CNumber::Load();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// オブジェクトの破棄
	CScene2D::ReleaseAll();

	// レンダラーの破棄
	m_pRenderer->Uninit();

	if(m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	m_pRenderer->Update();
	m_pInputKeyboard->Update();

	//エネミー生成
	if( CManager::GetInputKeyboard()->GetKeyTrigger(DIK_R) == TRUE && CEnemy::m_nEnemyCount <= 0)
	{
		//エネミー
		for(int i = 0; i < 3 ; i++)
		{
			CEnemy::Create(150.0f * i + 300.0f ,100.0f,CEnemy::TYPE_EBI000);
			CEnemy::Create(150.0f * i + 300.0f ,150.0f,CEnemy::TYPE_IKA000);
			CEnemy::Create(150.0f * i + 350.0f ,200.0f,CEnemy::TYPE_KURO);
			CEnemy::Create(150.0f * i + 350.0f ,250.0f,CEnemy::TYPE_IKA000);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
	//CScene2D::DrawAll();
}

