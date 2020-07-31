sys = tf([1.6],[1 2 1 0]);

nyquist(sys);

%% 

sys2 = tf([1.6], [1,1,0]);

nyquist(sys2)

%% 

k = 1.6;
M = 5;
a = 5;

syms A w

eq1 = w^2 - (2*k*M/(pi*A^2))*sqrt(A^2-a^2);
eq2 = w-w^3-4*M*a*k/(pi*A^2);
sol = solve(eq1,eq2);  

A   = double(sol.A);
w  = double(sol.w);

%%


k = 1.6;
M = 5;
a = 5;

syms A2 w2

eq3 = w2^2 - (4*k*M/(pi*A2^2))*sqrt(A2^2-a^2);
eq4 = w2-4*M*a*k/(pi*A2^2);
sol = solve(eq3,eq4);  

A2   = double(sol.A2);
w2  = double(sol.w2);
