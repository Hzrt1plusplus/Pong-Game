# Description 
This is a simple version of classic PONG game in SDL2 and made by using C++ language. For compiling run ` sh build.sh ` in Pong directory.
* **NOTE:** It won't work if you haven't installed libraries bellow: 
    1. SDL2
    2. SDL2_image 
    3. SDL2_mixer 
    4. SDL2_ttf 

For downloading libraries in linux use `sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev` or use `sudo pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf` if you are using arch linux based os. In mac `brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf`. After downloading prerequisites you can build program by simply running `sh build.sh`. If you want a simple shell command use `g++ ./src/*.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o ./bin/pongprog`. After compiling, run ./bin/pongprog. Have fun!

# Preview
### preview1.png
![FILE NOT FOUND!](<./preview1.png>)
### preview2.png
![FILE NOT FOUND!](<./preview2.png>)

# Resources and Attribution 

All third-party resources used in this project (e.g., images, fonts, libraries) are either: 

- In the public domain, or 
- Licensed under free and open licenses (e.g., MIT, CC0, CC-BY, GPL, etc.)

Where required, attribution is provided bellow: 

- Library:
    - License : Zlib 
    - Source : [See Here](https://www.libsdl.org/)
- Collision sound effect:
    - License : CC-BY 3.0 
    - Source : [See Here](https://opengameart.org/content/collision-nutfall-yo-frankie)
- Font:
    - License : Free For Personal Use 
    - Source : [See Here](https://www.1001freefonts.com/space-age.font)
    - Redistribution : Allowed under the font's license terms(Please see Space.txt - the license for details).




