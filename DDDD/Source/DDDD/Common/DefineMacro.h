#pragma once

#include "MainFramework.h"
#include "Engine.h"









//ȭ�鿡 �α� ���
#define LOG_MSG(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::White, TEXT(x));}
#define LOG_STRING(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, x);}

//UClass NULL üũ
#define IS_VALID(p) (((p!=nullptr) && (p->IsValidLowLevel()))? true : false)