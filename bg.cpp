//------------------------------------------------------
//インクルードファイル
//------------------------------------------------------
#include "main.h"
#include "polygon.h"//自分自身のインクルードファイルは使う時以外必要ない,C++対にしなくてはいけない

//------------------------------------------------------
//マクロ
//------------------------------------------------------
#define BG_POS_X (350.0f)								//ポリゴンの表示位置X
#define BG_POS_Y (180.0f)								//ポリゴンの表示位置Y
#define BG_POS_WIDTH (243.0f * 0.8f)					//ポリゴンの幅
#define BG_POS_HEIGHT (432.0f * 0.8f)					//ポリゴンの高さ
#define BG_TEXTURENAME "data/TEXTURE/bg000.jpg"			//テクスチャの追加

//png,jpg,tga,bmp,dds  半透明はjpg,tga,dds
//------------------------------------------------------
//グローバル変数
//------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBG = NULL;			//頂点バッファ管理用
//削除　　VERTEX_2D g_aVertex[ NUM_VERTEX ];							//頂点情報格納用配列
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;				//テクスチャインターフェースへのポインタ

//------------------------------------------------------
//プロトタイプ宣言
//------------------------------------------------------
HRESULT MakeVertexBG ( LPDIRECT3DDEVICE9 pDevice );		//頂点の作成

//------------------------------------------------------
//初期化処理関数
//------------------------------------------------------
HRESULT InitBG ( void )
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//BG設定
	MakeVertexBG ( pDevice );

	//テクスチャーの読み込み/一回しか読み込めない
	D3DXCreateTextureFromFile( pDevice , BG_TEXTURENAME , &g_pTextureBG);

	//読み込みエラー
	if(FAILED(D3DXCreateTextureFromFile(pDevice,BG_TEXTURENAME,&g_pTextureBG))){
		MessageBox( NULL , "読み込みエラーです。" , "Error" , MB_YESNOCANCEL | MB_ICONASTERISK | MB_DEFBUTTON3 );
		return E_FAIL;
	}
}

//------------------------------------------------------
//終了処理関数
//------------------------------------------------------
void UninitBG ( void )//解放する順番　ポリゴン　デバイス　ダイレクト３D　解放の
{
	//vtxバッファーポリゴンのお片付け
	if( g_pVtxBufferBG != NULL ){
	g_pVtxBufferBG->Release();									// Direct3Dデバイス（インターフェース）の解放
	g_pVtxBufferBG = NULL;
	}

	if( g_pTextureBG != NULL ){
		g_pTextureBG->Release();									// Direct3Dデバイス（インターフェース）の解放
		g_pTextureBG = NULL;
	}


}

//------------------------------------------------------
//更新処理関数
//------------------------------------------------------
void UpdateBG ( void )
{

}

//------------------------------------------------------
//描画処理関数
//------------------------------------------------------
void DrawBG( void )
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//パイプライン(ストリームセット),第三引数はoffset、つまり用意した頂点バッファの途中から出力可能
	pDevice->SetStreamSource( 0 , g_pVtxBufferBG , 0 , sizeof(VERTEX_2D) );

	//ポリゴン描画をする前に
	pDevice->SetTexture(0,g_pTextureBG);
	//逆？？？上と下
	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_2D );										// いまからこれで書くよ

	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP ,
							0 ,						//オフセット(頂点数)
							NUM_POLYGON );			//プリミティブ数/ポリゴン何枚書くの？

	//上記に書き換え
	// プリミティブ（ポリゴン）の描画
	//pDevice->DrawPrimitiveUP(
	//	D3DPT_TRIANGLESTRIP,														// プリミティブの種類
	//	NUM_BG,															// プリミティブの数
	//	&g_aVertex[ 0 ],														// 頂点データの先頭アドレス
	//	sizeof(VERTEX_2D));														// 頂点データ１個分のサイズ（byte）
}

//------------------------------------------------------
//ポリゴンの頂点を作成
//------------------------------------------------------
HRESULT MakeVertexBG ( LPDIRECT3DDEVICE9 pDevice )
{
	//現状ほしいバッファーサイズを取得(一個の頂点×頂点数)							//メモリ管理
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX ,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufferBG,NULL);
	
	//エラーチェックする戻り値はE_FAIL

	////エラー対応/HRESULT型にする
	if( FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX ,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufferBG,NULL) ) ){
		return E_FAIL;
	}

	//エラーじゃなかった時
	VERTEX_2D* pVtx;				//バーテックスバッファの仮想アドレスを取得する為のポインタ

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferBG->Lock( 0 , 0 , ( void** )&pVtx , 0 );//0,0は全てロックする,第三引数はアドレスが書かれたメモ帳

	//上のg_pVtxBufferBGをアンユニットポリゴンに終了処理を書く
	


	//例外処理（アサートマクロを作っていく）

	// 頂点座標の設定（2D座標・右回り）-0.5
	pVtx[ 0 ].pos = D3DXVECTOR3( 0, 0, 0.0f );//左↑
	pVtx[ 1 ].pos = D3DXVECTOR3( SCREEN_WIDTH , 0 , 0.0f );//右↑
	pVtx[ 2 ].pos = D3DXVECTOR3( 0, SCREEN_HEIGHT , 0.0f );//左↓
	pVtx[ 3 ].pos = D3DXVECTOR3( SCREEN_WIDTH , SCREEN_HEIGHT, 0.0f );//右下

	// rhwの設定（必ず1.0f）
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	// 頂点カラーの設定（0～255の整数値）
	pVtx[ 0 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
	pVtx[ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );

#if 0//実験用
	//頂点データへUVデータの追加/テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f , 0.0f );//左↑
	pVtx[ 1 ].tex = D3DXVECTOR2( 2.0f , 0.0f );//右↑
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f , 2.0f );//左下
	pVtx[ 3 ].tex = D3DXVECTOR2( 2.0f , 2.0f );//右↓

#else

	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f , 0.0f );//左↑
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f , 0.0f );//右↑
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f , 1.0f );//左下
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f , 1.0f );//右↓
#endif

	//鍵の解放(鍵を開放したあとGPUは編集を始める)
	g_pVtxBufferBG->Unlock();
}

/*
Polygon　→　BG
POLYGON－＞BG

*/