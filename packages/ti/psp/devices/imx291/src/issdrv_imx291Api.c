/*******************************************************************************
 *                                                                             *
 * Copyright (c) 2009 Texas Instruments Incorporated - http://www.ti.com/      *
 *                        ALL RIGHTS RESERVED                                  *
 *                                                                             *
 ******************************************************************************/
#include <math.h>
#include <ti/psp/devices/imx291/src/issdrv_imx291Priv.h>
#include <ti/psp/devices/imx291/issdrv_imx291_config.h>
#include <ti/psp/platforms/iss_platform.h>
#include <ti/psp/iss/hal/iss/isp/isif/inc/isif_reg.h>
#include <ti/psp/iss/hal/iss/isp/isif/inc/isif.h>
#include <ti/psp/devices/imx291/src/imx291_reg_setting.h>
#include "ti/psp/devices/src/vpsdrv_devicePriv.h"
#include <ti/psp/iss/drivers/alg/2A/inc/issdrv_alg2APriv.h>

#define IMGS_SENSOR_LINEWIDTH		(1125)
#define IMGS_SENSOR_LINEWIDTH_3MP	(1608)

int Transplant_DRV_imgsSetEshutter(Uint32 eshutterInUsec, int setRegDirect);
int Transplant_DRV_imgsSetAgain(int again, int setRegDirect);
int DRV_IMX291SetRegs(void);

/* add by lsr 20130624 增加曝光和增益 begin */
 int shutter_table[] =
{
	10,		/* 1/100000	*/
	100,	/* 1/10000	*/
	1000,	/* 1/1000	*/
	2000,	/* 1/500	*/
	4000,	/* 1/250	*/
	10000,	/* 1/100	*/
	16666,	/* 1/60		*/
	33333,	/* 1/30		*/
	66666,	/* 1/15		*/
	133333	/* 1/7.5	*/
};

 float gain_table[] =
{
	1000,  /* 0dB 1000, */
	1200,  /* 1.5dB 2000, */
	1500,  /* 3dB 3000, */
	2000,  /* 4.5dB 4000, */
	3000,  /* 6dB 5000, */
	4000,  /* 7.5dB 6000, */
	8000,  /* 9dB 7000, */
	16000,  /* 10.5dB 8000, */
	24000,  /* 12dB	8500, */
	32000,  /* 13.5dB 8000, */
	64000,  /* 15dB 9500, */
	128000,  /* 16dB 10000,	*/
};

int g_s32ExpMode;
int g_s32ExpPrevIndex;
int g_s32GainPrevIndex;
/* add by lsr 20130624 增加曝光和增益 end */

/* add by lsr 20130727 */
int g_s32Framerate;

extern isif_regs_ovly isif_reg;

/* Global object storing all information related to all
  IMX291 driver handles */
static Iss_Imx291CommonObj 	gIss_Imx291CommonObj;
extern ti2a_output 		ti2a_output_params;

#define	 CAMERARST_PINCNTL153_PINMUX	    *(volatile Uint32*)(0x48140000 + 0x0A60) /* gp2_18*/
#define	 CLKENABLE_PINCNTL224_PINMUX	    *(volatile Uint32*)(0x48140000 + 0x0B7C) /* gp3_16*/

#define	 CAMERARST_PINCNTL153_OE	     	*(volatile Uint32*)(0x481AC000 + 0x0134)
#define	 CLKENABLE_PINCNTL224_OE	     	*(volatile Uint32*)(0x481AE000 + 0x0134)

#define  CAMERARST_PINCNTL153_DATAOUT		*(volatile Uint32*)(0x481AC000 + 0x013C)
#define  CLKENABLE_PINCNTL224_DATAOUT		*(volatile Uint32*)(0x481AE000 + 0x013C)

static void Iss_IMX291_Reset(void)
{
	Int32 tmpValue;

	/* OUT SENSOR_OEn HIGH-使得晶振输出时钟*/
	CLKENABLE_PINCNTL224_PINMUX = 0x60080;
	tmpValue = CLKENABLE_PINCNTL224_OE;
	tmpValue &= ~(1<<16);
	CLKENABLE_PINCNTL224_OE = tmpValue;
	tmpValue = CLKENABLE_PINCNTL224_DATAOUT;
	tmpValue |= (1<<16);
	CLKENABLE_PINCNTL224_DATAOUT = tmpValue;
	Task_sleep(200);

	/* OUT DM8127_RESET LOW使得CMOS正常*/
	CAMERARST_PINCNTL153_PINMUX = 0x60080;
	tmpValue = CAMERARST_PINCNTL153_OE;
	tmpValue &= ~(1<<18);
	CAMERARST_PINCNTL153_OE = tmpValue;
	tmpValue = CAMERARST_PINCNTL153_DATAOUT;
	tmpValue &= ~(1<<18);
	CAMERARST_PINCNTL153_DATAOUT = tmpValue;
	Task_sleep(200);
	tmpValue = CAMERARST_PINCNTL153_DATAOUT;
	tmpValue |= (1<<18);
	CAMERARST_PINCNTL153_DATAOUT = tmpValue;
}



