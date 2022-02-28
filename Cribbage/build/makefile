CC = g++
CFLAGS =

UTIL_SRCS = $(wildcard ../Utils/*.cpp)
UTIL_SRCS := $(UTIL_SRCS:%test.cpp=)
UTIL_OBJS = $(UTIL_SRCS:../Utils/%.cpp=%.o)

HAND_AIS_SRCS = $(wildcard ../AIs/Hand/*.cpp)
HAND_AIS_SRCS := $(HAND_AIS_SRCS:%test.cpp=)
HAND_AIS_OBJS = $(HAND_AIS_SRCS:../AIs/Hand/%.cpp=%.o)

PEGGER_AIS_SRCS = $(wildcard ../AIs/Pegger/*.cpp)
PEGGER_AIS_SRCS := $(PEGGER_AIS_SRCS:%test.cpp=)
PEGGER_AIS_OBJS = $(PEGGER_AIS_SRCS:../AIs/Pegger/%.cpp=%.o)

GAME_SRCS = $(wildcard ../Game/*.cpp)
GAME_SRCS := $(GAME_SRCS:%test.cpp=)
GAME_OBJS = $(GAME_SRCS:../Game/%.cpp=%.o)

ANALYSIS_SRCS = $(wildcard ../Analysis/*.cpp)
ANALYSIS_SRCS := $(ANALYSIS_SRCS:%test.cpp=)
ANALYSIS_OBJS = $(ANALYSIS_SRCS:../Analysis/%.cpp=%.o)

ROOT_SRCS = $(wildcard ../*.cpp)
ROOT_OBJS = $(ROOT_SRCS:../%.cpp=%.o)

.PHONY: options util-dir hand-ai-dir pegger-ai-dir game-dir analysis-dir root-dir util util.o hand-ai hand-ai.o pegger-ai pegger-ai.o game game.o analysis analysis.o root root.o clean-object-files clean

# display options (this is the default command)
options:
	@echo "options:"
	@echo " ---- util-dir"
	@echo " ---- hand-ai-dir"
	@echo " ---- pegger-ai-dir"
	@echo " ---- game-dir"
	@echo " ---- analysis-dir"
	@echo " ---- root-dir"

all: util-dir hand-ai-dir pegger-ai-dir game-dir analysis-dir root-dir

# options that we want to display to users
util-dir: util clean-object-files

hand-ai-dir: hand-ai clean-object-files

pegger-ai-dir: pegger-ai clean-object-files

game-dir: game clean-object-files

analysis-dir: analysis clean-object-files

root-dir: root clean-object-files

# targets to compile the Utils directoy
util: util.o
	@$(CC) $(CFLAGS) -c ../Utils/test.cpp
	@echo "compiled test file"
	@echo "linking..."
	@$(CC) $(CFLAGS) -o test-util.exe test.o $(UTIL_OBJS)
	@echo "done"

util.o:
	@$(CC) $(CFLAGS) -c $(UTIL_SRCS)
	@echo "compiled Util/"

# targets to compile the Hand AIs directory
hand-ai: util.o hand-ai.o
	@$(CC) $(CFLAGS) -c ../AIs/Hand/test.cpp
	@echo "compiled test file"
	@echo "linking..."
	@$(CC) $(CFLAGS) -o test-hand-ai.exe test.o $(UTIL_OBJS) $(HAND_AIS_OBJS)
	@echo "done"

hand-ai.o: util.o
	@$(CC) $(CFLAGS) -c $(HAND_AIS_SRCS)
	@echo "compiled AIs/Hand/"

# targets to compile the Pegger AIs directory
pegger-ai: util.o pegger-ai.o
	@$(CC) $(CFLAGS) -c ../AIs/Pegger/test.cpp
	@echo "compiled test file"
	@echo "linking..."
	@$(CC) $(CFLAGS) -o test-pegger-ai.exe test.o $(UTIL_OBJS) $(PEGGER_AIS_OBJS)
	@echo "done"

pegger-ai.o: util.o
	@$(CC) $(CFLAGS) -c $(PEGGER_AIS_SRCS)
	@echo "compiled AIs/Pegger/"

# targets to compile the Game directory
game: util.o hand-ai.o pegger-ai.o game.o
	@$(CC) $(CFLAGS) -c ../Game/test.cpp
	@echo "compiled test file"
	@echo "linking..."
	@$(CC) $(CFLAGS) -o test-game.exe test.o $(UTIL_OBJS) $(HAND_AIS_OBJS) $(PEGGER_AIS_OBJS) $(GAME_OBJS)
	@echo "done"

game.o: util.o hand-ai.o pegger-ai.o
	@$(CC) $(CFLAGS) -c $(GAME_SRCS)
	@echo "compiled Game/"

# targets to compile the Analysis directory
analysis: util.o hand-ai.o pegger-ai.o game.o analysis.o
	@$(CC) $(CFLAGS) -c ../Analysis/test.cpp
	@echo "compiled test file"
	@echo "linking..."
	@$(CC) $(CFLAGS) -o test-analysis.exe test.o $(UTIL_OBJS) $(HAND_AIS_OBJS) $(PEGGER_AIS_OBJS) $(GAME_OBJS) $(ANALYSIS_OBJS)
	@echo "done"

analysis.o: util.o hand-ai.o pegger-ai.o game.o
	@$(CC) $(CFLAGS) -c $(ANALYSIS_SRCS)
	@echo "compiled Analysis/"

# targets to compile the root directory
root: util.o hand-ai.o pegger-ai.o game.o analysis.o root.o
	@echo "compiled main file"
	@echo "linking..."
	@$(CC) $(CFLAGS) -o test-root.exe $(UTIL_OBJS) $(HAND_AIS_OBJS) $(PEGGER_AIS_OBJS) $(GAME_OBJS) $(ANALYSIS_OBJS) $(ROOT_OBJS)
	@echo "done"

root.o: util.o hand-ai.o pegger-ai.o game.o analysis.o
	@$(CC) $(CFLAGS) -c $(ROOT_SRCS)
	@echo "compiled root directory"

# targets to clean object files
clean-object-files:
	@rm *.o

clean: clean-object-files
	@rm *.exe
