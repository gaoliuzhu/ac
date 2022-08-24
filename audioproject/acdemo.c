#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <stdint.h>


#include "../api/audioapi.h"

//---------------------------------------------------------------------------------------------------
/*
input reference:
	1、codecid, 0:encode, 1:decode;
	2、codec, 0:g711a, 1:g711u, 2:g729, 3:g722, 4:opus;
	3、input audio file name;
	4、output audio file name; 

usage exampel:
	audioproject.exe 0 0 input_8k.pcm  output_8k
					 1 0 output_8k  output_8k.pcm 

					 0 2 input_8k.pcm  output_8k
					 1 2 output_8k  output_8k.pcm  

					 0 3 input_16k.pcm  output_16k
					 1 3 output_16k  output_16k.pcm 

					 0 4 input_16k.pcm  output_16k
					 
*/		
//---------------------------------------------------------------------------------------------------
#define DEFAULT_SAMPLE_FRAME_LEN 640

int main(int argc, char* argv[])
{
	uint8_t 	*pcSrcBuf = NULL;
	uint8_t 	*pcDstBuf = NULL;
	FILE		*pfInput_fd = NULL;
	FILE		*pfOutput_fd = NULL;

	int iInFrameLen = 320, iOutFrameLen = 320;
	int iCodecId = 2, iCodecType = 0,  iRet = 0;

	if(argc < 5)
	{
		printf("Error:argc=%d\n",argc);

		return -1;
	};

	iCodecType = atoi(argv[1]);
	if (iCodecType < 0)
	{
		iCodecType = 0;
	}

	iCodecId = atoi(argv[2]);
	if (iCodecId <= 0)
	{
		iCodecId = 0;
	}
	
	pfInput_fd = fopen(argv[3], "rb");
	if(pfInput_fd == NULL)
	{
		printf("Error:can not open audio input file %s.\n", argv[2]);
		return (-1);
	};

	pfOutput_fd = fopen(argv[4], "wb");
	if(pfOutput_fd == NULL)
	{
		printf("Error:can not create audio output file %s.\n",argv[3]);
		return (-1);
	};

	pcSrcBuf = (uint8_t*)malloc(sizeof(uint8_t)*DEFAULT_SAMPLE_FRAME_LEN);
	if(pcSrcBuf == NULL)
	{
		printf("Error\n");
		return (-1);
	}	
	pcDstBuf = (uint8_t*)malloc(sizeof(uint8_t)*DEFAULT_SAMPLE_FRAME_LEN);
	if (pcDstBuf == NULL)
	{
		printf("Error\n");
		return (-1);
	}

	stAudioContext *pstContext = NULL;
	pstContext = (stAudioContext *)malloc(sizeof(stAudioContext));
	if (pstContext == NULL)
	{
		return -1;
	}
	pstContext->iCodecType = iCodecType;//0:encode, 1:decode;
	pstContext->iCodecId = iCodecId;
	pstContext->iSampleRate = 8000;
	pstContext->iChannel = 1;
	pstContext->iDecMode = 0;

	switch (pstContext->iCodecType)
	{
	case 0://encode
		if (iCodecId == CODEC_ID_G729)
		{
			iInFrameLen = 320;
			iOutFrameLen = 20;
		}
		else if (iCodecId == CODEC_ID_ALAW || iCodecId == CODEC_ID_ULAW)
		{
			iInFrameLen = 320;
			iOutFrameLen = 160;
		}
		else if (iCodecId == CODEC_ID_G722)
		{
			iInFrameLen = 640;
			iOutFrameLen = 160;
			pstContext->iSampleRate = 16000;
		}
		else if (iCodecId == CODEC_ID_OPUS)
		{
			iInFrameLen = 640;
			iOutFrameLen = 160;
			pstContext->iSampleRate = 16000;
		}
		break;
	case 1://decode
		if (iCodecId == CODEC_ID_G729)
		{
			iInFrameLen = 20;
			iOutFrameLen = 320;
		}
		else if (iCodecId == CODEC_ID_ALAW || iCodecId == CODEC_ID_ULAW)
		{
			iInFrameLen = 160;
			iOutFrameLen = 320;
		}
		else if (iCodecId == CODEC_ID_G722)
		{
			pstContext->iSampleRate = 16000;

			iInFrameLen = 160;
			iOutFrameLen = 640;
		}
		else if (iCodecId == CODEC_ID_OPUS)
		{
			pstContext->iSampleRate = 16000;
			return -1;
		}
		break;
	default:
		break;
	}

	//---------------------------------codec process-----------------------------------------------------------------------
	uniqueAudioInit(pstContext);

	while (!feof(pfInput_fd))
	{
		if((iRet = fread(pcSrcBuf, sizeof(uint8_t), iInFrameLen, pfInput_fd))!= iInFrameLen)
		{
			printf("while Exit.file over.\n ");	
			break;
		}
		
		if (pstContext->iCodecType == 0)
		{
			iRet = uniqueAudioEncode(pstContext, (char*)pcSrcBuf, iInFrameLen, (char*)pcDstBuf, iOutFrameLen);
		}
		else
		{
			iRet = uniqueAudioDecode(pstContext, (char*)pcSrcBuf, iInFrameLen, (char*)pcDstBuf, iOutFrameLen);
		}

		if (iRet > 0)
		{
			fwrite(pcDstBuf, sizeof(uint8_t), iRet, pfOutput_fd);
			fflush(stdout);
		}

		printf("audio frame len %d\n", iRet);
	}

	fclose(pfInput_fd);
	fclose(pfOutput_fd);

	uniqueAudioDestroy(pstContext);
	free(pstContext);

	if (pcSrcBuf)
	{
		free(pcSrcBuf);
	}

	if (pcDstBuf)
	{
		free(pcDstBuf);
	}

	getchar();

	return 0;
}
