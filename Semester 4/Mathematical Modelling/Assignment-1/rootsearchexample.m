clc
clear all

func = @(x)(x ^ 3 - 10 * x ^ 2 + 5);
dfunc = @(x)(3 * x ^ 2 - 20 * x);
ddfunc = @(x)(6 * x - 20);

a = - 1; b = 2; dx = 0.01;
[x1, x2, num_itr_i, convergence_i] = incremental(func, a, b, dx);

x1 = - 1; x2 = 0;
[root, num_itr_b, convergence_b] = bisect(func, x1, x2);

x_0 = -1; 
[root, num_itr_n, convergence_n] = newtonraphson(func, dfunc, x_0);

x_0 = - 1;
x_1 = 2;
[root, num_itr_s, convergence_s] = secant(func, x_1, x_0);

x_0 = -1;
[root, num_itr_m, convergence_m] = modifiednewtonraphson(func, dfunc, ddfunc, x_0);



figure
% the plot doesn't include incremental search's errors because it just
% tries values over an interval and two consecutive iterations have nothing
% to do with each other
plot((1:1:num_itr_b), convergence_b, (1:1:num_itr_n), convergence_n, (1:1:num_itr_s), convergence_s, (1:1:num_itr_m), convergence_m)
hold on
grid on