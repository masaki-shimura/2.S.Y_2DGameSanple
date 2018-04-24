//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "background.h"
#include "multiBackground.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FILENAME		"data/TEXTURE/player000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BG_TEXTURE_FILENAME000		"data/TEXTURE/bg100.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BG_TEXTURE_FILENAME001		"data/TEXTURE/bg101.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BG_TEXTURE_FILENAME002		"data/TEXTURE/bg102.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;			// �����_���[�ւ̃|�C���^
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CScore *CManager::m_pScore = {NULL};

//=============================================================================
// CManager�R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// CManager�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance,hWnd);

	//�w�i����
	CBackground::Create(0,0,BG_TEXTURE_FILENAME002,BGTYPE_1);
	CBackground::Create(0,0,BG_TEXTURE_FILENAME001,BGTYPE_2);
	CBackground::Create(0,0,BG_TEXTURE_FILENAME000,BGTYPE_3);

	//�ꖇ�|���S���ŕ����`��
	//CMultiBackground::Create(0.0f,0.0f,CMultiBackground::BGTYPE_1,3);

	// �I�u�W�F�N�g�̐���
	CPlayer::Create(400,400);		//�v���C���[

	//�G�l�~�[
	for(int i = 0; i < 3 ; i++)
	{
		CEnemy::Create(150.0f * i + 300.0f ,100.0f,CEnemy::TYPE_EBI000);
		CEnemy::Create(150.0f * i + 300.0f ,150.0f,CEnemy::TYPE_IKA000);
		CEnemy::Create(150.0f * i + 350.0f ,200.0f,CEnemy::TYPE_KURO);
		CEnemy::Create(150.0f * i + 350.0f ,250.0f,CEnemy::TYPE_IKA000);
	}

	//�X�R�A�̎��̂𐶐������̂��|�C���^��m_pScore�Ɏ擾����
	m_pScore = CScore::Create(D3DXVECTOR3(1200,100,0),00000000);
	//m_pScore = CScore::Create(D3DXVECTOR3(500,300,0),87654321);
	//m_pScore = CScore::Create(D3DXVECTOR3(500,600,0),87654321);

	//�e�N�X�`���ǂݍ���
	CBullet::Load();
	CExplosion::Load();
	CNumber::Load();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	CScene2D::ReleaseAll();

	// �����_���[�̔j��
	m_pRenderer->Uninit();

	if(m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	m_pRenderer->Update();
	m_pInputKeyboard->Update();

	//�G�l�~�[����
	if( CManager::GetInputKeyboard()->GetKeyTrigger(DIK_R) == TRUE && CEnemy::m_nEnemyCount <= 0)
	{
		//�G�l�~�[
		for(int i = 0; i < 3 ; i++)
		{
			CEnemy::Create(150.0f * i + 300.0f ,100.0f,CEnemy::TYPE_EBI000);
			CEnemy::Create(150.0f * i + 300.0f ,150.0f,CEnemy::TYPE_IKA000);
			CEnemy::Create(150.0f * i + 350.0f ,200.0f,CEnemy::TYPE_KURO);
			CEnemy::Create(150.0f * i + 350.0f ,250.0f,CEnemy::TYPE_IKA000);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
	//CScene2D::DrawAll();
}

