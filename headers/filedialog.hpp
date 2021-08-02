#if defined(__linux__) // any linux distribution
#define PLATFROM "linux"
#include <cstdio>
#include <cstdlib>
#include <cstring>
const char* openfilename(){

	const char* cmd = "/usr/bin/zenity --file-selection --title='iv - Select an Image' --file-filter='Photo files (jpg,png,jpeg) | *.jpg *.png *.jpeg'";
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

#else
	printf("Platform is not recognized , if you have a mac OSX or Windows they are not supported YET!\n");
#endif
