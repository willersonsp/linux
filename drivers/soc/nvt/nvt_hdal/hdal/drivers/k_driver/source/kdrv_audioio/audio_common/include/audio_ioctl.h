#ifndef __AUDIO_IOCTL_CMD_H_
#define __AUDIO_IOCTL_CMD_H_

#include <linux/ioctl.h>

#define MODULE_REG_LIST_NUM     2

typedef struct reg_info {
    unsigned int uiAddr;
    unsigned int uiValue;
} REG_INFO;

typedef struct reg_info_list {
    unsigned int uiCount;
    REG_INFO RegList[MODULE_REG_LIST_NUM];
} REG_INFO_LIST;

//============================================================================
// IOCTL command
//============================================================================
#define AUDIO_IOC_COMMON_TYPE 'M'
#define AUDIO_IOC_START                   _IO(AUDIO_IOC_COMMON_TYPE, 1)
#define AUDIO_IOC_STOP                    _IO(AUDIO_IOC_COMMON_TYPE, 2)

#define AUDIO_IOC_READ_REG                _IOWR(AUDIO_IOC_COMMON_TYPE, 3, void*)
#define AUDIO_IOC_WRITE_REG               _IOWR(AUDIO_IOC_COMMON_TYPE, 4, void*)
#define AUDIO_IOC_READ_REG_LIST           _IOWR(AUDIO_IOC_COMMON_TYPE, 5, void*)
#define AUDIO_IOC_WRITE_REG_LIST          _IOWR(AUDIO_IOC_COMMON_TYPE, 6, void*)




/* Add other command ID here*/


#endif
