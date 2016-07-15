/** ==================================================================
 *  @file   ipe3_bfsw_cred.h                                                  
 *                                                                    
 *  @path   /ti/psp/iss/hal/cred_cram/cred/inc/cortexm3_sys_ape/                                                  
 *                                                                    
 *  @desc   This  File contains.                                      
 * ===================================================================
 *  Copyright (c) Texas Instruments Inc 2011, 2012                    
 *                                                                    
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * ===================================================================*/

/* ============================================================================ 
 * TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION Property of Texas
 * Instruments For Unrestricted Internal Use Only Unauthorized reproduction
 * and/or distribution is strictly prohibited.  This product is protected
 * under copyright law and trade secret law as an unpublished work.  Created
 * 2008, (C) Copyright 2008 Texas Instruments.  All rights reserved. */

/**
 *  @Component:   IPE3_BFSW
 *
 *  @Filename:    ipe3_bfsw_cred.h
 *
 *  @Description: Component description is not available
 *
 *  Generated by: Socrates CRED generator prototype
 *
    *//* ====================================================================== */

#ifndef __IPE3_BFSW_CRED_H
#define __IPE3_BFSW_CRED_H

#ifdef __cplusplus
extern "C" {
#endif

    /* 
     * Instance IPE3_CFG__BFSW of component IPE3_BFSW mapped in MONICA at address 0x5A058A00
     */

                                                                              /*-------------------------------------------------------------------------*//**
 * @DEFINITION   BITFIELD
 *
 * @BRIEF        The bitfield must be defined according to register width
 *               of the component - 64/32/16/8
 *
    *//*------------------------------------------------------------------------ */
#undef BITFIELD
#define BITFIELD BITFIELD_32

    /* 
     *  List of Register arrays for component IPE3_BFSW
     *
     */

    /* 
     *  List of bundle arrays for component IPE3_BFSW
     *
     */

    /* 
     *  List of bundles for component IPE3_BFSW
     *
     */

    /* 
     * List of registers for component IPE3_BFSW
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   IPE3_BFSW__VIEWMODE
 *
 * @BRIEF        Register description is not available
 *
    *//*------------------------------------------------------------------------ */
#define IPE3_BFSW__VIEWMODE                                0x0ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   IPE3_BFSW__MSTID
 *
 * @BRIEF        Master ID 1 Register 
 *               Select master between HWA and DMA bus. 
 *               This register is used in both full view and ping-pong view 
 *               mode. 
 *               This register is for buffers which has two physical 
 *               memories. 
 *               This register is affected by direct_switch_pi input port. 
 *
    *//*------------------------------------------------------------------------ */
#define IPE3_BFSW__MSTID                                   0x4ul

    /* 
     * List of register bitfields for component IPE3_BFSW
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   IPE3_BFSW__VIEWMODE__VIEW_IPORGBUF   
 *
 * @BRIEF        View mode selection for iporgbuf 
 *               0: full view mode is selected 
 *               1: ping-pong view mode is selected - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define IPE3_BFSW__VIEWMODE__VIEW_IPORGBUF            BITFIELD(0, 0)
#define IPE3_BFSW__VIEWMODE__VIEW_IPORGBUF__POS       0

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   IPE3_BFSW__MSTID__MST_IPORGBUF_B   
 *
 * @BRIEF        Master selection for iporgbuf B. 
 *               This bit is only used in ping-pong view mode. 
 *               0: buffer B is assigned to DMA 
 *               1: buffer B is assigned to HWA 
 *               This bit has no effect in full view mode. 
 *               If direct_switch_pi is high, the value of this bit is 
 *               inverted. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define IPE3_BFSW__MSTID__MST_IPORGBUF_B              BITFIELD(1, 1)
#define IPE3_BFSW__MSTID__MST_IPORGBUF_B__POS         1

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   IPE3_BFSW__MSTID__MST_IPORGBUF_A   
 *
 * @BRIEF        Master selection for iporgbuf A. 
 *               This bit is used in both full view mode and ping-pong view 
 *               mode. 
 *               In full view mode, 
 *               0: both buffer A and B are assigned to DMA 
 *               1: both buffer A and B are assigned to HWA 
 *               In ping-pong view mode, 
 *               0: buffer A is assigned to DMA 
 *               1: buffer A is assigned to HWA 
 *               (Buffer B is not affected in ping-pong view mode.) 
 *               If direct_switch_pi is high, the value of this bit is 
 *               inverted. - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define IPE3_BFSW__MSTID__MST_IPORGBUF_A              BITFIELD(0, 0)
#define IPE3_BFSW__MSTID__MST_IPORGBUF_A__POS         0

    /* 
     * List of register bitfields values for component IPE3_BFSW
     *
     */

#ifdef __cplusplus
}
#endif
#endif                                                     /* __IPE3_BFSW_CRED_H 
                                                            */