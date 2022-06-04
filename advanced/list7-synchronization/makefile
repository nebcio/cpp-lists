# MAKEFILE list 7 windows
all: list7.exe listTask.obj list7.obj cleanup
.PHONY: all

listTask.obj: listtask.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:listTask.obj listTask.cpp

list7.exe: list7.obj listTask.obj
	link /DEBUG /OUT:lista7.exe list7.obj listTask.obj

list7.obj: list7.cpp
	cl /std:c++latest /EHsc /c /Zi /W4 /WX /Fo:list7.obj list7.cpp 

cleanup:
	DEL *.obj *.pdb *.ilk