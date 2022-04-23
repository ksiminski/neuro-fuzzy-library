
 

 
compiler=g++
standard=-std=c++20
threads=-pthread

#profile=-pg
profile=

pedantic=-pedantic-errors
memorydetector=valgrind
memoryopt=--leak-check=yes

#DEBUG ?= 1
DEBUG ?= 0

ifeq ($(DEBUG), 1)
    optimisation=
    debug=-g
    exec=debug
else
    optimisation=-O3
    debug=
    exec=release
endif


#######

.PHONY: directories clean doxygen

#============================================

# run experiments 

__ : directories $(exec)/main
	./$(exec)/main  
	
1 :  directories $(exec)/main
	./$(exec)/main  1  
		
2 :  directories $(exec)/main
	./$(exec)/main  2
		
3 :  directories $(exec)/main
	./$(exec)/main  3
		
4 :  directories $(exec)/main
	./$(exec)/main  4

5 :  directories $(exec)/main
	./$(exec)/main  5

lab : directories $(exec)/main
	./$(exec)/main  0

#----------------------------------------------
	
ifeq ($(DEBUG), 1) 
	$(memorydetector) $(memoryopt) ./$(exec)/main  
endif	
#============================================


# create a directory for executables
directories : $(exec)

$(exec) : 
	[ ! -d $(exec) ] && mkdir $(exec)

# consolidation of object files

$(exec)/main : $(exec)/main.o                      \
               $(exec)/exception.o                 \
               $(exec)/number.o                    \
               $(exec)/datum.o                     \
               $(exec)/result.o                    \
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
               $(exec)/granule.o                       \
               $(exec)/set_of_cooperating_granules.o  \
               $(exec)/set_of_granules.o              \
               $(exec)/set_of_standalone_granules.o   \
               $(exec)/data_item.o                    \
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
               $(exec)/s-norm.o                    \
               $(exec)/s-norm-sum.o                \
               $(exec)/s-norm-max.o                \
               $(exec)/s-norm-lukasiewicz.o        \
               $(exec)/s-norm-fodor.o              \
               $(exec)/s-norm-drastic.o            \
               $(exec)/s-norm-einstein.o           \
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
               $(exec)/annbfis.o                   \
               $(exec)/subspace-annbfis.o          \
               $(exec)/fubi-annbfis.o              \
               $(exec)/abstract-ma.o               \
               $(exec)/abstract-tsk.o              \
               $(exec)/abstract-annbfis.o          \
               $(exec)/abstract_fcom.o             \
               $(exec)/tsk.o                       \
               $(exec)/ma.o                        \
				   $(exec)/annbfis_prototype.o         \
				   $(exec)/tsk_prototype.o             \
				   $(exec)/fac_prototype.o             \
				   $(exec)/prototype.o                 \
				   $(exec)/prototype_minkowski.o       \
				   $(exec)/prototype_minkowski_regression.o     \
				   $(exec)/nfs_prototype.o             \
				   $(exec)/fac_prototype_minkowski.o   \
				   $(exec)/fac_prototype_minkowski_regression.o \
               $(exec)/gan.o                       \
               $(exec)/generative_model.o          \
               $(exec)/discriminative_model.o      \
               $(exec)/partition.o                 \
               $(exec)/cluster.o                   \
               $(exec)/partitioner.o               \
               $(exec)/partitioner-grid.o          \
               $(exec)/dbscan.o                    \
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
               $(exec)/directory.o        \
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
               $(exec)/exp-lab.o          
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -o $@ $^ 
	
	
	
# compilation of files
	            
$(exec)/main.o : main.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

# memory leaks:
$(exec)/static_mem_pool.o : memory/nvwa/static_mem_pool.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/mem_pool_base.o : memory/nvwa/mem_pool_base.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/debug_new.o : memory/nvwa/debug_new.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/bool_array.o : memory/nvwa/bool_array.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
 
	
# debug:
$(exec)/debug.o : service/debug.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/exception.o : service/exception.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

	
# common:
$(exec)/number.o : common/number.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/datum.o : common/datum.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/datum-interval.o : common/datum-interval.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/datum-incomplete.o : common/datum-incomplete.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/extensional-fuzzy-number-gaussian.o : common/extensional-fuzzy-number-gaussian.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/result.o : common/result.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

$(exec)/dataset.o : common/dataset.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 


$(exec)/data-modifier.o : common/data-modifier.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-normaliser.o : common/data-modifier-normaliser.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-standardiser.o : common/data-modifier-standardiser.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-marginaliser.o : common/data-modifier-marginaliser.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer.o : common/data-modifier-imputer.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-average.o : common/data-modifier-imputer-average.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-median.o : common/data-modifier-imputer-median.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-knn.o : common/data-modifier-imputer-knn.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-knn-average.o : common/data-modifier-imputer-knn-average.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-knn-median.o : common/data-modifier-imputer-knn-median.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data-modifier-imputer-values-from-knn.o : common/data-modifier-imputer-values-from-knn.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 




