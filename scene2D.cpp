//=============================================================================
//
// 2D�I�u�W�F�N�g�̏��� [scene2D.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	TEXTURE_FILENAME		"data/TEXTURE/enemy000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//�ǋL
#define POLYGON_POS_X (300.0f)//�|���S���̕\���ʒuX
#define POLYGON_POS_Y (180.0f)//�|���S���̕\���ʒuY
#define POLYGON_POS_WIDTH (50.0f)//�|���S���̕�
#define POLYGON_POS_HEIGHT (50.0f)//�|���S���̍���

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


//=============================================================================
// CScene2D����
// �|���S������`�悵�������Ɏg�p����
//=============================================================================
CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene2D;

	// CScene2D�̐���
	pScene2D = new CScene2D;
	pScene2D->Init();

	//�e�N�X�`���̓ǂݍ���
	//pScene2D->LoadTexture();

	return pScene2D;
}

//=============================================================================
// 
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//NULL�`�F�b�N�����Ȃ�
	m_pTexture = pTexture;
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
void CScene2D::LoadTexture( )
{
	//m_bLoadTexture��true�ɂȂ������ǂ����`�F�b�N����
	if( m_pTexture == NULL )
	{
		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �����e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME , &m_pTexture);

		//�e�N�X�`���̓ǂݍ���
		m_bLoadTexture = true;
		
	}
}

//=============================================================================
// �I�[�o�[���[�h::�e�N�X�`���ǂݍ���
//=============================================================================
void CScene2D::LoadTexture( const char TexPass[] )
{
	//m_bLoadTexture��true�ɂȂ������ǂ����`�F�b�N����
	if( m_pTexture == NULL )
	{
		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//�e�N�X�`���̃f�[�^�Ăяo��
		D3DXCreateTextureFromFile( pDevice , &TexPass[0] , &m_pTexture);

		//�e�N�X�`���̓ǂݍ���
		m_bLoadTexture = true;
		
	}
}
//=============================================================================
// CScene2D�R���X�g���N�^
//=============================================================================
CScene2D::CScene2D()
{
	//�o�b�t�@�̏�����
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	//���W�̏�����
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	
	//���A�����̏�����
	m_fWidth = POLYGON_POS_WIDTH;
	m_fHeight = POLYGON_POS_HEIGHT;
	
	//���a�擾
	m_fLength = sqrt( m_fWidth * m_fWidth + m_fHeight * m_fHeight );

	//���_�̊p�x
	m_fAngle = atan2( m_fWidth , m_fHeight );

	m_fRot = 0.0f;

	m_fMx = 0.0f;
	m_fMy = 0.0f;

	FpsCnt = 0;
}

//=============================================================================
// CScene2D�f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init( void )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	//m_pos = pos;

	// ���_�o�b�t�@�𐶐�
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		//return E_FAIL;
	}

	CScene2D::BindTexture(m_pTexture);

	CScene2D::SetVtx();
	SetVtxColor(255,255,255,255);

	return S_OK;
}

//=============================================================================
// ���������� �I�[�o�[���[�h
//=============================================================================
HRESULT CScene2D::Init( D3DXVECTOR3 pos )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	m_pos = pos;

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME , &m_pTexture);

	// ���_�o�b�t�@�𐶐�
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		//return E_FAIL;
	}

	CScene2D::SetVtx();
	SetVtxColor(255,255,255,255);

	return S_OK;
}

//=============================================================================
// ���������� �I�[�o�[���[�h
//=============================================================================
HRESULT CScene2D::Init( D3DXVECTOR3 pos , float fWidth , float fHeight )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	m_pos = pos;
	m_fWidth  = fWidth;	
	m_fHeight = fHeight;

	//���a�擾
	m_fLength = sqrt( m_fWidth * m_fWidth + m_fHeight * m_fHeight );

	//���_�̊p�x
	m_fAngle = atan2( m_fWidth , m_fHeight );

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile( pDevice , TEXTURE_FILENAME , &m_pTexture);

	// ���_�o�b�t�@�𐶐�
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &m_pVtxBuff , NULL) ) ){
		//return E_FAIL;
	}

	//CScene2D::SetVtx();
	SetVtxColor(255,255,255,255);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
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

	// �I�u�W�F�N�g�̔j��
	CScene::Release();

	//�e�N�X�`���̔j��
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{
	// �|���S���̍X�V����


}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
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
// �`�揈��
//=============================================================================
void CScene2D::Draw(LPDIRECT3DTEXTURE9 pTexture , int i)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// �|���S���̕`�揈��

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource( 0 , m_pVtxBuff , 0 , sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_2D );

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,pTexture);
	
	// �|���S���̕`��
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// �|�W�V�����Z�b�g�֐�
//=============================================================================
void CScene2D::SetPosition( D3DXVECTOR3 pos )
{
	m_pos = pos;
}

