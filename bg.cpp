//------------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------------
#include "main.h"
#include "polygon.h"//�������g�̃C���N���[�h�t�@�C���͎g�����ȊO�K�v�Ȃ�,C++�΂ɂ��Ȃ��Ă͂����Ȃ�

//------------------------------------------------------
//�}�N��
//------------------------------------------------------
#define BG_POS_X (350.0f)								//�|���S���̕\���ʒuX
#define BG_POS_Y (180.0f)								//�|���S���̕\���ʒuY
#define BG_POS_WIDTH (243.0f * 0.8f)					//�|���S���̕�
#define BG_POS_HEIGHT (432.0f * 0.8f)					//�|���S���̍���
#define BG_TEXTURENAME "data/TEXTURE/bg000.jpg"			//�e�N�X�`���̒ǉ�

//png,jpg,tga,bmp,dds  ��������jpg,tga,dds
//------------------------------------------------------
//�O���[�o���ϐ�
//------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBG = NULL;			//���_�o�b�t�@�Ǘ��p
//�폜�@�@VERTEX_2D g_aVertex[ NUM_VERTEX ];							//���_���i�[�p�z��
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;				//�e�N�X�`���C���^�[�t�F�[�X�ւ̃|�C���^

//------------------------------------------------------
//�v���g�^�C�v�錾
//------------------------------------------------------
HRESULT MakeVertexBG ( LPDIRECT3DDEVICE9 pDevice );		//���_�̍쐬

//------------------------------------------------------
//�����������֐�
//------------------------------------------------------
HRESULT InitBG ( void )
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//BG�ݒ�
	MakeVertexBG ( pDevice );

	//�e�N�X�`���[�̓ǂݍ���/��񂵂��ǂݍ��߂Ȃ�
	D3DXCreateTextureFromFile( pDevice , BG_TEXTURENAME , &g_pTextureBG);

	//�ǂݍ��݃G���[
	if(FAILED(D3DXCreateTextureFromFile(pDevice,BG_TEXTURENAME,&g_pTextureBG))){
		MessageBox( NULL , "�ǂݍ��݃G���[�ł��B" , "Error" , MB_YESNOCANCEL | MB_ICONASTERISK | MB_DEFBUTTON3 );
		return E_FAIL;
	}
}

//------------------------------------------------------
//�I�������֐�
//------------------------------------------------------
void UninitBG ( void )//������鏇�ԁ@�|���S���@�f�o�C�X�@�_�C���N�g�RD�@�����
{
	//vtx�o�b�t�@�[�|���S���̂��Еt��
	if( g_pVtxBufferBG != NULL ){
	g_pVtxBufferBG->Release();									// Direct3D�f�o�C�X�i�C���^�[�t�F�[�X�j�̉��
	g_pVtxBufferBG = NULL;
	}

	if( g_pTextureBG != NULL ){
		g_pTextureBG->Release();									// Direct3D�f�o�C�X�i�C���^�[�t�F�[�X�j�̉��
		g_pTextureBG = NULL;
	}


}

//------------------------------------------------------
//�X�V�����֐�
//------------------------------------------------------
void UpdateBG ( void )
{

}

//------------------------------------------------------
//�`�揈���֐�
//------------------------------------------------------
void DrawBG( void )
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�p�C�v���C��(�X�g���[���Z�b�g),��O������offset�A�܂�p�ӂ������_�o�b�t�@�̓r������o�͉\
	pDevice->SetStreamSource( 0 , g_pVtxBufferBG , 0 , sizeof(VERTEX_2D) );

	//�|���S���`�������O��
	pDevice->SetTexture(0,g_pTextureBG);
	//�t�H�H�H��Ɖ�
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_2D );										// ���܂��炱��ŏ�����

	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP ,
							0 ,						//�I�t�Z�b�g(���_��)
							NUM_POLYGON );			//�v���~�e�B�u��/�|���S�����������́H

	//��L�ɏ�������
	// �v���~�e�B�u�i�|���S���j�̕`��
	//pDevice->DrawPrimitiveUP(
	//	D3DPT_TRIANGLESTRIP,														// �v���~�e�B�u�̎��
	//	NUM_BG,															// �v���~�e�B�u�̐�
	//	&g_aVertex[ 0 ],														// ���_�f�[�^�̐擪�A�h���X
	//	sizeof(VERTEX_2D));														// ���_�f�[�^�P���̃T�C�Y�ibyte�j
}

//------------------------------------------------------
//�|���S���̒��_���쐬
//------------------------------------------------------
HRESULT MakeVertexBG ( LPDIRECT3DDEVICE9 pDevice )
{
	//����ق����o�b�t�@�[�T�C�Y���擾(��̒��_�~���_��)							//�������Ǘ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX ,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufferBG,NULL);
	
	//�G���[�`�F�b�N����߂�l��E_FAIL

	////�G���[�Ή�/HRESULT�^�ɂ���
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX ,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufferBG,NULL) ) ){
		return E_FAIL;
	}

	//�G���[����Ȃ�������
	VERTEX_2D* pVtx;				//�o�[�e�b�N�X�o�b�t�@�̉��z�A�h���X���擾����ׂ̃|�C���^

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferBG->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0�͑S�ă��b�N����,��O�����̓A�h���X�������ꂽ������

	//���g_pVtxBufferBG���A�����j�b�g�|���S���ɏI������������
	


	//��O�����i�A�T�[�g�}�N��������Ă����j

	// ���_���W�̐ݒ�i2D���W�E�E���j-0.5
	pVtx[ 0 ].pos = D3DXVECTOR3( 0, 0, 0.0f );//����
	pVtx[ 1 ].pos = D3DXVECTOR3( SCREEN_WIDTH , 0 , 0.0f );//�E��
	pVtx[ 2 ].pos = D3DXVECTOR3( 0, SCREEN_HEIGHT , 0.0f );//����
	pVtx[ 3 ].pos = D3DXVECTOR3( SCREEN_WIDTH , SCREEN_HEIGHT, 0.0f );//�E��

	// rhw�̐ݒ�i�K��1.0f�j
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	// ���_�J���[�̐ݒ�i0�`255�̐����l�j
	pVtx[ 0 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
	pVtx[ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

#if 0//�����p
	//���_�f�[�^��UV�f�[�^�̒ǉ�/�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f , 0.0f );//����
	pVtx[ 1 ].tex = D3DXVECTOR2( 2.0f , 0.0f );//�E��
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f , 2.0f );//����
	pVtx[ 3 ].tex = D3DXVECTOR2( 2.0f , 2.0f );//�E��

#else

	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f , 0.0f );//����
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f , 0.0f );//�E��
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f , 1.0f );//����
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f , 1.0f );//�E��
#endif

	//���̉��(�����J����������GPU�͕ҏW���n�߂�)
	g_pVtxBufferBG->Unlock();
}

/*
Polygon�@���@BG
POLYGON�|��BG

*/