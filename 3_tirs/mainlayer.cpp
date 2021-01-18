
#include "mainlayer.h"
#include "global.h"
#include <include/string.h>
#include <include/stdio.h>


Block blocks[ 22 ] = {
    {4,{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
    {3,{0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0}},
    {3,{1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0}},
    {3,{0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0}},
    {3,{1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0}},
    {3,{0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0}},
    {2,{1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0}},
    {3,{0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,0}},
    {3,{1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0}},
    {3,{0,1,1,0,0,1,0,0,1,1,0,0,0,0,0,0}},
    {3,{1,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0}},
    {3,{0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0}},
    {3,{0,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0}},
    {4,{0,1,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
    {4,{0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0}},
    {4,{0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
    {4,{0,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0}},
    {3,{0,1,0,0,0,1,0,0,1,1,1,0,0,0,0,0}},
    {1,{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {2,{0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}},
    {2,{1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}},
    {3,{0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0}},
};

float BrushColor[ 10 ][ 3 ] = {
    {1.0f, 1.0f, 1.0f},
    {233.0f / 255.0f, 121.0f / 255.0f, 118.0f / 255.0f},
    {255.0f / 255.0f, 255.0f / 255.0f, 102.0f / 255.0f},
    {0.0f / 255.0f, 143.0f / 255.0f, 224.0f / 255.0f},
    {153.0f / 255.0f, 153.0f / 255.0f, 204.0f / 255.0f},
    {204.0f / 255.0f, 204.0f / 255.0f, 204.0f / 255.0f},
    {232.0f / 255.0f, 123.0f / 255.0f,  20.0f / 255.0f},
    {235.0f / 255.0f,  88.0f / 255.0f, 235.0f / 255.0f},
    {51.0f / 255.0f, 204.0f / 255.0f, 102.0f / 255.0f},
    {220.0f / 255.0f,  39.0f / 255.0f,  75.0f / 255.0f},
};



CMainLayer::CMainLayer(){
    DeltaSpeed = 1000;
}

CMainLayer::~CMainLayer(){

}

void AddVertData( TV3C1T2 &vert, float x, float y, float z, color32 c, float u, float v ){
    vert.X = x, vert.Y = y, vert.Z = z, vert.C = c, vert.U = u, vert.V = v;
}

void CMainLayer::Init( CWindow* pParent ){
	TV3C1T2 _vert1[ 6 ];
	TV3C1T2 _vert0[ 6 ];
    AddVertData( _vert1[0], 0, 0, 0, 0xffffffff, 0, 0 );
    AddVertData( _vert1[1], 350.0f, 0, 0, 0xffffffff, 350.0f / 512.0f, 0 );
    AddVertData( _vert1[2], 350.0f, 400.0f, 0, 0xffffffff, 350.0f / 512.0f, 400.0f / 512.0f );
    AddVertData( _vert1[3], 350.0f, 400.0f, 0, 0xffffffff, 350.0f / 512.0f, 400.0f / 512.0f );
    AddVertData( _vert1[4], 0, 400.0f, 0, 0xffffffff, 0, 400.0f / 512.0f );
    AddVertData( _vert1[5], 0, 0, 0, 0xffffffff, 0, 0 );

    AddVertData( _vert0[0], 0, 0, 0, 0xffffffff, 384.0f / 511.0f, 0.0f );
    AddVertData( _vert0[1], 20.0f, 0, 0, 0xffffffff, 1.0f, 0.0f );
    AddVertData( _vert0[2], 20.0f, 20.0f, 0, 0xffffffff, 1.0f, 128.0f / 511.0f );
    AddVertData( _vert0[3], 20.0f, 20.0f, 0, 0xffffffff, 1.0f, 128.0f / 511.0f );
    AddVertData( _vert0[4], 0, 20.0f, 0, 0xffffffff, 384.0f / 511.0f, 128.0f / 511.0f );
    AddVertData( _vert0[5], 0, 0, 0, 0xffffffff, 384.0f / 511.0f, 0.0f );
	
    CButton *_pButton;
    CImage* _pCanvas;
    m_pLayerPanel = NEW CPanel( 0, 30, 360, 410 );
    pParent->AddElement( m_pLayerPanel );

    m_pTextureTarget = NEW CTextureTarget( 512, 512, True, False );
    _pCanvas = NEW CImage( 5, 35, 350, 400, m_pTextureTarget );
    _pCanvas->SetTextureCoordsInfo( 0, 512, 512, 0, 0, 350, 400 );
    _pCanvas->ApplyTextureCoordsInfo();
    _pCanvas->AddUIEvent( UEM_KEYEVENT );
    _pCanvas->OnKeyEventObject = this;
    m_pLayerPanel->AddElement( _pCanvas );

    m_pLevel = NEW CLable( 290, 200, 40, 20 );
    m_pLayerPanel->AddElement( m_pLevel );
    m_pScore = NEW CLable( 290, 248, 40, 20 );
    m_pLayerPanel->AddElement( m_pScore );
    m_pLines = NEW CLable( 290, 293, 40, 20 );
    m_pLayerPanel->AddElement( m_pLines );

    _pButton = NEW CButton( 250, 340, 80, 30, "重新开始" );
    _pButton->SetID( 0 );
    _pButton->AddUIEvent( UEM_CLICK );
    _pButton->OnClickEventObject = this;
    m_pLayerPanel->AddElement( _pButton );

    m_pContinueButton = NEW CButton( 250, 375, 80, 30, "暂 停" );
    _pButton->SetID( 1 );
    m_pContinueButton->AddUIEvent( UEM_CLICK );
    m_pContinueButton->OnClickEventObject = this;
    m_pLayerPanel->AddElement( m_pContinueButton );

    m_pTexture = NEW CTextureFile( "data/background.png" );
    m_pMaterial = NEW CPlaneMaterial( 350.0f, 400.0f );
    m_pMaterial->Init();
    m_pGroundRenderBuffer = NEW CVertexBuffer( EVT_VECTOR_COLOR_TEXCOORDS, _vert1, 6, False );
    m_pRenderBuffer = NEW CVertexBuffer( EVT_VECTOR_COLOR_TEXCOORDS, _vert0, 6, False );
}

void CMainLayer::OnRestartClick( CUIElement* pElement ){
    this->m_pSwitcherEventObject->OnSwitchLayer( 1 );
}
void CMainLayer::OnPauseClick( CUIElement* pElement ){
    if( gameState == GamePause ){
        gameState = BlockDropping;
        m_pContinueButton->SetText( "暂 停" );
    } else{
        gameState = GamePause;
        m_pContinueButton->SetText( "继 续" );
    }
}

void CMainLayer::OnKeyEvent( CUIElement* pElement, EUIKeyMessage eKeyMessage, int32 nKey ){
    if( eKeyMessage == UKE_KEYDOWN ){
        if( gameState == GameStart || gameState == GamePause || gameState == GameOver ){
            return;
        }
        switch( nKey ){
        case 0x25:{
            x--;
            if( HitTest( &currentBlock, x, y ) ){
                x++;
            }
        }break;
        case 0x27:{
            x++;
            if( HitTest( &currentBlock, x, y ) ){
                x--;
            }
        }break;
        case 0x28:{
            int32 i;
            for( i = 1; i <= GAME_HEIGHT; i++ ){
                y++;										// move block down
                if( HitTest( &currentBlock, x, y ) )
                    break;	// if it hit something
            }
            y--;										    // move it back up
            PlaceBlock();								    // make it permanent
            RemoveLines();
            NewBlock( Rand( Type( blocktype ) ) );
        }break;
        case 0x26:{
            Rotate();
            if( HitTest( &currentBlock, x, y ) ){
                Rotate();
                Rotate();
                Rotate();
            }break;
        }
        }
    }
}
void CMainLayer::OnClick( CUIElement* pSelf ){
    switch( pSelf->GetID() ){
    case 0:OnRestartClick(pSelf); break;
    case 1:OnPauseClick( pSelf ); break;
    }
}

void CMainLayer::Show(){
    m_pLayerPanel->SetVisible( True );
    m_pContinueButton->SetEnable( True );
    ClearBoard();
    int32 tmpblock = Rand( Type( blocktype ) );
    memcpy( &NextBlock, ( blocks + tmpblock ), sizeof( NextBlock ) );
    NextColorNo = ChooseColor( tmpblock );
    NewBlock( Rand( Type( blocktype ) ) );
    gameState = BlockDropping;
    LinesCount = 0;
    Score = 0;
    StartSpeed = 0;
    NowSpeed = 0;
    SetScoreText( Score );
    SetLinesText( LinesCount );
    SetLevelText( NowSpeed );
    DeltaSpeed = TimeDelay( NowSpeed );
    time = 0;
}

void CMainLayer::Hide(){
    m_pLayerPanel->SetVisible( False );
}

void CMainLayer::Update( int32 nDelta ){
    if( gameState != BlockDropping ) return;
    time += nDelta;
    if( time > DeltaSpeed ){
        OnTimer();
        time %= DeltaSpeed;
    }
}

void CMainLayer::Render(){
    Renderer_SetClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    m_pTextureTarget->BeginRender(350, 400);
    Renderer_Clear( True, False );
    //////////////////////////////////////////////////////
    m_pMaterial->Begin();
    m_pMaterial->SetTexture( m_pTexture );
    m_pGroundRenderBuffer->Render( EPT_TRIANGLE_LIST );
    ////////////////////////////////////////////////////////////
    DrawNextBlock();
    for( int32 j = 0; j < GAME_HEIGHT; j++ ){
        for( int32 i = 0; i < GAME_WIDTH; i++ ){
            int32 n = board[ j ][ i + 1 ];
            if( n != 0 ){
                float _x = ( i*BLOCK_SIZE );
                float _y = ( j*BLOCK_SIZE );
                m_pMaterial->SetPosition( _x, _y, 0.0f );
                m_pMaterial->SetColor( BrushColor[ n ][ 0 ], BrushColor[ n ][ 1 ], BrushColor[ n ][ 2 ], 1.0f );
                m_pRenderBuffer->Render( EPT_TRIANGLE_LIST );
            }
        }
    }
    DrawBlock( &currentBlock, x, y );
    m_pMaterial->End();
    m_pTextureTarget->EndRender();
}


int32 CMainLayer::Type( int32 t ){
    switch( t ){
    case 0:
    return 7;
    case 1:
    return 18;
    case 2:
    return 22;
    }
    return -1;
}
int32 CMainLayer::ChooseColor( int32 nowblock ){
    int32 nowcolor = 8;
    switch( ColorType ){
    case 0:{
        if( nowblock < BASIC_BLOCK_NUMBER ){
            nowcolor = nowblock + 1;
        } else if( nowblock < BASIC_BLOCK_NUMBER + EXTEND_BLOCK_NUMBER ){
            nowcolor = BASIC_BLOCK_NUMBER + 1;
        } else{
            nowcolor = BASIC_BLOCK_NUMBER + 2;
        }
    }break;
    case 1:{
        nowcolor = Rand( BASIC_BLOCK_NUMBER + 2 ) + 1;
    }break;
    case 2:
    break;
    }
    return nowcolor;
}
int32 CMainLayer::TimeDelay( int32 speed ){
    switch( speed ){
    case 0:
    return( 1000 );
    case 1:
    return( 900 );
    case 2:
    return( 800 );
    case 3:
    return( 700 );
    case 4:
    return( 600 );
    case 5:
    return( 500 );
    case 6:
    return( 400 );
    case 7:
    return( 300 );
    case 8:
    return( 200 );
    case 9:
    return( 150 );
    }
    return( 150 );
}

void CMainLayer::RemoveLines(){
    int32 i = 0;
    int32 j = 0;
    int32 k = 0;
    int32 l = 0;
    bool32 lineFull;
    int32  linescount = 0;

    linescount = 0;
    j = 20 - 1;
    while( j >= 0 ){
        lineFull = True;
        for( i = 1; i <= GAME_WIDTH; i++ )
            if( board[ j ][ i ] == 0 ){
                lineFull = False;
            }
        if( lineFull ){
            linescount++;
            for( k = j; k >= 1; k-- ){
                for( l = 1; l <= GAME_WIDTH; l++ ){
                    board[ k ][ l ] = board[ k - 1 ][ l ];
                }
            }
            for( l = 1; l <= 1; l++ ){
                board[ 0 ][ l ] = 0;
            }
        } else{
            j--;
        }
    }

    if( linescount ){
        LinesCount = LinesCount + linescount;
        switch( linescount ){
        case 1:
        Score += 100;
        break;
        case 2:
        Score += 300;
        break;
        case 3:
        Score += 500;
        break;
        case 4:
        Score += 1000;
        break;
        }
        SetScoreText( Score );
        SetLinesText( LinesCount );
        ChangeSpeed();
    }

}
void CMainLayer::SetScoreText( int32 nScore ){
    char _strText[ 32 ];
    sprintf( _strText, "%d", nScore );
    m_pScore->SetText( _strText );
}
void CMainLayer::SetLevelText( int32 nLevel ){
    char _strText[ 32 ];
    sprintf( _strText, "%d", nLevel + 1 );
    m_pLevel->SetText( _strText );
}
void CMainLayer::SetLinesText( int32 nLines ){
    char _strText[ 32 ];
    sprintf( _strText, "%d", nLines );
    m_pLines->SetText( _strText );
}
void CMainLayer::OnTimer(){
    if( gameState == GameOver || gameState == GameStart ){
        return;
    }
    y++;
    if( HitTest( &currentBlock, x, y ) ){
        y--;
        PlaceBlock();
        RemoveLines();
        NewBlock( Rand( Type( blocktype ) ) );
    }
}
void CMainLayer::ClearBoard(){
    int32 i = 0;
    int32 j = 0;
    for( i = 0; i < ( GAME_HEIGHT + 1 ); i++ ){
        for( j = 0; j < ( GAME_WIDTH + 2 ); j++ ){
            board[ i ][ j ] = 0;
        }
    }
    for( i = 0; i < ( GAME_HEIGHT + 1 ); i++ ){
        board[ i ][ 0 ] = -1;
        board[ i ][ GAME_WIDTH + 1 ] = -1;
    }
    for( j = 0; j < ( GAME_WIDTH + 2 ); j++ ){
        board[ GAME_HEIGHT ][ j ] = -1;
    }
}
bool32 CMainLayer::HitTest( Block* block, int32 x, int32 y ){
    for( int32 i = 0; i < 4; i++ ){
        for( int32 j = 0; j < 4; j++ ){
            if( ( ( x + i ) < ( GAME_WIDTH + 2 ) ) && ( ( x + i + 1 ) >= 0 ) && ( ( y + j ) < ( GAME_HEIGHT + 1 ) ) && ( ( y + j ) >= 0 ) ){
                if( board[ y + j ][ x + 1 + i ] != 0 ){
                    if( block->elements[ j * 4 + i ] ){
                        return True;
                    }
                }
            }
        }
    }
    return False;
}
void CMainLayer::NewBlock( int32 blockType ){
    memcpy( &currentBlock, &NextBlock, sizeof( NextBlock ) );
    memcpy( &NextBlock, ( blocks + blockType ), sizeof( NextBlock ) );
    x = 4;
    y = 0;
    CurrentColorNo = NextColorNo;
    NextColorNo = ChooseColor( blockType );
    if( HitTest( &currentBlock, x, y ) ){
        gameState = GameOver;
        for( int32 i = 1; i <= 3; i++ ){
            Removeoneline();
            if( ! HitTest( &currentBlock, x, y ) )
                break;
        }
        PlaceBlock();
        m_pContinueButton->SetEnable( 0 );
    }
}
void CMainLayer::PlaceBlock(){
    for( int32 i = 0; i < 4; i++ ){
        for( int32 j = 0; j < 4; j++ ){
            if( currentBlock.elements[ j * 4 + i ] ){
                board[ y + j ][ x + 1 + i ] = CurrentColorNo;
            }
        }
    }
}

void CMainLayer::DrawNextBlock(){
    int32 size = NextBlock.size;
    m_pMaterial->SetColor( BrushColor[ NextColorNo ][ 0 ], BrushColor[ NextColorNo ][ 1 ], BrushColor[ NextColorNo ][ 2 ], 1.0f );
    for( int32 i = 0; i < size; i++ ){
        for( int32 j = 0; j < size; j++ ){
            if( NextBlock.elements[ j * 4 + i ] ){
                float _x = ( 250 + i*BLOCK_SIZE );
                float _y = ( 50 + j*BLOCK_SIZE );
                m_pMaterial->SetPosition( _x, _y, 0.0f );
                m_pRenderBuffer->Render( EPT_TRIANGLE_LIST );
            }
        }
    }
}
void CMainLayer::DrawBlock( Block* block, int32 x, int32 y ){
    int32 size = block->size;
    m_pMaterial->SetColor( BrushColor[ CurrentColorNo ][ 0 ], BrushColor[ CurrentColorNo ][ 1 ], BrushColor[ CurrentColorNo ][ 2 ], 1.0f );
    for( int32 i = 0; i < size; i++ ){
        for( int32 j = 0; j < size; j++ ){
            if( block->elements[ j * 4 + i ] ){
                float _x = ( x*BLOCK_SIZE + i*BLOCK_SIZE );
                float _y = ( y*BLOCK_SIZE + j*BLOCK_SIZE );
                m_pMaterial->SetPosition( _x, _y, 0.0f );
                m_pRenderBuffer->Render( EPT_TRIANGLE_LIST );
            }
        }
    }
}
void CMainLayer::Rotate(){
    int32 i = 0;
    int32 j = 0;
    int32 tempBlock[ 16 ];

    switch( currentBlock.size ){
    case 4:{
        memcpy( tempBlock, currentBlock.elements, 64 );
        for( i = 0; i < 4; i++ ){
            for( j = 0; j < 4; j++ ){
                tempBlock[ ( 3 - i ) * 4 + j ] = currentBlock.elements[ j * 4 + i ];
            }
        }
        memcpy( currentBlock.elements, tempBlock, 64 );
    }break;
    case 3:{
        memcpy( tempBlock, currentBlock.elements, 64 );
        for( i = 0; i < 3; i++ ){
            for( j = 0; j < 3; j++ ){
                tempBlock[ ( 2 - i ) * 4 + j ] = currentBlock.elements[ j * 4 + i ];
            }
        }
        memcpy( currentBlock.elements, tempBlock, 64 );
    }break;
    case 2:{
        memcpy( tempBlock, currentBlock.elements, 64 );
        for( i = 0; i < 2; i++ ){
            for( j = 0; j < 2; j++ ){
                tempBlock[ ( 1 - i ) * 4 + j ] = currentBlock.elements[ j * 4 + i ];
            }
        }
        memcpy( currentBlock.elements, tempBlock, 64 );
    }break;
    case 1:
    break;
    }
}
void CMainLayer::ChangeSpeed(){
    int32 LINENUMBER = 30;
    if( NowSpeed != StartSpeed + LinesCount / LINENUMBER && NowSpeed < 9 ){
        NowSpeed = StartSpeed + LinesCount / LINENUMBER;
        DeltaSpeed = TimeDelay( NowSpeed );
        SetLevelText( NowSpeed );
    }
}
void CMainLayer::Removeoneline(){
    for( int32 j = 0; j < 4; j++ ){
        for( int32 i = 0; i < 3; i++ ){
            currentBlock.elements[ i * 4 + j ] = currentBlock.elements[ ( i + 1 ) * 4 + j ];
        }
        currentBlock.elements[ 3 * 4 + j ] = 0;
    }
}


