//=============================================================================
//
// オブジェクトの処理 [scene.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_SCENE		(100)	// オブジェクトの最大数

//*********************************************************
// オブジェクトクラス
//*********************************************************
class CScene
{
public:
	//弾と敵との当り判定用に追記
	typedef enum{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOSION,
		OBJTYPE_MAX,
	}OBJTYPE;

	static CScene *GetScene(int nIdyScene);
	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);

	virtual void SetPosition (D3DXVECTOR3 pos)=0;
	virtual D3DXVECTOR3 GetPosition(void)=0;
	virtual float GetLength ( void )=0;

	CScene();
	virtual ~CScene();

	virtual HRESULT Init(void)= 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	//当り判定
	virtual BOOL Hit(int nDamage);

protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_SCENE];	// オブジェクトへのポインタ
	static int m_nNumScene;					// 総オブジェクト数

	int m_nID;								// 固有ID

	OBJTYPE m_objType;

};

#endif
