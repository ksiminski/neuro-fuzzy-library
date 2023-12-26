
#############################
# Generator plikow makefile #
# Krzysztof Siminski, 2023  #
#############################

# STALE:
kompilator=g++
standard=-std=c++23

optRelease=-O3
optDebug=

errors=-pedantic-errors

release=
debug=-g

#rownoleglosc=-fopenmp
rownoleglosc=

release_folder=_release
debug_folder=_debug

#############################

.PHONY : clean $(debug_folder) $(release_folder)


#-----------------------
# run experiments 

__ : $(release_folder) $(release_folder)/main
	./$(release_folder)/main
	
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

# opcje uruchomienia projektu:

release : $(release_folder) $(release_folder)/main
	./$(release_folder)/main

debug : $(debug_folder) $(debug_folder)/main
	valgrind --leak-check=yes ./$(debug_folder)/main

# utworzenie folderow:

$(release_folder) : 
	mkdir -p $(release_folder)
$(debug_folder) : 
	mkdir -p $(debug_folder)

# kompilacja zrodel:

$(release_folder)/descriptors-descriptor_tanh.o : descriptors/descriptor_tanh.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor_tanh.o : descriptors/descriptor_tanh.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-gaussian.o : descriptors/descriptor-gaussian.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-gaussian.o : descriptors/descriptor-gaussian.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-interval-gaussian.o : descriptors/descriptor-interval-gaussian.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-interval-gaussian.o : descriptors/descriptor-interval-gaussian.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-semitriangular.o : descriptors/descriptor-semitriangular.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-semitriangular.o : descriptors/descriptor-semitriangular.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-gaussian-subspace.o : descriptors/descriptor-gaussian-subspace.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-gaussian-subspace.o : descriptors/descriptor-gaussian-subspace.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-triangular.o : descriptors/descriptor-triangular.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-triangular.o : descriptors/descriptor-triangular.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor.o : descriptors/descriptor.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor.o : descriptors/descriptor.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-interval-gaussian-subspace.o : descriptors/descriptor-interval-gaussian-subspace.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-interval-gaussian-subspace.o : descriptors/descriptor-interval-gaussian-subspace.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor_arctan.o : descriptors/descriptor_arctan.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor_arctan.o : descriptors/descriptor_arctan.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-trapezoidal.o : descriptors/descriptor-trapezoidal.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-trapezoidal.o : descriptors/descriptor-trapezoidal.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-constant.o : descriptors/descriptor-constant.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-constant.o : descriptors/descriptor-constant.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-singleton.o : descriptors/descriptor-singleton.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-singleton.o : descriptors/descriptor-singleton.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/descriptors-descriptor-sigmoidal.o : descriptors/descriptor-sigmoidal.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/descriptors-descriptor-sigmoidal.o : descriptors/descriptor-sigmoidal.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/heuristics-ridders.o : heuristics/ridders.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-ridders.o : heuristics/ridders.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/heuristics-ridders-gaussian-s.o : heuristics/ridders-gaussian-s.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-ridders-gaussian-s.o : heuristics/ridders-gaussian-s.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/heuristics-simulated-annealing.o : heuristics/simulated-annealing.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-simulated-annealing.o : heuristics/simulated-annealing.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/heuristics-ridders-test.o : heuristics/ridders-test.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-ridders-test.o : heuristics/ridders-test.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/heuristics-simulated-annealing-gaussian.o : heuristics/simulated-annealing-gaussian.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-simulated-annealing-gaussian.o : heuristics/simulated-annealing-gaussian.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/heuristics-ridders-gaussian-m.o : heuristics/ridders-gaussian-m.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/heuristics-ridders-gaussian-m.o : heuristics/ridders-gaussian-m.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/readers-reader-complete-by-parts.o : readers/reader-complete-by-parts.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/readers-reader-complete-by-parts.o : readers/reader-complete-by-parts.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/readers-cross_validation_reader.o : readers/cross_validation_reader.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/readers-cross_validation_reader.o : readers/cross_validation_reader.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/readers-multilabel_reader_complete.o : readers/multilabel_reader_complete.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/readers-multilabel_reader_complete.o : readers/multilabel_reader_complete.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/readers-reader-complete.o : readers/reader-complete.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/readers-reader-complete.o : readers/reader-complete.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/readers-reader.o : readers/reader.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/readers-reader.o : readers/reader.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/readers-weighted_reader_complete.o : readers/weighted_reader_complete.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/readers-weighted_reader_complete.o : readers/weighted_reader_complete.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/readers-reader-incomplete.o : readers/reader-incomplete.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/readers-reader-incomplete.o : readers/reader-incomplete.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-imp-kleene-dienes.o : implications/imp-kleene-dienes.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-kleene-dienes.o : implications/imp-kleene-dienes.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-imp-reichenbach.o : implications/imp-reichenbach.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-reichenbach.o : implications/imp-reichenbach.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-imp-rescher.o : implications/imp-rescher.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-rescher.o : implications/imp-rescher.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-implication.o : implications/implication.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-implication.o : implications/implication.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-imp-lukasiewicz.o : implications/imp-lukasiewicz.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-lukasiewicz.o : implications/imp-lukasiewicz.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-imp-goguen.o : implications/imp-goguen.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-goguen.o : implications/imp-goguen.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-imp-zadeh.o : implications/imp-zadeh.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-zadeh.o : implications/imp-zadeh.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-imp-goedel.o : implications/imp-goedel.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-goedel.o : implications/imp-goedel.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/implications-imp-fodor.o : implications/imp-fodor.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/implications-imp-fodor.o : implications/imp-fodor.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-mathematics.o : auxiliary/mathematics.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-mathematics.o : auxiliary/mathematics.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-error-RMSE.o : auxiliary/error-RMSE.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-error-RMSE.o : auxiliary/error-RMSE.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-utility-math.o : auxiliary/utility-math.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-utility-math.o : auxiliary/utility-math.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-utility-string.o : auxiliary/utility-string.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-utility-string.o : auxiliary/utility-string.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-error-MAE.o : auxiliary/error-MAE.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-error-MAE.o : auxiliary/error-MAE.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-colours.o : auxiliary/colours.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-colours.o : auxiliary/colours.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-directory.o : auxiliary/directory.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-directory.o : auxiliary/directory.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-vector-operators.o : auxiliary/vector-operators.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-vector-operators.o : auxiliary/vector-operators.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-error-calculator.o : auxiliary/error-calculator.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-error-calculator.o : auxiliary/error-calculator.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-least-error-squares-regression.o : auxiliary/least-error-squares-regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-least-error-squares-regression.o : auxiliary/least-error-squares-regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-clock.o : auxiliary/clock.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-clock.o : auxiliary/clock.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-tempus.o : auxiliary/tempus.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-tempus.o : auxiliary/tempus.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-confusion-matrix.o : auxiliary/confusion-matrix.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-confusion-matrix.o : auxiliary/confusion-matrix.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-multiclass_confusion_matrix.o : auxiliary/multiclass_confusion_matrix.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-multiclass_confusion_matrix.o : auxiliary/multiclass_confusion_matrix.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-numeric_function.o : auxiliary/numeric_function.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-numeric_function.o : auxiliary/numeric_function.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-print.o : auxiliary/print.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-print.o : auxiliary/print.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/auxiliary-roc.o : auxiliary/roc.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/auxiliary-roc.o : auxiliary/roc.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/main.o : main.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/main.o : main.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/dissimilarities-dis-huber.o : dissimilarities/dis-huber.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-huber.o : dissimilarities/dis-huber.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/dissimilarities-dis-sigmoidal-linear.o : dissimilarities/dis-sigmoidal-linear.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-sigmoidal-linear.o : dissimilarities/dis-sigmoidal-linear.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/dissimilarities-dis-log.o : dissimilarities/dis-log.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-log.o : dissimilarities/dis-log.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/dissimilarities-dis-sigmoidal.o : dissimilarities/dis-sigmoidal.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-sigmoidal.o : dissimilarities/dis-sigmoidal.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/dissimilarities-dis-linear.o : dissimilarities/dis-linear.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-linear.o : dissimilarities/dis-linear.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/dissimilarities-dissimilarity.o : dissimilarities/dissimilarity.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dissimilarity.o : dissimilarities/dissimilarity.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/dissimilarities-dis-log-linear.o : dissimilarities/dis-log-linear.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-log-linear.o : dissimilarities/dis-log-linear.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/dissimilarities-dis-square.o : dissimilarities/dis-square.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/dissimilarities-dis-square.o : dissimilarities/dis-square.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/gan-gan.o : gan/gan.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/gan-gan.o : gan/gan.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/gan-discriminative_model.o : gan/discriminative_model.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/gan-discriminative_model.o : gan/discriminative_model.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/gan-generative_model.o : gan/generative_model.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/gan-generative_model.o : gan/generative_model.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-nfs_prototype.o : neuro-fuzzy/nfs_prototype.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-nfs_prototype.o : neuro-fuzzy/nfs_prototype.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-abstract_fcom.o : neuro-fuzzy/abstract_fcom.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-abstract_fcom.o : neuro-fuzzy/abstract_fcom.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_minkowski.o : neuro-fuzzy/prototype_minkowski.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_minkowski.o : neuro-fuzzy/prototype_minkowski.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fubi-annbfis.o : neuro-fuzzy/fubi-annbfis.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fubi-annbfis.o : neuro-fuzzy/fubi-annbfis.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fcom-tsk.o : neuro-fuzzy/fcom-tsk.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fcom-tsk.o : neuro-fuzzy/fcom-tsk.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-annbfis.o : neuro-fuzzy/annbfis.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-annbfis.o : neuro-fuzzy/annbfis.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-rule.o : neuro-fuzzy/rule.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-rule.o : neuro-fuzzy/rule.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_mahalanobis_regression.o : neuro-fuzzy/prototype_mahalanobis_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis_regression.o : neuro-fuzzy/prototype_mahalanobis_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_minkowski_classification.o : neuro-fuzzy/prototype_minkowski_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_minkowski_classification.o : neuro-fuzzy/prototype_minkowski_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-neuro-fuzzy-system.o : neuro-fuzzy/neuro-fuzzy-system.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-neuro-fuzzy-system.o : neuro-fuzzy/neuro-fuzzy-system.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-annbfis_prototype.o : neuro-fuzzy/annbfis_prototype.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-annbfis_prototype.o : neuro-fuzzy/annbfis_prototype.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fcom-ma.o : neuro-fuzzy/fcom-ma.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fcom-ma.o : neuro-fuzzy/fcom-ma.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-consequence-CL.o : neuro-fuzzy/consequence-CL.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-consequence-CL.o : neuro-fuzzy/consequence-CL.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype.o : neuro-fuzzy/fac_prototype.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype.o : neuro-fuzzy/fac_prototype.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_nfs.o : neuro-fuzzy/granular_nfs.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_nfs.o : neuro-fuzzy/granular_nfs.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-consequence.o : neuro-fuzzy/consequence.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-consequence.o : neuro-fuzzy/consequence.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-consequence-TSK.o : neuro-fuzzy/consequence-TSK.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-consequence-TSK.o : neuro-fuzzy/consequence-TSK.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-abstract-tsk.o : neuro-fuzzy/abstract-tsk.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-abstract-tsk.o : neuro-fuzzy/abstract-tsk.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-three_way_decision_nfs.o : neuro-fuzzy/three_way_decision_nfs.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-three_way_decision_nfs.o : neuro-fuzzy/three_way_decision_nfs.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-subspace-premise.o : neuro-fuzzy/subspace-premise.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-subspace-premise.o : neuro-fuzzy/subspace-premise.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-logicalrule.o : neuro-fuzzy/logicalrule.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-logicalrule.o : neuro-fuzzy/logicalrule.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_tsk_classification.o : neuro-fuzzy/granular_tsk_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_tsk_classification.o : neuro-fuzzy/granular_tsk_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-tsk.o : neuro-fuzzy/tsk.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-tsk.o : neuro-fuzzy/tsk.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski_classification.o : neuro-fuzzy/fac_prototype_minkowski_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski_classification.o : neuro-fuzzy/fac_prototype_minkowski_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_tsk_regression.o : neuro-fuzzy/granular_tsk_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_tsk_regression.o : neuro-fuzzy/granular_tsk_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski.o : neuro-fuzzy/fac_prototype_minkowski.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski.o : neuro-fuzzy/fac_prototype_minkowski.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_minkowski_regression.o : neuro-fuzzy/fac_prototype_minkowski_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_minkowski_regression.o : neuro-fuzzy/fac_prototype_minkowski_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis_classification.o : neuro-fuzzy/fac_prototype_mahalanobis_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis_classification.o : neuro-fuzzy/fac_prototype_mahalanobis_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-tsk_prototype.o : neuro-fuzzy/tsk_prototype.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-tsk_prototype.o : neuro-fuzzy/tsk_prototype.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis_regression.o : neuro-fuzzy/fac_prototype_mahalanobis_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis_regression.o : neuro-fuzzy/fac_prototype_mahalanobis_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_ma_regression.o : neuro-fuzzy/granular_ma_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_ma_regression.o : neuro-fuzzy/granular_ma_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_subspace_annbfis_classification.o : neuro-fuzzy/granular_subspace_annbfis_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_subspace_annbfis_classification.o : neuro-fuzzy/granular_subspace_annbfis_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_subspace_annbfis_regression.o : neuro-fuzzy/granular_subspace_annbfis_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_subspace_annbfis_regression.o : neuro-fuzzy/granular_subspace_annbfis_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_nfs_regression.o : neuro-fuzzy/granular_nfs_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_nfs_regression.o : neuro-fuzzy/granular_nfs_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_mahalanobis.o : neuro-fuzzy/prototype_mahalanobis.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis.o : neuro-fuzzy/prototype_mahalanobis.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-abstract-ma.o : neuro-fuzzy/abstract-ma.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-abstract-ma.o : neuro-fuzzy/abstract-ma.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_minkowski_regression.o : neuro-fuzzy/prototype_minkowski_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_minkowski_regression.o : neuro-fuzzy/prototype_minkowski_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-rulebase.o : neuro-fuzzy/rulebase.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-rulebase.o : neuro-fuzzy/rulebase.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis.o : neuro-fuzzy/fac_prototype_mahalanobis.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis.o : neuro-fuzzy/fac_prototype_mahalanobis.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-fcom-annbfis.o : neuro-fuzzy/fcom-annbfis.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-fcom-annbfis.o : neuro-fuzzy/fcom-annbfis.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_annbfis_classification.o : neuro-fuzzy/granular_annbfis_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_annbfis_classification.o : neuro-fuzzy/granular_annbfis_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-subspace-annbfis.o : neuro-fuzzy/subspace-annbfis.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-subspace-annbfis.o : neuro-fuzzy/subspace-annbfis.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-consequence-MA.o : neuro-fuzzy/consequence-MA.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-consequence-MA.o : neuro-fuzzy/consequence-MA.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_annbfis_regression.o : neuro-fuzzy/granular_annbfis_regression.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_annbfis_regression.o : neuro-fuzzy/granular_annbfis_regression.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype.o : neuro-fuzzy/prototype.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype.o : neuro-fuzzy/prototype.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-ma.o : neuro-fuzzy/ma.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-ma.o : neuro-fuzzy/ma.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-abstract-annbfis.o : neuro-fuzzy/abstract-annbfis.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-abstract-annbfis.o : neuro-fuzzy/abstract-annbfis.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_ma_classification.o : neuro-fuzzy/granular_ma_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_ma_classification.o : neuro-fuzzy/granular_ma_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-prototype_mahalanobis_classification.o : neuro-fuzzy/prototype_mahalanobis_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-prototype_mahalanobis_classification.o : neuro-fuzzy/prototype_mahalanobis_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-granular_nfs_classification.o : neuro-fuzzy/granular_nfs_classification.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-granular_nfs_classification.o : neuro-fuzzy/granular_nfs_classification.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/neuro-fuzzy-premise.o : neuro-fuzzy/premise.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/neuro-fuzzy-premise.o : neuro-fuzzy/premise.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-marginaliser.o : common/data-modifier-marginaliser.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-marginaliser.o : common/data-modifier-marginaliser.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-standardiser.o : common/data-modifier-standardiser.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-standardiser.o : common/data-modifier-standardiser.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier.o : common/data-modifier.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier.o : common/data-modifier.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-knn-average.o : common/data-modifier-imputer-knn-average.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-knn-average.o : common/data-modifier-imputer-knn-average.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-dataset.o : common/dataset.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-dataset.o : common/dataset.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-normaliser.o : common/data-modifier-normaliser.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-normaliser.o : common/data-modifier-normaliser.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-knn.o : common/data-modifier-imputer-knn.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-knn.o : common/data-modifier-imputer-knn.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-filter.o : common/data-modifier-filter.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-filter.o : common/data-modifier-filter.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-average.o : common/data-modifier-imputer-average.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-average.o : common/data-modifier-imputer-average.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-median.o : common/data-modifier-imputer-median.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-median.o : common/data-modifier-imputer-median.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-result.o : common/result.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-result.o : common/result.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-outlier-remove-sigma.o : common/data-modifier-outlier-remove-sigma.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-outlier-remove-sigma.o : common/data-modifier-outlier-remove-sigma.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer.o : common/data-modifier-imputer.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer.o : common/data-modifier-imputer.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-values-from-knn.o : common/data-modifier-imputer-values-from-knn.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-values-from-knn.o : common/data-modifier-imputer-values-from-knn.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-data-modifier-imputer-knn-median.o : common/data-modifier-imputer-knn-median.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-data-modifier-imputer-knn-median.o : common/data-modifier-imputer-knn-median.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-datum.o : common/datum.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-datum.o : common/datum.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-extensional-fuzzy-number-gaussian.o : common/extensional-fuzzy-number-gaussian.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-extensional-fuzzy-number-gaussian.o : common/extensional-fuzzy-number-gaussian.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/common-number.o : common/number.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/common-number.o : common/number.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/snorms-s-norm-sum.o : snorms/s-norm-sum.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-sum.o : snorms/s-norm-sum.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/snorms-s-norm-einstein.o : snorms/s-norm-einstein.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-einstein.o : snorms/s-norm-einstein.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/snorms-s-norm-max.o : snorms/s-norm-max.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-max.o : snorms/s-norm-max.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/snorms-s-norm-drastic.o : snorms/s-norm-drastic.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-drastic.o : snorms/s-norm-drastic.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/snorms-s-norm-fodor.o : snorms/s-norm-fodor.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-fodor.o : snorms/s-norm-fodor.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/snorms-s-norm.o : snorms/s-norm.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm.o : snorms/s-norm.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/snorms-s-norm-lukasiewicz.o : snorms/s-norm-lukasiewicz.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/snorms-s-norm-lukasiewicz.o : snorms/s-norm-lukasiewicz.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/experiments-exp-001.o : experiments/exp-001.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-001.o : experiments/exp-001.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/experiments-exp-000.o : experiments/exp-000.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-000.o : experiments/exp-000.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/experiments-experiment.o : experiments/experiment.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/experiments-experiment.o : experiments/experiment.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/experiments-exp-002.o : experiments/exp-002.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-002.o : experiments/exp-002.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/experiments-exp-003.o : experiments/exp-003.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-003.o : experiments/exp-003.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/experiments-exp-004.o : experiments/exp-004.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-004.o : experiments/exp-004.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/experiments-exp-lab.o : experiments/exp-lab.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-lab.o : experiments/exp-lab.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/experiments-exp-005.o : experiments/exp-005.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/experiments-exp-005.o : experiments/exp-005.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-fubi.o : partitions/fubi.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fubi.o : partitions/fubi.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-partition.o : partitions/partition.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-partition.o : partitions/partition.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-granular-dbscan.o : partitions/granular-dbscan.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-granular-dbscan.o : partitions/granular-dbscan.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-grfcm.o : partitions/grfcm.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-grfcm.o : partitions/grfcm.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-partitioner.o : partitions/partitioner.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-partitioner.o : partitions/partitioner.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-rsfcm.o : partitions/rsfcm.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-rsfcm.o : partitions/rsfcm.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-fcom.o : partitions/fcom.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcom.o : partitions/fcom.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-gk.o : partitions/gk.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-gk.o : partitions/gk.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-dbscan.o : partitions/dbscan.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-dbscan.o : partitions/dbscan.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^

