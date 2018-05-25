#include <stdio.h>
// #include <emscripten/emscripten.h>


#ifdef __cplusplus
extern "C" {
#endif

int export_main(char* name) {
	if(name != nullptr)
		printf("HelloWorld! (by %s)\n", name);
	else
		printf("HelloWorld!\n");
	return 0;
}

#ifdef __cplusplus
}
#endif
