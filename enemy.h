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
class CEnemy : public CScene2D
{
public:
	//敵の状態
	typedef enum{
		STATE_NOMAL = 0,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	//エネミーのタイプ
		typedef enum{
		TYPE_NONE,
		TYPE_EBI000,
		TYPE_IKA000,
		TYPE_KURO,
		TYPE_MAX
	}TYPE;

	//通常処理
	CEnemy();
	~CEnemy();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CEnemy *Create( float fPosX , float fPosY , TYPE type);			//あとで引数指定
	
	void Init(float fPosX , float fPosY);
	void Update (void);

	//ダメージ処理
	BOOL Hit(int nDamage);		//戻り値は生死情報
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
	int m_nLife;	//体力
	STATE m_State;	//状態
	TYPE  m_Type;	//タイプ
	int m_nCounterState;	//状態カウンタ


public:
	static int m_nEnemyCount;
};