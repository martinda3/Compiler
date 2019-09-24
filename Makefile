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

tests:
	$(MAKE) $(TARGET)
	@echo ". . . . . . . . .";
	@echo " #1"  $(TESTDIR)/one.tc "...";
	$(TARGET) $(TESTDIR)/one.tc
	@echo "  [CHECKER]  Total tokens: 6";
	@echo ". . . . . . . . .";
	@echo " #2"  $(TESTDIR)/two.tc "...";
	$(TARGET) $(TESTDIR)/two.tc
	@echo "  [CHECKER]  Total tokens: 17";
	@echo ". . . . . . . . .";
	@echo " #3"  $(TESTDIR)/three.tc "...";
	$(TARGET) $(TESTDIR)/three.tc
	@echo "  [CHECKER]  Total tokens: 3";
	@echo ". . . . . . . . .";
	@echo " #4"  $(TESTDIR)/four.tc "...";
	$(TARGET) $(TESTDIR)/four.tc
	@echo "  [CHECKER]  Total tokens: 1";
	@echo ". . . . . . . . .";
	@echo " #6"  $(TESTDIR)/five.tc "...";
	$(TARGET) $(TESTDIR)/five.tc
	@echo "  [CHECKER]  Total tokens: 9";
	@echo ". . . . . . . . .";
	@echo " #7"  $(TESTDIR)/six.tc "...";
	$(TARGET) $(TESTDIR)/six.tc
	@echo "  [CHECKER]  Total tokens: 3";
	@echo ". . . . . . . . .";
	@echo " #8"  $(TESTDIR)/eight.tc "...";
	$(TARGET) $(TESTDIR)/eight.tc
	@echo "  [CHECKER]  Total tokens: 3";
	@echo ". . . . . . . . .";
	@echo " #9"  $(TESTDIR)/nine.tc "...";
	$(TARGET) $(TESTDIR)/nine.tc
	@echo "  [CHECKER]  Total tokens: 7";
	@echo ". . . . . . . . .";
	@echo " #10"  $(TESTDIR)/ten.tc "...";
	$(TARGET) $(TESTDIR)/ten.tc
	@echo "  [CHECKER]  Total tokens: 4";
	@echo ". . . . . . . . .";
	@echo " #11"  $(TESTDIR)/eleven.tc "...";
	$(TARGET) $(TESTDIR)/eleven.tc
	@echo "  [CHECKER]  Total tokens: 5";
	@echo ". . . . . . . . .";
	@echo " #12"  $(TESTDIR)/twelve.tc "...";
	$(TARGET) $(TESTDIR)/twelve.tc
	@echo "  [CHECKER]  Total tokens: 2";
	@echo ". . . . . . . . .";
	@echo " #13"  $(TESTDIR)/thirteen.tc "...";
	$(TARGET) $(TESTDIR)/thirteen.tc
	@echo "  [CHECKER]  Total tokens: 11";
	@echo ". . . . . . . . .";
	@echo " #14"  $(TESTDIR)/fourteen.tc "...";
	$(TARGET) -v $(TESTDIR)/fourteen.tc
	@echo "  [CHECKER]  Total tokens: 1";
	@echo ". . . . . . . . .";
	@echo "All Have Succeded";

fails:
	$(MAKE) $(TARGET)
	@echo ". . . . . . . . .";
	@echo " #6"  $(TESTDIR)/six_1.tc "...";
	$(TARGET) -v $(TESTDIR)/six_1.tc
	@echo "  [CHECKER]  Total tokens: 1";
	@echo ". . . . . . . . .";

.PHONY: clean
