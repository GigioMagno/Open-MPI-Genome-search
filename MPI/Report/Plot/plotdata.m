close all
clear
clc

cores = linspace(1,16,16);
avg_time_non_par = 1.146073;
%%Inter regional light cluster
irlsdbm = [49.629875 42.998434 30.462038 23.466897 19.800454 17.300720 15.080037 13.585844 13.869829 13.968340 14.290254 13.832556 13.787440 14.090869 14.240706 13.409973]-avg_time_non_par;
irlrk2 = [22.066156 13.110638 10.371123 8.948081 7.875234 7.594555 6.284773 6.208380 6.972334 8.463014 8.250257 8.799516 9.274381 9.538829 10.116572 9.885908]-avg_time_non_par;
irlpolyHash = [556.796603 403.029739 268.802703 203.633617 163.844210 136.320769 120.130784 104.449918 93.408450 85.175652 78.909221 74.047223 69.619595 64.966710 61.957830 58.793937]-avg_time_non_par;
irlloselose = [40.075866 35.302908 26.229152 20.008691 16.803243 14.653683 12.940203 12.297652 11.760082 11.980763 12.983281 12.323431 13.426353 12.992023 12.787234 12.690743]-avg_time_non_par;
irldjb2 = [44.368386 39.136189 27.727903 21.422809 17.850036 15.657548 13.602116 12.658606 12.900814 12.891161 12.276707 13.521907 12.947180 13.078359 13.512525 12.386850]-avg_time_non_par;

figure(1)
plot(cores, irlsdbm, 'LineWidth', 2);
hold on
plot(cores, irlrk2, 'LineWidth', 2);
hold on
plot(cores, irlloselose, 'LineWidth', 2);
hold on
plot(cores, irldjb2, 'LineWidth', 2);
hold on
plot(cores, irlpolyHash, 'LineWidth', 2);
hold on
%[m, idx] = min(irldjb2);
%scatter(idx, m, 'black', 'filled', 'o');
%hold on
%[m, idx] = min(irlloselose);
%scatter(idx, m, 'black', 'filled', 'o');
%hold on
%[m, idx] = min(irlrk2);
%scatter(idx, m, 'black', 'filled', 'o');
%hold on
%[m, idx] = min(irlsdbm);
%scatter(idx, m, 'black', 'filled', 'o');

axis([1,16,0, max(irlpolyHash)])
ylabel('Time [seconds]');
xlabel('Number of CPUs');
legend({'sdbm', 'rolling hash', 'loselose', 'djb2', 'polyhash'},'Location','northeast');
title("Hash functions comparision with light cluster");



figure(2)
n_cores = linspace(1, 180, 180);
p = 0.96;
values = n_cores./(n_cores + p*(1-n_cores));

%plot(n_cores, values, 'LineWidth',2);
scatter(n_cores, values, '.')
axis([1,180 ,0, max(values)+5])
ylabel('Speedup');
xlabel('Number of CPUs');
title("Amdahl's law");
