

#include <iostream>
#include <iomanip>

#include "../auxiliary/print.h"
#include "../auxiliary/colours.h"

void ksi::print_matrix_color (std::ostream & ss, const std::vector<std::vector<double>> & matrix, const double threshold, const int & width, const int & precision)
{
    for (const auto & w : matrix)
    {
        for (const auto & d : w)
        {
            if (d > threshold)
            {
                ss << ksi::eColour::DRUK_JASNY_red;
            }
            else
            {
                ss << ksi::eColour::DRUK_JASNY_yellow;
            }
            ss << std::setw(width) << std::setprecision(precision) << std::fixed << d;
            ss << ksi::eColour::DRUK_default;
        }
        ss << std::endl;
    }
}
