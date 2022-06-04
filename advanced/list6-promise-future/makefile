# MAKEFILE list 6 windows
all: list6.exe list6.obj cleanup
.PHONY: all

list6.exe: list6.obj
	link /DEBUG /OUT:list6.exe list6.obj

list6.obj: list6.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /openmp:experimental /Fo:list6.obj list6.cpp 

cleanup:
	DEL *.obj *.pdb *.ilk