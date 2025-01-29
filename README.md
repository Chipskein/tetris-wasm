# Tetris clone

<p align="center">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/9c/Typical_Tetris_Game.svg/640px-Typical_Tetris_Game.svg.png" alt="zero" width="60" height="120">
</p>

### Demo
  * [WASM](https://chipskein.github.io/tetris-wasm/)

### Description
  A tetris clone for testing WASM

### Keymap
| Key             | Action                                                                                                  |
|-----------------|---------------------------------------------------------------------------------------------------------|
| `KEY_ESCAPE`    | Closes the window.                                                                          |
| `KEY_SPACE`     | Rotate                                                                                                  |
| `KEY_RIGHT`     | Move right                                                                                              |
| `KEY_LEFT`      | Move left                                                                                               |
| `KEY_DOWN`      | Move down                                                                                               |



### How to Build

  * Clone recursively
    
        git clone --recursive https://github.com/Chipskein/tetris-wasm.git
    
  * Compile

      * linux(CC)
        
            make linux
    
      * WASM([Emscripten](https://emscripten.org/docs/introducing_emscripten/index.html))
    
            make web
    
      * for both
    
            make

### How to Run(linux)

    ./build/linux/game
    

### Dependencies
* GCC
* [Emscripten(web)](https://emscripten.org/docs/introducing_emscripten/index.html)
* [Raylib](https://github.com/raysan5/raylib)
  