/* Control API that gets called when FVID2_control is called

  This API does handle level semaphore locking

  handle - Imx291 driver handle
  cmd - command
  cmdArgs - command arguments
  cmdStatusArgs - command status

  returns error in case of
  - illegal parameters
  - I2C command RX/TX error
*/

Int32 Iss_Imx291Control ( Fdrv_Handle handle,
                           UInt32 cmd, Ptr cmdArgs, Ptr cmdStatusArgs )
{
    Iss_Imx291Obj *pObj = ( Iss_Imx291Obj * ) handle;
    Int32 status = FVID2_SOK;
    //Int32 *pInterTime = NULL;
	//int  loopNum=1;

    if ( pObj == NULL )
        return FVID2_EBADARGS;

    /* add by lsr 20141103 增加wdr模式 */
    //Int32 enable = *(Int32 *) cmdArgs;

    /*
     * lock handle
     */
    Iss_Imx291LockObj ( pObj );

    switch ( cmd )
    {
        case FVID2_START:
            break;
        case FVID2_STOP:
            break;
        case IOCTL_ISS_SENSOR_GET_CHIP_ID:
            break;
        case IOCTL_ISS_SENSOR_RESET:
            break;
        case IOCTL_ISS_SENSOR_REG_WRITE:
            break;
        case IOCTL_ISS_SENSOR_REG_READ:
            break;
		case IOCTL_ISS_SENSOR_UPDATE_FRAMERATE:
			break;
        case IOCTL_ISS_SENSOR_FRAME_RATE_SET:
            break;
        case IOCTL_ISS_SENSOR_UPDATE_EXP_GAIN:
            break;
		case IOCTL_ISS_SENSOR_PWM_CONFIG:
			break;
        default:
            status = FVID2_EUNSUPPORTED_CMD;
			Vps_printf( " !!!!!! FAIL, %s ( FVID2_EUNSUPPORTED_CMD ) !!!!!! \n", __FUNCTION__ );
            break;
    }

    /*
     * unlock handle
     */
    Iss_Imx291UnlockObj ( pObj );

    return status;
}

/*
  Create API that gets called when FVID2_create is called

  This API does not configure the Imx291 is any way.

  This API
  - validates parameters
  - allocates driver handle
  - stores create arguments in its internal data structure.

  Later the create arguments will be used when doing I2C communcation with
  Imx291

  drvId - driver ID, must be FVID2_ISS_VID_DEC_Imx291_DRV
  instanceId - must be 0
  createArgs - create arguments
  createStatusArgs - create status
  fdmCbParams  - NOT USED, set to NULL

  returns NULL in case of any error
*/
Fdrv_Handle Iss_Imx291Create ( UInt32 drvId,
                                UInt32 instanceId,
                                Ptr createArgs,
                                Ptr createStatusArgs,
                                const FVID2_DrvCbParams * fdmCbParams )
{
    Iss_Imx291Obj *pObj;
    Iss_SensorCreateParams *sensorCreateArgs
        = ( Iss_SensorCreateParams * ) createArgs;

    Iss_SensorCreateStatus *sensorCreateStatus
        = ( Iss_SensorCreateStatus * ) createStatusArgs;

    /*
     * check parameters
     */
    if ( sensorCreateStatus == NULL )
        return NULL;

    sensorCreateStatus->retVal = FVID2_SOK;

    if ( drvId != FVID2_ISS_SENSOR_IMX291_DRV
         || instanceId != 0 || sensorCreateArgs == NULL )
    {
        sensorCreateStatus->retVal = FVID2_EBADARGS;
        return NULL;
    }

    if ( sensorCreateArgs->deviceI2cInstId >= ISS_DEVICE_I2C_INST_ID_MAX )
    {
        sensorCreateStatus->retVal = FVID2_EINVALID_PARAMS;
        return NULL;
    }

    /*
     * allocate driver handle
     */
    pObj = Iss_Imx291AllocObj (  );
    if ( pObj == NULL )
    {
        sensorCreateStatus->retVal = FVID2_EALLOC;
        return NULL;
    }

    /*
     * copy parameters to allocate driver handle
     */
    memcpy ( &pObj->createArgs, sensorCreateArgs,
             sizeof ( *sensorCreateArgs ) );

    /*
     * return driver handle object pointer
     */

    return pObj;
}

