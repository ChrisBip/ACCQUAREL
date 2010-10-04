extern "C" {
double unrolloverlap(const int nbrofprimitives_a,
                     const double center_a[],
                     const double exponents_a[],
                     const double coefficients_a[],
                     const int monomialdegree_a[],
                     const int nbrofprimitives_b,
                     const double center_b[],
                     const double exponents_b[],
                     const double coefficients_b[],
                     const int monomialdegree_b[]);

double unrollkinetic(const int nbrofprimitives_a,
                     const double center_a[],
                     const double exponents_a[],
                     const double coefficients_a[],
                     const int monomialdegree_a[],
                     const int nbrofprimitives_b,
                     const double center_b[],
                     const double exponents_b[],
                     const double coefficients_b[],
                     const int monomialdegree_b[]);

double unrollderiv(const int nbrofprimitives_a,
                   const double center_a[],
                   const double exponents_a[],
                   const double coefficients_a[],
                   const int monomialdegree_a[],
                   const int nbrofprimitives_b,
                   const double center_b[],
                   const double exponents_b[],
                   const double coefficients_b[],
                   const int monomialdegree_b[],
                   const int dimension);

double unrollpotential(const int nbrofprimitives_a,
                       const double center_a[],
                       const double exponents_a[],
                       const double coefficients_a[],
                       const int monomialdegree_a[],
                       const int nbrofprimitives_b,
                       const double center_b[],
                       const double exponents_b[],
                       const double coefficients_b[],
                       const int monomialdegree_b[],
                       const double center[]);

double unrollxderiv(const int nbrofprimitives_a,
                    const double center_a[],
                    const double exponents_a[],
                    const double coefficients_a[],
                    const int monomialdegree_a[],
                    const int nbrofprimitives_b,
                    const double center_b[],
                    const double exponents_b[],
                    const double coefficients_b[],
                    const int monomialdegree_b[],
                    const int dimension1,
                    const int dimension2);

double unrollcoulomb(const int nbrofprimitives_a,
                     const double center_a[],
                     const double exponents_a[],
                     const double coefficients_a[],
                     const int monomialdegree_a[],
                     const int nbrofprimitives_b,
                     const double center_b[],
                     const double exponents_b[],
                     const double coefficients_b[],
                     const int monomialdegree_b[],
                     const int nbrofprimitives_c,
                     const double center_c[],
                     const double exponents_c[],
                     const double coefficients_c[],
                     const int monomialdegree_c[],
                     const int nbrofprimitives_d,
                     const double center_d[],
                     const double exponents_d[],
                     const double coefficients_d[],
                     const int monomialdegree_d[]);
}
