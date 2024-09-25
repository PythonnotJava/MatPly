//
// Created by 25654 on 24-9-20.
//

#include "mp_geometry.h"

#ifdef MP_CFG_H
#else
    #include "mp_cfg.h"
#endif

#ifdef MP_MANAGE_H
#else
    #include "mp_manage.h"
#endif

#ifdef  _standard_uniform
#else
    static inline double _standard_uniform() {
        return (double)rand_func() / MAXRAND;
    }
#endif

#ifdef _TIME_H_
#else
#include <time.h>
#endif

#ifdef _MATH_H_
#else
#include <math.h>
#endif

// 随机抖动，范围是[-bias / 2, bias / 2]
static inline double _random_bias(double bias) {
    return  (_standard_uniform() - 0.5) * bias;
}

double ** ellipse_edge(int size, double a, double b, int seed, bool use, double bias) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double **)malloc(sizeof(double *) * size);
    double theta;
    for (int i = 0; i < size; i++) {
        new[i] = (double *)malloc(sizeof (double) * 2);
        theta = 2 * M_PI * _standard_uniform();
        new[i][0] = a * cos(theta) + _random_bias(bias);
        new[i][1] = b * sin(theta) + _random_bias(bias);
    }
    return new;
}

double ** ellipse_area(int size, double a, double b, int seed, bool use, double bias) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double **)malloc(sizeof(double *) * size);
    double theta, r;
    for (int i = 0; i < size; i++) {
        new[i] = (double *)malloc(sizeof(double) * 2);
        theta = 2 * M_PI * _standard_uniform();
        r = sqrt(_standard_uniform());
        new[i][0] = a * r * cos(theta) + _random_bias(bias);
        new[i][1] = b * r * sin(theta) + _random_bias(bias);
    }
    return new;
}

double ** circle_edge(int size, double r, int seed, bool use, double bias) {
    return ellipse_edge(size, r, r, seed, use, bias);
}

double ** circle_area(int size, double r, int seed, bool use, double bias) {
    return  ellipse_area(size, r, r, seed, use, bias);
}

double ** line(int size, Point2D start, Point2D end, int seed, bool use, double bias) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double **)malloc(sizeof(double *) * size);
    double t;
    double deltax = end.x - start.x, deltay = end.y - start.y;
    for (int i = 0; i < size; i++) {
        new[i] = (double *)malloc(sizeof(double) * 2);
        t = _standard_uniform();
        new[i][0] = start.x + t * deltax + _random_bias(bias);
        new[i][1] = start.y + t * deltay + _random_bias(bias);
    }

    return new;
}

double ** triangle_edge(int size, Point2D a, Point2D b, Point2D c, int seed, bool use, double bias) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double **)malloc(sizeof(double *) * size);
    double t, u, delta1, delta2, delta3, delta4, delta5, delta6;
    delta1 = b.x - a.x;
    delta2 = b.y - a.y;
    delta3 = c.x - b.x;
    delta4 = c.y - b.y;
    delta5 = a.x - c.x;
    delta6 = a.y - c.y;
    for (int i = 0; i < size; i++) {
        new[i] = (double *)malloc(sizeof(double) * 2);
        t = _standard_uniform();
        u = _standard_uniform();
        if (t < 1.0 / 3.0) {
            new[i][0] = a.x + u * delta1 + _random_bias(bias);
            new[i][1] = a.y + u * delta2 + _random_bias(bias);
        } else if (t < 2.0 / 3.0) {
            new[i][0] = b.x + u * delta3 + _random_bias(bias);
            new[i][1] = b.y + u * delta4 + _random_bias(bias);
        } else {
            new[i][0] = c.x + u * delta5 + _random_bias(bias);
            new[i][1] = c.y + u * delta6 + _random_bias(bias);
        }
    }
    return new;
}

double ** triangle_area(int size, Point2D a, Point2D b, Point2D c, int seed, bool use, double bias) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double **)malloc(sizeof(double *) * size);
    double delta1, delta2, delta3, delta4;
    delta1 = b.x - a.x;
    delta2 = c.x - a.x;
    delta3 = b.y - a.y;
    delta4 = c.y - a.y;
    for (int i = 0; i < size; i++) {
        new[i] = (double *)malloc(sizeof(double) * 2);
        double u = _standard_uniform();
        double v = _standard_uniform();
        if (u + v > 1.0) {
            u = 1.0 - u;
            v = 1.0 - v;
        }
        new[i][0] = a.x + u * delta1 + v * delta2 + _random_bias(bias);
        new[i][1] = a.y + u * delta3 + v * delta4 + _random_bias(bias);
    }
    return new;
}

