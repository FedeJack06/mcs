{
  auto c = new TCanvas ("c","", 1000, 1000 ,1000 ,1000);
  auto gr = new TGraph2D();
  gr->SetMarkerStyle(20);
  gr->Draw("P");
  
  for(int i=0; i<30; i++){
    gr->SetMargin(0);
    gr->SetPoint(gr->GetN(), i+1, i-1, 1);
    gPad->Modified();
    gPad->Update();
    //gSystem->ProcessEvents();
  }
  
  gr->Print();
}
