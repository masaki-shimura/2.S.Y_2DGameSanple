//=============================================================================
//
// ���͏��� [input.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene2D.h"

//============================================================================
// �N���X
//=============================================================================
class CBullet:public CScene2D
{
public:
	CBullet();
	~CBullet();
	static HRESULT Load(void);
	static void Unlock(void);
	static CBullet *Create( D3DXVECTOR3 pos , float moveY);

	HRESULT Init (D3DXVECTOR3 pos , float moveY);
	void Update(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��
	D3DXVECTOR3 m_move;							//�ړ���
	int mnLife;
};

#endif