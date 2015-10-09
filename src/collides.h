#ifndef COLLIDES_H_
#define COLLIDES_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static inline double dotproduct(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

static inline bool overlap(double from_1, double to_1, double from_2, double to_2) {
    return (from_1 > from_2 && to_1 < to_2) || // Case 1: line 1 is contained in line 2
           (from_2 > from_1 && to_2 < to_1) || // Case 2: line 2 is contained in line 1
           (to_2 > from_1 && to_2 < to_1)   || // Case 3: line 2 is overlapping from the left of line 1
           (to_1 > from_2 && to_1 < to_2);     // Case 4: line 1 is overlapping from the left of line 2
}

/// Get the modulus of the vector (x, y)
static inline double modulus(double x, double y) {
    return sqrt(x * x + y * y);
}

/// Project p over the vector (x, y), to obtain the scalar c
///
/// This is technically a vector projection of the vector p
/// over (x, y)
///
/// let v = (x, y)
///          p
///          .
///         /|
///        / |
///       /__|__ v
///          c
///
/// So: c = cos(a) * |p|
///
/// Since cos(a) can be written in terms of the dot product of p and v:
/// cos(a) = (v . p)/(|v|*|p|)
///
/// Substituting and simplifying:
/// c = (p . v) / |v|
///
static inline double vector_projection_with_precalculated_axis_modulus(double axis_x,
                                                                       double axis_y,
                                                                       double px,
                                                                       double py,
                                                                       double axis_mod) {
    return dotproduct(px, py, axis_x, axis_y) / axis_mod;
}


static inline double vector_projection(double axis_x, double axis_y, double px, double py) {
    return vector_projection_with_precalculated_axis_modulus(axis_x,
                                                             axis_y,
                                                             px,
                                                             py,
                                                             modulus(axis_x, axis_y));
}

void projection_bounds(double axis_x,
                       double axis_y,
                       const double* points,
                       size_t len,
                       double* out_higher,
                       double* out_lower,
                       bool* success);

bool collides(const double* points_1,
              size_t len_1,
              const double* points_2,
              size_t len_2);

#endif
