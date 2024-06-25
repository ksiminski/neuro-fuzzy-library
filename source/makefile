
############################################
# Prosty generator plikow makefile dla g++ #
# Simple generator of makefiles for g++    #
#          Krzysztof Siminski, 2023        #
############################################

# [PL] OPCJE:
# [EN] OPTIONS:

compiler=g++
standard=-std=c++23

# [PL] optymalizacja [EN] optimisation
optRelease=-O3
optDebug=

errors=-pedantic-errors

release=
#debug=-g
# [PL] opcja -pg dla profilowania:
# [EN] -pg option for profiling:
debug=-pg

#parallel=-fopenmp
parallel=

release_folder=_release
debug_folder=_debug

#sanitizer=-fsanitize=address
#libasan=-static-libasan
sanitizer=
libasan=

#############################

.PHONY : clean $(debug_folder) $(release_folder)

# [PL] opcje uruchomienia projektu:
# [EN] project run options:
#-----------------------
# run experiments 

__ : $(release_folder) $(release_folder)/main
	./$(release_folder)/main
	
9 :  $(release_folder) $(release_folder)/main
	./$(release_folder)/main  9  
		
1 :  $(release_folder) $(release_folder)/main
	./$(release_folder)/main  1  
		
2 :  $(release_folder) $(release_folder)/main
	./$(release_folder)/main  2
		
3 :  $(release_folder) $(release_folder)/main
	./$(release_folder)/main  3
		
4 :  $(release_folder) $(release_folder)/main
	./$(release_folder)/main  4

5 :  $(release_folder) $(release_folder)/main
	./$(release_folder)/main  5

lab : $(release_folder) $(release_folder)/main
	./$(release_folder)/main  0

#-----------------------

release : $(release_folder) $(release_folder)/main
	./$(release_folder)/main

debug : $(debug_folder) $(debug_folder)/main
	valgrind --leak-check=yes ./$(debug_folder)/main
#	./$(debug_folder)/main

# [PL] profilowanie [EN] profiling
gprof : $(debug_folder) $(debug_folder)/main
	./$(debug_folder)/main
	gprof ./$(debug_folder)/main gmon.out
	rm gmon.out

# [PL] utworzenie folderow:
# [EN] create directories:

$(release_folder) : 
	mkdir -p $(release_folder)
$(debug_folder) : 
	mkdir -p $(debug_folder)

# [PL] kompilacja zrodel:
# [EN] source compilation:

