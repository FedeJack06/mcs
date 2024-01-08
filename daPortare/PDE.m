%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%CORDA VIBRANTE SINUOSOIDALE ES6 ESAME
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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% SOL EQ DI POISSON
function poisson_potenziale
%% Problema di poisson
%data la carica matrice charge, calcolo il potenziale
M = 100;%scatola 2D quadrata lato 100
e_0 = 8.854187e-12; %costante epsilon zero
q = 0.0001; %valore della carica

V = zeros(M,M); %Matrice del potenziale
charge = zeros(M,M); %Matrice della carica nella scatola, iniziale a 0
% IN GENERALE DA CAMBIARE SOLO LA DISTRIBUZIONE DI CARICA.

%% CONDENSATORE
%charge(30,20:80) = -q; %carica sulla 30-esima riga 
%charge(70,20:80) = q; %carica sulla 70-esima riga


%% DIPOLO ELETTRICO
charge(38,50) = q;
charge(62,50) = -q;

%% ESERCIZIO 11 RACCOLTA ESAME: CARICA AL CENTRO DELLA GRIGLIA 
%charge(50,50) = q;

%CRITERIO DI CONVERGENZA
epsilon = 0.001; %errore (assoluto = relativo)
max_deltaMatrice = epsilon; %valore massimo della matrice delta
maxV = 0; %per la componente di errore relativo di "delta"
delta_matrice = zeros(M,M); %(preallocazione per efficienza)

figure(1)
while(max_deltaMatrice >= epsilon + epsilon * maxV)%condizione di convergenza
    %massimo della matrice V
    maxV = max(max(V));%max(matrice) è vettore contenente il max per ogni colonna

    i = 2:M-1; 
    j = 2:M-1;
    Vn = V(i,j); %V al passo precedente
    V(i,j) = 0.25*(V(i+1,j)+V(i-1,j)+V(i,j+1)+V(i,j-1))+ 1/(4*e_0)*charge(i,j);%calcolo con Gauss-Seidel
    %sarebbe: V(2:M-1, 2:M-1) = 0.25*(V(3:M, 2:M-1) +V(1:M-2, 2:M-1) +V(2:M-1, 3:M) +V(2:M-1, 1:M-2)) +1/(4*e_0)*charge(2:M-1, 2:M-1); 
    delta_matrice(i,j) = abs(V(i,j)-Vn);  %differenza fra passo precente e successivo

    max_deltaMatrice = max(max(delta_matrice));
    %figure(f1);
    surfc(V);
    drawnow;
end
[Ex, Ey] = gradient(V);
figure(2)
quiver(linspace(1,M),linspace(1,M),Ex,Ey);
%plot(linspace(1,M), -Ex(:,50));

%% Problema di laplace
% fissato il potenziale sulle armature calcolo il potenziale negli altri punti del piano
% per farlo andare commentare solo il ciclo while qui precedente
%{
v = 100;
potential = zeros(M,M);
potential(30,20:80) = -v;
potential(70,20:80) = v;

f1 = figure;

while(max_deltaMatrice >= epsilon + epsilon * maxV)
    maxV = max(max(potential));
    for i = 2:M-1    
        for j = 2:M-1
            if(i == 30 && j >= 20 && j <= 80 || i == 70 && j >= 20 && j <= 80)
                continue;
            end

            vn = potential(i,j);
            potential(i,j) = 0.25*(potential(i+1,j)+potential(i-1,j)+potential(i,j+1)+potential(i,j-1));
            delta_matrice(i,j) = abs(potential(i,j)-vn);
        end
    end
    
    max_deltaMatrice = max(max(delta_matrice));
    figure(f1);
    surfc(potential);
    drawnow;

end
%}

%{
[Ex, Ey] = - gradient(potential);
E_inside = E(50,50)
drawnow;
%}



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%% CALORE AL BORDO - METODO ESPLICITO (hands on)
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


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%CALORE AL CENTRO - METODO CRANK NICOLSON (hans on)
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
