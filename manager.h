//=============================================================================
//
// マネージャーの処理 [manager.h]
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
// マネージャークラス
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
	static CRenderer *m_pRenderer;		// レンダラーへのポインタ
	static CInputKeyboard *m_pInputKeyboard;	//入力のポインタ
	static CScore *m_pScore;	//スコアのポインタ
};

#endif
