#!bin/bash 

#Set The arguments 

COMPILER="g++"
ARGS="-g -std=c++17"
SRC="./src/*.cpp"
INCLUDE="./include"
BINARY="./bin/pongprog"
LIBS="-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -ldl"

echo "Compiling for ${OSTYPE}"

if [["$OSTYPE" == "linux-gnu"*]]; then 
	echo ""
elif [[ "$OSTYPE" == "darwin"* ]]; then 
	echo "Compiling for MAC"
	INCLUDE="./include -I/Library/Frameworks/SDL2.framework/Headers"
	LIBS="-F/Library/Frameworks -framework SDL2"
	echo ""
elif [[ "$OSTYPE" == "mysys"* ]]; then 
	echo "Compiling for Windows(mysys)"
	LIBS="-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer"
	echo ""
else 
	echo "Sorry:(( But the program can't identify your os system or your system is unavailable for game!"
	echo ""
fi 

COMPILE="${COMPILER} ${ARGS} ${SRC} -I ${INCLUDE} ${LIBS} -o ${BINARY}"

echo "${COMPILE}"
eval $COMPILE 