$(release_folder)/partitions-fcm-T-metrics.o : partitions/fcm-T-metrics.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm-T-metrics.o : partitions/fcm-T-metrics.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^

$(release_folder)/partitions-fcm-T.o : partitions/fcm-T.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm-T.o : partitions/fcm-T.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-rfcom.o : partitions/rfcom.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-rfcom.o : partitions/rfcom.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-sfcm.o : partitions/sfcm.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-sfcm.o : partitions/sfcm.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-partitioner-grid.o : partitions/partitioner-grid.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-partitioner-grid.o : partitions/partitioner-grid.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-fcm.o : partitions/fcm.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm.o : partitions/fcm.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-fcm-conditional.o : partitions/fcm-conditional.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm-conditional.o : partitions/fcm-conditional.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-rfcm.o : partitions/rfcm.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-rfcm.o : partitions/rfcm.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-fcm-possibilistic.o : partitions/fcm-possibilistic.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm-possibilistic.o : partitions/fcm-possibilistic.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-fcm_generic.o : partitions/fcm_generic.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-fcm_generic.o : partitions/fcm_generic.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/partitions-cluster.o : partitions/cluster.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/partitions-cluster.o : partitions/cluster.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/granules-set_of_granules.o : granules/set_of_granules.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/granules-set_of_granules.o : granules/set_of_granules.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/granules-granule.o : granules/granule.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/granules-granule.o : granules/granule.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/granules-set_of_cooperating_granules.o : granules/set_of_cooperating_granules.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/granules-set_of_cooperating_granules.o : granules/set_of_cooperating_granules.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/granules-data_item.o : granules/data_item.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/granules-data_item.o : granules/data_item.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/granules-set_of_standalone_granules.o : granules/set_of_standalone_granules.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/granules-set_of_standalone_granules.o : granules/set_of_standalone_granules.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-min.o : tnorms/t-norm-min.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-min.o : tnorms/t-norm-min.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-schweizer-sklar.o : tnorms/t-norm-schweizer-sklar.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-schweizer-sklar.o : tnorms/t-norm-schweizer-sklar.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-yager.o : tnorms/t-norm-yager.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-yager.o : tnorms/t-norm-yager.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-frank.o : tnorms/t-norm-frank.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-frank.o : tnorms/t-norm-frank.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-lukasiewicz.o : tnorms/t-norm-lukasiewicz.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-lukasiewicz.o : tnorms/t-norm-lukasiewicz.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-dubois-prade.o : tnorms/t-norm-dubois-prade.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-dubois-prade.o : tnorms/t-norm-dubois-prade.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-parametrized.o : tnorms/t-norm-parametrized.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-parametrized.o : tnorms/t-norm-parametrized.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-product.o : tnorms/t-norm-product.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-product.o : tnorms/t-norm-product.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-drastic.o : tnorms/t-norm-drastic.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-drastic.o : tnorms/t-norm-drastic.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm.o : tnorms/t-norm.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm.o : tnorms/t-norm.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-hamacher.o : tnorms/t-norm-hamacher.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-hamacher.o : tnorms/t-norm-hamacher.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-sugeno-weber.o : tnorms/t-norm-sugeno-weber.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-sugeno-weber.o : tnorms/t-norm-sugeno-weber.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-fodor.o : tnorms/t-norm-fodor.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-fodor.o : tnorms/t-norm-fodor.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-einstein.o : tnorms/t-norm-einstein.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-einstein.o : tnorms/t-norm-einstein.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/tnorms-t-norm-dombi.o : tnorms/t-norm-dombi.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/tnorms-t-norm-dombi.o : tnorms/t-norm-dombi.cpp


	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/metrics-metric-minkowski-weighted.o : metrics/metric-minkowski-weighted.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-minkowski-weighted.o : metrics/metric-minkowski-weighted.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/metrics-metric-minkowski.o : metrics/metric-minkowski.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-minkowski.o : metrics/metric-minkowski.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/metrics-metric-chebyshev.o : metrics/metric-chebyshev.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-chebyshev.o : metrics/metric-chebyshev.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/metrics-metric-cosine.o : metrics/metric-cosine.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-cosine.o : metrics/metric-cosine.cpp
