%%metodo di gauss-seidel

function condensatore

%QUESTE 3 COSE SONO PER IL CRITERIO DI CONVERGENZA
delta = 100000; %variabile per criterio di convergenza 
epsilon = 0.001; %errore 
maxV_new = 1000000; %per la componente di errore relativo di "delta"

M = 100;
delta_mat = zeros(M,M); %anche quest aper il criterio di convergenza


%% Problema di poisson
%data la carica matrice charge, calcolo il potenziale 



e_0 = 8.854187e-12; %costante epsilon zero
V_new = zeros(M,M); 

q = 0.0001; %valore della carica
charge = zeros(M,M);

%{
%% CONDENSATORE
charge(30,20:80) = -q; %carica sulla 30-esima riga 
charge(70,20:80) = q; %carica sulla 70-esima riga
%}

%{ 
% IN GENERALE DA CAMBIARE SOLO LA DISTRIBUZIONE DI CARICA.
%% DIPOLO ELETTRICO
charge(38,50) = q;
charge(62,50) = -q;
%}


%% ESERCIZIO 11 RACCOLTA ESAME: CARICA AL CENTRO DELLA GRIGLIA 
charge(50,50) = q;


while(delta >= epsilon + epsilon * maxV_new)
    maxV_new = max(max(V_new));

    for i = 2:M-1 
        for j = 2:M-1

            vn = V_new(i,j);
            V_new(i,j) = 0.25*(V_new(i+1,j)+V_new(i-1,j)+V_new(i,j+1)+V_new(i,j-1))+ 1/(4*e_0)*charge(i,j);
            delta_mat(i,j) = abs(V_new(i,j)-vn);

        end
    end
    
    delta = max(max(delta_mat));
    %figure(f1);
    surfc(V_new);
    drawnow;
end



%% Problema di laplace
% fissato il potenziale sulle armature calcolo il potenziale negli altri punti del piano
% per farlo andare commentare solo il ciclo while qui precedente

%{

v = 100;
potential = zeros(M,M);
potential(30,20:80) = -v;
potential(70,20:80) = v;

f1 = figure;

while(delta >= epsilon + epsilon * maxV_new)
    maxV_new = max(max(potential));
    for i = 2:M-1    
        for j = 2:M-1
            if(i == 30 && j >= 20 && j <= 80 || i == 70 && j >= 20 && j <= 80)
                continue;
            end

            vn = potential(i,j);
            potential(i,j) = 0.25*(potential(i+1,j)+potential(i-1,j)+potential(i,j+1)+potential(i,j-1));
            delta_mat(i,j) = abs(potential(i,j)-vn);
        end
    end
    
    delta = max(max(delta_mat));
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






