/** @file */ 
#ifndef CONSEQUENCE_CL_H
#define CONSEQUENCE_CL_H

#include <utility>
#include <vector>
#include <array>
#include <iostream>

#include "consequence-TSK.h"
#include "../service/debug.h"

namespace ksi
{
   /** Consequence Czogala-Leski type
    * 
    */
   class consequence_CL : virtual public consequence_TSK 
   {
   protected:
      /** support width of an isosceles triangle fuzzy set */
      double _w;
      
      /** sum of dE / dw differentials */
      double sum_dE_dw;

      /*const static std::array<std::string, 7> CLLocationDescription;*/
   public:
      virtual ~consequence_CL();
      consequence_CL (const std::vector<double> & params, double w);
      virtual consequence * clone () const;
      
      /** A method returns width of the support of a triangle fuzzy set.
       * @return width of the support of a triangle fuzzy set
       */
      virtual double getW() const;
      
      /** The method sets all cummulated differentials to zero. */
      virtual void reset_differentials ();
      
      /** The method cummulates differentials for an X data item in the consequence.
       * The method cummulates only the differential for the support width.
       @param X the data item to cummulate differantials for 
              This parameter is not used in this method.
       @param partial_differential some differentials from other rules
       @param secundary_partial_differential some differentials (not used here)
       @param firing firing strength of the premise of the rule (not used here)
       @date 2018-01-20
       */
      virtual void cummulate_differentials(std::vector< double > X, 
                                           double partial_differential,
                                           double secundary_partial_differential,
                                           double firing
                                          );

      /** The method actualises values of parameters of the fuzzy consequence.
       * The method actualises the support width only.
       * If the new value of support width is negative, the old value is kept without
       * change. 
       * @param eta learning coefficient
       */
      virtual void actualise_parameters(double eta);

      /** The method prints an object into output stream.
      * @param ss an output stream to print to
      */
      virtual std::ostream & Print (std::ostream & ss); 

  //    /** The method prints an object linguistic description into output stream
  //      * @param ss an output stream to print to
  //      * @param descStat the descriptor statistics to print
  //      * @date 2023-12-26
  //      * @author Konrad Wnuk
  //      */
  //    virtual std::ostream& prettyPrint(std::ostream& ss, const DescriptorStatistics& descStat);
   };
}

#endif