$(exec)/distance.o : common/distance.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/distance-euclidean.o : common/distance-euclidean.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/distance-euclidean-incomplete.o : common/distance-euclidean-incomplete.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 


$(exec)/missingdata.o : common/missingdata.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

$(exec)/error-calculator.o : common/error-calculator.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/error-RMSE.o : common/error-RMSE.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/error-MAE.o : common/error-MAE.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

# metrics 
$(exec)/metric.o : metrics/metric.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/metric-euclidean.o : metrics/metric-euclidean.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/metric-euclidean-incomplete.o : metrics/metric-euclidean-incomplete.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/metric-minkowski.o : metrics/metric-minkowski.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/metric-minkowski-weighted.o : metrics/metric-minkowski-weighted.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

# granule

$(exec)/granule.o : granules/granule.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/data_item.o : granules/data_item.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/set_of_standalone_granules.o : granules/set_of_standalone_granules.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/set_of_granules.o : granules/set_of_granules.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/set_of_cooperating_granules.o : granules/set_of_cooperating_granules.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

# readers

$(exec)/reader.o : readers/reader.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/reader-complete.o : readers/reader-complete.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/reader-incomplete.o : readers/reader-incomplete.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
	
# tnorms

$(exec)/t-norm.o : tnorms/t-norm.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-product.o : tnorms/t-norm-product.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-min.o : tnorms/t-norm-min.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-lukasiewicz.o : tnorms/t-norm-lukasiewicz.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-fodor.o : tnorms/t-norm-fodor.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-drastic.o : tnorms/t-norm-drastic.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/t-norm-einstein.o : tnorms/t-norm-einstein.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

# snorms

$(exec)/s-norm.o : snorms/s-norm.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/s-norm-sum.o : snorms/s-norm-sum.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/s-norm-max.o : snorms/s-norm-max.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/s-norm-lukasiewicz.o : snorms/s-norm-lukasiewicz.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/s-norm-fodor.o : snorms/s-norm-fodor.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/s-norm-drastic.o : snorms/s-norm-drastic.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/s-norm-einstein.o : snorms/s-norm-einstein.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

# implications
$(exec)/implication.o : implications/implication.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/imp-lukasiewicz.o : implications/imp-lukasiewicz.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/imp-rescher.o : implications/imp-rescher.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/imp-goedel.o : implications/imp-goedel.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/imp-goguen.o : implications/imp-goguen.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/imp-zadeh.o : implications/imp-zadeh.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/imp-kleene-dienes.o : implications/imp-kleene-dienes.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/imp-reichenbach.o : implications/imp-reichenbach.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/imp-fodor.o : implications/imp-fodor.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

# descriptors
$(exec)/descriptor.o : descriptors/descriptor.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-triangular.o : descriptors/descriptor-triangular.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-semitriangular.o : descriptors/descriptor-semitriangular.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-trapezoidal.o : descriptors/descriptor-trapezoidal.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-singleton.o : descriptors/descriptor-singleton.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-gaussian.o : descriptors/descriptor-gaussian.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-interval-gaussian.o : descriptors/descriptor-interval-gaussian.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-gaussian-subspace.o : descriptors/descriptor-gaussian-subspace.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-interval-gaussian-subspace.o : descriptors/descriptor-interval-gaussian-subspace.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-sigmoidal.o : descriptors/descriptor-sigmoidal.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/descriptor-constant.o : descriptors/descriptor-constant.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

	
	
# neuro-fuzzy
$(exec)/premise.o : neuro-fuzzy/premise.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/subspace-premise.o : neuro-fuzzy/subspace-premise.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/consequence.o : neuro-fuzzy/consequence.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/consequence-MA.o : neuro-fuzzy/consequence-MA.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/consequence-TSK.o : neuro-fuzzy/consequence-TSK.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/consequence-CL.o : neuro-fuzzy/consequence-CL.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/rule.o : neuro-fuzzy/rule.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/logicalrule.o : neuro-fuzzy/logicalrule.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/rulebase.o : neuro-fuzzy/rulebase.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/subspace-rulebase.o : neuro-fuzzy/subspace-rulebase.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/neuro-fuzzy-system.o : neuro-fuzzy/neuro-fuzzy-system.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/abstract-annbfis.o : neuro-fuzzy/abstract-annbfis.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/annbfis.o : neuro-fuzzy/annbfis.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcom-annbfis.o : neuro-fuzzy/fcom-annbfis.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/subspace-annbfis.o : neuro-fuzzy/subspace-annbfis.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fubi-annbfis.o : neuro-fuzzy/fubi-annbfis.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/abstract-tsk.o : neuro-fuzzy/abstract-tsk.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/tsk.o : neuro-fuzzy/tsk.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcom-tsk.o : neuro-fuzzy/fcom-tsk.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/abstract_fcom.o : neuro-fuzzy/abstract_fcom.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/abstract-ma.o : neuro-fuzzy/abstract-ma.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcom-ma.o : neuro-fuzzy/fcom-ma.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/ma.o : neuro-fuzzy/ma.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/random-neuro-fuzzy-forest.o : neuro-fuzzy/random-neuro-fuzzy-forest.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/random-neuro-fuzzy-system.o : neuro-fuzzy/random-neuro-fuzzy-system.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/annbfis_prototype.o : neuro-fuzzy/annbfis_prototype.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/tsk_prototype.o : neuro-fuzzy/tsk_prototype.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fac_prototype.o : neuro-fuzzy/fac_prototype.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/prototype.o : neuro-fuzzy/prototype.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/prototype_minkowski.o : neuro-fuzzy/prototype_minkowski.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/prototype_minkowski_regression.o : neuro-fuzzy/prototype_minkowski_regression.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/nfs_prototype.o : neuro-fuzzy/nfs_prototype.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fac_prototype_minkowski.o : neuro-fuzzy/fac_prototype_minkowski.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fac_prototype_minkowski_regression.o : neuro-fuzzy/fac_prototype_minkowski_regression.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 




