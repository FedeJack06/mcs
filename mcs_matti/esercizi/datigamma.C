using namespace std;

namespace data{
  vector <double> x;
}

void fcn(int &npar,double *gin,double &f, double *par,int iflag){
  f= 0.;
  for(int i=0;i<data::x.size();i++){
    f += -(log(pow(data::x[i],2)/(2*pow(par[0],3)))-(data::x[i]/par[0]));
  }
}

void datigamma(){

  TH1D *h1= new TH1D("h","histo",25,0.,0.);
  
  ifstream ifile("DatiGamma.dat");
  double a;
  while(ifile>>a){
    data::x.push_back(a);
    h1->Fill(a);
  }

  h1->Draw();
  
  //cout<<"ciaooooo----------------------------------------------------"<<endl;
  TMinuit *minuit= new TMinuit(1);
  minuit->SetFCN(fcn);
  minuit->DefineParameter(0,"theta",5.74/3,3.555/3,0.,0.);

  minuit->Command("MINUIT");

  double theta, etheta;
  minuit->GetParameter(0,theta,etheta);
  cout<<"theta "<<theta<<" +/- "<<etheta<<endl;

  TF1 *g=new TF1("f","[1]*(pow(x,2)/(2*pow([0],3)))*exp(-x/[0])",0,30);

  g->SetParameter(0,theta);
  g->SetParameter(1,224);
  g->Draw("SAME");
  
}

