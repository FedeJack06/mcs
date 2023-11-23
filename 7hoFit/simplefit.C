{
  TGraphErrors *gr = new TGraphErrors("pendolo.dat");
  TF1 *f = new TF1("f","[1]*x+[0]");
  f->SetParameter(0,4);
  f->SetParameter(1,0);
  gr->Draw("AP");
  // Correlation matrix
  auto ptr = gr->Fit("f","S");
  auto cov = ptr->GetCovarianceMatrix();
  cov.Print();
  auto cor = ptr->GetCorrelationMatrix();
  cor.Print();
  
  // Band
  gMinuit->SetErrorDef(1);
  auto grc = (TGraph*)gMinuit->Contour(10,0,1); //cast di tobject
  grc->Draw("AC");
  // Contour
}
