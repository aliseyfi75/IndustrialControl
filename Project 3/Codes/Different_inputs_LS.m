%% Reading the datasets

% inputs
u1 = open("../Dataset/u1.mat");
u1 = u1.u1;

u2 = open("../Dataset/u2.mat");
u2 = u2.u2;

u3 = open("../Dataset/u3.mat");
u3 = u3.u3;

%outputs
y1 = open("../Dataset/y1.mat");
y1 = y1.y1;

y2 = open("../Dataset/y2.mat");
y2 = y2.y2;

y3 = open("../Dataset/y3.mat");
y3 = y3.y3;

%% Resample data set

u1_resampled = u1.resample(1:1000);
u2_resampled = u2.resample(1:1000);
u3_resampled = u3.resample(1:1000);

y1_resampled = y1.resample(1:1000);
y2_resampled = y2.resample(1:1000);
y3_resampled = y3.resample(1:1000);


%% Ts = 1s

u1_1_data = u1_resampled.Data;
u2_1_data = u2_resampled.Data;
u3_1_data = u3_resampled.Data;

y1_1_data = y1_resampled.Data;
y2_1_data = y2_resampled.Data;
y3_1_data = y3_resampled.Data;

%% Ts = 2s

u1_2_data = u1_resampled.Data(1:2:end);
u2_2_data = u2_resampled.Data(1:2:end);
u3_2_data = u3_resampled.Data(1:2:end);

y1_2_data = y1_resampled.Data(1:2:end);
y2_2_data = y2_resampled.Data(1:2:end);
y3_2_data = y3_resampled.Data(1:2:end);

%% Ts = 3s

u1_3_data = u1_resampled.Data(1:3:end);
u2_3_data = u2_resampled.Data(1:3:end);
u3_3_data = u3_resampled.Data(1:3:end);

y1_3_data = y1_resampled.Data(1:3:end);
y2_3_data = y2_resampled.Data(1:3:end);
y3_3_data = y3_resampled.Data(1:3:end);

%% Setting d (delay)

d = 150;

%% Creating Y Vector - Ts = 1s

Y1_1 = y1_1_data(d+3:end);
Y2_1 = y2_1_data(d+3:end);
Y3_1 = y3_1_data(d+3:end);

%% Creating Y vector - Ts = 2s

Y1_2 = y1_2_data(d+3:end);
Y2_2 = y2_2_data(d+3:end);
Y3_2 = y3_2_data(d+3:end);

%% Creating Y vector - Ts = 3s

Y1_3 = y1_3_data(d+3:end);
Y2_3 = y2_3_data(d+3:end);
Y3_3 = y3_3_data(d+3:end);

%% Creating X Matrix - Ts = 1s

X1_1 = [y1_1_data(d+2:end-1), u1_1_data(2:end-(d+1)), u1_1_data(1:end-(d+2))];
X2_1 = [y2_1_data(d+2:end-1), u2_1_data(2:end-(d+1)), u2_1_data(1:end-(d+2))];
X3_1 = [y3_1_data(d+2:end-1), u3_1_data(2:end-(d+1)), u3_1_data(1:end-(d+2))];

%% Creating X Matrix - Ts = 2s

X1_2 = [y1_2_data(d+2:end-1), u1_2_data(2:end-(d+1)), u1_2_data(1:end-(d+2))];
X2_2 = [y2_2_data(d+2:end-1), u2_2_data(2:end-(d+1)), u2_2_data(1:end-(d+2))];
X3_2 = [y3_2_data(d+2:end-1), u3_2_data(2:end-(d+1)), u3_2_data(1:end-(d+2))];

%% Creating X Matrix - Ts = 3s

X1_3 = [y1_3_data(d+2:end-1), u1_3_data(2:end-(d+1)), u1_3_data(1:end-(d+2))];
X2_3 = [y2_3_data(d+2:end-1), u2_3_data(2:end-(d+1)), u2_3_data(1:end-(d+2))];
X3_3 = [y3_3_data(d+2:end-1), u3_3_data(2:end-(d+1)), u3_3_data(1:end-(d+2))];

%% Finding tetha parameters - Ts = 1s

