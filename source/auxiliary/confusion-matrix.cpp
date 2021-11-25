/** @file */

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "../auxiliary/confusion-matrix.h"
#include "../auxiliary/mathematics.h"
#include "../service/debug.h"


std::string ksi::confusion_matrix::ca(int n)
{
   std::stringstream ss;
   const int WIDTH = 14;
   ss << std::setw(WIDTH) << n;
   return ss.str();
}

std::string ksi::confusion_matrix::ul(double d)
{
   std::stringstream ss;
   const int WIDTH = 14;
   const int PRECISION = 9;
   ss << std::setw(WIDTH) << std::fixed << std::setprecision(PRECISION) << d;
   return ss.str();
}

bool ksi::confusion_matrix::equal(const double left, const double right)
{
    const double EPSILON = 0.0001;
    return fabs(left - right) < EPSILON;
}

void ksi::confusion_matrix::calculate_statistics(
    const std::vector<double>& expected_classes, 
    const std::vector<double>& elaborated_classes, 
    double PositiveClassLabel,
    double NegativeClassLabel,
    int& nTruePositives, 
    int& nTrueNegatives, 
    int& nFalsePositives, 
    int& nFalseNegatives)
{
    try 
    {
        if (expected_classes.size() != elaborated_classes.size())
        {
            std::stringstream ss;
            ss << "Size of vectors do not match: expected_classes.size() == " << expected_classes.size() << ", elaborated_classes.size() == " << elaborated_classes.size() << std::endl;
            
            throw ss.str();
        }
        
        int nClassNegative = 0;
        int nClassPositive = 0;
        int nElaboratedPositive = 0;
        int nElaboratedNegative = 0;
        
        nTrueNegatives = nTruePositives = nFalsePositives = nFalseNegatives = 0;
        
        auto size = expected_classes.size();
        for (std::size_t i = 0; i < size; i++)
        {
            int ElaboratedClass = elaborated_classes[i];
            int OriginalClass   = expected_classes[i];

            if (equal(OriginalClass, PositiveClassLabel))
                nClassPositive++;
            else
                nClassNegative++;

            if (equal (ElaboratedClass, PositiveClassLabel))
                nElaboratedPositive++;
            else
                nElaboratedNegative++;
            
            if (equal (OriginalClass, PositiveClassLabel)) // original
            {
                if (equal (ElaboratedClass, PositiveClassLabel))
                    nTruePositives++;
                else
                    nFalseNegatives++;
            }
            else
            {
                if (equal (ElaboratedClass, PositiveClassLabel))
                    nFalsePositives++;
                else
                    nTrueNegatives++;
            }
        }
    }
    CATCH;
}


void ksi::confusion_matrix::calculate_statistics (
   const std::vector<double> & original, 
   const std::vector<double> & answers,
   double PositiveClassLabel,
   double NegativeClassLabel,
   int & nTruePositives,
   int & nTrueNegatives,
   int & nFalsePositives,
   int & nFalseNegatives,
   double dbThreshold)
{
    int nClassNegative = 0;
    int nClassPositive = 0;
    int nElaboratedPositive = 0;
    int nElaboratedNegative = 0;
    
    nTrueNegatives = nTruePositives = nFalsePositives = nFalseNegatives = 0;

    double dbProg;
    if (dbThreshold < -99)
        dbProg = (PositiveClassLabel - NegativeClassLabel) / 2.0;
    else
        dbProg = dbThreshold;

    nTrueNegatives = nTruePositives = 0;
    nFalsePositives = nFalseNegatives = 0;

    int size = original.size();
    int i;
    for (i = 0; i < size; i++)
    {
        int ElaboratedClass = answers[i] < dbProg ? NegativeClassLabel : PositiveClassLabel;
        int OriginalClass   = original[i];

        if (equal(OriginalClass, PositiveClassLabel))
            nClassPositive++;
        else
            nClassNegative++;

        if (equal (ElaboratedClass, PositiveClassLabel))
            nElaboratedPositive++;
        else
            nElaboratedNegative++;
        
        if (equal (OriginalClass, PositiveClassLabel)) // original
        {
            if (equal (ElaboratedClass, PositiveClassLabel))
                nTruePositives++;
            else
                nFalseNegatives++;
        }
        else
        {
            if (equal (ElaboratedClass, PositiveClassLabel))
                nFalsePositives++;
            else
                nTrueNegatives++;
        }
    }
}


