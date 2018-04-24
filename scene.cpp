//=============================================================================
//
// オブジェクトの処理 [scene.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// 静的変数
//*****************************************************************************
//CScene *g_pScene = NULL;
//CScene *g_apScene[] = {};
int CScene::m_nNumScene = 0;
CScene *CScene::m_apScene[MAX_SCENE] = {};

//CScene CScene::m_objType = OBJTYPE_NONE;


//=============================================================================
// CSceneコンストラクタ
//=============================================================================
CScene::CScene()
{
	for( int nCntScene = 0 ; nCntScene < MAX_SCENE ; nCntScene++ )
	{
		if(m_apScene[nCntScene]==NULL){
			m_apScene[nCntScene] = this;
			m_nID = nCntScene;
			m_nNumScene++;
			break;
		}
	}
}

//=============================================================================
// CSceneデストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// オブジェクトの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	for(int nCntScene = 0 ; nCntScene < MAX_SCENE ; nCntScene++ )
	{
		if(m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->Update();	
		}
	}
}
//=============================================================================
// オブジェクトの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for(int nCntScene = 0 ; nCntScene < MAX_SCENE ; nCntScene++ )
	{
		if(m_apScene[nCntScene]!=NULL)
		{
			m_apScene[nCntScene]->Draw();
		}
	}
}

//=============================================================================
// オブジェクトを全て破棄
//=============================================================================
void CScene::ReleaseAll(void)
{
	for(int nCntScene = 0 ; nCntScene < MAX_SCENE ; nCntScene++ )
	{
		if(m_apScene[nCntScene]!=NULL)
		{
			delete m_apScene[nCntScene];
			m_apScene[nCntScene] = NULL;
			m_nNumScene--;
		}
		if( m_nNumScene <= 0 )
		{
			break;
		}
	}
}

//=============================================================================
// オブジェクトを破棄
//=============================================================================
void CScene::Release(void)
{
	if( m_apScene[m_nID] != NULL ){
		int nID;
		nID = m_nID;
		delete m_apScene[nID];
		m_apScene[nID] = NULL;
		m_nNumScene--;
	}
}

//=============================================================================
// オブジェクトアドレスを返す
//=============================================================================
CScene *CScene::GetScene(int nIdyScene)
{
	return m_apScene[nIdyScene];
}

//=============================================================================
// オブジェクトのタイプを定義
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// オブジェクトのタイプを取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// ダミー関数
//=============================================================================
BOOL CScene::Hit(int nDamage)
{
	return false;
}