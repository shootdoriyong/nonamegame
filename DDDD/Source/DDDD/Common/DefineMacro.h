#pragma once

#include "MainFramework.h"
#include "Engine.h"

//#include "TRDefineMacro.generated.h"
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)   { if(p) { delete (p);   (p)=NULL; } }
#endif

#define GET_MAINFRAMEWORK()					Cast <UMainFramework>(GEngine->GameSingleton)
#define GET_INGAME_MANAGER()				GET_MAINFRAMEWORK()->_pInGameMng
#define GET_LOBBY_MANAGER()					GET_MAINFRAMEWORK()->_pLobbyMng
#define GET_UI_MANAGER()					GET_MAINFRAMEWORK()->_pUIMng
#define GET_DATA_MANAGER()					GET_MAINFRAMEWORK()->_pDataMng


//화면에 로그 출력
#define LOG_MSG(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::White, TEXT(x));}
#define LOG_STRING(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, x);}

//UClass NULL 체크
#define IS_VALID(p) (((p!=nullptr) && (p->IsValidLowLevel()))? true : false)