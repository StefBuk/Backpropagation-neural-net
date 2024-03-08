#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>


std::fstream otvarac( char const *naziv, int koji )
{
  std::fstream tok;

  if ( koji == 1 )    tok.open( naziv, std::fstream::in | std::fstream::out );
  if ( koji == 2 )    tok.open( naziv, std::fstream::app );

  if( !tok.is_open() )
  {
    std::cout << "Greska u otvaranju fajla!";
    exit( EXIT_FAILURE );
  };

  return tok;
};


void napuni_strukturu( std::vector < int > &struktura, int argc, char **argv )
{
  std::string linija;
  int broj;

  if( argc < 2 )
  {
    std::cout << "Niste uneli naziv ulaznog fajla";
    exit( EXIT_FAILURE );
  }

  ulaz = otvarac( *( argv + 1 ), 1 );

  getline( ulaz, linija );
  std::stringstream ss( linija );

  while( ss >> broj )
  {
    struktura.push_back( broj );
  };
}


bool ucitaj_ulaz( std::vector < double > &ulazne_vr, std::vector < double > &ciljane_vr )
{
  double broj;
  std::string linija;

  ulazne_vr.clear();
  ciljane_vr.clear();

  getline( ulaz, linija );
  std::stringstream citanje_ul( linija );
  while( citanje_ul >> broj ) {   ulazne_vr.push_back( broj );    }

  getline( ulaz, linija );
  std::stringstream citanje_cilj( linija );
  while( citanje_cilj >> broj ) {   ciljane_vr.push_back( broj );   }

  return ( !ulazne_vr.empty() && !ciljane_vr.empty() ) ? true : false;
}


void stampaj_vektor( std::string tekst, std::vector < double > &vektor )
{
  std::cout << tekst << ": ";
  for ( int i = 0; i < vektor.size(); i++ ) { std::cout << vektor.at( i ) << " "; }
  std::cout << std::endl;
}
