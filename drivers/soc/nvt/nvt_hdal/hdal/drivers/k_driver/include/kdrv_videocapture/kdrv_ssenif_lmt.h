/**
 * @file kdrv_ssenif_lmt.h
 * @brief parameter limitation of KDRV SSENIF.
 * @author ESW
 * @date in the year 2019
 */

#ifndef __KDRV_SSENIF_LIMIT_H__
#define __KDRV_SSENIF_LIMIT_H__

#include "comm/drv_lmt.h"
#include "kdrv_type.h"

typedef enum {
	KDRV_SSENIF_CAP_SIE0 	= 0x00000001,	// To SIE0/VCAP0
	KDRV_SSENIF_CAP_SIE1 	= 0x00000002,	// To SIE1/VCAP1
	KDRV_SSENIF_CAP_SIE2 	= 0x00000004,	// To SIE2/VCAP2
	KDRV_SSENIF_CAP_SIE3 	= 0x00000008,	// To SIE3/VCAP3
	KDRV_SSENIF_CAP_SIE4 	= 0x00000010,	// To SIE4/VCAP4
	KDRV_SSENIF_CAP_SIE5 	= 0x00000020,	// To SIE5/VCAP5
	KDRV_SSENIF_CAP_SIE6 	= 0x00000040,	// To SIE6/VCAP6
	KDRV_SSENIF_CAP_SIE7 	= 0x00000080,	// To SIE7/VCAP7

	KDRV_SSENIF_CAP_DL0		= 0x00000100,	// DataLane 0
	KDRV_SSENIF_CAP_DL1		= 0x00000200,	// DataLane 1
	KDRV_SSENIF_CAP_DL2		= 0x00000400,	// DataLane 2
	KDRV_SSENIF_CAP_DL3		= 0x00000800,	// DataLane 3
	KDRV_SSENIF_CAP_DL4		= 0x00001000,	// DataLane 4
	KDRV_SSENIF_CAP_DL5		= 0x00002000,	// DataLane 5
	KDRV_SSENIF_CAP_DL6		= 0x00004000,	// DataLane 6
	KDRV_SSENIF_CAP_DL7		= 0x00008000,	// DataLane 7

	KDRV_SSENIF_CAP_CK0		= 0x00010000,	// ClockLane 0
	KDRV_SSENIF_CAP_CK1		= 0x00020000,	// ClockLane 1
	KDRV_SSENIF_CAP_CK2		= 0x00040000,	// ClockLane 2
	KDRV_SSENIF_CAP_CK3		= 0x00080000,	// ClockLane 3
	KDRV_SSENIF_CAP_CK4		= 0x00100000,	// ClockLane 4
	KDRV_SSENIF_CAP_CK5		= 0x00200000,	// ClockLane 5
	KDRV_SSENIF_CAP_CK6		= 0x00400000,	// ClockLane 6
	KDRV_SSENIF_CAP_CK7		= 0x00800000,	// ClockLane 7

	KDRV_SSENIF_CAP_EXIST	= 0x80000000,	// Module Exist
	ENUM_DUMMY4WORD(KDRV_SSENIF_CAP)
} KDRV_SSENIF_CAP;



/*
	For KDRV_SSENIF_ENGINE_CSI0 / KDRV_SSENIF_ENGINE_LVDS0
*/
#define KDRV_SSENIF_CAP_CSILVDS0	(KDRV_SSENIF_CAP_EXIST | KDRV_SSENIF_CAP_SIE0 | KDRV_SSENIF_CAP_SIE1 \
									| KDRV_SSENIF_CAP_CK0 \
									| KDRV_SSENIF_CAP_DL0 | KDRV_SSENIF_CAP_DL1 | KDRV_SSENIF_CAP_DL2 | KDRV_SSENIF_CAP_DL3)

#define KDRV_SSENIF_CAP_CSILVDS0_528	(KDRV_SSENIF_CAP_EXIST | KDRV_SSENIF_CAP_SIE0 | KDRV_SSENIF_CAP_SIE1 | KDRV_SSENIF_CAP_SIE3 | KDRV_SSENIF_CAP_SIE4 \
									| KDRV_SSENIF_CAP_CK0 \
									| KDRV_SSENIF_CAP_DL0 | KDRV_SSENIF_CAP_DL1 | KDRV_SSENIF_CAP_DL2 | KDRV_SSENIF_CAP_DL3)


/*
	For KDRV_SSENIF_ENGINE_CSI1 / KDRV_SSENIF_ENGINE_LVDS1
*/
#define KDRV_SSENIF_CAP_CSILVDS1	(KDRV_SSENIF_CAP_EXIST | KDRV_SSENIF_CAP_SIE1 \
									| KDRV_SSENIF_CAP_CK1 \
								 	| KDRV_SSENIF_CAP_DL2 | KDRV_SSENIF_CAP_DL3)

#define KDRV_SSENIF_CAP_CSILVDS1_528	(KDRV_SSENIF_CAP_EXIST | KDRV_SSENIF_CAP_SIE1 | KDRV_SSENIF_CAP_SIE3 | KDRV_SSENIF_CAP_SIE4 \
										| KDRV_SSENIF_CAP_CK1 \
										| KDRV_SSENIF_CAP_DL2 | KDRV_SSENIF_CAP_DL3)


/*
	For KDRV_SSENIF_ENGINE_CSI2 / KDRV_SSENIF_ENGINE_LVDS2
*/
#define KDRV_SSENIF_CAP_CSILVDS2	(0)

/*
	For KDRV_SSENIF_ENGINE_CSI3 / KDRV_SSENIF_ENGINE_LVDS3
*/
#define KDRV_SSENIF_CAP_CSILVDS3	(0)

/*
	For KDRV_SSENIF_ENGINE_CSI4 / KDRV_SSENIF_ENGINE_LVDS4
*/
#define KDRV_SSENIF_CAP_CSILVDS4	(0)

/*
	For KDRV_SSENIF_ENGINE_CSI5 / KDRV_SSENIF_ENGINE_LVDS5
*/
#define KDRV_SSENIF_CAP_CSILVDS5	(0)

/*
	For KDRV_SSENIF_ENGINE_CSI6 / KDRV_SSENIF_ENGINE_LVDS6
*/
#define KDRV_SSENIF_CAP_CSILVDS6	(0)

/*
	For KDRV_SSENIF_ENGINE_CSI7 / KDRV_SSENIF_ENGINE_LVDS7
*/
#define KDRV_SSENIF_CAP_CSILVDS7	(0)


#endif
