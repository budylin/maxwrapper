shared:
	gcc -fpic -g -c -Wall example.c
	gcc -shared -o libargmax.so -fpic example.o 

module: shared
	python argmax_setup.py build_ext --inplace

c_test: shared
	gcc -L. -Wall c_test.c -o c_test -largmax
	./c_test

py_test: module
	python test.py

clean:
	rm -f *.o *.so c_test argmax.c
