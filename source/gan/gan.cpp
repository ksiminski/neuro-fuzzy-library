
#include <algorithm>
#include <random>
#include <chrono>

#include "../gan/gan.h"

#include "../service/debug.h"



ksi::gan::gan(const int number_of_iterations,
              const generative_model & p_gen,
              const discriminative_model & p_dis) 
          :
  _nIterations (number_of_iterations)
{
    _pGenerator = p_gen.clone_generator();
    _pDiscriminator = p_dis.clone_discriminant();
}


ksi::gan::gan (const ksi::gan & wzor)
{
    _pDiscriminator = wzor._pDiscriminator->clone_discriminant();
    _pGenerator     = wzor._pGenerator->clone_generator();
    
    _nIterations = wzor._nIterations;
}

ksi::gan::gan (ksi::gan && wzor)
{
    std::swap (_pDiscriminator, wzor._pDiscriminator);
    std::swap (_pGenerator, wzor._pGenerator);
    
    std::swap (_nIterations, wzor._nIterations);
}

ksi::gan & ksi::gan::operator= (const ksi::gan & wzor)
{
   if (this == & wzor)
      return *this;
// 
   // remove what is to remove
   delete _pDiscriminator;
   delete _pGenerator;
   
   // allocate what is to allocate
   _pDiscriminator = wzor._pDiscriminator->clone_discriminant();
   _pGenerator     = wzor._pGenerator->clone_generator();
   
   _nIterations = wzor._nIterations;

   return *this;
}

ksi::gan & ksi::gan::operator= (ksi::gan && wzor)
{
   if (this == & wzor)
      return *this;

   // swap what is to swap
   
   std::swap (_pDiscriminator, wzor._pDiscriminator);
   std::swap (_pGenerator, wzor._pGenerator);
   
   std::swap (_nIterations, wzor._nIterations);

   return *this;
}

ksi::gan::~gan ()
{
   // delete what is to delete
   delete _pDiscriminator;
   delete _pGenerator; 
}

void ksi::gan::train(const ksi::dataset& zbior_oryginalny)
{
    try 
    {
        ksi::generative_model * pBestGenerator = nullptr;
        double minimalRMSE = std::numeric_limits<double>::max();
        
        // no to jedziemy :-)
        auto nDataItems = zbior_oryginalny.getNumberOfData();
        auto nDataItemsTrain = nDataItems / 2;        
        auto podzielone = zbior_oryginalny.splitDataSetHorizontally(nDataItemsTrain);
        auto train = podzielone.first;
        debug (train.getNumberOfData());
        debug(train.getNumberOfAttributes());
        auto test  = podzielone.second;
        
        std::default_random_engine silnik (std::chrono::system_clock::now().time_since_epoch().count());
        
        auto zbior_rozszerzony_o_atrybut_autentycznosci = train;
        auto nAttributes = zbior_oryginalny.getNumberOfAttributes();
        
        for (std::size_t i = 0; i < train.getNumberOfData(); i++)
            zbior_rozszerzony_o_atrybut_autentycznosci.getDatumNonConst(i)->push_back(ORIGINAL);
        
        // najpierw stroimy generator
        
        _pGenerator->train_generative_model (train);
        double TestInitialRMSE = _pGenerator->elaborate_rmse_for_dataset(test);
        
//         auto zbior_dla_generatora = train;
        
        // teraz mamy utworzony generator
        std::cout << "# iteracja\tliczba_danych\tRMSE" << std::endl;
        
//         debug(_nIterations);
        for (int i = 0; i < _nIterations; i++)
        {
//             debug(i);
            
            ksi::dataset podrobione;
            for (int k = 0; k < nDataItemsTrain; k++)
            {
                auto podrobka = _pGenerator->get_random_datum(silnik);
                podrobka.push_back (FORGED);
                podrobka.setDecision(FORGED);
                podrobione.addDatum(podrobka);
//                 debug(podrobka);
            }

            ksi::dataset merged = zbior_rozszerzony_o_atrybut_autentycznosci;
            if (podrobione.getNumberOfData() > 0)
               merged += podrobione;
            
            _pDiscriminator->train_discriminative_model (merged);
//             debug(_pDiscriminator->to_string());
            
            // wybor tych przykladow, dla ktorych dyskryminator dal sie zwiesc 
            ksi::dataset oszukujace;
            std::size_t podrobione_size = podrobione.getNumberOfData();
            double GRANICA = (ORIGINAL + FORGED) / 2.0;
            
            for (std::size_t k = 0; k < podrobione_size; k++)
            {
//                 auto podzielona = podrobione.getDatum(k)->splitDatum(nAttributes).first;
//                 auto odpowiedz = _pDiscriminator->discriminate (podzielona);
                auto podrobka = _pGenerator->get_random_datum(silnik);
                auto odpowiedz = _pDiscriminator->discriminate (podrobka);
                if (odpowiedz > GRANICA)
                {
                    oszukujace.addDatum(podrobka);
                }
            }
            
//             debug(oszukujace.getNumberOfData());
            auto zbior_dla_generatora = train;
            if (oszukujace.getNumberOfData() > 0)
                 zbior_dla_generatora += oszukujace;
//                 zbior_dla_generatora = oszukujace;
            
            _pGenerator->train_generative_model (zbior_dla_generatora);
            
//             double rmse = _pGenerator->elaborate_rmse_for_dataset(test);
            double rmse = _pGenerator->elaborate_rmse_for_dataset(test);
//             debug(rmse);
            if (rmse < minimalRMSE)
            {
                delete pBestGenerator;
                pBestGenerator = _pGenerator->clone_generator();
                minimalRMSE = rmse;
            }
            else
            {
//                 delete _pGenerator;
//                 _pGenerator = pBestGenerator->clone_generator();
            }
            
            std::cout << i << "\t" << oszukujace.getNumberOfData() << "\t" << rmse << std::endl;
        }
        
        //debug(_pGenerator->to_string());
        
        delete pBestGenerator;
        pBestGenerator = nullptr;
        
        debug(TestInitialRMSE);
        debug(minimalRMSE);
        
    }
    CATCH;
    // w sumie ta metoda powinna cos zwrocic    
}

