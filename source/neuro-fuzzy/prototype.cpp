
#include <vector>
#include <tuple>

#include "../neuro-fuzzy/premise.h"
#include "../neuro-fuzzy/prototype.h"

ksi::prototype::prototype ()
{
}

ksi::prototype::~prototype ()
{
   // delete what is to delete

}

ksi::prototype::prototype (const ksi::prototype & wzor) : ksi::premise(wzor)
{
   // copy what is to copy

}

ksi::prototype & ksi::prototype::operator= (const ksi::prototype & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::premise::operator=(wzor);

   // remove what is to remove

   // allocate what is to allocate

   return *this;
}

ksi::prototype::prototype (ksi::prototype && wzor) : ksi::premise(wzor)
{
   // swap what is to swap

}

ksi::prototype & ksi::prototype::operator= (ksi::prototype && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::premise::operator=(wzor);

   // swap what is to swap

   return *this;
}


double ksi::prototype::getFiringStrength(const std::vector<double>& X)
{
   return last_firingStrength = get_similarity(X);
}

std::ostream & ksi::prototype::Print(std::ostream& ss) const
{
    ss << "(default prototype)";
    return ss;
}
 
double ksi::prototype::distance_to_similarity (const double distance) const
{
    return exp(-distance);
}

std::tuple<double, double, std::vector<double>> ksi::prototype::cardinality_similarities
(const std::vector<std::vector<double>>& X, const std::vector<double> & Y) const 
{
    try 
    {
        auto number_of_data_items = X.size();
        
        double cardinality = 0;
        double average_y_numerator = 0;
        std::vector<double> similarities(number_of_data_items, 0);
            
        for (std::size_t x = 0; x < number_of_data_items; x++)
        {
            auto sim = get_similarity(X[x]);
            similarities[x] = sim;
            cardinality += sim;
            average_y_numerator += sim * Y[x];  
        }
        auto average_y = average_y_numerator / cardinality;  // average of decision attribute for the prototype
        
        return { cardinality, average_y, similarities };
    } CATCH;
}
