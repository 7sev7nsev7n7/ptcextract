ptcextract : src/main.c src/lib/libutils.h
		gcc src/main.c /usr/lib/libb64.so -o ptcextract