/*
  Delete function that is called when FVID2_delete is called

  This API
  - free's driver handle object

  handle - driver handle
  deleteArgs - NOT USED, set to NULL

*/
Int32 Iss_Imx291Delete ( Fdrv_Handle handle, Ptr deleteArgs )
{
    Iss_Imx291Obj *pObj = ( Iss_Imx291Obj * ) handle;

    if ( pObj == NULL )
        return FVID2_EBADARGS;

    /*
     * free driver handle object
     */
    Iss_Imx291FreeObj ( pObj );

    return FVID2_SOK;
}



/*
  System init for Imx291 driver

  This API
  - create semaphore locks needed
  - registers driver to FVID2 sub-system
  - gets called as part of Iss_deviceInit()
*/
Int32 Iss_Imx291Init(void)
{
    Semaphore_Params semParams;
    Int32 status = FVID2_SOK;

    /*
     * Set to 0's for global object, descriptor memory
     */
    memset ( &gIss_Imx291CommonObj, 0, sizeof ( gIss_Imx291CommonObj ) );
    /*
     * Create global Imx291 lock
     */
    Semaphore_Params_init ( &semParams );

    semParams.mode = Semaphore_Mode_BINARY;

    gIss_Imx291CommonObj.lock = Semaphore_create ( 1u, &semParams, NULL );
    if ( gIss_Imx291CommonObj.lock == NULL )
        status = FVID2_EALLOC;
    if ( status == FVID2_SOK )
    {
        DRV_IMX291SetRegs();
        gIss_Imx291CommonObj.fvidDrvOps.create = ( FVID2_DrvCreate )Iss_Imx291Create;
        gIss_Imx291CommonObj.fvidDrvOps.delete = Iss_Imx291Delete;
        gIss_Imx291CommonObj.fvidDrvOps.control= Iss_Imx291Control;
        gIss_Imx291CommonObj.fvidDrvOps.queue  = NULL;
        gIss_Imx291CommonObj.fvidDrvOps.dequeue= NULL;
        gIss_Imx291CommonObj.fvidDrvOps.processFrames = NULL;
        gIss_Imx291CommonObj.fvidDrvOps.getProcessedFrames = NULL;
        gIss_Imx291CommonObj.fvidDrvOps.drvId = FVID2_ISS_SENSOR_IMX291_DRV;

        status = FVID2_registerDriver ( &gIss_Imx291CommonObj.fvidDrvOps );

        if ( status != FVID2_SOK )
        {
            /*
             * Error - free acquired resources
             */
            Semaphore_delete ( &gIss_Imx291CommonObj.lock );
        }
    }
    if ( status != FVID2_SOK )
    {
        Vps_printf ( " ERROR %s:%s:%d !!!\n", __FILE__, __FUNCTION__,
                        __LINE__ );
    }

    return status;
}

/*
  System de-init for Imx291 driver

  This API
  - de-registers driver from FVID2 sub-system
  - delete's allocated semaphore locks
  - gets called as part of Iss_deviceDeInit()
*/
Int32 Iss_Imx291DeInit()
{
    /*
     * Unregister FVID2 driver
     */
    FVID2_unRegisterDriver ( &gIss_Imx291CommonObj.fvidDrvOps );

    /*
     * Delete semaphore's
     */
    Semaphore_delete ( &gIss_Imx291CommonObj.lock );

    return 0;
}

