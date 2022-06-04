# MAKEFILE list 8 windows
all: list8.exe ZbiornikPaliwa.obj Silnik.obj list8.obj cleanup
.PHONY: all

ZbiornikPaliwa.obj: ZbiornikPaliwa.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:ZbiornikPaliwa.obj ZbiornikPaliwa.cpp

Silnik.obj: Silnik.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:Silnik.obj Silnik.cpp

list8.exe: list8.obj ZbiornikPaliwa.obj Silnik.obj
	link /DEBUG /OUT:lista8.exe list8.obj ZbiornikPaliwa.obj Silnik.obj

list8.obj: lista8.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:list8.obj list8.cpp 

cleanup:
	DEL *.obj *.pdb *.ilk