# MAKEFILE list 5 windows
all: list5.exe list5.obj cleanup
.PHONY: all

list5.exe: list5.obj
	link /DEBUG /OUT:list5.exe list5.obj

list5.obj: list5.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /openmp:experimental /Fo:list5.obj list5.cpp 

cleanup:
	DEL *.obj *.pdb *.ilk