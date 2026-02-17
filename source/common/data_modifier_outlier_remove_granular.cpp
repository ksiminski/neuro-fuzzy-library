
#include <utility>
#include <memory>
#include <format>

#include "data-modifier.h"
#include "data_modifier_outlier_remove_granular.h"
#include "../partitions/partitioner.h"
#include "../snorms/s-norm.h"
#include "../tnorms/t-norm.h"

#include "../partitions/fcm.h"
#include "../neuro-fuzzy/premise.h"

void ksi::data_modifier_outlier_remove_granular::modify(dataset& ds)
{
   // tutaj sprawa jest prosta:
   // 1. najpierw wyznaczam granule (np. FCM)
   auto partition = _pPartitioner->doPartition(ds);

   class set_of_granules
   {
      public:
         class granule
         {
            std::vector<std::shared_ptr<ksi::descriptor>> _descriptors;
         public:
            std::string to_string () const
            {
               std::string output;
               for (const auto & pD : _descriptors)
               {
                  output += pD->to_string();
               }
               return output;
            }
         public:
            void add_descriptor(const ksi::descriptor & d)
            {
               _descriptors.push_back(std::shared_ptr<ksi::descriptor> (d.clone()));
            }
            double get_membership (const ksi::datum & d, const ksi::t_norm & tnorm) const
            {
               try 
               {
                  auto nAttributes = d.getNumberOfAttributes();
                  if (d.getNumberOfAttributes() != _descriptors.size())
                     throw std::format("Number of attributes {} and descriptors {} do not match.", nAttributes, _descriptors.size());

                  double membership = 1.0;
                  auto X = d.getVector();
                  for (std::size_t i = 0; i < nAttributes; ++i)
                  {
                     
                     auto memb = _descriptors[i]->getMembership(X[i]);
                     membership = tnorm.tnorm(membership, memb);
                  }

                  return membership;
               }
               CATCH; 
            }
            
            granule()
            { }
            
            granule (const granule & other)
            {
               for (auto & p : other._descriptors)
               {
                  _descriptors.push_back(std::shared_ptr<ksi::descriptor> (p->clone()));
               }
            }
            granule (granule && other)
            {
               std::swap(_descriptors, other._descriptors);
            }
            
            granule operator= (const granule & other)
            {
               if (this == & other)
                  return *this;
               
               _descriptors.clear();
               for (auto & p : other._descriptors)
               {
                  _descriptors.push_back(std::shared_ptr<ksi::descriptor> (p->clone()));
               }
               
               return * this;               
            }
            
            granule operator= (granule && other)
            {
               if (this == & other)
                  return *this;
               
               std::swap(_descriptors, other._descriptors);   
               return * this;               
            }
            
            
         };

      protected:
         std::vector<granule> _granules;

         std::shared_ptr<ksi::s_norm> _pSnorm;
         std::shared_ptr<ksi::t_norm> _pTnorm;

      public:
         set_of_granules(const ksi::partition & p, const ksi::t_norm & Tnorm, const ksi::s_norm & Snorm)
         {
            _pTnorm = std::shared_ptr<ksi::t_norm> (Tnorm.clone());
            _pSnorm = std::shared_ptr<ksi::s_norm> (Snorm.clone());


            auto nCluster = p.getNumberOfClusters();
            for (std::size_t i = 0; i < nCluster; ++i)
            {
               granule g;
               auto cl = p.getCluster(i);
               auto nDescriptors = cl->get_number_of_desciptors();
               for (std::size_t d = 0; d < nDescriptors; ++d)
               {
                  g.add_descriptor(* cl->getDescriptor(d));
               }
               _granules.push_back(g);
               // debug(g.to_string());

            }
         }

         double get_membership (const ksi::datum & d)
         {
            double memb = 0.0;
            for (auto const & g : _granules)
            {
               double m = g.get_membership(d, *_pTnorm);
               memb = _pSnorm->snorm(memb, m);
            }
            return memb;
         }

   } granules (partition, *_pTnorm, *_pSnorm);

   // 2. nastepnie wyznaczam stopnie przynalezności wszystkich danych do granul 

   ksi::dataset result_ds;
   
   auto nData = ds.getNumberOfData();
   std::vector<double> memberships(nData);
   for (std::size_t i = 0; i < nData; ++i)
   {
      auto pDatum = ds.getDatum(i);
      auto memb = granules.get_membership(*pDatum);
      memberships[i] = memb;
      // debug(*pDatum); debug(memb);   
      // 4. usuwam przykłady ponizej progu przynaleznosci.
      if (memb > _threshold)
         result_ds.addDatum(*pDatum);
   }

   ds = result_ds;
   // 5. i tyle :-)    

}




