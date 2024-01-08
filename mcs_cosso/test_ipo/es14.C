void es14(){

	double p = 0;

	for (int i = 0; i <= 30; i++){
		p += TMath::PoissonI(i,15);
	}
	cout << 1-p << endl;
	

	//La probabilita di ottenere 30 conteggi dato un valore di aspettazione di 15 (poisson) è 0.00020. Possimao quindi rigettare l ipotesi nulla, e cioe la distribuzione non è una poissoniana 
	int ns = 0;
	double prob = 0;
	double prob2 = 0;
	bool b1 = false;
	bool b2 = false;
	while(1){
		if(!b1)
		{
			for(int i = 0; i <= 30; i++)
			{
				prob += TMath::PoissonI(i,15 + ns);
				//cout << prob << endl;
			}
			if(prob < 0.025)
			{
				cout << "il valore superiore è:"  << ns-1 << endl;
				b1 = true;
				//break;
			}
		}
		if(!b2)
		{
			for(int i = 0; i < 30;i++) // qui c'è il minore stretto per convenzione penso
			{
				prob2 += TMath::PoissonI(i,15+ns);
			}

			cout << prob2 << endl;
			
			if(prob2 < 0.975)
			{
				cout << "Il valore inferiore è: " << ns-1 << endl;
				b2 = true;
			}
		}
		
		if (b1 && b2)
		{
			break;
		}
		
		ns++;
		prob = 0;
		prob2 = 0;
		cout << ns << endl;
	}

};
//il numero massimo di eventi in eccesso a quelli attesi cosi che la probabilita sia suff bassa da oss un mumero di eventi uguale o minore di quelli osservati
