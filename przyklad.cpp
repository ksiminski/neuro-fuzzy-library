

// hierarcha klas
class bazowa 
{
   public:
      bazowa * clone () const; // wzorzec projektowy prototyp
};

class pochodna 
{
   public:
      bazowa * clone () const; // wzorzec projektowy prototyp
};


class korzystajaca
{
   protected:
      bazowa * pElement = nullptr; 

   public:
      korzystajaca (const bazowa & element) // wzorzec projektowy: wstrzykiwanie zależności (dependency injection)
      {
         pElement = element.clone(); // korzystamy z prototypu
      }
      ~korzystajaca()
      {
         delete pElement;
      }
      korzystajaca (const korzystajaca & k) = delete ; 
};

int main ()
{
   //pochodna obiekt;
   bazowa obiekt;
   korzystajaca ob_korzystajacej(obiekt); // wstrzykiwanie zależności

   return 0;
}
