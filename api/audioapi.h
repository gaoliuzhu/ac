/**
  ******************************************************************************
  * @author			unique
  * @vx				unique_no_1
  *
  * @date			2021-10-29
  * @description    This is a Audio codec program��including G711u/a, G729��G722, OPUS etc.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef  _AUDIO_CORE_H_
#define  _AUDIO_CORE_H_

#ifdef __cplusplus
extern "C" {
#endif 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum   _enCodecId_
{
	CODEC_ID_ALAW,
	CODEC_ID_ULAW,
	CODEC_ID_G729,
	CODEC_ID_G722,
	CODEC_ID_OPUS,
}enCodecId;

typedef struct _AudioContext_{
	//context parameter
	int			iCodecType;				//0:encode,		1:decode
	int 		iCodecId;				//ȡֵenCodecId

	//codec parameter
	int 		iSampleRate;			//������:8000, 16000, 48000
	int			iChannel;				//1:SINGLE,		2:STEREO	
	int			iDecMode;				//0:��������,		1:�ָ����ݣ�	ע�⣺����OPUS����ʱ��Ч 
		
	void		*pvAudioHandle;
}stAudioContext;


/************************************************************************************
Description:  	��ʼ����Ƶ������������
parameters:
				1.pstAContext��	���룬		��Ƶ������������ģ��ռ����������롢�ͷţ��������ϲ�Ӧ�����ã�

Return:  		0:�ɹ���-1:ʧ�ܣ�
************************************************************************************/
int		uniqueAudioInit(stAudioContext *pstAContext);

/************************************************************************************
Description:  	�ͷ���Ƶ������������
parameters:
				1.pstAContext��	���룬		��Ƶ������������ģ��ռ����������롢�ͷţ�

Return:  		0:�ɹ���-1:ʧ�ܣ�
************************************************************************************/
int		uniqueAudioDestroy(stAudioContext *pstAContext);

/************************************************************************************
Description:  	��Ƶ��������
parameters:
				1.pstAContext��	���룬		��Ƶ������������ģ�Ϊ��ʼ���ľ����
				2.pcSrcData��	���룬		ԭʼ���ݵ�ָ�룻20ms����
				3.iSrcLen��		���룬		ԭʼ���ݳ��ȣ� 8k������Ϊ320�ֽڣ�16k������Ϊ640�ֽ�
				4.pcDestData��	���룬		��������ݵ�ָ�룬�ռ���������䣻
				5.iDestLen��		���룬		����Ĵ洢����ռ���ڴ��С��

Return:  		�ɹ������ر������ֽ���, ʧ�ܣ�����-1
************************************************************************************/
int		uniqueAudioEncode(stAudioContext *pstAContext, char *pcSrcData, int iSrcLen, char *pcDestData, int iDestLen);

/************************************************************************************
Description:  	��Ƶ��������
parameters:
				1.pstAContext��	���룬		��Ƶ������������ģ�Ϊ��ʼ���ľ����
				2.pcSrcData��	���룬		�������ݵ�ָ�룻
				3.iSrcLen��		���룬		�������ݳ��ȣ�
				4.pcDestData��	���룬		��������ݵ�ָ�룬�ռ���������䣻
				5.iDestLen��		���룬		����Ĵ洢����ռ���ڴ��С��

Return:  		�ɹ������ؽ������ֽ���, ʧ�ܣ�����-1
************************************************************************************/
int		uniqueAudioDecode(stAudioContext *pstAContext, char *pcSrcData, int iSrcLen, char *pcDestData, int iDestLen);




#ifdef __cplusplus
}
#endif 



#endif //_AUDIO_CORE_H_


