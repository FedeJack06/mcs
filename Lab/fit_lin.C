{
  ifstream infile("uv.dat");
  double v,ev,v_gen, eVgen;
  TGraphErrors gr;
  while(infile >> v >> ev >> v_gen >> eVgen){
    gr.SetPoint(gr.GetN(), v, v_gen/988);
    gr.SetPointError(gr.GetN(), ev, 0.002);
  }
  gr.Draw("AP");
}
