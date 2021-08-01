#include <iostream>
#include "filedialog.hpp"

#if defined(__linux__)
int main(void*){
#elif defined(_WIN32)
int WinMain(void*){
#endif
	const char* filename = openfilename();

	std::cout << filename << std::endl;
	return 0;
}
