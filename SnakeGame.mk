##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SnakeGame
ConfigurationName      :=Debug
WorkspacePath          :=/home/farofus/Documents/Snake
ProjectPath            :=/home/farofus/Documents/Snake
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Leonardo Oliveira Reis
Date                   :=24/11/22
CodeLitePath           :=/home/farofus/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="SnakeGame.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/usr/include/SDL2 $(IncludeSwitch)tiny_dnn 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SDL2 $(LibrarySwitch)pthread 
ArLibs                 :=  "libSDL2.a" "pthread" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib/x86_64-linux-gnu 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall -pedantic -std=c++2a  $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
LD_LIBRARY_PATH:=/usr/local/lib:$LD_LIBRARY_PATH
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/snake_game.cpp$(ObjectSuffix) $(IntermediateDirectory)/DeepQAgent.cpp$(ObjectSuffix) $(IntermediateDirectory)/input.cpp$(ObjectSuffix) $(IntermediateDirectory)/graphics.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/farofus/Documents/Snake/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/snake_game.cpp$(ObjectSuffix): snake_game.cpp $(IntermediateDirectory)/snake_game.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/farofus/Documents/Snake/snake_game.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/snake_game.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/snake_game.cpp$(DependSuffix): snake_game.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/snake_game.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/snake_game.cpp$(DependSuffix) -MM snake_game.cpp

$(IntermediateDirectory)/snake_game.cpp$(PreprocessSuffix): snake_game.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/snake_game.cpp$(PreprocessSuffix) snake_game.cpp

$(IntermediateDirectory)/DeepQAgent.cpp$(ObjectSuffix): DeepQAgent.cpp $(IntermediateDirectory)/DeepQAgent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/farofus/Documents/Snake/DeepQAgent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DeepQAgent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DeepQAgent.cpp$(DependSuffix): DeepQAgent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DeepQAgent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DeepQAgent.cpp$(DependSuffix) -MM DeepQAgent.cpp

$(IntermediateDirectory)/DeepQAgent.cpp$(PreprocessSuffix): DeepQAgent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DeepQAgent.cpp$(PreprocessSuffix) DeepQAgent.cpp

$(IntermediateDirectory)/input.cpp$(ObjectSuffix): input.cpp $(IntermediateDirectory)/input.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/farofus/Documents/Snake/input.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/input.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/input.cpp$(DependSuffix): input.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/input.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/input.cpp$(DependSuffix) -MM input.cpp

$(IntermediateDirectory)/input.cpp$(PreprocessSuffix): input.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/input.cpp$(PreprocessSuffix) input.cpp

$(IntermediateDirectory)/graphics.cpp$(ObjectSuffix): graphics.cpp $(IntermediateDirectory)/graphics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/farofus/Documents/Snake/graphics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/graphics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/graphics.cpp$(DependSuffix): graphics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/graphics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/graphics.cpp$(DependSuffix) -MM graphics.cpp

$(IntermediateDirectory)/graphics.cpp$(PreprocessSuffix): graphics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/graphics.cpp$(PreprocessSuffix) graphics.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


