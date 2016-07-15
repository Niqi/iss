/** ==================================================================
 *  @file   issdrv_deviceI2c.c                                                  
 *                                                                    
 *  @path   /ti/psp/devices/src/                                                  
 *                                                                    
 *  @desc   This  File contains.                                      
 * ===================================================================
 *  Copyright (c) Texas Instruments Inc 2011, 2012                    
 *                                                                    
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * ===================================================================*/

#include <ti/psp/devices/src/vpsdrv_devicePriv.h>
#include "issdrv_devicePriv.h"

Int32 Iss_deviceRead16(UInt32 instId, UInt32 devAddr,
                       const UInt16 * regAddr,
                       UInt16 * regValue, UInt32 numRegs)
{
    Int32 status;

    UInt32 regId;

    PSP_I2cXferParams i2cParams;

    UInt16 tempBuf;

    UInt8 buffer[2];

    UInt8 tempBuf1, tempBuf2;

    if (regAddr == NULL || regValue == NULL || numRegs == 0)
    {
        if (gVps_deviceObj.i2cDebugEnable)
        {
            Vps_printf(" I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                       instId, devAddr);
        }
        return FVID2_EFAIL;
    }

    status = Iss_deviceI2cLock(instId, TRUE);

    if (status == FVID2_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.bufLen = 2;
        i2cParams.timeout = ISS_DEVICE_I2C_TIMEOUT;
        i2cParams.buffer = buffer;
        for (regId = 0; regId < numRegs; regId++)
        {
            tempBuf1 = (regAddr[regId]);
            tempBuf2 = ((regAddr[regId]) >> 8);
            buffer[0] = tempBuf2;
            buffer[1] = tempBuf1;
            i2cParams.flags = (I2C_WRITE | I2C_MASTER | I2C_START   /* |
                                                                     * I2C_STOP 
                                                                     */ );
            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);

            if (status != FVID2_SOK)
            {
                if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\n",
                               instId, devAddr, regAddr[regId]);
                }
                break;
            }
            tempBuf1 = (regValue[regId]);
            tempBuf2 = ((regValue[regId]) >> 8);
            buffer[0] = tempBuf2;
            buffer[1] = tempBuf1;
            // i2cParams.buffer = &regValue[regId];
            i2cParams.flags
                =
                (I2C_READ | I2C_MASTER | I2C_START | I2C_STOP |
                 I2C_IGNORE_BUS_BUSY);

            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);

            if (status != FVID2_SOK)
            {
                if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\n",
                               instId, devAddr, regAddr[regId]);
                }
                break;
            }

            tempBuf = buffer[0];
            regValue[regId] =
                ((buffer[1]) & 0x00FF) | ((tempBuf << 8) & 0xFF00);

            if (gVps_deviceObj.i2cDebugEnable)
            {
                Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x = 0x%02x \n",
                           instId, devAddr, regAddr[regId], regValue[regId]);
            }

        }

        Iss_deviceI2cLock(instId, FALSE);
    }

    return status;
}

Int32 Iss_deviceWrite16(UInt32 instId, UInt32 devAddr,
                        const UInt16 * regAddr,
                        const UInt16 * regValue, UInt32 numRegs)
{
    Int32 status;

    UInt32 regId;

    PSP_I2cXferParams i2cParams;

    UInt8 buffer[4];

    UInt8 tempBuf1, tempBuf2;

    if (regAddr == NULL || regValue == NULL || numRegs == 0)
    {
        if (gVps_deviceObj.i2cDebugEnable)
        {
            Vps_printf(" I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                       instId, devAddr);
        }
        return FVID2_EFAIL;
    }

    status = Iss_deviceI2cLock(instId, TRUE);

    if (status == FVID2_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.buffer = buffer;
        i2cParams.bufLen = 4;
        i2cParams.flags = I2C_DEFAULT_WRITE;
        i2cParams.timeout = ISS_DEVICE_I2C_TIMEOUT;

        for (regId = 0; regId < numRegs; regId++)
        {
            tempBuf1 = (regAddr[regId]);
            tempBuf2 = ((regAddr[regId]) >> 8);
            buffer[0] = tempBuf2;
            buffer[1] = tempBuf1;
            tempBuf1 = (regValue[regId]);
            tempBuf2 = ((regValue[regId]) >> 8);
            buffer[2] = tempBuf2;
            buffer[3] = tempBuf1;
            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);

            if (status != FVID2_SOK)
            {
                if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf
                        (" I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x ... ERROR !!! \n",
                         instId, devAddr, regAddr[regId], regValue[regId]);
                }
                break;
            }

            if (gVps_deviceObj.i2cDebugEnable)
            {
                Vps_printf(" I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x \n",
                           instId, devAddr, regAddr[regId], regValue[regId]);
            }
        }

        Iss_deviceI2cLock(instId, FALSE);
    }

    return status;
}

