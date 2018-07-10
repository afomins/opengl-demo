# Microsoft Developer Studio Project File - Name="ogl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ogl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ogl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ogl.mak" CFG="ogl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ogl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ogl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ogl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\source" /I ".\source\def" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"ogl.exe"

!ELSEIF  "$(CFG)" == "ogl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\source" /I ".\source\def" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"ogl_d.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ogl - Win32 Release"
# Name "ogl - Win32 Debug"
# Begin Group "def"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\def\def_main.h
# End Source File
# Begin Source File

SOURCE=.\source\def\def_res.h
# End Source File
# Begin Source File

SOURCE=.\source\def\def_rnd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\def\def_rnd.h
# End Source File
# Begin Source File

SOURCE=.\source\def\def_str.cpp
# End Source File
# Begin Source File

SOURCE=.\source\def\def_str.h
# End Source File
# Begin Source File

SOURCE=.\source\def\def_type.h
# End Source File
# End Group
# Begin Group "app"

# PROP Default_Filter ""
# Begin Group "res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\app\res\res.rc
# End Source File
# Begin Source File

SOURCE=.\source\app\res\resource.h
# End Source File
# End Group
# Begin Group "wnd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\app\wnd\wmd_about.cpp
# End Source File
# Begin Source File

SOURCE=.\source\app\wnd\wmd_main.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\app\app.cpp
# End Source File
# Begin Source File

SOURCE=.\source\app\app.h
# End Source File
# Begin Source File

SOURCE=.\source\app\app_fnt.cpp
# End Source File
# Begin Source File

SOURCE=.\source\app\app_fnt.h
# End Source File
# Begin Source File

SOURCE=.\source\app\app_ogl.cpp
# End Source File
# Begin Source File

SOURCE=.\source\app\app_ogl.h
# End Source File
# Begin Source File

SOURCE=.\source\app\app_tex.cpp
# End Source File
# Begin Source File

SOURCE=.\source\app\app_tex.h
# End Source File
# Begin Source File

SOURCE=.\source\app\app_timer.cpp
# End Source File
# Begin Source File

SOURCE=.\source\app\app_timer.h
# End Source File
# Begin Source File

SOURCE=.\source\app\app_wnd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\app\app_wnd.h
# End Source File
# End Group
# Begin Group "scene"

# PROP Default_Filter ""
# Begin Group "script"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\scene\script\scene_script.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script.h
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_00.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_01.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_02.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_03.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_04.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_05.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_change_cube_col.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_change_fov.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_change_rot_vect.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_change_sky_rot_vect.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_rnd_change_rot_vect.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_rnd_change_sky_rot_vect.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_rotate_cubes.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\script\scene_script_rotate_sky.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\scene\scene.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene.h
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_cube.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_cube.h
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_cube_line.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_cube_line.h
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_cube_point.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_cube_point.h
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_cube_side.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_cube_side.h
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_light.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_light.h
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_sky.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scene\scene_sky.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\main.cpp
# End Source File
# End Target
# End Project
