
#include "menulayer.h"
#include <standard/texturefile.h>
#include "global.h"

CMenuLayer::CMenuLayer(){

}
CMenuLayer::~CMenuLayer(){

}
void CMenuLayer::Init( CWindow* pParent ){
    CButton *_pButton;
    CImage *_pImage;
    CLable* _pLb;
    CTexture* _pTexture = NEW CTextureFile( "data/background.png" );

    m_pMenuLayerPanel = NEW CPanel( 0, 30, 360, 410 );
    pParent->AddElement( m_pMenuLayerPanel );
    _pImage = NEW CImage( 100, 40, 160, 160, _pTexture );
    _pImage->SetTextureCoordsInfo( 0, 512, 512, 350, 128, 350 + 160, 128 + 160 );
    _pImage->ApplyTextureCoordsInfo();
    m_pMenuLayerPanel->AddElement( _pImage );

    _pLb = NEW CLable( 100, 222, 40, 20, "使用扩展格子" );
    _pLb->SetFontInfo( 1, 0, 0 );
    m_pMenuLayerPanel->AddElement( _pLb );
    m_pBlockTypeCheck[ 0 ] = NEW CButton( 200, 220, 20, 20 );
    m_pBlockTypeCheck[0]->SetID( 0 );
    m_pBlockTypeCheck[ 0 ]->SetCheckMode( True );
    m_pBlockTypeCheck[ 0 ]->AddUIEvent( UEM_CLICK );
    m_pBlockTypeCheck[0]->OnClickEventObject = this;
    m_pMenuLayerPanel->AddElement( m_pBlockTypeCheck[ 0 ] );

    _pLb = NEW CLable( 100, 242, 40, 20, "使用简单格子" );
    m_pMenuLayerPanel->AddElement( _pLb );
    m_pBlockTypeCheck[ 1 ] = NEW CButton( 200, 240, 20, 20 );
    m_pBlockTypeCheck[1]->SetID( 1 );
    m_pBlockTypeCheck[ 1 ]->SetCheckMode( True );
    m_pBlockTypeCheck[ 1 ]->AddUIEvent( UEM_CLICK );
    m_pBlockTypeCheck[ 1 ]->OnClickEventObject = this;
    m_pMenuLayerPanel->AddElement( m_pBlockTypeCheck[ 1 ] );


    _pLb = NEW CLable( 100, 282, 40, 20, "使用标准颜色" );
    m_pMenuLayerPanel->AddElement( _pLb );
    m_pColorTypeCheck[ 0 ] = NEW CButton( 200, 280, 20, 20 );
    m_pColorTypeCheck[0]->SetID( 10 );
    m_pColorTypeCheck[ 0 ]->SetCheckMode( True );
    m_pColorTypeCheck[ 0 ]->AddUIEvent( UEM_CLICK );
    m_pColorTypeCheck[ 0 ]->OnClickEventObject = this;
    m_pMenuLayerPanel->AddElement( m_pColorTypeCheck[ 0 ] );

    _pLb = NEW CLable( 100, 302, 40, 20, "使用统一颜色" );
    m_pMenuLayerPanel->AddElement( _pLb );
    m_pColorTypeCheck[ 1 ] = NEW CButton( 200, 300, 20, 20 );
    m_pColorTypeCheck[ 1 ]->SetID( 11 );
    m_pColorTypeCheck[ 1 ]->SetCheckMode( True );
    m_pColorTypeCheck[ 1 ]->AddUIEvent( UEM_CLICK );
    m_pColorTypeCheck[ 1 ]->OnClickEventObject = this;
    m_pMenuLayerPanel->AddElement( m_pColorTypeCheck[ 1 ] );

    _pLb = NEW CLable( 100, 322, 40, 20, "使用随机颜色" );
    m_pMenuLayerPanel->AddElement( _pLb );
    m_pColorTypeCheck[ 2 ] = NEW CButton( 200, 320, 20, 20 );
    m_pColorTypeCheck[ 2]->SetID( 12 );
    m_pColorTypeCheck[ 2 ]->SetCheckMode( True );
    m_pColorTypeCheck[ 2 ]->AddUIEvent( UEM_CLICK );
    m_pColorTypeCheck[ 2 ]->OnClickEventObject = this;
    m_pMenuLayerPanel->AddElement( m_pColorTypeCheck[ 2 ] );

    _pLb = NEW CLable( 20, 352, 40, 20, "Desc: [<-]Left, [->]Right, [D]Down, [^]Rotation" );
    m_pMenuLayerPanel->AddElement( _pLb );

    _pButton = NEW CButton( 130, 380, 100, 35, "Game Begin" );
    _pButton->SetID( 20 );
    _pButton->AddUIEvent( UEM_CLICK );
    _pButton->OnClickEventObject = this;
    m_pMenuLayerPanel->AddElement( _pButton );
}
void CMenuLayer::OnGameBeginClick( CUIElement* pElement ){
    if( m_pBlockTypeCheck[ 1 ]->GetChecked() ){
        blocktype = 2;
    } else if( m_pBlockTypeCheck[ 0 ]->GetChecked() ){
        blocktype = 1;
    } else{
        blocktype = 0;
    }
    if( m_pColorTypeCheck[ 0 ]->GetChecked() ){
        ColorType = 0;
    } else if( m_pColorTypeCheck[ 1 ]->GetChecked() ){
        ColorType = 2;
    } else{
        ColorType = 1;
    }
    this->m_pSwitcherEventObject->OnSwitchLayer( 0 );
}

void CMenuLayer::OnClick( CUIElement *pSelf ){
    switch( pSelf->GetID() ){
    case 10:
    case 11:
    case 12: OnColorTypeClick( pSelf ); break;
    case 20: OnGameBeginClick( pSelf ); break;

    }
}
void CMenuLayer::OnExtButtonClick( CUIElement* pElement ){

}
void CMenuLayer::OnColorTypeClick( CUIElement* pElement ){
    if( pElement == m_pColorTypeCheck[ 0 ] ){
        m_pColorTypeCheck[ 0 ]->SetChecked( True );
        m_pColorTypeCheck[ 1 ]->SetChecked( False );
        m_pColorTypeCheck[ 2 ]->SetChecked( False );
    }
    if( pElement == m_pColorTypeCheck[ 1 ] ){
        m_pColorTypeCheck[ 0 ]->SetChecked( False );
        m_pColorTypeCheck[ 1 ]->SetChecked( True );
        m_pColorTypeCheck[ 2 ]->SetChecked( False );
    }
    if( pElement == m_pColorTypeCheck[ 2 ] ){
        m_pColorTypeCheck[ 0 ]->SetChecked( False );
        m_pColorTypeCheck[ 1 ]->SetChecked( False );
        m_pColorTypeCheck[ 2 ]->SetChecked( True );
    }
}

void CMenuLayer::Show(){
    m_pMenuLayerPanel->SetVisible( True );
    m_pBlockTypeCheck[ 0 ]->SetChecked( False );
    m_pBlockTypeCheck[ 1 ]->SetChecked( False );
    m_pColorTypeCheck[ 0 ]->SetChecked( True );
    m_pColorTypeCheck[ 1 ]->SetChecked( False );
    m_pColorTypeCheck[ 2 ]->SetChecked( False );

}
void CMenuLayer::Hide(){
    m_pMenuLayerPanel->SetVisible( False );
}
void CMenuLayer::Update( int32 nDelta ){

}
void CMenuLayer::Render(){

}

