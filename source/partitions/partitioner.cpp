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
