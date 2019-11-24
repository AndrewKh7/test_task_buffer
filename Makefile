#Target
TARGET = prog


#Build folder
BUILD = build

#Source 
SRC_DIR := \
src \
Buffer/src \
test/src

#SRC_DIR := $(addprefix ../,$(SRC_DIR))
SRC := $(addsuffix  /*.cpp, $(SRC_DIR))

#includes
INC = \
-Iinc \
-IBuffer/inc \
-Itest/inc

#Compiler
CXX = g++
CXXFLAGS = $(INC) -Wall  -Wfatal-errors
OBJ = $(addprefix $(BUILD)/,$(notdir $(patsubst %.cpp,%.o,$(wildcard $(SRC)))))

#debug
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CXXFLAGS += -DDEBUG -g
endif

VPATH = $(SRC_DIR)

#tasks
all: $(BUILD) $(BUILD)/$(TARGET)
	@echo Success

$(BUILD)/$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -fR $(BUILD)

