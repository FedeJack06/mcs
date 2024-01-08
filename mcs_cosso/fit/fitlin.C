using namespace std;

namespace data{
    vector<double>  x, y, ex, ey;
}

double fun(const double *x,const double *par){
    return par[0]*(*x)+par[1];
}

void fcn(int &npar, double *gin, double &f, double *par, int iflag){
    f = 0.0;
    for(int i=0; i<data::x.size(); i++)
        f += pow( (data::y[i] - fun(&data::x[i], par) ) / data::ey[i], 2);

}

void fitlin(){
    ifstream file("pendolo.dat");
    double x,y,ex,ey;
    while (file >> x >> y >> ex >> ey){
        data::x.push_back(x); data::y.push_back(y); data::ex.push_back(ex); data::ey.push_back(ey);
    }

    // Define the minimization problem

    TMinuit * m1  = new TMinuit(2); //prende il numero di parametri 
    m1->SetFCN(fcn); //setto FCN
    m1->DefineParameter(0, "a", 4.0, 0.01, 0., 0.); // numero parametro,nome,valore,step iniziale per il processo di minimizzazione,limiti sup e inf, se uguali fa in automatico
    m1->DefineParameter(1, "b", 1.0, 0.01, 0., 0.);
	
    // Minimize
    m1->Command("MIGRAD");

	// Get result
    double a, b, e_a, e_b;
    m1->GetParameter(0, a, e_a);
    m1->GetParameter(1, b, e_b);

    cout << "a: " << a << " +- " << e_a << "\np_1: " << b << " +- " << e_b << endl;


	//potrebbe essere utile il metodo SetErrorDef() che prende un double e serve a usare le cose di maximum likelihood 
   

   

}
