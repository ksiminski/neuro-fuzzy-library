/** @file */ 

#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <vector>

namespace ksi
{
    /** The function prints a matrix to an output stream. Values greater or equal the threshold are printed in red, otherwise in yellow.
    @param ss the stream to print to
    @param matrix the matrix to print
    @param threshold the value greater or equal the threshold are printed in red, otherwise in yellow.
    @param width field width a value is printed in
    @param precision precision of a printed value
    @date 2020-11-22
    */
    void print_matrix_color (std::ostream & ss, const std::vector<std::vector<double>> & matrix, const double threshold, const int & width = 5, const int & precision = 2);
}


#endif
