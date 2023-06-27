/** @file */  
#include "partitioner.h" 
#include "partition.h"


ksi::partitioner::~partitioner()
{
}

std::string ksi::partitioner::getAbbreviation() const
{
   return std::string ("partitioner");
}

int ksi::partitioner::get_number_of_iterations () const 
{
   return _nIterations;
}

int ksi::partitioner::get_number_of_clusters() const
{
   return _nClusters;
}
