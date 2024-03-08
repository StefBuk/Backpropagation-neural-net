#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "global.h"

class Neuron;

typedef std::vector < Neuron > Sloj;

struct Veza
{
  double tezina = 0.0;
  double delta_tezina = 0.0;
};

class Neuron
{
public:
  Neuron( int broj_izlaza, int indeks);
  ~Neuron(){};

//APIs
  void postavi_vrednost ( double vr );
  double uzmi_vrednost ();

  void feed_forward( Sloj &prethodni_sloj);
  void izracunaj_izlazni_gradijent( double ciljana_vr );
  void izracunaj_skriveni_gradijent( Sloj &sledeci_sloj );
  void izmeni_tezinu( Sloj &prethodni_sloj );

private:
  double aktivaciona_f( double x);
  double aktivaciona_f_izvod( double x);
  double random() { return rand() / double( RAND_MAX ); }

  static double eta;    // learning rate [0.0..1.0], 0.0 -> slow, 0.2 -> medium, 1.0 -> reckless
  static double alfa;   // momentum, last delta weight percentage [0.0 - 1.0], 0.0 -> no momentum,  0.5 -> moderate momentum

  std::vector < Veza > m_Tezina;

  double m_izlaz = 0.0;
  double m_gradient = 0.0;
  int m_indeks = 0;
};

double Neuron::eta = 0.15;
double Neuron::alfa = 0.5;
