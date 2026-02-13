ptcextract : src/main.c src/lib/libpony.h
		gcc src/main.c /usr/lib/libb64.so -o ptcextract
