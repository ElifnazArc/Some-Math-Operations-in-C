final:compile run

compile:
	@gcc .\main.c .\matrixLib.c -o main
run:
	@.\main.exe 103