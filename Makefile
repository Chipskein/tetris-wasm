
CC = cc
EMCC = emcc
CFLAGS = -Wall -Os
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
EMCC_FLAGS = -I. -Iraylib/src -L. -Lraylib/src -s USE_GLFW=3 --shell-file ./build/web/minshell.html -DPLATFORM_WEB
WEB_BUILD_DIR = build/web
LINUX_BUILD_DIR = build/linux


all: web linux

web: $(WEB_BUILD_DIR)/index.html $(WEB_BUILD_DIR)/index.js $(WEB_BUILD_DIR)/index.wasm

linux: $(LINUX_BUILD_DIR)/game

$(WEB_BUILD_DIR)/index.html $(WEB_BUILD_DIR)/index.js $(WEB_BUILD_DIR)/index.wasm: *.c
	$(EMCC) -o index.html *.c $(CFLAGS) ./raylib/src/libraylib.a $(EMCC_FLAGS)
	mv index.html $(WEB_BUILD_DIR)/index.html
	mv index.js $(WEB_BUILD_DIR)/index.js
	mv index.wasm $(WEB_BUILD_DIR)/index.wasm

$(LINUX_BUILD_DIR)/game: *.c
	$(CC) *.c -o game $(CFLAGS) $(LDFLAGS)
	mv game $(LINUX_BUILD_DIR)/game

clean:
	rm -f $(WEB_BUILD_DIR)/index.html $(WEB_BUILD_DIR)/index.js $(WEB_BUILD_DIR)/index.wasm $(LINUX_BUILD_DIR)/game

.PHONY: all web linux clean