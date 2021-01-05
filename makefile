
output: main.o prompt.o splitinp.o comfun1.o comfun2.o cominterp.o usercom.o pinfo.o redirect.o pipes.o headers.h
	gcc -g main.o prompt.o splitinp.o comfun1.o comfun2.o cominterp.o usercom.o pinfo.o redirect.o pipes.o -o output

main.o: main.c headers.h
	gcc -g -c main.c

comfun1.o: comfun1.c headers.h
	gcc -g -c comfun1.c

comfun2.o: comfun2.c headers.h
	gcc -g -c comfun2.c

splitinp.o: splitinp.c headers.h
	gcc -g -c splitinp.c

cominterp.o: cominterp.c headers.h
	gcc -g -c cominterp.c

prompt.o: prompt.c headers.h
	gcc -g -c prompt.c

pinfo.o: pinfo.c headers.h
	gcc -g -c pinfo.c

redirect.o: redirect.c headers.h
	gcc -g -c redirect.c

pipes.o: pipes.c headers.h
	gcc -g -c pipes.c

usercom.o: usercom.c headers.h
	gcc -g -c usercom.c

clean:
	rm *.o output
