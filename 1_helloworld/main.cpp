#include <include/apps.h> //MAIN函数需要此头文件
#include <include/stdio.h> //使用printf函数需要此头文件

//控制台程序主入口，这里先无视后面的参数，直接使用
int MAIN( int nType, int nParam0, int nParam1, int nParam2, int nParam3, int nParam4, int nParam5, int nParam6, int nParam7, int nParam8, int nParam9 ){
	
	switch( nType ){
		case EVMCT_Init:   
		//在此处执行printf函数输出字符串
		printf("Hello World!!!!"); 
    }
    return 0;
}



