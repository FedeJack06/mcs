function HeatLeftPeak_Explicit2
    % Parametri fisici
    eta = 0.3; L = 0.5; kappa = 10; % Delta x, Delta t
    N = 101; x = linspace(0.0,L,N);
    dx = x(2)-x(1); 
    dt = (eta*dx^2)/kappa; % Impulso di calore iniziale
    T0     = 20; DeltaT = 80;
    T      = ones(N,1)*T0;
    T(1:2) = T(1:2) + DeltaT;
    % Evoluzione
    t = 0; tend = 1e-3; 
    k = 0;
    %Vettori per stampa T(t) a x fissato 
    T_x_fix = [];
    t_var = [];
    %Stampa su file
    fileID = fopen('T(t).txt', 'w');
    while t<tend
       plot(x,T);
       T(N)   = T0;
       T_left = T(2);
       pippo = T(1)+eta*(T(2)+T_left-2*T(1));
       % Metodo esplicito
       T(2:N-1)=T(2:N-1)+eta*(T(3:N)+T(1:N-2)-2*T(2:N-1));
       % Salvataggio t e T (per un punto della sbarra) e loro disegno
       drawnow; % cercare parametri per rendere piu' o meno lenta la visualizzazione
       t_var(end+1)=t;
       T_x_fix(end+1)=T(50);%con T(50) valore di T a ~meta' sbarra
       T(1)=pippo;
       t = t+dt;
    end
    
    hold off;
    figure;
    plot(t_var,T_x_fix);
    drawnow;
    hold off;
    
    for i=1:10:length(t_var)
     fprintf(fileID, '%f %f\n',t_var(i),T_x_fix(i));
    end
    fclose(fileID);
   
end
