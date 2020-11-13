#ifndef GAUSSGEN_INCLUDED
#define GAUSSGEN_INCLUDED

// gaussians helper class based on NR routines
// to generate gaussian distributed random numbers
// for use in detector response modelling

class gaussgen
{
 private:
 public:
  float ran1(long *idum);
  float getRandom(long *iseed);
};

#endif











