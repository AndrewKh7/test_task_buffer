#Target
TARGET = prog

#Build folder
BUILD = build

#Source 
SRC_DIR := \
src \
Buffer/src

#SRC_DIR := $(addprefix ../,$(SRC_DIR))
SRC := $(addsuffix  /*.cpp, $(SRC_DIR))

#includes
INC = \
-Iinc \
-IBuffer/inc

#Compiler
CXX = g++
CXXFLAGS = $(INC) -Wall 
OBJ = $(notdir $(patsubst %.cpp,%.o,$(wildcard $(SRC))))

VPATH = $(SRC_DIR)

#tasks
all: $(BUILD) $(BUILD)/$(TARGET)
	@echo Success

$(BUILD)/$(TARGET): $(BUILD)/$(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -fR $(BUILD)

