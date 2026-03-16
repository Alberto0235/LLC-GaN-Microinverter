#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #ifndef pi
// #define pi 3.14159265358979323846
// #endif


int main() {
    // Dichiarazione delle variabili di input
    double Vin_min, Vin_max, Vin_nom, Vout, Pout, fr, M_nom, Qmax, m, Fxmin, Kmax;
    
    // Input dei valori
    printf("Inserisci Vin_min (Volt): ");
    scanf("%lf", &Vin_min);
    printf("Inserisci Vin_max (Volt): ");
    scanf("%lf", &Vin_max);
    printf("Inserisci Vin_nom (Volt): ");
    scanf("%lf", &Vin_nom);
    printf("Inserisci Vout (Volt): ");
    scanf("%lf", &Vout);
    printf("Inserisci Pout (Watt): ");
    scanf("%lf", &Pout);
    printf("Inserisci fr (Hertz): ");
    scanf("%lf", &fr);
    printf("Inserisci M_nom (1 = Full bridge, 0.5 = Half bridge): ");
    scanf("%lf", &M_nom);
    printf("Inserisci Qmax: ");
    scanf("%lf", &Qmax);
    printf("Inserisci m: ");
    scanf("%lf", &m);
    printf("Inserisci Fxmin: ");
    scanf("%lf", &Fxmin);
    printf("Inserisci Kmax: ");
    scanf("%lf", &Kmax);
    
    // Calcoli
    double pi = M_PI;
    double Np_Ns = (Vin_nom/Vout)*M_nom;
    double M_max = (Vin_nom/Vin_min)*M_nom;
    double M_min = (Vin_nom/Vin_max)*M_nom;
    double fs_min = Fxmin*fr;
    double Qmax_vmin = Qmax*(Vin_min/Vin_max);

    // K > M

    double Rac_min = (8/(pow(pi, 2)))*pow(Np_Ns, 2)*(pow(Vout, 2)/Pout);
    double Cr = sqrt(1/(pow(2*pi*fr, 2)*pow(Qmax*Rac_min, 2)));
    double Lr = pow(Qmax*Rac_min, 2)*Cr;
    double Lm = (m*Lr)-Lr;

    
    // Output dei risultati
    printf("\nOutput:\n");
    printf("Np/Ns: %lf\n", Np_Ns);
    printf("M_max: %lf\n", M_max);
    printf("M_min: %lf\n", M_min);
    printf("fs_min (Hertz): %lf\n", fs_min);
    printf("Qmax@vmin: %lf\n", Qmax_vmin);

    printf("Kmax: %lf e M_max: %lf\n", Kmax, M_max);

    printf("Rac_min (Ohm): %lf\n", Rac_min);
    printf("Lr (Henry): %0.15lf\n", Lr);
    printf("Cr (Farad): %0.15lf\n", Cr);
    printf("Lm (Henry): %0.15lf\n", Lm);

    //conversione
    double Lr_nH = Lr*1e9;
    double Cr_nF = Cr*1e9;
    double Lm_nH = Lm*1e9;

    printf("\nConversione:\n");
    printf("Lr (nH): %lf\n", Lr_nH);
    printf("Cr (nF): %lf\n", Cr_nF);
    printf("Lm (nH): %lf\n", Lm_nH);

    return 0;
}
