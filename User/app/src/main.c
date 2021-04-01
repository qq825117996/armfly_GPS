/*
*********************************************************************************************************
*
*	ģ������ : ������ģ�顣
*	�ļ����� : main.c
*	��    �� : V1.2
*	˵    �� : GPSģ������
*	�޸ļ�¼ :
*		�汾��  ����       ����    ˵��
*		v1.0    2015-08-30 armfly  �׷�
*	
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"			/* �ײ�Ӳ������ */

static void DispGPSStatus(void);

/* ʵ���人���� GPS����
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
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
int main(void)
{
	bsp_InitUart();
	
	while (1)
	{
			gps_pro();		/* ��ѯGPS�������ݣ����������ݣ���������ȫ�ֱ��� GPS_T g_tGPS; */
      DispGPSStatus();	/* ��ӡ������� */
	}
}

/*
*********************************************************************************************************
*	�� �� ��: DispGPSStatus
*	����˵��: ��ӡGPS���ݰ�������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DispGPSStatus(void)
{
	char buf[128];

	/* γ�� */
	if (g_tGPS.NS == 'S')
	{
		sprintf(buf, "��γ %02d��%02d.%04d'=%02d.%06d��", g_tGPS.WeiDu_Du,
			g_tGPS.WeiDu_Fen / 10000, g_tGPS.WeiDu_Fen % 10000,
			g_tGPS.WeiDu_Du, gps_FenToDu(g_tGPS.WeiDu_Fen));

		sprintf(&buf[strlen(buf)], "=%02d��%02d'%02d\"", g_tGPS.WeiDu_Du,
			g_tGPS.WeiDu_Fen / 10000, gps_FenToMiao(g_tGPS.WeiDu_Fen));
	}
	else
	{
		sprintf(buf, "��γ %02d��%02d.%04d'=%02d.%06d��", g_tGPS.WeiDu_Du,
			g_tGPS.WeiDu_Fen / 10000, g_tGPS.WeiDu_Fen % 10000,
			g_tGPS.WeiDu_Du, gps_FenToDu(g_tGPS.WeiDu_Fen));

		sprintf(&buf[strlen(buf)], "=%02d��%02d'%02d\"", g_tGPS.WeiDu_Du,
			g_tGPS.WeiDu_Fen / 10000, gps_FenToMiao(g_tGPS.WeiDu_Fen));
	}
	printf(buf);

	/* ���� */
	if (g_tGPS.EW == 'E')
	{
		sprintf(buf, "  ���� %03d��%02d.%04d'=%03d.%06d��", g_tGPS.JingDu_Du,
			g_tGPS.JingDu_Fen / 10000, g_tGPS.JingDu_Fen % 10000,
			g_tGPS.JingDu_Du, gps_FenToDu(g_tGPS.JingDu_Fen));

		sprintf(&buf[strlen(buf)], "=%03d��%02d'%02d\"", g_tGPS.JingDu_Du,
			g_tGPS.WeiDu_Fen / 10000, gps_FenToMiao(g_tGPS.JingDu_Fen));
	}
	else
	{
		sprintf(buf, "  ���� %03d��%02d.%04d'=%03d.%06d��", g_tGPS.JingDu_Du,
			g_tGPS.JingDu_Fen / 10000, g_tGPS.JingDu_Fen % 10000,
			g_tGPS.JingDu_Du, gps_FenToDu(g_tGPS.JingDu_Fen));

		sprintf(&buf[strlen(buf)], "=%03d��%02d'%02d\"", g_tGPS.JingDu_Du,
			g_tGPS.JingDu_Fen / 10000, gps_FenToMiao(g_tGPS.JingDu_Fen));
	}
	printf(buf);

	/* �ٶ� */
	sprintf(buf, "  �ٶ� = %5d.%d KM/h", g_tGPS.SpeedKM / 10, g_tGPS.SpeedKM % 10);
	printf(buf);

	/* ���� */
	sprintf(buf, "  ���� = %5d.%d M", g_tGPS.Altitude / 1000, g_tGPS.Altitude % 1000);
	printf(buf);

	printf("\r");	/* �س��������� */
}


/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
