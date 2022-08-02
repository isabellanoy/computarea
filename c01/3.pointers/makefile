all: p0.exe p1.exe

p0.exe: p0.cxx
  ${CC} p0.cxx -o p0

p1.exe: p1.cxx
  ${CC} p1.cxx -o p1

p0: p0.exe

p1: p1.exe

clean:
  rm -f *.exe *.map *.o *.s