tetha1_1 = ((X1_1'*X1_1)\X1_1')*Y1_1;
a1_1_1 = tetha1_1(1);
b0_1_1 = tetha1_1(2);
b1_1_1 = tetha1_1(3);

tetha2_1 = ((X2_1'*X2_1)\X2_1')*Y2_1;
a1_2_1 = tetha2_1(1);
b0_2_1 = tetha2_1(2);
b1_2_1 = tetha2_1(3);

tetha3_1 = ((X3_1'*X3_1)\X3_1')*Y3_1;
a1_3_1 = tetha3_1(1);
b0_3_1 = tetha3_1(2);
b1_3_1 = tetha3_1(3);

%% Finding tetha parameters - Ts = 2s

tetha1_2 = ((X1_2'*X1_2)\X1_2')*Y1_2;
a1_1_2 = tetha1_2(1);
b0_1_2 = tetha1_2(2);
b1_1_2 = tetha1_2(3);

tetha2_2 = ((X2_2'*X2_2)\X2_2')*Y2_2;
a1_2_2 = tetha2_2(1);
b0_2_2 = tetha2_2(2);
b1_2_2 = tetha2_2(3);

tetha3_2 = ((X3_2'*X3_2)\X3_2')*Y3_2;
a1_3_2 = tetha3_2(1);
b0_3_2 = tetha3_2(2);
b1_3_2 = tetha3_2(3);

%% Finding tetha parameters - Ts = 3s

tetha1_3 = ((X1_3'*X1_3)\X1_3')*Y1_3;
a1_1_3 = tetha1_3(1);
b0_1_3 = tetha1_3(2);
b1_1_3 = tetha1_3(3);

tetha2_3 = ((X2_3'*X2_3)\X2_3')*Y2_3;
a1_2_3 = tetha2_3(1);
b0_2_3 = tetha2_3(2);
b1_2_3 = tetha2_3(3);

tetha3_3 = ((X3_3'*X3_3)\X3_3')*Y3_3;
a1_3_3 = tetha3_3(1);
b0_3_3 = tetha3_3(2);
b1_3_3 = tetha3_3(3);

%% Finding the model parameters

Ts_1 = 1;
Ts_2 = 2;
Ts_3 = 3;

%% Finding the model parameters - T - Ts = 1s
T_1_1 = -Ts_1/log(a1_1_1);
T_2_1 = -Ts_1/log(a1_2_1);
T_3_1 = -Ts_1/log(a1_3_1);

%% Finding the model parameters - T - Ts = 2s

T_1_2 = -Ts_2/log(a1_1_2);
T_2_2 = -Ts_2/log(a1_2_2);
T_3_2 = -Ts_2/log(a1_3_2);

%% Finding the model parameters - T - Ts = 3s

T_1_3 = -Ts_3/log(a1_1_3);
T_2_3 = -Ts_3/log(a1_2_3);
T_3_3 = -Ts_3/log(a1_3_3);

%% Finding the model parameters - K & L0 - Ts = 1s

% first input
syms K L0

eq1 = b0_1_1 - K*(1-a1_1_1*exp(L0/T_1_1));
eq2 = b1_1_1 - K*a1_1_1*(exp(L0/T_1_1)-1);
sol = solve(eq1,eq2);  

K_1_1   = double(sol.K);
L0_1_1  = double(sol.L0);

% second input

syms K L0

eq1 = b0_2_1 - K*(1-a1_2_1*exp(L0/T_2_1));
eq2 = b1_2_1 - K*a1_2_1*(exp(L0/T_2_1)-1);
sol = solve(eq1,eq2);  

K_2_1   = double(sol.K);
L0_2_1  = double(sol.L0);

% third input

syms K L0

eq1 = b0_3_1 - K*(1-a1_3_1*exp(L0/T_3_1));
eq2 = b1_3_1 - K * a1_3_1*(exp(L0/T_3_1)-1);
sol = solve(eq1,eq2);  

K_3_1   = double(sol.K);
L0_3_1  = double(sol.L0);

%% Finding the model parameters - K & L0 - Ts = 2s

% first input
syms K L0

eq1 = b0_1_2 - K*(1-a1_1_2*exp(L0/T_1_2));
eq2 = b1_1_2 - K*a1_1_2*(exp(L0/T_1_2)-1);
sol = solve(eq1,eq2);  

K_1_2   = double(sol.K);
L0_1_2  = double(sol.L0);

% second input

syms K L0

eq1 = b0_2_2 - K*(1-a1_2_2*exp(L0/T_2_2));
eq2 = b1_2_2 - K*a1_2_2*(exp(L0/T_2_2)-1);
sol = solve(eq1,eq2); 

K_2_2   = double(sol.K);
L0_2_2  = double(sol.L0);

% third input

syms K L0

eq1 = b0_3_2 - K*(1-a1_3_2*exp(L0/T_3_2));
eq2 = b1_3_2 - K * a1_3_2*(exp(L0/T_3_2)-1);
sol = solve(eq1,eq2);  

K_3_2   = double(sol.K);
L0_3_2  = double(sol.L0);

%% Finding the model parameters - K & L0 - Ts = 3s

% first input
syms K L0

eq1 = b0_1_3 - K*(1-a1_1_3*exp(L0/T_1_3));
eq2 = b1_1_3 - K*a1_1_3*(exp(L0/T_1_3)-1);
sol = solve(eq1,eq2);  

K_1_3   = double(sol.K);
L0_1_3  = double(sol.L0);

% second input

syms K L0

eq1 = b0_2_3 - K*(1-a1_2_3*exp(L0/T_2_3));
eq2 = b1_2_3 - K*a1_2_3*(exp(L0/T_2_3)-1);
sol = solve(eq1,eq2);  

K_2_3   = double(sol.K);
L0_2_3  = double(sol.L0);

% third input

syms K L0

eq1 = b0_3_3 - K*(1-a1_3_3*exp(L0/T_3_3));
eq2 = b1_3_3 - K * a1_3_3*(exp(L0/T_3_3)-1);
sol = solve(eq1,eq2);  

K_3_3   = double(sol.K);
L0_3_3  = double(sol.L0);

%% Finding the model parameters - L - Ts = 1s

L_1_1 = d*Ts_1 + L0_1_1;
L_2_1 = d*Ts_1 + L0_2_1;
L_3_1 = d*Ts_1 + L0_3_1;

%% Finding the model parameters - L - Ts = 2s

L_1_2 = d*Ts_2 + L0_1_2;
L_2_2 = d*Ts_2 + L0_2_2;
L_3_2 = d*Ts_2 + L0_3_2;

%% Finding the model parameters - L - Ts = 3s

L_1_3 = d*Ts_3 + L0_1_3;
L_2_3 = d*Ts_3 + L0_2_3;
L_3_3 = d*Ts_3 + L0_3_3;
