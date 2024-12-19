all: serial python plot

serial:src/serial.cpp
	g++ src/serial.cpp -o outputs/serial -lCppLinuxSerial -lpython3.10 -I /usr/include/python3.10

python: src/python.cpp
	g++ src/python.cpp -o outputs/python -L /usr/lib/python3.10 -lpython3.10 -I /usr/include/python3.10

plot: src/plot.cpp
	g++ src/plot.cpp -o outputs/plot -lboost_iostreams -lboost_system -lboost_filesystem


