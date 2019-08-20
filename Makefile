src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

run: $(obj)
	$(CC) -o $@ $^ 

.PHONY: clean
clean:
	rm -f $(obj) run
