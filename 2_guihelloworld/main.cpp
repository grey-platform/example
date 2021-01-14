#include <standard/applite.h>
#include <standard/gui.h>

class CHelloWorldApp: public CAppLite{
public:
    CHelloWorldApp(){
    }
    virtual ~CHelloWorldApp(){

    }
    virtual int32 Init( HUIHANDLE hParentHandle, int32 nWidth, int32 nHeight ){
        CWindow* _pWindow = NEW CWindow( 100, 100, 400, 300, "HelloWorld" );
        return _pWindow->GetHandle();
    }
};

CAppLite* StartApplite(){
    return NEW CHelloWorldApp( );
}


