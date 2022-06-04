# MAKEFILE list 2 windows
all: list2.exe list2.obj cleanup
.PHONY: all

list2.exe: list2.obj
	link /DEBUG /OUT:list2.exe list2.obj

list2.obj: list2.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:list2.obj list2.cpp 

cleanup:
	DEL *.obj *.pdb *.ilk