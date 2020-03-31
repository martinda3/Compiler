CC := g++ # This is the main compiler

SRCDIR := src
INCDIR := include
TESTDIR := new_tests
BUILDDIR := build
JVMDIR := /JVM
JVMINSTRUCTDIR := /JVM/instruction
JVMLABELDIR := /JVM/label
JVMMETADIR := /JVM/meta
JVMDIRECTIVEDIR := /JVM/directive
TARGET := bin/tc

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB := -L lib
INC := -I include -I include$(JVMDIR) -I include$(JVMINSTRUCTDIR) -I include$(JVMLABELDIR) -I include$(JVMMETADIR) -I include$(JVMDIRECTIVEDIR)
_DEPS := *.h
DEPS := $(patsubst %,$(INCDIR)/%,$(_DEPS))
TESTFILES := $(wildcard $(TESTDIR)/*.tc)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(TARGET)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(DEPS)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)$(JVMINSTRUCTDIR)
	@mkdir -p $(BUILDDIR)$(JVMLABELDIR)
	@mkdir -p $(BUILDDIR)$(JVMMETADIR)
	@mkdir -p $(BUILDDIR)$(JVMDIRECTIVEDIR)
	@echo " $(CC) $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) "; $(RM) -r $(BUILDDIR) $(TARGET)

test1:
	$(MAKE) $(TARGET)
	@echo "	Testing Part 1";
	@echo "[Test 1]  "; $(TARGET) - $(TESTDIR)/test1.tc -d 1
	@echo "	46 tokens";
	@echo "	Part 1 Passed";

scan:
	$(MAKE) $(TARGET)
	@echo "	Testing Part 1";
	@echo "[Test 1]  "; $(TARGET) -v $(TESTDIR)/test1.tc
	@echo "                   31 tokens";
	@echo "[Test 2]  "; $(TARGET) -v $(TESTDIR)/test2.tc
	@echo "                   FAILED";
	@echo "[Test 3]  "; $(TARGET) -v $(TESTDIR)/test3.tc
	@echo "[Test 4]  "; $(TARGET) -v $(TESTDIR)/test4.tc
	@echo "                   FAILED";

part1:
	$(MAKE) $(TARGET)
	@echo "	Testing Part 1";
	@echo "[Test 1]  "; $(TARGET) - $(TESTDIR)/pt2.tc -d 1
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
