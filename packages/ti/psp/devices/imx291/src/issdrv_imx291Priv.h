/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2009 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/

#ifndef _ISS_IMX291_PRIV_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#define _ISS_IMX291_PRIV_H_

#include <string.h>
#include <xdc/runtime/System.h>
#include <ti/psp/vps/common/trace.h>
#include <ti/psp/devices/imx291/issdrv_imx291.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/psp/iss/drivers/alg/2A/inc/issdrv_algTIaewb.h>

/* Driver object state - NOT IN USE */
#define ISS_IMX291_OBJ_STATE_UNUSED   (0)
/* Driver object state - IN USE and IDLE */
#define ISS_IMX291_OBJ_STATE_IDLE     (1)

/*
  Driver handle object
*/
typedef struct
{
    UInt32 state;               /* handle state */
    UInt32 handleId;            /* handle ID, 0..ISS_DEVICE_MAX_HANDLES-1 */
    Semaphore_Handle lock;      /* handle lock */
    Iss_SensorCreateParams createArgs;    /* create time arguments  */
    UInt8 regCache[2][256]; 	/* register read cache */
} Iss_Imx291Obj;

/*
  Glabal driver object
*/
typedef struct
{
    FVID2_DrvOps fvidDrvOps;    /* FVID2 driver ops */
    Semaphore_Handle lock;      /* global driver lock */
    Iss_Imx291Obj Imx291Obj[ISS_DEVICE_MAX_HANDLES];
    /*
     * handle objects
     */
} Iss_Imx291CommonObj;


//Int32 Iss_Imx185GetChipId(Iss_Imx291Obj * pObj,Iss_SensorChipIdParams * pPrm,Iss_SensorChipIdStatus * pStatus );
//Int32 Iss_Imx185Reset(Iss_Imx291Obj * pObj );
//Int32 Iss_Imx185Start(Iss_Imx291Obj * pObj );
//Int32 Iss_Imx185Stop(Iss_Imx291Obj * pObj );
//Int32 Iss_Imx185RegWrite(Iss_Imx291Obj * pObj,Iss_VideoDecoderRegRdWrParams * pPrm );
//Int32 Iss_Imx185RegRead(Iss_Imx291Obj * pObj,Iss_VideoDecoderRegRdWrParams * pPrm );
Int32 Iss_Imx291LockObj ( Iss_Imx291Obj * pObj );
Int32 Iss_Imx291UnlockObj ( Iss_Imx291Obj * pObj );
Int32 Iss_Imx291Lock();
Int32 Iss_Imx291Unlock();
Iss_Imx291Obj *Iss_Imx291AllocObj();
Int32 Iss_Imx291FreeObj(Iss_Imx291Obj *pObj);

//Int32 Iss_Imx185PowerDown ( Iss_Imx291Obj * pObj, UInt32 powerDown );
//Int32 Iss_Imx185OutputEnable ( Iss_Imx291Obj * pObj, UInt32 enable );

Int32 Iss_Imx291UpdateExpGain(Iss_Imx291Obj *pObj, Ptr createArgs);
int Transplant_DRV_imgsSetEshutter();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*  _ISS_IMX291_PRIV_H_  */
