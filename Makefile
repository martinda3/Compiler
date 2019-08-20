APP := application

CXX := g++
CXXFLAGS := -Wall -g

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(APP)

$(APP): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(APP) $(OBJ)
	$(info Making!)

.PHONY: clean
clean:
	rm -f $(OBJ) $(APP)
	$(info Cleaning!)
