//=============================================================================
//
// îwåiÇÃèàóù [background.h]
// Author :
//
//=============================================================================
#include "scene2D.h"
//*********************************************************
// óÒãìå^
//*********************************************************
#define MULTIBACKGROUND_MAX (3)

//*********************************************************
// îwåiÉNÉâÉX
//*********************************************************
class CMultiBackground : public CScene2D
{
public:
	typedef enum{
		BGTYPE_NONE = 0,
		BGTYPE_1,
		BGTYPE_2,
		BGTYPE_3,
		BGTYPE_MAX
	}MULTIBGTYPE;

	CMultiBackground();
	~CMultiBackground();
	static CMultiBackground *Create(float fPosX , float fPosY ,MULTIBGTYPE type , int NumberOfsheets);

	void Update (void);
	void Draw (void);

	static HRESULT Load( void );

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[];
	MULTIBGTYPE m_BgType;
	static int m_NumberOfsheets;

	static float uv_x[];					//texÇÃxèÓïÒ
	static float uv_y[];					//texÇÃyèÓïÒ
};