CC := g++ # This is the main compiler

SRCDIR := src
INCDIR := include
TESTDIR := test
BUILDDIR := build
TARGET := bin/tc

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB := -L lib
INC := -I include
_DEPS := *.h
DEPS := $(patsubst %,$(INCDIR)/%,$(_DEPS))
TESTFILES := $(wildcard $(TESTDIR)/*.tc)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(SCANNER): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(SCANNER) $(LIB)"; $(CC) $^ -o $(SCANNER) $(LIB)

$(PARSER): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(PARSER) $(LIB)"; $(CC) $^ -o $(PARSER) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPS)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(SCANNER) $(PARSER)"; $(RM) -r $(BUILDDIR) $(TARGET) $(SCANNER) $(PARSER)

part1:
	$(MAKE) $(TARGET)
	@echo "	Testing Part 1";
	@echo "[Test 1]  "; $(TARGET) - $(TESTDIR)/p1_test.tc -d 1
	@echo "	46 tokens";
	@echo "	Part 1 Passed";

part2:
	$(MAKE) $(TARGET)
	@echo "	Testing Part 2";
	@echo "[Test 1]  "; $(TARGET) -v $(TESTDIR)/p2_test.tc
	@echo "	Part 2 Passed";

part2a:
	$(MAKE) $(TARGET)
	@echo "	Testing Abstract Syntax";
	@echo "[Test 1]  "; $(TARGET) - $(TESTDIR)/p2_test.tc -d 3
	@echo "	Abstract Syntax Passed";

.PHONY: clean
