CALL CMakeCommon.bat

ECHO *** Set VS2019 specifics and run CMake ***

SET MAINCMAKE=%SRCROOTDIR%\projects\CMake\targets\GUCEF_exe_udp2redis
SET VS19_OUTPUTDIR="%OUTPUTDIR%\VS2019x64_udp2redis"

CMake.exe -DBUILD_SHARED_LIBS=ON -G"Visual Studio 16 2019" -A x64 -H"%MAINCMAKE%" -B%VS19_OUTPUTDIR%
PAUSE