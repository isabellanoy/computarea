all: a b

before.exe:
	${CC} before_lambda.cxx -o before.exe

after.exe:
	${CC} after_lambda.cxx -o after.exe

b: before.exe

a: after.exe

clean:
	rm -f *.exe *.map *.o *.s
