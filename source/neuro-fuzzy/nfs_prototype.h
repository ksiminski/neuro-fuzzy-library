
#ifndef NFS_PROTOTYPE_H
#define NFS_PROTOTYPE_H

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/fac_prototype.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "../common/dataset.h"
#include "../common/datum.h"
#include "../common/number.h"
#include "../partitions/partition.h"


namespace ksi
{
   class nfs_prototype : public neuro_fuzzy_system
   {
   protected:
      std::shared_ptr<ksi::fac_prototype> _pFactory; 
      
//       void copy_fields(const prototype_nfs & wzor);
      
      partition doPartition(const dataset & ds);
       
    public:
      nfs_prototype ();
      nfs_prototype (const nfs_prototype & wzor);
      nfs_prototype (nfs_prototype && wzor);
      nfs_prototype & operator= (const nfs_prototype & wzor);
      nfs_prototype & operator= (nfs_prototype && wzor);
      virtual ~nfs_prototype ();
      
      nfs_prototype (const int number_of_rules,
                     const int number_of_clustering_iterations,
                     const int number_of_tuning_iterations,
                     const double learning_coefficient,
                     const bool normalisation,
                     const ksi::fac_prototype & prot);

      /** @date 2021-03-22 */
      nfs_prototype (const int number_of_rules,
                     const int number_of_clustering_iterations,
                     const int number_of_tuning_iterations,
                     const double learning_coefficient,
                     const bool normalisation,
                     const ksi::fac_prototype & prot,
                     const double positive_class, 
                     const double negative_class, 
                     const ksi::roc_threshold threshold_type);
            
    public:
      double answer(const ksi::datum & item) const override;
      ksi::number elaborate_answer(const ksi::datum & d) const override;
      
      // jakies metody, żeby interfejs był zaimplementowany -- zasmiecanie interfejsami  
      
      void train_discriminative_model(const ksi::dataset & ds) override;
      void train_generative_model(const ksi::dataset & ds) override;
      double discriminate(const ksi::datum & d) override;
      
      virtual std::string extra_report() const override;
      
   };
}


#endif