Int32 _Iss_deviceRead8(UInt32 instId, UInt32 devAddr,
                       const UInt16 * regAddr,
                       UInt16 * regValue, UInt32 numRegs)
{
    Int32 status;

    UInt32 regId;

    PSP_I2cXferParams i2cParams;

    

    UInt8 buffer[2];


    if (regAddr == NULL || regValue == NULL || numRegs == 0)
    {
        if (gVps_deviceObj.i2cDebugEnable)
        {
            Vps_printf(" I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                       instId, devAddr);
        }
        return FVID2_EFAIL;
    }

    status = Iss_deviceI2cLock(instId, TRUE);

    if (status == FVID2_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.bufLen = 1;
        i2cParams.timeout = ISS_DEVICE_I2C_TIMEOUT;
        i2cParams.buffer = buffer;
        for (regId = 0; regId < numRegs; regId++)
        {

            buffer[0] = (regAddr[regId]);
            
            i2cParams.flags = (I2C_WRITE | I2C_MASTER | I2C_START   /* |
                                                                     * I2C_STOP 
                                                                     */ );
            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);

            if (status != FVID2_SOK)
            {
                //if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\n",
                               instId, devAddr, regAddr[regId]);
                }
                break;
            }

            buffer[0] = (regValue[regId]);
            
            // i2cParams.buffer = &regValue[regId];
            i2cParams.flags
                =
                (I2C_READ | I2C_MASTER | I2C_START | I2C_STOP |
                 I2C_IGNORE_BUS_BUSY);

            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);

            if (status != FVID2_SOK)
            {
                //if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\n",
                               instId, devAddr, regAddr[regId]);
                }
                break;
            }

            
            regValue[regId] = buffer[0];;

            //if (gVps_deviceObj.i2cDebugEnable)
            {
                Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x = 0x%02x \n",
                           instId, devAddr, regAddr[regId], regValue[regId]);
            }

        }

        Iss_deviceI2cLock(instId, FALSE);
    }

    return status;
}

Int32 _Iss_deviceWrite8(UInt32 instId, UInt32 devAddr,
                        const UInt16 * regAddr,
                        const UInt16 * regValue, UInt32 numRegs)
{
    Int32 status;

    UInt32 regId;

    PSP_I2cXferParams i2cParams;

    UInt8 buffer[4];


    if (regAddr == NULL || regValue == NULL || numRegs == 0)
    {
        if (gVps_deviceObj.i2cDebugEnable)
        {
            Vps_printf(" I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                       instId, devAddr);
        }
        return FVID2_EFAIL;
    }

    status = Iss_deviceI2cLock(instId, TRUE);

    if (status == FVID2_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.buffer = buffer;
        i2cParams.bufLen = 2;
        i2cParams.flags = I2C_DEFAULT_WRITE;
        i2cParams.timeout = ISS_DEVICE_I2C_TIMEOUT;

        for (regId = 0; regId < numRegs; regId++)
        {

            buffer[0] = (regAddr[regId]);
            buffer[1] = (regValue[regId]);
            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);

            if (status != FVID2_SOK)
            {
                if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf
                        (" I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x ... ERROR !!! \n",
                         instId, devAddr, regAddr[regId], regValue[regId]);
                }
                break;
            }

            if (gVps_deviceObj.i2cDebugEnable)
            {
                Vps_printf(" I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x \n",
                           instId, devAddr, regAddr[regId], regValue[regId]);
            }
        }

        Iss_deviceI2cLock(instId, FALSE);
    }

    return status;
}


/* Jerry add 2013-6-6*/

/*Jerry, 16位寄存器,8位的值*/
Int32 Iss_device16Read8(UInt32 instId, UInt32 devAddr,
                       const UInt16 * regAddr,
                       UInt8 * regValue, UInt32 numRegs)
{
    Int32 status;

    UInt32 regId;

    PSP_I2cXferParams i2cParams;

    UInt8 buffer[2];

    if (regAddr == NULL || regValue == NULL || numRegs == 0)
    {
        if (gVps_deviceObj.i2cDebugEnable)
        {
            Vps_printf(" I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                       instId, devAddr);
        }
        return FVID2_EFAIL;
    }

    status = Iss_deviceI2cLock(instId, TRUE);

    if (status == FVID2_SOK)
    {
        for (regId = 0; regId < numRegs; regId++)
        {
            i2cParams.slaveAddr = devAddr;
            i2cParams.bufLen = 2;
            i2cParams.timeout = ISS_DEVICE_I2C_TIMEOUT;
            i2cParams.flags = (I2C_WRITE | I2C_MASTER | I2C_START );
            i2cParams.buffer = buffer;
			
            buffer[0] = ((regAddr[regId]) >> 8)&0xff;
			buffer[1] = (regAddr[regId])&0xff;

            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);
            if (status != FVID2_SOK)
            {
                if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\n",
                               instId, devAddr, regAddr[regId]);
                }
                break;
            }
			
            i2cParams.slaveAddr = devAddr;
            i2cParams.bufLen = 1;
            i2cParams.timeout = ISS_DEVICE_I2C_TIMEOUT;
            i2cParams.flags = (I2C_READ | I2C_MASTER | I2C_START | I2C_STOP | I2C_IGNORE_BUS_BUSY);
            i2cParams.buffer = regValue;

            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);

            if (status != FVID2_SOK)
            {
                if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x ... ERROR !!!\n",
                               instId, devAddr, regAddr[regId]);
                }
                break;
            }

            if (gVps_deviceObj.i2cDebugEnable)
            {
                Vps_printf(" I2C%d: DEV 0x%02x: RD 0x%02x = 0x%02x \n",
                           instId, devAddr, regAddr[regId], regValue[regId]);
            }

        }

        Iss_deviceI2cLock(instId, FALSE);
    }

    return status;
}

