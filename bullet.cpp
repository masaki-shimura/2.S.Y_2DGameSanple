//=============================================================================
//
// �o���b�g���� [.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	TEXTURE_FILENAME_BULLET	"data/TEXTURE/billboard.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define BULLET_POS_X (300.0f)   //�|���S���̕\���ʒuX
#define BULLET_POS_Y (180.0f)   //�|���S���̕\���ʒuY
#define BULLET_POS_WIDTH (10.0f)//�|���S���̕�
#define BULLET_POS_HEIGHT (10.0f)//�|���S���̍���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;		//�e�N�X�`���̃f�[�^�ۑ�


//=============================================================================
// �N���X
//=============================================================================
CBullet::CBullet()
{
	//�ϐ��̏�����
	m_move.x =
	m_move.y =
	m_move.z = 0;

	//����
	CBullet::SetObjType(OBJTYPE_BULLET);
}

//=============================================================================
// 
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// 
//=============================================================================
HRESULT CBullet::Load( void )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	if( m_pTexture == NULL )
	{
		//�e�N�X�`���ǂݍ���
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME_BULLET , &m_pTexture)))
		 {
			return E_FAIL;
		 }
	}
	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CBullet::Unlock(void)
{
	if( m_pTexture != NULL )
	{
		//�e�N�X�`���̔j��
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// ��������
//=============================================================================
CBullet *CBullet::Create( D3DXVECTOR3 pos , float moveY)//���W�A���x
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CBullet *pBullet;
	pBullet = new CBullet;
	//pBullet->m

	pBullet->Init( pos , moveY);				//�����̐����l�ɂ���ĕς��

	//�ړ��ʂ̎󂯓n��
	//m_move.y = moveY;


	return pBullet;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos , float moveY)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̃o�C���h
	BindTexture( m_pTexture);

	//�����ʒu�̐ݒ�
	m_pos = pos;
	m_move.y = moveY;

	//���_�o�b�t�@�𐶐�
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		return E_FAIL;
	}
	
	//�F���̐ݒ�
	SetVtxColor(255,255,255,255);
	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CBullet::Update(void)
{
	//���_�̐ݒu
	CBullet::SetVtx();

	//�ړ��ʂ̍X�V
	m_pos.y -= m_move.y;
	
	//�t�B�[���h�O�̍폜����
	if( m_pos.y < 0 )
	{
		CExplosion::Create(m_pos);
		CBullet::Release();
		CExplosion::Create(m_pos);
	}
	
	//�G�Ƃ̓��蔻��
	for( int nCntScene = 0 ; nCntScene < MAX_SCENE ; nCntScene++ )
	{
		
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);
	
		if( pScene != NULL )
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();
	
			if(objType == CScene::OBJTYPE_ENEMY)
			{
				D3DXVECTOR3 posEnemy;
				float		lengthEnemy;

				posEnemy = pScene->GetPosition();
				lengthEnemy = pScene->GetLength();

				//�e�ƓG���d�Ȃ�����
				//����_�E��
				if( posEnemy.x - lengthEnemy <= m_pos.x && posEnemy.x + lengthEnemy >= m_pos.x )
				{
					//�㑤�Ɖ���
					if( posEnemy.y - lengthEnemy <= m_pos.y && posEnemy.y + lengthEnemy >= m_pos.y )
					{
 						CExplosion::Create(m_pos);		//�����̐���
						//pScene->Uninit();			//�G�l�~�[�����[�X
						pScene->Hit(1);

						Release();			//�o���b�g
						
					}
				}
			}
		}
		
	}

}