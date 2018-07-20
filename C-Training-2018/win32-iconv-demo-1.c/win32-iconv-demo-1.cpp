// g++ -finput-charset=UTF-8 win32-iconv-demo-1.cpp -o win32-iconv-demo-1.exe


#include <stdio.h>
#include <windows.h>
#ifdef NULL
	#undef NULL
	#define NULL 0
#endif

//GBK编码转换到UTF8编码
int GBKToUTF8(unsigned char * lpGBKStr,unsigned char * lpUTF8Str,int nUTF8StrLen){
    wchar_t * lpUnicodeStr = NULL;
    int nRetLen = 0;

    if(!lpGBKStr)  //如果GBK字符串为NULL则出错退出
        return 0;

    nRetLen = ::MultiByteToWideChar(CP_ACP,0,(char *)lpGBKStr,-1,NULL,NULL);  //获取转换到Unicode编码后所需要的字符空间长度
    lpUnicodeStr = new WCHAR[nRetLen + 1];  //为Unicode字符串空间
    nRetLen = ::MultiByteToWideChar(CP_ACP,0,(char *)lpGBKStr,-1,lpUnicodeStr,nRetLen);  //转换到Unicode编码
    if(!nRetLen)  //转换失败则出错退出
        return 0;

    nRetLen = ::WideCharToMultiByte(CP_UTF8,0,lpUnicodeStr,-1,NULL,0,NULL,NULL);  //获取转换到UTF8编码后所需要的字符空间长度
    
    if(!lpUTF8Str){  //输出缓冲区为空则返回转换后需要的空间大小
        if(lpUnicodeStr)
            delete []lpUnicodeStr;
        return nRetLen;
    }
    
    if(nUTF8StrLen < nRetLen){  //如果输出缓冲区长度不够则退出
        if(lpUnicodeStr)
            delete []lpUnicodeStr;
        return 0;
    }

    nRetLen = ::WideCharToMultiByte(CP_UTF8,0,lpUnicodeStr,-1,(char *)lpUTF8Str,nUTF8StrLen,NULL,NULL);  //转换到UTF8编码
    
    if(lpUnicodeStr)
        delete []lpUnicodeStr;
    
    return nRetLen;
}

 //使用这两个函数的例子
int main(){
    char cGBKStr[] = "我是中国人!";
    char * lpGBKStr = NULL;
    char * lpUTF8Str = NULL;
    FILE * fp = NULL;
    int nRetLen = 0;

    nRetLen = GBKToUTF8((unsigned char *) cGBKStr,NULL,NULL);
    printf("转换后的字符串需要的空间长度为：%d ",nRetLen);
    lpUTF8Str = new char[nRetLen + 1];
    nRetLen = GBKToUTF8((unsigned char *)cGBKStr,(unsigned char *)lpUTF8Str,nRetLen);
    if(nRetLen){
        printf("GBKToUTF8转换成功！");
    }else{
        printf("GBKToUTF8转换失败！");
        goto Ret0;
    }
    fp = fopen("C:\\GBKtoUTF8.txt","wb");  //保存到文本文件
    fwrite(lpUTF8Str,nRetLen,1,fp);
    fclose(fp);
    getchar();  //先去打开那个文本文件看看，单击记事本的“文件”-“另存为”菜单，在对话框中看到编码框变为了“UTF-8”说明转换成功了
   
    Ret0:
    
    {
        if(lpGBKStr)
            delete []lpGBKStr;
        if(lpUTF8Str)
            delete []lpUTF8Str; 
    }
    return 0;
}