@echo off
SET BUIDUSINGNDK_FORTARGET_THEBATCHDIR=%~dp0

ECHO.
ECHO *** Starting build from MS Windows ***
ECHO.

CALL %BUIDUSINGNDK_FORTARGET_THEBATCHDIR%\FindGucefHome.bat



SET ANDROID_TARGET_PROJECT=GUCEF_exe_ProjectGenerator



SET MSWIN_MAINANDROIDMAKEDIR=%GUCEF_HOME%\projects\Android\targets\%ANDROID_TARGET_PROJECT%
ECHO MSWIN_MAINANDROIDMAKEDIR=%MSWIN_MAINANDROIDMAKEDIR%

SET NOPAUSE=1
CALL BuildUsingNDK.bat
PAUSE