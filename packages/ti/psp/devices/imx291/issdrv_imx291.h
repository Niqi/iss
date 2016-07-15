/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2009 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/

#ifndef _ISSDRV_IMX291_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#define _ISSDRV_IMX291_H_

#include <ti/psp/devices/iss_sensorDriver.h>
#include <ti/psp/vps/drivers/fvid2_drvMgr.h>

void DRV_imx185RegSet(UInt16  regIndex, UInt16  regData);
void DRV_imx185RegGet(UInt16  regIndex, UInt8 *u8Data);
void DRV_imx185RegHoldSet(void);
void DRV_imx185RegHoldClear(void);

Fdrv_Handle Iss_Imx291Create(UInt32 drvId,UInt32 instanceId,Ptr createArgs,
                                Ptr createStatusArgs,const FVID2_DrvCbParams *fdmCbParams);
Int32 Iss_Imx291Init(void);
Int32 Iss_Imx291Control(Fdrv_Handle handle,UInt32 cmd, Ptr cmdArgs, Ptr cmdStatusArgs );
Int32 Iss_Imx291Delete(Fdrv_Handle handle, Ptr deleteArgs);
Int32 Iss_Imx291DeInit(void);
Int32 Iss_Imx291PinMux(void);
Int32 DRV_imx185SetRegs(void);



#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

