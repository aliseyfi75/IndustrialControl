%% generate random input
n = 800;
EndTimeOfSimulation = 800;

f   = linspace(0.001,0.006,n);
A   = linspace(0.01,0.1,n);
t   = linspace(0,EndTimeOfSimulation,n);
ph  = pi *(2*rand(length(f),1) - 1);

RandomInput = 0;
%ph is a vector - it must be indexed now

for i = 1 : length(f)
    RandomInput = RandomInput + A(i) * cos(2*pi*f(i) * t + ph(i));
end

rand_temp   = zeros(1,100);
RandomInput = [rand_temp RandomInput];

plot(RandomInput)
%% 3-Parameter 1st order model using area methods - step input
signal  = simout.Data;
data    = signal(end-200:end);

k       = mean(data);

integral_a0 = sum(k - signal) * 0.3;
t_ar        = integral_a0 / k;

integral_a1 = sum(signal(1:ceil(t_ar/0.3))) * 0.3;

T = exp(1) * integral_a1 / k;
L = t_ar - T;

num = k;
den = [T 1];
P1  = tf(num,den,'InputDelay',L);
%% Plotting the result and computing the errors
figure()
hold on
step(P1, 1:900,'r')
plot(simout.resample([1:900]).Data)

data_new_0 = simout2.Data;
max_error0 = max(abs(data_new_0));

ise0 = sum(data_new_0(1:end/2).^2);
iae0 = sum(abs(data_new_0(1:end/2)));
%% 3-Parameter 1st order model using area methods - random input
zp = zeros(75,1);

resample_data1  = squeeze(simout4.resample([1:900]).Data);
final_response1 = [zp;resample_data1(1:825)];

figure()
hold on
plot(final_response1,'r')
plot(simout3.resample([1:900]).Data)

data_new_1 = final_response1 - simout5.resample([1:900]).Data;
max_error1 = max(abs(data_new_1));

ise1 = sum(data_new_1(1:end/2).^2);
iae1 = sum(abs(data_new_1(1:end/2)));
%% 3-Parameter 2nd order model using area methods - step input
signal  = simout8.Data;
data    = signal(end-200:end);

k       = mean(data);

integral_a0 = sum(k - signal) * 0.3;
t_ar        = integral_a0 / k;

integral_a1 = sum(signal(1:ceil(t_ar/0.3))) * 0.3;

T_second    = integral_a1 * exp(1)^2 / (4 * k);
L_second    = t_ar - 2 * T_second;

num_second  = k;
den_second  = [T_second^2 2*T_second 1];
P2          = tf(num_second,den_second,'InputDelay',190);
%% Plotting the result and computing the errors
data_new = simout3.Data;

max_error_second    = max(abs(data_new));
ise_second          = sum(data_new(1:end/2).^2);
iae_second          = sum(abs(data_new(1:end/2)));

figure()
hold on
step(P2, 1:900,'r')
plot(simout19.resample([1:900]).Data)
%% 3-Parameter 2nd order model using area methods - random input
resample_data   = squeeze(simout4.resample([1:900]).Data);
final_response  = [zp;resample_data(1:825)];

figure()
hold on
plot(final_response,'r')
plot(simout3.resample([1:900]).Data)

data_new_1  = final_response - simout5.resample([1:900]).Data;

max_error   = max(abs(data_new_1));
ise         = sum(data_new_1(1:end/2).^2);
iae         = sum(abs(data_new_1(1:end/2)));
%% 3-Parameter 1st order model using method of moments - step input
system_output = simout7.Data;
plot(simout7.resample([1:900]).Data)

k_moment    = sum(system_output) * 0.3 / 200;

time        = simout7.time;

t_integral  = sum(system_output.* time) * 0.3 / 200;
t_ar_moment = t_integral / k_moment;

t2_integral = sum(system_output.* (time.^2)) * 0.3 / 200;

T_moment    = (t2_integral / k_moment - t_ar_moment^2)^(1/2);
L_moment    = t_ar_moment - T_moment; 

num_moment1 = 40.1;
den_moment1 = [T_moment 1];
P3          = tf(num_moment1,den_moment1,'InputDelay',220);
%% Plotting the result and computing the errors
data_new    = simout10.Data;

max_error   = max(abs(data_new));
ise         = sum(data_new(1:end/2).^2);
iae         = sum(abs(data_new(1:end/2)));

figure()
hold on
step(P3, 1:900,'r')
plot(simout12.resample([1:900]).Data)
%% 3-Parameter 1st order model using method of moments - random input
zp              = zeros(80,1);
resample_data   = squeeze(simout9.resample([1:900]).Data);
final_response  = [zp;resample_data(1:820)];

figure()
hold on
plot(final_response,'r')
plot(simout8.resample([1:900]).Data)

data_new_1  = final_response - simout8.resample([1:900]).Data;

max_error   = max(abs(data_new_1));
ise         = sum(data_new_1(1:end/2).^2);
iae         = sum(abs(data_new_1(1:end/2)));
%% 3-Parameter 2nd order model using method of moments - step input
T_moment_2 = (t2_integral / (2*k_moment) - ((1/2)*t_ar_moment^2))^(1/2);
L_moment_2 = t_ar_moment - 2 * T_moment_2; 

num_moment2 = 40.1;
den_moment2 = [T_moment_2^2 2*T_moment_2 1];
P4 = tf(num_moment2,den_moment2,'InputDelay',180);
%% Plotting the result and computing the errors
data_new    = simout16.Data;

max_error   = max(abs(data_new));
ise         = sum(data_new(1:end/2).^2);
iae         = sum(abs(data_new(1:end/2)));

figure()
hold on
step(P4, 1:900,'r')
plot(simout15.resample([1:900]).Data)
%% 3-Parameter 2nd order model using method of moments - random input
zp              = zeros(50,1);
resample_data   = squeeze(simout14.resample([1:900]).Data);
final_response  = [zp;resample_data(1:850)];

figure()
hold on
plot(final_response,'r')
plot(simout13.resample([1:900]).Data)

data_new_1 = final_response - simout13.resample([1:900]).Data;

max_error   = max(abs(data_new_1));
ise         = sum(data_new_1(1:end/2).^2);
iae         = sum(abs(data_new_1(1:end/2)));
%% 4-Parameter 2nd order model using method of moments - step input
k_new = 40.1;

T_1 = 31.41;
T_2 = 69.56;

L_new = 198.70;

num_moment4 = k_new;
den_moment4 = [T_1*T_2 T_1+T_2 1];
P5          = tf(num_moment4,den_moment4,'InputDelay',L_new);
%% Plotting the result and computing the errors
data_new    = simout23.Data;

max_error   = max(abs(data_new));
ise         = sum(data_new(1:end/2).^2);
iae         = sum(abs(data_new(1:end/2)));

figure()
hold on
step(P5, 1:900,'r')
plot(simout22.resample([1:900]).Data)
%% 4-Parameter 2nd order model using method of moments - random input
zp              = zeros(58,1);
resample_data   = squeeze(simout21.resample([1:900]).Data);
final_response  = [zp;resample_data(1:842)];

figure()
hold on
plot(final_response,'r')
plot(simout20.resample([1:900]).Data)

data_new    = simout20.Data;

max_error   = max(abs(data_new));
ise         = sum(data_new(1:end/2).^2);
iae         = sum(abs(data_new(1:end/2)));
%%  Nichols 
nichols(P_second)
ngrid