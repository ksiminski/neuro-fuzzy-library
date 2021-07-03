
 
kompilator=g++
standard=-std=c++14

optymalizacja=-O3
debug=

#optymalizacja=
#debug=-g

#profilowanie=-pg
profilowanie=
pedantic=-pedantic-errors
exec=exec


#######

.PHONY: foldery clean doxygen

#============================================

# uruchomienie 

__ : foldery $(exec)/main
	./$(exec)/main  

#============================================


# utworzenie katalogu na pliki wykonywalne (jezeli nie istnieje):
foldery : $(exec)

$(exec) : 
	[ ! -d $(exec) ] && mkdir $(exec)

# kompilacja pliku wykonywalnego:

$(exec)/main : $(exec)/main.o                      \
               $(exec)/exception.o                 \
               $(exec)/number.o                    \
               $(exec)/datum.o                     \
               $(exec)/dataset.o                   \
               $(exec)/data-modifier.o             \
               $(exec)/data-modifier-normaliser.o  \
               $(exec)/data-modifier-standardiser.o      \
               $(exec)/data-modifier-marginaliser.o      \
               $(exec)/data-modifier-imputer.o           \
               $(exec)/data-modifier-imputer-average.o   \
               $(exec)/data-modifier-imputer-median.o    \
               $(exec)/data-modifier-imputer-knn.o       \
               $(exec)/data-modifier-imputer-knn-average.o   \
               $(exec)/data-modifier-imputer-knn-median.o    \
               $(exec)/data-modifier-imputer-values-from-knn.o   \
               $(exec)/extensional-fuzzy-number-gaussian.o       \
               $(exec)/error-calculator.o          \
               $(exec)/error-RMSE.o                \
               $(exec)/error-MAE.o                 \
               $(exec)/metric.o 	                  \
               $(exec)/metric-euclidean.o              \
               $(exec)/metric-euclidean-incomplete.o   \
               $(exec)/metric-minkowski.o              \
               $(exec)/metric-minkowski-weighted.o     \
               $(exec)/distance.o 	                 \
               $(exec)/distance-euclidean.o              \
               $(exec)/distance-euclidean-incomplete.o   \
               $(exec)/reader-complete.o           \
               $(exec)/reader-incomplete.o         \
               $(exec)/reader.o                    \
               $(exec)/t-norm.o                    \
               $(exec)/t-norm-product.o            \
               $(exec)/t-norm-min.o                \
               $(exec)/t-norm-lukasiewicz.o        \
               $(exec)/t-norm-fodor.o              \
               $(exec)/t-norm-drastic.o            \
               $(exec)/t-norm-einstein.o           \
               $(exec)/descriptor.o                \
               $(exec)/descriptor-triangular.o     \
               $(exec)/descriptor-semitriangular.o \
               $(exec)/descriptor-trapezoidal.o    \
               $(exec)/descriptor-singleton.o      \
               $(exec)/descriptor-gaussian.o       \
               $(exec)/descriptor-interval-gaussian.o   \
               $(exec)/descriptor-gaussian-subspace.o   \
               $(exec)/descriptor-interval-gaussian-subspace.o  \
               $(exec)/descriptor-sigmoidal.o      \
               $(exec)/descriptor-constant.o       \
               $(exec)/implication.o               \
               $(exec)/imp-lukasiewicz.o           \
               $(exec)/imp-rescher.o               \
               $(exec)/imp-goedel.o                \
               $(exec)/imp-goguen.o                \
               $(exec)/imp-zadeh.o                 \
               $(exec)/imp-kleene-dienes.o         \
               $(exec)/imp-reichenbach.o           \
               $(exec)/imp-fodor.o                 \
               $(exec)/dissimilarity.o             \
               $(exec)/dis-huber.o                 \
               $(exec)/dis-square.o                \
               $(exec)/dis-log.o                   \
               $(exec)/dis-log-linear.o            \
               $(exec)/dis-linear.o                \
               $(exec)/dis-sigmoidal.o             \
               $(exec)/dis-sigmoidal-linear.o      \
               $(exec)/owa.o                     \
               $(exec)/plowa.o                   \
               $(exec)/sowa.o                    \
               $(exec)/uowa.o                    \
               $(exec)/premise.o          \
               $(exec)/subspace-premise.o          \
               $(exec)/consequence.o      \
               $(exec)/consequence-MA.o   \
               $(exec)/consequence-TSK.o  \
               $(exec)/consequence-CL.o   \
               $(exec)/rule.o             \
               $(exec)/logicalrule.o      \
               $(exec)/rulebase.o         \
               $(exec)/neuro-fuzzy-system.o        \
               $(exec)/annbfis.o          \
               $(exec)/subspace-annbfis.o          \
               $(exec)/tsk.o              \
               $(exec)/ma.o               \
               $(exec)/random-neuro-fuzzy-system.o \
               $(exec)/random-neuro-fuzzy-forest.o \
               $(exec)/partition.o                 \
               $(exec)/cluster.o                   \
               $(exec)/partitioner.o               \
               $(exec)/partitioner-grid.o          \
               $(exec)/fcm.o                       \
               $(exec)/fcm_generic.o               \
               $(exec)/fcm-T.o                     \
               $(exec)/fcm-possibilistic.o         \
               $(exec)/fcm-conditional.o           \
               $(exec)/fcom.o                      \
               $(exec)/fubi.o                      \
               $(exec)/sfcm.o                      \
               $(exec)/rfcm.o                      \
               $(exec)/rsfcm.o                     \
               $(exec)/rfcom.o                     \
               $(exec)/debug.o            \
               $(exec)/utility-string.o   \
               $(exec)/utility-math.o     \
               $(exec)/ridders.o          \
               $(exec)/ridders-test.o     \
               $(exec)/ridders-gaussian-m.o   \
               $(exec)/ridders-gaussian-s.o   \
               $(exec)/simulated-annealing.o  \
               $(exec)/simulated-annealing-gaussian.o  \
               $(exec)/tempus.o           \
               $(exec)/clock.o            \
               $(exec)/colours.o          \
               $(exec)/mathematics.o      \
               $(exec)/vector-operators.o \
               $(exec)/print.o            \
               $(exec)/roc.o              \
               $(exec)/confusion-matrix.o \
               $(exec)/least-error-squares-regression.o   \
               $(exec)/experiment.o       \
               $(exec)/exp-000.o          \
               $(exec)/exp-001.o          \
               $(exec)/exp-002.o          \
               $(exec)/exp-003.o          \
               $(exec)/exp-004.o          \
               $(exec)/exp-005.o          \
               $(exec)/exp-006.o          \
               $(exec)/exp-007.o          \
               $(exec)/exp-008.o          \
               $(exec)/static_mem_pool.o  \
               $(exec)/mem_pool_base.o    \
               $(exec)/debug_new.o        \
               $(exec)/bool_array.o       
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -o $@ $^ 
	
	
	
