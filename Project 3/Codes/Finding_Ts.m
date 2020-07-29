%% 

clear all
clc

%% Reading the datasets

% inputs
u0 = open("../Dataset/u0.mat");
u0 = u0.u0;

%outputs
y0 = open("../Dataset/y0.mat");
y0 = y0.y0;

%% Resample data set

u0_resampled = u0.resample(1:1000);

y0_resampled = y0.resample(1:1000);

%% Ts = 1s

u0_1_data = u0_resampled.Data;

y0_1_data = y0_resampled.Data;

%% Ts = 2s

u0_2_data = u0_resampled.Data(1:2:end);

y0_2_data = y0_resampled.Data(1:2:end);

%% Ts = 3s

u0_3_data = u0_resampled.Data(1:3:end);

y0_3_data = y0_resampled.Data(1:3:end);

%% Setting d (delay)

d1 = 170;
d2 = 85;
d3 = 58;

%% Creating Y Vector - Ts = 1s

Y0_1 = y0_1_data(d1+3:end);

%% Creating Y vector - Ts = 2s

Y0_2 = y0_2_data(d2+3:end);

%% Creating Y vector - Ts = 3s

Y0_3 = y0_3_data(d3+3:end);

%% Creating X Matrix - Ts = 1s

X0_1 = [y0_1_data(d1+2:end-1), u0_1_data(2:end-(d1+1)), u0_1_data(1:end-(d1+2))];


%% Creating X Matrix - Ts = 2s

X0_2 = [y0_2_data(d2+2:end-1), u0_2_data(2:end-(d2+1)), u0_2_data(1:end-(d2+2))];

%% Creating X Matrix - Ts = 3s

X0_3 = [y0_3_data(d3+2:end-1), u0_3_data(2:end-(d3+1)), u0_3_data(1:end-(d3+2))];

%% Finding tetha parameters - Ts = 1s

tetha0_1 = ((X0_1'*X0_1)\X0_1')*Y0_1;
a1_0_1 = tetha0_1(1);
b0_0_1 = tetha0_1(2);
b1_0_1 = tetha0_1(3);

%% Finding tetha parameters - Ts = 2s

tetha0_2 = ((X0_2'*X0_2)\X0_2')*Y0_2;
a1_0_2 = tetha0_2(1);
b0_0_2 = tetha0_2(2);
b1_0_2 = tetha0_2(3);

%% Finding tetha parameters - Ts = 3s

tetha0_3 = ((X0_3'*X0_3)\X0_3')*Y0_3;
a1_0_3 = tetha0_3(1);
b0_0_3 = tetha0_3(2);
b1_0_3 = tetha0_3(3);

%% Finding the model parameters

Ts_1 = 1;
Ts_2 = 2;
Ts_3 = 3;

%% Finding the model parameters - T - Ts = 1s
T_0_1 = -Ts_1/log(a1_0_1);

%% Finding the model parameters - T - Ts = 2s
T_0_2 = -Ts_2/log(a1_0_2);

%% Finding the model parameters - T - Ts = 3s

T_0_3 = -Ts_3/log(a1_0_3);

%% Finding the model parameters - K & L0 - Ts = 1s

% first input
syms K L0

eq1 = b0_0_1 - K*(1-a1_0_1*exp(L0/T_0_1));
eq2 = b1_0_1 - K*a1_0_1*(exp(L0/T_0_1)-1);
sol = solve(eq1,eq2);  

K_0_1   = double(sol.K);
L0_0_1  = double(sol.L0);

%% Finding the model parameters - K & L0 - Ts = 2s

% first input
syms K L0

eq1 = b0_0_2 - K*(1-a1_0_2*exp(L0/T_0_2));
eq2 = b1_0_2 - K*a1_0_2*(exp(L0/T_0_2)-1);
sol = solve(eq1,eq2);  

K_0_2   = double(sol.K);
L0_0_2  = double(sol.L0);

%% Finding the model parameters - K & L0 - Ts = 3s

% first input
syms K L0

eq1 = b0_0_3 - K*(1-a1_0_3*exp(L0/T_0_3));
eq2 = b1_0_3 - K*a1_0_3*(exp(L0/T_0_3)-1);
sol = solve(eq1,eq2);  

K_0_3   = double(sol.K);
L0_0_3  = double(sol.L0);

%% Finding the model parameters - L - Ts = 1s

L_0_1 = d1*Ts_1 + L0_0_1;

%% Finding the model parameters - L - Ts = 2s

L_0_2 = d2*Ts_2 + L0_0_2;

%% Finding the model parameters - L - Ts = 3s

L_0_3 = d3*Ts_3 + L0_0_3;


%% Creating the model  - Ts = 1s

m0_1 = tf(K_0_1,[T_0_1 1],'InputDelay',L_0_1);

%% Creating the model  - Ts = 1s

m0_2 = tf(K_0_2,[T_0_2 1],'InputDelay',L_0_2);

%% Creating the model  - Ts = 1s

m0_3 = tf(K_0_3,[T_0_3 1],'InputDelay',L_0_3);

%% Comparing the model with the siganl - Ts = 1s

figure(1)
hold on

step(m0_1, 1:1000,'r')
plot(y0_1_data)

%% Comparing the model with the siganl - Ts = 2s

figure(2)
hold on

step(m0_2, 1:500,'r')
plot(y0_2_data)

%% Comparing the model with the siganl - Ts = 3s

figure(3)
hold on

step(m0_3, 1:334,'r')
plot(y0_3_data)