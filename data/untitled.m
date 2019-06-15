x = 1:1000;
plot(x,1000*T1)
title('Comparison of key generation time for key size of 256 bits')
xlabel('Iteration')
ylabel('Time in ms')
hold on

plot(x,gendata)

hold off