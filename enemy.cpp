//=============================================================================
//
// �I�u�W�F�N�g�̏��� [player.cpp]
// Author :
//
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ENEMY_FILENAME000		"data/TEXTURE/enemy000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ENEMY_FILENAME001		"data/TEXTURE/enemy001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_ENEMY_FILENAME002		"data/TEXTURE/enemy002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MOVECNT (10)
#define MOVECNTTIME (10)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
int CEnemy::m_nEnemyCount = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy()
{
	//����
	CEnemy::SetObjType(OBJTYPE_ENEMY);

	//�G�l�~�[�̏��
	m_State = STATE_NOMAL;
	m_Type = TYPE_NONE;
	m_nEnemyCount++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
	m_nEnemyCount--;
}

//=============================================================================
// ������
//=============================================================================
void CEnemy::Init(float fPosX , float fPosY)
{
	m_pos.x = fPosX;
	m_pos.y = fPosY;

	CScene2D::Init();

	//�̗͂̐ݒ�
	m_nLife = 2;
	//�e�N�X�`���̃o�C���h
	//BindTexture( m_pTexture);
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	//�G�l�~�[�̏��
	switch(m_State)
	{
	case STATE_NOMAL:
		//�G�l�~�[�̊p�x��ς���
		FpsCnt++;
		if(FpsCnt > 0 && FpsCnt < 10)
			m_fRot += 0.01f;

		if(FpsCnt > 10 && FpsCnt < 20)
			m_fRot -= 0.01f;

		if(FpsCnt > 20 && FpsCnt < 30)
			m_fRot -= 0.01f;

		if(FpsCnt > 30 && FpsCnt < 40)
			m_fRot += 0.01f;

		if(FpsCnt > 40)
			FpsCnt = 0;
		break;
	case STATE_DAMAGE:

		//�J�E���g�J�n
		m_nCounterState--;

		//�̗͂��Ȃ��Ȃ�����
		if(m_nCounterState <= 0)
		{
			//�m�[�}����Ԃɖ߂�
			m_State = STATE_NOMAL;

			//�F��߂�
			SetVtxColor(255,255,255,255);
		}
		break;
	}

	//�G�l�~�[�̍U��

	CEnemy::SetVtx();

	//�o���b�g
	//if(  )
	//{
	//	CBullet::Create(CScene2D::m_pos , 1.0f );
	//}

	CEnemy::SetPosition( CScene2D::m_pos );
	
}

//=============================================================================
// ����
//=============================================================================
CEnemy *CEnemy::Create( float fPosX , float fPosY , TYPE type)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy;

	//����������
	pEnemy->Init(fPosX,fPosY);

	//�e�N�X�`���[�̉摜�K�p
	switch(type)
	{
	case TYPE_EBI000:
		pEnemy->LoadTexture(TEXTURE_ENEMY_FILENAME000);
		break;
	case TYPE_IKA000:
		pEnemy->LoadTexture(TEXTURE_ENEMY_FILENAME001);
		break;
	case TYPE_KURO:
		pEnemy->LoadTexture(TEXTURE_ENEMY_FILENAME002);
		break;
	}

	//return S_OK;

	//�I������
	//CScene2D::Uninit();

	return pEnemy;
}

HRESULT CEnemy::Load(void)
{
	if( m_pTexture == NULL )
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//�e�N�X�`���ǂݍ���
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , TEXTURE_ENEMY_FILENAME000 , &m_pTexture)))
		 {
			return E_FAIL;
		 }
	}
	return S_OK;
}

void CEnemy::UnLoad(void)
{
	if( m_pTexture != NULL )
	{
		//�e�N�X�`���̔j��
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���蔻��
//=============================================================================
BOOL CEnemy::Hit(int nDamage)
{
	//�l�ɂ���Ă͏����R�[�h�𓱓�

	//�_���[�W����
	m_nLife -= nDamage;

	//���������񂾂�
	if(m_nLife <= 0)
	{
		//�����G�t�F�N�g
		CExplosion::Create(m_pos);	//�����̐���

		//�T�E���h�G�t�F�N�g

		//�X�R�A�̉��Z
		CScore *pScore = CManager::GetScore();
		
		pScore->AddScore(10);

		//�I������
		Uninit();

		//���񂾃t���O
		return TRUE;
	}
	else
	{
		//��Ԃ̐ݒ�
		m_State = STATE_DAMAGE;

		//�p�����Ԃ̐ݒ�
		m_nCounterState = 10;
	
		//�F�̐ݒ�
		SetVtxColor(255,0,0,255);

		return FALSE;
	}
}