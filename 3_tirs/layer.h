#ifndef _LAYER_H_
#define _LAYER_H_

#include <standard/gui.h>

class CLayerSwitchEvent{
public:
    virtual void OnSwitchLayer( int32 nLayer );
};
class CLayer{
public:
    CLayer();
    virtual ~CLayer();
    virtual void Init( CWindow* pParent );
    virtual void Show();
    virtual void Hide();
    virtual void Update( int32 nDelta );
    virtual void Render();
    CLayerSwitchEvent* m_pSwitcherEventObject;
};


#endif

