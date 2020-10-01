default:
	gcc total.c -w 
	./a.out

preprocessor:
	gcc -E total.c -o total.i

compiler:
	gcc -S total.c -w

assembler:
	gcc -c total.c -w

linker:
	gcc total.c -w