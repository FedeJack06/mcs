{
  double m=15;
  double nobs=30;

  double prob=0;
  for(int i=0;i<nobs;i++){
    prob=prob+ TMath::PoissonI(i,m);
  }
  if(prob>0.95){
    cout<<"rigettiamo l'ipotesi, p-value: "<<prob<<endl;
  }

  double ns=0;
  while(true){
    prob=0;
    for(int i=0;i<nobs;i++){
      prob= prob + TMath::PoissonI(i,m+ns);
      if(prob<0.025){
	cout<<"upper limit al 95% "<<ns-1<<endl;
	break;
      }
    }
    ns++;
  }
  ns=0;
  while(true){
    prob=0;
    for(int i=0;i<nobs;i++){
      prob= prob + TMath::PoissonI(i,m+ns);
      if(1-prob>0.025){
	cout<<"lower limit al 95% "<<ns-1<<endl;
	break;
      }
    }
    ns++;
  }
}
