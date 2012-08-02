shared:
	gcc -fpic -g -c -Wall example.c
	gcc -shared -o libargmax.so -fpic example.o 
c_test:
	gcc -L. -Wall c_test.c -o c_test -largmax
