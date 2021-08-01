#include <string>
#include <stdio.h>
#if defined(__linux__) // any linux distribution
#define PLATFROM "linux"

#include <stdlib.h>
std::string openfilename(){
	std::string filename;
	char* fn = (char*)malloc(1025);
	FILE *f = popen("zenity --file-selection --file-filter='Photo files (jpg,png,jpeg) | *.jpg *.png *.jpeg'", "r");
	fgets(fn, 1024, f);
	filename.assign(fn,1024);

	return filename;
}
#elif defined(_WIN32) // any windows system
#define PLATFROM "win"
#include <windows.h>
const char* openfilename(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";
  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = owner;
  ofn.lpstrFilter = filter;
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  ofn.lpstrDefExt = "";

  string fileNameStr;

  if ( GetOpenFileName(&ofn) )
    fileNameStr = fileName;

  return fileNameStr.c_str();
}


#else
#define PLATFROM "na"
	printf("Platform is not recognized , neither linux nor windows . if you have a mac OSX it is not supported")
#endif
