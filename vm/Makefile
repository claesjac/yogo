all: compile

compile:
	clang -g -L/opt/local/lib -I/opt/local/include -lJudy -shared -o libyogovm.so -Iinclude lib/*.c
	clang -g -Iinclude -I/opt/local/include -L. -L/opt/local/lib -lJudy -lyogovm  -o yogovm main.c