##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=work03
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=C:/Embedded_System/03_Firmware/Programming_SourceCode/CodeLite/work01
ProjectPath            :=C:/Embedded_System/03_Firmware/Programming_SourceCode/CodeLite/work01/work03
IntermediateDirectory  :=../build-$(ConfigurationName)/work03
OutDir                 :=../build-$(ConfigurationName)/work03
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=user
Date                   :=22/03/2022
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
Objects0=../build-$(ConfigurationName)/work03/main.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/work03/.d $(Objects) 
	@if not exist "..\build-$(ConfigurationName)\work03" mkdir "..\build-$(ConfigurationName)\work03"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\build-$(ConfigurationName)\work03" mkdir "..\build-$(ConfigurationName)\work03"
	@if not exist ""..\build-$(ConfigurationName)\bin"" mkdir ""..\build-$(ConfigurationName)\bin""

../build-$(ConfigurationName)/work03/.d:
	@if not exist "..\build-$(ConfigurationName)\work03" mkdir "..\build-$(ConfigurationName)\work03"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/work03/main.c$(ObjectSuffix): main.c ../build-$(ConfigurationName)/work03/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Embedded_System/03_Firmware/Programming_SourceCode/CodeLite/work01/work03/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/work03/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/work03/main.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/work03/main.c$(DependSuffix) -MM main.c

../build-$(ConfigurationName)/work03/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/work03/main.c$(PreprocessSuffix) main.c


-include ../build-$(ConfigurationName)/work03//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


