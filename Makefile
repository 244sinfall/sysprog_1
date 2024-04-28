run_test:
	gcc -o test test_ru_date.c ru_date.c -lcunit && ./test && rm test

run_child:
	gcc -o child child.c ru_date.c && ./child 29.12.1998 && rm child

build_child:
	gcc -o ./out/child child.c ru_date.c

build_parent:
	gcc parent.c ru_date.c -o ./out/parent

run_parent:
	make build_child && make build_parent && ./out/parent 29.12.1998 26.01.2004 && rm ./out/*

build_all:
	make build_child && make build_parent