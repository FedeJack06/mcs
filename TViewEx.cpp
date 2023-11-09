{
   cV3D = new TCanvas("cV3D","PolyLine3D & PolyMarker3D Window",200,10,500,500);
 
   // Creating a view
   TView3D *view = (TView3D*) TView::CreateView(1);
   view->SetRange(0,0,0,25,25,25);
   view->ShowAxis();
 
   // Create a first PolyLine3D
   //   TPolyMarker3D *pm3d1 = new TPolyMarker3D;
   // Add points
   TGraph2D *pm3d1 = new TGraph2D;
   pm3d1->SetPoint(0, 0, 0, 0);
   pm3d1->SetMarkerSize(0.5);
   pm3d1->SetMarkerColor(4);
   pm3d1->SetMarkerStyle(20);
   pm3d1->Draw("P");
   for (int i=1;i<10;i++){
     pm3d1->SetPoint(0, i, i, i);
     gPad->Modified();gPad->Update();
     gSystem->ProcessEvents();
   }
   
}
