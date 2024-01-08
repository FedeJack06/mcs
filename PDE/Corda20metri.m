%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%CORDA VIBRANTE SINUOSOIDALE ES ESAME
v = 1;
Vp=v+0.001;%condizione di stabilita`
N=200;
L=20;
x = linspace(0,L,N);
dx = x(2)-x(1);
t=0;
dt = dx/Vp;
tend = 1000*dt;
eta = (v/Vp)^2;
A=1;

psi0 = zeros(N,1);%spostamento al tempo precente
psi1 = zeros(N,1);%al tempo corrente
psi2 = zeros(N,1);%al tempo successivo

psi0(:,1) = A*sin(2*pi*(x/L));%fisso gli spostamenti della corda al tempo 0 (t-dt)
figure(1)%disegno la posizione iniziale della corda
plot(x,psi0)
%psi_0 = @(t) (1/sqrt(2*pi*sigma^2))*exp(-((t)^2/(2*sigma^2)));
%psi0(1) = psi_0(t);

psi1(2:N-1) = psi0(2:N-1) + (eta/2) * (psi0(3:N)+psi0(1:N-2)-2*psi0(2:N-1)); %calcolo lo spostamento al tempo t
t=t+dt;
figure(2)
while t<tend
    plot (x,psi1);
    axis([0, L, -A, A]); %% axis range for sine wave

    psi2(2:N-1) = 2*psi1(2:N-1) - psi0(2:N-1) + (eta)*(psi1(3:N)+psi1(1:N-2)-2*psi1(2:N-1));
    psi0 = psi1;
    psi1 = psi2;

    drawnow;
    t = t+dt;
end