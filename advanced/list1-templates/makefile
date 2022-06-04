# MAKEFILE list 1	windows
all: list1.exe list1.obj cleanup
.PHONY: all

list1.exe: list1.obj
	link /DEBUG /OUT:list1.exe list1.obj

list1.obj: list1.cpp wektor.h
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:list1.obj list1.cpp 

cleanup:
	DEL *.obj *.pdb *.ilk

