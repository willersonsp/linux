#ifndef __MODULE_DBG_H_
#define __MODULE_DBG_H_

#if defined(__LINUX)
#define vk_pr_warn pr_warn
#define vk_printk printk
#elif defined(__FREERTOS)
#include <stdio.h>
#define vk_pr_warn printf
#define vk_printk printf

#ifndef unlikely
#define unlikely(x) (x)
#endif

#else
#error Not supported OS
#endif


#define NVT_DBG_FATAL     0
#define NVT_DBG_ERR       1
#define NVT_DBG_WRN       2
#define NVT_DBG_WARN      2  // 1
#define NVT_DBG_UNIT      3
#define NVT_DBG_FUNC      4
#define NVT_DBG_IND       5
#define NVT_DBG_INFO      5  // 2
#define NVT_DBG_MSG       6
#define NVT_DBG_VALUE     7
#define NVT_DBG_USER      8



//#define nvt_dbg(fmt, ...)
extern unsigned int jpeg_debug_level;

#if 1
#ifdef DEBUG
#define nvt_dbg(level, fmt, args...)                \
	do {                                               \
		if (unlikely(NVT_DBG_##level <= jpeg_debug_level))    \
			vk_pr_warn("%s:" fmt, __func__, ##args);   \
	} while (0)
#else
#define nvt_dbg(fmt, ...)
#endif
#define nvt_dump_dbg(level, fmt, args...)                   \
	do {													\
		if (unlikely(NVT_DBG_##level <= jpeg_debug_level)) {  \
			vk_printk(fmt, ## args);						\
		}													\
	} while (0)
#endif
#endif


#define DBG_FATAL(fmt, args...) nvt_dbg(FATAL, fmt, ##args)
#if defined(__LINUX)
#define DBG_ERR(fmt, args...) nvt_dump_dbg(ERR, fmt, ##args)
#define DBG_WRN(fmt, args...) nvt_dump_dbg(WRN, fmt, ##args)
#else
#define DBG_ERR(fmt, args...) nvt_dbg(ERR, fmt, ##args)
#define DBG_WRN(fmt, args...) nvt_dbg(WRN, fmt, ##args)
#endif
#define DBG_UNIT(fmt, args...) nvt_dbg(UNIT, fmt, ##args)
#define DBG_FUNC(fmt, args...) nvt_dbg(FUNC, fmt, ##args)
#define DBG_IND(fmt, args...) nvt_dbg(IND, fmt, ##args)
#define DBG_MSG(fmt, args...) nvt_dbg(MSG, fmt, ##args)
#define DBG_VALUE(fmt, args...) nvt_dbg(VALUE, fmt, ##args)
#define DBG_USER(fmt, args...) nvt_dbg(USER, fmt, ##args)
#define DBG_DUMP(fmt, args...) vk_pr_warn("%s:" fmt, __func__, ##args);
