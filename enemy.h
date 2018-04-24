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
class CEnemy : public CScene2D
{
public:
	//�G�̏��
	typedef enum{
		STATE_NOMAL = 0,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	//�G�l�~�[�̃^�C�v
		typedef enum{
		TYPE_NONE,
		TYPE_EBI000,
		TYPE_IKA000,
		TYPE_KURO,
		TYPE_MAX
	}TYPE;

	//�ʏ폈��
	CEnemy();
	~CEnemy();
	static HRESULT Load(void);
	static void UnLoad(void);
	static CEnemy *Create( float fPosX , float fPosY , TYPE type);			//���Ƃň����w��
	
	void Init(float fPosX , float fPosY);
	void Update (void);

	//�_���[�W����
	BOOL Hit(int nDamage);		//�߂�l�͐������
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��
	int m_nLife;	//�̗�
	STATE m_State;	//���
	TYPE  m_Type;	//�^�C�v
	int m_nCounterState;	//��ԃJ�E���^


public:
	static int m_nEnemyCount;
};