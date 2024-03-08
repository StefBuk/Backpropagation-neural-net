#include "CMreza.h"


Mreza :: Mreza( std::vector < int > &struktura )
{

  int broj_slojeva = struktura.size();
  int broj_izlaza;  //broj veza (connections) koji izlazi iz svakog neurona

  for ( int sloj_br = 0; sloj_br < broj_slojeva; sloj_br++ )
  {
    m_slojevi.push_back( Sloj() );

    broj_izlaza = ( sloj_br == struktura.size() - 1 ? 0 : struktura.at( sloj_br + 1 ) );

    for ( int neuron_br = 0; neuron_br < struktura.at( sloj_br ) + 1; neuron_br++ ) //Dodajemo svuda BIAS (pristrasni) neuron
    {
      m_slojevi.back().push_back( Neuron( broj_izlaza, neuron_br ) ); //postavljanje indeksa veza
    }

    m_slojevi.back().back().postavi_vrednost( 1.0 );  //bias neuron ima vrednost 1.0
  }
};



void Mreza :: feed_forward( std::vector < double > &ulazne_vr )
{
  if( ulazne_vr.size() != m_slojevi.at( 0 ).size() - 1 )  //-1 zbog BIAS neurona
  {
    std::cout << "Greska, velicina ulaza ne odgovara formatu" << std::endl;
    exit( EXIT_FAILURE );
  }

  //kopira vrednosti u ulazni sloj mreze
  for ( int n = 0; n < ulazne_vr.size(); n++ )
  {
    m_slojevi.at( 0 ).at( n ).postavi_vrednost( ulazne_vr.at( n ) );
  }

  //racunanje vrednosti izlaza ostalih neurona, od vec ulaznih pa nadalje
  for ( int sloj_br = 1; sloj_br < m_slojevi.size(); sloj_br++ )
  {
    Sloj &prethodni_sloj = m_slojevi.at( sloj_br - 1 );

    for ( int n = 0; n < m_slojevi.at( sloj_br ).size() - 1; n++ )
    {
      m_slojevi.at( sloj_br ).at( n ).feed_forward( prethodni_sloj ); //racunanje na nivou neurona
    }
  }
};


void Mreza :: back_propagate( std::vector < double > &ciljane_vr )
{
  Sloj &izlazni_sloj = m_slojevi.back();

  //Root mean square (RMS) - racunanje greske jednog ponavljanja
  m_greska = 0.0;

  for ( int n = 0; n < izlazni_sloj.size() - 1; n++ )
  {
    double delta = ciljane_vr.at( n ) - izlazni_sloj.at( n ).uzmi_vrednost();
    m_greska += delta * delta;
  }
  m_greska /= ( izlazni_sloj.size() - 1 );
  m_greska = sqrt( m_greska );


  //dobijanje nove ukupne srednje greske sistema
  m_trenutna_srednja_greska = ( m_trenutna_srednja_greska * ( ( double )g_ponavljanje - 1.0 ) + m_greska )
                            / ( ( double )g_ponavljanje );


  //racunanje gradijenta izlaznog sloja
  for ( int n = 0; n < izlazni_sloj.size() - 1; n++ )
  {
    izlazni_sloj.at( n ).izracunaj_izlazni_gradijent( ciljane_vr.at( n ) );
  }

  //racunanje gradijenta skrivenih slojeva, od poslednjeg do prvog
  for ( int sloj_br = m_slojevi.size() - 2; sloj_br >= 1; sloj_br-- )
  {
    Sloj &trenutni_sloj = m_slojevi.at( sloj_br );
    Sloj &sledeci_sloj  = m_slojevi.at( sloj_br + 1 );

    for ( int n = 0; n < trenutni_sloj.size(); n++ )
    {
      trenutni_sloj.at( n ).izracunaj_skriveni_gradijent( sledeci_sloj );
    }
  }

  //Zamena vrednosti tezine( connection weight )od izlaznog sloja do prvog skrivenog
  for ( int sloj_br = m_slojevi.size() - 1; sloj_br > 0; sloj_br-- )
  {
    Sloj &trenutni_sloj  = m_slojevi.at( sloj_br );
    Sloj &prethodni_sloj = m_slojevi.at( sloj_br - 1 );

    for ( int n = 0; n < trenutni_sloj.size() - 1; n++ )
    {
      trenutni_sloj.at( n ).izmeni_tezinu( prethodni_sloj );
    };
  };
};



void Mreza :: izvuci_rezultat( std::vector < double > &rezultat_vr )
{
  rezultat_vr.clear();

  for ( int n = 0; n < m_slojevi.back().size() - 1; n++ )
  {
    rezultat_vr.push_back( m_slojevi.back().at( n ).uzmi_vrednost() );
  };
};
