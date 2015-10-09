#include "collides.h"

void projection_bounds(double axis_x,
                       double axis_y,
                       const double* points,
                       size_t len,
                       double* out_higher,
                       double* out_lower,
                       bool* out_success) {
    bool success = false;
    double max;
    double min;

    double axis_modulus = modulus(axis_x, axis_y);

    for (size_t i = 0; i < len; i += 2) {

        double px = points[i];
        double py = points[i + 1];

        double c = vector_projection_with_precalculated_axis_modulus(axis_x,
                                                                     axis_y,
                                                                     px,
                                                                     py,
                                                                     axis_modulus);

        if ( ! success ) {
            success = true;
            max = min = c;
        }

        if ( max < c ) {
            max = c;
        } else if ( min > c ) {
            min = c;
        }
    }

    if ( out_success )
        *out_success = success;

    if ( success ) {
        if ( out_higher )
            *out_higher = max;
        if ( out_lower )
            *out_lower = min;
    }
}

/// This function checks wherther two polygons collide,
/// using Separating Axis Theorem
///
/// This is a really low-level function to be able to interact both with cocoa and
/// c-sharp easily.
///
/// Each two entries in the points array is one point, so thre must be n*2 doubles
/// for a len of n.
///
/// Pending work:
///  * Have in account friction, bounce factor and allow to return the new speed and
///    directions, probably split in vx, vy
bool collides(const double* points_1,
              size_t len_1,
              const double* points_2,
              size_t len_2) {
    for (size_t i = 0; i + 2 < len_1; i += 2) {
        double x1 = points_1[i];
        double y1 = points_1[i + 1];

        double x2 = points_1[i + 2];
        double y2 = points_1[i + 3];

        double side_x = x1 - x2;
        double side_y = y1 - y2;

        /// get the perpendicular vector,
        /// which is the axis we want to project on
        /// perp(x, y) = (-y, x)
        double axis_1 = -side_y;
        double axis_2 = side_x;

        /// Project the points in the axis, and get the bounds
        double higher_1;
        double lower_1;
        projection_bounds(axis_1, axis_2, points_1, len_1, &higher_1, &lower_1, NULL);

        double higher_2;
        double lower_2;
        projection_bounds(axis_1, axis_2, points_2, len_2, &higher_2, &lower_2, NULL);

        if ( !overlap(lower_1, higher_1, lower_2, higher_2) )
            return false;
    }

    return true;
}
