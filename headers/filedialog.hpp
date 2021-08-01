#if defined(__linux__) // any linux distribution
#define PLATFROM "linux"
#include <cstdio>
#include <cstdlib>
#include <cstring>
const char* openfilename(){
	const char* cmd = "/usr/bin/zenity --file-selection --file-filter='Photo files (jpg,png,jpeg) | *.jpg *.png *.jpeg' > /tmp/iv_filename";
	system(cmd);
	FILE* fp = fopen("/tmp/iv_filename","r");
	char* buff = (char*)malloc(1024);
	fgets(buff,1024,fp);
	int size = strlen(buff);

	char* filename = (char*)malloc(size);
	filename = strncpy(filename,buff,size-1);
	// printf("%s\n %i",buff,(int)size);
	return filename;
}

#else
	printf("Platform is not recognized , if you have a mac OSX or Windows they are not supported YET!\n");
#endif
