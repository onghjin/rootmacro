//   On a terminal, create symbolic link to the root file for the calibrated data which you want to check:      
//      $ rm calFile.root     (if file exists)
//      $ ln -s filename calFile.root
//   
//   In a ROOT session, you can do:
//      Root > .L chkcaldata.C
//      Root > chkcaldata t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

#define chkcaldata_cxx
#include "chkcaldata.hh"
#include <TROOT.h>
#include <fstream>
#include <Riostream.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>

//using namespace std;

void chkcaldata::histo()
{
  char hMWDCnameX[20],hMWDCnameY[20];
  char hMWDCnameA[20],hMWDCnameB[20];
  char hMWDCnameXA[20],hMWDCnameYB[20];
  char hMWDCnamefocXA[20];
  char hMWDCnameXY[20],hMWDCnameAB[20];
  char hSCI41LnameQ[20],hSCI41LnameT[20];
  char hSCI41RnameQ[20],hSCI41RnameT[20];
  char hSCI41nameQave[20],hSCI41nameTave[20];
  char hTOF41LnameQ[20],hTOF41LnameT[20];
  char hTOF41RnameQ[20],hTOF41RnameT[20];
  char hTOF41nameQave[20],hTOF41nameTave[20];
  char hTOF42LnameQ[20],hTOF42LnameT[20];
  char hTOF42RnameQ[20],hTOF42RnameT[20];
  char hTOF42nameQave[20],hTOF42nameTave[20];
  char hTOF43LnameQ[20],hTOF43LnameT[20];
  char hTOF43RnameQ[20],hTOF43RnameT[20];
  char hTOF43nameQave[20],hTOF43nameTave[20];
  char hTOF1name[20],hTOF2name[20];
  char hTOFname[20];
  char hTOF1dEname[20],hTOF2dEname[20];
  char hTOFdEname[20];
  char hTOF1xfocname[20];
  
  sprintf(hMWDCnameX,"hMWDCx");
  hMWDC_X = new TH1F (hMWDCnameX,hMWDCnameX,400,-150,150);
  sprintf(hMWDCnameY,"hMWDCy");
  hMWDC_Y = new TH1F (hMWDCnameY,hMWDCnameY,400,-50,50);
  sprintf(hMWDCnameA,"hMWDCa");
  hMWDC_A = new TH1F (hMWDCnameA,hMWDCnameA,400,-20,20);
  sprintf(hMWDCnameB,"hMWDCb");
  hMWDC_B = new TH1F (hMWDCnameB,hMWDCnameB,400,-20,20);
  sprintf(hMWDCnameXY,"hMWDCxy");
  hMWDC_XY = new TH2F (hMWDCnameXY,hMWDCnameXY,400,-200,200,400,-50,50);
  sprintf(hMWDCnameXA,"hMWDCxa");
  hMWDC_XA = new TH2F (hMWDCnameXA,hMWDCnameXA,400,-200,200,400,-20,20);
  sprintf(hMWDCnamefocXA,"hMWDCfocxa");
  hMWDC_focXA = new TH2F (hMWDCnamefocXA,hMWDCnamefocXA,400,-200,200,400,-20,20);
  sprintf(hMWDCnameYB,"hMWDCyb");
  hMWDC_YB = new TH2F (hMWDCnameYB,hMWDCnameYB,400,-50,50,400,-20,20);
  sprintf(hMWDCnameAB,"hMWDCab");
  hMWDC_AB = new TH2F (hMWDCnameAB,hMWDCnameAB,400,-20,20,400,-20,20);
  
  sprintf(hSCI41LnameQ,"hSci41LQ");
  hSci41L_Q = new TH1F (hSCI41LnameQ,hSCI41LnameQ,400,0,4000);
  sprintf(hSCI41RnameQ,"hSci41RQ");
  hSci41R_Q = new TH1F (hSCI41RnameQ,hSCI41RnameQ,400,0,4000);
  sprintf(hSCI41nameQave,"hSci41Qave");
  hSci41_Qave = new TH1F (hSCI41nameQave,hSCI41nameQave,400,0,1000);
  sprintf(hSCI41LnameT,"hSci41LT");
  hSci41L_T = new TH1F (hSCI41LnameT,hSCI41LnameT,400,0,40000);
  sprintf(hSCI41RnameT,"hSci41RT");
  hSci41R_T = new TH1F (hSCI41RnameT,hSCI41RnameT,400,0,40000);
  sprintf(hSCI41nameTave,"hSci41Tave");
  hSci41_Tave = new TH1F (hSCI41nameTave,hSCI41nameTave,400,0,40000);

  sprintf(hTOF41LnameT,"hTOF41LT");
  hTOF41L_T = new TH1F (hTOF41LnameT,hTOF41LnameT,400,0,40000);
  sprintf(hTOF41RnameT,"hTOF41RT");
  hTOF41R_T = new TH1F (hTOF41RnameT,hTOF41RnameT,400,0,40000);
  sprintf(hTOF41nameTave,"hTOF41Tave");
  hTOF41_Tave = new TH1F (hTOF41nameTave,hTOF41nameTave,400,0,40000);

  sprintf(hTOF42LnameT,"hTOF42LT");
  hTOF42L_T = new TH1F (hTOF42LnameT,hTOF42LnameT,400,0,40000);
  sprintf(hTOF42RnameT,"hTOF42RT");
  hTOF42R_T = new TH1F (hTOF42RnameT,hTOF42RnameT,400,0,40000);
  sprintf(hTOF42nameTave,"hTOF42Tave");
  hTOF42_Tave = new TH1F (hTOF42nameTave,hTOF42nameTave,400,0,40000);

  sprintf(hTOF43LnameT,"hTOF43LT");
  hTOF43L_T = new TH1F (hTOF43LnameT,hTOF43LnameT,400,0,40000);
  sprintf(hTOF43RnameT,"hTOF43RT");
  hTOF43R_T = new TH1F (hTOF43RnameT,hTOF43RnameT,400,0,40000);
  sprintf(hTOF43nameTave,"hTOF43Tave");
  hTOF43_Tave = new TH1F (hTOF43nameTave,hTOF43nameTave,400,0,40000);
  
  sprintf(hTOF1name,"hTOF41");
  hTOF1 = new TH1F (hTOF1name,hTOF1name,500,-5000,5000);
  sprintf(hTOF2name,"hTOF42");
  hTOF2 = new TH1F (hTOF2name,hTOF2name,500,-5000,5000);
  sprintf(hTOFname,"hTOF412");
  hTOF = new TH1F (hTOFname,hTOFname,500,-5000,5000);

  sprintf(hTOF1dEname,"hTOF41dE");
  hTOF1dE = new TH2F (hTOF1dEname,hTOF1dEname,500,-5000,5000,400,0,800);
  sprintf(hTOF2dEname,"hTOF42dE");
  hTOF2dE = new TH2F (hTOF2dEname,hTOF2dEname,500,-5000,5000,400,0,4000);
  sprintf(hTOFdEname,"hTOF412dE");
  hTOFdE = new TH2F (hTOFdEname,hTOFdEname,500,-5000,5000,400,0,4000);
  sprintf(hTOF1xfocname,"hTOF41xfoc");
  hTOF1xfoc = new TH2F (hTOF1xfocname,hTOF1xfocname,500,-150,150,400,0,4000);
    
}

