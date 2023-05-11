/** @file */ 

#include <vector>
#include <sstream>
#include <cmath>

#include "error-calculator.h"
#include "error-MAE.h"
#include "../service/debug.h"
#include "../common/number.h"

ksi::error_calculator * ksi::error_MAE::clone() const
{
   return new error_MAE();
}
 
ksi::error_MAE::~error_MAE()
{

}

double ksi::error_MAE::getError(const std::vector< double >& expected, 
		const std::vector< double >& elaborated)
{
	try
	{
		if (expected.size() != elaborated.size())
		{
			std::stringstream ss;
			ss << "The dimensions of vectors do not match: "
				<< expected.size() << " != " 
				<< elaborated.size() << ".";

			throw ss.str();
		}
		else
		{
			std::size_t size = expected.size();
			double suma = 0.0;

#pragma omp parallel for reduction (+ : suma) 
			for (std::size_t i = 0; i < size; i++)
				suma += fabs(expected[i] - elaborated[i]);

			return suma / size;
		}
	}
	CATCH;
}


double ksi::error_MAE::getError(const std::vector< double >     & expected, 
		const std::vector< ksi::number >& elaborated)
{
	try
	{
		if (expected.size() != elaborated.size())
		{
			std::stringstream ss;
			ss << "The dimensions of vectors do not match: "
				<< expected.size() << " != " 
				<< elaborated.size() << ".";

			throw ss.str();
		}
		else
		{
			std::size_t size = expected.size();
			double suma = 0.0;
			std::size_t counter { 0 };

#pragma omp parallel for reduction (+ : suma) 
			for (std::size_t i = 0; i < size; i++)
			{
				if (elaborated[i].exists())
				{
					double lower = elaborated[i].getValue();
					double upper = elaborated[i].getUpperValue();

					if (not elaborated[i].isInterval())
						upper = lower;

					double roznica = std::max(expected[i] - lower, expected[i] - upper);
					suma +=  roznica;

					counter++;
				} 
			}
			if (counter == 0)
			{
				throw std::string ("Vector of elaborated values holds only non-existing numbers!");
			}
			return suma / counter;
		}
	}
	CATCH;
}

double ksi::error_MAE::getError(const std::vector<ksi::number>& elaborated, const std::vector<double>& expected)
{
	return getError(expected, elaborated);
}

