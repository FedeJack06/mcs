%CORDA VIBRANTE
%parametri fisici e geometrici
v=1e-2;
t=0; tend=1e3;
%valori psi(x,t) a t=0
L=0.25;
N=100;
x=linspace(0.0,L,N);
dx=x(2)-x(1);
dt=1e-1;
vprimo=dx/dt;
psi=zeros(1,N);
psi_1=zeros(1,N); %per tempi successivi
psi_0=zeros(1,N); %per tempi precedenti

%da imporre la condizione iniziale, una gaussiana 
A=3;
k=5*pi/L;
psi=A*sin(x*k);

psi_1(2:N-1)=psi(2:N-1)+(v^2/vprimo^2)*(psi(3:N)+psi(1:N-2)-2*(psi(2:N-1)));
    
t=t+dt;  %faccio passare un istante di tempo
     
while t<tend %parte da t+dt
    plot(x,psi);
    axis([0 L -2*A 2*A]);

    psi_0(1:N)=psi(1:N);  %salvo i valori del tempo presente nel passato
    psi(1:N)=psi_1(1:N);  %salvo i valori del tempo superiore nel tempo presente
    psi_1(2:N-1)=2*psi(2:N-1)-psi_0(2:N-1)+(v^2/vprimo^2)*(psi(3:N)+psi(1:N-2)-2*(psi(2:N-1)));
        
    drawnow;
    t=t+dt;
end
      