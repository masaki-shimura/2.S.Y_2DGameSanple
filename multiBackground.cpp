//=============================================================================
//
// �w�i�̏��� [background.cpp]
// Author :
//
//=============================================================================
#include "multiBackground.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MULTIBG_TEXTURE_FILENAME000		"data/TEXTURE/bg100.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MULTIBG_TEXTURE_FILENAME001		"data/TEXTURE/bg101.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MULTIBG_TEXTURE_FILENAME002		"data/TEXTURE/bg102.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMultiBackground::m_pTexture[MULTIBACKGROUND_MAX] = {NULL};		//�e�N�X�`�����
int CMultiBackground::m_NumberOfsheets = 0;											//�w�i�̖���
float CMultiBackground::uv_x[MULTIBACKGROUND_MAX] = {NULL};							//uv���
float CMultiBackground::uv_y[MULTIBACKGROUND_MAX] = {NULL};							//uv���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMultiBackground::CMultiBackground()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMultiBackground::~CMultiBackground()
{

}

//=============================================================================
// ��������
//=============================================================================
CMultiBackground *CMultiBackground::Create(float fPosX , float fPosY , MULTIBGTYPE type, int NumberOfsheets)
{
	//��������
	CMultiBackground *pBg;
	pBg = new CMultiBackground;

	//������
	pBg->Init(D3DXVECTOR3(fPosX,fPosY,0.0f),SCREEN_WIDTH,SCREEN_HEIGHT);

	//�����f�[�^�̕ۑ�
	m_NumberOfsheets = NumberOfsheets;

	//�e�N�X�`���ǂݍ���
	CMultiBackground::Load();

	return pBg;
}

//=============================================================================
// �X�V����
//=============================================================================
void CMultiBackground::Update(void)
{
	CMultiBackground::SetVtxWidthHeight();

	for( int i = 0; i < MULTIBACKGROUND_MAX ; i++ )
	{
		//�L�[���͎��ɔw�i�ړ�
		if( CManager::GetInputKeyboard()->GetKeyPress(DIK_A) == TRUE)
		{
			uv_x[i] = 0.001f;
		}else if( CManager::GetInputKeyboard()->GetKeyPress(DIK_D) == TRUE)
		{
			uv_x[i] = -0.001f;
		}else
		{
			uv_x[i] = 0.0f;
		}
	}
}

void CMultiBackground::Draw(void)
{

	for( int i = 0; i < MULTIBACKGROUND_MAX ; i++ )
	{
		//�����X�N���[��
		switch(i)
		{
		case 0:
			uv_x[i] *= 1.0f;
			CMultiBackground::SetVtxUVMulti(0.0f + uv_x[i],-0.0001f,i);
			break;

		case 1:
			uv_x[i] *= 0.8f;
			CMultiBackground::SetVtxUVMulti(0.0f + uv_x[i],-0.002f,i);
		break;

		case 2:
			uv_x[i] *= 0.6f;
			CMultiBackground::SetVtxUVMulti(0.0f + uv_x[i],-0.003f,i);
			break;
		}
		
		CScene2D::Draw(m_pTexture[i],i);
	}
}

HRESULT CMultiBackground::Load( void )
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	if( m_pTexture[0] == NULL )
	{
		//�e�N�X�`���ǂݍ���
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , MULTIBG_TEXTURE_FILENAME000 , &m_pTexture[0])))
		 {
			return E_FAIL;
		 }
	}

	if( m_pTexture[1] == NULL )
	{
		//�e�N�X�`���ǂݍ���
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , MULTIBG_TEXTURE_FILENAME001 , &m_pTexture[1])))
		 {
			return E_FAIL;
		 }
	}

	if( m_pTexture[2] == NULL )
	{
		//�e�N�X�`���ǂݍ���
		 if(  FAILED(D3DXCreateTextureFromFile( pDevice , MULTIBG_TEXTURE_FILENAME002 , &m_pTexture[2])))
		 {
			return E_FAIL;
		 }
	}
	return S_OK;
}