Int32 Iss_Imx291PinMux()
{
 	/* setup CAM input pin mux */
	*PINCNTL156 = 0x00050002;				// select function 2 with receiver enabled and pullup/down disabled  - only works in supervisor mode
	*PINCNTL157 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL158 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL159 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL160 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL161 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL162 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL163 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL164 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL165 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL166 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL167 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL168 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL169 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL170 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL171 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL172 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL173 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL174 = 0x00050002;				// select function 2  - only works in supervisor mode
	*PINCNTL175 = 0x00050002;				// select function 2  - only works in supervisor mode

    #if defined(TI_8107_BUILD)
    *PINCNTL74 = 0xE0040;   /* i2c2_scl_mux0 */
    *PINCNTL75 = 0xE0040;   /* i2c2_sda_mux0 */
    *PINCNTL135 = 0xE0040;   /* i2c2_scl_mux0 */
    *PINCNTL136 = 0xE0040;   /* i2c2_sda_mux0 */
    #endif
	#if defined(TI_814X_BUILD)
    *PINCNTL74 = 0x00020;
    *PINCNTL75 = 0x00020;
    #endif

    *PINCNTL85 = 0x00000080;
    *PINCNTL86 = 0x00000080;
    *PINCNTL88 = 0x00000080;

	Iss_IMX291_Reset();

    //Vps_printf (" spi gio enable in %s\n",__FUNCTION__);
	return 0;
}
/*
  Handle level lock
*/
Int32 Iss_Imx291LockObj ( Iss_Imx291Obj * pObj )
{
    Semaphore_pend ( pObj->lock, BIOS_WAIT_FOREVER );

    return FVID2_SOK;
}

/*
  Handle level unlock
*/
Int32 Iss_Imx291UnlockObj ( Iss_Imx291Obj * pObj )
{
    Semaphore_post ( pObj->lock );

    return FVID2_SOK;
}

/*
  Global driver level lock
*/
Int32 Iss_Imx291Lock (  )
{
    Semaphore_pend ( gIss_Imx291CommonObj.lock, BIOS_WAIT_FOREVER );

    return FVID2_SOK;
}

/*
  Global driver level unlock
*/
Int32 Iss_Imx291Unlock (  )
{
    Semaphore_post ( gIss_Imx291CommonObj.lock );

    return FVID2_SOK;
}

/*
  Allocate driver object

  Searches in list of driver handles and allocate's a 'NOT IN USE' handle
  Also create's handle level semaphore lock

  return NULL in case handle could not be allocated
*/
Iss_Imx291Obj *Iss_Imx291AllocObj (  )
{
    UInt32 handleId;
    Iss_Imx291Obj *pObj;
    Semaphore_Params semParams;
    UInt32 found = FALSE;

    /*
     * Take global lock to avoid race condition
     */
    Iss_Imx291Lock (  );

    /*
     * find a unallocated object in pool
     */
    for ( handleId = 0; handleId < ISS_DEVICE_MAX_HANDLES; handleId++ )
    {

        pObj = &gIss_Imx291CommonObj.Imx291Obj[handleId];

        if ( pObj->state == ISS_IMX291_OBJ_STATE_UNUSED )
        {
            /*
             * free object found
             */

            /*
             * init to 0's
             */
            memset ( pObj, 0, sizeof ( *pObj ) );

            /*
             * init state and handle ID
             */
            pObj->state = ISS_IMX291_OBJ_STATE_UNUSED;
            pObj->handleId = handleId;

            /*
             * create driver object specific semaphore lock
             */
            Semaphore_Params_init ( &semParams );

            semParams.mode = Semaphore_Mode_BINARY;

            pObj->lock = Semaphore_create ( 1u, &semParams, NULL );

            found = TRUE;

            if ( pObj->lock == NULL )
            {
                /*
                 * Error - release object
                 */
                found = FALSE;
                pObj->state = ISS_IMX291_OBJ_STATE_UNUSED;
            }

            break;
        }
    }

    /*
     * Release global lock
     */
    Iss_Imx291Unlock (  );

    if ( found )
        return pObj;    /* Free object found return it */

    /*
     * free object not found, return NULL
     */
    return NULL;
}

/*
  De-Allocate driver object

  Marks handle as 'NOT IN USE'
  Also delete's handle level semaphore lock
*/
Int32 Iss_Imx291FreeObj ( Iss_Imx291Obj * pObj )
{
    /*
     * take global lock
     */
    Iss_Imx291Lock (  );

    if ( pObj->state != ISS_IMX291_OBJ_STATE_UNUSED )
    {
        /*
         * mark state as unused
         */
        pObj->state = ISS_IMX291_OBJ_STATE_UNUSED;

        /*
         * delete object locking semaphore
         */
        Semaphore_delete ( &pObj->lock );
    }

    /*
     * release global lock
     */
    Iss_Imx291Unlock (  );

    return FVID2_SOK;
}