void chkcaldata::Loop()
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Float_t  tTOF1,tTOF2,tTOF3,TOF;
   Float_t  qSci;
   Bool_t   TOF2flag,TOF3flag;
   
   tTOF1 = -999999.;
   tTOF2 = -999999.;
   tTOF3 = -999999.;
   TOF = -999999.;
   qSci  = -999999.;
   TOF2flag = false;
   TOF3flag = false;

   histo();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);

      if (ientry < 0) break;
      //      if (5000 < ientry < 0) break;
      //      nb = fChain->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_mwdc_x->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_mwdc_y->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_mwdc_a->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_mwdc_b->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_sc41_x->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_sc41_y->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_sc41_a->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_sc41_b->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_s4foc_x->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_s4foc_y->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_s4foc_a->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_s4foc_b->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_sci_qdc->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_sci_tdc->GetEntry(jentry);   nbytes += nb;
      nb = b_FRSCalibrEvent_sci_t0_tdc->GetEntry(jentry);   nbytes += nb;

      // if (Cut(ientry) < 0) continue;
      
      //      if (ientry>50000) break;
      //      if (ientry>5000) break;

      hMWDC_X.Fill(FRSCalibrEvent_mwdc_x);
      hMWDC_Y.Fill(FRSCalibrEvent_mwdc_y);
      hMWDC_A.Fill(FRSCalibrEvent_mwdc_a*1000);
      hMWDC_B.Fill(FRSCalibrEvent_mwdc_b*1000);
      
      hMWDC_XA.Fill(FRSCalibrEvent_mwdc_x,FRSCalibrEvent_mwdc_a*1000);
      hMWDC_YB.Fill(FRSCalibrEvent_mwdc_y,FRSCalibrEvent_mwdc_b*1000);
      hMWDC_XY.Fill(FRSCalibrEvent_mwdc_x,FRSCalibrEvent_mwdc_y);
      hMWDC_AB.Fill(FRSCalibrEvent_mwdc_a*1000,FRSCalibrEvent_mwdc_b*1000);      

      hMWDC_focXA.Fill(FRSCalibrEvent_s4foc_x,FRSCalibrEvent_s4foc_a*1000);

      if(FRSCalibrEvent_sci_qdc[4][0]>100. && FRSCalibrEvent_sci_qdc[4][1]>100.){
	qSci = sqrt((FRSCalibrEvent_sci_qdc[4][0]-1120.)*(FRSCalibrEvent_sci_qdc[4][1]-1230.));
	hSci41L_Q.Fill(FRSCalibrEvent_sci_qdc[4][0]);
	hSci41R_Q.Fill(FRSCalibrEvent_sci_qdc[4][1]);      
      }

      if(FRSCalibrEvent_sci_tdc[4][0]>-999.)
	hSci41L_T.Fill(FRSCalibrEvent_sci_tdc[4][0]);
      if(FRSCalibrEvent_sci_tdc[4][1]>-999.)
	hSci41R_T.Fill(FRSCalibrEvent_sci_tdc[4][1]);
      
      if(FRSCalibrEvent_sci_tdc[6][0]>-999. && FRSCalibrEvent_sci_tdc[6][1]>-999.)
	tTOF1 = 0.5*(FRSCalibrEvent_sci_tdc[6][0]+FRSCalibrEvent_sci_tdc[6][1]);
      if(FRSCalibrEvent_sci_tdc[7][0]>-999. && FRSCalibrEvent_sci_tdc[7][1]>-999.){
	tTOF2 = 0.5*(FRSCalibrEvent_sci_tdc[7][0]+FRSCalibrEvent_sci_tdc[7][1]);
	TOF2flag = true;
      }
      if(FRSCalibrEvent_sci_tdc[8][0]>-999. && FRSCalibrEvent_sci_tdc[8][1]>-999.){
	tTOF3 = 0.5*(FRSCalibrEvent_sci_tdc[8][0]+FRSCalibrEvent_sci_tdc[8][1]);
	TOF3flag = true;
      }

      //      cout << TOF2flag << "" << TOF3flag << endl;
      
      if(TOF2flag==1)TOF = tTOF2-tTOF1;
      if(TOF3flag==1)TOF = tTOF3-tTOF1;

      //      cout << "TOF: " << TOF << endl;
      
      hSci41_Tave.Fill(0.5*(FRSCalibrEvent_sci_t0_tdc[4][0]+FRSCalibrEvent_sci_t0_tdc[4][1]));      
      
      hTOF41L_T.Fill(FRSCalibrEvent_sci_tdc[6][0]);
      hTOF41R_T.Fill(FRSCalibrEvent_sci_tdc[6][1]);
      hTOF41_Tave.Fill(0.5*(FRSCalibrEvent_sci_t0_tdc[6][0]+FRSCalibrEvent_sci_t0_tdc[6][1]));
      hTOF42L_T.Fill(FRSCalibrEvent_sci_tdc[7][0]);
      hTOF42R_T.Fill(FRSCalibrEvent_sci_tdc[7][1]);
      hTOF42_Tave.Fill(0.5*(FRSCalibrEvent_sci_t0_tdc[7][0]+FRSCalibrEvent_sci_t0_tdc[7][1]));
      hTOF43L_T.Fill(FRSCalibrEvent_sci_tdc[8][0]);
      hTOF43R_T.Fill(FRSCalibrEvent_sci_tdc[8][1]);
      hTOF43_Tave.Fill(0.5*(FRSCalibrEvent_sci_t0_tdc[8][0]+FRSCalibrEvent_sci_t0_tdc[8][1]));

      if(FRSCalibrEvent_mwdc_x>-150. && FRSCalibrEvent_mwdc_x<150.){
	hSci41Qave->Fill(qSci);
	hTOF1.Fill(tTOF2-tTOF1);
	hTOF2.Fill(tTOF3-tTOF1);
	hTOF.Fill(TOF);
	hTOF1dE.Fill(tTOF2-tTOF1,qSci);
	hTOF2dE.Fill(tTOF3-tTOF1,qSci);
	//	hTOF1xfoc.Fill(FRSCalibrEvent_s4foc_x,tTOF3-tTOF1);
	hTOF1xfoc.Fill(FRSCalibrEvent_s4foc_x,TOF);	
      }
   }

   //   TString dir = gSystem->->UnixPathName(gInterpreter->GetCurrentMacroName());
   //   dir.ReplaceAll("chkcaldata.C","");
   //   dir.ReplaceAll("/./","/");
   //   in.open(Form("/home/daq/Desktop/s436/offline/jin2018jan/chkrun.txt"));
   //   ifstream ifs("/home/daq/Desktop/s436/offline/jin2018jan/chkrun.txt");
   ifstream ifs;
   ifs.open("chkrun.txt");
   char runnum[4];
   //   while(ifs && getline(ifs,runnum)){
   //     cout << runnum << endl;
   //   }
   while (1) {
     ifs >> runnum;
     if (!ifs.good()) break;
   }
   ifs.close();
   
   //   Int_t runnum=180;
   char rootfilename[20];
   char psfilename[20];
   sprintf(rootfilename,"run%s.root",runnum);
   sprintf(psfilename,"run%s.ps",runnum);

   TPostScript *ps = new TPostScript(psfilename,112);
   
   TCanvas *cv1 = new TCanvas("cv1","Canvas",1500,1200);
   TCanvas *cv2 = new TCanvas("cv2","Canvas",1500,1200);
   cv1->Divide(3,3);
   cv2->Divide(4,4);
   
   ps->NewPage();
   cv1->cd(1);
   hMWDC_X.Draw(""); 
   cv1->cd(2);
   hMWDC_A.Draw(""); 
   cv1->cd(3);
   hMWDC_Y.Draw(""); 
   cv1->cd(4);
   hMWDC_B.Draw("");
   cv1->cd(5);
   hMWDC_XY.Draw("colz"); gPad->SetLogz();
   cv1->cd(6);
   hMWDC_XA.Draw("colz"); gPad->SetLogz();
   cv1->cd(7);
   hMWDC_YB.Draw("colz"); gPad->SetLogz();
   cv1-> cd(8);
   hMWDC_AB.Draw("colz"); gPad->SetLogz();
   cv1-> cd(9);
   hMWDC_focXA.Draw("colz"); gPad->SetLogz();

   cv1->Update();

   ps->NewPage();
   
   cv2-> cd(1);
   hSci41L_Q.Draw(""); gPad->SetLogy();
   cv2-> cd(2);
   hSci41R_Q.Draw(""); gPad->SetLogy();
   cv2-> cd(3);
   hSci41Qave->Draw(""); gPad->SetLogy();
   cv2-> cd(4);
   hSci41L_T.Draw(""); gPad->SetLogy();
   cv2-> cd(5);
   hSci41R_T.Draw(""); gPad->SetLogy();
   cv2-> cd(6);
   hTOF41L_T.Draw(""); gPad->SetLogy();
   cv2-> cd(7);
   hTOF41R_T.Draw(""); gPad->SetLogy();
   cv2-> cd(8);
   hTOF42L_T.Draw(""); gPad->SetLogy();
   cv2-> cd(9);
   hTOF42R_T.Draw(""); gPad->SetLogy();
   cv2-> cd(10);
   hTOF43L_T.Draw(""); gPad->SetLogy();
   cv2-> cd(11);
   hTOF43R_T.Draw(""); gPad->SetLogy();
   cv2-> cd(12);   
   hTOF1.Draw(""); gPad->SetLogy();
   cv2-> cd(13);   
   hTOF2.Draw(""); gPad->SetLogy();
   cv2-> cd(14);
   hTOF.Draw(""); gPad->SetLogy();
   cv2-> cd(15);   
   hTOF1dE.Draw("colz"); gPad->SetLogz();
   cv2-> cd(16);
   hTOF1xfoc.Draw("colz"); //gPad->SetLogz();
   //   hTOF2dE.Draw("colz"); gPad->SetLogz();

   cv2->Update();
   ps->Close();
   
   //   TFile *fout = new TFile("run229.root","RECREATE");
   TFile *fout = new TFile(rootfilename,"RECREATE");
   hMWDC_X.Write(); 
   hMWDC_A.Write(); 
   hMWDC_Y.Write(); 
   hMWDC_B.Write();
   hMWDC_XY.Write();
   hMWDC_XA.Write();
   hMWDC_YB.Write();
   hMWDC_AB.Write();
   hMWDC_focXA.Write();

   hSci41L_Q.Write();
   hSci41R_Q.Write();
   hSci41Qave->Write();
   hSci41L_T.Write();
   hSci41R_T.Write();
   hTOF41L_T.Write();
   hTOF41R_T.Write();
   hTOF42L_T.Write();
   hTOF42R_T.Write();
   hTOF43L_T.Write();
   hTOF43R_T.Write();
   hTOF1.Write();
   hTOF2.Write();
   hTOF.Write();
   hTOF1dE.Write();
   hTOF1xfoc.Write();
   
   fout->Close();
}
