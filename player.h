//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author :
//
//=============================================================================
#include "scene2D.h"

//*********************************************************
// �v���C���[�N���X
//*********************************************************
class CPlayer : public CScene2D
{
public:
	CPlayer();
	~CPlayer();

	static CPlayer *Create(void);			//���Ƃň����w��
	static CPlayer *Create(float fPosX , float fPosY);			//���Ƃň����w��

	void Update (void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};