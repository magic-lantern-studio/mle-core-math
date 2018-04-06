# Microsoft Developer Studio Project File - Name="mlmath" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mlmath - Win32 Tools Float Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mlmath.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mlmath.mak" CFG="mlmath - Win32 Tools Float Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mlmath - Win32 Float Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mlmath - Win32 Float Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mlmath - Win32 Fixed Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mlmath - Win32 Fixed Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mlmath - Win32 Tools Float Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "mlmath - Win32 Tools Float Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mlmath - Win32 Float Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Float Debug"
# PROP BASE Intermediate_Dir ".\Float Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FloatDebug"
# PROP Intermediate_Dir "FloatDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ML_DEBUG" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /YX /c
# ADD CPP /nologo /Gz /Zp4 /W3 /GX /Z7 /Od /I "..\..\..\..\util\common\include" /I "..\..\..\common\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ML_DEBUG" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /D "MLE_NOT_DLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"FloatDebug\mlmathd.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Install Libraries
PostBuild_Cmds=mkdir $(MLE_HOME)\lib\runtime\stdcall	copy FloatDebug\mlmathd.lib $(MLE_HOME)\lib\runtime\stdcall\mlmathd.lib	mkdir $(MLE_HOME)\include\math	xcopy /Y ..\..\..\common\include\math\* $(MLE_HOME)\include\math
# End Special Build Tool

!ELSEIF  "$(CFG)" == "mlmath - Win32 Float Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Float Release"
# PROP BASE Intermediate_Dir ".\Float Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "FloatRelease"
# PROP Intermediate_Dir "FloatRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /YX /c
# ADD CPP /nologo /Gz /Zp4 /W3 /GX /O2 /I "..\..\..\..\util\common\include" /I "..\..\..\common\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /D "MLE_NOT_DLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Install Libraries
PostBuild_Cmds=mkdir $(MLE_HOME)\lib\runtime\stdcall	copy FloatRelease\mlmath.lib $(MLE_HOME)\lib\runtime\stdcall\mlmath.lib	mkdir $(MLE_HOME)\include\math	xcopy /Y ..\..\..\common\include\math\* $(MLE_HOME)\include\math
# End Special Build Tool

!ELSEIF  "$(CFG)" == "mlmath - Win32 Fixed Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Fixed Debug"
# PROP BASE Intermediate_Dir ".\Fixed Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "FixedDebug"
# PROP Intermediate_Dir "FixedDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ML_DEBUG" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /YX /c
# ADD CPP /nologo /Gz /Zp4 /W3 /GX /Z7 /Od /I "..\..\..\..\util\common\include" /I "..\..\..\common\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ML_DEBUG" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=1 /D "MLE_NOT_DLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"FixedDebug\mlfmath.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"FixedDebug\mlfmathd.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Install Libraries
PostBuild_Cmds=mkdir $(MLE_HOME)\lib\runtime\stdcall	copy FixedDebug\mlfmathd.lib $(MLE_HOME)\lib\runtime\stdcall\mlfmathd.lib	mkdir $(MLE_HOME)\include\math	xcopy /Y ..\..\..\common\include\math\* $(MLE_HOME)\include\math
# End Special Build Tool

!ELSEIF  "$(CFG)" == "mlmath - Win32 Fixed Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Fixed Release"
# PROP BASE Intermediate_Dir ".\Fixed Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "FixedRelease"
# PROP Intermediate_Dir "FixedRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /YX /c
# ADD CPP /nologo /Gz /Zp4 /W3 /GX /O2 /I "..\..\..\..\util\common\include" /I "..\..\..\common\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=1 /D "MLE_NOT_DLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"FixedRelease\mlfmath.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"FixedRelease\mlfmath.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Install Libraries
PostBuild_Cmds=mkdir $(MLE_HOME)\lib\runtime\stdcall	copy FixedRelease\mlfmath.lib $(MLE_HOME)\lib\runtime\stdcall\mlfmath.lib	mkdir $(MLE_HOME)\include\math	xcopy /Y  ..\..\..\common\include\math\* $(MLE_HOME)\include\math
# End Special Build Tool

!ELSEIF  "$(CFG)" == "mlmath - Win32 Tools Float Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mlmath___Win32_Tools_Float_Debug"
# PROP BASE Intermediate_Dir "mlmath___Win32_Tools_Float_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ToolsFloatDebug"
# PROP Intermediate_Dir "ToolsFloatDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /W3 /GX /Z7 /Od /I "..\..\..\..\util\common\include" /I "..\..\..\common\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ML_DEBUG" /D "ML_CDECL" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /YX /FD /c
# ADD CPP /nologo /Zp8 /MTd /W3 /GX /Z7 /Od /I "..\..\..\..\util\common\include" /I "..\..\..\common\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "ML_DEBUG" /D "ML_CDECL" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /D "MLE_NOT_DLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"RehearsalFloatDebug\mlmathd.lib"
# ADD LIB32 /nologo /out:"ToolsFloatDebug\mlmathd.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Install Libraries
PostBuild_Cmds=mkdir $(MLE_HOME)\lib\tools	copy ToolsFloatDebug\mlmathd.lib $(MLE_HOME)\lib\tools\mlmathd.lib	mkdir $(MLE_HOME)\lib\runtime\cdecl	copy ToolsFloatDebug\mlmathd.lib $(MLE_HOME)\lib\runtime\cdecl\mlmathd.lib	mkdir $(MLE_HOME)\include\math	xcopy /Y ..\..\..\common\include\math\* $(MLE_HOME)\include\math
# End Special Build Tool

!ELSEIF  "$(CFG)" == "mlmath - Win32 Tools Float Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "mlmath___Win32_Tools_Float_Release"
# PROP BASE Intermediate_Dir "mlmath___Win32_Tools_Float_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ToolsFloatRelease"
# PROP Intermediate_Dir "ToolsFloatRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp4 /W3 /GX /O2 /I "..\..\..\..\util\common\include" /I "..\..\..\common\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "ML_CDECL" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /YX /FD /c
# ADD CPP /nologo /Zp8 /MT /W3 /GX /O2 /I "..\..\..\..\util\common\include" /I "..\..\..\common\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "ML_CDECL" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /D "MLE_NOT_DLL" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Install Libraries
PostBuild_Cmds=mkdir $(MLE_HOME)\lib\tools	copy ToolsFloatRelease\mlmath.lib $(MLE_HOMe)\lib\tools\mlmath.lib	mkdir $(MLE_HOME)\lib\runtime\cdecl	copy ToolsFloatRelease\mlmath.lib $(MLE_HOMe)\lib\runtime\cdecl\mlmath.lib	mkdir $(MLE_HOME)\include\math	xcopy /Y ..\..\..\common\include\math\* $(MLE_HOME)\include\math
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "mlmath - Win32 Float Debug"
# Name "mlmath - Win32 Float Release"
# Name "mlmath - Win32 Fixed Debug"
# Name "mlmath - Win32 Fixed Release"
# Name "mlmath - Win32 Tools Float Debug"
# Name "mlmath - Win32 Tools Float Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\..\common\src\asine.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\atan.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\fixed.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\recip.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\rotation.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\scalar.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\sine.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\sqrt.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\transfrm.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\common\src\vector.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\..\common\include\math\3dmath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\angle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\anglebr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\asine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\atan.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\recip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\rotation.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\scalar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\sine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\sqrt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\transfrm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\trig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\common\include\math\vector.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
