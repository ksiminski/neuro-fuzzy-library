

#include "../partitions/fcm-T.h"


// Specjalizowane metody szablonu w pliku *.cpp (inaczej blad linkera: wielokrotna definicja metody).

template<>
ksi::dataset ksi::fcm_T<double>::elaborate_gaussian_prototypes (
   const int _nClusters, 
   const int nAttr,  
   const std::vector<std::vector<double>> & mV, 
   const std::vector<std::vector<double>> & mS)
{
   ksi::dataset ds;
   
   for (std::size_t c = 0; c < _nClusters; c++)
   {
      ksi::datum d;
      for (std::size_t a = 0; a < nAttr; a++)
      {
         ksi::ext_fuzzy_number_gaussian num (mV[c][a], mS[c][a]);
         d.push_back(ksi::number (num));
      }
      ds.addDatum(d);
   }
   return ds;
}


template<>
ksi::dataset ksi::fcm_T<ksi::ext_fuzzy_number_gaussian>::elaborate_gaussian_prototypes (
   const int _nClusters, 
   const int nAttr, 
   const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & mV, 
   const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & mS)
{
   ksi::dataset ds;
   
   for (std::size_t c = 0; c < _nClusters; c++)
   {
      ksi::datum d;
      for (std::size_t a = 0; a < nAttr; a++)
      {
         ksi::ext_fuzzy_number_gaussian num (mV[c][a].get_value(), mV[c][a].get_sigma() + mS[c][a].get_value());
         d.push_back(ksi::number (num));
      }
      ds.addDatum(d);
   }
   return ds;
}

template <> 
ksi::partition ksi::fcm_T<double>::elaborate_gaussian_partition (
   const int _nClusters, 
   const int nAttr, 
   const std::vector<std::vector<double>> & mV, 
   const std::vector<std::vector<double>> & mS)
{
   // przeksztalcenie do postaci zbiorow gaussowskich
   ksi::partition part;
   for (int c = 0; c < _nClusters; c++)
   {
      ksi::cluster cl; 
      for (std::size_t a = 0; a < nAttr; a++)
      {
         ksi::descriptor_gaussian d (mV[c][a], mS[c][a]);
         cl.addDescriptor(d);
      }
      part.addCluster(cl);
   }
   
   part.setClusterCentres(mV);
   part.setPartitionMatrix(mU);
   
   return part;
}

template <>
ksi::partition ksi::fcm_T<ksi::ext_fuzzy_number_gaussian>::elaborate_gaussian_partition (
   const int _nClusters, const int nAttr, 
   const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & mV, 
   const std::vector<std::vector<ksi::ext_fuzzy_number_gaussian>> & mS)
{
   // przeksztalcenie do postaci zbiorow gaussowskich
   ksi::partition part;
   for (int c = 0; c < _nClusters; c++)
   {
      ksi::cluster cl; 
      for (std::size_t a = 0; a < nAttr; a++)
      {
         ksi::descriptor_gaussian d (mV[c][a].get_value(), mV[c][a].get_sigma() + mS[c][a].get_value());
         cl.addDescriptor(d);
      }
      part.addCluster(cl);
   }
   
   part.setClusterCentres(mV);
   part.setPartitionMatrix(mU);
   
   return part;
}
