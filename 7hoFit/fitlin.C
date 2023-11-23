namespace data{
  vector<double>  x, y, ex, ey;
}

double fun(const double *x,const double *par){
  return par[1]*(*x)+par[0];
}

void fcn(int &npar,double *gin,double &f,double *par,int iflag){
  f = 0.0;
  for (int i=0;i<data::x.size();i++){
    f += pow(data::y[i]-fun(&data::x[i],par),2)/(pow(data::ey[i],2) + pow(par[1]*data::ex[i],2));
    // Calcolo del Chi2
  }
}

void fitlin(){
  ifstream file("pendolo.dat");
  double x,y,ex,ey;
  while (file >> x >> y >> ex >> ey){
    data::x.push_back(x); data::y.push_back(y); data::ex.push_back(ex); data::ey.push_back(ey);
  }

  // Define the minimization problem
  TMinuit *minuit = new TMinuit(2); // numero di parametri  
  minuit->SetFCN(fcn);
  //minuit->SetErrorDef(1.0);
  minuit->DefineParameter(0,"beta_0",0,0.01,0.0,0.0);
  minuit->DefineParameter(1,"beta_1",4,0.01,0.0,0.0);
  // per ogni indice inserisco nome, valore iniziale, step, minimo, massimo del parametro

  // Minimize
  minuit->Command("MIGRAD"); // Comando di minimizzazione //HESSE calcolo preciso matrice di covarianza
  //MINOS calcolo erorrori asim
  //trova solo il minimo, e i parametri, non disegna
  double beta0, beta1, ebeta0, ebeta1;

  // Get result
  minuit->GetParameter(0,beta0,ebeta0);
  minuit->GetParameter(1,beta1,ebeta1);
  // per ogni indice estraggo il valore del parametro e del suo errore
  // minuit->GetParameter(indice,val,eval);

}
