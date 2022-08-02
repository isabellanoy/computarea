all: v t

v: var_sizes.exe

t: type_sizes.exe

var_sizes.exe:
	${CC} var_sizes.cxx -o var_sizes.exe

type_sizes.exe:
	${CC} type_sizes.cxx -o type_sizes.exe

clean:
	rm -f *.exe *.map *.o *.s
