%%Histograms plot
lcsr = [103.55, 14.49, 12.35, 11.47, 6.34];
hf = categorical({'polyHash', 'sdbm', 'djb2', 'loselose', 'rolling hash'},{'polyHash', 'sdbm', 'djb2', 'loselose', 'rolling hash'});

figure(1)
b = bar(hf, lcsr);
b.FaceColor = 'flat';
b.CData(1,:)=[0.4660 0.6740 0.1880];
b.CData(2,:)=[0 0.4470 0.7410];
b.CData(3,:)=[0.4940 0.1840 0.5560];
b.CData(4,:)=[0.9290 0.6940 0.1250];
b.CData(5,:)=[0.8500 0.3250 0.0980];
hold on
xtips1 = b(1).XEndPoints;
ytips1 = b(1).YEndPoints;
labels1 = string(b(1).YData);
text(xtips1,ytips1,labels1,'HorizontalAlignment','center','VerticalAlignment','bottom')
ylabel('Time [seconds]');
xlabel('Hash function');
title("Light cluster (single region) [4 cores each 2vCPUs]");

lcmr = [113.19, 20.74, 19.58, 20.80, 14.64];
figure(2)
b = bar(hf, lcmr);
b.FaceColor = 'flat';
b.CData(1,:)=[0.4660 0.6740 0.1880];
b.CData(2,:)=[0 0.4470 0.7410];
b.CData(3,:)=[0.4940 0.1840 0.5560];
b.CData(4,:)=[0.9290 0.6940 0.1250];
b.CData(5,:)=[0.8500 0.3250 0.0980];
hold on
xtips1 = b(1).XEndPoints;
ytips1 = b(1).YEndPoints;
labels1 = string(b(1).YData);
text(xtips1,ytips1,labels1,'HorizontalAlignment','center','VerticalAlignment','bottom')
hold on
ylabel('Time [seconds]');
xlabel('Hash function');
title("Light cluster (multi region) [4 cores each 2vCPUs]");

lcmr_ = [58.79, 13.40, 12.38, 12.69, 9.88];
figure(3)
b = bar(hf, lcmr_);
b.FaceColor = 'flat';
b.CData(1,:)=[0.4660 0.6740 0.1880];
b.CData(2,:)=[0 0.4470 0.7410];
b.CData(3,:)=[0.4940 0.1840 0.5560];
b.CData(4,:)=[0.9290 0.6940 0.1250];
b.CData(5,:)=[0.8500 0.3250 0.0980];
hold on
xtips1 = b(1).XEndPoints;
ytips1 = b(1).YEndPoints;
labels1 = string(b(1).YData);
text(xtips1,ytips1,labels1,'HorizontalAlignment','center','VerticalAlignment','bottom')
hold on
ylabel('Time [seconds]');
xlabel('Hash function');
title("Light cluster (multiple region) [16 cores each 2vCPUs]");


figure(4)
fcsr = [22.56, 5.83, 5.38, 5.51, 1.89];
b = bar(hf, fcsr);
b.FaceColor = 'flat';
b.CData(1,:)=[0.4660 0.6740 0.1880];
b.CData(2,:)=[0 0.4470 0.7410];
b.CData(3,:)=[0.4940 0.1840 0.5560];
b.CData(4,:)=[0.9290 0.6940 0.1250];
b.CData(5,:)=[0.8500 0.3250 0.0980];
hold on
xtips1 = b(1).XEndPoints;
ytips1 = b(1).YEndPoints;
labels1 = string(b(1).YData);
text(xtips1,ytips1,labels1,'HorizontalAlignment','center','VerticalAlignment','bottom')
ylabel('Time [seconds]');
xlabel('Hash function');
title("Fat cluster (single region) [16 cores each 2vCPUs]");


figure(5)
weak_scalability = [2.22, 2.35, 2.55, 2.60];
coresize = categorical({'1 (250MB)', '2 (500MB)', '4 (1GB)', '8 (2GB)'});
b = bar(coresize, weak_scalability);
hold on
xtips1 = b(1).XEndPoints;
ytips1 = b(1).YEndPoints;
labels1 = string(b(1).YData);
text(xtips1,ytips1,labels1,'HorizontalAlignment','center','VerticalAlignment','bottom')
ylabel("Time [seconds]")
xlabel('Cores (size)')
title("Weak scalability")

figure(6)
strong_scalability = [8.81, 4.69, 2.43, 1.29]
coresize = categorical({'1 (1GB)', '2 (1GB)', '4 (1GB)', '8 (1GB)'});
b = bar(coresize, strong_scalability);
hold on
xtips1 = b(1).XEndPoints;
ytips1 = b(1).YEndPoints;
labels1 = string(b(1).YData);
text(xtips1,ytips1,labels1,'HorizontalAlignment','center','VerticalAlignment','bottom')
ylabel("Time [seconds]")
xlabel('Cores (size)')
title("Strong scalability")