# kompilacja poszczegolnych plikow:
	            
$(exec)/main.o : main.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 

# memory leaks:
$(exec)/static_mem_pool.o : memory/nvwa/static_mem_pool.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/mem_pool_base.o : memory/nvwa/mem_pool_base.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/debug_new.o : memory/nvwa/debug_new.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/bool_array.o : memory/nvwa/bool_array.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
 
	
# debug:
$(exec)/debug.o : service/debug.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/exception.o : service/exception.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 

	
# common:
$(exec)/number.o : common/number.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/datum.o : common/datum.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/datum-interval.o : common/datum-interval.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/datum-incomplete.o : common/datum-incomplete.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/extensional-fuzzy-number-gaussian.o : common/extensional-fuzzy-number-gaussian.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 

$(exec)/dataset.o : common/dataset.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 


$(exec)/data-modifier.o : common/data-modifier.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-normaliser.o : common/data-modifier-normaliser.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-standardiser.o : common/data-modifier-standardiser.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-marginaliser.o : common/data-modifier-marginaliser.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer.o : common/data-modifier-imputer.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-average.o : common/data-modifier-imputer-average.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-median.o : common/data-modifier-imputer-median.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-knn.o : common/data-modifier-imputer-knn.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-knn-average.o : common/data-modifier-imputer-knn-average.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-knn-median.o : common/data-modifier-imputer-knn-median.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-values-from-knn.o : common/data-modifier-imputer-values-from-knn.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 




