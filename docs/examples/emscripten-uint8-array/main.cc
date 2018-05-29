#include <stdio.h>
#include <memory.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

class BufferArea {
	char* buffer;
public:
	BufferArea(size_t size) { buffer = (char*) malloc(size);}
	~BufferArea() { if(buffer) free(buffer); buffer= nullptr;}
	char* getPtr() { return buffer; }
};

const static size_t bufferSize = 1024;
static BufferArea buffer(bufferSize);

emscripten::val getBufferArea() {
	return emscripten::val(emscripten::typed_memory_view(bufferSize, buffer.getPtr()));
}

EMSCRIPTEN_BINDINGS(uint8_array_test) {
	function("getBufferArea", &getBufferArea);
}
