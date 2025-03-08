#include "project1.hpp"
#include <iostream>

int main() {
    TimeSeries timeSeriesObj;

    std::string input;
    while (true) {
        std::cin >> input;
        if (input == "LOAD") {
        std::string filename;
        std::cin >> filename;
        timeSeriesObj.load(filename);
        }
        else if (input == "PRINT") {
            timeSeriesObj.print();
        }
        else if (input == "ADD") {
            double year;
            double data;
            std::cin >> year;
            std::cin >> data;
            timeSeriesObj.add(year,data);
        }
        else if (input == "UPDATE") {
            double year;
            double data;
            std::cin >> year;
            std::cin >> data;
            timeSeriesObj.update(year,data);
        }
        else if (input == "MEAN") {
            timeSeriesObj.mean();
        }
        else if (input == "MONOTONIC") {
            timeSeriesObj.is_monotonic();
        }
        else if (input == "FIT") {
            double slope = 0;
            double intercept = 0;
            timeSeriesObj.best_fit(slope,intercept);
        }
        else if (input == "EXIT") {
            break;
        }
    }

    return 0;
}