ksi::data_modifier_outlier_remove_granular::data_modifier_outlier_remove_granular (const ksi::partitioner & Partitioner, const ksi::t_norm & Tnorm, const ksi::s_norm & Snorm, const double threshold)
{
   description = "granular-outlier-remove";
   _threshold = threshold;

   _pPartitioner = std::shared_ptr<ksi::partitioner> (Partitioner.clone());
   _pTnorm = std::shared_ptr<ksi::t_norm> (Tnorm.clone());
   _pSnorm = std::shared_ptr<ksi::s_norm> (Snorm.clone());
}

ksi::data_modifier_outlier_remove_granular::~data_modifier_outlier_remove_granular ()
{
   // delete what is to delete

}

ksi::data_modifier_outlier_remove_granular::data_modifier_outlier_remove_granular (const ksi::data_modifier_outlier_remove_granular & other) : ksi::data_modifier(other)
{
   // copy what is to copy
   _pPartitioner = std::shared_ptr<ksi::partitioner> (other._pPartitioner->clone());
   _pSnorm = std::shared_ptr<ksi::s_norm> (other._pSnorm->clone());
   
   _threshold = other._threshold;
}

ksi::data_modifier_outlier_remove_granular & ksi::data_modifier_outlier_remove_granular::operator= (const ksi::data_modifier_outlier_remove_granular & other)
{
   if (this == & other)
      return *this;

   ksi::data_modifier::operator=(other);

   // remove what is to remove

   // allocate what is to allocate
   _pPartitioner = std::shared_ptr<ksi::partitioner> (other._pPartitioner->clone());
   _pSnorm = std::shared_ptr<ksi::s_norm> (other._pSnorm->clone());
   
   _threshold = other._threshold;

   return *this;
}

ksi::data_modifier_outlier_remove_granular::data_modifier_outlier_remove_granular (ksi::data_modifier_outlier_remove_granular && other) : ksi::data_modifier(std::move(other))
{
   // swap what is to swap
   std::swap(_pPartitioner, other._pPartitioner);
   std::swap(_pSnorm, other._pSnorm);
   std::swap(_threshold, other._threshold);
}

ksi::data_modifier_outlier_remove_granular & ksi::data_modifier_outlier_remove_granular::operator= (ksi::data_modifier_outlier_remove_granular && other)
{
   if (this == & other)
      return *this;

   ksi::data_modifier::operator=(other);

   // swap what is to swap
   std::swap(_pPartitioner, other._pPartitioner);
   std::swap(_pSnorm, other._pSnorm);
   std::swap(_threshold, other._threshold);

   return *this;
}

/*
   std::shared_ptr<ksi::data_modifier> ksi::data_modifier_outlier_remove_granular::clone () const
   {
// prototype design pattern
return std::shared_ptr<ksi::data_modifier> (new ksi::data_modifier_outlier_remove_granular(*this));
}
*/

ksi::data_modifier * ksi::data_modifier_outlier_remove_granular::clone () const
{
   // prototype design pattern
   return new ksi::data_modifier_outlier_remove_granular(*this);
}



