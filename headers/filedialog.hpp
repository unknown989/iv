#if defined(__linux__) // any linux distribution
#define PLATFROM "linux"
#include <cstdio>
#include <cstdlib>
#include <cstring>
const char* openfilename(){

	const char* cmd = "/usr/bin/zenity --file-selection --title='iv - Select an Image' --file-filter='Photo files (jpg,png,jpeg,bmp) | *.jpg *.png *.jpeg *.bmp'";
	FILE* fp = popen(cmd,"r");
	
	char* buff = (char*)malloc(1024);
	if(!fp){
		exit(1);
	}
	fgets(buff,1024,fp);
	int size = strlen(buff);
	char* filename = (char*)malloc(size);
	if(size == 0){
		printf("No file was selected\n");
		exit(1);
	}
	filename = strncpy(filename,buff,size-1);
	pclose(fp);
	return filename;
	
}
#elif defined(_WIN32) || defined(WIN32) 

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <windows.h>
#include <iostream>
#include <commdlg.h>
#include <winuser.h>
#include <stdlib.h>
// Code taken from https://github.com/unknown989/WChanger/ another project of mine , check it out
const wchar_t *GetWC(const char *c)
{
    const size_t cSize = strlen(c)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs (wc, c, cSize);

    return wc;
}
bool openBox(LPCTSTR lpText,LPCTSTR lpCaption){
    return (MessageBox(NULL,lpText,lpCaption,MB_OK)) ? true: false;
}

const char* openfilename(){
	OPENFILENAME ofn = {0};
    TCHAR szFile[260]={0};
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter =  _T("*.JPEG*;*.JPG*;*.PNG*;*.BMP*");
    ofn.nFilterIndex = 0;
    ofn.lpstrTitle = GetWC("Choose an image file...");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if(!GetOpenFileName(&ofn)){
        openBox(GetWC("Failed to open the image"),GetWC("Failure"));exit(1);
    }
	char* sfe = (char*)malloc(260);
	wcstombs(sfe,szFile,260);
	
	return sfe;
    
}

#else
	printf("Platform is not recognized , if you have a mac OSX it is not supported YET!\n");
#endif
