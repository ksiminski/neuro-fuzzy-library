/** @file */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <chrono>
#include <fstream> 

#include "../neuro-fuzzy/premise.h"
#include "../descriptors/descriptor-gaussian.h"
#include "../descriptors/descriptor-triangular.h"
#include "../descriptors/descriptor-semitriangular.h"
#include "../descriptors/descriptor-sigmoidal.h"
#include "../descriptors/descriptor_arctan.h"
#include "../descriptors/descriptor_tanh.h"
#include "../descriptors/descriptor-trapezoidal.h"
#include "../descriptors/descriptor-triangular.h"
#include "../neuro-fuzzy/consequence-MA.h"
#include "../neuro-fuzzy/consequence-TSK.h"
#include "../neuro-fuzzy/rule.h"
#include "../neuro-fuzzy/rulebase.h"
#include "../tnorms/t-norm-lukasiewicz.h"
#include "../tnorms/t-norm-product.h"
#include "../tnorms/t-norm-min.h"
#include "../tnorms/t-norm-fodor.h"
#include "../tnorms/t-norm-dubois-prade.h"
#include "../tnorms/t-norm-einstein.h"
#include "../auxiliary/definitions.h"
#include "../implications/imp-reichenbach.h"
#include "../neuro-fuzzy/ma.h"
#include "../neuro-fuzzy/tsk.h"
#include "../neuro-fuzzy/annbfis.h"

#include "../service/debug.h"

#include "../experiments/exp-lab.h"



void ksi::exp_lab::execute()
{
	try 
	{
		// [PL] system rozmyty 
		// [EN] fuzzy system
		fuzzy_system();

		// [PL] system neuronowo-rozmyty 
		//  Proszę sprawdzić, jaki wygląda model wypracowany przez system neuronowo-rozmyty dla danych z zadania Z1. W tym celu należy odkomentować ponizsza linie. Zostaną utworozne dwa pliki results-neuro-fuzzy-MA i results-neuro-fuzzy-TSK.

		// [EN] neuro-fuzzy system
		// Uncomment the commented line below. Now two neuro-fuzzy systems (MA and TSK) are run for the data set. Compare your results with the results elaborated by the neuro-fuzzy systems. Try to interpret fuzzy rule bases produced by the systems.

		neuro_fuzzy_system();
	}    
	CATCH;
}

