all : encode decode
decode : decode.o
encode : encode.o
encode.o : encode.c b40.h
decode.o : decode.c b40.h
