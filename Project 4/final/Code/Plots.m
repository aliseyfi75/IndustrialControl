%% part 8
figure()
hold on
plot(simout10,'r')
plot(simout11,'b')
plot(simout8,'g')
legend("M = 3", "M = 5", "M = 7");
%% part 7
figure()
hold on
plot(simout,'r')
plot(simout1,'b')
plot(simout2,'g')
legend("dead-band width = 0", "dead-band width = 1", "dead-band width = 2");
%% part 6
figure()
hold on
plot(simout,'r')
plot(simout1,'b')
plot(simout2,'g')
legend("set-point = -1", "set-point = 0", "set-point = 1");
%%
plot(d)
%%
figure()
hold on
plot(simout,'r')
plot(simout6,'b')
legend("typical output with hystersis h = 2", "output with dead-band width d = 2 (h=d)");

