/** ==================================================================
 *  @file   abess_l4_la_cred.h                                                  
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
 *  @Component:   ABESS_L4_LA
 *
 *  @Filename:    abess_l4_la_cred.h
 *
 *  @Description: Component description is not available
 *
 *  Generated by: Socrates CRED generator prototype
 *
    *//* ====================================================================== */

#ifndef __ABESS_L4_LA_CRED_H
#define __ABESS_L4_LA_CRED_H

#ifdef __cplusplus
extern "C" {
#endif

    /* 
     * Instance ABESS_L4_LA of component ABESS_L4_LA mapped in MONICA at address 0x49000000
     */

                                                                              /*-------------------------------------------------------------------------*//**
 * @DEFINITION   BITFIELD
 *
 * @BRIEF        The bitfield must be defined according to register width
 *               of the component - 64/32/16/8
 *
    *//*------------------------------------------------------------------------ */
#undef BITFIELD
#define BITFIELD BITFIELD_64

    /* 
     *  List of Register arrays for component ABESS_L4_LA
     *
     */

    /* 
     *  List of bundle arrays for component ABESS_L4_LA
     *
     */

    /* 
     *  List of bundles for component ABESS_L4_LA
     *
     */

    /* 
     * List of registers for component ABESS_L4_LA
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__COMPONENT
 *
 * @BRIEF        ID of the component 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__COMPONENT                             0x0ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK
 *
 * @BRIEF        ID of the interconnect 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK                               0x10ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__INITIATOR_INFO
 *
 * @BRIEF        Initiator subsystem information (read-only) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__INITIATOR_INFO                        0x18ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL
 *
 * @BRIEF        Global network control function 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL                       0x20ul

    /* 
     * List of register bitfields for component ABESS_L4_LA
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__COMPONENT__CODE   
 *
 * @BRIEF        Interconnect code - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__COMPONENT__CODE                  BITFIELD(31, 16)
#define ABESS_L4_LA__COMPONENT__CODE__POS             16

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__COMPONENT__REV   
 *
 * @BRIEF        Sonics3220 revision - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__COMPONENT__REV                   BITFIELD(15, 0)
#define ABESS_L4_LA__COMPONENT__REV__POS              0

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK__ID   
 *
 * @BRIEF        Unique on-chip interconnect ID - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK__ID                      BITFIELD(63, 32)
#define ABESS_L4_LA__NETWORK__ID__POS                 32

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__INITIATOR_INFO__THREADS   
 *
 * @BRIEF        Number of initiator threads - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__INITIATOR_INFO__THREADS          BITFIELD(50, 48)
#define ABESS_L4_LA__INITIATOR_INFO__THREADS__POS     48

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__INITIATOR_INFO__CONNID_WIDTH   
 *
 * @BRIEF        Initiator subsystem connID width - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__INITIATOR_INFO__CONNID_WIDTH     BITFIELD(46, 44)
#define ABESS_L4_LA__INITIATOR_INFO__CONNID_WIDTH__POS 44

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__INITIATOR_INFO__BYTE_DATA_WIDTH_EXP   
 *
 * @BRIEF        Initiator subsystem data width - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__INITIATOR_INFO__BYTE_DATA_WIDTH_EXP BITFIELD(42, 40)
#define ABESS_L4_LA__INITIATOR_INFO__BYTE_DATA_WIDTH_EXP__POS 40

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__INITIATOR_INFO__ADDR_WIDTH   
 *
 * @BRIEF        Initiator subsystem address width - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__INITIATOR_INFO__ADDR_WIDTH       BITFIELD(37, 32)
#define ABESS_L4_LA__INITIATOR_INFO__ADDR_WIDTH__POS  32

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__INITIATOR_INFO__PROT_GROUPS   
 *
 * @BRIEF        Number of protection groups - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__INITIATOR_INFO__PROT_GROUPS      BITFIELD(27, 24)
#define ABESS_L4_LA__INITIATOR_INFO__PROT_GROUPS__POS 24

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__INITIATOR_INFO__NUMBER_REGIONS   
 *
 * @BRIEF        Number of regions - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__INITIATOR_INFO__NUMBER_REGIONS   BITFIELD(23, 16)
#define ABESS_L4_LA__INITIATOR_INFO__NUMBER_REGIONS__POS 16

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__INITIATOR_INFO__SEGMENTS   
 *
 * @BRIEF        Number of segments - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__INITIATOR_INFO__SEGMENTS         BITFIELD(3, 0)
#define ABESS_L4_LA__INITIATOR_INFO__SEGMENTS__POS    0

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__CLOCK_GATE_DISABLE   
 *
 * @BRIEF        Overrides clock gating - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__CLOCK_GATE_DISABLE BITFIELD(56, 56)
#define ABESS_L4_LA__NETWORK_CONTROL__CLOCK_GATE_DISABLE__POS 56

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__THREAD0_PRI   
 *
 * @BRIEF        Set thread priority - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__THREAD0_PRI     BITFIELD(52, 52)
#define ABESS_L4_LA__NETWORK_CONTROL__THREAD0_PRI__POS 52

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__EXT_CLOCK   
 *
 * @BRIEF        Global external clock control - (RO) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__EXT_CLOCK       BITFIELD(40, 40)
#define ABESS_L4_LA__NETWORK_CONTROL__EXT_CLOCK__POS  40

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE   
 *
 * @BRIEF        Timeout period - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE    BITFIELD(10, 8)
#define ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__POS 8

    /* 
     * List of register bitfields values for component ABESS_L4_LA
     *
     */

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_0
 *
 * @BRIEF        timeout disabled - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_0 0x0ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_1
 *
 * @BRIEF        base cycles is set to 2^6 Sonics3220 clock cycles - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_1 0x1ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_2
 *
 * @BRIEF        base cycles is set to 2^8 Sonics3220 clock cycles - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_2 0x2ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_3
 *
 * @BRIEF        base cycles is set to 2^10 Sonics3220 clock cycles - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_3 0x3ul

                                                                             /*-------------------------------------------------------------------------*//**
 * @DEFINITION   ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_4
 *
 * @BRIEF        base cycles is set to 2^12 Sonics3220 clock cycles - (RW) 
 *
    *//*------------------------------------------------------------------------ */
#define ABESS_L4_LA__NETWORK_CONTROL__TIMEOUT_BASE__TA_NETWORK_CONTROL_TIMEOUT_BASE_4 0x4ul

#ifdef __cplusplus
}
#endif
#endif                                                     /* __ABESS_L4_LA_CRED_H 
                                                            */
