

#include <sstream>
#include <string>

#include "../neuro-fuzzy/neuro-fuzzy-system.h"
#include "../neuro-fuzzy/abstract_fcom.h"
#include "../owas/owa.h"
#include "../dissimilarities/dissimilarity.h"


std::string ksi::abstract_fcom::extra_report()
{
    std::stringstream ss;
    ss << "epsilon for Frobenius norm in clustering:    " << _dbFrobeniusEpsilon << std::endl;
    ss << "dissimilarity function: " << _pDissimilarity->print() << std::endl;
    ss << "ordered weighted averaging function: " << _pOwa->print() << std::endl;
    return ss.str();
}

ksi::abstract_fcom::abstract_fcom ()
{
}

ksi::abstract_fcom::~abstract_fcom ()
{
    // delete what is to delete
    
    delete _pOwa;
    _pOwa = nullptr;
    
    delete _pDissimilarity;
    _pDissimilarity = nullptr;

}

ksi::abstract_fcom::abstract_fcom (const ksi::abstract_fcom & wzor) : ksi::neuro_fuzzy_system(wzor)
{
   // copy what is to copy
    _pOwa = wzor._pOwa ? wzor._pOwa->clone() : nullptr;
    _pDissimilarity = wzor._pDissimilarity ? wzor._pDissimilarity->clone() : nullptr;
}

ksi::abstract_fcom & ksi::abstract_fcom::operator= (const ksi::abstract_fcom & wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // remove what is to remove
   delete _pOwa;
   delete _pDissimilarity;
   
   // allocate what is to allocate
   _pOwa = wzor._pOwa ? wzor._pOwa->clone() : nullptr;
   _pDissimilarity = wzor._pDissimilarity ? wzor._pDissimilarity->clone() : nullptr;   
   
   return *this;
}

ksi::abstract_fcom::abstract_fcom (ksi::abstract_fcom && wzor) : ksi::neuro_fuzzy_system(wzor)
{
   // swap what is to swap
   std::swap(_pOwa, wzor._pOwa);
   std::swap(_pDissimilarity, wzor._pDissimilarity);
   
    
}

ksi::abstract_fcom & ksi::abstract_fcom::operator= (ksi::abstract_fcom && wzor)
{
   if (this == & wzor)
      return *this;

   ksi::neuro_fuzzy_system::operator=(wzor);

   // swap what is to swap
   
   std::swap(_pOwa, wzor._pOwa);
   std::swap(_pDissimilarity, wzor._pDissimilarity);
   
   
   return *this;
}


 
