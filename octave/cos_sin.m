frequency = 5;
timeperiod = 1/frequency;
amplitude = 1;
dcoffset = 0;

t=0:0.01:4*timeperiod;

out=dcoffset+amplitude*cos(2*pi*frequency*t);
out1=dcoffset+amplitude*sin(2*pi*frequency*t);

plot(t,out,t,out1)
grid on
xlabel('time')
ylabel('Amplitude')
title "cos (t)  & sin (t) for t = 0 4*timeperiod";
legend("cos(t)","sin(t)")
