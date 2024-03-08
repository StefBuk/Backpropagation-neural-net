#include "CNeuron.cpp"

class Mreza
{
public:
  Mreza( std::vector < int > &struktura );
  ~Mreza(){};

  void feed_forward     ( std::vector < double > &ulazne_vr  );
  void back_propagate   ( std::vector < double > &ciljane_vr );
  void izvuci_rezultat  ( std::vector < double > &resultVals );

  double trenutna_sr_greska() { return m_trenutna_srednja_greska; }

private:
  std::vector < Sloj > m_slojevi;

  double m_greska = 0.0;
  double m_trenutna_srednja_greska = 1.0;   // Da ne bismo dobili situaciju 0.0 * 0.0 pri prvom racunanju
};
