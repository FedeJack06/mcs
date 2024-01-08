%%CRANK-NICKOLSON

%% ci sono due metodi, uno in cui risolviamo il sistema direttamente dalla
%%matrice non semplificata, un altro in cui usiamo l equazione iterativa.
%%Il metodo con l equazione iterativa non funziona ma non riusciamo a
%%capire come mai 

function calore
%parametri
    
eta = 0.2;
L = 0.5;
kappa = 1;


%dimensioni degli inervalli

N = 101;
x = linspace(0.0,L,N);
dx = x(2) - x(1);
dt = (eta*dx^2)/kappa;

T0 = 20;
deltaT = 80;
T = T0 * ones(N,1);

t = N*dt;
a = -1; % =c
d = (2/eta+2);

%costruisco la matrice 

v1 = a * ones(1,N-3);
v2 = a * ones(1,N-3);
matrix = zeros(N-2,N-2) + d * eye(N-2,N-2) + diag(v1,1) + diag(v2,-1);


%vettori per il calcolo della soluzione con equazioni per la matrice
%gia semplificata
p = ones(N-2,1);
b = ones(N-2,1);
h = ones(N-2,1);



T(51) = T(51) + deltaT; %picco di altezza detaT al centro della sbarretta lunga L
tend = 1e-2;


while(t< tend)
    b(2:N-3) = T(2:N-3) + (2/eta -2)*T(3:N-2)+T(4:N-1);
    b(1) = T(1) + T0 + (2/eta -2) * T(2) + T(3);
    b(N-2) = T0 + T(N) + (2/eta -2) * T(N-1) + T(N-2);
    T_l = linsolve(matrix,b);
    T = [T0; T_l; T0]; %%modo furbo per appendere vettori
    plot(x,T,"g");
    drawnow;
    t = t + dt;
end


%{
QUESTO NON VA 

while(t < tend)
    h(1) = a/d;
    b(1) = T(1) + T0 + (2/eta -2) * T(2) + T(3);
    p(1) = b(1)/d;
    b(N-2) = T0 + T(N) + (2/eta -2) * T(N-1) + T(N-2);
    b(2:N-3) = T(2:N-3) + (2/eta -2)*T(3:N-2)+T(4:N-1);
    
    for i = 2:N-2
        h(i) = a/(d-a*h(i-1));
    end

    for i = 2:N-2
        p(i) = (b(i) + p(i-1)) / (d + h(i-1));
    end

    %l = length(T)
    T(N-1) = p(N-2);
   

    % non funzionaaaa mette T(N-2) = 23.3... sia a me che ad andre non
    % capisco percheeee
    for i = N-2:-1:2
        T(i) = p(i) - h(i) * T(i+1);
    end
   
    plot(x,T,"g");
    drawnow;
    t = t + dt;

end

%}

