#include "collides.h"
#include "tests.h"

TEST(project_vector_basic, {
    double vec[] = { 0.0, 1.0 };
    double p[] = { 1.0, 1.0 };

    double res = vector_projection(vec[0], vec[1], p[0], p[1]);

    ASSERT(res == 1.0);
})

TEST(project_vectors, {
    double vec[] = { 1.0, 1.0 };
    double p[] = { 0.0, 0.0,
                   0.0, sqrt(2.0) };

    bool success;
    double h;
    double l;

    projection_bounds(vec[0], vec[1], p, STATIC_ARRAY_SIZE(p), &h, &l, &success);

    ASSERT(success);
    ASSERT(h != l);
    ASSERT(h == 1.0);
    ASSERT(l == 0.0);
})

TEST(basic_collision, {
    double square[] = {
        0.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,
        1.0, 0.0
    };

    double other_square[] = {
        0.5, 0.5,
        0.5, 1.5,
        1.5, 1.5,
        1.5, 0.5
    };

    ASSERT(collides(square,
                    STATIC_ARRAY_SIZE(square),
                    other_square,
                    STATIC_ARRAY_SIZE(other_square)));
})

TEST(basic_collision_2, {
    double square[] = {
        0.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,
        1.0, 0.0
    };

    double triangle[] = {
        0.9, 0.9,
        0.5, 1.5,
        1.5, 1.5
    };

    ASSERT(collides(square,
                    STATIC_ARRAY_SIZE(square),
                    triangle,
                    STATIC_ARRAY_SIZE(triangle)));
})

TEST_MAIN({
    RUN_TEST(project_vector_basic);
    RUN_TEST(project_vectors);
    RUN_TEST(basic_collision);
    RUN_TEST(basic_collision_2);
})
