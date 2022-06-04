# MAKEFILE list 3 windows
all: list3.exe a.obj list3.obj cleanup
.PHONY: all

a.obj: a.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:a.obj a.cpp

list3.exe: lista3.obj a.obj
	link /DEBUG /OUT:lista3.exe list3.obj a.obj

list3.obj: list3.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:list3.obj lista3.cpp 

cleanup:
	DEL *.obj *.pdb *.ilk