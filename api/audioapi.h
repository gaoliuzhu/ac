/**
  ******************************************************************************
  * @author			unique
  * @vx				unique_no_1
  *
  * @date			2021-10-29
  * @description    This is a Audio codec program，including G711u/a, G729，G722, OPUS etc.
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
	int 		iCodecId;				//取值enCodecId

	//codec parameter
	int 		iSampleRate;			//采样率:8000, 16000, 48000
	int			iChannel;				//1:SINGLE,		2:STEREO	
	int			iDecMode;				//0:正常解码,		1:恢复数据，	注意：仅在OPUS编码时有效 
		
	void		*pvAudioHandle;
}stAudioContext;


/************************************************************************************
Description:  	初始化音频编解码器句柄；
parameters:
				1.pstAContext：	输入，		音频编解码器上下文，空间由外面申请、释放，参数由上层应用设置；

Return:  		0:成功，-1:失败；
************************************************************************************/
int		uniqueAudioInit(stAudioContext *pstAContext);

/************************************************************************************
Description:  	释放音频编解码器句柄；
parameters:
				1.pstAContext：	输入，		音频编解码器上下文，空间由外面申请、释放；

Return:  		0:成功，-1:失败；
************************************************************************************/
int		uniqueAudioDestroy(stAudioContext *pstAContext);

/************************************************************************************
Description:  	音频编码器；
parameters:
				1.pstAContext：	输入，		音频编解码器上下文，为初始化的句柄；
				2.pcSrcData：	输入，		原始数据的指针；20ms数据
				3.iSrcLen：		输入，		原始数据长度； 8k采样率为320字节，16k采样率为640字节
				4.pcDestData：	输入，		编码后数据的指针，空间由外面分配；
				5.iDestLen：		输入，		输入的存储编码空间的内存大小；

Return:  		成功：返回编码后的字节数, 失败：返回-1
************************************************************************************/
int		uniqueAudioEncode(stAudioContext *pstAContext, char *pcSrcData, int iSrcLen, char *pcDestData, int iDestLen);

/************************************************************************************
Description:  	音频解码器；
parameters:
				1.pstAContext：	输入，		音频编解码器上下文，为初始化的句柄；
				2.pcSrcData：	输入，		编码数据的指针；
				3.iSrcLen：		输入，		编码数据长度；
				4.pcDestData：	输入，		解码后数据的指针，空间由外面分配；
				5.iDestLen：		输入，		输入的存储解码空间的内存大小；

Return:  		成功：返回解码后的字节数, 失败：返回-1
************************************************************************************/
int		uniqueAudioDecode(stAudioContext *pstAContext, char *pcSrcData, int iSrcLen, char *pcDestData, int iDestLen);




#ifdef __cplusplus
}
#endif 



#endif //_AUDIO_CORE_H_


