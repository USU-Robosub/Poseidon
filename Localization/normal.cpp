#include <cmath>

/**
 * Calculates the probability of a pixel to contain the feature.
 * @param pixelDist distance between the pixel and sub in pixels.
 * @param worldDist distance between the feature and sub in world units (meters?).
 * @param sigma the confidence that our world measurement is accurate.
 * @return the probability in [0,1]
 */
double norm(double pixelDist, double worldDist, double sigma) {
  // Affects the variance of the distribution.
  // TODO: Tune.
  const double SIG_SCALE = 10;

  // Computes the height of the distribution with worldDist as the mean.
  double u = (worldDist - pixelDist) / (sigma * SIG_SCALE);
  // Note that this is not a standard distribution as we are not multiplying
  // by 1 / (sqrt(2 * PI) * SIG_SCALE * sigma).
  double mu = exp(-0.5 * u * u);
  return mu;
}