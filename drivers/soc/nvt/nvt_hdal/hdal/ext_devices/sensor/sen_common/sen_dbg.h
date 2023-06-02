#ifndef _SEN_DBG_H_
#define _SEN_DBG_H_

#define THIS_DBGLVL         NVT_DBG_WRN  //NVT_DBG_MSG
#define __MODULE__          sen
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" // *=All, [mark]=CustomClass

#if defined (__UITRON)
#include "DebugModule.h"
#else
#include "kwrap/debug.h"
#endif

#endif

