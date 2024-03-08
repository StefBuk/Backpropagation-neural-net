#include "CNeuron.h"

Neuron::Neuron( int broj_izlaza, int indeks )
{
  for ( int i = 0; i < broj_izlaza; i++ )
  {
    m_Tezina.push_back( Veza() ); //Poziva se default constructor i postavlja se novi objekat strukture Veza u vektor (0.0, 0.0)
    m_Tezina.back().tezina = random();
  }

  m_indeks = indeks;
}

//API - set/get
void Neuron :: postavi_vrednost( double vr )
{
  m_izlaz = vr;
};

double Neuron :: uzmi_vrednost()
{
  return m_izlaz;
};


double Neuron :: aktivaciona_f( double x )
{
  return tanh(x);     //[-1.0 .. 1.0] - resenja su samo u ovom opsegu
}

double Neuron :: aktivaciona_f_izvod( double x )
{
// inace je izvod f'(x) = 1 - tanh^2( x ), ali mi cemo koristiti
  return 1.0 - x * x;     //aproksimacija za raspon [-1.0 .. 1.0]
}


void Neuron :: feed_forward ( Sloj &prethodni_sloj )
{
  //new_input = f( sum( weight * output.at(i) ) )
  double suma = 0.0;

  for ( int n = 0; n < prethodni_sloj.size(); n++ )
  {
    suma += prethodni_sloj.at( n ).uzmi_vrednost() *
            prethodni_sloj.at( n ).m_Tezina.at( m_indeks ).tezina;
  }

  m_izlaz = aktivaciona_f( suma );
}


void Neuron :: izracunaj_skriveni_gradijent( Sloj &sledeci_sloj)  //gradijent kod skrivenih slojeva, unazad se racuna
{
  //new_gradient = f'(x) *  sum( weight * gradient_of_next_layers_neuron )
  double suma = 0.0;

  for ( int n = 0; n < sledeci_sloj.size() - 1; n++ )
  {
    suma += m_Tezina.at( n ).tezina * sledeci_sloj.at( n ).m_gradient;
  }

  m_gradient = suma * aktivaciona_f_izvod( m_izlaz );
}


void Neuron :: izracunaj_izlazni_gradijent( double ciljana_vr ) //gradijent u izlaznom sloju
{
  //gradient = f'(x) *  delta
  double delta;

  delta = ciljana_vr - m_izlaz;
  m_gradient = delta * aktivaciona_f_izvod( m_izlaz );
}


void Neuron::izmeni_tezinu( Sloj &prethodni_sloj )
{
  for ( int n = 0; n < prethodni_sloj.size(); n++ )
  {
    Neuron &neuron = prethodni_sloj.at( n );
    double stara_delta_tezina = neuron.m_Tezina.at( m_indeks ).delta_tezina;

    double nova_delta_tezina = eta * neuron.uzmi_vrednost() * m_gradient      //brzina kojom se menja vrednost * vrednost * smer u kom se menja vrednost
                             + alfa * stara_delta_tezina;                     //ucinak stare delta tezine u novoj

    neuron.m_Tezina.at( m_indeks ).delta_tezina = nova_delta_tezina;
    neuron.m_Tezina.at( m_indeks ).tezina      += nova_delta_tezina;
  }
};
