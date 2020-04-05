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

full:
	$(MAKE) $(TARGET)
	@echo "	Testing Part 1";
	@echo "[Test 1]  "; $(TARGET) -c $(TESTDIR)/full.tc

syn:
	$(MAKE) $(TARGET)
	@echo "	Testing Part 1";
	@echo "[Test 1]  "; $(TARGET) -a $(TESTDIR)/full.tc

pars:
	$(MAKE) $(TARGET)
	@echo "	Testing Part 1";
	@echo "[Test 1]  "; $(TARGET) -p $(TESTDIR)/full.tc

scan0:
	$(MAKE) $(TARGET)
	$ clear
	@echo "	Testing Scanner";
#	@echo "\n[Test 1]  "; $(TARGET) -s0 $(TESTDIR)/test1.tc
#	@echo "                   31 tokens";
	@echo "\n[Test 2]  "; $(TARGET) -s0 $(TESTDIR)/test2.tc
	@echo "            RESULT 1 token";
#	@echo "\n[Test 3]  "; $(TARGET) -s0 $(TESTDIR)/test3.tc
#	@echo "\n[Test 4]  "; $(TARGET) -s0 $(TESTDIR)/test4.tc
#	@echo "                   7 tokens";

scan:
	$(MAKE) $(TARGET)
	$ clear
	@echo "	Testing Scanner";
#	@echo "\n[Test 1]  "; $(TARGET) -s $(TESTDIR)/test1.tc
#	@echo "                   31 tokens";
	@echo "\n[Test 2]  "; $(TARGET) -s $(TESTDIR)/full.tc
	@echo "            RESULT 59 token";
	@echo "\n[Test 2]  "; $(TARGET) -s $(TESTDIR)/test2.tc
	@echo "            RESULT 7 token";
#	@echo "\n[Test 4]  "; $(TARGET) -s $(TESTDIR)/full.tc
#	@echo "            RESULT 1 token";
#	@echo "\n[Test 3]  "; $(TARGET) -s $(TESTDIR)/test3.tc
#	@echo "\n[Test 4]  "; $(TARGET) -s $(TESTDIR)/test4.tc
#	@echo "                   7 tokens";

.PHONY: clean
