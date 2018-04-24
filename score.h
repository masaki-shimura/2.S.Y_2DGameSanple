//=============================================================================
//
// ���͏��� [score.cpp]
// Author : MASAKI SHIMURA
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "number.h"
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCORE_MAX (8)

//=============================================================================
// �N���X
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

	static CScore *Create(D3DXVECTOR3 pos , int nValue);		//�l�ɂ���Ă͈������ς��

	void AddScore(int Value);

	int GetScore(void);
	void SetPos(int, D3DXVECTOR3 pos);

private:
	CNumber *m_apNumber[SCORE_MAX];	//������
	D3DXVECTOR3 m_pos;		//�ʒu
	int m_nScore;			//�X�R�A�l
	//static int m_nScore;			//�X�R�A�l
	float m_fLength;
};
#endif