int DRV_IMX291SetRegs(void)
{
	int i = 0;
    int IMX291_reg_count = 0;
	Uint8 regValue;
	UInt16 regAddr;
	Int32 status;
    IMX291_reg_count = (sizeof(IMX291_SETTING_SHORT) / sizeof(unsigned short) );

    Vps_printf("IMX291_reg_count = %d sizeof(IMX291_SETTING) = %d  sizeof(unsigned short) = %d  I am in the %s %s %d\n",IMX291_reg_count,sizeof(IMX291_SETTING_SHORT),sizeof(unsigned short),__FILE__,__FUNCTION__,__LINE__);

    //DRV_imx291RegHoldSet();
	regAddr=0x3001;regValue=0x01;
	status = Iss_device16Write8(2, 0x1A, &regAddr, &regValue,1);

	for (i = 0; i < IMX291_reg_count; i = i+2)
	{

			regAddr=(Uint16)IMX291_SETTING_SHORT[i];
			regValue=(Uint8)IMX291_SETTING_SHORT[i+1];
	        /* add by dxm 2013.5.21, 修改SPI发送*/
			if((regAddr & 0x0500) == 0x0500)
			{
				regAddr &= ~(0xFF00);
				regAddr |= (0x3300);
			}
			else if((regAddr & 0x0400) == 0x0400)
			{
				regAddr &= ~(0xFF00);
				regAddr |= (0x3200);
			}
			else if((regAddr & 0x0300) == 0x0300)
			{
				regAddr &= ~(0xFF00);
				regAddr |= (0x3100);
			}
			else if((regAddr & 0x0200) == 0x0200)
			{
				regAddr &= ~(0xFF00);
				regAddr |= (0x3000);
			}
			//Vps_printf("Ori[%04x][%02x]:[%04x][%02x]\n",IMX291_SETTING_SHORT[i],IMX291_SETTING_SHORT[i+1],
			//	regAddr,regValue);
			status = Iss_device16Write8(2, 0x1A, &regAddr, &regValue,1);
			if(status != FVID2_SOK){
				Vps_printf("DRV_IMX291SetRegs Error\n");
			}
	}
	Task_sleep(10);
	regAddr=0x3001;regValue=0x00;
	status = Iss_device16Write8(2, 0x1A, &regAddr, &regValue,1);

	Task_sleep(1000);
	regAddr=0x3000;regValue=0x00;
	status = Iss_device16Write8(2, 0x1A, &regAddr, &regValue,1);
	Task_sleep(100);
	regAddr=0x3002;regValue=0x00;
	status|= Iss_device16Write8(2, 0x1A, &regAddr, &regValue,1);
	Task_sleep(10);
	regAddr=0x304B;regValue=0x0A;
	status|= Iss_device16Write8(2, 0x1A, &regAddr, &regValue,1);
	Task_sleep(100);
	if(status != FVID2_SOK){
		Vps_printf("Error\n");
	}
	//DRV_imx291RegHoldClear();
	return 0;
}
void DRV_IMX291RegSet_NEW(UInt16 regaddr,UInt8 value)
{
	Iss_device16Write8(2, 0x1A, &regaddr,&value,1);
}

Int32 DRV_IMX291imgsSetAgain(Int32 again, Int32 setRegDirect)
{
	unsigned short SetIso, SetDb;
	if(again>6550)
		again=6550;
	SetIso=again;
	SetDb = 20*log10((float)SetIso/100);
	//SetDb = 0;
	Vps_rprintf("again=%d,setRegDirect=%d,SetDb=%d\n",again,setRegDirect,SetDb);
	DRV_IMX291RegSet_NEW(0x3014, SetDb*10/3);
	return 0;
}
Int32 DRV_IMX291imgsSetEshutter(Uint32 eshutterInUsec, Int32 setRegDirect)
{
	UInt32 tmpLine,tmpRegVal=0;
	Uint8 Send_HH,Send_H,Send_L;

	if(eshutterInUsec>40000)
		eshutterInUsec = 40000;
	//eshutterInUsec = 40000;
	tmpLine = eshutterInUsec*1125/40000;
	if(tmpLine > 1123) tmpLine=1123;
	if(tmpLine < 1)	tmpLine = 1;
	tmpRegVal = 1125-(tmpLine+1);
	Vps_rprintf("eshutterInUsec=%d,setRegDirect=%d,tmpRegVal=%d\n",eshutterInUsec,setRegDirect,tmpRegVal);
	Send_HH=(Uint8)(tmpRegVal>>16);
    Send_H =(Uint8)((tmpRegVal>>8)&0x00FF);
    Send_L =(Uint8)(tmpRegVal & 0x00FF);

	DRV_IMX291RegSet_NEW(0x3020, Send_L);
    DRV_IMX291RegSet_NEW(0x3021, Send_H);
    DRV_IMX291RegSet_NEW(0x3022, Send_HH);

	return 0;
}


