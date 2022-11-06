function x = compute(f, J, x_old)

% avoiding calculating index because that is a costlier algorithm
%     delta = inv(J) * -transpose(f);
%     x = delta + x_old;
delta = gaussianelimination(J, -transpose(f));
x = delta + x_old;

end