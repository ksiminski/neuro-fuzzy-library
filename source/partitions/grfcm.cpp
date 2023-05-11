/** @file */ 

#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>

#include "../common/dataset.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../readers/reader-complete-by-parts.h"
#include "partitioner.h"
#include "partition.h"
#include "fcm.h"
#include "fcm-T.h"
#include "grfcm.h"
#include "../service/debug.h"

std::string ksi::grfcm::getAbbreviation() const
{
   return std::string ("granular fcm");
}

ksi::partitioner * ksi::grfcm::clone() const
{
   return new ksi::grfcm(*this);
}

ksi::grfcm::grfcm(const ksi::grfcm & wzor) : fcm_T<ext_fuzzy_number_gaussian> (wzor)
{
    _max_number_of_dataitems_in_a_part = wzor._max_number_of_dataitems_in_a_part;
    _input_file_name = wzor._input_file_name;
}

ksi::grfcm::grfcm(ksi::grfcm && wzor) : fcm_T<ext_fuzzy_number_gaussian> (wzor)
{
    std::swap (_max_number_of_dataitems_in_a_part, wzor._max_number_of_dataitems_in_a_part);
    std::swap(_input_file_name, wzor._input_file_name);
}


ksi::grfcm & ksi::grfcm::operator=(ksi::grfcm && wzor)
{
    if (this == & wzor)
      return *this;
   
   ksi::fcm_T<ext_fuzzy_number_gaussian>::operator=(wzor);   
   
   std::swap (_max_number_of_dataitems_in_a_part, wzor._max_number_of_dataitems_in_a_part);
   std::swap(_input_file_name, wzor._input_file_name);
   
   return *this;
}




ksi::grfcm & ksi::grfcm::operator=(const ksi::grfcm & wzor)
{
   if (this == & wzor)
      return *this;
   
   ksi::fcm_T<ext_fuzzy_number_gaussian>::operator=(wzor); 
   
   _max_number_of_dataitems_in_a_part = wzor._max_number_of_dataitems_in_a_part;
   _input_file_name = wzor._input_file_name;
   
   return *this;
}


ksi::grfcm::grfcm(const int MAXIMAL_NUMBER_OF_DATAITEMS_IN_A_PART, const std::string & INPUT_FILE_NAME, const double EPSILON)
{
    _max_number_of_dataitems_in_a_part = MAXIMAL_NUMBER_OF_DATAITEMS_IN_A_PART;
    _input_file_name = INPUT_FILE_NAME;
    setEpsilonForFrobeniusNorm(EPSILON);
}


ksi::grfcm::~grfcm()
{
}

ksi::partition ksi::grfcm::doPartition(const ksi::dataset& ds)
{
    const int INTERNAL_NUMBER_OF_CLUSTERS = _nClusters;// * 2;
    const int THRESHOLD_MAX = std::max(_max_number_of_dataitems_in_a_part / 2, INTERNAL_NUMBER_OF_CLUSTERS);
    const int THRESHOLD_MIN = _nClusters * 10;
    
    ksi::reader_complete_by_parts input (_input_file_name);
    
    ksi::partition podzial;
    std::vector<ksi::partition> granule_sets;
   
    bool exist_more_data = true;
   
    setNumberOfClusters(INTERNAL_NUMBER_OF_CLUSTERS);
   
    int number_of_chunks = 1;
    while (exist_more_data)
    {
//        debug(number_of_chunks);
       auto data = input.read_part(_max_number_of_dataitems_in_a_part);
       number_of_chunks++;
       if (data.getNumberOfData() > 0)
       {
           auto podzial = ksi::fcm_T<ext_fuzzy_number_gaussian>::doPartition(data);
           if (granule_sets.empty())
               granule_sets.push_back(podzial);
           else
               granule_sets[0] += podzial;
           
           for (std::size_t it = 0; it < granule_sets.size(); it++)
           {
//               debug(it);
               if (granule_sets[it].getNumberOfClusters() > THRESHOLD_MAX)
               {
//                   debug(granule_sets[it].getNumberOfClusters());
                   auto granules = granule_sets[it].getGranules();
                   ksi::dataset granulated_dataset (granules);
                   auto clusters = ksi::fcm_T<ext_fuzzy_number_gaussian>::doPartition(granulated_dataset);
                   
                   if (it + 1 < granule_sets.size())
                       granule_sets[it + 1] += clusters;
                   else
                       granule_sets.push_back(clusters);
                   granule_sets[it] = ksi::partition{};
               }
           }
       }
       else 
           exist_more_data = false;
     }
     
     
     // all data already read 
     for (std::size_t i = 0; i < granule_sets.size(); i++)
     {
         if (granule_sets[i].getNumberOfClusters() > THRESHOLD_MIN)
         {
             auto granules = granule_sets[i].getGranules();
             ksi::dataset granulated_dataset (granules);
             auto clusters = ksi::fcm_T<ext_fuzzy_number_gaussian>::doPartition(granulated_dataset);
             
             if (i + 1 < granule_sets.size())
             {
                 granule_sets[i + 1] += clusters;
                 granule_sets[i] = ksi::partition();
             }
             else
                 granule_sets.push_back(clusters);
         }
         else 
         {
             if (i + 1 < granule_sets.size())
                granule_sets[i + 1] += granule_sets[i];
         }
     }
    
    if (granule_sets.back().getNumberOfClusters() > _nClusters)
    {
       setNumberOfClusters(_nClusters);
       auto granules = granule_sets.back().getGranules();
       ksi::dataset granulated_dataset (granules);
       auto clusters = ksi::fcm_T<ext_fuzzy_number_gaussian>::doPartition(granulated_dataset);
       granule_sets.push_back(clusters);
    }  
    
    return granule_sets.back();
}

