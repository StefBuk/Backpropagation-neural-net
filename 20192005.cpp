#include <vector>
#include <iostream>

#include "CMreza.cpp"
#include "fun.h"

int main( int argc, char **argv )
{
  std::vector < double > ulazne_vr, ciljane_vr, rezultat_vr;
  std::vector < int > struktura;

  napuni_strukturu( struktura, argc, argv );

  Mreza NN( struktura );

  while( ucitaj_ulaz( ulazne_vr, ciljane_vr ) )
  {
    std::cout << "Krug: " << ++g_ponavljanje << std::endl;

    NN.feed_forward   ( ulazne_vr   );
    NN.izvuci_rezultat( rezultat_vr );
    NN.back_propagate ( ciljane_vr  );

    stampaj_vektor( "Ulazne vrednosti ", ulazne_vr   );
    stampaj_vektor( "Izlazne vrednosti", rezultat_vr );
    stampaj_vektor( "Ciljane vrednosti", ciljane_vr  );
    std::cout << "Trenutna srednja greska: " << NN.trenutna_sr_greska() << std::endl;

    std::cout << std::endl;
  }

  ulaz.close();
  return 0;
}
