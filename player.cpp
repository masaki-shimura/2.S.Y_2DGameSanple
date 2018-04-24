//=============================================================================
//
// �I�u�W�F�N�g�̏��� [player.cpp]
// Author :
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FILENAME		"data/TEXTURE/player000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;		//�e�N�X�`���̃f�[�^�ۑ�

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer()
{
	//����
	CPlayer::SetObjType(OBJTYPE_PLAYER);
	//CPlayer::BindTexture( TEXTURE_FILENAME );
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	//m_pos.x += 1;
	if( CManager::GetInputKeyboard()->GetKeyPress(DIK_A) == TRUE)
	{
		m_pos.x -= 10.0f;
	}
	if( CManager::GetInputKeyboard()->GetKeyPress(DIK_W) == TRUE)
	{
		m_pos.y -= 10.0f;
	}
	if( CManager::GetInputKeyboard()->GetKeyPress(DIK_D) == TRUE)
	{
		m_pos.x += 10.0f;
	}
	if( CManager::GetInputKeyboard()->GetKeyPress(DIK_S) == TRUE)
	{
		m_pos.y += 10.0f;
	}

	CPlayer::SetVtx();

	//�o���b�g
	if( CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE) == TRUE)
	{
		CBullet::Create(CScene2D::m_pos , 10.0f );
	}

	CPlayer::SetPosition( CScene2D::m_pos );
}

//=============================================================================
// ����
//=============================================================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	//����������
	pPlayer->Init();

	//�e�N�X�`���ǂݍ���
	pPlayer->LoadTexture(TEXTURE_FILENAME);

	//return S_OK;

	//�I������
	//CScene2D::Uninit();


	return pPlayer;
}

//=============================================================================
// ����
//=============================================================================
CPlayer *CPlayer::Create(float fPosX , float fPosY)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	//����������
	//pPlayer->Init();
	pPlayer->Init(D3DXVECTOR3(fPosX,fPosY,0.0f));
	
	pPlayer->LoadTexture(TEXTURE_FILENAME);

	//return S_OK;

	//�I������
	//CScene2D::Uninit();


	return pPlayer;
}