//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

class CRenderer;
class CInputKeyboard;
class CScore;

//*********************************************************
// �}�l�[�W���[�N���X
//*********************************************************
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void){ return m_pRenderer;};
	static CScore *GetScore(void){ return m_pScore; };
	static CInputKeyboard *GetInputKeyboard(void){return m_pInputKeyboard;};

private:
	static CRenderer *m_pRenderer;		// �����_���[�ւ̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	//���͂̃|�C���^
	static CScore *m_pScore;	//�X�R�A�̃|�C���^
};

#endif
