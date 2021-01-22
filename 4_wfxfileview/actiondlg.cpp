#include "actiondlg.h"
#include <standard/applite.h>

CActionDialog::CActionDialog( list<SActionInfo>& vActionInfoList ):
CDialog(){
    SetID( 0 );
    SetColor( 0x0 );
    int32 _nWindowWidth = 400;
    int32 _nWindowHeight = 300;
    int32 _nWindowLeft = CAppLite::m_nRootWidth / 2 - _nWindowWidth / 2;
    int32 _nWindowTop = CAppLite::m_nRootHeight / 2 - _nWindowHeight / 2;

    CPanel* _pPanel = NULL;

    _pPanel = NEW CPanel( _nWindowLeft, _nWindowTop, _nWindowWidth, _nWindowHeight );
    AddElement( _pPanel );
    m_vElementList[0] = _pPanel;

    CListView* _pLV = NEW CListView( _nWindowLeft + 4, _nWindowTop + 20, _nWindowWidth - 8, 240 );
    _pLV->SetCell( 4, 0 );
    _pLV->SetHeaderInfo( 0, "编号", LIIT_INT, 25 );
    _pLV->SetHeaderInfo( 1, "     名称", LIIT_STRING, 60 );
    _pLV->SetHeaderInfo( 2, "开始", LIIT_FLOAT, 40 );
    _pLV->SetHeaderInfo( 3, "结束", LIIT_FLOAT, 40 );
    _pPanel->AddElement( _pLV );
    m_vElementList[1] = _pLV;

    for( list<SActionInfo>::iterator it = vActionInfoList.begin(); it != vActionInfoList.end(); it ++ ){
        SActionInfo& _sActionInfo = *it;
        int32 _nRow = _pLV->AddNewRow() - 1;
        _pLV->SetCellInfo( 0, _nRow, _sActionInfo.m_nIndex );
        _pLV->SetCellInfo( 1, _nRow, _sActionInfo.m_strName );
        _pLV->SetCellInfo( 2, _nRow, _sActionInfo.m_fStartTime );
        _pLV->SetCellInfo( 3, _nRow, _sActionInfo.m_fEndTime );
    }

    CButton* _pButton = NEW CButton( _nWindowLeft + 182, _nWindowTop + 265, 80, 24, "OK" );
    _pButton->SetEnable( False );
    _pButton->SetID( 0 );
    _pButton->AddUIEvent( UEM_CLICK );
    _pButton->OnClickEventObject = this;
    _pPanel->AddElement( _pButton );
    m_vElementList[2] = _pButton;

    _pButton = NEW CButton( _nWindowLeft + 290, _nWindowTop + 265, 80, 24, "Close" );
    _pButton->SetID( 1 );
    _pButton->AddUIEvent( UEM_CLICK );
    _pButton->OnClickEventObject = this;
    _pPanel->AddElement( _pButton );
    m_vElementList[3] = _pButton;

    GUI_Element_AddElement( CAppLite::m_hRootHandle, this->m_hHandle );
}
CActionDialog::~CActionDialog(){

}
void CActionDialog::OnClick( CUIElement *pSelf ){
    Close();
}
void CActionDialog::Close(){
    for( int32 i = 0; i < 4; i ++ ){
        DELETE( m_vElementList[i] );
    }
    this->Destroy();
    delete this;
}