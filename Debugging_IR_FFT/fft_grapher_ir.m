filename = 'fft_ir.xlsx';
binNumber = xlsread(filename,'A2:A129');
neither = xlsread(filename,'B2:B129');
both = xlsread(filename,'C2:C129');
hat = xlsread(filename,'D2:D129');
decoy = xlsread(filename,'E2:E129');
figure(1)
plot(binNumber, neither)
hold on
plot(binNumber, both)
hold on
plot(binNumber, hat)
hold on
plot(binNumber, decoy)
legend('Neither', 'Both', 'IR Hat', 'IR Decoy');
xlabel('Bin Number (1-based counting)');
