namespace data{
  vector<double>  x, y, ex, ey;
}

double fun(const double *x,const double *par){
  return par[0]*(*x)+par[1];
}

void fcn(int &npar,double *gin,double &f,double *par,int iflag){
  f = 0.0;
  for (int i=0;i<data::x.size();i++){
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
  // TMinuit *minuit = new TMinuit(...); // numero di parametri  
  //  minuit->SetFCN(fcn);
  // minuit->DefineParameter(indice,"nome",valin,step,min,max);
  // per ogni indice inserisco nome, valore iniziale, step, minimo, massimo del parametro

  // Minimize
  //  minuit->Command("MIGRAD"); // Comando di minimizzazione

  // Get result
  // minuit->GetParameter(indice,val,eval);
  // per ogni indice estraggo il valore del parametro e del suo errore
  // minuit->GetParameter(indice,val,eval);

}
