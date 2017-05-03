figure
fid = fopen('orig-out.32t','r'); v = fread(fid, 256, 'float32'); fclose(fid);
t=1:256;
plot(t,v);

figure
y = abs(fft(v, 256));
y = fftshift(y);
f=-128:127;
plot(f, y);
