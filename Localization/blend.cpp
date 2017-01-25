#include <random>

// Returns a random double in [0,1]
double randNextDouble() {
  return rand() / RAND_MAX;
}

// Resamples pixels then blends them with new weights
double blend(double oldWeight, double newWeight) {
  // Resample
  double acceptance = randNextDouble();
  if (oldWeight < acceptance) oldWeight = 0;

  // Apply the new weight
  return (oldWeight * newWeight);
}