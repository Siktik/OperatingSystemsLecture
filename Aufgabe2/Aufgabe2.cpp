//
// Created by maxsp on 06.11.2024.
//

#include "Aufgabe2.h"

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


double Aufgabe2::runLowOverheadSystemCall(int amountIfMultipleTimes){

    LARGE_INTEGER frequency, start, end;
    FILETIME fileTime;

    std::cout << "############################################"
                 "\n\trunning Low Overhead System Call MultipleTimes (x"<<amountIfMultipleTimes<<")\n"
                                                                                                 "############################################\n";

    // Get the high-resolution timer frequency
    QueryPerformanceFrequency(&frequency);

    // Measure latency of GetSystemTimeAsFileTime system call
    QueryPerformanceCounter(&start);

    for(int i=0; i < amountIfMultipleTimes; i++) {
        GetSystemTimeAsFileTime(&fileTime);
    }
    QueryPerformanceCounter(&end);
    // Calculate elapsed time in microseconds

    return static_cast<double>(end.QuadPart - start.QuadPart) * 1e6 / frequency.QuadPart;



}


double Aufgabe2::runHighOverheadSystemCall(int amountIfMultipleTimes, const std::string& fileName, bool average){
    LARGE_INTEGER frequency, start, end;

    std::cout << "############################################"
                 "\nrunning High Overhead System Call MultipleTimes (x"<<amountIfMultipleTimes<<")\n"
                                                                                                "############################################\n";

    // Get the high-resolution timer frequency
    QueryPerformanceFrequency(&frequency);

    std::vector<double> result;

    for (int i = 0; i < amountIfMultipleTimes; ++i) {
        // Start timing
        QueryPerformanceCounter(&start);

        // Create a file and immediately close it
        HANDLE fileHandle = CreateFile(
                fileName.c_str(),            // File name
                GENERIC_WRITE,               // Desired access
                0,                           // Share mode
                NULL,                        // Security attributes
                CREATE_ALWAYS,               // Creation disposition
                FILE_ATTRIBUTE_NORMAL,       // Flags and attributes
                NULL                         // Template file handle
        );

        // Stop timing
        QueryPerformanceCounter(&end);
        result.push_back(static_cast<double>(end.QuadPart - start.QuadPart) * 1e6 / frequency.QuadPart);


        if (fileHandle != INVALID_HANDLE_VALUE) {
            CloseHandle(fileHandle);      // Close the file
            DeleteFile(fileName.c_str()); // Optionally delete the file after creation
        } else {
            std::cerr << "Failed to create file on iteration " << i + 1 << std::endl;
            continue;
        }

    }
    if(average)    //it turns out the values are so small, averaging them will result in 0 microseconds as a lot values are smaller than 0.1 microseconds which is the precision here
        return std::accumulate(result.begin(), result.end(), 0.0) / amountIfMultipleTimes;
    else
        return result[0];
}




void Aufgabe2::runningMultipleSystemCalls(std::vector<double>& resultVector, const int& size, const int& runs, bool lowOverhead, bool average){

    if(lowOverhead) {
        for (int i = 0; i < size; i++) {
            resultVector[i] = runLowOverheadSystemCall(runs);
        }
    }else{
        for (int i = 0; i < size; i++) {
            resultVector[i] = runHighOverheadSystemCall(runs, "testfile.txt", average);
        }
    }

}

void Aufgabe2::writeToCSV (const std::vector<double>& resultVector, const std::string& filename, const int& amountOfRuns){
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



void Aufgabe2::runA2() {
    int amountOfRuns = 50; //eg size of vector
    std::vector<double> resultVector(amountOfRuns);
    runningMultipleSystemCalls(resultVector, amountOfRuns, 1, true, false);
    //writeToCSV(resultVector, "lowOverheadSingleRun.csv", amountOfRuns);
    runningMultipleSystemCalls(resultVector, amountOfRuns, 1, false, false);
    //writeToCSV(resultVector, "highOverheadMultipleRuns.csv", amountOfRuns);
    runningMultipleSystemCalls(resultVector, amountOfRuns, 10, false, true);
    //writeToCSV(resultVector, "highOverheadMultipleRunsAVG.csv", amountOfRuns);

}