$(release_folder)/descriptors-descriptor_tanh.o : descriptors/descriptor_tanh.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor_tanh.o : descriptors/descriptor_tanh.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-gaussian.o : descriptors/descriptor-gaussian.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-gaussian.o : descriptors/descriptor-gaussian.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-interval-gaussian.o : descriptors/descriptor-interval-gaussian.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-interval-gaussian.o : descriptors/descriptor-interval-gaussian.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-semitriangular.o : descriptors/descriptor-semitriangular.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-semitriangular.o : descriptors/descriptor-semitriangular.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-gaussian-subspace.o : descriptors/descriptor-gaussian-subspace.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-gaussian-subspace.o : descriptors/descriptor-gaussian-subspace.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-triangular.o : descriptors/descriptor-triangular.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-triangular.o : descriptors/descriptor-triangular.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor.o : descriptors/descriptor.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor.o : descriptors/descriptor.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-interval-gaussian-subspace.o : descriptors/descriptor-interval-gaussian-subspace.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-interval-gaussian-subspace.o : descriptors/descriptor-interval-gaussian-subspace.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor_arctan.o : descriptors/descriptor_arctan.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor_arctan.o : descriptors/descriptor_arctan.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-trapezoidal.o : descriptors/descriptor-trapezoidal.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-trapezoidal.o : descriptors/descriptor-trapezoidal.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-constant.o : descriptors/descriptor-constant.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-constant.o : descriptors/descriptor-constant.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-singleton.o : descriptors/descriptor-singleton.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-singleton.o : descriptors/descriptor-singleton.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-descriptor-sigmoidal.o : descriptors/descriptor-sigmoidal.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-sigmoidal.o : descriptors/descriptor-sigmoidal.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/descriptors-DescriptorStatistics.o : descriptors/DescriptorStatistics.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-DescriptorStatistics.o : descriptors/DescriptorStatistics.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/heuristics-ridders.o : heuristics/ridders.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-ridders.o : heuristics/ridders.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/heuristics-ridders-gaussian-s.o : heuristics/ridders-gaussian-s.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-ridders-gaussian-s.o : heuristics/ridders-gaussian-s.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/heuristics-simulated-annealing.o : heuristics/simulated-annealing.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-simulated-annealing.o : heuristics/simulated-annealing.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/heuristics-ridders-test.o : heuristics/ridders-test.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-ridders-test.o : heuristics/ridders-test.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/heuristics-simulated-annealing-gaussian.o : heuristics/simulated-annealing-gaussian.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-simulated-annealing-gaussian.o : heuristics/simulated-annealing-gaussian.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/heuristics-ridders-gaussian-m.o : heuristics/ridders-gaussian-m.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-ridders-gaussian-m.o : heuristics/ridders-gaussian-m.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-reader-complete-by-parts.o : readers/reader-complete-by-parts.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-reader-complete-by-parts.o : readers/reader-complete-by-parts.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-cross_validation_reader.o : readers/cross_validation_reader.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-cross_validation_reader.o : readers/cross_validation_reader.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-multilabel_reader_complete.o : readers/multilabel_reader_complete.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-multilabel_reader_complete.o : readers/multilabel_reader_complete.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-reader-complete.o : readers/reader-complete.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-reader-complete.o : readers/reader-complete.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-train_test_model.o : readers/train_test_model.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-train_test_model.o : readers/train_test_model.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-cross_validation_model.o : readers/cross_validation_model.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-cross_validation_model.o : readers/cross_validation_model.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-reader.o : readers/reader.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-reader.o : readers/reader.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-weighted_reader_complete.o : readers/weighted_reader_complete.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-weighted_reader_complete.o : readers/weighted_reader_complete.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-reader-incomplete.o : readers/reader-incomplete.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-reader-incomplete.o : readers/reader-incomplete.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/readers-train_validation_test_model.o : readers/train_validation_test_model.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/readers-train_validation_test_model.o : readers/train_validation_test_model.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-imp-kleene-dienes.o : implications/imp-kleene-dienes.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-kleene-dienes.o : implications/imp-kleene-dienes.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-imp-reichenbach.o : implications/imp-reichenbach.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-reichenbach.o : implications/imp-reichenbach.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-imp-rescher.o : implications/imp-rescher.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-rescher.o : implications/imp-rescher.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-implication.o : implications/implication.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-implication.o : implications/implication.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-imp-lukasiewicz.o : implications/imp-lukasiewicz.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-lukasiewicz.o : implications/imp-lukasiewicz.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-imp-goguen.o : implications/imp-goguen.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-goguen.o : implications/imp-goguen.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-imp-zadeh.o : implications/imp-zadeh.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-zadeh.o : implications/imp-zadeh.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-imp-goedel.o : implications/imp-goedel.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-goedel.o : implications/imp-goedel.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/implications-imp-fodor.o : implications/imp-fodor.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-fodor.o : implications/imp-fodor.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-mathematics.o : auxiliary/mathematics.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-mathematics.o : auxiliary/mathematics.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-error-RMSE.o : auxiliary/error-RMSE.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-error-RMSE.o : auxiliary/error-RMSE.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-utility-math.o : auxiliary/utility-math.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-utility-math.o : auxiliary/utility-math.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-utility-string.o : auxiliary/utility-string.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-utility-string.o : auxiliary/utility-string.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-error-MAE.o : auxiliary/error-MAE.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-error-MAE.o : auxiliary/error-MAE.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-colours.o : auxiliary/colours.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-colours.o : auxiliary/colours.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-directory.o : auxiliary/directory.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-directory.o : auxiliary/directory.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-vector-operators.o : auxiliary/vector-operators.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-vector-operators.o : auxiliary/vector-operators.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-error-calculator.o : auxiliary/error-calculator.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-error-calculator.o : auxiliary/error-calculator.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-least-error-squares-regression.o : auxiliary/least-error-squares-regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-least-error-squares-regression.o : auxiliary/least-error-squares-regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-clock.o : auxiliary/clock.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-clock.o : auxiliary/clock.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-tempus.o : auxiliary/tempus.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-tempus.o : auxiliary/tempus.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-to_string.o : auxiliary/to_string.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-to_string.o : auxiliary/to_string.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-confusion-matrix.o : auxiliary/confusion-matrix.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-confusion-matrix.o : auxiliary/confusion-matrix.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-multiclass_confusion_matrix.o : auxiliary/multiclass_confusion_matrix.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-multiclass_confusion_matrix.o : auxiliary/multiclass_confusion_matrix.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-numeric_function.o : auxiliary/numeric_function.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-numeric_function.o : auxiliary/numeric_function.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-print.o : auxiliary/print.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-print.o : auxiliary/print.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/auxiliary-roc.o : auxiliary/roc.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-roc.o : auxiliary/roc.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/main.o : main.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/main.o : main.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/dissimilarities-dis-huber.o : dissimilarities/dis-huber.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-huber.o : dissimilarities/dis-huber.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/dissimilarities-dis-sigmoidal-linear.o : dissimilarities/dis-sigmoidal-linear.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-sigmoidal-linear.o : dissimilarities/dis-sigmoidal-linear.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/dissimilarities-dis-log.o : dissimilarities/dis-log.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-log.o : dissimilarities/dis-log.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/dissimilarities-dis-sigmoidal.o : dissimilarities/dis-sigmoidal.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-sigmoidal.o : dissimilarities/dis-sigmoidal.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/dissimilarities-dis-linear.o : dissimilarities/dis-linear.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-linear.o : dissimilarities/dis-linear.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/dissimilarities-dissimilarity.o : dissimilarities/dissimilarity.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dissimilarity.o : dissimilarities/dissimilarity.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/dissimilarities-dis-log-linear.o : dissimilarities/dis-log-linear.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-log-linear.o : dissimilarities/dis-log-linear.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/dissimilarities-dis-square.o : dissimilarities/dis-square.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-square.o : dissimilarities/dis-square.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/gan-gan.o : gan/gan.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/gan-gan.o : gan/gan.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/gan-discriminative_model.o : gan/discriminative_model.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/gan-discriminative_model.o : gan/discriminative_model.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/gan-generative_model.o : gan/generative_model.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/gan-generative_model.o : gan/generative_model.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-nfs_prototype.o : neuro-fuzzy/nfs_prototype.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-nfs_prototype.o : neuro-fuzzy/nfs_prototype.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-abstract_fcom.o : neuro-fuzzy/abstract_fcom.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-abstract_fcom.o : neuro-fuzzy/abstract_fcom.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_minkowski.o : neuro-fuzzy/prototype_minkowski.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_minkowski.o : neuro-fuzzy/prototype_minkowski.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fubi-annbfis.o : neuro-fuzzy/fubi-annbfis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fubi-annbfis.o : neuro-fuzzy/fubi-annbfis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fcom-tsk.o : neuro-fuzzy/fcom-tsk.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fcom-tsk.o : neuro-fuzzy/fcom-tsk.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-annbfis.o : neuro-fuzzy/annbfis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-annbfis.o : neuro-fuzzy/annbfis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-rule.o : neuro-fuzzy/rule.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-rule.o : neuro-fuzzy/rule.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_mahalanobis_regression.o : neuro-fuzzy/prototype_mahalanobis_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis_regression.o : neuro-fuzzy/prototype_mahalanobis_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_minkowski_classification.o : neuro-fuzzy/prototype_minkowski_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_minkowski_classification.o : neuro-fuzzy/prototype_minkowski_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-neuro-fuzzy-system.o : neuro-fuzzy/neuro-fuzzy-system.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-neuro-fuzzy-system.o : neuro-fuzzy/neuro-fuzzy-system.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-annbfis_prototype.o : neuro-fuzzy/annbfis_prototype.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-annbfis_prototype.o : neuro-fuzzy/annbfis_prototype.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fcom-ma.o : neuro-fuzzy/fcom-ma.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fcom-ma.o : neuro-fuzzy/fcom-ma.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-consequence-CL.o : neuro-fuzzy/consequence-CL.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-consequence-CL.o : neuro-fuzzy/consequence-CL.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype.o : neuro-fuzzy/fac_prototype.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype.o : neuro-fuzzy/fac_prototype.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_nfs.o : neuro-fuzzy/granular_nfs.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_nfs.o : neuro-fuzzy/granular_nfs.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-consequence.o : neuro-fuzzy/consequence.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-consequence.o : neuro-fuzzy/consequence.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-consequence-TSK.o : neuro-fuzzy/consequence-TSK.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-consequence-TSK.o : neuro-fuzzy/consequence-TSK.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-abstract-tsk.o : neuro-fuzzy/abstract-tsk.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-abstract-tsk.o : neuro-fuzzy/abstract-tsk.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-three_way_decision_nfs.o : neuro-fuzzy/three_way_decision_nfs.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-three_way_decision_nfs.o : neuro-fuzzy/three_way_decision_nfs.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-subspace-premise.o : neuro-fuzzy/subspace-premise.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-subspace-premise.o : neuro-fuzzy/subspace-premise.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-logicalrule.o : neuro-fuzzy/logicalrule.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-logicalrule.o : neuro-fuzzy/logicalrule.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_tsk_classification.o : neuro-fuzzy/granular_tsk_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_tsk_classification.o : neuro-fuzzy/granular_tsk_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-tsk.o : neuro-fuzzy/tsk.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-tsk.o : neuro-fuzzy/tsk.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski_classification.o : neuro-fuzzy/fac_prototype_minkowski_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski_classification.o : neuro-fuzzy/fac_prototype_minkowski_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_tsk_regression.o : neuro-fuzzy/granular_tsk_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_tsk_regression.o : neuro-fuzzy/granular_tsk_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski.o : neuro-fuzzy/fac_prototype_minkowski.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski.o : neuro-fuzzy/fac_prototype_minkowski.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski_regression.o : neuro-fuzzy/fac_prototype_minkowski_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski_regression.o : neuro-fuzzy/fac_prototype_minkowski_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis_classification.o : neuro-fuzzy/fac_prototype_mahalanobis_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis_classification.o : neuro-fuzzy/fac_prototype_mahalanobis_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-tsk_prototype.o : neuro-fuzzy/tsk_prototype.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-tsk_prototype.o : neuro-fuzzy/tsk_prototype.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis_regression.o : neuro-fuzzy/fac_prototype_mahalanobis_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis_regression.o : neuro-fuzzy/fac_prototype_mahalanobis_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_ma_regression.o : neuro-fuzzy/granular_ma_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_ma_regression.o : neuro-fuzzy/granular_ma_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_subspace_annbfis_classification.o : neuro-fuzzy/granular_subspace_annbfis_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_subspace_annbfis_classification.o : neuro-fuzzy/granular_subspace_annbfis_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_subspace_annbfis_regression.o : neuro-fuzzy/granular_subspace_annbfis_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_subspace_annbfis_regression.o : neuro-fuzzy/granular_subspace_annbfis_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_nfs_regression.o : neuro-fuzzy/granular_nfs_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_nfs_regression.o : neuro-fuzzy/granular_nfs_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_mahalanobis.o : neuro-fuzzy/prototype_mahalanobis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis.o : neuro-fuzzy/prototype_mahalanobis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-abstract-ma.o : neuro-fuzzy/abstract-ma.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-abstract-ma.o : neuro-fuzzy/abstract-ma.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_minkowski_regression.o : neuro-fuzzy/prototype_minkowski_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_minkowski_regression.o : neuro-fuzzy/prototype_minkowski_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-rulebase.o : neuro-fuzzy/rulebase.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-rulebase.o : neuro-fuzzy/rulebase.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis.o : neuro-fuzzy/fac_prototype_mahalanobis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis.o : neuro-fuzzy/fac_prototype_mahalanobis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fcom-annbfis.o : neuro-fuzzy/fcom-annbfis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fcom-annbfis.o : neuro-fuzzy/fcom-annbfis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_annbfis_classification.o : neuro-fuzzy/granular_annbfis_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_annbfis_classification.o : neuro-fuzzy/granular_annbfis_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-subspace-annbfis.o : neuro-fuzzy/subspace-annbfis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-subspace-annbfis.o : neuro-fuzzy/subspace-annbfis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-consequence-MA.o : neuro-fuzzy/consequence-MA.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-consequence-MA.o : neuro-fuzzy/consequence-MA.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-weighted_annbfis.o : neuro-fuzzy/weighted_annbfis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-weighted_annbfis.o : neuro-fuzzy/weighted_annbfis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_annbfis_regression.o : neuro-fuzzy/granular_annbfis_regression.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_annbfis_regression.o : neuro-fuzzy/granular_annbfis_regression.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype.o : neuro-fuzzy/prototype.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype.o : neuro-fuzzy/prototype.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-ma.o : neuro-fuzzy/ma.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-ma.o : neuro-fuzzy/ma.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-abstract-annbfis.o : neuro-fuzzy/abstract-annbfis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-abstract-annbfis.o : neuro-fuzzy/abstract-annbfis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_ma_classification.o : neuro-fuzzy/granular_ma_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_ma_classification.o : neuro-fuzzy/granular_ma_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_mahalanobis_classification.o : neuro-fuzzy/prototype_mahalanobis_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis_classification.o : neuro-fuzzy/prototype_mahalanobis_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_nfs_classification.o : neuro-fuzzy/granular_nfs_classification.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_nfs_classification.o : neuro-fuzzy/granular_nfs_classification.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/neuro-fuzzy-premise.o : neuro-fuzzy/premise.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-premise.o : neuro-fuzzy/premise.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-marginaliser.o : common/data-modifier-marginaliser.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-marginaliser.o : common/data-modifier-marginaliser.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-standardiser.o : common/data-modifier-standardiser.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-standardiser.o : common/data-modifier-standardiser.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier.o : common/data-modifier.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier.o : common/data-modifier.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-knn-average.o : common/data-modifier-imputer-knn-average.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-knn-average.o : common/data-modifier-imputer-knn-average.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-dataset.o : common/dataset.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-dataset.o : common/dataset.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-normaliser.o : common/data-modifier-normaliser.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-normaliser.o : common/data-modifier-normaliser.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-knn.o : common/data-modifier-imputer-knn.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-knn.o : common/data-modifier-imputer-knn.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-filter.o : common/data-modifier-filter.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-filter.o : common/data-modifier-filter.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-average.o : common/data-modifier-imputer-average.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-average.o : common/data-modifier-imputer-average.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-median.o : common/data-modifier-imputer-median.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-median.o : common/data-modifier-imputer-median.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-result.o : common/result.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-result.o : common/result.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-outlier-remove-sigma.o : common/data-modifier-outlier-remove-sigma.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-outlier-remove-sigma.o : common/data-modifier-outlier-remove-sigma.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer.o : common/data-modifier-imputer.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer.o : common/data-modifier-imputer.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-values-from-knn.o : common/data-modifier-imputer-values-from-knn.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-values-from-knn.o : common/data-modifier-imputer-values-from-knn.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-knn-median.o : common/data-modifier-imputer-knn-median.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-knn-median.o : common/data-modifier-imputer-knn-median.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-datum.o : common/datum.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-datum.o : common/datum.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-extensional-fuzzy-number-gaussian.o : common/extensional-fuzzy-number-gaussian.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-extensional-fuzzy-number-gaussian.o : common/extensional-fuzzy-number-gaussian.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-DatasetStatistics.o : common/DatasetStatistics.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-DatasetStatistics.o : common/DatasetStatistics.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/common-number.o : common/number.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/common-number.o : common/number.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/snorms-s-norm-sum.o : snorms/s-norm-sum.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-sum.o : snorms/s-norm-sum.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/snorms-s-norm-einstein.o : snorms/s-norm-einstein.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-einstein.o : snorms/s-norm-einstein.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/snorms-s-norm-max.o : snorms/s-norm-max.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-max.o : snorms/s-norm-max.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/snorms-s-norm-drastic.o : snorms/s-norm-drastic.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-drastic.o : snorms/s-norm-drastic.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/snorms-s-norm-fodor.o : snorms/s-norm-fodor.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-fodor.o : snorms/s-norm-fodor.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/snorms-s-norm.o : snorms/s-norm.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm.o : snorms/s-norm.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/snorms-s-norm-lukasiewicz.o : snorms/s-norm-lukasiewicz.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-lukasiewicz.o : snorms/s-norm-lukasiewicz.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/experiments-exp-001.o : experiments/exp-001.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-001.o : experiments/exp-001.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/experiments-exp-000.o : experiments/exp-000.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-000.o : experiments/exp-000.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/experiments-experiment.o : experiments/experiment.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/experiments-experiment.o : experiments/experiment.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/experiments-exp-002.o : experiments/exp-002.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-002.o : experiments/exp-002.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/experiments-exp-003.o : experiments/exp-003.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-003.o : experiments/exp-003.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/experiments-exp-004.o : experiments/exp-004.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-004.o : experiments/exp-004.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/experiments-exp-lab.o : experiments/exp-lab.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-lab.o : experiments/exp-lab.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/experiments-exp-005.o : experiments/exp-005.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-005.o : experiments/exp-005.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-fubi.o : partitions/fubi.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fubi.o : partitions/fubi.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-partition.o : partitions/partition.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-partition.o : partitions/partition.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-granular-dbscan.o : partitions/granular-dbscan.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-granular-dbscan.o : partitions/granular-dbscan.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-grfcm.o : partitions/grfcm.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-grfcm.o : partitions/grfcm.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-partitioner.o : partitions/partitioner.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-partitioner.o : partitions/partitioner.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-rsfcm.o : partitions/rsfcm.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-rsfcm.o : partitions/rsfcm.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-fcom.o : partitions/fcom.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcom.o : partitions/fcom.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-gk.o : partitions/gk.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-gk.o : partitions/gk.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-dbscan.o : partitions/dbscan.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-dbscan.o : partitions/dbscan.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-fcm-T.o : partitions/fcm-T.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm-T.o : partitions/fcm-T.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-rfcom.o : partitions/rfcom.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-rfcom.o : partitions/rfcom.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-sfcm.o : partitions/sfcm.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-sfcm.o : partitions/sfcm.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-partitioner-grid.o : partitions/partitioner-grid.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-partitioner-grid.o : partitions/partitioner-grid.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-fcm.o : partitions/fcm.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm.o : partitions/fcm.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-fcm-conditional.o : partitions/fcm-conditional.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm-conditional.o : partitions/fcm-conditional.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-fcm-T-metrics.o : partitions/fcm-T-metrics.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm-T-metrics.o : partitions/fcm-T-metrics.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-rfcm.o : partitions/rfcm.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-rfcm.o : partitions/rfcm.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-fcm-possibilistic.o : partitions/fcm-possibilistic.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm-possibilistic.o : partitions/fcm-possibilistic.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-fcm_generic.o : partitions/fcm_generic.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm_generic.o : partitions/fcm_generic.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/partitions-cluster.o : partitions/cluster.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/partitions-cluster.o : partitions/cluster.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/granules-set_of_granules.o : granules/set_of_granules.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/granules-set_of_granules.o : granules/set_of_granules.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/granules-granule.o : granules/granule.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/granules-granule.o : granules/granule.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/granules-set_of_cooperating_granules.o : granules/set_of_cooperating_granules.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/granules-set_of_cooperating_granules.o : granules/set_of_cooperating_granules.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/granules-data_item.o : granules/data_item.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/granules-data_item.o : granules/data_item.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/granules-set_of_standalone_granules.o : granules/set_of_standalone_granules.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/granules-set_of_standalone_granules.o : granules/set_of_standalone_granules.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-min.o : tnorms/t-norm-min.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-min.o : tnorms/t-norm-min.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-schweizer-sklar.o : tnorms/t-norm-schweizer-sklar.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-schweizer-sklar.o : tnorms/t-norm-schweizer-sklar.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-yager.o : tnorms/t-norm-yager.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-yager.o : tnorms/t-norm-yager.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-frank.o : tnorms/t-norm-frank.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-frank.o : tnorms/t-norm-frank.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-lukasiewicz.o : tnorms/t-norm-lukasiewicz.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-lukasiewicz.o : tnorms/t-norm-lukasiewicz.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-dubois-prade.o : tnorms/t-norm-dubois-prade.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-dubois-prade.o : tnorms/t-norm-dubois-prade.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-parametrized.o : tnorms/t-norm-parametrized.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-parametrized.o : tnorms/t-norm-parametrized.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-product.o : tnorms/t-norm-product.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-product.o : tnorms/t-norm-product.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-drastic.o : tnorms/t-norm-drastic.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-drastic.o : tnorms/t-norm-drastic.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm.o : tnorms/t-norm.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm.o : tnorms/t-norm.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-hamacher.o : tnorms/t-norm-hamacher.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-hamacher.o : tnorms/t-norm-hamacher.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-sugeno-weber.o : tnorms/t-norm-sugeno-weber.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-sugeno-weber.o : tnorms/t-norm-sugeno-weber.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-fodor.o : tnorms/t-norm-fodor.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-fodor.o : tnorms/t-norm-fodor.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-einstein.o : tnorms/t-norm-einstein.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-einstein.o : tnorms/t-norm-einstein.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/tnorms-t-norm-dombi.o : tnorms/t-norm-dombi.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-dombi.o : tnorms/t-norm-dombi.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric-minkowski-weighted.o : metrics/metric-minkowski-weighted.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-minkowski-weighted.o : metrics/metric-minkowski-weighted.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric-minkowski.o : metrics/metric-minkowski.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-minkowski.o : metrics/metric-minkowski.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric-euclidean.o : metrics/metric-euclidean.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-euclidean.o : metrics/metric-euclidean.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric_mahalanobis.o : metrics/metric_mahalanobis.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric_mahalanobis.o : metrics/metric_mahalanobis.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric-manhattan.o : metrics/metric-manhattan.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-manhattan.o : metrics/metric-manhattan.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric-euclidean-incomplete.o : metrics/metric-euclidean-incomplete.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-euclidean-incomplete.o : metrics/metric-euclidean-incomplete.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric-cosine.o : metrics/metric-cosine.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-cosine.o : metrics/metric-cosine.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric-chebyshev.o : metrics/metric-chebyshev.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-chebyshev.o : metrics/metric-chebyshev.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/metrics-metric.o : metrics/metric.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric.o : metrics/metric.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/service-debug.o : service/debug.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/service-debug.o : service/debug.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/service-exception.o : service/exception.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/service-exception.o : service/exception.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/owas-uowa.o : owas/uowa.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/owas-uowa.o : owas/uowa.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/owas-sowa.o : owas/sowa.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/owas-sowa.o : owas/sowa.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/owas-owa.o : owas/owa.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/owas-owa.o : owas/owa.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^
$(release_folder)/owas-plowa.o : owas/plowa.cpp
	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^
