/* ======================================================================= *
 * Texas Instruments OMAP(TM) Platform Software * (c) Copyright 2008 Texas
 * Instruments Incorporated. All Rights Reserved. * * Use of this software is 
 * controlled by the terms and conditions found * in the license agreement
 * under which this software has been supplied. *
 * ======================================================================== */
/**
* @file isp5_csl_utils.h
*          This file contains the bit macros for seting fields withinin specified register
* 
*
* @path Centaurus\drivers\drv_isp\inc\csl
*
* @rev 1.0
*/
/*========================================================================
*!
*! Revision History
*! 
*========================================================================= */

#ifndef _ISP5_CSL_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#define _ISP5_CSL_UTILS_H

/****************************************************************
*  INCLUDE FILES                                                 
*****************************************************************/

#include "../../common/csl_utils/csl_utils.h"

#if 1
/* ================================================================ */
/* 
 *================================================================== */
#define ISP_SET32 REG_SET32

/* ================================================================ */
/* 
 *================================================================== */
#define ISP_WRITE32 REG_WRITE32

/* ================================================================ */
/* 
 *================================================================== */
#define ISP_WRITE16 REG_WRITE16

/* ================================================================ */
/* 
 *================================================================== */
#define ISP_WRITE8 REG_WRITE8

/* ================================================================ */
/* 
 *================================================================== */
#define ISP_READ32 REG_READ32

/* ================================================================ */
/* 
 *================================================================== */
#define ISP_FEXT REG_FEXT

/* ================================================================ */
/* 
 *================================================================== */
#define register_write(add,val)		\
	*(volatile uint32*)(add)=val

#endif
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
