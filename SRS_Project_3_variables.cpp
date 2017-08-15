#include <iostream>
#include <cmath>
#include<iomanip>
using namespace std;

const double EPS=1e-9, epsi=1e-10;

double x_0, y_0, z_0, v_0, u_0, s_0;

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
double f(double x, double y, double z) {

    return ( 100*(y-x*x)*(y-x*x) + (x-1)*(x-1) + 100*(z-y*y)*(z-y*y) + (y-1)*(y-1) );
}
double f_x(double x, double y, double z) {

    return ( 2*(x-1)-400*x*(y-x*x) );
}
double f_y(double x, double y, double z) {

    return ( 400*y*y*y + 202*y - 400*y*z - 200*x*x -2 );
}
double f_z(double x, double y, double z) {

    return ( 200*(z-y*y) );
}



double g_t(double t) {

    return f(x_0+t*u_0, y_0+t*v_0, z_0+t*s_0);
}

int main(int argc, char **argv) {

    double x1, y1,  x2, y2, z2;

    x_0=1;
    y_0=1;
    z_0=1;

    u_0=f_x(x_0, y_0, z_0);
    v_0=f_y(x_0, y_0, z_0);
    s_0=f_z(x_0, y_0, z_0);
    // въпрос на долния ред за z
    while(u_0*u_0 + v_0*v_0 + s_0*s_0 > epsi) {

        //cout << x_0 << " " << y_0 << "  " << f(x_0, y_0) << endl;


        u_0=f_x(x_0, y_0, z_0);
        v_0=f_y(x_0, y_0, z_0);
        s_0=f_z(x_0, y_0, z_0);

        double t0=goldenRatioMethodMin(g_t, -10.,10.);
        //cout << t0 << endl;
        x2=x_0+t0*u_0;
        y2=y_0+t0*v_0;
        z2=z_0+t0*s_0;

        x_0=x2;
        y_0=y2;
        z_0=z2;
    }

    cout<<x_0<< " " << y_0<<" "<< z_0 << endl;

    return 0;
}
