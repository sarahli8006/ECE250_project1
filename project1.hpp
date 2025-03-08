#ifndef PROJECT1_HPP
#define PROJECT1_HPP
#include <string>

class TimeSeries {
    private:
        std::string seriesName;
        std::string seriesCode;
        int yCap = 2;
        int dCap = 2;
        double* years;
        double* data;
        int size = 0;

    public:
    //constructor
    TimeSeries() {
        years = new double[yCap];
        data  = new double[dCap];
    }

    //destructor
    ~TimeSeries() {
        delete[] years;
        delete[] data;
        years = nullptr;
        data = nullptr;
    }

    void load(std::string filename);

    void print();

    void add(double y, double d);

    void update(double y, double d);

    double mean();

    bool is_monotonic();

    void best_fit (double &m, double &b);
};

#endif
