//**************//
//HANDS ON 2 E 3//
//**************//

//********************//
//HANDS ON 2: FIT CHI2//
//********************//

//*******************************************************************************************************************//
//PROGRAMMA 1: MACRO NAMED DI ROOT (file con stesso nome macro)                                                      //
//MINIMIZZAZIONE DELLA FUNZIONE FCN DI CHI2 A PARTIRE DA UNA FUNZIONE FUN LINEARE NEI PARAMETRI CON PACCHETTO TMinuit//
//*******************************************************************************************************************//
using namespace std;

//Namespace dei dati letti da file
namespace data{
  vector<double>  x, y, ex, ey;
}

//Funzione di fit lineare nei parametri: funzione TF1 da fittare come al primo anno 
double fun(const double *x,const double *par){
  return par[0]*(*x)+par[1];
}

//Funzione da minimizzare cin TMinuit: f e' chi2; classico chi2 da definizione con la funzione di TF1 specificata
void fcn(int &npar, double *gin, double &f, double *par, int iflag){ 
  f=0.0;
  for(int i = 0; i < data::x.size(); i++){
    f += pow((data::y[i]-fun(&data::x[i], par))/data::ey[i] , 2); 
  }
}

//----//
//Main//
//----//
void fitlin(){
  //Lettura file di dati e salvataggio nel namespace
  ifstream file("pendolo.dat");
  double x,y,ex,ey;
  while (file >> x >> y >> ex >> ey){
    data::x.push_back(x); data::y.push_back(y); data::ex.push_back(ex); data::ey.push_back(ey);
  }

  //Definizione del problema di minimizzazione
  TMinuit *minuit = new TMinuit(2); //si istanzia un oggetto di classe TMinuit e si dichiara il # di parametri che serviranno
  minuit->SetFCN(fcn); //istanziazione funzione da minimizzare
  minuit->DefineParameter(0, "a", 4.0, 0.01, 0., 0.); //# parametro, stringa nome parametro, valore iniziale parametro, ampiezza primo step variazione, max e min su cui far variare il primo parametro (0.,0. estremi variano ovunque)
  minuit->DefineParameter(1, "b", 0.0, 0.01, 0., 0.);

  //Comando di minimizzazione
  minuit->Command("MIGRAD");

  //Presa dei risultati
  double a,b,ea,eb; //salvataggio parametri forniti dall'oggetto di TMinuit, ovvero la miglior stima dei parametri in gioco
  minuit->GetParameter(0,a,ea);
  minuit->GetParameter(1,b,eb) ;
  cout << endl;
  cout << "a = " << a << "+/-" << ea << endl;
  cout << "b = " << b << "+/-" << eb << endl; 
}

//*****************************//
//HANDS ON 3: FIT DI LIKELIHOOD//
//*****************************//

//******************************************************************************************************************//
//PROGRAMMA 2: MACRO NAMED DI ROOT (file con stesso nome macro)                                                     //
//MINIMIZZAZIONE DELLA FUNZIONE DI -LOGL PER GENERICA PDF ED UTILIZZO DEL METODO GRAFICO MINOS CON PACCHETTO TMinuit//
//******************************************************************************************************************//
using namespace std;

//Namespace in cui salvare vector di dati
namespace data{ 
  vector<double>  x;
}

//Definizione della funzione di -log(Likelihood)
void logl(int &npar, double *gin, double &f, double *par, int iflag){ //funzione da minimizzare con minuit; attenzione: e' meno logl
  f = 0.0;
  // Definisco la logl: sommatoria termini una per evento
  for(int i=0; i<data::x.size(); i++){
    //ad ogni iterazione ad f somma la -log(Likelihood) del problema esponenziale in esame (va cambiata ogni volta!!)
    f +=  log(par[0])+data::x[i]/par[0];
  }
  
}

void fitexp(){
  //Lettura file di dati ed istanziazione istogramma 1D (allocazione dinamica)
  ifstream file("exp.dat");
  double x; 
  TH1D *h = new TH1D("h","",40,0,10); 
  while (file >> x){ 
    data::x.push_back(x); //variabile con stesso nome vettore in namespace, ma non in conflitto per namespace
    h->Fill(x);           //si riempe l'istogramma per rappresentare la distribuzione dei dati sperimentali
  }
  
  //Si istanzia oggetto di TMinuit  con un parametro per minimizzare logl
  TMinuit minuit(1); 
  minuit.SetFCN(logl); //si da' FCN da minimizzare 

  //Definizione dei parametri
  minuit.DefineParameter(0,"tau",2,0.01,0.,0.); //si da': numero e nome ai parametri, valore iniziale di prova, step iniziale di variazione e limiti

  //Si sfrutta METODO GRAFICO PER MAXIMUM LIKELIHOOD:
  minuit.SetErrorDef(0.5); //invece che variazione una unita' (chi2), 0.5 (-logL)
  minuit.Command("MINOS");
  //Presa parametri
  double tau, etau;
  minuit.GetParameter(0,tau,etau);

  h->SetMarkerStyle(20); //si usa il pallino per iesimo bin in modo da vedere bene dove passi la funzione di fit
  h->Draw("E");          //istogramma rappresentato con barre di errore

  //Definizione della pdf: tau e' [1], range funzione stesso dell'istogramma, [0] normalizzazione della funzione t.c. coerente con rappresentazione istogramma
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);
  // Disegno della funzione
  fe->SetParameter(1, tau);
  fe->SetParameter(0,h->GetEntries()*h->GetBinWidth(1));//normalizzazione: prodotto numero totale eventi in istogramma*larghezza bin (tutte uguali, si sceglie il primo)
  fe->Draw("SAME");//sovrappongo funzione ad istogramma
}


//*******************************************************************************************************************//
//PROGRAMMA 3: MACRO NAMED DI ROOT (file con stesso nome macro)                                                      //
//MINIMIZZAZIONE DELLA FUNZIONE DI -LOGL PER GENERICA PDF; FIT UNBINNED DI LIKELIHOOD CON UTILIZZO DELLA CLASSE TTree//
//*******************************************************************************************************************//
using namespace std;

void fitexpttree(){ 

  //Lettura dati da file ed istanziazione istogramma 1D (allocazione dinamica)
  ifstream file("exp.dat");
  double x; 
  TH1D *h = new TH1D("h","",40,0,10); 
  while (file >> x)
    h->Fill(x); //si riempe l'istogramma per rappresentare la distribuzione dei dati sperimentali

  //Si istanzia un oggetto di classe TTree
  TTree *t = new TTree();
  //Lettura riga per riga: in questo caso solo una variabile (t), dichiarata di tipo double (/D)
  t->ReadFile("exp.dat","t/D");

  //Definizione della pdf: tau e' [1], range funzione stesso dell'istogramma, [0] normalizzazione QUI FISSATO AD 1
  TF1 *fe = new TF1("fe","[0]*1/[1]*exp(-x/[1])",0,10);
  fe->FixParameter(0,1.);
  fe->SetParameter(1,2.);

  //Comando per UnbinnedFit con TF1 su oggetto di TTree
  t->UnbinnedFit("fe","t");
  
  h->SetMarkerStyle(20); //si usa il pallino per iesimo bin in modo da vedere bene dove passi la funzione di fit
  h->Draw("E");          //istogramma rappresentato con barre di errore
  
  // Disegno della funzione con normalizzazione ad AREA ISTOGRAMMA
  fe->SetParameter(0, h->GetEntries()*h->GetBinWidth(1)); 
  fe->Draw("SAME");
}

