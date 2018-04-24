//=============================================================================
//
// �I�u�W�F�N�g�̏��� [scene.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define TEXTURE_FILENAME_NUMBER "data/TEXTURE/score.png"
#define NUMBER_WIDTH  (50.0f)
#define NUMBER_HEIGHT (50.0f)
#define NUMBER_POS_WIDTH ( -30.0f)
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
LPDIRECT3DTEXTURE9 CNumber::m_pTexture;

//=============================================================================
// Number�R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	
	//�ǋL ���S���W
	//���a�擾
	m_fLength = sqrt( NUMBER_WIDTH * NUMBER_WIDTH + NUMBER_HEIGHT * NUMBER_HEIGHT );

	//���_�̊p�x
	m_fAngle = atan2( NUMBER_WIDTH , NUMBER_HEIGHT );

	m_fRot = 0.0f;

	m_fMx = 0.0f;
	m_fMy = 0.0f;
	FpsCnt = 0;
}

//=============================================================================
// CScene�f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// 
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = pos;

	// ���_�o�b�t�@�𐶐�
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CNumber::Uninit(void)
{
	// �e�N�X�`���̊J��
	if( m_pTexture != NULL ){
		m_pTexture->Release();									// Direct3D�f�o�C�X�i�C���^�[�t�F�[�X�j�̉��
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if( m_pVtxBuff != NULL ){
		m_pVtxBuff->Release();									// Direct3D�f�o�C�X�i�C���^�[�t�F�[�X�j�̉��
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�j���H
}

//=============================================================================
// 
//=============================================================================
void CNumber::Update(void)
{
	
}

//=============================================================================
// 
//=============================================================================
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// �|���S���̕`�揈��

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource( 0 , m_pVtxBuff , 0 , sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_2D );

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// 
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos)
{
	//�ϐ��̐錾
	CNumber *pNumber;

	//����
	pNumber = new CNumber;

	//����������
	pNumber->Init(pos);

	//�擪�A�h���X��Ԃ�
	return pNumber;
}

//=============================================================================
// 
//=============================================================================
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`�����ǂݍ��܂�Ă��Ȃ��ꍇ
	if( m_pTexture == NULL )
	{
		//�e�N�X�`���ǂݍ���
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME_NUMBER , &m_pTexture)))
		 {
			return E_FAIL;
		 }
	}

	return S_OK;
}

//=============================================================================
// 
//=============================================================================
void CNumber::Unload(void)
{
	if( m_pTexture != NULL )
	{
		//�e�N�X�`���̔j��
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// 
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	//�ϐ��̐錾
	float Value = 0;

	//�v�Z����
	Value = nNumber * 0.1f;

	// ���_����ݒ�
	VERTEX_2D* pVtx ={ NULL};				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������

	pVtx[ 0 ].pos = D3DXVECTOR3( cos( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//����

	pVtx[ 1 ].pos = D3DXVECTOR3( cos( -m_fAngle + m_fRot ) * m_fLength + m_pos.x + NUMBER_POS_WIDTH,
								 sin( -m_fAngle + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//����

	pVtx[ 2 ].pos = D3DXVECTOR3( cos( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//����

	pVtx[ 3 ].pos = D3DXVECTOR3( cos( m_fAngle + m_fRot ) * m_fLength + m_pos.x + NUMBER_POS_WIDTH,
								 sin( m_fAngle + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//����

	// rhw�̐ݒ�i�K��1.0f�j
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	// ���_�J���[�̐ݒ�i0�`255�̐����l�j
	pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	//���_�f�[�^��UV�f�[�^�̒ǉ�/�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f + Value , 0.0f );//����
	pVtx[ 1 ].tex = D3DXVECTOR2( 0.1f + Value , 0.0f );//�E��
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f + Value , 1.0f );//����
	pVtx[ 3 ].tex = D3DXVECTOR2( 0.1f + Value , 1.0f );//�E��
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 
//=============================================================================
void CNumber::SetVtx(void)
{

}

//=============================================================================
// 
//=============================================================================