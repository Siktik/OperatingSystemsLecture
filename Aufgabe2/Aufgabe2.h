//
// Created by maxsp on 06.11.2024.
//

#ifndef OPERATINGSYSTEMSLECTURE_AUFGABE2_H
#define OPERATINGSYSTEMSLECTURE_AUFGABE2_H
#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>


class Aufgabe2 {
public:
    void runA2();
private:
    void writeToCSV (const std::vector<double>& resultVector, const std::string& filename, const int& amountOfRuns);
    double runLowOverheadSystemCall(int amountIfMultipleTimes);
    double runHighOverheadSystemCall(int amountIfMultipleTimes, const std::string& fileName, bool average);
    void runningMultipleSystemCalls(std::vector<double>& resultVector, const int& size, const int& runs, bool lowOverhead, bool average);
};


#endif //OPERATINGSYSTEMSLECTURE_AUFGABE2_H
