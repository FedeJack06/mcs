#ifndef _POLIGONO
#define _POLIGONO

#include <iostream>
#include <TVector2.h>
#include <cmath>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>
#include <TApplication.h>

using namespace std;

class punto : public TVector2{

 public:
	
	using TVector2::TVector2;
	punto(const double& a=0, const double& b=0):TVector2(a,b){};

 private:

};


class poligono {

 public:
	poligono(const vector<punto>& punti):m_punti(punti){};
    poligono() : poligono(vector<punto> (0)){};

	virtual double area() = 0;
	double perimetro(){
		
		double per = 0;
		for(int i = 0; i<m_punti.size(); i++){
		  
			if(i == m_punti.size()-1)
			{
				TVector2 v;
				v = m_punti[m_punti.size()-1] - m_punti[0];
				per += v.Mod();
			}
			
			else
			{
				punto v1 = m_punti[i] ;
				punto v2 = m_punti[i+1];
				TVector2 v;
				v = v2-v1;
				per += v.Mod();
			}	
		}
		return per;
	};

	
	void Draw(){

		TApplication app("app",0,NULL);
		TGraph g;
		TCanvas c;
		for(int i = 0;i < m_punti.size(); i++){
			g.SetPoint(i,m_punti[i].X(),m_punti[i].Y());
		}

		c.Draw();
		c.cd();
		g.SetMarkerStyle(39);
		g.SetFillColor(kCyan-3);
		g.Draw("APF");
		app.Run(true);
	}

 protected:
	vector <punto> m_punti;

};




//*********************************************
//TRIANGOLOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO



class triangolo :public poligono{

 public:
	using poligono::poligono;

    triangolo(punto a, punto b, punto c):poligono(){ //lo creo come un poligono vuoto e poi aggiungo i punti successivamente 
		m_punti.push_back(a);
		m_punti.push_back(b);
		m_punti.push_back(c);
		
	};

    triangolo(double l1,double l2, double phi):poligono(){
		punto a;
		punto b;
		punto c;
		b.SetMagPhi(l1, 0);
		c.SetMagPhi(l2, (phi*TMath::Pi())/180);
		
		m_punti.push_back(a);
		m_punti.push_back(b);
		m_punti.push_back(c);
	};

	double area(){

		TVector2 v1 = m_punti[1]-m_punti[0];
		TVector2 v2 = m_punti[2]-m_punti[1];
		double area = abs(v1^v2)/2;
		return area;	   	
	}

	
 private:

};


#endif
