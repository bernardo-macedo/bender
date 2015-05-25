LIB_TMXPARSER = libs/tmxparser
LIB_TINYXML   = libs/tinyxml
LIB_ZLIB      = libs/zlib
LIB_BASE64    = libs/tmxparser/base64

LIBS_CFILES   = $(LIB_TMXPARSER)/*.c \
                $(LIB_TINYXML)/*.c   \
                $(LIB_ZLIB)/*.c      \
                $(LIB_BASE64)/*.c

LIBS_CXXFILES =  $(LIB_TMXPARSER)/*.cpp \
                 $(LIB_TINYXML)/*.cpp   \
                 $(LIB_ZLIB)/*.cpp      \
                 $(LIB_BASE64)/*.cpp

INCLUDE = -I$(LIB_TMXPARSER)   \
          -I$(LIB_TINYXML)     \
          -I$(LIB_ZLIB)        \
          -I$(LIB_BASE64)

all:
	g++ *cpp $(LIBS_CFILES) $(LIBS_CXXFILES) Engine/*.cpp Engine/Geometry/*.cpp Engine/TileSet/*.cpp -o prog -W -Wall -pedantic -ansi -std=gnu++11 $(INCLUDE) -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2_gfx -lSDL2_ttf

clean: 
	rm prog