//=============================================================================
// �|�W�V�����Z�b�g�֐�
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// ���a�擾
//=============================================================================
float CScene2D::GetLength(void)
{
	return m_fLength;
}

//=============================================================================
// �ʒu�̂�
//=============================================================================
void CScene2D::SetVtxPos (void)
{
		// ���_����ݒ�
	VERTEX_2D* pVtx ={ NULL};				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������
		pVtx[ 0 ].pos = D3DXVECTOR3( cos( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//����
	pVtx[ 1 ].pos = D3DXVECTOR3( cos( -m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//����
	pVtx[ 2 ].pos = D3DXVECTOR3( cos( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//����
	pVtx[ 3 ].pos = D3DXVECTOR3( cos( m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//����
	m_pVtxBuff->Unlock();
}

void CScene2D::SetVtxUV(float x , float y)
{
	m_fMx += x;
	m_fMy += y;
	// ���_����ݒ�
	VERTEX_2D* pVtx ={ NULL};				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������

	//���_�f�[�^��UV�f�[�^�̒ǉ�/�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f + m_fMx , 0.0f + m_fMy);//����
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f + m_fMx , 0.0f + m_fMy);//�E��
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f + m_fMx , 1.0f + m_fMy);//����
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f + m_fMx , 1.0f + m_fMy);//�E��

	m_pVtxBuff->Unlock();
}

void CScene2D::SetVtxUVMulti(float x , float y , int i)
{
	m_fMxMulti[i] += x;
	m_fMyMulti[i] += y;

	// ���_����ݒ�
	VERTEX_2D* pVtx ={ NULL};				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������

	//���_�f�[�^��UV�f�[�^�̒ǉ�/�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f + m_fMxMulti[i] , 0.0f + m_fMyMulti[i]);//����
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f + m_fMxMulti[i] , 0.0f + m_fMyMulti[i]);//�E��
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f + m_fMxMulti[i] , 1.0f + m_fMyMulti[i]);//����
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f + m_fMxMulti[i] , 1.0f + m_fMyMulti[i]);//�E��

	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�Q�Ɨp�֐� 
// ����
// �c�A��
//=============================================================================
void CScene2D::SetVtxWidthHeight(void)
{
	// ���_����ݒ�
	VERTEX_2D* pVtx ={ NULL};				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������
	//�ʒu
	pVtx[ 0 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y, 0.0f );//����
	pVtx[ 1 ].pos = D3DXVECTOR3( m_pos.x + m_fWidth , m_pos.y , 0.0f );//�E��
	pVtx[ 2 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y + m_fHeight, 0.0f );//����
	pVtx[ 3 ].pos = D3DXVECTOR3( m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f );//�E��

	// rhw�̐ݒ�i�K��1.0f�j
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	//���_�f�[�^��UV�f�[�^�̒ǉ�/�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f , 0.0f );//����
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f , 0.0f );//�E��
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f , 1.0f );//����
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f , 1.0f );//�E��
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���_�Q�Ɨp�֐� 
// ����
// �v���C���[��G�l�~�[�ȂǂŁA���_�𓮂���������ɂ����Ƃ���B
//=============================================================================
void CScene2D::SetVtx (void)
{
	
	// ���_����ݒ�
	VERTEX_2D* pVtx ={ NULL};				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������
#if 0
	pVtx[ 0 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y, 0.0f );//����
	pVtx[ 1 ].pos = D3DXVECTOR3( m_pos.x + POLYGON_POS_WIDTH , m_pos.y , 0.0f );//�E��
	pVtx[ 2 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y + POLYGON_POS_HEIGHT, 0.0f );//����
	pVtx[ 3 ].pos = D3DXVECTOR3( m_pos.x + POLYGON_POS_WIDTH, m_pos.y + POLYGON_POS_HEIGHT, 0.0f );//�E��
#else
	
	pVtx[ 0 ].pos = D3DXVECTOR3( cos( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//����
	pVtx[ 1 ].pos = D3DXVECTOR3( cos( -m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//����
	pVtx[ 2 ].pos = D3DXVECTOR3( cos( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//����
	pVtx[ 3 ].pos = D3DXVECTOR3( cos( m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//����
#endif

	// rhw�̐ݒ�i�K��1.0f�j
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	// ���_�J���[�̐ݒ�i0�`255�̐����l�j
	//pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	//���_�f�[�^��UV�f�[�^�̒ǉ�/�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f , 0.0f );//����
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f , 0.0f );//�E��
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f , 1.0f );//����
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f , 1.0f );//�E��
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���_�Q�Ɨp�֐� 
// ����
// �v���C���[��G�l�~�[�ȂǂŁA���_�𓮂���������ɂ����Ƃ���B
// �e�N�X�`���A�j���[�V����
//=============================================================================
BOOL CScene2D::SetVtx ( float UVmoveX , float UVmoveY , int nSpan)
{
	
	// ���_����ݒ�
	VERTEX_2D* pVtx ={ NULL};				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������
#if 0
	pVtx[ 0 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y, 0.0f );//����
	pVtx[ 1 ].pos = D3DXVECTOR3( m_pos.x + POLYGON_POS_WIDTH , m_pos.y , 0.0f );//�E��
	pVtx[ 2 ].pos = D3DXVECTOR3( m_pos.x, m_pos.y + POLYGON_POS_HEIGHT, 0.0f );//����
	pVtx[ 3 ].pos = D3DXVECTOR3( m_pos.x + POLYGON_POS_WIDTH, m_pos.y + POLYGON_POS_HEIGHT, 0.0f );//�E��
#else

	pVtx[ 0 ].pos = D3DXVECTOR3( cos( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//����
	pVtx[ 1 ].pos = D3DXVECTOR3( cos( -m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + m_fRot ) * m_fLength + m_pos.y,
								 0.0f );//����
	pVtx[ 2 ].pos = D3DXVECTOR3( cos( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.x,
								 sin( -m_fAngle + D3DX_PI + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//����
	pVtx[ 3 ].pos = D3DXVECTOR3( cos( m_fAngle + m_fRot ) * m_fLength + m_pos.x,
								 sin( m_fAngle + m_fRot ) * m_fLength + m_pos.y,
							 0.0f );//����
#endif

	// rhw�̐ݒ�i�K��1.0f�j
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	// ���_�J���[�̐ݒ�i0�`255�̐����l�j
	//pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	//pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		
	pVtx[ 0 ].tex = D3DXVECTOR2( m_fMx + 0 , 0 );								//����0~
	pVtx[ 1 ].tex = D3DXVECTOR2( m_fMx + 0 + 0.125f , 0 );							//�E��
	pVtx[ 2 ].tex = D3DXVECTOR2( m_fMx + 0 , 1 );							//����
	pVtx[ 3 ].tex = D3DXVECTOR2( m_fMx + 0 + 0.125f , 1 );				//�E��

	m_pVtxBuff->Unlock();

	FpsCnt++;

	//�e�N�X�`���A�j���[�V����
	m_fMx = m_fMx + UVmoveX * ( FpsCnt % nSpan == 0 );
	m_fMy = m_fMx + UVmoveY * ( FpsCnt % ( nSpan * 5 ) == 0 );

	if(m_fMx >= 1.0f)
	{
		return true;
	}

	//float�C��
	m_fMx = m_fMx - m_fMx * ( m_fMx >= 1.0f );

	return false;
}

void CScene2D::SetVtxColor(int r,int g,int b,int a)
{
	// ���_����ݒ�
	VERTEX_2D* pVtx ={ NULL};				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������
	// ���_�J���[�̐ݒ�i0�`255�̐����l�j
	pVtx[ 0 ].col = D3DCOLOR_RGBA( r, g, b, a );
	pVtx[ 1 ].col = D3DCOLOR_RGBA( r, g, b, a );
	pVtx[ 2 ].col = D3DCOLOR_RGBA( r, g, b, a );
	pVtx[ 3 ].col = D3DCOLOR_RGBA( r, g, b, a );
	m_pVtxBuff->Unlock();
}

void CScene2D::SetWidthHeight( float fWidth , float fHeight )
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//���a�擾
	m_fLength = sqrt( m_fWidth * m_fWidth + m_fHeight * m_fHeight );
	//���_�̊p�x
	m_fAngle = atan2( m_fWidth , m_fHeight );
}