#ifndef META_CLASSIFIER_THREE_WAY_DECISION_NFS_H
#define META_CLASSIFIER_THREE_WAY_DECISION_NFS_H

#include <vector>
#include <memory>

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../gan/discriminative_model.h"
#include "../gan/generative_model.h"
#include "three_way_decision_nfs.h"

namespace ksi
{
    /** 
     * Meta-classifier cascade: After each classifier is trained, a meta-classifier is trained
     * to learn when the primary classifier makes incorrect predictions. Items predicted to be 
     * incorrect by the meta-classifier are passed to the next level in the cascade.
     * Meta-classifiers use Youden index for threshold determination.
     * 
     * @author Wojciech Ptaś
     * @date 2026-01-24
     */
    class three_way_decision_nfs_meta : public three_way_decision_nfs
    {
    protected:
        /** Meta-classifiers that predict when primary classifiers make errors.
         *  One meta-classifier for each level except the last. */
        std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>> _meta_classifiers;
        
    public:
        /** Default constructor */
        three_way_decision_nfs_meta();
        
        /** @param cascade cascade of neuro-fuzzy systems (primary classifiers)
         *  @param meta_cascade cascade of meta-classifiers (one for each primary except last)
         */
        three_way_decision_nfs_meta(
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade
        );
        
        /** @param cascade cascade of neuro-fuzzy systems (primary classifiers)
         *  @param meta_cascade cascade of meta-classifiers
         *  @param train   name of train dataset file 
         *  @param test    name of test dataset file
         *  @param result  name of output result file 
         */
        three_way_decision_nfs_meta(
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
            const std::string& train, 
            const std::string& test, 
            const std::string& result
        );
        
        /** @param cascade cascade of neuro-fuzzy systems (primary classifiers)
         *  @param meta_cascade cascade of meta-classifiers
         *  @param train   name of train dataset file 
         *  @param validation name of validation dataset file
         *  @param test    name of test dataset file
         *  @param result  name of output result file 
         */
        three_way_decision_nfs_meta(
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
            const std::string& train,
            const std::string& validation, 
            const std::string& test, 
            const std::string& result
        );
        
        /** @param cascade cascade of neuro-fuzzy systems (primary classifiers)
         *  @param meta_cascade cascade of meta-classifiers
         *  @param train   train dataset
         *  @param test    test dataset
         *  @param result  name of output result file 
         */
        three_way_decision_nfs_meta(
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
            const ksi::dataset& train, 
            const ksi::dataset& test, 
            const std::string& result
        );
        
        /** @param cascade cascade of neuro-fuzzy systems (primary classifiers)
         *  @param meta_cascade cascade of meta-classifiers
         *  @param train   train dataset
         *  @param validation validation dataset
         *  @param test    test dataset
         *  @param result  name of output result file 
         */
        three_way_decision_nfs_meta(
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& cascade,
            const std::vector<std::shared_ptr<ksi::neuro_fuzzy_system>>& meta_cascade,
            const ksi::dataset& train,
            const ksi::dataset& validation, 
            const ksi::dataset& test, 
            const std::string& result
        );
        
        three_way_decision_nfs_meta(const three_way_decision_nfs_meta& wzor);
        three_way_decision_nfs_meta(three_way_decision_nfs_meta&& wzor);
        three_way_decision_nfs_meta& operator=(const three_way_decision_nfs_meta& wzor);
        three_way_decision_nfs_meta& operator=(three_way_decision_nfs_meta&& wzor);
        virtual ~three_way_decision_nfs_meta();
        
        ksi::neuro_fuzzy_system* clone() const override;
        
        /** Trains the cascade with meta-classifiers.
         *  For each level (except last):
         *  1. Train primary classifier
         *  2. Train meta-classifier to predict when primary makes errors
         *  3. Pass items predicted as errors to next level
         */
        virtual void createFuzzyRulebase(
            const ksi::dataset& train, 
            const ksi::dataset& test, 
            const ksi::dataset& validation
        ) override;
        
        /** Answer classification using meta-classifiers to route data items. */
        virtual std::pair<double, double> answer_classification(const ksi::datum& item) const override;
        
        /** Answer classification with cascade depth information.
         *  @param item datum to classify
         *  @return tuple of (elaborated_numeric, elaborated_class, cascade_level)
         *          where cascade_level indicates which level made the final decision
         */
        virtual std::tuple<double, double, std::size_t> answer_classification_with_cascade_depth(const ksi::datum& item) const override;
        
        /** @return name of the neuro-fuzzy system */
        virtual std::string get_nfs_name() const override;
        
        /** @return brief name of the neuro-fuzzy system */
        virtual std::string get_brief_nfs_name() const override;
        
        /** @return description of the neuro-fuzzy system */
        virtual std::string get_nfs_description() const override;
        
        /** Print rulebase including meta-classifiers.
         *  @param ss ostream to print to
         */
        virtual void printRulebase(std::ostream& ss) override;
        
        /** @return a description of the cascade including meta-classifiers
         *  @date 2026-01-25 */
        virtual std::string get_cascade_names() const override;
        
        /** @return a brief description of the cascade including meta-classifiers
         *  @date 2026-01-25 */
        virtual std::string get_brief_cascade_names() const override;
        
    protected:
        /** Helper to copy fields from another instance */
        void meta_copy_fields(const three_way_decision_nfs_meta& other);
        
        /** Extract incorrectly classified data items.
         *  @param data original dataset
         *  @param answers answers from classifier (expected, elaborated_numeric, elaborated_class)
         *  @return dataset with incorrectly classified items
         */
        ksi::dataset extract_incorrect_results(
            const ksi::dataset& data,
            const std::vector<std::tuple<double, double, double>>& answers
        );
        
        /** Create a binary classification dataset for meta-classifier training.
         *  Label: 1.0 if primary classifier was correct, -1.0 if incorrect.
         *  @param data original dataset
         *  @param answers answers from primary classifier
         *  @return dataset with binary labels (correct/incorrect)
         */
        ksi::dataset create_meta_training_data(
            const ksi::dataset& data,
            const std::vector<std::tuple<double, double, double>>& answers
        );
    };
}

#endif
