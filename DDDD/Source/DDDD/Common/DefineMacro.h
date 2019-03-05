#pragma once

#include "MainFramework.h"
#include "Engine.h"









//화면에 로그 출력
#define LOG_MSG(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::White, TEXT(x));}
#define LOG_STRING(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, x);}

//UClass NULL 체크
#define IS_VALID(p) (((p!=nullptr) && (p->IsValidLowLevel()))? true : false)