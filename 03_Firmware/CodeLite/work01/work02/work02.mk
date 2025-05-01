##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=work02
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=C:/Embedded_System/03_Firmware/Programming_SourceCode/CodeLite/work01
ProjectPath            :=C:/Embedded_System/03_Firmware/Programming_SourceCode/CodeLite/work01/work02
IntermediateDirectory  :=../build-$(ConfigurationName)/work02
OutDir                 :=../build-$(ConfigurationName)/work02
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=user
Date                   :=11/03/2022
CodeLitePath           :="C:/Embedded_System/03_Firmware/CodeLite_32 bit"
LinkerName             :=C:/Embedded_System/03_Firmware/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/Embedded_System/03_Firmware/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/Embedded_System/03_Firmware/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/Embedded_System/03_Firmware/msys64/mingw64/bin/ar.exe rcu
CXX      := C:/Embedded_System/03_Firmware/msys64/mingw64/bin/g++.exe
CC       := C:/Embedded_System/03_Firmware/msys64/mingw64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/Embedded_System/03_Firmware/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=../build-$(ConfigurationName)/work02/main.c$(ObjectSuffix) ../build-$(ConfigurationName)/work02/led.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/work02/.d $(Objects) 
	@if not exist "..\build-$(ConfigurationName)\work02" mkdir "..\build-$(ConfigurationName)\work02"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\build-$(ConfigurationName)\work02" mkdir "..\build-$(ConfigurationName)\work02"
	@if not exist ""..\build-$(ConfigurationName)\bin"" mkdir ""..\build-$(ConfigurationName)\bin""

../build-$(ConfigurationName)/work02/.d:
	@if not exist "..\build-$(ConfigurationName)\work02" mkdir "..\build-$(ConfigurationName)\work02"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/work02/main.c$(ObjectSuffix): main.c ../build-$(ConfigurationName)/work02/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Embedded_System/03_Firmware/Programming_SourceCode/CodeLite/work01/work02/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/work02/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/work02/main.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/work02/main.c$(DependSuffix) -MM main.c

../build-$(ConfigurationName)/work02/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/work02/main.c$(PreprocessSuffix) main.c

../build-$(ConfigurationName)/work02/led.c$(ObjectSuffix): led.c ../build-$(ConfigurationName)/work02/led.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Embedded_System/03_Firmware/Programming_SourceCode/CodeLite/work01/work02/led.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/led.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/work02/led.c$(DependSuffix): led.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/work02/led.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/work02/led.c$(DependSuffix) -MM led.c

../build-$(ConfigurationName)/work02/led.c$(PreprocessSuffix): led.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/work02/led.c$(PreprocessSuffix) led.c


-include ../build-$(ConfigurationName)/work02//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


