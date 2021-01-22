#include "workcanvas.h"
#include <include/stdio.h>
#include <standard/math.h>
#include <bigimage/spheregeometry.h>
#include <bigimage/ringgeometry.h>
#include <bigimage/boxgeometry.h>
#include <include/tools.h>
#include <standard/log.h>
#include <standard/system.h>
#include <standard/texturepack.h>

CWorkCanvas::CWorkCanvas( int32 nLeft, int32 nTop, int32 nWidth, int32 hHeight ):
CImage( nLeft, nTop, nWidth, hHeight, (CTexture*)NULL ){
    this->SetTextureCoordsInfo( 0, 1024, 1024, 0, hHeight, nWidth,0  );
    this->ApplyTextureCoordsInfo();
    m_nWidth = nWidth;
    m_nHeight = hHeight;

    this->AddUIEvent( UEM_MOUSEEVENT );
    this->AddUIEvent( UEM_KEYEVENT );
    this->OnMouseEventObject = this;
    this->OnKeyEventObject = this;
    m_bShiftDown = False;
    m_bCtrlDown = False;

    m_pGameObject = NULL;
    m_bPause = False;
}
CWorkCanvas::~CWorkCanvas(){

}
void CWorkCanvas::Init(){
    m_pTextureTarget = NEW CTextureTarget( 1024, 1024, True, True );
    this->SetTexture( m_pTextureTarget );

    CDirectionLightScene* _pScene = NEW CDirectionLightScene();
    _pScene->SetSkyBoxInfo( 1200, "MilkyWay" );
    _pScene->m_fFogNear = 400.0f;
    _pScene->m_fFogFar = 1000.0f;
    _pScene->m_tFogColor.R = 0.0f / 255.0f;
    _pScene->m_tFogColor.G = 0.0f / 255.0f;
    _pScene->m_tFogColor.B = 0.0f / 255.0f;
    _pScene->m_tFogColor.A = 1.0f;

    CScene::m_pCurrentActiveScene = _pScene;
    m_pCamera = NEW CPerspectiveCamera(65.0f, (float)m_nWidth / (float)m_nHeight, 0.01f, 2000.0f);
    m_pCamera->m_tPosition.Set(-200, 200, 200 );

    m_pCameraControls = NEW COrbitControls(m_pCamera, m_nWidth, m_nHeight);
    m_pCameraControls->target.Set( 0, 0, 0 );
    m_pCameraControls->enableDamping = False;
    m_pCameraControls->dampingFactor = 0.25f;
    m_pCameraControls->screenSpacePanning = False;
    m_pCameraControls->minDistance = 250;
    m_pCameraControls->maxDistance = 400;
    m_pCameraControls->maxPolarAngle = TWO_PI;
    _pScene->SetCamera(m_pCamera);
    CLight* _pLight = _pScene->GetLight();
    _pLight->SetDirectionPos(-200.0f, 200.0f, -200.0f);
    _pLight->SetPosition(0, 0, 0);

    CVector3* _pLightDir = _pLight->GetDirectionPos();
    CAction* _pAction = NEW CSpringAction( &_pLightDir->X, -250, 250, 10, True );
    m_vActionList.push_back( _pAction );
    _pAction = NEW CSpringAction( &_pLightDir->Z, -250, 250, 5, True );
    m_vActionList.push_back( _pAction );

    CPanelGeometry* _pGridGeometry = NEW CPanelGeometry(2000.0f, 2000.0f, 32, 32);
    CTexture* _pTestTexture = NEW CTextureFile("UV_Grid_Sm.jpg", RepeatWrapping, RepeatWrapping, LinearFilter, LinearMipMapLinearFilter, True );
    CGeometryGameObject* _pGeometryGameObject = NEW CGeometryGameObject(_pGridGeometry, _pTestTexture );
    _pGeometryGameObject->SetPosition( 0.0f, 0.0f, 0.0f );
    _pGeometryGameObject->SetOrder(100);
    _pGeometryGameObject->m_pRenderElement->m_bCastShadow = False;
    _pGeometryGameObject->m_pRenderElement->m_bLightEnable = True;
    _pScene->AddChild(_pGeometryGameObject);
}


