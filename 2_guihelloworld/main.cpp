#include <standard/applite.h> //要显示gui则必须引入此文件，并继承CAppLite
#include <standard/gui.h> //必须引入，定义了gui所需的各种方法

//该示例展示了如何创建一个窗口，并在窗口中增加控件。
//首先，创建窗口控件的类必须继承CAppLite
class CHelloWorldApp: public CAppLite{
public:
//需要保留构造器、析构函数 注意析构函数是虚方法
    CHelloWorldApp(){
    }
    virtual ~CHelloWorldApp(){

    }
//Init也必须是虚方法，写法如下
    virtual int32 Init( HUIHANDLE hParentHandle, int32 nWidth, int32 nHeight ){
		//创建一个窗口，参数依次为：x位置，y位置，宽，高，窗口标题
        CWindow* _pWindow = NEW CWindow( 100, 100, 400, 300, "HelloWorld" );
		//创建一个按钮，参数依次为：x位置，y位置，宽，高，按钮文字
        CButton* _pBtn = NEW CButton( 300, 200, 100, 30, "Button" );
		//将创建好的按钮，加入创建的窗口中
        _pWindow->AddElement( _pBtn );
        
        return _pWindow->GetHandle();
    }
};
//实际执行的方法在这里，写法如下：
CAppLite* StartApplite(){
    return NEW CHelloWorldApp( );
}


