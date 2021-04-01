/*
*********************************************************************************************************
*
*	模块名称 : 主程序模块。
*	文件名称 : main.c
*	版    本 : V1.2
*	说    明 : GPS模块例程
*	修改记录 :
*		版本号  日期       作者    说明
*		v1.0    2015-08-30 armfly  首发
*	
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"			/* 底层硬件驱动 */

static void DispGPSStatus(void);

/* 实测武汉地区 GPS数据
$GNGGA,064518.046,,,,,0,00,,,M,0.0,M,,0000*5A
$GPGLL,,,,,064518.046,V,N*76
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GPGSV,3,1,12,18,56,351,,22,51,026,,14,51,206,21,19,48,285,*78
$GPGSV,3,2,12,26,38,041,,24,37,323,,03,37,281,,09,31,097,*78
$GPGSV,3,3,12,21,17,122,,25,13,176,,31,13,054,,20,00,266,*7A
$GPRMC,064518.046,V,,,,,,,250213,,,N*46
$GPVTG,,T,,M,,N,,K,N*2C
*/

/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
	bsp_InitUart();
	
	while (1)
	{
			gps_pro();		/* 轮询GPS串口数据，并解析数据，结果存放在全局变量 GPS_T g_tGPS; */
      DispGPSStatus();	/* 打印解析结果 */
	}
}

/*
*********************************************************************************************************
*	函 数 名: DispGPSStatus
*	功能说明: 打印GPS数据包解码结果
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void DispGPSStatus(void)
{
	char buf[128];

	/* 纬度 */
	if (g_tGPS.NS == 'S')
	{
		sprintf(buf, "南纬 %02d°%02d.%04d'=%02d.%06d°", g_tGPS.WeiDu_Du,
			g_tGPS.WeiDu_Fen / 10000, g_tGPS.WeiDu_Fen % 10000,
			g_tGPS.WeiDu_Du, gps_FenToDu(g_tGPS.WeiDu_Fen));

		sprintf(&buf[strlen(buf)], "=%02d°%02d'%02d\"", g_tGPS.WeiDu_Du,
			g_tGPS.WeiDu_Fen / 10000, gps_FenToMiao(g_tGPS.WeiDu_Fen));
	}
	else
	{
		sprintf(buf, "北纬 %02d°%02d.%04d'=%02d.%06d°", g_tGPS.WeiDu_Du,
			g_tGPS.WeiDu_Fen / 10000, g_tGPS.WeiDu_Fen % 10000,
			g_tGPS.WeiDu_Du, gps_FenToDu(g_tGPS.WeiDu_Fen));

		sprintf(&buf[strlen(buf)], "=%02d°%02d'%02d\"", g_tGPS.WeiDu_Du,
			g_tGPS.WeiDu_Fen / 10000, gps_FenToMiao(g_tGPS.WeiDu_Fen));
	}
	printf(buf);

	/* 经度 */
	if (g_tGPS.EW == 'E')
	{
		sprintf(buf, "  东经 %03d°%02d.%04d'=%03d.%06d°", g_tGPS.JingDu_Du,
			g_tGPS.JingDu_Fen / 10000, g_tGPS.JingDu_Fen % 10000,
			g_tGPS.JingDu_Du, gps_FenToDu(g_tGPS.JingDu_Fen));

		sprintf(&buf[strlen(buf)], "=%03d°%02d'%02d\"", g_tGPS.JingDu_Du,
			g_tGPS.WeiDu_Fen / 10000, gps_FenToMiao(g_tGPS.JingDu_Fen));
	}
	else
	{
		sprintf(buf, "  西经 %03d°%02d.%04d'=%03d.%06d°", g_tGPS.JingDu_Du,
			g_tGPS.JingDu_Fen / 10000, g_tGPS.JingDu_Fen % 10000,
			g_tGPS.JingDu_Du, gps_FenToDu(g_tGPS.JingDu_Fen));

		sprintf(&buf[strlen(buf)], "=%03d°%02d'%02d\"", g_tGPS.JingDu_Du,
			g_tGPS.JingDu_Fen / 10000, gps_FenToMiao(g_tGPS.JingDu_Fen));
	}
	printf(buf);

	/* 速度 */
	sprintf(buf, "  速度 = %5d.%d KM/h", g_tGPS.SpeedKM / 10, g_tGPS.SpeedKM % 10);
	printf(buf);

	/* 海拔 */
	sprintf(buf, "  海拔 = %5d.%d M", g_tGPS.Altitude / 1000, g_tGPS.Altitude % 1000);
	printf(buf);

	printf("\r");	/* 回车，不换行 */
}


/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