std::string ksi::confusion_matrix::print(
   int nTruePositives, 
   int nTrueNegatives, 
   int nFalsePositives, 
   int nFalseNegatives)
{

   std::stringstream ss;

   
   int CP; // conditional (original) positives 
   int CN; // conditional (original) negatives 
   int OP; //  TestOutcomePositives
   int ON; // TestOutcomeNegatives;
   int To; // TotalPopulation

   CP = nTruePositives + nFalseNegatives;
   CN = nFalsePositives + nTrueNegatives;

   OP = nTruePositives + nFalsePositives;
   ON = nFalseNegatives + nTrueNegatives;

   To = CP + CN;
   
   int TP = nTruePositives;
   int TN = nTrueNegatives;
   int FP = nFalsePositives;
   int FN = nFalseNegatives;

  
   double PRE, PPV, FDR, FOR, NPV, LRP, TPR, FPR, ACC, FNR, TNR, DOR, LRN, F1S;

   PRE = (double) CP / To;
   PPV = (double) nTruePositives / OP;
   FDR = (double) nFalsePositives / OP;
   FOR = (double) nFalseNegatives / ON;
   NPV = (double) nTrueNegatives /  ON;
   TPR = (double) nTruePositives / CP;
   FNR = (double) nFalsePositives / CP;
   FPR = (double) nFalsePositives / CN;
   TNR = (double) nTrueNegatives / CN;
   ACC = (double) (nTruePositives + nTrueNegatives) / To;
   
   F1S = 2 * TPR * PPV / (TPR + PPV);
   LRP = TPR / FPR;
   LRN = FNR / TNR;
   DOR = LRP / LRN;

   ss <<
   "+------------------+------------------+--------------------+-----------------------+---------------------+" << std::endl <<
   "| total            |      original    |     original       | prevalence =          | accuracy (ACC) =    |" << std::endl <<
   "| population       |      positive    |     negative       |   original positive   |        TP + TN      |" << std::endl <<
   "|                  |                  |                    | = -----------------   | = ----------------  |" << std::endl <<
   "|                  |                  |                    |   total population    |   total population  |" << std::endl <<
   "| = "<< ca(To)<< " | = "<< ca(CP)<< " | =   "<< ca(CN)<< " | = "<< ul(PRE)<<"      | = "<< ul(ACC)<<"    |" << std::endl <<
   "+------------------+------------------+--------------------+-----------------------+---------------------+" << std::endl <<
   "| predicted        |  true positive   |  false positive    | positive predictive   | false discovery     |" << std::endl <<
   "| positive         |  TP, power       |  FP, type I error  | value, PPV, precision | rate, FDR =         |" << std::endl <<
   "|                  |                  |                    |      TP               |      FP             |" << std::endl <<
   "|                  |                  |                    | = ---------           | = ---------         |" << std::endl <<
   "|                  |                  |                    |    TP + FP            |    TP + FP          |" << std::endl <<
   "| = "<< ca(OP)<< " | = "<< ca(TP)<< " | =   "<< ca(FP)<< " | = "<< ul(PPV)<<"      | = "<< ul(FDR)<<"    |" << std::endl <<
   "+------------------+------------------+--------------------+-----------------------+---------------------+" << std::endl <<
   "| predicted        | false negative   | true negative      | false omission rate   | negative predictive |" << std::endl <<
   "| negative         | FN               | TN                 | FOR                   | value, NPV          |" << std::endl <<
   "|                  | type II error    |                    |      FN               |      TN             |" << std::endl <<
   "|                  |                  |                    | = ---------           | = ---------         |" << std::endl <<
   "|                  |                  |                    |    FN + TN            |    FN + TN          |" << std::endl <<
   "| = "<< ca(ON)<< " | = "<< ca(FN)<< " | =   "<< ca(TN)<< " | = "<< ul(FOR)<<"      | = "<< ul(NPV)<<"    |" << std::endl <<
   "+------------------+------------------+--------------------+-----------------------+---------------------+" << std::endl <<
   "                   | true positive    | false positive     | positive likelihood   | diagnostic odds     |" << std::endl <<
   "                   | rate, TPR,       | rate, FPR, fall-out| ratio (LR+)           | ratio, DOR          |" << std::endl <<
   "                   | recall,          |                    |                       |                     |" << std::endl <<
   "                   | sensitivity      |                    |                       |                     |" << std::endl <<
   "                   |      TP          |      FP            |    TPR                |    LR+              |" << std::endl << 
   "                   | = ---------      | = ---------        | = -----               | = -----             |" << std::endl <<
   "                   |    TP + FN       |    TN + FP         |    FPR                |    LR-              |" << std::endl <<
   "                   | = "<< ul(TPR)<<" | = "<< ul(FPR)<<"   | = "<< ul(LRP)<<"      | = "<< ul(DOR)<<"    |" << std::endl <<
   "                   +------------------+--------------------+-----------------------+---------------------+" << std::endl <<
   "                   | false negative   | true negative      | negative likelihood   | F1 score            |" << std::endl <<
   "                   | rate, FNR,       | rate, TNR,         | ratio (LR-)           |                     |" << std::endl <<
   "                   | miss rate        | specificity, SPC   |                       |                     |" << std::endl <<
   "                   |      FN          |      TN            |    FNR                |    2 * TPR * PPV    |" << std::endl <<
   "                   | = ---------      | = ---------        | = -----               | = ---------------   |" << std::endl <<
   "                   |    TP + FN       |    TN + FP         |    TNR                |      TPR + PPV      |" << std::endl <<
   "                   | = "<< ul(FNR)<<" | = "<< ul(TNR)<<"   | = "<< ul(LRN)<<"      | = "<< ul(F1S)<<"    |" << std::endl <<
   "                   +------------------+--------------------+-----------------------+---------------------+" << std::endl;

   
   ss << "Total Population:                                               " << ca(To) << std::endl;
   ss << "True Positive (power):                                          " << ca(nTruePositives)  << std::endl;
   ss << "True Negative:                                                  " << ca(nTrueNegatives)  << std::endl;
   ss << "False Positive (type I error):                                  " << ca(nFalsePositives) << std::endl;
   ss << "False Negative (type II error):                                 " << ca(nFalseNegatives) << std::endl;
   ss << std::endl;
   ss << "Condition (original) Positive = True Positive + False Negative: " << ca(CP) << std::endl;
   ss << "Condition (original) Negative = False Positive + True Negative: " << ca(CN) << std::endl;
   ss << "Test Outcome Positive = True Positive + False Positive:         " << ca(OP) << std::endl;
   ss << "Test Outcome Negative = True Negative + False Negative:         " << ca(ON) << std::endl;
   ss << std::endl;
   
   
   ss << "Prevalence = Condition (original) positive / Total population:                      " << ul(PRE) << std::endl;
   ss << "Positive predictive value (PPV, Precision) = True positive / Test outcome positive: " << ul(PPV) << std::endl;
   ss << "False discovery rate (FDR) = False positive / Test outcome positive:                " << ul(FDR) << std::endl;
   ss << "False omission rate (FOR) = False negative / Test outcome negative:                 " << ul(FOR) << std::endl;
   ss << "Negative predictive value (NPV) = True negative / Test outcome negative:            " << ul(NPV) << std::endl;
   ss << "True positive rate (TPR, Sensitivity, Recall) = True positive / Condition positive: " << ul(TPR) << std::endl;
   ss << "False positive rate (FPR, Fall-out) = False positive / Condition negative:          " << ul(FPR) << std::endl;
   ss << "False negative rate (FNR) = False negative / Condition positive:                    " << ul(FNR) << std::endl;
   ss << "True negative rate (TNR, Specificity, SPC) = True negative / Condition negative:    " << ul(TNR) << std::endl;
   ss << "Accuracy (ACC) = (True positive + True negative) / Total population:                " << ul(ACC) << std::endl;
   ss << "Positive likelihood ratio (LR+) = TPR / FPR:                                        " << ul(LRP) << std::endl;
   ss << "Negative likelihood ratio (LR−) = FNR / TNR:                                        " << ul(LRN) << std::endl;
   ss << "Diagnostic odds ratio (DOR) = LR+ / LR−:                                            " << ul(DOR) << std::endl;
   ss << "F1 score = recall * precision / (recall + precision):                               " << ul(F1S) << std::endl;

   return ss.str();
  
}