$(release_folder)/metrics-metric-manhattan.o : metrics/metric-manhattan.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-manhattan.o : metrics/metric-manhattan.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/metrics-metric-euclidean.o : metrics/metric-euclidean.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-euclidean.o : metrics/metric-euclidean.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/metrics-metric_mahalanobis.o : metrics/metric_mahalanobis.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric_mahalanobis.o : metrics/metric_mahalanobis.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/metrics-metric-euclidean-incomplete.o : metrics/metric-euclidean-incomplete.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric-euclidean-incomplete.o : metrics/metric-euclidean-incomplete.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/metrics-metric.o : metrics/metric.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/metrics-metric.o : metrics/metric.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/service-debug.o : service/debug.cpp


	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/service-debug.o : service/debug.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/service-exception.o : service/exception.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/service-exception.o : service/exception.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/owas-uowa.o : owas/uowa.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/owas-uowa.o : owas/uowa.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/owas-sowa.o : owas/sowa.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/owas-sowa.o : owas/sowa.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/owas-owa.o : owas/owa.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/owas-owa.o : owas/owa.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^
$(release_folder)/owas-plowa.o : owas/plowa.cpp
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -c -o $@ $^
$(debug_folder)/owas-plowa.o : owas/plowa.cpp
	$(kompilator) $(standard) $(debug) $(optyDebug) $(rownoleglosc) $(errors) -c -o $@ $^

