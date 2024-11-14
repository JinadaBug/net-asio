@echo off
:: ================== Compilation Commands ==================
cl /std:c++20 /EHsc /c /Fo"out\obj\\" /D "_WIN32_WINNT=0x0602" /I ./add ./src/client.cxx
cl /std:c++20 /EHsc /c /Fo"out\obj\\" /D "_WIN32_WINNT=0x0602" /I ./add ./src/server.cxx
:: ==================== Linking Commands ====================
link ./out/obj/client.obj /OUT:./out/bin/client.exe /SUBSYSTEM:CONSOLE
link ./out/obj/server.obj /OUT:./out/bin/server.exe /SUBSYSTEM:CONSOLE