$(debug_folder)/owas-plowa.o : owas/plowa.cpp
	$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^

# [PL] linkowanie:
# [EN] linking:

$(release_folder)/main : \
$(release_folder)/dissimilarities-dis-linear.o \
$(release_folder)/neuro-fuzzy-abstract-tsk.o \
$(release_folder)/service-exception.o \
$(release_folder)/neuro-fuzzy-rulebase.o \
$(release_folder)/snorms-s-norm-sum.o \
$(release_folder)/neuro-fuzzy-neuro-fuzzy-system.o \
$(release_folder)/metrics-metric-cosine.o \
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis_regression.o \
$(release_folder)/auxiliary-numeric_function.o \
$(release_folder)/neuro-fuzzy-annbfis.o \
$(release_folder)/experiments-experiment.o \
$(release_folder)/partitions-grfcm.o \
$(release_folder)/partitions-dbscan.o \
$(release_folder)/neuro-fuzzy-tsk_prototype.o \
$(release_folder)/dissimilarities-dis-log-linear.o \
$(release_folder)/readers-reader-complete.o \
$(release_folder)/implications-imp-rescher.o \
$(release_folder)/main.o \
$(release_folder)/owas-sowa.o \
$(release_folder)/experiments-exp-lab.o \
$(release_folder)/heuristics-ridders.o \
$(release_folder)/granules-set_of_cooperating_granules.o \
$(release_folder)/neuro-fuzzy-prototype_minkowski_classification.o \
$(release_folder)/dissimilarities-dis-huber.o \
$(release_folder)/common-dataset.o \
$(release_folder)/neuro-fuzzy-subspace-annbfis.o \
$(release_folder)/auxiliary-error-calculator.o \
$(release_folder)/common-result.o \
$(release_folder)/metrics-metric-chebyshev.o \
$(release_folder)/common-data-modifier-imputer-knn-average.o \
$(release_folder)/tnorms-t-norm-frank.o \
$(release_folder)/partitions-cluster.o \
$(release_folder)/readers-cross_validation_model.o \
$(release_folder)/partitions-fcm-possibilistic.o \
$(release_folder)/common-data-modifier-filter.o \
$(release_folder)/auxiliary-tempus.o \
$(release_folder)/metrics-metric-minkowski-weighted.o \
$(release_folder)/descriptors-descriptor-sigmoidal.o \
$(release_folder)/snorms-s-norm-fodor.o \
$(release_folder)/common-data-modifier-imputer-values-from-knn.o \
$(release_folder)/partitions-fcm_generic.o \
$(release_folder)/common-data-modifier-outlier-remove-sigma.o \
$(release_folder)/neuro-fuzzy-tsk.o \
$(release_folder)/common-data-modifier-imputer-median.o \
$(release_folder)/neuro-fuzzy-prototype_mahalanobis.o \
$(release_folder)/auxiliary-colours.o \
$(release_folder)/granules-granule.o \
$(release_folder)/common-extensional-fuzzy-number-gaussian.o \
$(release_folder)/metrics-metric-euclidean-incomplete.o \
$(release_folder)/snorms-s-norm-max.o \
$(release_folder)/neuro-fuzzy-granular_tsk_classification.o \
$(release_folder)/service-debug.o \
$(release_folder)/neuro-fuzzy-nfs_prototype.o \
$(release_folder)/auxiliary-roc.o \
$(release_folder)/owas-owa.o \
$(release_folder)/tnorms-t-norm-yager.o \
$(release_folder)/partitions-fcm-conditional.o \
$(release_folder)/metrics-metric-euclidean.o \
$(release_folder)/common-data-modifier.o \
$(release_folder)/neuro-fuzzy-granular_ma_regression.o \
$(release_folder)/neuro-fuzzy-granular_tsk_regression.o \
$(release_folder)/neuro-fuzzy-weighted_annbfis.o \
$(release_folder)/neuro-fuzzy-abstract_fcom.o \
$(release_folder)/auxiliary-to_string.o \
$(release_folder)/tnorms-t-norm-dubois-prade.o \
$(release_folder)/readers-reader-incomplete.o \
$(release_folder)/partitions-rsfcm.o \
$(release_folder)/auxiliary-confusion-matrix.o \
$(release_folder)/implications-imp-zadeh.o \
$(release_folder)/implications-implication.o \
$(release_folder)/tnorms-t-norm-drastic.o \
$(release_folder)/partitions-sfcm.o \
$(release_folder)/heuristics-simulated-annealing.o \
$(release_folder)/tnorms-t-norm-min.o \
$(release_folder)/neuro-fuzzy-three_way_decision_nfs.o \
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski.o \
$(release_folder)/neuro-fuzzy-logicalrule.o \
$(release_folder)/implications-imp-goedel.o \
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis.o \
$(release_folder)/neuro-fuzzy-granular_nfs_regression.o \
$(release_folder)/gan-gan.o \
$(release_folder)/common-data-modifier-marginaliser.o \
$(release_folder)/neuro-fuzzy-premise.o \
$(release_folder)/readers-reader.o \
$(release_folder)/partitions-fcm-T-metrics.o \
$(release_folder)/neuro-fuzzy-granular_nfs_classification.o \
$(release_folder)/readers-multilabel_reader_complete.o \
$(release_folder)/common-data-modifier-imputer-average.o \
$(release_folder)/neuro-fuzzy-prototype_mahalanobis_regression.o \
$(release_folder)/granules-set_of_standalone_granules.o \
$(release_folder)/partitions-rfcm.o \
$(release_folder)/neuro-fuzzy-fac_prototype.o \
$(release_folder)/descriptors-descriptor_tanh.o \
$(release_folder)/metrics-metric.o \
$(release_folder)/neuro-fuzzy-granular_subspace_annbfis_regression.o \
$(release_folder)/auxiliary-print.o \
$(release_folder)/neuro-fuzzy-subspace-premise.o \
$(release_folder)/partitions-fcm.o \
$(release_folder)/neuro-fuzzy-ma.o \
$(release_folder)/descriptors-descriptor-interval-gaussian-subspace.o \
$(release_folder)/descriptors-descriptor-triangular.o \
$(release_folder)/implications-imp-fodor.o \
$(release_folder)/readers-weighted_reader_complete.o \
$(release_folder)/snorms-s-norm-lukasiewicz.o \
$(release_folder)/tnorms-t-norm-lukasiewicz.o \
$(release_folder)/common-data-modifier-imputer-knn-median.o \
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski_classification.o \
$(release_folder)/implications-imp-kleene-dienes.o \
$(release_folder)/readers-cross_validation_reader.o \
$(release_folder)/snorms-s-norm-einstein.o \
$(release_folder)/implications-imp-reichenbach.o \
$(release_folder)/descriptors-descriptor-trapezoidal.o \
$(release_folder)/partitions-partitioner-grid.o \
$(release_folder)/neuro-fuzzy-abstract-annbfis.o \
$(release_folder)/partitions-granular-dbscan.o \
$(release_folder)/neuro-fuzzy-consequence-TSK.o \
$(release_folder)/neuro-fuzzy-consequence-CL.o \
$(release_folder)/implications-imp-lukasiewicz.o \
$(release_folder)/snorms-s-norm.o \
$(release_folder)/common-data-modifier-standardiser.o \
$(release_folder)/neuro-fuzzy-prototype.o \
$(release_folder)/neuro-fuzzy-prototype_minkowski.o \
$(release_folder)/dissimilarities-dis-sigmoidal.o \
$(release_folder)/auxiliary-directory.o \
$(release_folder)/partitions-rfcom.o \
$(release_folder)/partitions-gk.o \
$(release_folder)/auxiliary-error-MAE.o \
$(release_folder)/tnorms-t-norm-dombi.o \
$(release_folder)/descriptors-descriptor_arctan.o \
$(release_folder)/partitions-fcom.o \
$(release_folder)/partitions-partition.o \
$(release_folder)/dissimilarities-dis-square.o \
$(release_folder)/readers-reader-complete-by-parts.o \
$(release_folder)/granules-data_item.o \
$(release_folder)/common-DatasetStatistics.o \
$(release_folder)/neuro-fuzzy-fcom-annbfis.o \
$(release_folder)/experiments-exp-000.o \
$(release_folder)/common-data-modifier-imputer-knn.o \
$(release_folder)/neuro-fuzzy-rule.o \
$(release_folder)/experiments-exp-001.o \
$(release_folder)/descriptors-descriptor-gaussian.o \
$(release_folder)/experiments-exp-002.o \
$(release_folder)/gan-generative_model.o \
$(release_folder)/experiments-exp-003.o \
$(release_folder)/granules-set_of_granules.o \
$(release_folder)/experiments-exp-004.o \
$(release_folder)/descriptors-descriptor-constant.o \
$(release_folder)/tnorms-t-norm-schweizer-sklar.o \
$(release_folder)/partitions-fubi.o \
$(release_folder)/experiments-exp-005.o \
$(release_folder)/descriptors-DescriptorStatistics.o \
$(release_folder)/neuro-fuzzy-consequence.o \
$(release_folder)/dissimilarities-dis-log.o \
$(release_folder)/tnorms-t-norm-product.o \
$(release_folder)/partitions-fcm-T.o \
$(release_folder)/neuro-fuzzy-granular_subspace_annbfis_classification.o \
$(release_folder)/neuro-fuzzy-granular_nfs.o \
$(release_folder)/readers-train_test_model.o \
$(release_folder)/auxiliary-mathematics.o \
$(release_folder)/tnorms-t-norm-fodor.o \
$(release_folder)/neuro-fuzzy-consequence-MA.o \
$(release_folder)/heuristics-ridders-test.o \
$(release_folder)/descriptors-descriptor-gaussian-subspace.o \
$(release_folder)/descriptors-descriptor-singleton.o \
$(release_folder)/common-datum.o \
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski_regression.o \
$(release_folder)/readers-train_validation_test_model.o \
$(release_folder)/metrics-metric-minkowski.o \
$(release_folder)/tnorms-t-norm-sugeno-weber.o \
$(release_folder)/common-data-modifier-normaliser.o \
$(release_folder)/neuro-fuzzy-fcom-tsk.o \
$(release_folder)/auxiliary-error-RMSE.o \
$(release_folder)/tnorms-t-norm-einstein.o \
$(release_folder)/neuro-fuzzy-granular_annbfis_classification.o \
$(release_folder)/implications-imp-goguen.o \
$(release_folder)/gan-discriminative_model.o \
$(release_folder)/tnorms-t-norm.o \
$(release_folder)/partitions-partitioner.o \
$(release_folder)/neuro-fuzzy-fcom-ma.o \
$(release_folder)/dissimilarities-dis-sigmoidal-linear.o \
$(release_folder)/snorms-s-norm-drastic.o \
$(release_folder)/neuro-fuzzy-fubi-annbfis.o \
$(release_folder)/descriptors-descriptor-interval-gaussian.o \
$(release_folder)/common-data-modifier-imputer.o \
$(release_folder)/auxiliary-multiclass_confusion_matrix.o \
$(release_folder)/tnorms-t-norm-hamacher.o \
$(release_folder)/neuro-fuzzy-abstract-ma.o \
$(release_folder)/metrics-metric_mahalanobis.o \
$(release_folder)/neuro-fuzzy-annbfis_prototype.o \
$(release_folder)/owas-uowa.o \
$(release_folder)/heuristics-ridders-gaussian-m.o \
$(release_folder)/neuro-fuzzy-granular_annbfis_regression.o \
$(release_folder)/auxiliary-least-error-squares-regression.o \
$(release_folder)/neuro-fuzzy-prototype_minkowski_regression.o \
$(release_folder)/owas-plowa.o \
$(release_folder)/common-number.o \
$(release_folder)/heuristics-ridders-gaussian-s.o \
$(release_folder)/neuro-fuzzy-prototype_mahalanobis_classification.o \
$(release_folder)/auxiliary-utility-math.o \
$(release_folder)/dissimilarities-dissimilarity.o \
$(release_folder)/auxiliary-clock.o \
$(release_folder)/auxiliary-utility-string.o \
$(release_folder)/descriptors-descriptor.o \
$(release_folder)/heuristics-simulated-annealing-gaussian.o \
$(release_folder)/metrics-metric-manhattan.o \
$(release_folder)/tnorms-t-norm-parametrized.o \
$(release_folder)/neuro-fuzzy-granular_ma_classification.o \
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis_classification.o \
$(release_folder)/auxiliary-vector-operators.o \
$(release_folder)/descriptors-descriptor-semitriangular.o \

	$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -o $@ $^

