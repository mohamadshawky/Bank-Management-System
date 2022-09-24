all : app.exe
	@ app.exe
	
app.exe: obj/app.o obj/client.o
	@ gcc obj/app.o obj/client.o -o app.exe
	
obj/app.o: app.c
	@ gcc -c app.c -o obj/app.o
	
obj/client.o: src/client.c
	@ cd src && gcc -c client.c -o ../obj/client.o 