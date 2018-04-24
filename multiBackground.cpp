//=============================================================================
//
// 背景の処理 [background.cpp]
// Author :
//
//=============================================================================
#include "multiBackground.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MULTIBG_TEXTURE_FILENAME000		"data/TEXTURE/bg100.png"	// 読み込むテクスチャファイル名
#define	MULTIBG_TEXTURE_FILENAME001		"data/TEXTURE/bg101.png"	// 読み込むテクスチャファイル名
#define	MULTIBG_TEXTURE_FILENAME002		"data/TEXTURE/bg102.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 静的変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMultiBackground::m_pTexture[MULTIBACKGROUND_MAX] = {NULL};		//テクスチャ情報
int CMultiBackground::m_NumberOfsheets = 0;											//背景の枚数
float CMultiBackground::uv_x[MULTIBACKGROUND_MAX] = {NULL};							//uv情報
float CMultiBackground::uv_y[MULTIBACKGROUND_MAX] = {NULL};							//uv情報

//=============================================================================
// コンストラクタ
//=============================================================================
CMultiBackground::CMultiBackground()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CMultiBackground::~CMultiBackground()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CMultiBackground *CMultiBackground::Create(float fPosX , float fPosY , MULTIBGTYPE type, int NumberOfsheets)
{
	//生成処理
	CMultiBackground *pBg;
	pBg = new CMultiBackground;

	//初期化
	pBg->Init(D3DXVECTOR3(fPosX,fPosY,0.0f),SCREEN_WIDTH,SCREEN_HEIGHT);

	//枚数データの保存
	m_NumberOfsheets = NumberOfsheets;

	//テクスチャ読み込み
	CMultiBackground::Load();

	return pBg;
}

//=============================================================================
// 更新処理
//=============================================================================
void CMultiBackground::Update(void)
{
	CMultiBackground::SetVtxWidthHeight();

	for( int i = 0; i < MULTIBACKGROUND_MAX ; i++ )
	{
		//キー入力時に背景移動
		if( CManager::GetInputKeyboard()->GetKeyPress(DIK_A) == TRUE)
		{
			uv_x[i] = 0.001f;
		}else if( CManager::GetInputKeyboard()->GetKeyPress(DIK_D) == TRUE)
		{
			uv_x[i] = -0.001f;
		}else
		{
			uv_x[i] = 0.0f;
		}
	}
}

void CMultiBackground::Draw(void)
{

	for( int i = 0; i < MULTIBACKGROUND_MAX ; i++ )
	{
		//強制スクロール
		switch(i)
		{
		case 0:
			uv_x[i] *= 1.0f;
			CMultiBackground::SetVtxUVMulti(0.0f + uv_x[i],-0.0001f,i);
			break;

		case 1:
			uv_x[i] *= 0.8f;
			CMultiBackground::SetVtxUVMulti(0.0f + uv_x[i],-0.002f,i);
		break;

		case 2:
			uv_x[i] *= 0.6f;
			CMultiBackground::SetVtxUVMulti(0.0f + uv_x[i],-0.003f,i);
			break;
		}
		
		CScene2D::Draw(m_pTexture[i],i);
	}
}

HRESULT CMultiBackground::Load( void )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	if( m_pTexture[0] == NULL )
	{
		//テクスチャ読み込み
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , MULTIBG_TEXTURE_FILENAME000 , &m_pTexture[0])))
		 {
			return E_FAIL;
		 }
	}

	if( m_pTexture[1] == NULL )
	{
		//テクスチャ読み込み
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , MULTIBG_TEXTURE_FILENAME001 , &m_pTexture[1])))
		 {
			return E_FAIL;
		 }
	}

	if( m_pTexture[2] == NULL )
	{
		//テクスチャ読み込み
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , MULTIBG_TEXTURE_FILENAME002 , &m_pTexture[2])))
		 {
			return E_FAIL;
		 }
	}
	return S_OK;
}