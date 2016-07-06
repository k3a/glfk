unix:
	mkdir -p bin build && cd build && cmake .. && $(MAKE)

xcode:
	mkdir -p build/xcode && cd build/xcode && cmake -G Xcode ../..

vs:
	mkdir -p build/vs && cd build/vs && cmake -G 'Visual Studio 9 2008' ../..

clean:
	rm -rf bin build
