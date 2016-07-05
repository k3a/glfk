
all:
	mkdir -p bin build && cd build && cmake .. && $(MAKE)

clean:
	rm -rf bin build
