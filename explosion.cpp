//=============================================================================
//
// �o���b�g���� [.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	TEXTURE_FILENAME_EXPLOSION	"data/TEXTURE/explosion000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define EXPLOSION_POS_X (300.0f)		//�|���S���̕\���ʒuX
#define EXPLOSION_POS_Y (180.0f)		//�|���S���̕\���ʒuY
#define EXPLOSION_POS_WIDTH (150.0f)	//�|���S���̕�
#define EXPLOSION_POS_HEIGHT (180.0f)	//�|���S���̍���

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
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;		//�e�N�X�`���̃f�[�^�ۑ�

//=============================================================================
// �N���X
//=============================================================================
CExplosion::CExplosion()
{
	//�ϐ��̏�����
	m_nLife = 0;

	//����
	CExplosion::SetObjType(OBJTYPE_EXPLOSION);
}

//=============================================================================
// 
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// 
//=============================================================================
HRESULT CExplosion::Load( void )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	if( m_pTexture == NULL )
	{
		//�e�N�X�`���ǂݍ���
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME_EXPLOSION , &m_pTexture)))
		 {
			return E_FAIL;
		 }
	}
	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CExplosion::Unlock(void)
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
CExplosion *CExplosion::Create( D3DXVECTOR3 pos )//���W
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CExplosion *pExplosion;
	pExplosion = new CExplosion;
	//pBullet->m
	pExplosion->Init( pos );				//�����̐����l�ɂ���ĕς��

	return pExplosion;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̃o�C���h
	BindTexture( m_pTexture);

	//�����ʒu�̐ݒ�
	m_pos = pos;

	//�̗�
	m_nLife = 100;
	m_nSpan = 10;

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
void CExplosion::Update(void)
{
	bool bTest = false;

	//���_�̐ݒu
	bTest = CExplosion::SetVtx(0.125f,0.0f,3);

	//false����
	if( bTest == true )
	{
		m_nLife = 0;
		CExplosion::Release();
	}
}