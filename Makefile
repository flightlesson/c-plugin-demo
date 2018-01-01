all: app c-plugin.so

app: main.c
	$(CC) main.c -o app

c-plugin.so: c_plugin.o
	$(CC) -shared -o c-plugin.so c_plugin.o

