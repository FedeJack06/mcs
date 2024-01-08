v = 1e-02;

N=101;
L=0.5;
x = linspace(0,L,N);
dx = x(2)-x(1);
dt = 0.09;

eta = v^2/(dx/dt)^2;


psi0 = zeros(N,1);
psi1 = zeros(N,1);
psi2 = zeros(N,1);


sigma= 0.9;
t=0; q = 3;
tend = 1000*dt;
psi_0 = @(t) (1/sqrt(2*pi*sigma^2))*exp(-((t)^2/(2*sigma^2)));
psi0(1) = psi_0(t);
%psi0(2:N-1) = A * sin(x(2:N-1)*q*pi/L);

psi1(2:N-1) = psi0(2:N-1) + (eta/2) * (psi0(3:N)+psi0(1:N-2)-2*psi0(2:N-1));

t=t+dt;


  while t<tend

    
     psi1(1)=psi_0(t);

     plot (x,psi1);

     axis([0, L, -6*A, 6*A]); %% axis range for sine wave

     psi2(2:N-1) = 2*psi1(2:N-1) - psi0(2:N-1) + (eta)*(psi1(3:N)+psi1(1:N-2)-2*psi1(2:N-1));

     psi0 = psi1;
     psi1 = psi2;


     drawnow;
        
     t = t+dt;

  end




