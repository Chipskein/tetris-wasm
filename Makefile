
web:
	emcc -o index.html *.c -Os -Wall ./raylib/src/libraylib.a -I. -Iraylib/src -L. -L raylib/src -s USE_GLFW=3 --shell-file ./build/web/minshell.html -DPLATFORM_WEB
	mv index.html build/web/index.html
	mv index.js build/web/index.js
	mv index.wasm build/web/index.wasm
linux:
	cc *.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game
	mv game build/linux/game
clean:
	rm -f build/web/index.html build/web/index.js build/web/index.wasm build/linux/game