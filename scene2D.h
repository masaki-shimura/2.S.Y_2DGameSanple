//=============================================================================
//
// 2D�I�u�W�F�N�g�̏��� [scene2D.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*********************************************************
// 2D�I�u�W�F�N�g�N���X
//*********************************************************
class CScene2D : public CScene
{
public:
	CScene2D();
	~CScene2D();

	static CScene2D *Create(void);

	virtual HRESULT Init( void );
	virtual HRESULT Init( D3DXVECTOR3 pos );
	virtual HRESULT Init( D3DXVECTOR3 pos , float fWidth , float fHeight );

	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Draw(LPDIRECT3DTEXTURE9 pTexture , int DrawCnt);
	

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void LoadTexture(  );//�l�ɂ���Ĉ������Ⴄ
	void LoadTexture( const char TexPass[] );

	void SetPosition ( D3DXVECTOR3 pos );
	void SetWidthHeight( float fWidth , float fHeight );
	D3DXVECTOR3 GetPosition ( void );
	float GetLength ( void );

	//���_�Q�Ɨp�֐�
	void SetVtx( void );//���S���W
	void SetVtxUV(float x , float y);//UV����p
	void SetVtxUVMulti(float x , float y ,int i);//UV����p
	void SetVtxWidthHeight(void);
	BOOL CScene2D::SetVtx ( float UVmoveX , float UVmoveY , int nSpan);
	void SetVtxPos( void );
	void SetVtxColor(int r,int g,int b,int a);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	bool m_bLoadTexture;//�e�N�X�`���ǂݍ��񂾂��ǂ���

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �|���S���̈ʒu

	//�ǋL
	float m_fAngle;		//�p�x
	float m_fRot;		//��]��
	float m_fLength;	//���a
	int FpsCnt;			//�A�j���[�V�����p�J�E���g
	float m_fMx;		//tex��uv�l����p
	float m_fMy;
	float m_fWidth;		//��
	float m_fHeight;	//����

	float m_fMxMulti[3];		//tex��uv�l����p
	float m_fMyMulti[3];
};

#endif
