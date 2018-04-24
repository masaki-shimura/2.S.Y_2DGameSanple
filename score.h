//=============================================================================
//
// 入力処理 [score.cpp]
// Author : MASAKI SHIMURA
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "number.h"
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SCORE_MAX (8)

//=============================================================================
// クラス
//=============================================================================
class CScore : public CScene
{
public:
	CScore();
	~CScore();

	HRESULT Init(void);
	HRESULT Init( D3DXVECTOR3 pos , int value);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition (D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	float GetLength ( void );

	static CScore *Create(D3DXVECTOR3 pos , int nValue);		//人によっては引数が変わる

	void AddScore(int Value);

	int GetScore(void);
	void SetPos(int, D3DXVECTOR3 pos);

private:
	CNumber *m_apNumber[SCORE_MAX];	//桁数字
	D3DXVECTOR3 m_pos;		//位置
	int m_nScore;			//スコア値
	//static int m_nScore;			//スコア値
	float m_fLength;
};
#endif