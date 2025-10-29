gcc -c libreria.c -o libreria.o
ar -rv liblibreria.a libreria.o
gcc -Wall -Wextra test.c -o test -L. -llibreria