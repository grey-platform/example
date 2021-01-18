#ifndef __MAIN_H__
#define __MAIN_H__

#include <standard/include/applite.h>
#include <standard/include/gui.h>
#include "menulayer.h"
#include "mainlayer.h"

BeginClass( CTirsApp )
#define CTirsApp__Data \
CAppLite__Data \
CWindow* m_pWindow;\
CLayer* m_pLayer0; \
CLayer* m_pLayer1; \
CLayer* m_pCurLayer;
#define CTirsApp__Func \
CAppLite__Func \
OverrideMemberFunc( CTirsApp, Init )\
OverrideMemberFunc( CTirsApp, Update )\
OverrideMemberFunc( CTirsApp, Render )\
OverrideMemberFunc( CTirsApp, Final )\
MemberFunc( CTirsApp, OnSwitchLayer )
DeclareFunc3( CTirsApp, Init, int32, HUIHANDLE, int32, int32 )
DeclareFunc2( CTirsApp, Update, int32, int32, float )
DeclareFunc0( CTirsApp, Render, int32 )
DeclareFunc0( CTirsApp, Final, int32 )
DeclareFunc1( CTirsApp, OnSwitchLayer, void, int32 nLayer )
EndClass( CTirsApp )



#endif
