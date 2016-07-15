
#ifndef __ALG2A_DEV_H__
#define __ALG2A_DEV_H__


#ifdef __cplusplus
extern "C" {
#endif

/*  */
typedef struct tagStPgApiEwfiPrerunParam
{
  unsigned char ucSensrChipId;
  unsigned char ucAewbVendor;
  unsigned char ucSensrEnable;
  unsigned char ucSensrFovMod;
  unsigned char ucSensrBinMod;
  unsigned char ucSensrFovFps;
  unsigned char ucSysPowerHzMod;
}StPgApiEwfiPrerunParam;

/*  */
typedef struct tagStPgApiEwfiCreateParam
{
	unsigned short usAlgId;
	unsigned short usSensrFovMode;
	unsigned short usSensrFovFps;
	unsigned short usVnfDemoCfg;
	unsigned short usAewbType;
	unsigned short usAewbVendor;
	unsigned short usAewbPriority;
	unsigned short usBinMode;
	unsigned short usReduceShutter;
	unsigned short usFlickerType;
	unsigned short usShiftValue;
	unsigned short usSaldre;
}StPgApiEwfiCreateParam;

/*  */
typedef struct tagStPgApiEwfiRunParam
{
	void *pvHaewBuffAddr;
	unsigned short usVnfDemoCfg;
	unsigned short usAewbType;
	unsigned short usAewbVendor;
	unsigned short usAewbPriority;
	unsigned short usReduceShutter;
	unsigned short usSaldre;
	unsigned short usSensorMode;
}StPgApiEwfiRunParam;


/* PreInit  */
int SnAewb_AewbPrerun(void *rpvSensrInitParam);
int SnAewb_PreInitHaew(int sensorMode, void *rpvH3aAewCfg, int *rpsiAewBufSize);

/* Run */
void *SnAewb_AewbCreate(void *rpvSnEwfiCreateParam);
int SnAewb_AewbRun(void *hndl, void *rpvSnEwfiRunParam,int snapShotFlag,int flashPort);
int SnAewb_AewbDelete(void *hndl);


/*########################################
   快门模式
    ShutrCtrlMod_Auto = 0,
    ShutrCtrlMod_Manu,
  #########################################*/
unsigned char SnAewb_UiGetShutrCtrlMode(void);
int SnAewb_UiSetShutrCtrlMode(unsigned char rucShutrCtrlMode);
/* 自动快门模式最大,最小曝光时间 us 例40000 是40ms */
int	SnAewb_UiSetMaxShutr4Auto(int rsiMaxShutr4Auto);
int SnAewb_UiGetMaxShutr4Auto(void);
int	SnAewb_UiSetMinShutr4Auto(int rsiMinShutr4Auto);
int SnAewb_UiGetMinShutr4Auto(void);
/*固定快门时间 单位 us 例40000 是40ms*/
int	SnAewb_UiSetFixShutr4Manu(int rsiFixShutr4Manu);
int	SnAewb_UiGetFixShutr4Manu(void);


/*#################################################
    增益模式
     GainCtrlMod_Auto = 0,
	 GainCtrlMod_Manu,
  #################################################	*/
unsigned char SnAewb_UiGetGainCtrlMode(void);
int SnAewb_UiSetGainCtrlMode(unsigned char rucGainCtrlMode);
/* 自动增益下最大 ISO 0-100 default 50*/
signed long SnAewb_UiGetMaxGain4Auto(void);
int SnAewb_UiSetMaxGain4Auto(signed long rslMaxGain4Auto);
/*固定增益 ISO 0-100 在default 50*/
signed long SnAewb_UiGetFixGain4Manu(void);
int SnAewb_UiSetFixGain4Manu(signed long rslFixGain4Manu);


/*锐度调节 	Default 50, 0-100可调*/
int SnAewb_UiGetSharpness(void);
int SnAewb_UiSetSharpness(int nSharpness);

/*亮度调节 	Default 50, 0-100可调*/
int SnAewb_UiGetBrtness(void);
int SnAewb_UiSetBrtness(int rsiBrtness);


/*色饱和度 	Default 50, 0-100 可调*/
int SnAewb_UiSetSatDgr(int rsiSatDgr);
int SnAewb_UiGetSatDgr(void);

/*对比度	Default 50, 0-100 可调*/
int SnAewb_UiSetContrast(int rsiContrast);
int SnAewb_UiGetContrast(void);

/*
AE 50/60hz 选择
   50Hz = 0,
   60Hz = 1,
*/
int SnAewb_UiSetVideoSystem(int pVideoSystem);
int SnAewb_UiGetVideoSystem(void);

/*日夜模式*/
/* 0==Day; 1==Night;  */
int SnAewb_UiSetDayNightStat(int rsiDayNightStat);
int SnAewb_UiGetDayNightStat(void);
/*夜晚模式色彩*/
/* 0==Color; 1==BlackWhite;  */
int SnAewb_UiSetNightColorMode(int rsiNightColorMode);
int SnAewb_UiGetNightColorMode(void);

/*背光补偿 选择 0: defalut 1:High 2:Mid 3:Low*/
int SnAewb_UiSetHlcCtrl(int rsiHlcCtrl);
int SnAewb_UiGetHlcCtrl(void);

/*白平衡模式*/
/*
eWbCtrlMode_Auto = 0,
eWbCtrlMode_Manu,
eWbCtrlMode_Auto_wide,
eWbCtrlMode_Sunny,
eWbCtrlMode_Shadow,
eWbCtrlMode_Indoor,
eWbCtrlMode_Lamp,
eWbCtrlMode_PL1,
eWbCtrlMode_PL2,
*/
int SnAewb_UiSetWbCtrlMode(int rsiWbCtrlMode);
int SnAewb_UiGetWbCtrlMode(void);

#ifdef __cplusplus
}
#endif

#endif
