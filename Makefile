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

iftests:
	$(MAKE) $(TARGET)
	@echo "	If Statments";
	@echo "[Test 1] if (n == 0) "; $(TARGET) -v $(TESTDIR)/type.tc
	@echo "[Test 2] if ((n*3) == 0) "; $(TARGET) $(TESTDIR)/type1.tc
	@echo "[Test 3] if (n > 0) "; $(TARGET) $(TESTDIR)/type2.tc
	@echo "[Test 4] if (n < 0) "; $(TARGET) $(TESTDIR)/type3.tc
	@echo "[Test 5] if (n <= 0) "; $(TARGET) $(TESTDIR)/type4.tc
	@echo "[Test 6] if (n >= 0) "; $(TARGET) $(TESTDIR)/type5.tc
	@echo "[Test 7] if (n != 0) "; $(TARGET) $(TESTDIR)/type6.tc
	@echo "[Test 8] if (n)"; $(TARGET) $(TESTDIR)/type7.tc

.PHONY: clean
