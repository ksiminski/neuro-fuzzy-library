/** @file */  

#include <string>
#include "partitioner.h"
#include "partitioner-grid.h" 
#include "partition.h"
#include "../descriptors/descriptor.h"
#include "../descriptors/descriptor-triangular.h"
#include "../descriptors/descriptor-semitriangular.h"
#include "../common/dataset.h"

std::string ksi::partitioner_grid::getAbbreviation() const
{
   return std::string ("partitioner_grid");
}


ksi::partitioner_grid::~partitioner_grid()
{
}

ksi::partitioner_grid::partitioner_grid (int number_of_intervals)
{
   _number_of_intervals = number_of_intervals;
}

ksi::partitioner_grid::partitioner_grid()
{
   _number_of_intervals = 0;
}


ksi::partitioner * ksi::partitioner_grid::clone() const
{
   return new ksi::partitioner_grid (_number_of_intervals);
}


ksi::partition ksi::partitioner_grid::doPartition(const ksi::dataset & ds)
{
   throw std::string ("not implemented yet");
   
   // TODO dokonczyc te metode. 
   
   
   
   
   return ksi::partition();
}

