#include <iostream>
#include <cmath>
#include<iomanip>
using namespace std;

const double EPS=1e-9, epsi=1e-10;

double x_0, y_0, z_0, k_0, v_0, u_0, s_0, n_0;

double goldenRatioMethodMin(double(*p_pFunction)(double), double a, double b) {
    double k = (sqrt(5.) - 1.) / 2.;
    double xL = b - k * (b - a);
    double xR = a + k * (b - a);
    while (b - a > EPS) {
        if (p_pFunction(xL) > p_pFunction(xR)) {
            a = xL;
            xL = xR;
            xR = a + k * (b - a);
        } else {
            b = xR;
            xR = xL;
            xL = b - k*(b - a);
        }
    }
    return (a + b) / 2.;
}
// Point gradientMethod(double(*p_pFunction)(double, double), double ax, double bx, double ay, double by)

double h_gs_tester(double x) {
    return (3*x*x+3.125);
}

double f(double x, double y, double z, double k) {

    return ( x*x + y*y + z*z + k*k );
}

double f_x(double x, double y, double z, double k) {

    return ( 2*x );
}

double f_y(double x, double y, double z, double k) {

    return ( 2*y );
}

double f_z(double x, double y, double z, double k) {

    return ( 2*z );
}

double f_k(double x, double y, double z, double k) {

    return ( 2*k );
}


double g_t(double t) {
    return f(x_0+t*u_0, y_0+t*v_0, z_0+t*s_0, k_0+t*n_0);
}

int main(int argc, char **argv) {

    double x1, y1,  x2, y2, z2, k2;

    x_0=5;
    y_0=5;
    z_0=5;
    k_0=5;

    u_0=f_x(x_0, y_0, z_0, k_0);
    v_0=f_y(x_0, y_0, z_0, k_0);
    s_0=f_z(x_0, y_0, z_0, k_0);
    n_0=f_k(x_0, y_0, z_0, k_0);

    while(u_0*u_0 + v_0*v_0 + s_0*s_0 + n_0*n_0 > epsi) {

        //cout << x_0 << " " << y_0 << "  " << f(x_0, y_0) << endl;


        u_0=f_x(x_0, y_0, z_0, k_0);
        v_0=f_y(x_0, y_0, z_0, k_0);
        s_0=f_z(x_0, y_0, z_0, k_0);
        n_0=f_k(x_0, y_0, z_0, k_0);

        double t0=goldenRatioMethodMin(g_t, -10.,10.);
        //cout << t0 << endl;
        x2=x_0+t0*u_0;
        y2=y_0+t0*v_0;
        z2=z_0+t0*s_0;
        k2=k_0+t0*n_0;

        x_0=x2;
        y_0=y2;
        z_0=z2;
        k_0=k2;
    }

    cout<< x_0<< " " << y_0<<" "<< z_0<< " "<< k_0 << endl;

    return 0;
}
