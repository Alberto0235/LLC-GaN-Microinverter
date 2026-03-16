clc;
clear all;
close all;

% Dichiarazione delle variabili di input
Vin_min = input('Inserisci Vin_min (Volt): ');
Vin_max = input('Inserisci Vin_max (Volt): ');
Vin_nom = input('Inserisci Vin_nom (Volt): ');
Vout = input('Inserisci Vout (Volt): ');
Pout = input('Inserisci Pout (Watt): ');
fr = input('Inserisci fr (Hertz): ');
M_nom = input('Inserisci M_nom (1 = Full bridge, 0.5 = Half bridge): ');
Qmax = input('Inserisci Qmax: ');
m = input('Inserisci m: ');
Fxmin = input('Inserisci Fxmin: ');
Kmax = input('Inserisci Kmax: ');

% Calcoli
pi_value = pi; % Ottieni il valore di pi da MATLAB
Np_Ns = (Vin_nom/Vout)*M_nom;
M_max = double((Vin_nom/Vin_min)*M_nom);
M_min = double((Vin_nom/Vin_max)*M_nom);
fs_min = Fxmin*fr;
Qmax_vmin = Qmax*(Vin_min/Vin_max);

% Calcolo di Rac_min con valori numerici
Rac_min = double((8/(pi_value^2))*(Np_Ns^2)*((Vout^2)/Pout));

Cr = double(sqrt(1/(power(2*pi_value*fr, 2)*power(Qmax*Rac_min, 2))));
Lr = double(power(Qmax*Rac_min, 2)*Cr);
Lm = double((m*Lr)-Lr);

% Output dei risultati
fprintf('\nOutput:\n');
fprintf('Np/Ns: %f\n', Np_Ns);
fprintf('M_max: %f\n', M_max);
fprintf('M_min: %f\n', M_min);
fprintf('fs_min (Hertz): %f\n', fs_min);
fprintf('Qmax@vmin: %f\n', Qmax_vmin);

fprintf('Kmax: %f e M_max: %f\n', Kmax, M_max);

fprintf('Rac_min (Ohm): %f\n', Rac_min);
fprintf('Lr (Henry): %.15f\n', Lr);
fprintf('Cr (Farad): %.15f\n', Cr);
fprintf('Lm (Henry): %.15f\n', Lm);

% Conversione
Lr_nH = Lr*1e9;
Cr_nF = Cr*1e9;
Lm_nH = Lm*1e9;

fprintf('\nConversione:\n');
fprintf('Lr (nH): %f\n', Lr_nH);
fprintf('Cr (nF): %f\n', Cr_nF);
fprintf('Lm (nH): %f\n', Lm_nH);
