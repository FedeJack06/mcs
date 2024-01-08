function 20 Poisson
n = 100;
V = zeros(n);
r = zeros(n-2); w=1.6; % Rilassamento 

V(:,1) = 10; V(:,n) = 10;
V(1,:) = -10; V(n,:) = -10;

rho = zeros(n);
rho(50:51,50:51) = 2;

r = 0.25 * (V(1:n-2,1:n-2) + V(1:n-2,3:n) + V(3:n, 1:n-2) + V(3:n, 3:n) + rho(2:n-1,2:n-1)) - V(2:n-1,2:n-1);

while max(max(r./V(2:n-1,2:n-1))) > 0.01
    figure(1);
    surfc(V);
    % Metodo 1 - Piu' semplice sfruttando al massimo le potenzialita' di
    % matlab ma non permette di applicare facilmente il metodo di
    % rilassamento che diverge gia' per w=1.005

    %r = 0.25 * (V(1:n-2,1:n-2) + V(1:n-2,3:n) + V(3:n, 1:n-2) + V(3:n, 3:n) + rho(2:n-1,2:n-1)) - V(2:n-1,2:n-1);
    %V(2:n-1,2:n-1) = V(2:n-1,2:n-1) + w*r;

    % Metodo 2 - Non sfrutta al massimo le potenzialita' di matlab per il 
    % calcolo matriciale ma sfrutta il metodo di rilassamento. Grazie a 
    % questo metodo la soluzione non diverge anche per w=1.5 e si arriva 
    % alla soluzione molto velocemente

    for i=2:n-1
        for j=2:n-1
            r(i-1,j-1) = 0.25 * (V(i-1,j-1) + V(i-1,j+1) + V(i+1, j-1) + V(i+1, j+1) + rho(i,j)) - V(i,j);
            V(i,j) = V(i,j) + w * r(i-1,j-1);
        end
    end
end
