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
	$(MAKE) $(TARGET2)
	@echo "	Passed if no scanner output";
	@echo "[Test  1]"; $(TARGET) $(TESTDIR)/one.tc
	@echo "[Test  2]"; $(TARGET) $(TESTDIR)/two.tc
	@echo "[Test  3]"; $(TARGET) $(TESTDIR)/three.tc
	@echo "[Test  4]"; $(TARGET) $(TESTDIR)/four.tc
	@echo "[Test  6]"; $(TARGET) $(TESTDIR)/five.tc
	@echo "[Test  7]"; $(TARGET) $(TESTDIR)/six.tc
	@echo "[Test  8]"; $(TARGET) $(TESTDIR)/eight.tc
	@echo "[Test  9]"; $(TARGET) $(TESTDIR)/nine.tc
	@echo "[Test 10]"; $(TARGET) $(TESTDIR)/ten.tc
	@echo "[Test 11]"; $(TARGET) $(TESTDIR)/eleven.tc
	@echo "[Test 12]"; $(TARGET) $(TESTDIR)/twelve.tc
	@echo "[Test 13]"; $(TARGET) $(TESTDIR)/thirteen.tc
	@echo "[Test 14]"; $(TARGET) $(TESTDIR)/fourteen.tc
	@echo "[Test 16]"; $(TARGET) $(TESTDIR)/six_1.tc
	@echo "[Test 17]"; $(TARGET) $(TESTDIR)/six_2.tc
	@echo "[Test 18]"; $(TARGET) $(TESTDIR)/six_3.tc
	@echo "[Test 19]"; $(TARGET) $(TESTDIR)/six_4.tc
	@echo "[Test  1]"; $(TARGET) -v $(TESTDIR)/one.tc
	@echo "  [CHECKER] Correct Total: 7";
	@echo "[Test  2]"; $(TARGET) -v $(TESTDIR)/two.tc
	@echo "  [CHECKER] Correct Total: 17";
	@echo "[Test  3]"; $(TARGET) -v $(TESTDIR)/three.tc
	@echo "  [CHECKER] Correct Total: 4";
	@echo "[Test  4]"; $(TARGET) -v $(TESTDIR)/four.tc
	@echo "  [CHECKER] Correct Total: 1";
	@echo "[Test  6]"; $(TARGET) -v $(TESTDIR)/five.tc
	@echo "  [CHECKER] Correct Total: 9";
	@echo "[Test  7]"; $(TARGET) -v $(TESTDIR)/six.tc
	@echo "  [CHECKER] Correct Total: 3";
	@echo "[Test  8]"; $(TARGET) -v $(TESTDIR)/eight.tc
	@echo "  [CHECKER] Correct Total: 3";
	@echo "[Test  9]"; $(TARGET) -v $(TESTDIR)/nine.tc
	@echo "  [CHECKER] Correct Total: 7";
	@echo "[Test 10]"; $(TARGET) -v $(TESTDIR)/ten.tc
	@echo "  [CHECKER] Correct Total: 4";
	@echo "[Test 11]"; $(TARGET) -v $(TESTDIR)/eleven.tc
	@echo "  [CHECKER] Correct Total: 5";
	@echo "[Test 12]"; $(TARGET) -v $(TESTDIR)/twelve.tc
	@echo "  [CHECKER] Correct Total: 2";
	@echo "[Test 13]"; $(TARGET) -v $(TESTDIR)/thirteen.tc
	@echo "  [CHECKER] Correct Total: 11";
	@echo "[Test 14]"; $(TARGET) -v $(TESTDIR)/fourteen.tc
	@echo "  [CHECKER] Correct Total: 1 & 6 Warnings";
	@echo "[Test 16]"; $(TARGET) -v $(TESTDIR)/six_1.tc
	@echo "  [CHECKER] Correct Total: 7 & 1 Warning";
	@echo "[Test 17]"; $(TARGET) -v $(TESTDIR)/six_2.tc
	@echo "  [CHECKER] Correct Total: 4 & 1 Warning";
	@echo "[Test 18]"; $(TARGET) -v $(TESTDIR)/six_3.tc
	@echo "  [CHECKER] Correct Total: 4";
	@echo "[Test 19]"; $(TARGET) -v $(TESTDIR)/six_4.tc
	@echo "  [CHECKER] Correct Total: 6";
	@echo "PASSED ALL TESTS FOR PART 1";

part2:
	$(MAKE) $(TARGET)
	@echo "	Passed if no scanner output";
	@echo "[factorial.tc]"; $(TARGET) -v $(TESTDIR)/factorial.tc
	@echo "[test1.tc]"; $(TARGET) -v $(TESTDIR)/test1.tc
	@echo "[test1a.tc]"; $(TARGET) -v $(TESTDIR)/test1a.tc
	@echo "[test1b.tc]"; $(TARGET) -v $(TESTDIR)/test1b.tc
	@echo "[test1c.tc]"; $(TARGET) -v $(TESTDIR)/test1c.tc
	@echo "[test2.tc]"; $(TARGET) -v $(TESTDIR)/test2.tc
	@echo "[test3.tc]"; $(TARGET) -v $(TESTDIR)/test3.tc
	@echo "[test4.tc]"; $(TARGET) -v $(TESTDIR)/test4.tc
	@echo "[test5.tc]"; $(TARGET) -v $(TESTDIR)/test5.tc
	@echo "[test6.tc]"; $(TARGET) -v $(TESTDIR)/test6.tc
	@echo "[test7.tc]"; $(TARGET) -v $(TESTDIR)/test7.tc
	@echo "[test8.tc]"; $(TARGET) -v $(TESTDIR)/test8.tc
	@echo "[test9.tc]"; $(TARGET) -v $(TESTDIR)/test9.tc
	@echo "[test10.tc]"; $(TARGET) -v $(TESTDIR)/test10.tc
	@echo "[scanTest1.tc]"; $(TARGET) -v $(TESTDIR)/scanTest1.tc
	@echo "[Test 20]"; $(TARGET) -v $(TESTDIR)/p1tokens.tc
	@echo "  [CHECKER] Correct Total: ??";

.PHONY: clean
