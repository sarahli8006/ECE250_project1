#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "project1.hpp"

void TimeSeries::load(std::string filename) {
    std::ifstream file(filename);
    //read line of file into a string
    std::string line;

    //assign separate vars for index in the row of a file (fileIndex) and index in the time series (seriesIndex)
    int fileIndex = 0;
    int seriesIndex = 0;
    int year = 1960;

    while (std::getline(file, line)) {
        //create string stream from the string
        std::stringstream s_stream(line);
        //read each substring of the line separated by commas into a string
        std::string subLine;
        fileIndex = 0;
        while (std::getline(s_stream, subLine, ',')) {
            if (fileIndex == 2) {
                seriesName = subLine;
                std::cout << seriesName << std::endl;
            }
            else if (fileIndex == 3) {
                seriesCode = subLine;
            }
            else if (fileIndex > 3) {
                if (seriesIndex >= dCap) {
                int newCap = dCap * 2;

                //double years array
                double* newYears = new double[newCap];
                for (int j = 0; j < dCap; j++) {
                    newYears[j] = years[j];
                }
                delete[] years;
                years = newYears;

                //double data array
                double* newData = new double[newCap];
                for (int j = 0; j < dCap; j++) {
                    newData[j] = data[j];
                }
                delete[] data;
                data = newData;
                dCap = newCap;
                }
                if (std::stod(subLine) != -1) { //ignore if data value is invalid
                    years[seriesIndex] = year; //fill in years array with values 1960 to 2023
                    data[seriesIndex] = std::stod(subLine); //convert string to double
                    seriesIndex++;
                }
                year++;
            }
            fileIndex++;
        }
    }

    size = seriesIndex;

    //close file
    file.close();

    std::cout << "success" << std::endl;
}

void TimeSeries::print() {
    if (size == 0) {
        std::cout << "failure" << std::endl;
    }
    else {
        for (int i = 0; i < size; i++) {
            if (data[i] != -1) {
                std::cout << "(" << years[i] << "," << data[i] << ") ";
            }
        }
        std::cout << "" << std::endl;
    }
}

void TimeSeries::add(double y, double d) {
    bool existingData = false;
        //check if that year already exists in time series
        for (int i = 0; i < size; i++) {
            if (years[i] == y) {
                existingData = true;
            }
        }
        //if year doesn't already exist, create new arrays and copy elements in
        if (!existingData) {
            if (size == dCap) {
                int newCap = dCap + 1;
                double* newYears = new double[newCap];
                double* newData = new double[newCap];

                for (int i = 0; i < size; i++) {
                newYears[i] = years[i];
                newData[i] = data[i];
                }

                delete[] years;
                delete[] data;
                years = newYears;
                data = newData;
                dCap = newCap;
            }

            int index = 0;
            while (y > years[index] && index < size) {
                index++;
            }
            for (int i = size; i > index; i--) {
                years[i] = years[i - 1];
                data[i] = data[i - 1];
            }
            years[index] = y;
            data[index] = d;
            if (d != -1) {
                size++;
            }
            std::cout << "success" << std::endl;
        }
        else {
            std::cout << "failure" << std::endl;
        }
}

void TimeSeries::update(double y, double d) {

    bool existingData = false;
    //check if that year already exists in time series
    for (int i = 0; i < size; i++) {
        if (years[i] == y) {
            existingData = true;

            //remove element if user inputs invalid data
            if (d == -1) {
                for (int j = i; j < size - 1; j++) { //shift everything to the left
                    years[j] = years[j + 1];
                    data[j] = data[j + 1];
                }
                size--;

                //resize array to be 1/2 of original capacity if number of elements in array is less than or equal to 1/4 of the original capacity
                if (size <= dCap / 4) {
                    int newCap = dCap / 2;
                    double* newYears = new double[newCap];
                    double* newData = new double[newCap];

                    for (int j = 0; j < size; j++) {
                        newYears[j] = years[j];
                        newData[j] = data[j];
                    }

                    delete[] years;
                    delete[] data;

                    years = newYears;
                    data = newData;
                    dCap = newCap;
                }
            }
            else {
                years[i] = y;
                data[i] = d;
            }
            std::cout << "success" << std::endl;
        }
    }
    if (!existingData) {
        std::cout << "failure" << std::endl;
    }
}

double TimeSeries::mean() {
    double M = 0;
    if (size == 0) {
        std::cout << "failure" << std::endl;
        return 0;
    }
    else {
        for (int i = 0; i < size; i++) { //sum up all elements of array and divide by array size
            M += data[i];
        }
        M /= size;
        std::cout << "mean is " << M << std::endl;
        return M;
    }
}

bool TimeSeries::is_monotonic() {
    if (size == 0) {
        std::cout << "failure" << std::endl;
        return false;
    }
    bool increasing = true;
    bool decreasing = true;
    for (int i = 0; i < size - 1; i++) {
        if (data[i] >= data[i+1]) { //check if data is increasing
            increasing = false;
        }
        else if (data[i] <= data[i+1] ){ //check if data is decreasing
            decreasing = false;
        }
    }
    if (increasing || decreasing) {
        std::cout << "series is monotonic" << std::endl;
        return true;
    }
    else {
        std::cout << "series is not monotonic" << std::endl;
        return false;
    }
}

void TimeSeries::best_fit (double &m, double &b) {
    if (size == 0) {
        std::cout << "failure" << std::endl;
        m = 0;
        b = 0;
    }
    else {
        //m is slope, b is y-intercept
        double term1 = 0;
        double term2 = 0;
        double term3 = 0;
        double term4 = 0;
        double term5 = 0;

        for (int i = 0; i < size; i++) {
            term1 += years[i] * data[i];
            term2 += years[i];
            term3 += data[i];
            term4 += years[i] * years[i];
        }
        term5 =  term2;
        term1 *= size;
        term4 *= size;
        term5 *= term5;

        if (term4 - term5 == 0) {
            std::cout << "failure" << std::endl;
            m = 0;
            b = 0;
        }

        m = (term1 - (term2 * term3)) / (term4 - term5);
        b = (term3 - (m * term2)) / size;

        std::cout << "slope is " << m << " intercept is " << b << std::endl;
    }
}

//https://www.geeksforgeeks.org/how-to-dynamically-allocate-an-array-in-cpp/