# generative adversial networks
$(exec)/gan.o : gan/gan.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/generative_model.o : gan/generative_model.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/discriminative_model.o : gan/discriminative_model.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 



# dissimilarity measures
$(exec)/dissimilarity.o : dissimilarities/dissimilarity.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/dis-huber.o : dissimilarities/dis-huber.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/dis-log.o : dissimilarities/dis-log.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/dis-log-linear.o : dissimilarities/dis-log-linear.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/dis-linear.o : dissimilarities/dis-linear.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/dis-sigmoidal.o : dissimilarities/dis-sigmoidal.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/dis-sigmoidal-linear.o : dissimilarities/dis-sigmoidal-linear.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/dis-square.o : dissimilarities/dis-square.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
	

# ordered-weighted averaging	
$(exec)/owa.o : owas/owa.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/uowa.o : owas/uowa.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/plowa.o : owas/plowa.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/sowa.o : owas/sowa.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
	
	
# partitions
$(exec)/partition.o : partitions/partition.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/cluster.o : partitions/cluster.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 

$(exec)/partitioner.o : partitions/partitioner.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/partitioner-grid.o : partitions/partitioner-grid.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/dbscan.o : partitions/dbscan.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcm.o : partitions/fcm.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcm_generic.o : partitions/fcm_generic.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcm-T.o : partitions/fcm-T.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcm-possibilistic.o : partitions/fcm-possibilistic.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcm-conditional.o : partitions/fcm-conditional.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fcom.o : partitions/fcom.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/fubi.o : partitions/fubi.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/sfcm.o : partitions/sfcm.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/rfcm.o : partitions/rfcm.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/rsfcm.o : partitions/rsfcm.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/rfcom.o : partitions/rfcom.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
 
# auxiliary
$(exec)/utility-string.o : auxiliary/utility-string.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/colours.o : auxiliary/colours.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/tempus.o : auxiliary/tempus.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/roc.o : auxiliary/roc.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/utility-math.o : auxiliary/utility-math.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/least-error-squares-regression.o : auxiliary/least-error-squares-regression.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/confusion-matrix.o : auxiliary/confusion-matrix.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/clock.o : auxiliary/clock.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/mathematics.o : auxiliary/mathematics.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/vector-operators.o : auxiliary/vector-operators.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/print.o : auxiliary/print.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/directory.o : auxiliary/directory.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^


# heuristics
$(exec)/ridders.o : heuristics/ridders.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/ridders-test.o : heuristics/ridders-test.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/ridders-gaussian-m.o : heuristics/ridders-gaussian-m.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/ridders-gaussian-s.o : heuristics/ridders-gaussian-s.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/simulated-annealing.o : heuristics/simulated-annealing.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 
$(exec)/simulated-annealing-gaussian.o : heuristics/simulated-annealing-gaussian.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^ 


	
	
# experiments
$(exec)/experiment.o : experiments/experiment.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/exp-000.o : experiments/exp-000.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/exp-001.o : experiments/exp-001.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/exp-002.o : experiments/exp-002.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/exp-003.o : experiments/exp-003.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/exp-004.o : experiments/exp-004.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/exp-005.o : experiments/exp-005.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
$(exec)/exp-lab.o : experiments/exp-lab.cpp
	$(compiler) $(standard) $(debug) $(optimisation) $(pedantic) -c -o $@ $^
	
#profil : main.cpp 
#	if [ -f main ]; then rm main ; fi ;
#	$(compiler) $(standard) -o main main.cpp 
#	./main
#	gprof main > profil.txt
	
	
clean : 
	rm $(exec)/*


doxygen : 
	doxygen doxyfile
