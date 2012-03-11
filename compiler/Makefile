all: compile

compile:
	tools/lemon T=tools/lempar.c lib/grammar.y
	mv lib/grammar.h include/grammar.h.temp
	gawk -f ./addopcodes.awk include/grammar.h.temp > include/grammar.h
	clang -g -shared -o libyogoc.so -Iinclude lib/*.c
	clang -g -Iinclude -L. -lyogoc -o yogoc main.c
	
clean:
	find t/ \! -name '*.c' -depth 1 -print | xargs rm -r