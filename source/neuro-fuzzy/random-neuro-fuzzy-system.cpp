/** @file */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "neuro-fuzzy-system.h" 
#include "random-neuro-fuzzy-system.h"
#include "../service/debug.h"


void ksi::random_neuro_fuzzy_system::copy_fields(const ksi::random_neuro_fuzzy_system& source)
{
   _attribute_indices = source._attribute_indices;
   _data_indices = source._data_indices;
}
 
ksi::random_neuro_fuzzy_system::~random_neuro_fuzzy_system()
{
   delete _nfs;
   _nfs = nullptr;
}
 
ksi::random_neuro_fuzzy_system::random_neuro_fuzzy_system()
{
   _nfs = nullptr;
}

ksi::random_neuro_fuzzy_system::random_neuro_fuzzy_system (const ksi::random_neuro_fuzzy_system & wzor)
{
   _nfs = wzor._nfs->clone();
   
   copy_fields(wzor);
}


ksi::random_neuro_fuzzy_system::random_neuro_fuzzy_system(ksi::random_neuro_fuzzy_system && wzor)
{
   std::swap(_nfs, wzor._nfs);
   
   std::swap (_attribute_indices, wzor._attribute_indices);
   std::swap (_data_indices, wzor._data_indices);
   
}

ksi::random_neuro_fuzzy_system& ksi::random_neuro_fuzzy_system::operator= (const ksi::random_neuro_fuzzy_system & wzor)
{
   if (this == & wzor)
      return *this;
   
   if (_nfs)
      delete _nfs;
   _nfs = wzor._nfs->clone();
   
   _attribute_indices = wzor._attribute_indices;
   _data_indices = wzor._data_indices;
   
   return *this;
}


ksi::random_neuro_fuzzy_system & ksi::random_neuro_fuzzy_system::operator= (ksi::random_neuro_fuzzy_system && wzor)
{
   if (this == & wzor)
      return *this;
   
   std::swap(_nfs, wzor._nfs);
   std::swap(_data_indices, wzor._data_indices);
   std::swap(_attribute_indices, wzor._attribute_indices);
   
   return *this;
}
 
ksi::random_neuro_fuzzy_system::random_neuro_fuzzy_system (
   const ksi::neuro_fuzzy_system & nfs, 
   const std::unordered_multiset<std::size_t> & data_indices, 
   const std::vector<bool> & attribute_pattern)
{
   _nfs = nfs.clone();
   _data_indices = data_indices;
   _attribute_indices = attribute_pattern; 
   
}

void ksi::random_neuro_fuzzy_system::train(ksi::dataset abridged_data, 
                                           int nClusteringIterations, 
                                           int nTuningIterations, 
                                           int nRules, double dbLearningCoefficient)
{
   try
   {
      _nfs->createFuzzyRulebase(nRules, nClusteringIterations, nTuningIterations, dbLearningCoefficient, abridged_data);
   }
   CATCH;
}

std::vector<bool> ksi::random_neuro_fuzzy_system::get_attribute_indices() const
{
   return _attribute_indices;
}

ksi::number ksi::random_neuro_fuzzy_system::answer(const ksi::datum & d) const
{
   try
   {
      return _nfs->elaborate_answer(d);
   }
   CATCH;
}

std::string ksi::random_neuro_fuzzy_system::get_nfs_description() const
{
   return _nfs->get_nfs_description();
}
 
std::string ksi::random_neuro_fuzzy_system::get_nfs_name() const
{
   return _nfs->get_nfs_name();
}

void ksi::random_neuro_fuzzy_system::set_classification_threshold(double threshold)
{
   classification_threshold = threshold;
}

double ksi::random_neuro_fuzzy_system::get_threshold() const 
{
   return classification_threshold;
}


 