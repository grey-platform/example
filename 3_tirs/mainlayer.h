#ifndef _MAINLAYER_H_
#define _MAINLAYER_H_

#include "layer.h"
#include <standard/gui.h>
#include <standard/planematerial.h>
#include <standard/renderbuffer.h>
#include <standard/texturefile.h>
#include <standard/texturetarget.h>
#include <standard/math.h>

#define GAME_WIDTH  10
#define GAME_HEIGHT  20
#define BLOCK_SIZE  20

#define BASIC_BLOCK_NUMBER  7
#define EXTEND_BLOCK_NUMBER  11
#define SAMPLE_BLOCK_NUMBER  4


typedef enum{
    GameOver,
    GamePause,
    BlockDropping,
    GameStart
}GameState;

typedef enum{
    BasicType,
    ExtendType,
    SampleType
}BlockType;

typedef struct{
    int32 size;
    int32 elements[ 16 ];
}Block;

class CMainLayer: public CLayer, public CUIEvent{
public:
    CMainLayer();
    virtual ~CMainLayer();
    virtual void Init( CWindow* pParent );
    virtual void Show();
    virtual void Hide();
    virtual void Update( int32 nDelta );
    virtual void Render();
    virtual void OnClick( CUIElement* pSelf );
public:
    int32 Type( int32 t );
    int32 ChooseColor( int32 nowblock );
    int32 TimeDelay( int32 speed );
    void RemoveLines();
    void SetScoreText( int32 nScore );
    void SetLevelText( int32 nLevel );
    void SetLinesText( int32 nLines );
    void OnTimer();
    void ClearBoard();
    bool32 HitTest( Block* block, int32 x, int32 y );
    void NewBlock( int32 blockType );
    void PlaceBlock();
    void DrawNextBlock();
    void DrawBlock( Block* block, int32 x, int32 y );
    void Rotate();
    void Removeoneline();
    void ChangeSpeed();

    void OnRestartClick( CUIElement* pElement );
    void OnPauseClick( CUIElement* pElement );
    virtual void OnKeyEvent( CUIElement* pElement, EUIKeyMessage eKeyMessage, int32 nKey );
    
    CPanel* m_pLayerPanel;
    CLable* m_pLevel, *m_pScore, *m_pLines;
    CButton* m_pContinueButton;
    CTextureTarget* m_pTextureTarget;
    CPlaneMaterial* m_pMaterial;
    CTexture* m_pTexture;
    CVertexBuffer* m_pRenderBuffer;
    CVertexBuffer* m_pGroundRenderBuffer;

    GameState gameState;
    Block  currentBlock;
    int32  CurrentColorNo;
    Block  NextBlock;
    int32  NextColorNo;
    int32  x, y;
    int32  board[ GAME_HEIGHT + 1 ][ GAME_WIDTH + 2 ];
    int32  LinesCount;
    int32  Score;
    int32  DeltaSpeed;
    int32  time;
};




#endif