$(exec)/distance.o : common/distance.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/distance-euclidean.o : common/distance-euclidean.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/distance-euclidean-incomplete.o : common/distance-euclidean-incomplete.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 


$(exec)/missingdata.o : common/missingdata.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 

$(exec)/error-calculator.o : common/error-calculator.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/error-RMSE.o : common/error-RMSE.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/error-MAE.o : common/error-MAE.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 

# metrics 
$(exec)/metric.o : metrics/metric.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 
$(exec)/metric-euclidean.o : metrics/metric-euclidean.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 
$(exec)/metric-euclidean-incomplete.o : metrics/metric-euclidean-incomplete.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 
$(exec)/metric-minkowski.o : metrics/metric-minkowski.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 
$(exec)/metric-minkowski-weighted.o : metrics/metric-minkowski-weighted.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 


# readers

$(exec)/reader.o : readers/reader.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/reader-complete.o : readers/reader-complete.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/reader-incomplete.o : readers/reader-incomplete.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
	
# tnorms

$(exec)/t-norm.o : tnorms/t-norm.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-product.o : tnorms/t-norm-product.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-min.o : tnorms/t-norm-min.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-lukasiewicz.o : tnorms/t-norm-lukasiewicz.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-fodor.o : tnorms/t-norm-fodor.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-drastic.o : tnorms/t-norm-drastic.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-einstein.o : tnorms/t-norm-einstein.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 

# implications
$(exec)/implication.o : implications/implication.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/imp-lukasiewicz.o : implications/imp-lukasiewicz.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/imp-rescher.o : implications/imp-rescher.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/imp-goedel.o : implications/imp-goedel.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/imp-goguen.o : implications/imp-goguen.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/imp-zadeh.o : implications/imp-zadeh.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/imp-kleene-dienes.o : implications/imp-kleene-dienes.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/imp-reichenbach.o : implications/imp-reichenbach.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/imp-fodor.o : implications/imp-fodor.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 

# descriptors
$(exec)/descriptor.o : descriptors/descriptor.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-triangular.o : descriptors/descriptor-triangular.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-semitriangular.o : descriptors/descriptor-semitriangular.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-trapezoidal.o : descriptors/descriptor-trapezoidal.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-singleton.o : descriptors/descriptor-singleton.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-gaussian.o : descriptors/descriptor-gaussian.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-interval-gaussian.o : descriptors/descriptor-interval-gaussian.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-gaussian-subspace.o : descriptors/descriptor-gaussian-subspace.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-interval-gaussian-subspace.o : descriptors/descriptor-interval-gaussian-subspace.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-sigmoidal.o : descriptors/descriptor-sigmoidal.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-constant.o : descriptors/descriptor-constant.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 

	
	
# neuro-fuzzy
$(exec)/premise.o : neuro-fuzzy/premise.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/subspace-premise.o : neuro-fuzzy/subspace-premise.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/consequence.o : neuro-fuzzy/consequence.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/consequence-MA.o : neuro-fuzzy/consequence-MA.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/consequence-TSK.o : neuro-fuzzy/consequence-TSK.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/consequence-CL.o : neuro-fuzzy/consequence-CL.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/rule.o : neuro-fuzzy/rule.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/logicalrule.o : neuro-fuzzy/logicalrule.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/rulebase.o : neuro-fuzzy/rulebase.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/subspace-rulebase.o : neuro-fuzzy/subspace-rulebase.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/neuro-fuzzy-system.o : neuro-fuzzy/neuro-fuzzy-system.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/annbfis.o : neuro-fuzzy/annbfis.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/subspace-annbfis.o : neuro-fuzzy/subspace-annbfis.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/tsk.o : neuro-fuzzy/tsk.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/ma.o : neuro-fuzzy/ma.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/random-neuro-fuzzy-forest.o : neuro-fuzzy/random-neuro-fuzzy-forest.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/random-neuro-fuzzy-system.o : neuro-fuzzy/random-neuro-fuzzy-system.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 

