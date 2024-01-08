function HeatLeftPeak_Explicit
  % Parametri fisici
  eta = 0.30;  L = 0.5; kappa = 10;
  % Delta x, Delta t
  N   = 101;  
  x   = linspace(0.0,L,N); %N elementi in x
  dx  = x(2)-x(1);
  dt  = (eta*dx^2)/kappa;
  % Impulso di calore iniziale
  T0           = 20;
  DeltaT       = 80;
  T            = ones(1,N)*T0; %N elementi in T corrispondenti alle x
  T(1)         = T0+DeltaT;
  % Evoluzione temporale
  t    = 0; tend = 1e-3;
  %Stampa su file
  %fileOUT = fopen('T(t).txt', 'w');
  while t<tend
    plot(x,T);
    %T(N)=T0; %gia impostato nella creazione di T, T(N) non viene mai cambiato
    
    %per aggiornare T(1)
    T_left = T(2);%condizione T'(x=0,t)=0  ==> creo l'informazione a T(x=-dx, t)
    T_1 = T(1) + eta*(T(2)+T_left-2*T(1));%evoluzione di T(1), successiva ala calcolo di T(2)
    T(1) = T_1;

    % Metodo esplicito - evoluzione T(t) a x fisso
    % riempo le righe dell griglia del dominio per ogni t+dt 
    T(2:N-1) = T(2:N-1) +eta*(T(3:N) + T(1:N-2) -2*T(2:N-1));
    
    % Salvataggio t e T (per un punto x_term della sbarra) e loro disegno
    %fprintf(fileOUT, '%f %f\n' , t, T(1)); %T(x=0,t)

    drawnow limitrate nocallbacks
    t = t+dt;
  end
  % Grafico T(x_term) vs t
end
%Propagazione del calore lungo una sbarra uni-dimensionale  con temperatura fissa all'estremo destro, 
%gradiente di temperatura nullo all'estremo sinistra (la sbarra è isolata), picco di temperatura all'estremo sinistro.
%Implementazione: metodo esplicito
%Grafico dell'evoluzione temporale di T(x)
%Grafico dell'andamento della temperatura in un punto fissato della sbarra (x0) al variare del tempo T(x0,t)
