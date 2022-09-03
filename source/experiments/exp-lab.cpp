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
		fuzzy_system();
		// neuro_fuzzy_system();
	}    
	CATCH;
}

void ksi::exp_lab::fuzzy_system()
{
	try 
	{
		// [PL] deskryptory
		// [EN] descriptors
		//         ksi::descriptor_gaussian
		//         ksi::descriptor_semitriangular
		//         ksi::descriptor_sigmoidal
		//         ksi::descriptor_triangular
      //         ksi::descriptor_trapezoidal
					


		// [PL] T-normy
		// [EN] T-norms
		//          ksi::t_norm_lukasiewicz
		//          ksi::t_norm_min
		//          ksi::t_norm_product
		//          ksi::t_norm_fodor 


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

		const std::string DIRECTORY ("data/exp-lab");
		const std::string TRAIN   (DIRECTORY + "/train"), 
				RESULTS (DIRECTORY + "/results-fuzzy");
		const bool NORMALISATION = false;

		for (auto p : systems)
		{
			p->elaborate_answers_for_regression(TRAIN, 
					RESULTS + "-" + p->get_nfs_name(),
					NORMALISATION);
		}
	}
	CATCH;
}

void ksi::exp_lab::neuro_fuzzy_system()
{
	try 
	{
		// regression 

		ksi::ma MA;
		ksi::tsk TSK;

		std::vector<ksi::neuro_fuzzy_system *> systems { & MA,  & TSK };

		const std::string DIRECTORY ("data/exp-lab");
		const std::string TRAIN   (DIRECTORY + "/train"), 
				TEST    (DIRECTORY + "/test"),
				RESULTS (DIRECTORY + "/results-neuro-fuzzy");
		const int NUMBER_OF_RULES = 4;
		const int NUMBER_OF_CLUSTERING_ITERATIONS = 1000;
		const int NUMBER_OF_TUNING_ITERATIONS     = 1000;
		const double ETA = 0.0005;
		const bool NORMALISATION = false;

		for (auto p : systems)
		{
			p->experiment_regression(TRAIN, TEST, 
					RESULTS + "-" + p->get_nfs_name(),
					NUMBER_OF_RULES,
					NUMBER_OF_CLUSTERING_ITERATIONS,
					NUMBER_OF_TUNING_ITERATIONS, ETA,
					NORMALISATION);
		}
	}
	CATCH;
}