# linkowanie:

$(release_folder)/main : $(release_folder)/descriptors-descriptor-gaussian.o $(release_folder)/descriptors-descriptor-interval-gaussian.o $(release_folder)/descriptors-descriptor-semitriangular.o $(release_folder)/descriptors-descriptor-gaussian-subspace.o $(release_folder)/descriptors-descriptor-triangular.o $(release_folder)/descriptors-descriptor.o $(release_folder)/descriptors-descriptor-interval-gaussian-subspace.o $(release_folder)/descriptors-descriptor-trapezoidal.o $(release_folder)/descriptors-descriptor-constant.o $(release_folder)/descriptors-descriptor-singleton.o $(release_folder)/descriptors-descriptor-sigmoidal.o $(release_folder)/heuristics-ridders.o $(release_folder)/heuristics-ridders-gaussian-s.o $(release_folder)/heuristics-simulated-annealing.o $(release_folder)/heuristics-ridders-test.o $(release_folder)/heuristics-simulated-annealing-gaussian.o $(release_folder)/heuristics-ridders-gaussian-m.o $(release_folder)/readers-reader-complete-by-parts.o $(release_folder)/readers-cross_validation_reader.o $(release_folder)/readers-multilabel_reader_complete.o $(release_folder)/readers-reader-complete.o $(release_folder)/readers-reader.o $(release_folder)/readers-weighted_reader_complete.o $(release_folder)/readers-reader-incomplete.o $(release_folder)/implications-imp-kleene-dienes.o $(release_folder)/implications-imp-reichenbach.o $(release_folder)/implications-imp-rescher.o $(release_folder)/implications-implication.o $(release_folder)/implications-imp-lukasiewicz.o $(release_folder)/implications-imp-goguen.o $(release_folder)/implications-imp-zadeh.o $(release_folder)/implications-imp-goedel.o $(release_folder)/implications-imp-fodor.o $(release_folder)/auxiliary-mathematics.o $(release_folder)/auxiliary-error-RMSE.o $(release_folder)/auxiliary-utility-math.o $(release_folder)/auxiliary-utility-string.o $(release_folder)/auxiliary-error-MAE.o $(release_folder)/auxiliary-colours.o $(release_folder)/auxiliary-directory.o $(release_folder)/auxiliary-vector-operators.o $(release_folder)/auxiliary-error-calculator.o $(release_folder)/auxiliary-least-error-squares-regression.o $(release_folder)/auxiliary-clock.o $(release_folder)/auxiliary-tempus.o $(release_folder)/auxiliary-confusion-matrix.o $(release_folder)/auxiliary-multiclass_confusion_matrix.o $(release_folder)/auxiliary-numeric_function.o $(release_folder)/auxiliary-print.o $(release_folder)/auxiliary-roc.o $(release_folder)/main.o $(release_folder)/dissimilarities-dis-huber.o $(release_folder)/dissimilarities-dis-sigmoidal-linear.o $(release_folder)/dissimilarities-dis-log.o $(release_folder)/dissimilarities-dis-sigmoidal.o $(release_folder)/dissimilarities-dis-linear.o $(release_folder)/dissimilarities-dissimilarity.o $(release_folder)/dissimilarities-dis-log-linear.o $(release_folder)/dissimilarities-dis-square.o $(release_folder)/gan-gan.o $(release_folder)/gan-discriminative_model.o $(release_folder)/gan-generative_model.o $(release_folder)/neuro-fuzzy-nfs_prototype.o $(release_folder)/neuro-fuzzy-abstract_fcom.o $(release_folder)/neuro-fuzzy-prototype_minkowski.o $(release_folder)/neuro-fuzzy-fubi-annbfis.o $(release_folder)/neuro-fuzzy-fcom-tsk.o $(release_folder)/neuro-fuzzy-annbfis.o $(release_folder)/neuro-fuzzy-rule.o $(release_folder)/neuro-fuzzy-prototype_mahalanobis_regression.o $(release_folder)/neuro-fuzzy-prototype_minkowski_classification.o $(release_folder)/neuro-fuzzy-neuro-fuzzy-system.o $(release_folder)/neuro-fuzzy-annbfis_prototype.o $(release_folder)/neuro-fuzzy-fcom-ma.o $(release_folder)/neuro-fuzzy-consequence-CL.o $(release_folder)/neuro-fuzzy-fac_prototype.o $(release_folder)/neuro-fuzzy-granular_nfs.o $(release_folder)/neuro-fuzzy-consequence.o $(release_folder)/neuro-fuzzy-consequence-TSK.o $(release_folder)/neuro-fuzzy-abstract-tsk.o $(release_folder)/neuro-fuzzy-three_way_decision_nfs.o $(release_folder)/neuro-fuzzy-subspace-premise.o $(release_folder)/neuro-fuzzy-logicalrule.o $(release_folder)/neuro-fuzzy-granular_tsk_classification.o $(release_folder)/neuro-fuzzy-tsk.o $(release_folder)/neuro-fuzzy-fac_prototype_minkowski_classification.o $(release_folder)/neuro-fuzzy-granular_tsk_regression.o $(release_folder)/neuro-fuzzy-fac_prototype_minkowski.o $(release_folder)/neuro-fuzzy-fac_prototype_minkowski_regression.o $(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis_classification.o $(release_folder)/neuro-fuzzy-tsk_prototype.o $(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis_regression.o $(release_folder)/neuro-fuzzy-granular_ma_regression.o $(release_folder)/neuro-fuzzy-granular_subspace_annbfis_classification.o $(release_folder)/neuro-fuzzy-granular_subspace_annbfis_regression.o $(release_folder)/neuro-fuzzy-granular_nfs_regression.o $(release_folder)/neuro-fuzzy-prototype_mahalanobis.o $(release_folder)/neuro-fuzzy-abstract-ma.o $(release_folder)/neuro-fuzzy-prototype_minkowski_regression.o $(release_folder)/neuro-fuzzy-rulebase.o $(release_folder)/neuro-fuzzy-fac_prototype_mahalanobis.o $(release_folder)/neuro-fuzzy-fcom-annbfis.o $(release_folder)/neuro-fuzzy-granular_annbfis_classification.o $(release_folder)/neuro-fuzzy-subspace-annbfis.o $(release_folder)/neuro-fuzzy-consequence-MA.o $(release_folder)/neuro-fuzzy-granular_annbfis_regression.o $(release_folder)/neuro-fuzzy-prototype.o $(release_folder)/neuro-fuzzy-ma.o $(release_folder)/neuro-fuzzy-abstract-annbfis.o $(release_folder)/neuro-fuzzy-granular_ma_classification.o $(release_folder)/neuro-fuzzy-prototype_mahalanobis_classification.o $(release_folder)/neuro-fuzzy-granular_nfs_classification.o $(release_folder)/neuro-fuzzy-premise.o $(release_folder)/common-data-modifier-marginaliser.o $(release_folder)/common-data-modifier-standardiser.o $(release_folder)/common-data-modifier.o $(release_folder)/common-data-modifier-imputer-knn-average.o $(release_folder)/common-dataset.o $(release_folder)/common-data-modifier-normaliser.o $(release_folder)/common-data-modifier-imputer-knn.o $(release_folder)/common-data-modifier-filter.o $(release_folder)/common-data-modifier-imputer-average.o $(release_folder)/common-data-modifier-imputer-median.o $(release_folder)/common-result.o $(release_folder)/common-data-modifier-outlier-remove-sigma.o $(release_folder)/common-data-modifier-imputer.o $(release_folder)/common-data-modifier-imputer-values-from-knn.o $(release_folder)/common-data-modifier-imputer-knn-median.o $(release_folder)/common-datum.o $(release_folder)/common-extensional-fuzzy-number-gaussian.o $(release_folder)/common-number.o $(release_folder)/snorms-s-norm-sum.o $(release_folder)/snorms-s-norm-einstein.o $(release_folder)/snorms-s-norm-max.o $(release_folder)/snorms-s-norm-drastic.o $(release_folder)/snorms-s-norm-fodor.o $(release_folder)/snorms-s-norm.o $(release_folder)/snorms-s-norm-lukasiewicz.o $(release_folder)/experiments-exp-001.o $(release_folder)/experiments-exp-000.o $(release_folder)/experiments-experiment.o $(release_folder)/experiments-exp-002.o $(release_folder)/experiments-exp-003.o $(release_folder)/experiments-exp-004.o $(release_folder)/experiments-exp-lab.o $(release_folder)/experiments-exp-005.o $(release_folder)/partitions-fubi.o $(release_folder)/partitions-partition.o $(release_folder)/partitions-granular-dbscan.o $(release_folder)/partitions-grfcm.o $(release_folder)/partitions-partitioner.o $(release_folder)/partitions-rsfcm.o $(release_folder)/partitions-fcom.o $(release_folder)/partitions-gk.o $(release_folder)/partitions-dbscan.o $(release_folder)/partitions-fcm-T.o $(release_folder)/partitions-rfcom.o $(release_folder)/partitions-sfcm.o $(release_folder)/partitions-partitioner-grid.o $(release_folder)/partitions-fcm.o $(release_folder)/partitions-fcm-conditional.o $(release_folder)/partitions-rfcm.o $(release_folder)/partitions-fcm-possibilistic.o $(release_folder)/partitions-fcm_generic.o $(release_folder)/partitions-cluster.o $(release_folder)/granules-set_of_granules.o $(release_folder)/granules-granule.o $(release_folder)/granules-set_of_cooperating_granules.o $(release_folder)/granules-data_item.o $(release_folder)/granules-set_of_standalone_granules.o $(release_folder)/tnorms-t-norm-min.o $(release_folder)/tnorms-t-norm-schweizer-sklar.o $(release_folder)/tnorms-t-norm-yager.o $(release_folder)/tnorms-t-norm-frank.o $(release_folder)/tnorms-t-norm-lukasiewicz.o $(release_folder)/tnorms-t-norm-dubois-prade.o $(release_folder)/tnorms-t-norm-parametrized.o $(release_folder)/tnorms-t-norm-product.o $(release_folder)/tnorms-t-norm-drastic.o $(release_folder)/tnorms-t-norm.o $(release_folder)/tnorms-t-norm-hamacher.o $(release_folder)/tnorms-t-norm-sugeno-weber.o $(release_folder)/tnorms-t-norm-fodor.o $(release_folder)/tnorms-t-norm-einstein.o $(release_folder)/tnorms-t-norm-dombi.o $(release_folder)/metrics-metric-minkowski-weighted.o $(release_folder)/metrics-metric-manhattan.o $(release_folder)/metrics-metric-chebyshev.o $(release_folder)/metrics-metric-cosine.o $(release_folder)/metrics-metric-minkowski.o $(release_folder)/metrics-metric-euclidean.o $(release_folder)/metrics-metric_mahalanobis.o $(release_folder)/metrics-metric-euclidean-incomplete.o $(release_folder)/metrics-metric.o $(release_folder)/service-debug.o $(release_folder)/service-exception.o $(release_folder)/owas-uowa.o $(release_folder)/owas-sowa.o $(release_folder)/owas-owa.o $(release_folder)/owas-plowa.o $(release_folder)/descriptors-descriptor_tanh.o $(release_folder)/descriptors-descriptor_arctan.o $(release_folder)/partitions-fcm-T-metrics.o
	$(kompilator) $(standard) $(release) $(optRelease) $(rownoleglosc) $(errors) -o $@ $^

$(debug_folder)/main : $(debug_folder)/descriptors-descriptor-gaussian.o $(debug_folder)/descriptors-descriptor-interval-gaussian.o $(debug_folder)/descriptors-descriptor-semitriangular.o $(debug_folder)/descriptors-descriptor-gaussian-subspace.o $(debug_folder)/descriptors-descriptor-triangular.o $(debug_folder)/descriptors-descriptor.o $(debug_folder)/descriptors-descriptor-interval-gaussian-subspace.o $(debug_folder)/descriptors-descriptor-trapezoidal.o $(debug_folder)/descriptors-descriptor-constant.o $(debug_folder)/descriptors-descriptor-singleton.o $(debug_folder)/descriptors-descriptor-sigmoidal.o $(debug_folder)/heuristics-ridders.o $(debug_folder)/heuristics-ridders-gaussian-s.o $(debug_folder)/heuristics-simulated-annealing.o $(debug_folder)/heuristics-ridders-test.o $(debug_folder)/heuristics-simulated-annealing-gaussian.o $(debug_folder)/heuristics-ridders-gaussian-m.o $(debug_folder)/readers-reader-complete-by-parts.o $(debug_folder)/readers-cross_validation_reader.o $(debug_folder)/readers-multilabel_reader_complete.o $(debug_folder)/readers-reader-complete.o $(debug_folder)/readers-reader.o $(debug_folder)/readers-weighted_reader_complete.o $(debug_folder)/readers-reader-incomplete.o $(debug_folder)/implications-imp-kleene-dienes.o $(debug_folder)/implications-imp-reichenbach.o $(debug_folder)/implications-imp-rescher.o $(debug_folder)/implications-implication.o $(debug_folder)/implications-imp-lukasiewicz.o $(debug_folder)/implications-imp-goguen.o $(debug_folder)/implications-imp-zadeh.o $(debug_folder)/implications-imp-goedel.o $(debug_folder)/implications-imp-fodor.o $(debug_folder)/auxiliary-mathematics.o $(debug_folder)/auxiliary-error-RMSE.o $(debug_folder)/auxiliary-utility-math.o $(debug_folder)/auxiliary-utility-string.o $(debug_folder)/auxiliary-error-MAE.o $(debug_folder)/auxiliary-colours.o $(debug_folder)/auxiliary-directory.o $(debug_folder)/auxiliary-vector-operators.o $(debug_folder)/auxiliary-error-calculator.o $(debug_folder)/auxiliary-least-error-squares-regression.o $(debug_folder)/auxiliary-clock.o $(debug_folder)/auxiliary-tempus.o $(debug_folder)/auxiliary-confusion-matrix.o $(debug_folder)/auxiliary-multiclass_confusion_matrix.o $(debug_folder)/auxiliary-numeric_function.o $(debug_folder)/auxiliary-print.o $(debug_folder)/auxiliary-roc.o $(debug_folder)/main.o $(debug_folder)/dissimilarities-dis-huber.o $(debug_folder)/dissimilarities-dis-sigmoidal-linear.o $(debug_folder)/dissimilarities-dis-log.o $(debug_folder)/dissimilarities-dis-sigmoidal.o $(debug_folder)/dissimilarities-dis-linear.o $(debug_folder)/dissimilarities-dissimilarity.o $(debug_folder)/dissimilarities-dis-log-linear.o $(debug_folder)/dissimilarities-dis-square.o $(debug_folder)/gan-gan.o $(debug_folder)/gan-discriminative_model.o $(debug_folder)/gan-generative_model.o $(debug_folder)/neuro-fuzzy-nfs_prototype.o $(debug_folder)/neuro-fuzzy-abstract_fcom.o $(debug_folder)/neuro-fuzzy-prototype_minkowski.o $(debug_folder)/neuro-fuzzy-fubi-annbfis.o $(debug_folder)/neuro-fuzzy-fcom-tsk.o $(debug_folder)/neuro-fuzzy-annbfis.o $(debug_folder)/neuro-fuzzy-rule.o $(debug_folder)/neuro-fuzzy-prototype_mahalanobis_regression.o $(debug_folder)/neuro-fuzzy-prototype_minkowski_classification.o $(debug_folder)/neuro-fuzzy-neuro-fuzzy-system.o $(debug_folder)/neuro-fuzzy-annbfis_prototype.o $(debug_folder)/neuro-fuzzy-fcom-ma.o $(debug_folder)/neuro-fuzzy-consequence-CL.o $(debug_folder)/neuro-fuzzy-fac_prototype.o $(debug_folder)/neuro-fuzzy-granular_nfs.o $(debug_folder)/neuro-fuzzy-consequence.o $(debug_folder)/neuro-fuzzy-consequence-TSK.o $(debug_folder)/neuro-fuzzy-abstract-tsk.o $(debug_folder)/neuro-fuzzy-three_way_decision_nfs.o $(debug_folder)/neuro-fuzzy-subspace-premise.o $(debug_folder)/neuro-fuzzy-logicalrule.o $(debug_folder)/neuro-fuzzy-granular_tsk_classification.o $(debug_folder)/neuro-fuzzy-tsk.o $(debug_folder)/neuro-fuzzy-fac_prototype_minkowski_classification.o $(debug_folder)/neuro-fuzzy-granular_tsk_regression.o $(debug_folder)/neuro-fuzzy-fac_prototype_minkowski.o $(debug_folder)/neuro-fuzzy-fac_prototype_minkowski_regression.o $(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis_classification.o $(debug_folder)/neuro-fuzzy-tsk_prototype.o $(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis_regression.o $(debug_folder)/neuro-fuzzy-granular_ma_regression.o $(debug_folder)/neuro-fuzzy-granular_subspace_annbfis_classification.o $(debug_folder)/neuro-fuzzy-granular_subspace_annbfis_regression.o $(debug_folder)/neuro-fuzzy-granular_nfs_regression.o $(debug_folder)/neuro-fuzzy-prototype_mahalanobis.o $(debug_folder)/neuro-fuzzy-abstract-ma.o $(debug_folder)/neuro-fuzzy-prototype_minkowski_regression.o $(debug_folder)/neuro-fuzzy-rulebase.o $(debug_folder)/neuro-fuzzy-fac_prototype_mahalanobis.o $(debug_folder)/neuro-fuzzy-fcom-annbfis.o $(debug_folder)/neuro-fuzzy-granular_annbfis_classification.o $(debug_folder)/neuro-fuzzy-subspace-annbfis.o $(debug_folder)/neuro-fuzzy-consequence-MA.o $(debug_folder)/neuro-fuzzy-granular_annbfis_regression.o $(debug_folder)/neuro-fuzzy-prototype.o $(debug_folder)/neuro-fuzzy-ma.o $(debug_folder)/neuro-fuzzy-abstract-annbfis.o $(debug_folder)/neuro-fuzzy-granular_ma_classification.o $(debug_folder)/neuro-fuzzy-prototype_mahalanobis_classification.o $(debug_folder)/neuro-fuzzy-granular_nfs_classification.o $(debug_folder)/neuro-fuzzy-premise.o $(debug_folder)/common-data-modifier-marginaliser.o $(debug_folder)/common-data-modifier-standardiser.o $(debug_folder)/common-data-modifier.o $(debug_folder)/common-data-modifier-imputer-knn-average.o $(debug_folder)/common-dataset.o $(debug_folder)/common-data-modifier-normaliser.o $(debug_folder)/common-data-modifier-imputer-knn.o $(debug_folder)/common-data-modifier-filter.o $(debug_folder)/common-data-modifier-imputer-average.o $(debug_folder)/common-data-modifier-imputer-median.o $(debug_folder)/common-result.o $(debug_folder)/common-data-modifier-outlier-remove-sigma.o $(debug_folder)/common-data-modifier-imputer.o $(debug_folder)/common-data-modifier-imputer-values-from-knn.o $(debug_folder)/common-data-modifier-imputer-knn-median.o $(debug_folder)/common-datum.o $(debug_folder)/common-extensional-fuzzy-number-gaussian.o $(debug_folder)/common-number.o $(debug_folder)/snorms-s-norm-sum.o $(debug_folder)/snorms-s-norm-einstein.o $(debug_folder)/snorms-s-norm-max.o $(debug_folder)/snorms-s-norm-drastic.o $(debug_folder)/snorms-s-norm-fodor.o $(debug_folder)/snorms-s-norm.o $(debug_folder)/snorms-s-norm-lukasiewicz.o $(debug_folder)/experiments-exp-001.o $(debug_folder)/experiments-exp-000.o $(debug_folder)/experiments-experiment.o $(debug_folder)/experiments-exp-002.o $(debug_folder)/experiments-exp-003.o $(debug_folder)/experiments-exp-004.o $(debug_folder)/experiments-exp-lab.o $(debug_folder)/experiments-exp-005.o $(debug_folder)/partitions-fubi.o $(debug_folder)/partitions-partition.o $(debug_folder)/partitions-granular-dbscan.o $(debug_folder)/partitions-grfcm.o $(debug_folder)/partitions-partitioner.o $(debug_folder)/partitions-rsfcm.o $(debug_folder)/partitions-fcom.o $(debug_folder)/partitions-gk.o $(debug_folder)/partitions-dbscan.o $(debug_folder)/partitions-fcm-T.o $(debug_folder)/partitions-rfcom.o $(debug_folder)/partitions-sfcm.o $(debug_folder)/partitions-partitioner-grid.o $(debug_folder)/partitions-fcm.o $(debug_folder)/partitions-fcm-conditional.o $(debug_folder)/partitions-rfcm.o $(debug_folder)/partitions-fcm-possibilistic.o $(debug_folder)/partitions-fcm_generic.o $(debug_folder)/partitions-cluster.o $(debug_folder)/granules-set_of_granules.o $(debug_folder)/granules-granule.o $(debug_folder)/granules-set_of_cooperating_granules.o $(debug_folder)/granules-data_item.o $(debug_folder)/granules-set_of_standalone_granules.o $(debug_folder)/tnorms-t-norm-min.o $(debug_folder)/tnorms-t-norm-schweizer-sklar.o $(debug_folder)/tnorms-t-norm-yager.o $(debug_folder)/tnorms-t-norm-frank.o $(debug_folder)/tnorms-t-norm-lukasiewicz.o $(debug_folder)/tnorms-t-norm-dubois-prade.o $(debug_folder)/tnorms-t-norm-parametrized.o $(debug_folder)/tnorms-t-norm-product.o $(debug_folder)/tnorms-t-norm-drastic.o $(debug_folder)/tnorms-t-norm.o $(debug_folder)/tnorms-t-norm-hamacher.o $(debug_folder)/tnorms-t-norm-sugeno-weber.o $(debug_folder)/tnorms-t-norm-fodor.o $(debug_folder)/tnorms-t-norm-einstein.o $(debug_folder)/tnorms-t-norm-dombi.o $(debug_folder)/metrics-metric-minkowski-weighted.o $(debug_folder)/metrics-metric-manhattan.o $(debug_folder)/metrics-metric-chebyshev.o $(debug_folder)/metrics-metric-cosine.o $(debug_folder)/metrics-metric-minkowski.o $(debug_folder)/metrics-metric-euclidean.o $(debug_folder)/metrics-metric_mahalanobis.o $(debug_folder)/metrics-metric-euclidean-incomplete.o $(debug_folder)/metrics-metric.o $(debug_folder)/service-debug.o $(debug_folder)/service-exception.o $(debug_folder)/owas-uowa.o $(debug_folder)/owas-sowa.o $(debug_folder)/owas-owa.o $(debug_folder)/owas-plowa.o $(debug_folder)/descriptors-descriptor_tanh.o $(debug_folder)/descriptors-descriptor_arctan.o $(debug_folder)/partitions-fcm-T-metrics.o 
	$(kompilator) $(standard) $(debug) $(optDebug) $(rownoleglosc) $(errors) -o $@ $^

# usuniecie plikow skompilowanych:

clean : 
	if [ -d $(debug_folder)      ] ; then rm -r $(debug_folder)   ; fi
	if [ -d $(release_folder)    ] ; then rm -r $(release_folder) ; fi;


