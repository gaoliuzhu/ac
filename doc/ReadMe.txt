һ �����뻷����
windows��VS2017�� 64λ;
linux��cenos7.0;
android��ios��armƽ̨Ҳ��֧�֣����β���˵��;

����֧��g711u��g711a��g729��g722��opus����Ƶ����룬�ӿڵ��ü򵥣����д�����������Ƶ�ı���빤����
����demo û����opus�����ʾ����ʾ�����ǽ��빦�ܿ��ã�

�������Է�����
1.windows���Է�����
����cmd���л���output/winĿ¼�£�ִ��
			./audioproject.exe     0 0 input_8k.pcm  output_8k		//g711 test
					 1 0 output_8k  output_8k.pcm 

					 0 2 input_8k.pcm  output_8k		//g729 test
					 1 2 output_8k  output_8k.pcm  

					 0 3 input_16k.pcm  output_16k	//g722 test
					 1 3 output_16k  output_16k.pcm 

					 0 4 input_16k.pcm  output_16k	//opus test
���򼴿�;


2.linux���Է�����
ֱ���ڸ�Ŀ¼��make clean;make all����������ִ���ļ�������ֱ��ʹ��output/linux/audioproject.exe����Ҳ���ԣ�����ͬwindows��

������ϵ��ʽ��

΢�ţ�unique_no_1