double ** quadrilateral_edge(
    int size, Point2D a, Point2D b, Point2D c, Point2D d, int seed, bool use, double bias
) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double **new = (double **)malloc(sizeof(double *) * size);
    int edge_size = size / 4;
    int remaining = size % 4;
    double t;
    double ab_x = b.x - a.x, ab_y = b.y - a.y;
    double bc_x = c.x - b.x, bc_y = c.y - b.y;
    double cd_x = d.x - c.x, cd_y = d.y - c.y;
    double da_x = a.x - d.x, da_y = a.y - d.y;
    int idx = 0;
    for (int i = 0; i < edge_size + (remaining > 0 ? 1 : 0); i++, idx++) {
        new[idx] = (double *)malloc(sizeof(double) * 2);
        t = (double)i / (edge_size + (remaining > 0 ? 1 : 0));
        new[idx][0] = a.x + t * ab_x + _random_bias(bias);
        new[idx][1] = a.y + t * ab_y + _random_bias(bias);
    }
    remaining--;
    for (int i = 0; i < edge_size + (remaining > 0 ? 1 : 0); i++, idx++) {
        new[idx] = (double *)malloc(sizeof(double) * 2);
        t = (double)i / (edge_size + (remaining > 0 ? 1 : 0));
        new[idx][0] = b.x + t * bc_x + _random_bias(bias);
        new[idx][1] = b.y + t * bc_y + _random_bias(bias);
    }
    remaining--;
    for (int i = 0; i < edge_size + (remaining > 0 ? 1 : 0); i++, idx++) {
        new[idx] = (double *)malloc(sizeof(double) * 2);
        t = (double)i / (edge_size + (remaining > 0 ? 1 : 0));
        new[idx][0] = c.x + t * cd_x + _random_bias(bias);
        new[idx][1] = c.y + t * cd_y + _random_bias(bias);
    }
    remaining--;
    for (int i = 0; i < edge_size + (remaining > 0 ? 1 : 0); i++, idx++) {
        new[idx] = (double *)malloc(sizeof(double) * 2);
        t = (double)i / (edge_size + (remaining > 0 ? 1 : 0));
        new[idx][0] = d.x + t * da_x + _random_bias(bias);
        new[idx][1] = d.y + t * da_y + _random_bias(bias);
    }
    return new;
}

//////////////////////////////////////////////////////////////////
double cross_product(Point2D o, Point2D a, Point2D b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

bool is_convex(Point2D a, Point2D b, Point2D c, Point2D d) {
    double z1 = cross_product(a, b, c);
    double z2 = cross_product(b, c, d);
    double z3 = cross_product(c, d, a);
    double z4 = cross_product(d, a, b);

    bool has_positive = (z1 > 0) || (z2 > 0) || (z3 > 0) || (z4 > 0);
    bool has_negative = (z1 < 0) || (z2 < 0) || (z3 < 0) || (z4 < 0);
    return !(has_positive && has_negative);
}

double _triangle_area(Point2D a, Point2D b, Point2D c) {
    return fabs((a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0);
}

Point2D random_point_in_triangle(Point2D a, Point2D b, Point2D c) {
    double u = _standard_uniform();
    double v = _standard_uniform();
    if (u + v > 1.0) {
        u = 1.0 - u;
        v = 1.0 - v;
    }
    Point2D p;
    p.x = a.x + u * (b.x - a.x) + v * (c.x - a.x);
    p.y = a.y + u * (b.y - a.y) + v * (c.y - a.y);
    return p;
}

double ** quadrilateral_area(
    int size, Point2D a, Point2D b, Point2D c, Point2D d, int seed, bool use, double bias
) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double**)malloc(sizeof(double *) * size);
    bool convex = is_convex(a, b, c, d);
    Point2D t1_p1, t1_p2, t1_p3;
    Point2D t2_p1, t2_p2, t2_p3;
    if (convex) {
        t1_p1 = a;
        t1_p2 = b;
        t1_p3 = c;
        t2_p1 = a;
        t2_p2 = c;
        t2_p3 = d;
    } else {
        t1_p1 = b;
        t1_p2 = c;
        t1_p3 = d;
        t2_p1 = b;
        t2_p2 = d;
        t2_p3 = a;
    }

    double area1 = _triangle_area(t1_p1, t1_p2, t1_p3);
    double area2 = _triangle_area(t2_p1, t2_p2, t2_p3);
    double total_area = area1 + area2;
    Point2D point_2d;
    double r;
    for (int i = 0; i < size; i++) {
        new[i] = (double *)malloc(sizeof(double) * 2);
        r = _standard_uniform() * total_area;
        if (r < area1) {
            point_2d = random_point_in_triangle(t1_p1, t1_p2, t1_p3);
        } else {
            point_2d = random_point_in_triangle(t2_p1, t2_p2, t2_p3);
        }
        new[i][0] = point_2d.x + _random_bias(bias);
        new[i][1] = point_2d.y + _random_bias(bias);
    }
    return new;
}

