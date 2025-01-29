CC = cc
EMCC = emcc
CFLAGS = -Wall -Os
LDFLAGS = -lGL -lm -lpthread -ldl -lrt -lX11
EMCC_FLAGS = -I. -Iraylib/src -L. -Lraylib/src -s USE_GLFW=3 --shell-file ./build/web/minshell.html -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2


WEB_BUILD_DIR = build/web
LINUX_BUILD_DIR = build/linux
RAYLIB_SRC_DIR = raylib/src


SRCS = $(wildcard *.c)
RAYLIB_SRCS = $(RAYLIB_SRC_DIR)/rcore.c $(RAYLIB_SRC_DIR)/rshapes.c $(RAYLIB_SRC_DIR)/rtextures.c \
              $(RAYLIB_SRC_DIR)/rtext.c $(RAYLIB_SRC_DIR)/rmodels.c $(RAYLIB_SRC_DIR)/utils.c \
              $(RAYLIB_SRC_DIR)/raudio.c
RAYLIB_OBJS = $(RAYLIB_SRCS:.c=.o)


all: web linux

web: $(WEB_BUILD_DIR)/index.html $(WEB_BUILD_DIR)/index.js $(WEB_BUILD_DIR)/index.wasm

linux: $(LINUX_BUILD_DIR)/game


$(RAYLIB_OBJS): %.o: %.c
	$(EMCC) -c $< -o $@ $(CFLAGS) -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2


libraylib.a: $(RAYLIB_OBJS)
	emar rcs $@ $^


$(WEB_BUILD_DIR)/index.html $(WEB_BUILD_DIR)/index.js $(WEB_BUILD_DIR)/index.wasm: $(SRCS) libraylib.a
	$(EMCC) -o index.html $(SRCS) $(CFLAGS) libraylib.a $(EMCC_FLAGS)
	mv index.html $(WEB_BUILD_DIR)/index.html
	mv index.js $(WEB_BUILD_DIR)/index.js
	mv index.wasm $(WEB_BUILD_DIR)/index.wasm


$(LINUX_BUILD_DIR)/game: $(SRCS)
	$(CC) $(SRCS) -o game $(CFLAGS) -L$(RAYLIB_SRC_DIR) -lraylib $(LDFLAGS)
	mv game $(LINUX_BUILD_DIR)/game

clean:
	rm -f $(RAYLIB_OBJS) libraylib.a
	rm -f $(WEB_BUILD_DIR)/index.html $(WEB_BUILD_DIR)/index.js $(WEB_BUILD_DIR)/index.wasm
	rm -f $(LINUX_BUILD_DIR)/game

.PHONY: all web linux clean