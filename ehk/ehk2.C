namespace data{
  const double m_e = 1.608, s_e = 0.020, m_hk = 3.27, s_hk = 0.04, m_ek = 1.1440, s_ek = 0.0040;
  const double m_eh[2] = {0.201, 0.252};
  const double s_eh[2] = {0.006, 0.010};
}

void fcn(int& npar, double *deriv, double& f, double p[], int flag){
  f = 0.0;
  for (unsigned int i=0; i<2; i++)
    {
      f += pow((data::m_e - p[0])/data::s_e, 2);
      f += pow((data::m_hk - p[1]/p[2])/data::s_hk, 2);
      f += pow((data::m_ek - p[0]/p[2])/data::s_ek, 2);
      f += pow((data::m_eh[i] - p[0]/p[1])/data::s_eh[i], 2);
    }
}

void ehk2(){

  auto *m = new TMinuit(3);
  m->SetFCN(fcn);
  m->SetErrorDef(1);

  double p[3] = {1.5, 6.2, 1.2};
  double sS[3] = {0.01, 0.01, 0.01};
  double mv[3] = {1, 4, 1};
  double Mv[3] = {2, 7, 2};
  string nmp[3] = {"e", "h", "k"};

  for (int i=0; i<3; i++)
    m->DefineParameter(i, nmp[i].c_str(), p[i], sS[i], mv[i], Mv[i]);

  m->Command("MIGRAD");
  m->Command("HESSE");

  auto *eh = (TGraph*)m->Contour(100, 0, 1);
  eh->Draw("AL");
    
  return;
}
