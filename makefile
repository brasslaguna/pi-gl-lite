
OBJ = $(wildcard **/*.cc)

OBJ_APP = app.cc
OBJ_MAIN = main.cc

FLAG_INCLUDE = -I.
FLAG_DEBUG = -g
FLAG_PI = -ldrm -lgbm -lEGL -lGL -I/usr/include/libdrm
FLAG_IMAGE = -lfreeimage
FLAG_VAR = -DINCLUDE_GL_PI_4 -DDEFINE_GLSL_VERSION='"300 es"'

OBJ = $(OBJ_MAIN) $(OBJ_APP) $(OBJ)
FLAG = $(FLAG_VAR) $(FLAG_INCLUDE) $(FLAG_PI) $(FLAG_IMAGE) 

O = bin/app

CC = g++
C++ = -std=c++11

main: $(OBJ)
	$(CC) $(C++) $(FLAG) $(OBJ) -o $(O)