# dissimilarity measures
$(exec)/dissimilarity.o : dissimilarities/dissimilarity.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/dis-huber.o : dissimilarities/dis-huber.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/dis-log.o : dissimilarities/dis-log.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/dis-log-linear.o : dissimilarities/dis-log-linear.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/dis-linear.o : dissimilarities/dis-linear.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/dis-sigmoidal.o : dissimilarities/dis-sigmoidal.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/dis-sigmoidal-linear.o : dissimilarities/dis-sigmoidal-linear.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/dis-square.o : dissimilarities/dis-square.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
	

# ordered-weighted averaging	
$(exec)/owa.o : owas/owa.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/uowa.o : owas/uowa.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/plowa.o : owas/plowa.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/sowa.o : owas/sowa.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
	
	
# partitions
$(exec)/partition.o : partitions/partition.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/cluster.o : partitions/cluster.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 

$(exec)/partitioner.o : partitions/partitioner.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/partitioner-grid.o : partitions/partitioner-grid.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/fcm.o : partitions/fcm.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/fcm_generic.o : partitions/fcm_generic.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 
$(exec)/fcm-T.o : partitions/fcm-T.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 
$(exec)/fcm-possibilistic.o : partitions/fcm-possibilistic.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/fcm-conditional.o : partitions/fcm-conditional.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/fcom.o : partitions/fcom.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/fubi.o : partitions/fubi.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/sfcm.o : partitions/sfcm.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/rfcm.o : partitions/rfcm.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/rsfcm.o : partitions/rsfcm.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/rfcom.o : partitions/rfcom.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
 
# auxiliary
$(exec)/utility-string.o : auxiliary/utility-string.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/colours.o : auxiliary/colours.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^ 
$(exec)/tempus.o : auxiliary/tempus.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/roc.o : auxiliary/roc.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/utility-math.o : auxiliary/utility-math.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/least-error-squares-regression.o : auxiliary/least-error-squares-regression.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/confusion-matrix.o : auxiliary/confusion-matrix.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/clock.o : auxiliary/clock.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/mathematics.o : auxiliary/mathematics.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(profilowanie) $(pedantic) -c -o $@ $^
$(exec)/vector-operators.o : auxiliary/vector-operators.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/print.o : auxiliary/print.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^


# heuristics
$(exec)/ridders.o : heuristics/ridders.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/ridders-test.o : heuristics/ridders-test.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/ridders-gaussian-m.o : heuristics/ridders-gaussian-m.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/ridders-gaussian-s.o : heuristics/ridders-gaussian-s.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/simulated-annealing.o : heuristics/simulated-annealing.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 
$(exec)/simulated-annealing-gaussian.o : heuristics/simulated-annealing-gaussian.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^ 


	
	
# experiments
$(exec)/experiment.o : experiments/experiment.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-000.o : experiments/exp-000.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-001.o : experiments/exp-001.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-002.o : experiments/exp-002.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-003.o : experiments/exp-003.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-004.o : experiments/exp-004.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-005.o : experiments/exp-005.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-006.o : experiments/exp-006.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-007.o : experiments/exp-007.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^
$(exec)/exp-008.o : experiments/exp-008.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(pedantic) -c -o $@ $^

	
#profil : main.cpp 
#	if [ -f main ]; then rm main ; fi ;
#	$(kompilator) $(standard) $(profilowanie) -o main main.cpp 
#	./main
#	gprof main > profil.txt
	
	
clean : 
	rm $(exec)/*


doxygen : 
	doxygen doxyfile
