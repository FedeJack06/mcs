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