void CWorkCanvas::OpenNewWFXFile( char* strFileName ){
    CScene::m_pCurrentActiveScene->RemoveChild( m_pGameObject );
    DELETE( m_pGameObject );
    int32 _nFileSize;
    void* _pFileData = GetAssetFileData( strFileName, &_nFileSize, NULL );
    m_pGameObject = NEW CWFXGameObject();
    m_pGameObject->Init( this, strFileName, _pFileData );
    FREE( _pFileData );
    CScene::m_pCurrentActiveScene->AddChild( m_pGameObject );
}

CTexture* CWorkCanvas::OnGetTexture( CGameModel* pGameModel, const char* strFileName ){
    CTexture* _pTexture = NULL;
    char _strTextureFileName[256];
    char _strExt[32];
    Format( _strTextureFileName, "model/%s", strFileName );
    GetFileNameType( strFileName, _strExt );
    if( strcmp( _strExt, "png" ) == 0 ){
        _pTexture = NEW CTextureFile( _strTextureFileName, RepeatWrapping, RepeatWrapping, LinearFilter, LinearMipMapLinearFilter, True );
    } else if( strcmp( _strExt, "wft" ) == 0 ){
        _pTexture = NEW CTexturePack( _strTextureFileName, RepeatWrapping, RepeatWrapping, LinearFilter, LinearMipMapLinearFilter, True );
    }
    return _pTexture;
}


void CWorkCanvas::Final(){

}
void CWorkCanvas::Update( float fDelta ){

}
int32 CWorkCanvas::Update( int32 nDelta, float fDelta ){ 
    for( list<CAction*>::iterator it = m_vActionList.begin(); it != m_vActionList.end(); it ++ ){
        CAction* _pAction = *it;
        _pAction->Update(fDelta);
    }
    m_pCameraControls->update();


    CDirectionLightScene::_fCameraX = m_pCameraControls->spherical.theta;
    CDirectionLightScene::_fCameraY = m_pCameraControls->spherical.phi;

    if( m_bPause == True ){
        CScene::m_pCurrentActiveScene->Update( 0.0f );
    } else{
        CScene::m_pCurrentActiveScene->Update( fDelta );
    }
    return 0;
}
int32 CWorkCanvas::Render(){
    CScene::m_pCurrentActiveScene->Render(m_pTextureTarget, m_nWidth , m_nHeight );
    return 0;
}
void CWorkCanvas::OnMouseEvent( CUIElement *pSelf, EUIMouseMessage eMouseMessage, int32 x, int32 y, int32 z, int32 s ){
    switch (eMouseMessage) {
    case UME_MOUSELDOWN: m_pCameraControls->onMouseDown(ORBIT, x, y);  break;
    case UME_MOUSERDOWN: m_pCameraControls->onMouseDown(_PAN, x, y);  break;
    case UME_MOUSELUP:   m_pCameraControls->onMouseUp(ORBIT, x, y);  break;
    case UME_MOUSERUP:   m_pCameraControls->onMouseUp(_PAN, x, y);  break;
    case UME_MOUSEMOVE:  m_pCameraControls->onMouseMove(x, y);  break;
    case UME_MOUSEWHEEL: m_pCameraControls->onMouseWheel(z); break;
    }
}
void CWorkCanvas::OnKeyEvent( CUIElement *pSelf, EUIKeyMessage eKeyMessage, int32 nKey ){
    
}
void CWorkCanvas::Reset(){

}

void CWorkCanvas::Test0( int32 n ){

}

void CWorkCanvas::Play(){
    m_bPause = False;
}
void CWorkCanvas::Pause(){
    m_bPause = True;
}
void CWorkCanvas::SetAction( int32 nAction ){
    m_pGameObject->SetAnimaltionIndex( nAction, nAction );
}