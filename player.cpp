//=============================================================================
//
// オブジェクトの処理 [player.cpp]
// Author :
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FILENAME		"data/TEXTURE/player000.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 静的変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;		//テクスチャのデータ保存

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer()
{
	//属性
	CPlayer::SetObjType(OBJTYPE_PLAYER);
	//CPlayer::BindTexture( TEXTURE_FILENAME );
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	//m_pos.x += 1;
	if( CManager::GetInputKeyboard()->GetKeyPress(DIK_A) == TRUE)
	{
		m_pos.x -= 10.0f;
	}
	if( CManager::GetInputKeyboard()->GetKeyPress(DIK_W) == TRUE)
	{
		m_pos.y -= 10.0f;
	}
	if( CManager::GetInputKeyboard()->GetKeyPress(DIK_D) == TRUE)
	{
		m_pos.x += 10.0f;
	}
	if( CManager::GetInputKeyboard()->GetKeyPress(DIK_S) == TRUE)
	{
		m_pos.y += 10.0f;
	}

	CPlayer::SetVtx();

	//バレット
	if( CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE) == TRUE)
	{
		CBullet::Create(CScene2D::m_pos , 10.0f );
	}

	CPlayer::SetPosition( CScene2D::m_pos );
}

//=============================================================================
// 生成
//=============================================================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	//初期化処理
	pPlayer->Init();

	//テクスチャ読み込み
	pPlayer->LoadTexture(TEXTURE_FILENAME);

	//return S_OK;

	//終了処理
	//CScene2D::Uninit();


	return pPlayer;
}

//=============================================================================
// 生成
//=============================================================================
CPlayer *CPlayer::Create(float fPosX , float fPosY)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	//初期化処理
	//pPlayer->Init();
	pPlayer->Init(D3DXVECTOR3(fPosX,fPosY,0.0f));
	
	pPlayer->LoadTexture(TEXTURE_FILENAME);

	//return S_OK;

	//終了処理
	//CScene2D::Uninit();


	return pPlayer;
}