void ksi::exp_lab::fuzzy_system()
{
	try 
	{
		// [PL] ADIIO
		//
		// Pewien system ma dwa wejścia i jedno wyjście. Wartości wejść mają wartości z zakresu od ok. 0 do ok. 10. Wartości wyjścia są od ok. 0 do ok. 10. Od eksperta dziedzinowego wiemy, że wyjście systemu powinno być niskie, jeżeli wartości obu atrybutów są albo jednocześnie duże, albo jednocześnie małe. Gdy jeden z atrybutów ma wartość dużą, a drugi małą, to wyjście systemu powinno być wysokie. 
		// 		
		// 	Proszę skonstruować bazę reguł rozmytych dla systemu MA, tak by wartości błędu RMSE dla danych treningowych były jak najmniejsze. W katalogu data/exp-lab zostanie utworzony plik results-fuzzy-MA. 

		// [EN] DAACI
		// 
		// A system has two inputs and one output. Approximate range of input values is 0-10. Output values from approx. 0 to approx. 10. An expert says the output of the system is low, if both inputs are simultaneously low or high. The output is high, if one input is low and the other high. 
		// 
		// Construct a fuzzy rule base for a MA fuzzy system to reduce the output root mean square error (RMSE) for the train set. The system produces the result file results-fuzzy-MA in the directory data/exp-lab.

		////////////////////////////////////////////////////////////////////////////////////
		
		// [PL] Proszę zapisać reguły zidentyfikowane w opisie eksperta.
		// [EN] Please write down the rules indentified in the expert's description.
		
		
		
		
		
		
		
		
		
		// [PL] Jakie zmienne lingwistyczne występują w regułach?
		// [EN] What linguistic variables can you find in the rules?
		
		
		
		// [PL] Proszę zamodelować zmienne lingwistyczne przy użyciu poniższych deskryptorów (zbiorów rozmytych).
		// [EN] Please model the linguistic variables with the descriptors (fuzzy sets) below.

		// [PL] deskryptory (dostępne klasy)
		// [EN] descriptors (available classes)
		//         ksi::descriptor_gaussian
		//         ksi::descriptor_semitriangular
		//         ksi::descriptor_triangular
		//         ksi::descriptor_trapezoidal
		//         ksi::descriptor_sigmoidal
		//         ksi::descriptor_arctan
		//         ksi::descriptor_tanh



		// [PL] T-normy (dostępne klasy)
		// [EN] T-norms (available classes)
		//          ksi::t_norm_lukasiewicz
		//          ksi::t_norm_min
		//          ksi::t_norm_product
		//          ksi::t_norm_fodor 
		//          ksi::t_norm_dubois_prade
		//          ksi::t_norm_einstein
		
		


		// [PL] przesłanka
		// [EN] premise
		//          ksi::premise P1;
		// [PL] dodanie deskryptora do przesłanki: 
		// [EN] add descriptor to a premise
		//          P1.addDescriptor(D11);

		// [PL] konkluzja
		// [EN] consequence
		//          ksi::consequence_MA C1 (support_min, core, support_max);

		// [PL] utworzenie reguły z przesłanki, konkluzji i t-normy:
		// [EN] compose the premise, consequence and t-norm into a rule
		//          ksi::rule R1 (tnorm);
		//          R1.setPremise(P1);
		//          R1.setConsequence(C1);         

		// [PL] dodanie reguł do bazy reguł      
		// [EN] add a rule to a fuzzy rule base
		//          ksi::rulebase Rulebase;         
		//          Rulebase.addRule(R1);

		// [PL] system rozmyty Mamdamiego-Assilana
		// [EN] Mamdani-Assilan fuzzy system
		ksi::ma MA;

		// [PL] ustawienie systemowi bazy reguł 
		// [EN] set the composed fuzzy rule base
		//          MA.set_rulebase(Rulebase);



		// [PL] wykonanie eksperymentu
		// [EN] run an experiment
		std::vector<ksi::neuro_fuzzy_system *> systems { & MA };

		const std::string DIRECTORY ("../data/exp-lab");
		const std::string TRAIN     (DIRECTORY + "/train.txt");
		const std::string RESULTS   (DIRECTORY + "/results-fuzzy.txt");
		const bool NORMALISATION = false;

		for (auto p : systems)
		{
			p->elaborate_answers_for_regression(TRAIN, RESULTS + "-" + p->get_nfs_name(), NORMALISATION);
		}

		std::cout << "done" << std::endl;
	}
	CATCH;
}

void ksi::exp_lab::neuro_fuzzy_system()
{
	try 
	{
		// regression 
		const std::string DIRECTORY ("../data/exp-lab");
		const std::string TRAIN   (DIRECTORY + "/train"); 
		const std::string TEST    (DIRECTORY + "/test");
		const std::string RESULTS (DIRECTORY + "/results-neuro-fuzzy");
		const int NUMBER_OF_RULES = 4;
		const int NUMBER_OF_CLUSTERING_ITERATIONS = 1000;
		const int NUMBER_OF_TUNING_ITERATIONS     = 1000;
		const double ETA = 0.0005;
		const bool NORMALISATION = false;
		const ksi::t_norm_product TNORM;

		ksi::ma MA (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, TNORM);
		ksi::tsk TSK (NUMBER_OF_RULES, NUMBER_OF_CLUSTERING_ITERATIONS, NUMBER_OF_TUNING_ITERATIONS, ETA, NORMALISATION, TNORM);

		std::vector<ksi::neuro_fuzzy_system *> systems { & MA,  & TSK };


		for (auto p : systems)
		{
			p->experiment_regression(TRAIN, TEST, RESULTS + "-" + p->get_nfs_name());
		}

		std::cout << "done" << std::endl;
	}
	CATCH;
}


