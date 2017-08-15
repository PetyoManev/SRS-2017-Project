#include <iostream>
#include <cmath>
#include<iomanip>
using namespace std;

class Optimization {

    double EPS, epsi;

    double v_0, u_0, s_0;
    double x1[5], y1[5], x3[5], y3[5];

    double x_0;
    double y_0;
    double z_0;

public:
    void init() {
        EPS=1e-9;
        epsi=1e-10;



        x_0=1;
        y_0=1;
        z_0=1;
    }

    double g_t(double t) {

        return sborna_Func(x_0+t*u_0, y_0+t*v_0, z_0+t*s_0);
    }

    double goldenRatioMethodMin(double a, double b) {
        double k = (sqrt(5.) - 1.) / 2.;
        double xL = b - k * (b - a);
        double xR = a + k * (b - a);
        while (b - a > EPS) {
            if (g_t(xL) > g_t(xR)) {
                a = xL;
                xL = xR;
                xR = a + k*(b - a);
            } else {
                b = xR;
                xR = xL;
                xL = b - k*(b - a);
            }
        }
        return (a + b) / 2.;
    }
// Point gradientMethod(double(*p_pFunction)(double, double), double ax, double bx, double ay, double by)
public:
    void input() {

        for(int i=0; i<5; i++)
            cin>>x1[i]>>y1[i];
        for(int i=0; i<5; i++)
            cin >> x3[i]>>y3[i];
    }
    //cout<<endl;

    double h_gs_tester(double x) {

        return (3*x*x+3.125);
    }

    double f(int j,double x, double y, double z) {

        return (     (x1[j]-(x3[j]+x)*z)*(x1[j]-(x3[j]+x)*z)      );
    }
    double f_x(int j, double x, double y, double z) {

        return ( 2*(x1[j]-(x3[j]+x)*z)*z);
    }
    double f_y(int j, double x, double y, double z) {

        return 0; //  return (  );
    }
    double f_z(int j, double x, double y, double z) {

        return ( -2*(x1[j]-(x3[j]+x)*z)*(x3[j]+x));
    }


    double g(int j, double x, double y, double z) {
        return (   (y1[j]-(y3[j]+y)*z)*(y1[j]-(y3[j]+y)*z)  );
    }

    double g_x(int j, double x, double y, double z) {
        return 0;
    }

    //}
    double g_y(int j, double x, double y, double z) {

        return (2*(y1[j]-(y3[j]+y)*z)*z );

    }

    double g_z(int j, double x, double y, double z) {

        return ( -2*(y1[j]-(y3[j]+y)*z)*(y3[j]+y));
    }


    double sborna_Func(double x, double y, double z) {
        double S=0;
        for(int j=0; j<5; j++) S=S+f(j,x,y,z)+g(j,x,y,z);
        return S;
    }
    double sborna_Func_x(double x, double y, double z) {
        double S=0;
        for(int j=0; j<5; j++) S=S+f_x(j,x,y,z)+g_x(j,x,y,z);
        return S;
    }
    double sborna_Func_y(double x, double y, double z) {
        double S=0;
        for(int j=0; j<5; j++) S=S+f_y(j,x,y,z)+g_y(j,x,y,z);
        return S;
    }
    double sborna_Func_z(double x, double y, double z) {
        double S=0;
        for(int j=0; j<5; j++) S=S+f_z(j,x,y,z)+g_z(j,x,y,z);
        return S;
    }


    double x2, y2, z2;





public:
    void opt() {



        u_0=sborna_Func_x(x_0, y_0, z_0);
        v_0=sborna_Func_y(x_0, y_0, z_0);
        s_0=sborna_Func_z(x_0, y_0, z_0);



        int br=0;
        while(u_0*u_0 + v_0*v_0 + s_0*s_0 > epsi) {



            //cout << u_0*u_0 + v_0*v_0 + s_0*s_0 << endl;

            br++;
            if(br>1000) break;
            u_0=sborna_Func_x(x_0, y_0, z_0);
            v_0=sborna_Func_y(x_0, y_0, z_0);
            s_0=sborna_Func_z(x_0, y_0, z_0);


            double t0=goldenRatioMethodMin(-10.,10.);
            //cout << t0 << endl;
            x2=x_0+t0*u_0;
            y2=y_0+t0*v_0;
            z2=z_0+t0*s_0;

            x_0=x2;
            y_0=y2;
            z_0=z2;
        }

        cout << u_0*u_0 + v_0*v_0 + s_0*s_0 << endl;

        cout << x_0 << " " << y_0 << " " << z_0 << endl;


    }

};

int main(int argc, char **argv) {

    Optimization method;
    method.init();
    method.input();
    method.opt();


    return 0;
}