double ** heart_edge(int size, double x_center, int seed, bool use, double bias) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double x, y ,t;
    double **new = (double **)malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++) {
        new[i] = (double *)malloc(2 * sizeof(double));
         t = _standard_uniform() * 2.0 * M_PI;
         x = 16.0 * pow(sin(t), 3);
         y = 13.0 * cos(t) - 5.0 * cos(2.0 * t) - 2.0 * cos(3.0 * t) - cos(4.0 * t);
        new[i][0] = x + x_center + _random_bias(bias);
        new[i][1] = y + _random_bias(bias);
    }

    return new;
}

double ** heart_area(int size, double x_center, int seed, bool use, double bias) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double **)malloc(sizeof(double*) * size);
    double t, u, x, y;
    for (int i = 0; i < size; i++) {
        new[i] = (double*)malloc(sizeof(double) *2 );
        t = _standard_uniform() * 2.0 * M_PI;
        u = sqrt(_standard_uniform());
        x = 16.0 * pow(sin(t), 3) * u;
        y = (13.0 * cos(t) - 5.0 * cos(2.0 * t) - 2.0 * cos(3.0 * t) - cos(4.0 * t)) * u;
        new[i][0] = x + x_center + _random_bias(bias);
        new[i][1] = y + _random_bias(bias);
    }
    return new;
}

double ** curve(int size, double x1, double x2, double (*func)(double), int seed, bool use, double bias) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double **)malloc(size * sizeof(double *));
    double delta_x = (x2 - x1) / (size - 1);
    double x, y;
    for (int i = 0; i < size; i++) {
        new[i] = (double *)malloc(2 * sizeof(double));
         x = x1 + i * delta_x;
         y = func(x);
        new[i][0] = x + _random_bias(bias);
        new[i][1] = y + _random_bias(bias);
    }

    return new;
}

Point2D bezier_point(Point2D start, Point2D end, Point2D control, double t) {
    Point2D point;
    point.x = (1 - t) * (1 - t) * start.x + 2 * (1 - t) * t * control.x + t * t * end.x;
    point.y = (1 - t) * (1 - t) * start.y + 2 * (1 - t) * t * control.y + t * t * end.y;
    return point;
}

// 生成贝塞尔曲线上的点
double ** bezier(
    int size, Point2D start, Point2D end, Point2D control, int seed, bool use, double bias
) {
    use ? setSeed(seed) : setSeed(time(NULL));

    double **curve = (double **)malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++) {
        curve[i] = (double *)malloc(2 * sizeof(double));
    }
    for (int i = 0; i < size; i++) {
        double u = (double)i / (size - 1);
        Point2D point = bezier_point(start, end, control, u);
        curve[i][0] = point.x + _random_bias(bias);
        curve[i][1] = point.y + _random_bias(bias);
    }

    return curve;
}

void shake(int row, int column, double ** data, int seed, bool use, double bias){
    use ? setSeed(seed) : setSeed(time(NULL ));
    for (int r = 0;r < row;r++) {
        for(int c = 0;c < column;c ++)
            data[r][c] += _random_bias(bias);
    }
}

double ** custom_curve(
    int size, coord_func x_func, coord_func y_func, void* params, double theta_start, double theta_step, int seed, bool use, double bias
) {
    use ? setSeed(seed) : setSeed(time(NULL));
    double ** new = (double**)malloc(size * sizeof(double*));
    double theta;
    for (int i = 0; i < size; i++) {
        new[i] = (double*)malloc(2 * sizeof(double));
        theta = theta_start + i * theta_step;
        new[i][0] = x_func(theta, params) + _random_bias(bias);
        new[i][1] = y_func(theta, params) + _random_bias(bias);
    }
    return new;
}