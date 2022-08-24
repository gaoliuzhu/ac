一 、编译环境：
windows：VS2017， 64位;
linux：cenos7.0;
android、ios、arm平台也可支持，本次不做说明;

可以支持g711u，g711a，g729，g722，opus等音频编解码，接口调用简单，几行代码解决所有音频的编解码工作；
测试demo 没有做opus解码的示例演示，但是解码功能可用；

二、测试方法：
1.windows测试方法：
运行cmd，切换到output/win目录下，执行
			./audioproject.exe     0 0 input_8k.pcm  output_8k		//g711 test
					 1 0 output_8k  output_8k.pcm 

					 0 2 input_8k.pcm  output_8k		//g729 test
					 1 2 output_8k  output_8k.pcm  

					 0 3 input_16k.pcm  output_16k	//g722 test
					 1 3 output_16k  output_16k.pcm 

					 0 4 input_16k.pcm  output_16k	//opus test
程序即可;


2.linux测试方法：
直接在根目录下make clean;make all即可生产可执行文件，或者直接使用output/linux/audioproject.exe测试也可以，方法同window
