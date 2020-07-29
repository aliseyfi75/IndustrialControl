%%

clear all
clc
%% Reading the datasets

% inputs
u = open("../Dataset/u0.mat");
u = u.u0;

%outputs
y = open("../Dataset/y0.mat");
y = y.y0;

%% Resample data set

u_resampled = u.resample(1:1000);

y_resampled = y.resample(1:1000);

%% Ts = 1s

u_data = u_resampled.Data;

y_data = y_resampled.Data;


%% Setting d (delay)

d = 170;

%% initializing P and tetha

P = eye(3);

tetha = ones(3,(length(y_data)-d-2));

error = zeros(1,(length(y_data)-d-2));

%% loop over input and output

for i=1:(length(y_data)-d-2)
   
    x = [y_data(i+d+1), u_data(i+1), u_data(i)];

    y = y_data(i+d+2);

    error(i) = y - x*tetha(:,i);

    P = P * (eye(3) - (x'*x*P)/(1+x*P*x'));
    
    tetha(:,i+1) = tetha(:,i) + P*x'*error(i);
    
end

%% Plotting the tetha over time

figure(1);

hold on

plot(tetha(1,:),'b');

plot(tetha(2,:),'r');

plot(tetha(3,:),'k');

legend("a1", "b0", "b1");

%% Plotting error by time

figure(2);

plot(error);

%% final parameters

a1 = tetha(1,end);
b0 = tetha(2,end);
b1 = tetha(3,end);

%% Finding the model parameters

Ts = 1;

%% Finding the model parameters - T - Ts = 1s
T = -Ts/log(a1);

%% Finding the model parameters - K & L0 - Ts = 1s

% first input
syms K_sym L0_sym

eq1 = b0 - K_sym*(1-a1*exp(L0_sym/T));
eq2 = b1 - K_sym*a1*(exp(L0_sym/T)-1);
sol = solve(eq1,eq2);  

K   = double(sol.K_sym);
L0  = double(sol.L0_sym);

%% Finding the model parameters - L - Ts = 1s

L = d*Ts + L0;


%% Creating the model  - Ts = 1s

m = tf(K,[T 1],'InputDelay',L);

%% Comparing the model with the siganl

figure(3)
hold on

step(m, 1:1000,'r')
plot(y_data)

%% ISE & IAE
result = step(m, 1:500);

ISE = sum((result - y_data(1:500)).^2);
IAE = sum(abs((result - y_data(1:500))));
max_error = abs(max(result - y_data(1:500)));


