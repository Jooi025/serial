#include "CppLinuxSerial/SerialPort.hpp"
#include <iostream>
#include <fstream> 
#include <vector>
#include <chrono>
#include "matplotlibcpp.h"

#include "gnuplot-iostream.h"

namespace plt = matplotlibcpp;
using namespace mn::CppLinuxSerial;
using namespace std::chrono;


uint64_t timeSinceEpochMicro() {
  using namespace std::chrono;
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}


int main() {
    int BAUDRATE = 560800;
    std::string SERIAL_PORT = "/dev/ttyACM0";

    SerialPort serialPort(SERIAL_PORT, BAUDRATE);
    serialPort.SetTimeout(0); 
    serialPort.Open();

    std::vector <uint8_t> readData;
    std::vector <uint8_t> datas;
    std::vector <uint64_t> times;
    uint64_t startTime = timeSinceEpochMicro();
    time_t elapsedTime = 0; // mirco
    
    int duration = 5; //seconds
    int count = 0;
    while (elapsedTime < duration*1000000){
        serialPort.ReadBinary(readData);
        for(uint8_t data:readData){
            elapsedTime = timeSinceEpochMicro() - startTime;
	        std::cout << "Read data = \"" << (int)data << "\" Time = \"" << elapsedTime << "\"" << std::endl;
            datas.push_back(data);
            times.push_back(elapsedTime);
        }
        readData.clear();
    }
    
    for(int i=0;i<datas.size();i++){
        if (i % 1000 == 0){
            // Clear previous plot
			plt::clf();
			// Plot line from given x and y data. Color is selected automatically.
            plt::plot(times,datas);
			// Add graph title
			plt::title("Sample figure");
			// Display plot continuously
			plt::pause(0.01);
        }
    }

    std::cout << "Closing Serial Port with " << times.size()/duration << " Hz" << count << std::endl;
    serialPort.Close();


    // plt::show();

    // std::ofstream myFile("data/datas.csv");
    // myFile << "Times,Values\n";
    // for(int i=0;i<times.size();i++){
    //     myFile << times[i] << "," << (int)datas[i] << "\n";
    // }
    // myFile.close();


    return 0;
}