$(debug_folder)/main : \
$(debug_folder)/dissimilarities-dis-linear.o \
$(debug_folder)/neuro-fuzzy-abstract-tsk.o \
$(debug_folder)/service-exception.o \
$(debug_folder)/neuro-fuzzy-rulebase.o \
$(debug_folder)/snorms-s-norm-sum.o \
$(debug_folder)/neuro-fuzzy-neuro-fuzzy-system.o \
$(debug_folder)/metrics-metric-cosine.o \
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis_regression.o \
$(debug_folder)/auxiliary-numeric_function.o \
$(debug_folder)/neuro-fuzzy-annbfis.o \
$(debug_folder)/experiments-experiment.o \
$(debug_folder)/partitions-grfcm.o \
$(debug_folder)/partitions-dbscan.o \
$(debug_folder)/neuro-fuzzy-tsk_prototype.o \
$(debug_folder)/dissimilarities-dis-log-linear.o \
$(debug_folder)/readers-reader-complete.o \
$(debug_folder)/implications-imp-rescher.o \
$(debug_folder)/main.o \
$(debug_folder)/owas-sowa.o \
$(debug_folder)/experiments-exp-lab.o \
$(debug_folder)/heuristics-ridders.o \
$(debug_folder)/granules-set_of_cooperating_granules.o \
$(debug_folder)/neuro-fuzzy-prototype_minkowski_classification.o \
$(debug_folder)/dissimilarities-dis-huber.o \
$(debug_folder)/common-dataset.o \
$(debug_folder)/neuro-fuzzy-subspace-annbfis.o \
$(debug_folder)/auxiliary-error-calculator.o \
$(debug_folder)/common-result.o \
$(debug_folder)/metrics-metric-chebyshev.o \
$(debug_folder)/common-data-modifier-imputer-knn-average.o \
$(debug_folder)/tnorms-t-norm-frank.o \
$(debug_folder)/partitions-cluster.o \
$(debug_folder)/readers-cross_validation_model.o \
$(debug_folder)/partitions-fcm-possibilistic.o \
$(debug_folder)/common-data-modifier-filter.o \
$(debug_folder)/auxiliary-tempus.o \
$(debug_folder)/metrics-metric-minkowski-weighted.o \
$(debug_folder)/descriptors-descriptor-sigmoidal.o \
$(debug_folder)/snorms-s-norm-fodor.o \
$(debug_folder)/common-data-modifier-imputer-values-from-knn.o \
$(debug_folder)/partitions-fcm_generic.o \
$(debug_folder)/common-data-modifier-outlier-remove-sigma.o \
$(debug_folder)/neuro-fuzzy-tsk.o \
$(debug_folder)/common-data-modifier-imputer-median.o \
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis.o \
$(debug_folder)/auxiliary-colours.o \
$(debug_folder)/granules-granule.o \
$(debug_folder)/common-extensional-fuzzy-number-gaussian.o \
$(debug_folder)/metrics-metric-euclidean-incomplete.o \
$(debug_folder)/snorms-s-norm-max.o \
$(debug_folder)/neuro-fuzzy-granular_tsk_classification.o \
$(debug_folder)/service-debug.o \
$(debug_folder)/neuro-fuzzy-nfs_prototype.o \
$(debug_folder)/auxiliary-roc.o \
$(debug_folder)/owas-owa.o \
$(debug_folder)/tnorms-t-norm-yager.o \
$(debug_folder)/partitions-fcm-conditional.o \
$(debug_folder)/metrics-metric-euclidean.o \
$(debug_folder)/common-data-modifier.o \
$(debug_folder)/neuro-fuzzy-granular_ma_regression.o \
$(debug_folder)/neuro-fuzzy-granular_tsk_regression.o \
$(debug_folder)/neuro-fuzzy-weighted_annbfis.o \
$(debug_folder)/neuro-fuzzy-abstract_fcom.o \
$(debug_folder)/auxiliary-to_string.o \
$(debug_folder)/tnorms-t-norm-dubois-prade.o \
$(debug_folder)/readers-reader-incomplete.o \
$(debug_folder)/partitions-rsfcm.o \
$(debug_folder)/auxiliary-confusion-matrix.o \
$(debug_folder)/implications-imp-zadeh.o \
$(debug_folder)/implications-implication.o \
$(debug_folder)/tnorms-t-norm-drastic.o \
$(debug_folder)/partitions-sfcm.o \
$(debug_folder)/heuristics-simulated-annealing.o \
$(debug_folder)/tnorms-t-norm-min.o \
$(debug_folder)/neuro-fuzzy-three_way_decision_nfs.o \
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski.o \
$(debug_folder)/neuro-fuzzy-logicalrule.o \
$(debug_folder)/implications-imp-goedel.o \
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis.o \
$(debug_folder)/neuro-fuzzy-granular_nfs_regression.o \
$(debug_folder)/gan-gan.o \
$(debug_folder)/common-data-modifier-marginaliser.o \
$(debug_folder)/neuro-fuzzy-premise.o \
$(debug_folder)/readers-reader.o \
$(debug_folder)/partitions-fcm-T-metrics.o \
$(debug_folder)/neuro-fuzzy-granular_nfs_classification.o \
$(debug_folder)/readers-multilabel_reader_complete.o \
$(debug_folder)/common-data-modifier-imputer-average.o \
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis_regression.o \
$(debug_folder)/granules-set_of_standalone_granules.o \
$(debug_folder)/partitions-rfcm.o \
$(debug_folder)/neuro-fuzzy-fac_prototype.o \
$(debug_folder)/descriptors-descriptor_tanh.o \
$(debug_folder)/metrics-metric.o \
$(debug_folder)/neuro-fuzzy-granular_subspace_annbfis_regression.o \
$(debug_folder)/auxiliary-print.o \
$(debug_folder)/neuro-fuzzy-subspace-premise.o \
$(debug_folder)/partitions-fcm.o \
$(debug_folder)/neuro-fuzzy-ma.o \
$(debug_folder)/descriptors-descriptor-interval-gaussian-subspace.o \
$(debug_folder)/descriptors-descriptor-triangular.o \
$(debug_folder)/implications-imp-fodor.o \
$(debug_folder)/readers-weighted_reader_complete.o \
$(debug_folder)/snorms-s-norm-lukasiewicz.o \
$(debug_folder)/tnorms-t-norm-lukasiewicz.o \
$(debug_folder)/common-data-modifier-imputer-knn-median.o \
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski_classification.o \
$(debug_folder)/implications-imp-kleene-dienes.o \
$(debug_folder)/readers-cross_validation_reader.o \
$(debug_folder)/snorms-s-norm-einstein.o \
$(debug_folder)/implications-imp-reichenbach.o \
$(debug_folder)/descriptors-descriptor-trapezoidal.o \
$(debug_folder)/partitions-partitioner-grid.o \
$(debug_folder)/neuro-fuzzy-abstract-annbfis.o \
$(debug_folder)/partitions-granular-dbscan.o \
$(debug_folder)/neuro-fuzzy-consequence-TSK.o \
$(debug_folder)/neuro-fuzzy-consequence-CL.o \
$(debug_folder)/implications-imp-lukasiewicz.o \
$(debug_folder)/snorms-s-norm.o \
$(debug_folder)/common-data-modifier-standardiser.o \
$(debug_folder)/neuro-fuzzy-prototype.o \
$(debug_folder)/neuro-fuzzy-prototype_minkowski.o \
$(debug_folder)/dissimilarities-dis-sigmoidal.o \
$(debug_folder)/auxiliary-directory.o \
$(debug_folder)/partitions-rfcom.o \
$(debug_folder)/partitions-gk.o \
$(debug_folder)/auxiliary-error-MAE.o \
$(debug_folder)/tnorms-t-norm-dombi.o \
$(debug_folder)/descriptors-descriptor_arctan.o \
$(debug_folder)/partitions-fcom.o \
$(debug_folder)/partitions-partition.o \
$(debug_folder)/dissimilarities-dis-square.o \
$(debug_folder)/readers-reader-complete-by-parts.o \
$(debug_folder)/granules-data_item.o \
$(debug_folder)/common-DatasetStatistics.o \
$(debug_folder)/neuro-fuzzy-fcom-annbfis.o \
$(debug_folder)/experiments-exp-000.o \
$(debug_folder)/common-data-modifier-imputer-knn.o \
$(debug_folder)/neuro-fuzzy-rule.o \
$(debug_folder)/experiments-exp-001.o \
$(debug_folder)/descriptors-descriptor-gaussian.o \
$(debug_folder)/experiments-exp-002.o \
$(debug_folder)/gan-generative_model.o \
$(debug_folder)/experiments-exp-003.o \
$(debug_folder)/granules-set_of_granules.o \
$(debug_folder)/experiments-exp-004.o \
$(debug_folder)/descriptors-descriptor-constant.o \
$(debug_folder)/tnorms-t-norm-schweizer-sklar.o \
$(debug_folder)/partitions-fubi.o \
$(debug_folder)/experiments-exp-005.o \
$(debug_folder)/descriptors-DescriptorStatistics.o \
$(debug_folder)/neuro-fuzzy-consequence.o \
$(debug_folder)/dissimilarities-dis-log.o \
$(debug_folder)/tnorms-t-norm-product.o \
$(debug_folder)/partitions-fcm-T.o \
$(debug_folder)/neuro-fuzzy-granular_subspace_annbfis_classification.o \
$(debug_folder)/neuro-fuzzy-granular_nfs.o \
$(debug_folder)/readers-train_test_model.o \
$(debug_folder)/auxiliary-mathematics.o \
$(debug_folder)/tnorms-t-norm-fodor.o \
$(debug_folder)/neuro-fuzzy-consequence-MA.o \
$(debug_folder)/heuristics-ridders-test.o \
$(debug_folder)/descriptors-descriptor-gaussian-subspace.o \
$(debug_folder)/descriptors-descriptor-singleton.o \
$(debug_folder)/common-datum.o \
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski_regression.o \
$(debug_folder)/readers-train_validation_test_model.o \
$(debug_folder)/metrics-metric-minkowski.o \
$(debug_folder)/tnorms-t-norm-sugeno-weber.o \
$(debug_folder)/common-data-modifier-normaliser.o \
$(debug_folder)/neuro-fuzzy-fcom-tsk.o \
$(debug_folder)/auxiliary-error-RMSE.o \
$(debug_folder)/tnorms-t-norm-einstein.o \
$(debug_folder)/neuro-fuzzy-granular_annbfis_classification.o \
$(debug_folder)/implications-imp-goguen.o \
$(debug_folder)/gan-discriminative_model.o \
$(debug_folder)/tnorms-t-norm.o \
$(debug_folder)/partitions-partitioner.o \
$(debug_folder)/neuro-fuzzy-fcom-ma.o \
$(debug_folder)/dissimilarities-dis-sigmoidal-linear.o \
$(debug_folder)/snorms-s-norm-drastic.o \
$(debug_folder)/neuro-fuzzy-fubi-annbfis.o \
$(debug_folder)/descriptors-descriptor-interval-gaussian.o \
$(debug_folder)/common-data-modifier-imputer.o \
$(debug_folder)/auxiliary-multiclass_confusion_matrix.o \
$(debug_folder)/tnorms-t-norm-hamacher.o \
$(debug_folder)/neuro-fuzzy-abstract-ma.o \
$(debug_folder)/metrics-metric_mahalanobis.o \
$(debug_folder)/neuro-fuzzy-annbfis_prototype.o \
$(debug_folder)/owas-uowa.o \
$(debug_folder)/heuristics-ridders-gaussian-m.o \
$(debug_folder)/neuro-fuzzy-granular_annbfis_regression.o \
$(debug_folder)/auxiliary-least-error-squares-regression.o \
$(debug_folder)/neuro-fuzzy-prototype_minkowski_regression.o \
$(debug_folder)/owas-plowa.o \
$(debug_folder)/common-number.o \
$(debug_folder)/heuristics-ridders-gaussian-s.o \
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis_classification.o \
$(debug_folder)/auxiliary-utility-math.o \
$(debug_folder)/dissimilarities-dissimilarity.o \
$(debug_folder)/auxiliary-clock.o \
$(debug_folder)/auxiliary-utility-string.o \
$(debug_folder)/descriptors-descriptor.o \
$(debug_folder)/heuristics-simulated-annealing-gaussian.o \
$(debug_folder)/metrics-metric-manhattan.o \
$(debug_folder)/tnorms-t-norm-parametrized.o \
$(debug_folder)/neuro-fuzzy-granular_ma_classification.o \
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis_classification.o \
$(debug_folder)/auxiliary-vector-operators.o \
$(debug_folder)/descriptors-descriptor-semitriangular.o \

	$(compiler) $(standard) $(debug) $(optDebug) $(parallel) $(errors) $(sanitizer) $(libasan) -o $@ $^

# [PL] usuniecie plikow skompilowanych:
# [EN] remove compiled files:

clean : 
	if [ -d $(debug_folder)      ] ; then rm -r $(debug_folder)   ; fi
	if [ -d $(release_folder)    ] ; then rm -r $(release_folder) ; fi;


5-minutes:
	find $(release_folder)/ -maxdepth 1 -type f -mmin -5 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mmin -5 -delete

10-minutes:
	find $(release_folder)/ -maxdepth 1 -type f -mmin -10 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mmin -10 -delete

30-minutes:
	find $(release_folder)/ -maxdepth 1 -type f -mmin -30 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mmin -30 -delete

60-minutes:
	find $(release_folder)/ -maxdepth 1 -type f -mmin -60 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mmin -60 -delete

1-days:
	find $(release_folder)/ -maxdepth 1 -type f -mtime -1 -delete
	find $(debug_folder)/ -maxdepth 1 -type f -mtime -1 -delete

doxygen:
	doxygen doxyfile

