all: app plugin

app: main.c
	$(CC) main.c -o app

plugin: plugin-impl.o
	$(CC) -shared -o plugin.so plugin-impl.o