Int32 Iss_device16Write8(UInt32 instId, UInt32 devAddr,
                        const UInt16 * regAddr,
                        const UInt8 * regValue, UInt32 numRegs)
{
    Int32 status;

    UInt32 regId;

    PSP_I2cXferParams i2cParams;

    UInt8 buffer[3];

    if (regAddr == NULL || regValue == NULL || numRegs == 0)
    {
        if (gVps_deviceObj.i2cDebugEnable)
        {
            Vps_printf(" I2C%d: DEV 0x%02x: Illegal Params ... ERROR !!!\n",
                       instId, devAddr);
        }
        return FVID2_EFAIL;
    }

    status = Iss_deviceI2cLock(instId, TRUE);

    if (status == FVID2_SOK)
    {
        i2cParams.slaveAddr = devAddr;
        i2cParams.buffer = buffer;
        i2cParams.bufLen = 3;
        i2cParams.flags = I2C_DEFAULT_WRITE;
        i2cParams.timeout = ISS_DEVICE_I2C_TIMEOUT;

        for (regId = 0; regId < numRegs; regId++)
        {
            buffer[0] = ((regAddr[regId])>>8)&0xff;        
            buffer[1] = (regAddr[regId])&0xff;
            buffer[2] = (regValue[regId])&0xff;
			
            status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],
                                     &i2cParams);

            if (status != FVID2_SOK)
            {
                if (gVps_deviceObj.i2cDebugEnable)
                {
                    Vps_printf
                        (" I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x ... ERROR !!! \n",
                         instId, devAddr, regAddr[regId], regValue[regId]);
                }
                break;
            }

            if (gVps_deviceObj.i2cDebugEnable)
            {
                Vps_printf(" I2C%d: DEV 0x%02x: WR 0x%02x = 0x%02x \n",
                           instId, devAddr, regAddr[regId], regValue[regId]);
            }
        }

        Iss_deviceI2cLock(instId, FALSE);
    }

    return status;
}
#if 0
Int32 Iss_deviceRead8BitWithSlave(UInt32 instId, Uint8 *readBuf,UInt8 *readLen)
{
#if 0
    Int32 status;
	UInt32 tmpLen = readLen;
    PSP_I2cXferParams i2cParams;
    if (readBuf == NULL || readLen == 0)
    {
        return FVID2_EFAIL;
    }

    status = Iss_deviceI2cLock(instId, TRUE);

    if (status == FVID2_SOK)
    {
    	i2cParams.slaveAddr = 0x00;
        i2cParams.bufLen 	= readLen;
        i2cParams.timeout 	= ISS_DEVICE_I2C_TIMEOUT;
        i2cParams.flags 	= (I2C_READ | I2C_SLAVE | I2C_IGNORE_BUS_BUSY);
        i2cParams.buffer 	= readBuf;
		status = PSP_i2cTransfer(gVps_deviceObj.i2cHndl[instId],&i2cParams);
		if (status != FVID2_SOK)
        {
            return FVID2_EFAIL;
        }        

        Iss_deviceI2cLock(instId, FALSE);
    }

    return (tmpLen - i2cParams.bufLen);
#else
	Int32 status;
	status = PSP_i2cWaitDataFrom(readBuf,readLen);
	return status;
#endif
}

Int32 Iss_deviceEnableInterrupt(UInt32 instId, UInt8 enable)
{
    Int32 status = FVID2_SOK;
    if (enable != 0 && enable != 1)
    {
        return FVID2_EFAIL;
    }
    status = Iss_deviceI2cLock(instId, TRUE);
	if (status == FVID2_SOK)
    {
		status = PSP_i2cEnableInterrupt(gVps_deviceObj.i2cHndl[instId],enable);
		Iss_deviceI2cLock(instId, FALSE);
	}
    return status;
}
#endif


/* add end*/

