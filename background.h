//=============================================================================
//
// �w�i�̏��� [background.h]
// Author :
//
//=============================================================================
#include "scene2D.h"
//*********************************************************
// �񋓌^
//*********************************************************
	typedef enum{
		BGTYPE_NONE = 0,
		BGTYPE_1,
		BGTYPE_2,
		BGTYPE_3,
		BGTYPE_MAX
	}BGTYPE;

//*********************************************************
// �w�i�N���X
//*********************************************************
class CBackground : public CScene2D
{
public:

	CBackground();
	~CBackground();
	static CBackground *Create(float fPosX , float fPosY ,  const char TexPass[] ,BGTYPE type);

	void Update (void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	BGTYPE m_BgType;
};