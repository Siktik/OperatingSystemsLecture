//
// Created by maxsp on 05.11.2024.
//

#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "Aufgabe2/Aufgabe2.h"
#include <chrono>
#include <thread>  // For sleep




void writeToCSV (const std::vector<double>& resultVector, const std::string& filename, const int& amountOfRuns){
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }


    for (size_t i = 0; i < amountOfRuns; ++i) {
        file << std::fixed << std::setprecision(1) << resultVector[i];
        if (i < amountOfRuns - 1) {
            file << ";"; // Add a comma after each element except the last one
        }
    }

    file.close();
}

double firstApproach (){
    const int iterations = 10000; // Number of measurements
    std::chrono::nanoseconds total_duration(0);

    for (int i = 0; i < iterations; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::nanoseconds(0)); // Yield the CPU
        auto end_time = std::chrono::high_resolution_clock::now();

        total_duration += (end_time - start_time);
    }

    double average_context_switch_time =
            static_cast<double>(total_duration.count()) / iterations; // Nanoseconds

    //std::cout << "Average context switch time: "
    //          << average_context_switch_time
    //          << " nanoseconds." << std::endl;
    return average_context_switch_time;
}




int main() {
    //Aufgabe2 a2;
    //a2.runA2();


    //Aufgabe 3
    int amountOfRuns = 1000;
    std::vector<double> results (amountOfRuns);
    for(int i =0; i< amountOfRuns; i++){
        results[i] = firstApproach();
    }
    writeToCSV(results, "test.csv", amountOfRuns);




    return 0;
}



