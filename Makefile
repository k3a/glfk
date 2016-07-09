unix:
	mkdir -p bin build && cd build && cmake .. && $(MAKE)

xcode:
	mkdir -p build/xcode && cd build/xcode && cmake -G Xcode ../..

clean:
	rm -rf bin build
