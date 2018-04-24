//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author :
//
//=============================================================================
#include "scene2D.h"

//*********************************************************
// プレイヤークラス
//*********************************************************
class CPlayer : public CScene2D
{
public:
	CPlayer();
	~CPlayer();

	static CPlayer *Create(void);			//あとで引数指定
	static CPlayer *Create(float fPosX , float fPosY);			//あとで引数指定

	void Update (void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};