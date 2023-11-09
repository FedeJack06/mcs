function HeatLeftPeak_CN2
    % Parametri fisici
    eta = 0.30; L = 0.5; kappa = 10; 
    % Delta x, Delta t
    N = 101; x = linspace(0.0,L,N);
    dx = x(2)-x(1); dt = (eta*dx^2)/kappa; % Impulso di calore iniziale
    T0 = 20;
    DeltaT = 80;
    T = ones(N,1)*T0; T((N-1)/2+1) = T0+DeltaT;
    %matrice di crack nicolson
    X = ones(1,N-2);
    Y = ones(1,N-3);
    M = diag(X*(2/eta + 2)) + diag(Y*(-1),1) + diag(Y*(-1),-1);
    disp(size(M));
    t =0; 
    tend = 1000*dt;
    
    while t<tend
        plot(x,T);
        T(N) = T0;
        T(1) = T0;
        % ... (Cranck-Nicholson o inv. matrice) 
        V(1:N-2,1) = T(1:N-2) +(2/eta - 2)* T(2:N-1)+T(3:N);
        V(1,1) = V(1,1) + T(1);
        V(N-2,1)= V(N-2,1) +T(N);
        T(2:N-1)= M\V;
        drawnow;
        % limitrate;
        pause(0.0001);%cercare parametri per rendere meno lenta la visualizzazione pause(0.0001)
        t = t+dt; 
    end
    fteo = @(x)(T0+DeltaT*dx/sqrt(4*pi*kappa*t)*(exp(-(x-L/2).^2/(4*kappa*t))));
    hold on
    fplot(fteo,[0 L]);
    hold off

end