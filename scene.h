//=============================================================================
//
// �I�u�W�F�N�g�̏��� [scene.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_SCENE		(100)	// �I�u�W�F�N�g�̍ő吔

//*********************************************************
// �I�u�W�F�N�g�N���X
//*********************************************************
class CScene
{
public:
	//�e�ƓG�Ƃ̓��蔻��p�ɒǋL
	typedef enum{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOSION,
		OBJTYPE_MAX,
	}OBJTYPE;

	static CScene *GetScene(int nIdyScene);
	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);

	virtual void SetPosition (D3DXVECTOR3 pos)=0;
	virtual D3DXVECTOR3 GetPosition(void)=0;
	virtual float GetLength ( void )=0;

	CScene();
	virtual ~CScene();

	virtual HRESULT Init(void)= 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	//���蔻��
	virtual BOOL Hit(int nDamage);

protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_SCENE];	// �I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumScene;					// ���I�u�W�F�N�g��

	int m_nID;								// �ŗLID

	OBJTYPE m_objType;

};

#endif
