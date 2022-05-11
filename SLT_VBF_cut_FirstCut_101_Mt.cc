#include "TFile.h"
#include "Tcanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TTree.h"
#include "Tlegend.h"
#include "TChain.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TPad.h"
#include "TMath.h"
#include <iostream>
using namespace std;
string itoa(int num);

void SLT_VBF_cut_FirstCut_101_Mt(){

  const int n_smp = 10;
  string smp_tree[n_smp] = { "SMH", "diboson", "DY", "fake", "Z", "W", "Ztt", "singletop", "ttbar", "VBF101" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "SLT_job_SR_data18/Ntuple/"; // path to input files
  string ana_tag = "FinalNtuple.TauLH.";
  string smp_names[n_smp] = { "SM_H", "diboson", "DY", "Fake", "Zll", "W", "Ztautau1", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv0cv1." };
 
  for (int i=0; i<n_smp; i++)
    {
      smp = pwd + ana_tag + smp_names[i] +".0.root";
      cout<<smp<<endl;
      chain_smp[i] = new TChain(smp_tree[i].c_str());
      chain_smp[i]->Add(smp.c_str());
    }
  
  string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake", "Z", "Wl#nu", "Z#tau#tau", "single top", "ttbar", "VBF101 x 7314.718" };  // only for legend

  string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake", "Z", "W", "Ztt", "singletop", "ttbar", "VBF101" };
    
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];

    TCut weight = "weight";
    TCut TwoBTaggedJets = "BTag==2";
    TCut TwoOppositeSignTau = "LepQ*TauQ<0";
    TCut FakeTau = "isFakeTau==1";
    TCut TrueTau = "isFakeTau==0";
    TCut factor = "7314.718";
    
    // SM cut flow
    /*TCut Mhh = "Mhh>490000";
    TCut mBB = "mBB>80000";
    TCut mMMC = "mMMC<150000";
    TCut dEtaBB = "dEtaBB<1.4";
    TCut dRHH = "dRHH>2.2";
    TCut dEtaLepTau = "abs(TauEta-LepEta)<1.4";
    TCut pTVBFj1 = "pTVBFj1>30000";
    TCut Mvis = "Mvis<120000";*/
    
    // Optimize individually
    TCut MT2 = "MT2>190000";
    TCut dRLepTau = "dRLepTau<1.4";
    TCut mBB = "mBB>90000";
    TCut mVBFjj = "mVBFjj>550000";
    TCut dPhiLep0MET = "dPhiLep0MET<1.2";
    TCut Mvis = "Mvis<120000";
    TCut Mw = "Mw>60000";
    TCut etaVBFj1 = "abs(etaVBFj1)>0.4";
     
    cout << " " << endl;
    cout << "  ===========================================================   dEtaBB   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut1 = 15;
    TCut cut1_1[n_cut1] = { "dEtaBB<0.2", "dEtaBB<0.4", "dEtaBB<0.6", "dEtaBB<0.8", "dEtaBB<1 ", "dEtaBB<1.2", "dEtaBB<1.4", "dEtaBB<1.6", "dEtaBB<1.8", "dEtaBB<2", "dEtaBB<2.2", "dEtaBB<2.4", "dEtaBB<2.6", "dEtaBB<2.8", "dEtaBB<3" };
    string cut1_2[n_cut1] = { "dEtaBB<0.2", "dEtaBB<0.4", "dEtaBB<0.6", "dEtaBB<0.8", "dEtaBB<1 ", "dEtaBB<1.2", "dEtaBB<1.4", "dEtaBB<1.6", "dEtaBB<1.8", "dEtaBB<2", "dEtaBB<2.2", "dEtaBB<2.4", "dEtaBB<2.6", "dEtaBB<2.8", "dEtaBB<3", };
    
    TCanvas *canvas1[n_cut1] ;
    canvas1[0] = new TCanvas ("c0", "Mhh",980,580);
    canvas1[1] = new TCanvas ("c1", "Mhh",980,580);
    canvas1[2] = new TCanvas ("c2", "Mhh",980,580);
    canvas1[3] = new TCanvas ("c3", "Mhh",980,580);
    canvas1[4] = new TCanvas ("c4", "Mhh",980,580);
    canvas1[5] = new TCanvas ("c5", "Mhh",980,580);
    canvas1[6] = new TCanvas ("c6", "Mhh",980,580);
    canvas1[7] = new TCanvas ("c7", "Mhh",980,580);
    canvas1[8] = new TCanvas ("c8", "Mhh",980,580);
    canvas1[9] = new TCanvas ("c9", "Mhh",980,580);
    canvas1[10] = new TCanvas ("c10", "Mhh",980,580);
    canvas1[11] = new TCanvas ("c11", "Mhh",980,580);
    canvas1[12] = new TCanvas ("c12", "Mhh",980,580);
    canvas1[13] = new TCanvas ("c13", "Mhh",980,580);
    canvas1[14] = new TCanvas ("c14", "Mhh",980,580);
    
    TPad *pad11[n_cut1];
    pad11[0] = new TPad ("pad0", "", 0,0,0.75,1);
    pad11[1] = new TPad ("pad11", "", 0,0,0.75,1);
    pad11[2] = new TPad ("pad12", "", 0,0,0.75,1);
    pad11[3] = new TPad ("pad3", "", 0,0,0.75,1);
    pad11[4] = new TPad ("pad4", "", 0,0,0.75,1);
    pad11[5] = new TPad ("pad5", "", 0,0,0.75,1);
    pad11[6] = new TPad ("pad6", "", 0,0,0.75,1);
    pad11[7] = new TPad ("pad7", "", 0,0,0.75,1);
    pad11[8] = new TPad ("pad8", "", 0,0,0.75,1);
    pad11[9] = new TPad ("pad9", "", 0,0,0.75,1);
    pad11[10] = new TPad ("pad10", "", 0,0,0.75,1);
    pad11[11] = new TPad ("pad11", "", 0,0,0.75,1);
    pad11[12] = new TPad ("pad12", "", 0,0,0.75,1);
    pad11[13] = new TPad ("pad13", "", 0,0,0.75,1);
    pad11[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
    TPad *pad12[n_cut1];
    pad12[0] = new TPad ("pad0", "",0.73,0,1,1);
    pad12[1] = new TPad ("pad11", "",0.73,0,1,1);
    pad12[2] = new TPad ("pad12", "",0.73,0,1,1);
    pad12[3] = new TPad ("pad3", "",0.73,0,1,1);
    pad12[4] = new TPad ("pad4", "",0.73,0,1,1);
    pad12[5] = new TPad ("pad5", "",0.73,0,1,1);
    pad12[6] = new TPad ("pad6", "",0.73,0,1,1);
    pad12[7] = new TPad ("pad7", "",0.73,0,1,1);
    pad12[8] = new TPad ("pad8", "",0.73,0,1,1);
    pad12[9] = new TPad ("pad9", "",0.73,0,1,1);
    pad12[10] = new TPad ("pad10", "",0.73,0,1,1);
    pad12[11] = new TPad ("pad11", "",0.73,0,1,1);
    pad12[12] = new TPad ("pad12", "",0.73,0,1,1);
    pad12[13] = new TPad ("pad13", "",0.73,0,1,1);
    pad12[14] = new TPad ("pad14", "",0.73,0,1,1);
    
    for (int k=0;k<n_cut1;k++) {
         canvas1[k]->cd();
         pad11[k]->Draw();
         pad12[k]->Draw();
         
         pad11[k]->cd();
         pad11[k]->SetTickx();

         gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
          h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
      h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
      h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
      h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
      h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
      h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
      h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101
    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]=("Mt*0.001>>"+h_title[i]);
      }
      
      for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut1_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut1_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut1_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut1_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut1_1[k]),  "SAMEHIST");
        }
        
        THStack *hs1 = new THStack("hs1", "");
        for(int i= 0; i<9 ; i++){ hs1->Add(h_hist[i], "hist1"); }
        hs1->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut1_1[k]), "SAMEHIST");} //VBF101
        }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h11 = new TH1F("h11","Quadratic Sum from left",40,0,2000); //left
      
     float S_l_1 = 0;
     float B_l_1_0 = 0;
     float B_l_1_1 = 0;
     float B_l_1_2 = 0;
     float B_l_1_3 = 0;
     float B_l_1_4 = 0;
     float B_l_1_5 = 0;
     float B_l_1_6 = 0;
     float B_l_1_7 = 0;
     float B_l_1_8 = 0;
      
     float QuadraticSum_l_1 = 0;
     float Sum_l_1 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_1 = h_hist[9]->GetBinContent(j); //VBF101
         //cout << " S of each bin = " << S_l_1 << endl;
         B_l_1_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_1_8 << endl;
         B_l_1_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_1_7 << endl;
         B_l_1_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_1_6 << endl;
         B_l_1_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_1_5 << endl;
         B_l_1_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_1_4 << endl;
         B_l_1_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake of each bin = " << B_l_1_3 << endl;
         B_l_1_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_1_2 << endl;
         B_l_1_2 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_1_2 << endl;
         B_l_1_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_1_0 << endl;
         
         float B_l_1 = 0;
         for(int i = 0; i<9; i++) { B_l_1 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_1 << endl;
         
         
        float Bin_l_1 = 0;
        if (B_l_1 > 0){
            Bin_l_1 =  2* ( (S_l_1 + B_l_1) * log(1+S_l_1/B_l_1) - S_l_1 );
            //Bin_l_1 = (S_l_1/sqrt(B_l_1))*(S_l_1/sqrt(B_l_1));
            }
          
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_1) << endl; //
         

         Sum_l_1 += Bin_l_1 ;
         QuadraticSum_l_1 = sqrt(Sum_l_1);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_1 << endl;

         h11->SetBinContent(j,QuadraticSum_l_1);
         h11->SetLineColor(kBlue-9);
         h11->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h12 = new TH1F("h12","Quadratic Sum from right",40,0,2000); //right
      
     float S_r_1 = 0;
     float B_r_1_0 = 0;
     float B_r_1_1= 0;
     float B_r_1_2 = 0;
     float B_r_1_3 = 0;
     float B_r_1_4 = 0;
     float B_r_1_5 = 0;
     float B_r_1_6 = 0;
     float B_r_1_7 = 0;
     float B_r_1_8 = 0;
      
     float QuadraticSum_r_1 = 0;
     float Sum_r_1 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_1 = h_hist[9]->GetBinContent(j); //VBF101
        //cout << " S of each bin = " << S_r_1 << endl;
        B_r_1_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_1_8 << endl;
        B_r_1_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_1_7 << endl;
        B_r_1_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_1_6 << endl;
        B_r_1_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_1_5 << endl;
        B_r_1_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_1_4 << endl;
        B_r_1_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake of each bin = " << B_r_1_3 << endl;
        B_r_1_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_1_2 << endl;
        B_r_1_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r << endl;
        B_r_1_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SM H of each bin = " << B_r_1_0 << endl;
        
        float B_r_1 = 0;
        for(int i = 0; i<9; i++) { B_r_1 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_1 << endl;
        
        float Bin_r_1 = 0;
        if (B_r_1 > 0){
            Bin_r_1 =  2* ( (S_r_1 + B_r_1) * log(1+S_r_1/B_r_1) - S_r_1 );
            //Bin_r_1 = (S_r_1/sqrt(B_r_1))*(S_r_1/sqrt(B_r_1));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_1) << endl;
        

        Sum_r_1 += Bin_r_1 ;
        QuadraticSum_r_1 = sqrt(Sum_r_1);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_1 << endl;

        h12->SetBinContent(j,QuadraticSum_r_1);
        h12->SetLineColor(kGreen-9);
        h12->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
      
      float rightmax1 = 1.1*h11->GetMaximum();
      float scale1 = 5000 / rightmax1;
      h11->Scale(scale1);
      h11->Draw("SAMEHIST");
      h12->Scale(scale1);
      h12->Draw("SAMEHIST");
      
      TGaxis*axis1 = new TGaxis(2000,0,2000,5000,0,rightmax1,510,"+L");
      axis1->SetTitle("Quadratic Sum of significance");
      axis1->SetTitleSize(0.03);
      axis1->SetLabelSize(0.025);
      axis1->Draw();
      
      pad12[k]->cd();
      TLegend *leg1 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg1->SetBorderSize(1);
      leg1->SetFillColor(0);
      leg1->SetTextFont(42);
      leg1->SetTextSize(0.053);
      
      for(int i= 9; i>=0 ; i--){
          leg1->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg1->AddEntry(h11, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg1->AddEntry(h12, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg1->Draw();
      
      
      // =================  Significance  =================
        
      cout << "" << endl;
      cout << cut1_2[k] << endl;
      cout << "Mt =" << QuadraticSum_l_1 << endl;
      cout << "" << endl;
        
    }
     
   
     
    cout << " " << endl;
    cout << "  ===========================================================   dEtaHBB   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut2 = 26;
    TCut cut2_1[n_cut2] = { "dEtaHBB>0.2", "dEtaHBB>0.4", "dEtaHBB>0.6", "dEtaHBB>0.8", "dEtaHBB>1 ", "dEtaHBB>1.2", "dEtaHBB>1.4", "dEtaHBB>1.6", "dEtaHBB>1.8", "dEtaHBB>2", "dEtaHBB>2.2", "dEtaHBB>2.4", "dEtaHBB>2.6", "dEtaHBB>2.8", "dEtaHBB>3", "dEtaHBB>3.2", "dEtaHBB>3.4", "dEtaHBB>3.6", "dEtaHBB>3.8", "dEtaHBB>4", "dEtaHBB>4.2", "dEtaHBB>4.4", "dEtaHBB>4.6","dEtaHBB>4.8", "dEtaHBB>5",  "dEtaHBB>5.2" };
    string cut2_2[n_cut2] = { "dEtaHBB>0.2", "dEtaHBB>0.4", "dEtaHBB>0.6", "dEtaHBB>0.8", "dEtaHBB>1 ", "dEtaHBB>1.2", "dEtaHBB>1.4", "dEtaHBB>1.6", "dEtaHBB>1.8", "dEtaHBB>2", "dEtaHBB>2.2", "dEtaHBB>2.4", "dEtaHBB>2.6", "dEtaHBB>2.8", "dEtaHBB>3", "dEtaHBB>3.2", "dEtaHBB>3.4", "dEtaHBB>3.6", "dEtaHBB>3.8", "dEtaHBB>4", "dEtaHBB>4.2", "dEtaHBB>4.4", "dEtaHBB>4.6","dEtaHBB>4.8", "dEtaHBB>5",  "dEtaHBB>5.2" };
    

      TCanvas *canvas2[n_cut2] ;
      canvas2[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas2[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas2[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas2[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas2[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas2[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas2[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas2[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas2[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas2[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas2[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas2[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas2[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas2[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas2[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas2[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas2[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas2[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas2[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas2[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas2[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas2[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas2[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas2[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas2[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas2[25] = new TCanvas ("c25", "Mhh",980,580);
      
      TPad *pad21[n_cut2];
      pad21[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad21[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad21[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad21[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad21[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad21[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad21[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad21[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad21[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad21[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad21[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad21[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad21[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad21[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad21[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad21[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad21[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad21[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad21[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad21[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad21[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad21[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad21[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad21[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad21[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad21[25] = new TPad ("pad25", "", 0,0,0.75,1);
      
      TPad *pad22[n_cut2];
      pad22[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad22[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad22[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad22[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad22[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad22[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad22[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad22[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad22[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad22[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad22[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad22[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad22[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad22[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad22[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad22[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad22[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad22[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad22[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad22[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad22[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad22[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad22[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad22[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad22[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad22[25] = new TPad ("pad25", "",0.73,0,1,1);
    
      
      for (int k=0;k<n_cut2;k++) {
           canvas2[k]->cd();
           pad21[k]->Draw();
           pad22[k]->Draw();
           
           pad21[k]->cd();
           pad21[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut2_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut2_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut2_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut2_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut2_1[k]),  "SAMEHIST");
        }
        
        THStack *hs2 = new THStack("hs2", "");
        for(int i= 0; i<9 ; i++){ hs2->Add(h_hist[i], "hist1"); }
        hs2->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut2_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h21 = new TH1F("h21","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_2 = 0;
       float B_l_2_0 = 0;
       float B_l_2_1 = 0;
       float B_l_2_2 = 0;
       float B_l_2_3 = 0;
       float B_l_2_4 = 0;
       float B_l_2_5 = 0;
       float B_l_2_6 = 0;
       float B_l_2_7 = 0;
       float B_l_2_8 = 0;
        
       float QuadraticSum_l_2 = 0;
       float Sum_l_2 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_2 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_2 << endl;
           B_l_2_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_2_8 << endl;
           B_l_2_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_2_7 << endl;
           B_l_2_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_2_6 << endl;
           B_l_2_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_2_5 << endl;
           B_l_2_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_2_4 << endl;
           B_l_2_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_2_3 << endl;
           B_l_2_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_2_2 << endl;
           B_l_2_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_2_1 << endl;
           B_l_2_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_2_0 << endl;
           
           float B_l_2 = 0;
           for(int i = 0; i<9; i++) { B_l_2 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_2 << endl;
           
           float Bin_l_2 = 0;
           if (B_l_2 > 0){
               Bin_l_2 =  2* ( (S_l_2 + B_l_2) * log(1+S_l_2/B_l_2) - S_l_2 );
               //Bin_l_2 = (S_l_2/sqrt(B_l_2))*(S_l_2/sqrt(B_l_2));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_2) << endl; //
           

           Sum_l_2 += Bin_l_2 ;
           QuadraticSum_l_2 = sqrt(Sum_l_2);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_2 << endl; //

           h21->SetBinContent(j,QuadraticSum_l_2);
           h21->SetLineColor(kBlue-9);
           h21->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h22 = new TH1F("h22","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_2 = 0;
       float B_r_2_0 = 0;
       float B_r_2_1 = 0;
       float B_r_2_2 = 0;
       float B_r_2_3 = 0;
       float B_r_2_4 = 0;
       float B_r_2_5 = 0;
       float B_r_2_6 = 0;
       float B_r_2_7 = 0;
       float B_r_2_8 = 0;
        
       float QuadraticSum_r_2 = 0;
       float Sum_r_2 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_2 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_2 << endl;
          B_r_2_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_2_8 << endl;
          B_r_2_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_2_7 << endl;
          B_r_2_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_2_6 << endl;
          B_r_2_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_2_5 << endl;
          B_r_2_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_2_4 << endl;
          B_r_2_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_2_3 << endl;
          B_r_2_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_2_2 << endl;
          B_r_2_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_2_1 << endl;
          B_r_2_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_2_0 << endl;
          
          float B_r_2 = 0;
          for(int i = 0; i<9; i++) { B_r_2 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_2 << endl;
          
          float Bin_r_2 = 0;
          if (B_r_2 > 0){
              Bin_r_2 =  2* ( (S_r_2 + B_r_2) * log(1+S_r_2/B_r_2) - S_r_2 );
              //Bin_r_2 = (S_r_2/sqrt(B_r_2))*(S_r_2/sqrt(B_r_2));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_2) << endl;
          

          Sum_r_2 += Bin_r_2 ;
          QuadraticSum_r_2 = sqrt(Sum_r_2);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_2 << endl;

          h22->SetBinContent(j,QuadraticSum_r_2);
          h22->SetLineColor(kGreen-9);
          h22->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax2 = 1.1*h21->GetMaximum();
    float scale2 = 5000 / rightmax2;
    h21->Scale(scale2);
    h21->Draw("SAMEHIST");
    
    h22->Scale(scale2);
    h22->Draw("SAMEHIST");
    

    TGaxis*axis2 = new TGaxis(2000,0,2000,5000,0,rightmax2,510,"+L");
    axis2->SetTitle("Quadratic Sum of significance");
    axis2->SetTitleSize(0.03);
    axis2->SetLabelSize(0.025);
    axis2->Draw();
    
    pad22[k]->cd();
    TLegend *leg2 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg2->SetBorderSize(1);
    leg2->SetFillColor(0);
    leg2->SetTextFont(42);
    leg2->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg2->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg2->AddEntry(h21, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg2->AddEntry(h22, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg2->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut2_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_2 << endl;
        cout << "" << endl;
          
      }
      
     
    cout << " " << endl;
    cout << "  ===========================================================   dEtaLepTau   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut3 = 24;
    TCut cut3_1[n_cut3] = { "abs(TauEta-LepEta)<0.2", "abs(TauEta-LepEta)<0.4", "abs(TauEta-LepEta)<0.6", "abs(TauEta-LepEta)<0.8", "abs(TauEta-LepEta)<1 ", "abs(TauEta-LepEta)<1.2", "abs(TauEta-LepEta)<1.4", "abs(TauEta-LepEta)<1.6", "abs(TauEta-LepEta)<1.8", "abs(TauEta-LepEta)<2", "abs(TauEta-LepEta)<2.2", "abs(TauEta-LepEta)<2.4", "abs(TauEta-LepEta)<2.6", "abs(TauEta-LepEta)<2.8", "abs(TauEta-LepEta)<3", "abs(TauEta-LepEta)<3.2", "abs(TauEta-LepEta)<3.4", "abs(TauEta-LepEta)<3.6", "abs(TauEta-LepEta)<3.8", "abs(TauEta-LepEta)<4", "abs(TauEta-LepEta)<4.2", "abs(TauEta-LepEta)<4.4", "abs(TauEta-LepEta)<4.6","abs(TauEta-LepEta)<4.8" };
    string cut3_2[n_cut3] = { "dEtaLepTau<0.2", "dEtaLepTau<0.4", "dEtaLepTau<0.6", "dEtaLepTau<0.8", "dEtaLepTau<1 ", "dEtaLepTau<1.2", "dEtaLepTau<1.4", "dEtaLepTau<1.6", "dEtaLepTau<1.8", "dEtaLepTau<2", "dEtaLepTau<2.2", "dEtaLepTau<2.4", "dEtaLepTau<2.6", "dEtaLepTau<2.8", "dEtaLepTau<3", "dEtaLepTau<3.2", "dEtaLepTau<3.4", "dEtaLepTau<3.6", "dEtaLepTau<3.8", "dEtaLepTau<4", "dEtaLepTau<4.2", "dEtaLepTau<4.4", "dEtaLepTau<4.6","dEtaLepTau<4.8" };
    

      TCanvas *canvas3[n_cut3] ;
      canvas3[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas3[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas3[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas3[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas3[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas3[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas3[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas3[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas3[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas3[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas3[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas3[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas3[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas3[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas3[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas3[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas3[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas3[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas3[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas3[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas3[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas3[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas3[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas3[23] = new TCanvas ("c23", "Mhh",980,580);
      
      TPad *pad31[n_cut3];
      pad31[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad31[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad31[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad31[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad31[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad31[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad31[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad31[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad31[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad31[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad31[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad31[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad31[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad31[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad31[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad31[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad31[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad31[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad31[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad31[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad31[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad31[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad31[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad31[23] = new TPad ("pad23", "", 0,0,0.75,1);
      
      TPad *pad32[n_cut3];
      pad32[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad32[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad32[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad32[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad32[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad32[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad32[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad32[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad32[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad32[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad32[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad32[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad32[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad32[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad32[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad32[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad32[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad32[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad32[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad32[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad32[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad32[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad32[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad32[23] = new TPad ("pad23", "",0.73,0,1,1);
    
      
      for (int k=0;k<n_cut3;k++) {
           canvas3[k]->cd();
           pad31[k]->Draw();
           pad32[k]->Draw();
           
           pad31[k]->cd();
           pad31[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut3_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut3_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut3_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut3_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut3_1[k]),  "SAMEHIST");
        }
        
        THStack *hs3 = new THStack("hs3", "");
        for(int i= 0; i<9 ; i++){ hs3->Add(h_hist[i], "hist1"); }
        hs3->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut3_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h31 = new TH1F("h31","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_3 = 0;
       float B_l_3_0 = 0;
       float B_l_3_1 = 0;
       float B_l_3_2 = 0;
       float B_l_3_3 = 0;
       float B_l_3_4 = 0;
       float B_l_3_5 = 0;
       float B_l_3_6 = 0;
       float B_l_3_7 = 0;
       float B_l_3_8 = 0;
        
       float QuadraticSum_l_3 = 0;
       float Sum_l_3 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_3 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_3 << endl;
           B_l_3_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_3_8 << endl;
           B_l_3_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_3_7 << endl;
           B_l_3_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_3_6 << endl;
           B_l_3_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_3_5 << endl;
           B_l_3_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_3_4 << endl;
           B_l_3_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_3_3 << endl;
           B_l_3_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_3_2 << endl;
           B_l_3_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_3_1 << endl;
           B_l_3_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_3_0 << endl;
           
           float B_l_3 = 0;
           for(int i = 0; i<9; i++) { B_l_3 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_3 << endl;
           
           float Bin_l_3 = 0;
           if (B_l_3 > 0){
               Bin_l_3 =  2* ( (S_l_3 + B_l_3) * log(1+S_l_3/B_l_3) - S_l_3 );
               //Bin_l_3 = (S_l_3/sqrt(B_l_3))*(S_l_3/sqrt(B_l_3));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_3) << endl; //
           

           Sum_l_3 += Bin_l_3 ;
           QuadraticSum_l_3 = sqrt(Sum_l_3);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_3 << endl; //

           h31->SetBinContent(j,QuadraticSum_l_3);
           h31->SetLineColor(kBlue-9);
           h31->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h32 = new TH1F("h32","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_3 = 0;
       float B_r_3_0 = 0;
       float B_r_3_1 = 0;
       float B_r_3_2 = 0;
       float B_r_3_3 = 0;
       float B_r_3_4 = 0;
       float B_r_3_5 = 0;
       float B_r_3_6 = 0;
       float B_r_3_7 = 0;
       float B_r_3_8 = 0;
        
       float QuadraticSum_r_3 = 0;
       float Sum_r_3 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_3 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_3 << endl;
          B_r_3_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_3_8 << endl;
          B_r_3_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_3_7 << endl;
          B_r_3_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_3_6 << endl;
          B_r_3_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_3_5 << endl;
          B_r_3_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_3_4 << endl;
          B_r_3_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_3_3 << endl;
          B_r_3_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_3_2 << endl;
          B_r_3_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_3_1 << endl;
          B_r_3_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_3_0 << endl;
          
          float B_r_3 = 0;
          for(int i = 0; i<9; i++) { B_r_3 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_3 << endl;
          
          float Bin_r_3 = 0;
          if (B_r_3 > 0){
              Bin_r_3 =  2* ( (S_r_3 + B_r_3) * log(1+S_r_3/B_r_3) - S_r_3 );
              //Bin_r_3 = (S_r_3/sqrt(B_r_3))*(S_r_3/sqrt(B_r_3));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_3) << endl;
          

          Sum_r_3 += Bin_r_3 ;
          QuadraticSum_r_3 = sqrt(Sum_r_3);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_3 << endl;

          h32->SetBinContent(j,QuadraticSum_r_3);
          h32->SetLineColor(kGreen-9);
          h32->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax3 = 1.1*h31->GetMaximum();
    float scale3 = 5000 / rightmax3;
    h31->Scale(scale3);
    h31->Draw("SAMEHIST");
    
    h32->Scale(scale3);
    h32->Draw("SAMEHIST");
    

    TGaxis*axis3 = new TGaxis(2000,0,2000,5000,0,rightmax3,510,"+L");
    axis3->SetTitle("Quadratic Sum of significance");
    axis3->SetTitleSize(0.03);
    axis3->SetLabelSize(0.025);
    axis3->Draw();
    
    pad32[k]->cd();
    TLegend *leg3 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg3->SetBorderSize(1);
    leg3->SetFillColor(0);
    leg3->SetTextFont(42);
    leg3->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg3->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg3->AddEntry(h31, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg3->AddEntry(h32, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg3->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut3_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_3 << endl;
        cout << "" << endl;
          
      }
     
      
    cout << " " << endl;
    cout << "  ===========================================================   dEtaVBFjj   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut4 = 26;
    TCut cut4_1[n_cut4] = { "dEtaVBFjj>1 ", "dEtaVBFjj>1.2", "dEtaVBFjj>1.4", "dEtaVBFjj>1.6", "dEtaVBFjj>1.8", "dEtaVBFjj>2", "dEtaVBFjj>2.2", "dEtaVBFjj>2.4", "dEtaVBFjj>2.6", "dEtaVBFjj>2.8", "dEtaVBFjj>3", "dEtaVBFjj>3.2", "dEtaVBFjj>3.4", "dEtaVBFjj>3.6", "dEtaVBFjj>3.8", "dEtaVBFjj>4", "dEtaVBFjj>4.2", "dEtaVBFjj>4.4", "dEtaVBFjj>4.6","dEtaVBFjj>4.8", "dEtaVBFjj>5", "dEtaVBFjj>5.2", "dEtaVBFjj>5.4", "dEtaVBFjj>5.6", "dEtaVBFjj>5.8", "dEtaVBFjj>6" };
    string cut4_2[n_cut4] = { "dEtaVBFjj>1 ", "dEtaVBFjj>1.2", "dEtaVBFjj>1.4", "dEtaVBFjj>1.6", "dEtaVBFjj>1.8", "dEtaVBFjj>2", "dEtaVBFjj>2.2", "dEtaVBFjj>2.4", "dEtaVBFjj>2.6", "dEtaVBFjj>2.8", "dEtaVBFjj>3", "dEtaVBFjj>3.2", "dEtaVBFjj>3.4", "dEtaVBFjj>3.6", "dEtaVBFjj>3.8", "dEtaVBFjj>4", "dEtaVBFjj>4.2", "dEtaVBFjj>4.4", "dEtaVBFjj>4.6","dEtaVBFjj>4.8", "dEtaVBFjj>5", "dEtaVBFjj>5.2", "dEtaVBFjj>5.4", "dEtaVBFjj>5.6", "dEtaVBFjj>5.8", "dEtaVBFjj>6" };
    

      TCanvas *canvas4[n_cut4] ;
      canvas4[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas4[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas4[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas4[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas4[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas4[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas4[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas4[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas4[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas4[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas4[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas4[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas4[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas4[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas4[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas4[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas4[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas4[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas4[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas4[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas4[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas4[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas4[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas4[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas4[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas4[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad41[n_cut4];
      pad41[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad41[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad41[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad41[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad41[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad41[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad41[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad41[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad41[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad41[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad41[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad41[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad41[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad41[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad41[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad41[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad41[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad41[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad41[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad41[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad41[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad41[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad41[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad41[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad41[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad41[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad42[n_cut4];
      pad42[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad42[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad42[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad42[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad42[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad42[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad42[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad42[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad42[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad42[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad42[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad42[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad42[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad42[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad42[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad42[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad42[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad42[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad42[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad42[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad42[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad42[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad42[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad42[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad42[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad42[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut4;k++) {
           canvas4[k]->cd();
           pad41[k]->Draw();
           pad42[k]->Draw();
           
           pad41[k]->cd();
           pad41[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut4_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut4_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut4_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut4_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut4_1[k]),  "SAMEHIST");
        }
        
        THStack *hs4 = new THStack("hs4", "");
        for(int i= 0; i<9 ; i++){ hs4->Add(h_hist[i], "hist1"); }
        hs4->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut4_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h41 = new TH1F("h41","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_4 = 0;
       float B_l_4_0 = 0;
       float B_l_4_1 = 0;
       float B_l_4_2 = 0;
       float B_l_4_3 = 0;
       float B_l_4_4 = 0;
       float B_l_4_5 = 0;
       float B_l_4_6 = 0;
       float B_l_4_7 = 0;
       float B_l_4_8 = 0;
        
       float QuadraticSum_l_4 = 0;
       float Sum_l_4 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_4 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_4 << endl;
           B_l_4_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_4_8 << endl;
           B_l_4_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_4_7 << endl;
           B_l_4_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_4_6 << endl;
           B_l_4_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_4_5 << endl;
           B_l_4_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_4_4 << endl;
           B_l_4_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_4_3 << endl;
           B_l_4_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_4_2 << endl;
           B_l_4_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_4_1 << endl;
           B_l_4_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_4_0 << endl;
           
           float B_l_4 = 0;
           for(int i = 0; i<9; i++) { B_l_4 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_4 << endl;
           
           float Bin_l_4 = 0;
           if (B_l_4 > 0){
               Bin_l_4 =  2* ( (S_l_4 + B_l_4) * log(1+S_l_4/B_l_4) - S_l_4 );
               //Bin_l_4 = (S_l_4/sqrt(B_l_4))*(S_l_4/sqrt(B_l_4));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_4) << endl; //
           

           Sum_l_4 += Bin_l_4 ;
           QuadraticSum_l_4 = sqrt(Sum_l_4);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_4 << endl; //

           h41->SetBinContent(j,QuadraticSum_l_4);
           h41->SetLineColor(kBlue-9);
           h41->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h42 = new TH1F("h42","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_4 = 0;
       float B_r_4_0 = 0;
       float B_r_4_1 = 0;
       float B_r_4_2 = 0;
       float B_r_4_3 = 0;
       float B_r_4_4 = 0;
       float B_r_4_5 = 0;
       float B_r_4_6 = 0;
       float B_r_4_7 = 0;
       float B_r_4_8 = 0;
        
       float QuadraticSum_r_4 = 0;
       float Sum_r_4 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_4 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_4 << endl;
          B_r_4_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_4_8 << endl;
          B_r_4_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_4_7 << endl;
          B_r_4_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_4_6 << endl;
          B_r_4_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_4_5 << endl;
          B_r_4_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_4_4 << endl;
          B_r_4_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_4_3 << endl;
          B_r_4_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_4_2 << endl;
          B_r_4_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_4_1 << endl;
          B_r_4_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_4_0 << endl;
          
          float B_r_4 = 0;
          for(int i = 0; i<9; i++) { B_r_4 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_4 << endl;
          
          float Bin_r_4 = 0;
          if (B_r_4 > 0){
              Bin_r_4 =  2* ( (S_r_4 + B_r_4) * log(1+S_r_4/B_r_4) - S_r_4 );
              //Bin_r_4 = (S_r_4/sqrt(B_r_4))*(S_r_4/sqrt(B_r_4));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_4) << endl;
          

          Sum_r_4 += Bin_r_4 ;
          QuadraticSum_r_4 = sqrt(Sum_r_4);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_4 << endl;

          h42->SetBinContent(j,QuadraticSum_r_4);
          h42->SetLineColor(kGreen-9);
          h42->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax4 = 1.1*h41->GetMaximum();
    float scale4 = 5000 / rightmax4;
    h41->Scale(scale4);
    h41->Draw("SAMEHIST");
    
    h42->Scale(scale4);
    h42->Draw("SAMEHIST");
    

    TGaxis*axis4 = new TGaxis(2000,0,2000,5000,0,rightmax4,510,"+L");
    axis4->SetTitle("Quadratic Sum of significance");
    axis4->SetTitleSize(0.03);
    axis4->SetLabelSize(0.025);
    axis4->Draw();
    
    pad42[k]->cd();
    TLegend *leg4 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg4->SetBorderSize(1);
    leg4->SetFillColor(0);
    leg4->SetTextFont(42);
    leg4->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg4->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg4->AddEntry(h41, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg4->AddEntry(h42, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg4->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut4_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_4 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   dPhiBB   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut5 = 16;
    TCut cut5_1[n_cut5] = { "dPhiBB<0.2", "dPhiBB<0.4", "dPhiBB<0.6", "dPhiBB<0.8", "dPhiBB<1", "dPhiBB<1.2", "dPhiBB<1.4", "dPhiBB<1.6", "dPhiBB<1.8", "dPhiBB<2", "dPhiBB<2.2", "dPhiBB<2.4", "dPhiBB<2.6", "dPhiBB<2.8", "dPhiBB<3", "dPhiBB<3.2" };
    string cut5_2[n_cut5] = { "dPhiBB<0.2", "dPhiBB<0.4", "dPhiBB<0.6", "dPhiBB<0.8", "dPhiBB<1", "dPhiBB<1.2", "dPhiBB<1.4", "dPhiBB<1.6", "dPhiBB<1.8", "dPhiBB<2", "dPhiBB<2.2", "dPhiBB<2.4", "dPhiBB<2.6", "dPhiBB<2.8", "dPhiBB<3", "dPhiBB<3.2" };
    

      TCanvas *canvas5[n_cut5] ;
      canvas5[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas5[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas5[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas5[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas5[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas5[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas5[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas5[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas5[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas5[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas5[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas5[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas5[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas5[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas5[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas5[15] = new TCanvas ("c15", "Mhh",980,580);
    
      TPad *pad51[n_cut5];
      pad51[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad51[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad51[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad51[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad51[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad51[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad51[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad51[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad51[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad51[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad51[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad51[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad51[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad51[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad51[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad51[15] = new TPad ("pad15", "", 0,0,0.75,1);
    
      TPad *pad52[n_cut5];
      pad52[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad52[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad52[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad52[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad52[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad52[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad52[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad52[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad52[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad52[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad52[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad52[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad52[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad52[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad52[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad52[15] = new TPad ("pad15", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut5;k++) {
           canvas5[k]->cd();
           pad51[k]->Draw();
           pad52[k]->Draw();
           
           pad51[k]->cd();
           pad51[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut5_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut5_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut5_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut5_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut5_1[k]),  "SAMEHIST");
        }
        
        THStack *hs5 = new THStack("hs5", "");
        for(int i= 0; i<9 ; i++){ hs5->Add(h_hist[i], "hist1"); }
        hs5->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut5_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h51 = new TH1F("h51","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_5 = 0;
       float B_l_5_0 = 0;
       float B_l_5_1 = 0;
       float B_l_5_2 = 0;
       float B_l_5_3 = 0;
       float B_l_5_4 = 0;
       float B_l_5_5 = 0;
       float B_l_5_6 = 0;
       float B_l_5_7 = 0;
       float B_l_5_8 = 0;
        
       float QuadraticSum_l_5 = 0;
       float Sum_l_5 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_5 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_5 << endl;
           B_l_5_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_5_8 << endl;
           B_l_5_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_5_7 << endl;
           B_l_5_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_5_6 << endl;
           B_l_5_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_5_5 << endl;
           B_l_5_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_5_4 << endl;
           B_l_5_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_5_3 << endl;
           B_l_5_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_5_2 << endl;
           B_l_5_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_5_1 << endl;
           B_l_5_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_5_0 << endl;
           
           float B_l_5 = 0;
           for(int i = 0; i<9; i++) { B_l_5 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_5 << endl;
           
           float Bin_l_5 = 0;
           if (B_l_5 > 0){
               Bin_l_5 =  2* ( (S_l_5 + B_l_5) * log(1+S_l_5/B_l_5) - S_l_5 );
               //Bin_l_5 = (S_l_5/sqrt(B_l_5))*(S_l_5/sqrt(B_l_5));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_5) << endl; //
           

           Sum_l_5 += Bin_l_5 ;
           QuadraticSum_l_5 = sqrt(Sum_l_5);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_5 << endl; //

           h51->SetBinContent(j,QuadraticSum_l_5);
           h51->SetLineColor(kBlue-9);
           h51->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h52 = new TH1F("h52","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_5 = 0;
       float B_r_5_0 = 0;
       float B_r_5_1 = 0;
       float B_r_5_2 = 0;
       float B_r_5_3 = 0;
       float B_r_5_4 = 0;
       float B_r_5_5 = 0;
       float B_r_5_6 = 0;
       float B_r_5_7 = 0;
       float B_r_5_8 = 0;
        
       float QuadraticSum_r_5 = 0;
       float Sum_r_5 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_5 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_5 << endl;
          B_r_5_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_5_8 << endl;
          B_r_5_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_5_7 << endl;
          B_r_5_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_5_6 << endl;
          B_r_5_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_5_5 << endl;
          B_r_5_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_5_4 << endl;
          B_r_5_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_5_3 << endl;
          B_r_5_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_5_2 << endl;
          B_r_5_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_5_1 << endl;
          B_r_5_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_5_0 << endl;
          
          float B_r_5 = 0;
          for(int i = 0; i<9; i++) { B_r_5 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_5 << endl;
          
          float Bin_r_5 = 0;
          if (B_r_5 > 0){
              Bin_r_5 =  2* ( (S_r_5 + B_r_5) * log(1+S_r_5/B_r_5) - S_r_5 );
              //Bin_r_5 = (S_r_5/sqrt(B_r_5))*(S_r_5/sqrt(B_r_5));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_5) << endl;
          

          Sum_r_5 += Bin_r_5 ;
          QuadraticSum_r_5 = sqrt(Sum_r_5);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_5 << endl;

          h52->SetBinContent(j,QuadraticSum_r_5);
          h52->SetLineColor(kGreen-9);
          h52->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax5 = 1.1*h51->GetMaximum();
    float scale5 = 5000 / rightmax5;
    h51->Scale(scale5);
    h51->Draw("SAMEHIST");
    
    h52->Scale(scale5);
    h52->Draw("SAMEHIST");
    

    TGaxis*axis5 = new TGaxis(2000,0,2000,5000,0,rightmax5,510,"+L");
    axis5->SetTitle("Quadratic Sum of significance");
    axis5->SetTitleSize(0.03);
    axis5->SetLabelSize(0.025);
    axis5->Draw();
    
    pad52[k]->cd();
    TLegend *leg5 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg5->SetBorderSize(1);
    leg5->SetFillColor(0);
    leg5->SetTextFont(42);
    leg5->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg5->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg5->AddEntry(h51, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg5->AddEntry(h52, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg5->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut5_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_5 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   dPhiHBB   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut6 = 16;
    TCut cut6_1[n_cut6] = { "dPhiHBB>0.2", "dPhiHBB>0.4", "dPhiHBB>0.6", "dPhiHBB>0.8", "dPhiHBB>1", "dPhiHBB>1.2", "dPhiHBB>1.4", "dPhiHBB>1.6", "dPhiHBB>1.8", "dPhiHBB>2", "dPhiHBB>2.2", "dPhiHBB>2.4", "dPhiHBB>2.6", "dPhiHBB>2.8", "dPhiHBB>3", "dPhiHBB>3.2" };
    string cut6_2[n_cut6] = { "dPhiHBB>0.2", "dPhiHBB>0.4", "dPhiHBB>0.6", "dPhiHBB>0.8", "dPhiHBB>1", "dPhiHBB>1.2", "dPhiHBB>1.4", "dPhiHBB>1.6", "dPhiHBB>1.8", "dPhiHBB>2", "dPhiHBB>2.2", "dPhiHBB>2.4", "dPhiHBB>2.6", "dPhiHBB>2.8", "dPhiHBB>3", "dPhiHBB>3.2" };
    

      TCanvas *canvas6[n_cut6] ;
      canvas6[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas6[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas6[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas6[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas6[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas6[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas6[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas6[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas6[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas6[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas6[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas6[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas6[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas6[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas6[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas6[15] = new TCanvas ("c15", "Mhh",980,580);
    
      TPad *pad61[n_cut6];
      pad61[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad61[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad61[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad61[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad61[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad61[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad61[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad61[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad61[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad61[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad61[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad61[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad61[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad61[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad61[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad61[15] = new TPad ("pad15", "", 0,0,0.75,1);
    
      TPad *pad62[n_cut6];
      pad62[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad62[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad62[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad62[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad62[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad62[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad62[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad62[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad62[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad62[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad62[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad62[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad62[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad62[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad62[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad62[15] = new TPad ("pad15", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut6;k++) {
           canvas6[k]->cd();
           pad61[k]->Draw();
           pad62[k]->Draw();
           
           pad61[k]->cd();
           pad61[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut6_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut6_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut6_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut6_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut6_1[k]),  "SAMEHIST");
        }
        
        THStack *hs6 = new THStack("hs6", "");
        for(int i= 0; i<9 ; i++){ hs6->Add(h_hist[i], "hist1"); }
        hs6->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut6_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h61 = new TH1F("h61","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_6 = 0;
       float B_l_6_0 = 0;
       float B_l_6_1 = 0;
       float B_l_6_2 = 0;
       float B_l_6_3 = 0;
       float B_l_6_4 = 0;
       float B_l_6_5 = 0;
       float B_l_6_6 = 0;
       float B_l_6_7 = 0;
       float B_l_6_8 = 0;
        
       float QuadraticSum_l_6 = 0;
       float Sum_l_6 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_6 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_6 << endl;
           B_l_6_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_6_8 << endl;
           B_l_6_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_6_7 << endl;
           B_l_6_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_6_6 << endl;
           B_l_6_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_6_5 << endl;
           B_l_6_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_6_4 << endl;
           B_l_6_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_6_3 << endl;
           B_l_6_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_6_2 << endl;
           B_l_6_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_6_1 << endl;
           B_l_6_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_6_0 << endl;
           
           float B_l_6 = 0;
           for(int i = 0; i<9; i++) { B_l_6 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_6 << endl;
           
           float Bin_l_6 = 0;
           if (B_l_6 > 0){
               Bin_l_6 =  2* ( (S_l_6 + B_l_6) * log(1+S_l_6/B_l_6) - S_l_6 );
               //Bin_l_6 = (S_l_6/sqrt(B_l_6))*(S_l_6/sqrt(B_l_6));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_6) << endl; //
           

           Sum_l_6 += Bin_l_6 ;
           QuadraticSum_l_6 = sqrt(Sum_l_6);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_6 << endl; //

           h61->SetBinContent(j,QuadraticSum_l_6);
           h61->SetLineColor(kBlue-9);
           h61->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h62 = new TH1F("h62","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_6 = 0;
       float B_r_6_0 = 0;
       float B_r_6_1 = 0;
       float B_r_6_2 = 0;
       float B_r_6_3 = 0;
       float B_r_6_4 = 0;
       float B_r_6_5 = 0;
       float B_r_6_6 = 0;
       float B_r_6_7 = 0;
       float B_r_6_8 = 0;
        
       float QuadraticSum_r_6 = 0;
       float Sum_r_6 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_6 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_6 << endl;
          B_r_6_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_6_8 << endl;
          B_r_6_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_6_7 << endl;
          B_r_6_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_6_6 << endl;
          B_r_6_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_6_5 << endl;
          B_r_6_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_6_4 << endl;
          B_r_6_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_6_3 << endl;
          B_r_6_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_6_2 << endl;
          B_r_6_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_6_1 << endl;
          B_r_6_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_6_0 << endl;
          
          float B_r_6 = 0;
          for(int i = 0; i<9; i++) { B_r_6 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_6 << endl;
          
          float Bin_r_6 = 0;
          if (B_r_6 > 0){
              Bin_r_6 =  2* ( (S_r_6 + B_r_6) * log(1+S_r_6/B_r_6) - S_r_6 );
              //Bin_r_6 = (S_r_6/sqrt(B_r_6))*(S_r_6/sqrt(B_r_6));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_6) << endl;
          

          Sum_r_6 += Bin_r_6 ;
          QuadraticSum_r_6 = sqrt(Sum_r_6);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_6 << endl;

          h62->SetBinContent(j,QuadraticSum_r_6);
          h62->SetLineColor(kGreen-9);
          h62->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax6 = 1.1*h61->GetMaximum();
    float scale6 = 5000 / rightmax6;
    h61->Scale(scale6);
    h61->Draw("SAMEHIST");
    
    h62->Scale(scale6);
    h62->Draw("SAMEHIST");
    

    TGaxis*axis6 = new TGaxis(2000,0,2000,5000,0,rightmax6,510,"+L");
    axis6->SetTitle("Quadratic Sum of significance");
    axis6->SetTitleSize(0.03);
    axis6->SetLabelSize(0.025);
    axis6->Draw();
    
    pad62[k]->cd();
    TLegend *leg6 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg6->SetBorderSize(1);
    leg6->SetFillColor(0);
    leg6->SetTextFont(42);
    leg6->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg6->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg6->AddEntry(h61, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg6->AddEntry(h62, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg6->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut6_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_6 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   dPhiHbbMET   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut7 = 16;
    TCut cut7_1[n_cut7] = { "dPhiHbbMET>0.2", "dPhiHbbMET>0.4", "dPhiHbbMET>0.6", "dPhiHbbMET>0.8", "dPhiHbbMET>1", "dPhiHbbMET>1.2", "dPhiHbbMET>1.4", "dPhiHbbMET>1.6", "dPhiHbbMET>1.8", "dPhiHbbMET>2", "dPhiHbbMET>2.2", "dPhiHbbMET>2.4", "dPhiHbbMET>2.6", "dPhiHbbMET>2.8", "dPhiHbbMET>3", "dPhiHbbMET>3.2" };
    string cut7_2[n_cut7] = { "dPhiHbbMET>0.2", "dPhiHbbMET>0.4", "dPhiHbbMET>0.6", "dPhiHbbMET>0.8", "dPhiHbbMET>1", "dPhiHbbMET>1.2", "dPhiHbbMET>1.4", "dPhiHbbMET>1.6", "dPhiHbbMET>1.8", "dPhiHbbMET>2", "dPhiHbbMET>2.2", "dPhiHbbMET>2.4", "dPhiHbbMET>2.6", "dPhiHbbMET>2.8", "dPhiHbbMET>3", "dPhiHbbMET>3.2" };
    

      TCanvas *canvas7[n_cut7] ;
      canvas7[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas7[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas7[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas7[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas7[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas7[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas7[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas7[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas7[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas7[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas7[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas7[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas7[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas7[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas7[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas7[15] = new TCanvas ("c15", "Mhh",980,580);
    
      TPad *pad71[n_cut7];
      pad71[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad71[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad71[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad71[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad71[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad71[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad71[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad71[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad71[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad71[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad71[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad71[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad71[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad71[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad71[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad71[15] = new TPad ("pad15", "", 0,0,0.75,1);
    
      TPad *pad72[n_cut7];
      pad72[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad72[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad72[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad72[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad72[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad72[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad72[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad72[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad72[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad72[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad72[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad72[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad72[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad72[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad72[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad72[15] = new TPad ("pad15", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut7;k++) {
           canvas7[k]->cd();
           pad71[k]->Draw();
           pad72[k]->Draw();
           
           pad71[k]->cd();
           pad71[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut7_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut7_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut7_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut7_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut7_1[k]),  "SAMEHIST");
        }
        
        THStack *hs7 = new THStack("hs7", "");
        for(int i= 0; i<9 ; i++){ hs7->Add(h_hist[i], "hist1"); }
        hs7->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut7_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h71 = new TH1F("h71","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_7 = 0;
       float B_l_7_0 = 0;
       float B_l_7_1 = 0;
       float B_l_7_2 = 0;
       float B_l_7_3 = 0;
       float B_l_7_4 = 0;
       float B_l_7_5 = 0;
       float B_l_7_6 = 0;
       float B_l_7_7 = 0;
       float B_l_7_8 = 0;
        
       float QuadraticSum_l_7 = 0;
       float Sum_l_7 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_7 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_7 << endl;
           B_l_7_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_7_8 << endl;
           B_l_7_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_7_7 << endl;
           B_l_7_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_7_6 << endl;
           B_l_7_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_7_5 << endl;
           B_l_7_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_7_4 << endl;
           B_l_7_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_7_3 << endl;
           B_l_7_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_7_2 << endl;
           B_l_7_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_7_1 << endl;
           B_l_7_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_7_0 << endl;
           
           float B_l_7 = 0;
           for(int i = 0; i<9; i++) { B_l_7 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_7 << endl;
           
           float Bin_l_7 = 0;
           if (B_l_7 > 0){
               Bin_l_7 =  2* ( (S_l_7 + B_l_7) * log(1+S_l_7/B_l_7) - S_l_7 );
               //Bin_l_7 = (S_l_7/sqrt(B_l_7))*(S_l_7/sqrt(B_l_7));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_7) << endl; //
           

           Sum_l_7 += Bin_l_7 ;
           QuadraticSum_l_7 = sqrt(Sum_l_7);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_7 << endl; //

           h71->SetBinContent(j,QuadraticSum_l_7);
           h71->SetLineColor(kBlue-9);
           h71->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h72 = new TH1F("h72","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_7 = 0;
       float B_r_7_0 = 0;
       float B_r_7_1 = 0;
       float B_r_7_2 = 0;
       float B_r_7_3 = 0;
       float B_r_7_4 = 0;
       float B_r_7_5 = 0;
       float B_r_7_6 = 0;
       float B_r_7_7 = 0;
       float B_r_7_8 = 0;
        
       float QuadraticSum_r_7 = 0;
       float Sum_r_7 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_7 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_7 << endl;
          B_r_7_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_7_8 << endl;
          B_r_7_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_7_7 << endl;
          B_r_7_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_7_6 << endl;
          B_r_7_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_7_5 << endl;
          B_r_7_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_7_4 << endl;
          B_r_7_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_7_3 << endl;
          B_r_7_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_7_2 << endl;
          B_r_7_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_7_1 << endl;
          B_r_7_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_7_0 << endl;
          
          float B_r_7 = 0;
          for(int i = 0; i<9; i++) { B_r_7 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_7 << endl;
          
          float Bin_r_7 = 0;
          if (B_r_7 > 0){
              Bin_r_7 =  2* ( (S_r_7 + B_r_7) * log(1+S_r_7/B_r_7) - S_r_7 );
              //Bin_r_7 = (S_r_7/sqrt(B_r_7))*(S_r_7/sqrt(B_r_7));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_7) << endl;
          

          Sum_r_7 += Bin_r_7 ;
          QuadraticSum_r_7 = sqrt(Sum_r_7);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_7 << endl;

          h72->SetBinContent(j,QuadraticSum_r_7);
          h72->SetLineColor(kGreen-9);
          h72->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax7 = 1.1*h71->GetMaximum();
    float scale7 = 5000 / rightmax7;
    h71->Scale(scale7);
    h71->Draw("SAMEHIST");
    
    h72->Scale(scale7);
    h72->Draw("SAMEHIST");
    

    TGaxis*axis7 = new TGaxis(2000,0,2000,5000,0,rightmax7,510,"+L");
    axis7->SetTitle("Quadratic Sum of significance");
    axis7->SetTitleSize(0.03);
    axis7->SetLabelSize(0.025);
    axis7->Draw();
    
    pad72[k]->cd();
    TLegend *leg7 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg7->SetBorderSize(1);
    leg7->SetFillColor(0);
    leg7->SetTextFont(42);
    leg7->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg7->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg7->AddEntry(h71, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg7->AddEntry(h72, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg7->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut7_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_7 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   dPhiHttMET   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut8 = 16;
    TCut cut8_1[n_cut8] = { "dPhiHttMET<0.2", "dPhiHttMET<0.4", "dPhiHttMET<0.6", "dPhiHttMET<0.8", "dPhiHttMET<1", "dPhiHttMET<1.2", "dPhiHttMET<1.4", "dPhiHttMET<1.6", "dPhiHttMET<1.8", "dPhiHttMET<2", "dPhiHttMET<2.2", "dPhiHttMET<2.4", "dPhiHttMET<2.6", "dPhiHttMET<2.8", "dPhiHttMET<3", "dPhiHttMET<3.2" };
    string cut8_2[n_cut8] = { "dPhiHttMET<0.2", "dPhiHttMET<0.4", "dPhiHttMET<0.6", "dPhiHttMET<0.8", "dPhiHttMET<1", "dPhiHttMET<1.2", "dPhiHttMET<1.4", "dPhiHttMET<1.6", "dPhiHttMET<1.8", "dPhiHttMET<2", "dPhiHttMET<2.2", "dPhiHttMET<2.4", "dPhiHttMET<2.6", "dPhiHttMET<2.8", "dPhiHttMET<3", "dPhiHttMET<3.2" };
    

      TCanvas *canvas8[n_cut8] ;
      canvas8[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas8[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas8[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas8[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas8[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas8[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas8[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas8[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas8[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas8[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas8[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas8[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas8[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas8[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas8[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas8[15] = new TCanvas ("c15", "Mhh",980,580);
    
      TPad *pad81[n_cut8];
      pad81[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad81[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad81[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad81[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad81[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad81[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad81[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad81[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad81[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad81[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad81[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad81[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad81[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad81[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad81[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad81[15] = new TPad ("pad15", "", 0,0,0.75,1);
    
      TPad *pad82[n_cut8];
      pad82[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad82[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad82[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad82[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad82[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad82[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad82[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad82[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad82[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad82[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad82[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad82[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad82[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad82[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad82[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad82[15] = new TPad ("pad15", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut8;k++) {
           canvas8[k]->cd();
           pad81[k]->Draw();
           pad82[k]->Draw();
           
           pad81[k]->cd();
           pad81[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut8_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut8_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut8_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut8_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut8_1[k]),  "SAMEHIST");
        }
        
        THStack *hs8 = new THStack("hs8", "");
        for(int i= 0; i<9 ; i++){ hs8->Add(h_hist[i], "hist1"); }
        hs8->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut8_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h81 = new TH1F("h81","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_8 = 0;
       float B_l_8_0 = 0;
       float B_l_8_1 = 0;
       float B_l_8_2 = 0;
       float B_l_8_3 = 0;
       float B_l_8_4 = 0;
       float B_l_8_5 = 0;
       float B_l_8_6 = 0;
       float B_l_8_7 = 0;
       float B_l_8_8 = 0;
        
       float QuadraticSum_l_8 = 0;
       float Sum_l_8 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_8 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_8 << endl;
           B_l_8_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_8_8 << endl;
           B_l_8_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_8_7 << endl;
           B_l_8_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_8_6 << endl;
           B_l_8_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_8_5 << endl;
           B_l_8_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_8_4 << endl;
           B_l_8_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_8_3 << endl;
           B_l_8_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_8_2 << endl;
           B_l_8_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_8_1 << endl;
           B_l_8_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_8_0 << endl;
           
           float B_l_8 = 0;
           for(int i = 0; i<9; i++) { B_l_8 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_8 << endl;
           
           float Bin_l_8 = 0;
           if (B_l_8 > 0){
               Bin_l_8 =  2* ( (S_l_8 + B_l_8) * log(1+S_l_8/B_l_8) - S_l_8 );
               //Bin_l_8 = (S_l_8/sqrt(B_l_8))*(S_l_8/sqrt(B_l_8));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_8) << endl; //
           

           Sum_l_8 += Bin_l_8 ;
           QuadraticSum_l_8 = sqrt(Sum_l_8);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_8 << endl; //

           h81->SetBinContent(j,QuadraticSum_l_8);
           h81->SetLineColor(kBlue-9);
           h81->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h82 = new TH1F("h82","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_8 = 0;
       float B_r_8_0 = 0;
       float B_r_8_1 = 0;
       float B_r_8_2 = 0;
       float B_r_8_3 = 0;
       float B_r_8_4 = 0;
       float B_r_8_5 = 0;
       float B_r_8_6 = 0;
       float B_r_8_7 = 0;
       float B_r_8_8 = 0;
        
       float QuadraticSum_r_8 = 0;
       float Sum_r_8 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_8 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_8 << endl;
          B_r_8_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_8_8 << endl;
          B_r_8_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_8_7 << endl;
          B_r_8_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_8_6 << endl;
          B_r_8_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_8_5 << endl;
          B_r_8_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_8_4 << endl;
          B_r_8_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_8_3 << endl;
          B_r_8_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_8_2 << endl;
          B_r_8_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_8_1 << endl;
          B_r_8_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_8_0 << endl;
          
          float B_r_8 = 0;
          for(int i = 0; i<9; i++) { B_r_8 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_8 << endl;
          
          float Bin_r_8 = 0;
          if (B_r_8 > 0){
              Bin_r_8 =  2* ( (S_r_8 + B_r_8) * log(1+S_r_8/B_r_8) - S_r_8 );
              //Bin_r_8 = (S_r_8/sqrt(B_r_8))*(S_r_8/sqrt(B_r_8));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_8) << endl;
          

          Sum_r_8 += Bin_r_8 ;
          QuadraticSum_r_8 = sqrt(Sum_r_8);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_8 << endl;

          h82->SetBinContent(j,QuadraticSum_r_8);
          h82->SetLineColor(kGreen-9);
          h82->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax8 = 1.1*h81->GetMaximum();
    float scale8 = 5000 / rightmax8;
    h81->Scale(scale8);
    h81->Draw("SAMEHIST");
    
    h82->Scale(scale8);
    h82->Draw("SAMEHIST");
    

    TGaxis*axis8 = new TGaxis(2000,0,2000,5000,0,rightmax8,510,"+L");
    axis8->SetTitle("Quadratic Sum of significance");
    axis8->SetTitleSize(0.03);
    axis8->SetLabelSize(0.025);
    axis8->Draw();
    
    pad82[k]->cd();
    TLegend *leg8 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg8->SetBorderSize(1);
    leg8->SetFillColor(0);
    leg8->SetTextFont(42);
    leg8->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg8->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg8->AddEntry(h81, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg8->AddEntry(h82, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg8->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut8_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_8 << endl;
        cout << "" << endl;
          
      }
    
    /*
    cout << " " << endl;
    cout << "  ===========================================================   dPhiLep0MET   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut9 = 16;
    TCut cut9_1[n_cut9] = { "dPhiLep0MET<0.2", "dPhiLep0MET<0.4", "dPhiLep0MET<0.6", "dPhiLep0MET<0.8", "dPhiLep0MET<1", "dPhiLep0MET<1.2", "dPhiLep0MET<1.4", "dPhiLep0MET<1.6", "dPhiLep0MET<1.8", "dPhiLep0MET<2", "dPhiLep0MET<2.2", "dPhiLep0MET<2.4", "dPhiLep0MET<2.6", "dPhiLep0MET<2.8", "dPhiLep0MET<3", "dPhiLep0MET<3.2" };
    string cut9_2[n_cut9] = { "dPhiLep0MET<0.2", "dPhiLep0MET<0.4", "dPhiLep0MET<0.6", "dPhiLep0MET<0.8", "dPhiLep0MET<1", "dPhiLep0MET<1.2", "dPhiLep0MET<1.4", "dPhiLep0MET<1.6", "dPhiLep0MET<1.8", "dPhiLep0MET<2", "dPhiLep0MET<2.2", "dPhiLep0MET<2.4", "dPhiLep0MET<2.6", "dPhiLep0MET<2.8", "dPhiLep0MET<3", "dPhiLep0MET<3.2" };
    

      TCanvas *canvas9[n_cut9] ;
      canvas9[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas9[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas9[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas9[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas9[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas9[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas9[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas9[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas9[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas9[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas9[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas9[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas9[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas9[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas9[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas9[15] = new TCanvas ("c15", "Mhh",980,580);
    
      TPad *pad91[n_cut9];
      pad91[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad91[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad91[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad91[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad91[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad91[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad91[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad91[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad91[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad91[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad91[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad91[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad91[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad91[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad91[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad91[15] = new TPad ("pad15", "", 0,0,0.75,1);
    
      TPad *pad92[n_cut9];
      pad92[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad92[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad92[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad92[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad92[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad92[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad92[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad92[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad92[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad92[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad92[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad92[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad92[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad92[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad92[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad92[15] = new TPad ("pad15", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut9;k++) {
           canvas9[k]->cd();
           pad91[k]->Draw();
           pad92[k]->Draw();
           
           pad91[k]->cd();
           pad91[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut9_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut9_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut9_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut9_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut9_1[k]),  "SAMEHIST");
        }
        
        THStack *hs9 = new THStack("hs9", "");
        for(int i= 0; i<9 ; i++){ hs9->Add(h_hist[i], "hist1"); }
        hs9->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut9_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h91 = new TH1F("h91","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_9 = 0;
       float B_l_9_0 = 0;
       float B_l_9_1 = 0;
       float B_l_9_2 = 0;
       float B_l_9_3 = 0;
       float B_l_9_4 = 0;
       float B_l_9_5 = 0;
       float B_l_9_6 = 0;
       float B_l_9_7 = 0;
       float B_l_9_8 = 0;
        
       float QuadraticSum_l_9 = 0;
       float Sum_l_9 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_9 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_9 << endl;
           B_l_9_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_9_8 << endl;
           B_l_9_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_9_7 << endl;
           B_l_9_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_9_6 << endl;
           B_l_9_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_9_5 << endl;
           B_l_9_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_9_4 << endl;
           B_l_9_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_9_3 << endl;
           B_l_9_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_9_2 << endl;
           B_l_9_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_9_1 << endl;
           B_l_9_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_9_0 << endl;
           
           float B_l_9 = 0;
           for(int i = 0; i<9; i++) { B_l_9 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_9 << endl;
           
           float Bin_l_9 = 0;
           if (B_l_9 > 0){
               Bin_l_9 =  2* ( (S_l_9 + B_l_9) * log(1+S_l_9/B_l_9) - S_l_9 );
               //Bin_l_9 = (S_l_9/sqrt(B_l_9))*(S_l_9/sqrt(B_l_9));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_9) << endl; //
           

           Sum_l_9 += Bin_l_9 ;
           QuadraticSum_l_9 = sqrt(Sum_l_9);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_9 << endl; //

           h91->SetBinContent(j,QuadraticSum_l_9);
           h91->SetLineColor(kBlue-9);
           h91->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h92 = new TH1F("h92","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_9 = 0;
       float B_r_9_0 = 0;
       float B_r_9_1 = 0;
       float B_r_9_2 = 0;
       float B_r_9_3 = 0;
       float B_r_9_4 = 0;
       float B_r_9_5 = 0;
       float B_r_9_6 = 0;
       float B_r_9_7 = 0;
       float B_r_9_8 = 0;
        
       float QuadraticSum_r_9 = 0;
       float Sum_r_9 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_9 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_9 << endl;
          B_r_9_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_9_8 << endl;
          B_r_9_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_9_7 << endl;
          B_r_9_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_9_6 << endl;
          B_r_9_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_9_5 << endl;
          B_r_9_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_9_4 << endl;
          B_r_9_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_9_3 << endl;
          B_r_9_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_9_2 << endl;
          B_r_9_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_9_1 << endl;
          B_r_9_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_9_0 << endl;
          
          float B_r_9 = 0;
          for(int i = 0; i<9; i++) { B_r_9 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_9 << endl;
          
          float Bin_r_9 = 0;
          if (B_r_9 > 0){
              Bin_r_9 =  2* ( (S_r_9 + B_r_9) * log(1+S_r_9/B_r_9) - S_r_9 );
              //Bin_r_9 = (S_r_9/sqrt(B_r_9))*(S_r_9/sqrt(B_r_9));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_9) << endl;
          

          Sum_r_9 += Bin_r_9 ;
          QuadraticSum_r_9 = sqrt(Sum_r_9);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_9 << endl;

          h92->SetBinContent(j,QuadraticSum_r_9);
          h92->SetLineColor(kGreen-9);
          h92->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax9 = 1.1*h91->GetMaximum();
    float scale9 = 5000 / rightmax9;
    h91->Scale(scale9);
    h91->Draw("SAMEHIST");
    
    h92->Scale(scale9);
    h92->Draw("SAMEHIST");
    

    TGaxis*axis9 = new TGaxis(2000,0,2000,5000,0,rightmax9,510,"+L");
    axis9->SetTitle("Quadratic Sum of significance");
    axis9->SetTitleSize(0.03);
    axis9->SetLabelSize(0.025);
    axis9->Draw();
    
    pad92[k]->cd();
    TLegend *leg9 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg9->SetBorderSize(1);
    leg9->SetFillColor(0);
    leg9->SetTextFont(42);
    leg9->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg9->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg9->AddEntry(h91, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg9->AddEntry(h92, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg9->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut9_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_9 << endl;
        cout << "" << endl;
          
      }
    */
    
    cout << " " << endl;
    cout << "  ===========================================================   dPhiLep1MET   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut10 = 16;
    TCut cut10_1[n_cut10] = { "dPhiLep1MET<0.2", "dPhiLep1MET<0.4", "dPhiLep1MET<0.6", "dPhiLep1MET<0.8", "dPhiLep1MET<1", "dPhiLep1MET<1.2", "dPhiLep1MET<1.4", "dPhiLep1MET<1.6", "dPhiLep1MET<1.8", "dPhiLep1MET<2", "dPhiLep1MET<2.2", "dPhiLep1MET<2.4", "dPhiLep1MET<2.6", "dPhiLep1MET<2.8", "dPhiLep1MET<3", "dPhiLep1MET<3.2" };
    string cut10_2[n_cut10] = { "dPhiLep1MET<0.2", "dPhiLep1MET<0.4", "dPhiLep1MET<0.6", "dPhiLep1MET<0.8", "dPhiLep1MET<1", "dPhiLep1MET<1.2", "dPhiLep1MET<1.4", "dPhiLep1MET<1.6", "dPhiLep1MET<1.8", "dPhiLep1MET<2", "dPhiLep1MET<2.2", "dPhiLep1MET<2.4", "dPhiLep1MET<2.6", "dPhiLep1MET<2.8", "dPhiLep1MET<3", "dPhiLep1MET<3.2" };
    

      TCanvas *canvas10[n_cut10] ;
      canvas10[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas10[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas10[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas10[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas10[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas10[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas10[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas10[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas10[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas10[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas10[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas10[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas10[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas10[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas10[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas10[15] = new TCanvas ("c15", "Mhh",980,580);
    
      TPad *pad101[n_cut10];
      pad101[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad101[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad101[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad101[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad101[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad101[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad101[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad101[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad101[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad101[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad101[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad101[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad101[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad101[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad101[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad101[15] = new TPad ("pad15", "", 0,0,0.75,1);
    
      TPad *pad102[n_cut10];
      pad102[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad102[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad102[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad102[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad102[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad102[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad102[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad102[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad102[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad102[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad102[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad102[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad102[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad102[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad102[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad102[15] = new TPad ("pad15", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut10;k++) {
           canvas10[k]->cd();
           pad101[k]->Draw();
           pad102[k]->Draw();
           
           pad101[k]->cd();
           pad101[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut10_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut10_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut10_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut10_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut10_1[k]),  "SAMEHIST");
        }
        
        THStack *hs10 = new THStack("hs10", "");
        for(int i= 0; i<9 ; i++){ hs10->Add(h_hist[i], "hist1"); }
        hs10->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut10_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h101 = new TH1F("h101","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_10 = 0;
       float B_l_10_0 = 0;
       float B_l_10_1 = 0;
       float B_l_10_2 = 0;
       float B_l_10_3 = 0;
       float B_l_10_4 = 0;
       float B_l_10_5 = 0;
       float B_l_10_6 = 0;
       float B_l_10_7 = 0;
       float B_l_10_8 = 0;
        
       float QuadraticSum_l_10 = 0;
       float Sum_l_10 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_10 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_10 << endl;
           B_l_10_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_10_8 << endl;
           B_l_10_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_10_7 << endl;
           B_l_10_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_10_6 << endl;
           B_l_10_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_10_5 << endl;
           B_l_10_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_10_4 << endl;
           B_l_10_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_10_3 << endl;
           B_l_10_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_10_2 << endl;
           B_l_10_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_10_1 << endl;
           B_l_10_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_10_0 << endl;
           
           float B_l_10 = 0;
           for(int i = 0; i<9; i++) { B_l_10 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_10 << endl;
           
           float Bin_l_10 = 0;
           if (B_l_10 > 0){
               Bin_l_10 =  2* ( (S_l_10 + B_l_10) * log(1+S_l_10/B_l_10) - S_l_10 );
               //Bin_l_10 = (S_l_10/sqrt(B_l_10))*(S_l_10/sqrt(B_l_10));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_10) << endl; //
           

           Sum_l_10 += Bin_l_10 ;
           QuadraticSum_l_10 = sqrt(Sum_l_10);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_10 << endl; //

           h101->SetBinContent(j,QuadraticSum_l_10);
           h101->SetLineColor(kBlue-9);
           h101->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h102 = new TH1F("h102","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_10 = 0;
       float B_r_10_0 = 0;
       float B_r_10_1 = 0;
       float B_r_10_2 = 0;
       float B_r_10_3 = 0;
       float B_r_10_4 = 0;
       float B_r_10_5 = 0;
       float B_r_10_6 = 0;
       float B_r_10_7 = 0;
       float B_r_10_8 = 0;
        
       float QuadraticSum_r_10 = 0;
       float Sum_r_10 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_10 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_10 << endl;
          B_r_10_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_10_8 << endl;
          B_r_10_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_10_7 << endl;
          B_r_10_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_10_6 << endl;
          B_r_10_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_10_5 << endl;
          B_r_10_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_10_4 << endl;
          B_r_10_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_10_3 << endl;
          B_r_10_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_10_2 << endl;
          B_r_10_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_10_1 << endl;
          B_r_10_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_10_0 << endl;
          
          float B_r_10 = 0;
          for(int i = 0; i<9; i++) { B_r_10 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_10 << endl;
          
          float Bin_r_10 = 0;
          if (B_r_10 > 0){
              Bin_r_10 =  2* ( (S_r_10 + B_r_10) * log(1+S_r_10/B_r_10) - S_r_10 );
              //Bin_r_10 = (S_r_10/sqrt(B_r_10))*(S_r_10/sqrt(B_r_10));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_10) << endl;
          

          Sum_r_10 += Bin_r_10 ;
          QuadraticSum_r_10 = sqrt(Sum_r_10);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_10 << endl;

          h102->SetBinContent(j,QuadraticSum_r_10);
          h102->SetLineColor(kGreen-9);
          h102->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax10 = 1.1*h101->GetMaximum();
    float scale10 = 5000 / rightmax10;
    h101->Scale(scale10);
    h101->Draw("SAMEHIST");
    
    h102->Scale(scale10);
    h102->Draw("SAMEHIST");
    

    TGaxis*axis10 = new TGaxis(2000,0,2000,5000,0,rightmax10,510,"+L");
    axis10->SetTitle("Quadratic Sum of significance");
    axis10->SetTitleSize(0.03);
    axis10->SetLabelSize(0.025);
    axis10->Draw();
    
    pad102[k]->cd();
    TLegend *leg10 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg10->SetBorderSize(1);
    leg10->SetFillColor(0);
    leg10->SetTextFont(42);
    leg10->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg10->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg10->AddEntry(h101, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg10->AddEntry(h102, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg10->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut10_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_10 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   dPhiLepTau_abs   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut11 = 16;
    TCut cut11_1[n_cut11] = { "abs(dPhiLepTau)<0.2", "abs(dPhiLepTau)<0.4", "abs(dPhiLepTau)<0.6", "abs(dPhiLepTau)<0.8", "abs(dPhiLepTau)<1", "abs(dPhiLepTau)<1.2", "abs(dPhiLepTau)<1.4", "abs(dPhiLepTau)<1.6", "abs(dPhiLepTau)<1.8", "abs(dPhiLepTau)<2", "abs(dPhiLepTau)<2.2", "abs(dPhiLepTau)<2.4", "abs(dPhiLepTau)<2.6", "abs(dPhiLepTau)<2.8", "abs(dPhiLepTau)<3", "abs(dPhiLepTau)<3.2" };
    string cut11_2[n_cut11] = { "abs(dPhiLepTau)<0.2", "abs(dPhiLepTau)<0.4", "abs(dPhiLepTau)<0.6", "abs(dPhiLepTau)<0.8", "abs(dPhiLepTau)<1", "abs(dPhiLepTau)<1.2", "abs(dPhiLepTau)<1.4", "abs(dPhiLepTau)<1.6", "abs(dPhiLepTau)<1.8", "abs(dPhiLepTau)<2", "abs(dPhiLepTau)<2.2", "abs(dPhiLepTau)<2.4", "abs(dPhiLepTau)<2.6", "abs(dPhiLepTau)<2.8", "abs(dPhiLepTau)<3", "abs(dPhiLepTau)<3.2" };
    

      TCanvas *canvas11[n_cut11] ;
      canvas11[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas11[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas11[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas11[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas11[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas11[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas11[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas11[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas11[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas11[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas11[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas11[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas11[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas11[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas11[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas11[15] = new TCanvas ("c15", "Mhh",980,580);
    
      TPad *pad111[n_cut11];
      pad111[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad111[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad111[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad111[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad111[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad111[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad111[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad111[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad111[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad111[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad111[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad111[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad111[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad111[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad111[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad111[15] = new TPad ("pad15", "", 0,0,0.75,1);
    
      TPad *pad112[n_cut11];
      pad112[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad112[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad112[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad112[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad112[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad112[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad112[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad112[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad112[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad112[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad112[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad112[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad112[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad112[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad112[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad112[15] = new TPad ("pad15", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut11;k++) {
           canvas11[k]->cd();
           pad111[k]->Draw();
           pad112[k]->Draw();
           
           pad111[k]->cd();
           pad111[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut11_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut11_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut11_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut11_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut11_1[k]),  "SAMEHIST");
        }
        
        THStack *hs11 = new THStack("hs11", "");
        for(int i= 0; i<9 ; i++){ hs11->Add(h_hist[i], "hist1"); }
        hs11->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut11_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h111 = new TH1F("h111","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_11 = 0;
       float B_l_11_0 = 0;
       float B_l_11_1 = 0;
       float B_l_11_2 = 0;
       float B_l_11_3 = 0;
       float B_l_11_4 = 0;
       float B_l_11_5 = 0;
       float B_l_11_6 = 0;
       float B_l_11_7 = 0;
       float B_l_11_8 = 0;
        
       float QuadraticSum_l_11 = 0;
       float Sum_l_11 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_11 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_11 << endl;
           B_l_11_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_11_8 << endl;
           B_l_11_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_11_7 << endl;
           B_l_11_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_11_6 << endl;
           B_l_11_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_11_5 << endl;
           B_l_11_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_11_4 << endl;
           B_l_11_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_11_3 << endl;
           B_l_11_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_11_2 << endl;
           B_l_11_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_11_1 << endl;
           B_l_11_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_11_0 << endl;
           
           float B_l_11 = 0;
           for(int i = 0; i<9; i++) { B_l_11 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_11 << endl;
           
           float Bin_l_11 = 0;
           if (B_l_11 > 0){
               Bin_l_11 =  2* ( (S_l_11 + B_l_11) * log(1+S_l_11/B_l_11) - S_l_11 );
               //Bin_l_11 = (S_l_11/sqrt(B_l_11))*(S_l_11/sqrt(B_l_11));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_11) << endl; //
           

           Sum_l_11 += Bin_l_11 ;
           QuadraticSum_l_11 = sqrt(Sum_l_11);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_11 << endl; //

           h111->SetBinContent(j,QuadraticSum_l_11);
           h111->SetLineColor(kBlue-9);
           h111->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h112 = new TH1F("h112","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_11 = 0;
       float B_r_11_0 = 0;
       float B_r_11_1 = 0;
       float B_r_11_2 = 0;
       float B_r_11_3 = 0;
       float B_r_11_4 = 0;
       float B_r_11_5 = 0;
       float B_r_11_6 = 0;
       float B_r_11_7 = 0;
       float B_r_11_8 = 0;
        
       float QuadraticSum_r_11 = 0;
       float Sum_r_11 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_11 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_11 << endl;
          B_r_11_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_11_8 << endl;
          B_r_11_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_11_7 << endl;
          B_r_11_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_11_6 << endl;
          B_r_11_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_11_5 << endl;
          B_r_11_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_11_4 << endl;
          B_r_11_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_11_3 << endl;
          B_r_11_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_11_2 << endl;
          B_r_11_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_11_1 << endl;
          B_r_11_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_11_0 << endl;
          
          float B_r_11 = 0;
          for(int i = 0; i<9; i++) { B_r_11 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_11 << endl;
          
          float Bin_r_11 = 0;
          if (B_r_11 > 0){
              Bin_r_11 =  2* ( (S_r_11 + B_r_11) * log(1+S_r_11/B_r_11) - S_r_11 );
              //Bin_r_11 = (S_r_11/sqrt(B_r_11))*(S_r_11/sqrt(B_r_11));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_11) << endl;
          

          Sum_r_11 += Bin_r_11 ;
          QuadraticSum_r_11 = sqrt(Sum_r_11);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_11 << endl;

          h112->SetBinContent(j,QuadraticSum_r_11);
          h112->SetLineColor(kGreen-9);
          h112->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax11 = 1.1*h111->GetMaximum();
    float scale11 = 5000 / rightmax11;
    h111->Scale(scale11);
    h111->Draw("SAMEHIST");
    
    h112->Scale(scale11);
    h112->Draw("SAMEHIST");
    

    TGaxis*axis11 = new TGaxis(2000,0,2000,5000,0,rightmax11,510,"+L");
    axis11->SetTitle("Quadratic Sum of significance");
    axis11->SetTitleSize(0.03);
    axis11->SetLabelSize(0.025);
    axis11->Draw();
    
    pad112[k]->cd();
    TLegend *leg11 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg11->SetBorderSize(1);
    leg11->SetFillColor(0);
    leg11->SetTextFont(42);
    leg11->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg11->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg11->AddEntry(h111, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg11->AddEntry(h112, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg11->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut11_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_11 << endl;
        cout << "" << endl;
          
      }
    
    
    
    cout << " " << endl;
    cout << "  ===========================================================   dPtLepTau   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut13 = 26;
    TCut cut13_1[n_cut13] = { "dPtLepTau<10000", "dPtLepTau<20000", "dPtLepTau<30000", "dPtLepTau<40000", "dPtLepTau<50000", "dPtLepTau<60000", "dPtLepTau<70000", "dPtLepTau<80000", "dPtLepTau<90000", "dPtLepTau<100000", "dPtLepTau<110000", "dPtLepTau<120000", "dPtLepTau<130000", "dPtLepTau<140000", "dPtLepTau<150000", "dPtLepTau<160000", "dPtLepTau<170000", "dPtLepTau<180000", "dPtLepTau<190000","dPtLepTau<200000", "dPtLepTau<210000", "dPtLepTau<220000", "dPtLepTau<230000", "dPtLepTau<240000", "dPtLepTau<250000", "dPtLepTau<260000" };
    string cut13_2[n_cut13] = { "dPtLepTau<10GeV", "dPtLepTau<20GeV", "dPtLepTau<30GeV", "dPtLepTau<40GeV", "dPtLepTau<50GeV", "dPtLepTau<60GeV", "dPtLepTau<70GeV", "dPtLepTau<80GeV", "dPtLepTau<90GeV", "dPtLepTau<100GeV", "dPtLepTau<110GeV", "dPtLepTau<120GeV", "dPtLepTau<130GeV", "dPtLepTau<140GeV", "dPtLepTau<150GeV", "dPtLepTau<160GeV", "dPtLepTau<170GeV", "dPtLepTau<180GeV", "dPtLepTau<190GeV","dPtLepTau<200GeV", "dPtLepTau<210GeV", "dPtLepTau<220GeV", "dPtLepTau<230GeV", "dPtLepTau<240GeV", "dPtLepTau<250GeV", "dPtLepTau<260GeV" };
    

      TCanvas *canvas13[n_cut13] ;
      canvas13[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas13[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas13[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas13[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas13[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas13[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas13[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas13[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas13[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas13[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas13[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas13[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas13[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas13[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas13[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas13[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas13[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas13[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas13[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas13[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas13[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas13[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas13[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas13[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas13[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas13[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad131[n_cut13];
      pad131[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad131[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad131[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad131[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad131[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad131[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad131[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad131[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad131[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad131[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad131[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad131[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad131[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad131[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad131[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad131[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad131[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad131[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad131[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad131[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad131[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad131[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad131[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad131[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad131[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad131[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad132[n_cut13];
      pad132[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad132[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad132[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad132[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad132[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad132[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad132[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad132[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad132[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad132[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad132[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad132[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad132[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad132[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad132[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad132[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad132[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad132[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad132[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad132[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad132[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad132[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad132[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad132[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad132[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad132[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut13;k++) {
           canvas13[k]->cd();
           pad131[k]->Draw();
           pad132[k]->Draw();
           
           pad131[k]->cd();
           pad131[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut13_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut13_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut13_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut13_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut13_1[k]),  "SAMEHIST");
        }
        
        THStack *hs13 = new THStack("hs13", "");
        for(int i= 0; i<9 ; i++){ hs13->Add(h_hist[i], "hist1"); }
        hs13->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut13_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h131 = new TH1F("h131","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_13 = 0;
       float B_l_13_0 = 0;
       float B_l_13_1 = 0;
       float B_l_13_2 = 0;
       float B_l_13_3 = 0;
       float B_l_13_4 = 0;
       float B_l_13_5 = 0;
       float B_l_13_6 = 0;
       float B_l_13_7 = 0;
       float B_l_13_8 = 0;
        
       float QuadraticSum_l_13 = 0;
       float Sum_l_13 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_13 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_13 << endl;
           B_l_13_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_13_8 << endl;
           B_l_13_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_13_7 << endl;
           B_l_13_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_13_6 << endl;
           B_l_13_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_13_5 << endl;
           B_l_13_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_13_4 << endl;
           B_l_13_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_13_3 << endl;
           B_l_13_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_13_2 << endl;
           B_l_13_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_13_1 << endl;
           B_l_13_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_13_0 << endl;
           
           float B_l_13 = 0;
           for(int i = 0; i<9; i++) { B_l_13 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_13 << endl;
           
           float Bin_l_13 = 0;
           if (B_l_13 > 0){
               Bin_l_13 =  2* ( (S_l_13 + B_l_13) * log(1+S_l_13/B_l_13) - S_l_13 );
               //Bin_l_13 = (S_l_13/sqrt(B_l_13))*(S_l_13/sqrt(B_l_13));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_13) << endl; //
           

           Sum_l_13 += Bin_l_13 ;
           QuadraticSum_l_13 = sqrt(Sum_l_13);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_13 << endl; //

           h131->SetBinContent(j,QuadraticSum_l_13);
           h131->SetLineColor(kBlue-9);
           h131->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h132 = new TH1F("h132","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_13 = 0;
       float B_r_13_0 = 0;
       float B_r_13_1 = 0;
       float B_r_13_2 = 0;
       float B_r_13_3 = 0;
       float B_r_13_4 = 0;
       float B_r_13_5 = 0;
       float B_r_13_6 = 0;
       float B_r_13_7 = 0;
       float B_r_13_8 = 0;
        
       float QuadraticSum_r_13 = 0;
       float Sum_r_13 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_13 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_13 << endl;
          B_r_13_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_13_8 << endl;
          B_r_13_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_13_7 << endl;
          B_r_13_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_13_6 << endl;
          B_r_13_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_13_5 << endl;
          B_r_13_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_13_4 << endl;
          B_r_13_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_13_3 << endl;
          B_r_13_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_13_2 << endl;
          B_r_13_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_13_1 << endl;
          B_r_13_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_13_0 << endl;
          
          float B_r_13 = 0;
          for(int i = 0; i<9; i++) { B_r_13 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_13 << endl;
          
          float Bin_r_13 = 0;
          if (B_r_13 > 0){
              Bin_r_13 =  2* ( (S_r_13 + B_r_13) * log(1+S_r_13/B_r_13) - S_r_13 );
              //Bin_r_13 = (S_r_13/sqrt(B_r_13))*(S_r_13/sqrt(B_r_13));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_13) << endl;
          

          Sum_r_13 += Bin_r_13 ;
          QuadraticSum_r_13 = sqrt(Sum_r_13);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_13 << endl;

          h132->SetBinContent(j,QuadraticSum_r_13);
          h132->SetLineColor(kGreen-9);
          h132->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax13 = 1.1*h131->GetMaximum();
    float scale13 = 5000 / rightmax13;
    h131->Scale(scale13);
    h131->Draw("SAMEHIST");
    
    h132->Scale(scale13);
    h132->Draw("SAMEHIST");
    

    TGaxis*axis13 = new TGaxis(2000,0,2000,5000,0,rightmax13,510,"+L");
    axis13->SetTitle("Quadratic Sum of significance");
    axis13->SetTitleSize(0.03);
    axis13->SetLabelSize(0.025);
    axis13->Draw();
    
    pad132[k]->cd();
    TLegend *leg13 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg13->SetBorderSize(1);
    leg13->SetFillColor(0);
    leg13->SetTextFont(42);
    leg13->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg13->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg13->AddEntry(h131, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg13->AddEntry(h132, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg13->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut13_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_13 << endl;
        cout << "" << endl;
          
      }
    
    
    
    cout << " " << endl;
    cout << "  ===========================================================   dRBB   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut16 = 15;
    TCut cut16_1[n_cut16] = { "dRBB<1 ", "dRBB<1.2", "dRBB<1.4", "dRBB<1.6", "dRBB<1.8", "dRBB<2", "dRBB<2.2", "dRBB<2.4", "dRBB<2.6", "dRBB<2.8", "dRBB<3", "dRBB<3.2", "dRBB<3.4", "dRBB<3.6", "dRBB<3.8" };
    string cut16_2[n_cut16] = { "dRBB<1 ", "dRBB<1.2", "dRBB<1.4", "dRBB<1.6", "dRBB<1.8", "dRBB<2", "dRBB<2.2", "dRBB<2.4", "dRBB<2.6", "dRBB<2.8", "dRBB<3", "dRBB<3.2", "dRBB<3.4", "dRBB<3.6", "dRBB<3.8" };
    

      TCanvas *canvas16[n_cut16] ;
      canvas16[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas16[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas16[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas16[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas16[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas16[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas16[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas16[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas16[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas16[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas16[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas16[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas16[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas16[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas16[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad161[n_cut16];
      pad161[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad161[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad161[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad161[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad161[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad161[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad161[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad161[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad161[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad161[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad161[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad161[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad161[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad161[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad161[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad162[n_cut16];
      pad162[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad162[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad162[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad162[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad162[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad162[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad162[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad162[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad162[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad162[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad162[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad162[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad162[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad162[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad162[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut16;k++) {
           canvas16[k]->cd();
           pad161[k]->Draw();
           pad162[k]->Draw();
           
           pad161[k]->cd();
           pad161[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut16_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut16_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut16_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut16_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut16_1[k]),  "SAMEHIST");
        }
        
        THStack *hs16 = new THStack("hs16", "");
        for(int i= 0; i<9 ; i++){ hs16->Add(h_hist[i], "hist1"); }
        hs16->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut16_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h161 = new TH1F("h161","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_16 = 0;
       float B_l_16_0 = 0;
       float B_l_16_1 = 0;
       float B_l_16_2 = 0;
       float B_l_16_3 = 0;
       float B_l_16_4 = 0;
       float B_l_16_5 = 0;
       float B_l_16_6 = 0;
       float B_l_16_7 = 0;
       float B_l_16_8 = 0;
        
       float QuadraticSum_l_16 = 0;
       float Sum_l_16 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_16 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_16 << endl;
           B_l_16_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_16_8 << endl;
           B_l_16_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_16_7 << endl;
           B_l_16_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_16_6 << endl;
           B_l_16_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_16_5 << endl;
           B_l_16_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_16_4 << endl;
           B_l_16_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_16_3 << endl;
           B_l_16_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_16_2 << endl;
           B_l_16_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_16_1 << endl;
           B_l_16_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_16_0 << endl;
           
           float B_l_16 = 0;
           for(int i = 0; i<9; i++) { B_l_16 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_16 << endl;
           
           float Bin_l_16 = 0;
           if (B_l_16 > 0){
               Bin_l_16 =  2* ( (S_l_16 + B_l_16) * log(1+S_l_16/B_l_16) - S_l_16 );
               //Bin_l_16 = (S_l_16/sqrt(B_l_16))*(S_l_16/sqrt(B_l_16));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_16) << endl; //
           

           Sum_l_16 += Bin_l_16 ;
           QuadraticSum_l_16 = sqrt(Sum_l_16);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_16 << endl; //

           h161->SetBinContent(j,QuadraticSum_l_16);
           h161->SetLineColor(kBlue-9);
           h161->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h162 = new TH1F("h162","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_16 = 0;
       float B_r_16_0 = 0;
       float B_r_16_1 = 0;
       float B_r_16_2 = 0;
       float B_r_16_3 = 0;
       float B_r_16_4 = 0;
       float B_r_16_5 = 0;
       float B_r_16_6 = 0;
       float B_r_16_7 = 0;
       float B_r_16_8 = 0;
        
       float QuadraticSum_r_16 = 0;
       float Sum_r_16 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_16 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_16 << endl;
          B_r_16_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_16_8 << endl;
          B_r_16_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_16_7 << endl;
          B_r_16_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_16_6 << endl;
          B_r_16_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_16_5 << endl;
          B_r_16_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_16_4 << endl;
          B_r_16_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_16_3 << endl;
          B_r_16_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_16_2 << endl;
          B_r_16_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_16_1 << endl;
          B_r_16_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_16_0 << endl;
          
          float B_r_16 = 0;
          for(int i = 0; i<9; i++) { B_r_16 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_16 << endl;
          
          float Bin_r_16 = 0;
          if (B_r_16 > 0){
              Bin_r_16 =  2* ( (S_r_16 + B_r_16) * log(1+S_r_16/B_r_16) - S_r_16 );
              //Bin_r_16 = (S_r_16/sqrt(B_r_16))*(S_r_16/sqrt(B_r_16));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_16) << endl;
          

          Sum_r_16 += Bin_r_16 ;
          QuadraticSum_r_16 = sqrt(Sum_r_16);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_16 << endl;

          h162->SetBinContent(j,QuadraticSum_r_16);
          h162->SetLineColor(kGreen-9);
          h162->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax16 = 1.1*h161->GetMaximum();
    float scale16 = 5000 / rightmax16;
    h161->Scale(scale16);
    h161->Draw("SAMEHIST");
    
    h162->Scale(scale16);
    h162->Draw("SAMEHIST");
    

    TGaxis*axis16 = new TGaxis(2000,0,2000,5000,0,rightmax16,510,"+L");
    axis16->SetTitle("Quadratic Sum of significance");
    axis16->SetTitleSize(0.03);
    axis16->SetLabelSize(0.025);
    axis16->Draw();
    
    pad162[k]->cd();
    TLegend *leg16 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg16->SetBorderSize(1);
    leg16->SetFillColor(0);
    leg16->SetTextFont(42);
    leg16->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg16->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg16->AddEntry(h161, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg16->AddEntry(h162, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg16->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut16_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_16 << endl;
        cout << "" << endl;
          
      }
     
   
    cout << " " << endl;
    cout << "  ===========================================================   dRHH   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut17 = 26;
    TCut cut17_1[n_cut17] = { "dRHH>1 ", "dRHH>1.2", "dRHH>1.4", "dRHH>1.6", "dRHH>1.8", "dRHH>2", "dRHH>2.2", "dRHH>2.4", "dRHH>2.6", "dRHH>2.8", "dRHH>3", "dRHH>3.2", "dRHH>3.4", "dRHH>3.6", "dRHH>3.8", "dRHH>4", "dRHH>4.2", "dRHH>4.4", "dRHH>4.6","dRHH>4.8", "dRHH>5", "dRHH>5.2", "dRHH>5.4", "dRHH>5.6", "dRHH>5.8", "dRHH>6" };
    string cut17_2[n_cut17] = { "dRHH>1 ", "dRHH>1.2", "dRHH>1.4", "dRHH>1.6", "dRHH>1.8", "dRHH>2", "dRHH>2.2", "dRHH>2.4", "dRHH>2.6", "dRHH>2.8", "dRHH>3", "dRHH>3.2", "dRHH>3.4", "dRHH>3.6", "dRHH>3.8", "dRHH>4", "dRHH>4.2", "dRHH>4.4", "dRHH>4.6","dRHH>4.8", "dRHH>5", "dRHH>5.2", "dRHH>5.4", "dRHH>5.6", "dRHH>5.8", "dRHH>6" };
    

      TCanvas *canvas17[n_cut17] ;
      canvas17[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas17[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas17[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas17[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas17[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas17[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas17[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas17[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas17[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas17[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas17[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas17[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas17[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas17[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas17[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas17[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas17[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas17[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas17[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas17[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas17[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas17[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas17[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas17[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas17[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas17[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad171[n_cut17];
      pad171[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad171[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad171[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad171[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad171[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad171[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad171[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad171[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad171[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad171[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad171[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad171[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad171[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad171[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad171[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad171[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad171[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad171[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad171[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad171[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad171[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad171[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad171[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad171[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad171[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad171[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad172[n_cut17];
      pad172[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad172[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad172[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad172[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad172[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad172[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad172[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad172[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad172[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad172[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad172[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad172[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad172[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad172[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad172[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad172[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad172[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad172[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad172[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad172[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad172[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad172[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad172[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad172[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad172[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad172[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut17;k++) {
           canvas17[k]->cd();
           pad171[k]->Draw();
           pad172[k]->Draw();
           
           pad171[k]->cd();
           pad171[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut17_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut17_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut17_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut17_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut17_1[k]),  "SAMEHIST");
        }
        
        THStack *hs17 = new THStack("hs17", "");
        for(int i= 0; i<9 ; i++){ hs17->Add(h_hist[i], "hist1"); }
        hs17->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut17_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h171 = new TH1F("h171","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_17 = 0;
       float B_l_17_0 = 0;
       float B_l_17_1 = 0;
       float B_l_17_2 = 0;
       float B_l_17_3 = 0;
       float B_l_17_4 = 0;
       float B_l_17_5 = 0;
       float B_l_17_6 = 0;
       float B_l_17_7 = 0;
       float B_l_17_8 = 0;
        
       float QuadraticSum_l_17 = 0;
       float Sum_l_17 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_17 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_17 << endl;
           B_l_17_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_17_8 << endl;
           B_l_17_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_17_7 << endl;
           B_l_17_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_17_6 << endl;
           B_l_17_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_17_5 << endl;
           B_l_17_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_17_4 << endl;
           B_l_17_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_17_3 << endl;
           B_l_17_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_17_2 << endl;
           B_l_17_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_17_1 << endl;
           B_l_17_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_17_0 << endl;
           
           float B_l_17 = 0;
           for(int i = 0; i<9; i++) { B_l_17 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_17 << endl;
           
           float Bin_l_17 = 0;
           if (B_l_17 > 0){
               Bin_l_17 =  2* ( (S_l_17 + B_l_17) * log(1+S_l_17/B_l_17) - S_l_17 );
               //Bin_l_17 = (S_l_17/sqrt(B_l_17))*(S_l_17/sqrt(B_l_17));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_17) << endl; //
           

           Sum_l_17 += Bin_l_17 ;
           QuadraticSum_l_17 = sqrt(Sum_l_17);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_17 << endl; //

           h171->SetBinContent(j,QuadraticSum_l_17);
           h171->SetLineColor(kBlue-9);
           h171->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h172 = new TH1F("h172","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_17 = 0;
       float B_r_17_0 = 0;
       float B_r_17_1 = 0;
       float B_r_17_2 = 0;
       float B_r_17_3 = 0;
       float B_r_17_4 = 0;
       float B_r_17_5 = 0;
       float B_r_17_6 = 0;
       float B_r_17_7 = 0;
       float B_r_17_8 = 0;
        
       float QuadraticSum_r_17 = 0;
       float Sum_r_17 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_17 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_17 << endl;
          B_r_17_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_17_8 << endl;
          B_r_17_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_17_7 << endl;
          B_r_17_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_17_6 << endl;
          B_r_17_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_17_5 << endl;
          B_r_17_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_17_4 << endl;
          B_r_17_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_17_3 << endl;
          B_r_17_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_17_2 << endl;
          B_r_17_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_17_1 << endl;
          B_r_17_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_17_0 << endl;
          
          float B_r_17 = 0;
          for(int i = 0; i<9; i++) { B_r_17 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_17 << endl;
          
          float Bin_r_17 = 0;
          if (B_r_17 > 0){
              Bin_r_17 =  2* ( (S_r_17 + B_r_17) * log(1+S_r_17/B_r_17) - S_r_17 );
              //Bin_r_17 = (S_r_17/sqrt(B_r_17))*(S_r_17/sqrt(B_r_17));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_17) << endl;
          

          Sum_r_17 += Bin_r_17 ;
          QuadraticSum_r_17 = sqrt(Sum_r_17);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_17 << endl;

          h172->SetBinContent(j,QuadraticSum_r_17);
          h172->SetLineColor(kGreen-9);
          h172->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax17 = 1.1*h171->GetMaximum();
    float scale17 = 5000 / rightmax17;
    h171->Scale(scale17);
    h171->Draw("SAMEHIST");
    
    h172->Scale(scale17);
    h172->Draw("SAMEHIST");
    

    TGaxis*axis17 = new TGaxis(2000,0,2000,5000,0,rightmax17,510,"+L");
    axis17->SetTitle("Quadratic Sum of significance");
    axis17->SetTitleSize(0.03);
    axis17->SetLabelSize(0.025);
    axis17->Draw();
    
    pad172[k]->cd();
    TLegend *leg17 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg17->SetBorderSize(1);
    leg17->SetFillColor(0);
    leg17->SetTextFont(42);
    leg17->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg17->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg17->AddEntry(h171, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg17->AddEntry(h172, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg17->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut17_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_17 << endl;
        cout << "" << endl;
          
      }
     
    /* 
    cout << " " << endl;
    cout << "  ===========================================================   dRLepTau   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut18 = 26;
    TCut cut18_1[n_cut18] = { "dRLepTau<1 ", "dRLepTau<1.2", "dRLepTau<1.4", "dRLepTau<1.6", "dRLepTau<1.8", "dRLepTau<2", "dRLepTau<2.2", "dRLepTau<2.4", "dRLepTau<2.6", "dRLepTau<2.8", "dRLepTau<3", "dRLepTau<3.2", "dRLepTau<3.4", "dRLepTau<3.6", "dRLepTau<3.8", "dRLepTau<4", "dRLepTau<4.2", "dRLepTau<4.4", "dRLepTau<4.6","dRLepTau<4.8", "dRLepTau<5", "dRLepTau<5.2", "dRLepTau<5.4", "dRLepTau<5.6", "dRLepTau<5.8", "dRLepTau<6" };
    string cut18_2[n_cut18] = { "dRLepTau<1 ", "dRLepTau<1.2", "dRLepTau<1.4", "dRLepTau<1.6", "dRLepTau<1.8", "dRLepTau<2", "dRLepTau<2.2", "dRLepTau<2.4", "dRLepTau<2.6", "dRLepTau<2.8", "dRLepTau<3", "dRLepTau<3.2", "dRLepTau<3.4", "dRLepTau<3.6", "dRLepTau<3.8", "dRLepTau<4", "dRLepTau<4.2", "dRLepTau<4.4", "dRLepTau<4.6","dRLepTau<4.8", "dRLepTau<5", "dRLepTau<5.2", "dRLepTau<5.4", "dRLepTau<5.6", "dRLepTau<5.8", "dRLepTau<6" };
    

      TCanvas *canvas18[n_cut18] ;
      canvas18[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas18[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas18[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas18[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas18[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas18[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas18[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas18[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas18[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas18[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas18[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas18[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas18[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas18[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas18[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas18[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas18[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas18[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas18[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas18[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas18[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas18[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas18[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas18[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas18[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas18[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad181[n_cut18];
      pad181[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad181[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad181[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad181[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad181[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad181[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad181[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad181[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad181[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad181[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad181[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad181[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad181[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad181[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad181[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad181[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad181[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad181[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad181[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad181[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad181[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad181[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad181[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad181[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad181[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad181[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad182[n_cut18];
      pad182[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad182[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad182[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad182[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad182[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad182[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad182[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad182[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad182[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad182[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad182[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad182[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad182[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad182[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad182[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad182[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad182[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad182[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad182[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad182[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad182[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad182[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad182[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad182[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad182[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad182[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut18;k++) {
           canvas18[k]->cd();
           pad181[k]->Draw();
           pad182[k]->Draw();
           
           pad181[k]->cd();
           pad181[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut18_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut18_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut18_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut18_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut18_1[k]),  "SAMEHIST");
        }
        
        THStack *hs18 = new THStack("hs18", "");
        for(int i= 0; i<9 ; i++){ hs18->Add(h_hist[i], "hist1"); }
        hs18->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut18_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h181 = new TH1F("h181","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_18 = 0;
       float B_l_18_0 = 0;
       float B_l_18_1 = 0;
       float B_l_18_2 = 0;
       float B_l_18_3 = 0;
       float B_l_18_4 = 0;
       float B_l_18_5 = 0;
       float B_l_18_6 = 0;
       float B_l_18_7 = 0;
       float B_l_18_8 = 0;
        
       float QuadraticSum_l_18 = 0;
       float Sum_l_18 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_18 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_18 << endl;
           B_l_18_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_18_8 << endl;
           B_l_18_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_18_7 << endl;
           B_l_18_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_18_6 << endl;
           B_l_18_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_18_5 << endl;
           B_l_18_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_18_4 << endl;
           B_l_18_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_18_3 << endl;
           B_l_18_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_18_2 << endl;
           B_l_18_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_18_1 << endl;
           B_l_18_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_18_0 << endl;
           
           float B_l_18 = 0;
           for(int i = 0; i<9; i++) { B_l_18 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_18 << endl;
           
           float Bin_l_18 = 0;
           if (B_l_18 > 0){
               Bin_l_18 =  2* ( (S_l_18 + B_l_18) * log(1+S_l_18/B_l_18) - S_l_18 );
               //Bin_l_18 = (S_l_18/sqrt(B_l_18))*(S_l_18/sqrt(B_l_18));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_18) << endl; //
           

           Sum_l_18 += Bin_l_18 ;
           QuadraticSum_l_18 = sqrt(Sum_l_18);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_18 << endl; //

           h181->SetBinContent(j,QuadraticSum_l_18);
           h181->SetLineColor(kBlue-9);
           h181->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h182 = new TH1F("h182","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_18 = 0;
       float B_r_18_0 = 0;
       float B_r_18_1 = 0;
       float B_r_18_2 = 0;
       float B_r_18_3 = 0;
       float B_r_18_4 = 0;
       float B_r_18_5 = 0;
       float B_r_18_6 = 0;
       float B_r_18_7 = 0;
       float B_r_18_8 = 0;
        
       float QuadraticSum_r_18 = 0;
       float Sum_r_18 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_18 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_18 << endl;
          B_r_18_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_18_8 << endl;
          B_r_18_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_18_7 << endl;
          B_r_18_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_18_6 << endl;
          B_r_18_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_18_5 << endl;
          B_r_18_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_18_4 << endl;
          B_r_18_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_18_3 << endl;
          B_r_18_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_18_2 << endl;
          B_r_18_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_18_1 << endl;
          B_r_18_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_18_0 << endl;
          
          float B_r_18 = 0;
          for(int i = 0; i<9; i++) { B_r_18 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_18 << endl;
          
          float Bin_r_18 = 0;
          if (B_r_18 > 0){
              Bin_r_18 =  2* ( (S_r_18 + B_r_18) * log(1+S_r_18/B_r_18) - S_r_18 );
              //Bin_r_18 = (S_r_18/sqrt(B_r_18))*(S_r_18/sqrt(B_r_18));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_18) << endl;
          

          Sum_r_18 += Bin_r_18 ;
          QuadraticSum_r_18 = sqrt(Sum_r_18);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_18 << endl;

          h182->SetBinContent(j,QuadraticSum_r_18);
          h182->SetLineColor(kGreen-9);
          h182->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax18 = 1.1*h181->GetMaximum();
    float scale18 = 5000 / rightmax18;
    h181->Scale(scale18);
    h181->Draw("SAMEHIST");
    
    h182->Scale(scale18);
    h182->Draw("SAMEHIST");
    

    TGaxis*axis18 = new TGaxis(2000,0,2000,5000,0,rightmax18,510,"+L");
    axis18->SetTitle("Quadratic Sum of significance");
    axis18->SetTitleSize(0.03);
    axis18->SetLabelSize(0.025);
    axis18->Draw();
    
    pad182[k]->cd();
    TLegend *leg18 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg18->SetBorderSize(1);
    leg18->SetFillColor(0);
    leg18->SetTextFont(42);
    leg18->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg18->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg18->AddEntry(h181, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg18->AddEntry(h182, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg18->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut18_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_18 << endl;
        cout << "" << endl;
          
      }
    */
    
    cout << " " << endl;
    cout << "  ===========================================================   dRVBFjj   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut19 = 26;
    TCut cut19_1[n_cut19] = { "dRVBFjj>1 ", "dRVBFjj>1.2", "dRVBFjj>1.4", "dRVBFjj>1.6", "dRVBFjj>1.8", "dRVBFjj>2", "dRVBFjj>2.2", "dRVBFjj>2.4", "dRVBFjj>2.6", "dRVBFjj>2.8", "dRVBFjj>3", "dRVBFjj>3.2", "dRVBFjj>3.4", "dRVBFjj>3.6", "dRVBFjj>3.8", "dRVBFjj>4", "dRVBFjj>4.2", "dRVBFjj>4.4", "dRVBFjj>4.6","dRVBFjj>4.8", "dRVBFjj>5", "dRVBFjj>5.2", "dRVBFjj>5.4", "dRVBFjj>5.6", "dRVBFjj>5.8", "dRVBFjj>6" };
    string cut19_2[n_cut19] = { "dRVBFjj>1 ", "dRVBFjj>1.2", "dRVBFjj>1.4", "dRVBFjj>1.6", "dRVBFjj>1.8", "dRVBFjj>2", "dRVBFjj>2.2", "dRVBFjj>2.4", "dRVBFjj>2.6", "dRVBFjj>2.8", "dRVBFjj>3", "dRVBFjj>3.2", "dRVBFjj>3.4", "dRVBFjj>3.6", "dRVBFjj>3.8", "dRVBFjj>4", "dRVBFjj>4.2", "dRVBFjj>4.4", "dRVBFjj>4.6","dRVBFjj>4.8", "dRVBFjj>5", "dRVBFjj>5.2", "dRVBFjj>5.4", "dRVBFjj>5.6", "dRVBFjj>5.8", "dRVBFjj>6" };
    

      TCanvas *canvas19[n_cut19] ;
      canvas19[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas19[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas19[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas19[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas19[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas19[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas19[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas19[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas19[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas19[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas19[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas19[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas19[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas19[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas19[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas19[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas19[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas19[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas19[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas19[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas19[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas19[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas19[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas19[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas19[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas19[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad191[n_cut19];
      pad191[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad191[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad191[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad191[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad191[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad191[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad191[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad191[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad191[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad191[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad191[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad191[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad191[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad191[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad191[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad191[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad191[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad191[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad191[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad191[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad191[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad191[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad191[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad191[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad191[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad191[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad192[n_cut19];
      pad192[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad192[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad192[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad192[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad192[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad192[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad192[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad192[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad192[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad192[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad192[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad192[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad192[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad192[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad192[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad192[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad192[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad192[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad192[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad192[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad192[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad192[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad192[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad192[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad192[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad192[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut19;k++) {
           canvas19[k]->cd();
           pad191[k]->Draw();
           pad192[k]->Draw();
           
           pad191[k]->cd();
           pad191[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut19_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut19_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut19_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut19_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut19_1[k]),  "SAMEHIST");
        }
        
        THStack *hs19 = new THStack("hs19", "");
        for(int i= 0; i<9 ; i++){ hs19->Add(h_hist[i], "hist1"); }
        hs19->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut19_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h191 = new TH1F("h191","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_19 = 0;
       float B_l_19_0 = 0;
       float B_l_19_1 = 0;
       float B_l_19_2 = 0;
       float B_l_19_3 = 0;
       float B_l_19_4 = 0;
       float B_l_19_5 = 0;
       float B_l_19_6 = 0;
       float B_l_19_7 = 0;
       float B_l_19_8 = 0;
        
       float QuadraticSum_l_19 = 0;
       float Sum_l_19 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_19 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_19 << endl;
           B_l_19_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_19_8 << endl;
           B_l_19_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_19_7 << endl;
           B_l_19_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_19_6 << endl;
           B_l_19_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_19_5 << endl;
           B_l_19_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_19_4 << endl;
           B_l_19_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_19_3 << endl;
           B_l_19_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_19_2 << endl;
           B_l_19_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_19_1 << endl;
           B_l_19_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_19_0 << endl;
           
           float B_l_19 = 0;
           for(int i = 0; i<9; i++) { B_l_19 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_19 << endl;
           
           float Bin_l_19 = 0;
           if (B_l_19 > 0){
               Bin_l_19 =  2* ( (S_l_19 + B_l_19) * log(1+S_l_19/B_l_19) - S_l_19 );
               //Bin_l_19 = (S_l_19/sqrt(B_l_19))*(S_l_19/sqrt(B_l_19));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_19) << endl; //
           

           Sum_l_19 += Bin_l_19 ;
           QuadraticSum_l_19 = sqrt(Sum_l_19);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_19 << endl; //

           h191->SetBinContent(j,QuadraticSum_l_19);
           h191->SetLineColor(kBlue-9);
           h191->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h192 = new TH1F("h192","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_19 = 0;
       float B_r_19_0 = 0;
       float B_r_19_1 = 0;
       float B_r_19_2 = 0;
       float B_r_19_3 = 0;
       float B_r_19_4 = 0;
       float B_r_19_5 = 0;
       float B_r_19_6 = 0;
       float B_r_19_7 = 0;
       float B_r_19_8 = 0;
        
       float QuadraticSum_r_19 = 0;
       float Sum_r_19 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_19 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_19 << endl;
          B_r_19_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_19_8 << endl;
          B_r_19_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_19_7 << endl;
          B_r_19_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_19_6 << endl;
          B_r_19_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_19_5 << endl;
          B_r_19_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_19_4 << endl;
          B_r_19_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_19_3 << endl;
          B_r_19_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_19_2 << endl;
          B_r_19_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_19_1 << endl;
          B_r_19_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_19_0 << endl;
          
          float B_r_19 = 0;
          for(int i = 0; i<9; i++) { B_r_19 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_19 << endl;
          
          float Bin_r_19 = 0;
          if (B_r_19 > 0){
              Bin_r_19 =  2* ( (S_r_19 + B_r_19) * log(1+S_r_19/B_r_19) - S_r_19 );
              //Bin_r_19 = (S_r_19/sqrt(B_r_19))*(S_r_19/sqrt(B_r_19));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_19) << endl;
          

          Sum_r_19 += Bin_r_19 ;
          QuadraticSum_r_19 = sqrt(Sum_r_19);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_19 << endl;

          h192->SetBinContent(j,QuadraticSum_r_19);
          h192->SetLineColor(kGreen-9);
          h192->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax19 = 1.1*h191->GetMaximum();
    float scale19 = 5000 / rightmax19;
    h191->Scale(scale19);
    h191->Draw("SAMEHIST");
    
    h192->Scale(scale19);
    h192->Draw("SAMEHIST");
    

    TGaxis*axis19 = new TGaxis(2000,0,2000,5000,0,rightmax19,510,"+L");
    axis19->SetTitle("Quadratic Sum of significance");
    axis19->SetTitleSize(0.03);
    axis19->SetLabelSize(0.025);
    axis19->Draw();
    
    pad192[k]->cd();
    TLegend *leg19 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg19->SetBorderSize(1);
    leg19->SetFillColor(0);
    leg19->SetTextFont(42);
    leg19->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg19->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg19->AddEntry(h191, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg19->AddEntry(h192, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg19->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut19_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_19 << endl;
        cout << "" << endl;
          
      }
    
    /*
    cout << " " << endl;
    cout << "  ===========================================================   etaVBFj1_abs   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut21 = 15;
    TCut cut21_1[n_cut21] = { "abs(etaVBFj1)>0.2", "abs(etaVBFj1)>0.4", "abs(etaVBFj1)>0.6", "abs(etaVBFj1)>0.8", "abs(etaVBFj1)>1", "abs(etaVBFj1)>1.2", "abs(etaVBFj1)>1.4", "abs(etaVBFj1)>1.6", "abs(etaVBFj1)>1.8", "abs(etaVBFj1)>2", "abs(etaVBFj1)>2.2", "abs(etaVBFj1)>2.4", "abs(etaVBFj1)>2.6", "abs(etaVBFj1)>2.8", "abs(etaVBFj1)>3" };
    string cut21_2[n_cut21] = { "abs(etaVBFj1)>0.2", "abs(etaVBFj1)>0.4", "abs(etaVBFj1)>0.6", "abs(etaVBFj1)>0.8", "abs(etaVBFj1)>1", "abs(etaVBFj1)>1.2", "abs(etaVBFj1)>1.4", "abs(etaVBFj1)>1.6", "abs(etaVBFj1)>1.8", "abs(etaVBFj1)>2", "abs(etaVBFj1)>2.2", "abs(etaVBFj1)>2.4", "abs(etaVBFj1)>2.6", "abs(etaVBFj1)>2.8", "abs(etaVBFj1)>3" };
    

      TCanvas *canvas21[n_cut21] ;
      canvas21[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas21[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas21[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas21[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas21[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas21[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas21[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas21[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas21[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas21[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas21[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas21[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas21[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas21[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas21[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad211[n_cut21];
      pad211[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad211[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad211[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad211[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad211[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad211[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad211[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad211[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad211[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad211[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad211[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad211[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad211[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad211[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad211[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad212[n_cut21];
      pad212[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad212[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad212[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad212[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad212[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad212[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad212[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad212[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad212[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad212[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad212[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad212[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad212[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad212[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad212[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut21;k++) {
           canvas21[k]->cd();
           pad211[k]->Draw();
           pad212[k]->Draw();
           
           pad211[k]->cd();
           pad211[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut21_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut21_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut21_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut21_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut21_1[k]),  "SAMEHIST");
        }
        
        THStack *hs21 = new THStack("hs21", "");
        for(int i= 0; i<9 ; i++){ hs21->Add(h_hist[i], "hist1"); }
        hs21->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut21_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h211 = new TH1F("h211","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_21 = 0;
       float B_l_21_0 = 0;
       float B_l_21_1 = 0;
       float B_l_21_2 = 0;
       float B_l_21_3 = 0;
       float B_l_21_4 = 0;
       float B_l_21_5 = 0;
       float B_l_21_6 = 0;
       float B_l_21_7 = 0;
       float B_l_21_8 = 0;
        
       float QuadraticSum_l_21 = 0;
       float Sum_l_21 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_21 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_21 << endl;
           B_l_21_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_21_8 << endl;
           B_l_21_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_21_7 << endl;
           B_l_21_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_21_6 << endl;
           B_l_21_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_21_5 << endl;
           B_l_21_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_21_4 << endl;
           B_l_21_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_21_3 << endl;
           B_l_21_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_21_2 << endl;
           B_l_21_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_21_1 << endl;
           B_l_21_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_21_0 << endl;
           
           float B_l_21 = 0;
           for(int i = 0; i<9; i++) { B_l_21 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_21 << endl;
           
           float Bin_l_21 = 0;
           if (B_l_21 > 0){
               Bin_l_21 =  2* ( (S_l_21 + B_l_21) * log(1+S_l_21/B_l_21) - S_l_21 );
               //Bin_l_21 = (S_l_21/sqrt(B_l_21))*(S_l_21/sqrt(B_l_21));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_21) << endl; //
           

           Sum_l_21 += Bin_l_21 ;
           QuadraticSum_l_21 = sqrt(Sum_l_21);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_21 << endl; //

           h211->SetBinContent(j,QuadraticSum_l_21);
           h211->SetLineColor(kBlue-9);
           h211->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h212 = new TH1F("h212","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_21 = 0;
       float B_r_21_0 = 0;
       float B_r_21_1 = 0;
       float B_r_21_2 = 0;
       float B_r_21_3 = 0;
       float B_r_21_4 = 0;
       float B_r_21_5 = 0;
       float B_r_21_6 = 0;
       float B_r_21_7 = 0;
       float B_r_21_8 = 0;
        
       float QuadraticSum_r_21 = 0;
       float Sum_r_21 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_21 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_21 << endl;
          B_r_21_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_21_8 << endl;
          B_r_21_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_21_7 << endl;
          B_r_21_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_21_6 << endl;
          B_r_21_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_21_5 << endl;
          B_r_21_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_21_4 << endl;
          B_r_21_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_21_3 << endl;
          B_r_21_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_21_2 << endl;
          B_r_21_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_21_1 << endl;
          B_r_21_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_21_0 << endl;
          
          float B_r_21 = 0;
          for(int i = 0; i<9; i++) { B_r_21 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_21 << endl;
          
          float Bin_r_21 = 0;
          if (B_r_21 > 0){
              Bin_r_21 =  2* ( (S_r_21 + B_r_21) * log(1+S_r_21/B_r_21) - S_r_21 );
              //Bin_r_21 = (S_r_21/sqrt(B_r_21))*(S_r_21/sqrt(B_r_21));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_21) << endl;
          

          Sum_r_21 += Bin_r_21 ;
          QuadraticSum_r_21 = sqrt(Sum_r_21);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_21 << endl;

          h212->SetBinContent(j,QuadraticSum_r_21);
          h212->SetLineColor(kGreen-9);
          h212->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax21 = 1.1*h211->GetMaximum();
    float scale21 = 5000 / rightmax21;
    h211->Scale(scale21);
    h211->Draw("SAMEHIST");
    
    h212->Scale(scale21);
    h212->Draw("SAMEHIST");
    

    TGaxis*axis21 = new TGaxis(2000,0,2000,5000,0,rightmax21,510,"+L");
    axis21->SetTitle("Quadratic Sum of significance");
    axis21->SetTitleSize(0.03);
    axis21->SetLabelSize(0.025);
    axis21->Draw();
    
    pad212[k]->cd();
    TLegend *leg21 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg21->SetBorderSize(1);
    leg21->SetFillColor(0);
    leg21->SetTextFont(42);
    leg21->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg21->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg21->AddEntry(h211, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg21->AddEntry(h212, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg21->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut21_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_21 << endl;
        cout << "" << endl;
          
      }
    */
    
    
    cout << " " << endl;
    cout << "  ===========================================================   etaVBFj2_abs   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut24 = 15;
    TCut cut24_1[n_cut24] = { "abs(etaVBFj2)>0.2", "abs(etaVBFj2)>0.4", "abs(etaVBFj2)>0.6", "abs(etaVBFj2)>0.8", "abs(etaVBFj2)>1", "abs(etaVBFj2)>1.2", "abs(etaVBFj2)>1.4", "abs(etaVBFj2)>1.6", "abs(etaVBFj2)>1.8", "abs(etaVBFj2)>2", "abs(etaVBFj2)>2.2", "abs(etaVBFj2)>2.4", "abs(etaVBFj2)>2.6", "abs(etaVBFj2)>2.8", "abs(etaVBFj2)>3" };
    string cut24_2[n_cut24] = { "abs(etaVBFj2)>0.2", "abs(etaVBFj2)>0.4", "abs(etaVBFj2)>0.6", "abs(etaVBFj2)>0.8", "abs(etaVBFj2)>1", "abs(etaVBFj2)>1.2", "abs(etaVBFj2)>1.4", "abs(etaVBFj2)>1.6", "abs(etaVBFj2)>1.8", "abs(etaVBFj2)>2", "abs(etaVBFj2)>2.2", "abs(etaVBFj2)>2.4", "abs(etaVBFj2)>2.6", "abs(etaVBFj2)>2.8", "abs(etaVBFj2)>3" };
    

      TCanvas *canvas24[n_cut24] ;
      canvas24[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas24[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas24[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas24[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas24[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas24[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas24[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas24[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas24[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas24[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas24[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas24[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas24[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas24[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas24[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad241[n_cut24];
      pad241[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad241[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad241[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad241[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad241[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad241[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad241[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad241[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad241[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad241[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad241[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad241[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad241[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad241[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad241[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad242[n_cut24];
      pad242[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad242[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad242[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad242[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad242[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad242[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad242[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad242[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad242[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad242[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad242[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad242[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad242[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad242[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad242[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut24;k++) {
           canvas24[k]->cd();
           pad241[k]->Draw();
           pad242[k]->Draw();
           
           pad241[k]->cd();
           pad241[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut24_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut24_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut24_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut24_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut24_1[k]),  "SAMEHIST");
        }
        
        THStack *hs24 = new THStack("hs24", "");
        for(int i= 0; i<9 ; i++){ hs24->Add(h_hist[i], "hist1"); }
        hs24->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut24_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h241 = new TH1F("h241","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_24 = 0;
       float B_l_24_0 = 0;
       float B_l_24_1 = 0;
       float B_l_24_2 = 0;
       float B_l_24_3 = 0;
       float B_l_24_4 = 0;
       float B_l_24_5 = 0;
       float B_l_24_6 = 0;
       float B_l_24_7 = 0;
       float B_l_24_8 = 0;
        
       float QuadraticSum_l_24 = 0;
       float Sum_l_24 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_24 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_24 << endl;
           B_l_24_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_24_8 << endl;
           B_l_24_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_24_7 << endl;
           B_l_24_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_24_6 << endl;
           B_l_24_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_24_5 << endl;
           B_l_24_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_24_4 << endl;
           B_l_24_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_24_3 << endl;
           B_l_24_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_24_2 << endl;
           B_l_24_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_24_1 << endl;
           B_l_24_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_24_0 << endl;
           
           float B_l_24 = 0;
           for(int i = 0; i<9; i++) { B_l_24 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_24 << endl;
           
           float Bin_l_24 = 0;
           if (B_l_24 > 0){
               Bin_l_24 =  2* ( (S_l_24 + B_l_24) * log(1+S_l_24/B_l_24) - S_l_24 );
               //Bin_l_24 = (S_l_24/sqrt(B_l_24))*(S_l_24/sqrt(B_l_24));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_24) << endl; //
           

           Sum_l_24 += Bin_l_24 ;
           QuadraticSum_l_24 = sqrt(Sum_l_24);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_24 << endl; //

           h241->SetBinContent(j,QuadraticSum_l_24);
           h241->SetLineColor(kBlue-9);
           h241->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h242 = new TH1F("h242","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_24 = 0;
       float B_r_24_0 = 0;
       float B_r_24_1 = 0;
       float B_r_24_2 = 0;
       float B_r_24_3 = 0;
       float B_r_24_4 = 0;
       float B_r_24_5 = 0;
       float B_r_24_6 = 0;
       float B_r_24_7 = 0;
       float B_r_24_8 = 0;
        
       float QuadraticSum_r_24 = 0;
       float Sum_r_24 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_24 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_24 << endl;
          B_r_24_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_24_8 << endl;
          B_r_24_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_24_7 << endl;
          B_r_24_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_24_6 << endl;
          B_r_24_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_24_5 << endl;
          B_r_24_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_24_4 << endl;
          B_r_24_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_24_3 << endl;
          B_r_24_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_24_2 << endl;
          B_r_24_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_24_1 << endl;
          B_r_24_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_24_0 << endl;
          
          float B_r_24 = 0;
          for(int i = 0; i<9; i++) { B_r_24 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_24 << endl;
          
          float Bin_r_24 = 0;
          if (B_r_24 > 0){
              Bin_r_24 =  2* ( (S_r_24 + B_r_24) * log(1+S_r_24/B_r_24) - S_r_24 );
              //Bin_r_24 = (S_r_24/sqrt(B_r_24))*(S_r_24/sqrt(B_r_24));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_24) << endl;
          

          Sum_r_24 += Bin_r_24 ;
          QuadraticSum_r_24 = sqrt(Sum_r_24);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_24 << endl;

          h242->SetBinContent(j,QuadraticSum_r_24);
          h242->SetLineColor(kGreen-9);
          h242->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax24 = 1.1*h241->GetMaximum();
    float scale24 = 5000 / rightmax24;
    h241->Scale(scale24);
    h241->Draw("SAMEHIST");
    
    h242->Scale(scale24);
    h242->Draw("SAMEHIST");
    

    TGaxis*axis24 = new TGaxis(2000,0,2000,5000,0,rightmax24,510,"+L");
    axis24->SetTitle("Quadratic Sum of significance");
    axis24->SetTitleSize(0.03);
    axis24->SetLabelSize(0.025);
    axis24->Draw();
    
    pad242[k]->cd();
    TLegend *leg24 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg24->SetBorderSize(1);
    leg24->SetFillColor(0);
    leg24->SetTextFont(42);
    leg24->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg24->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg24->AddEntry(h241, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg24->AddEntry(h242, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg24->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut24_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_24 << endl;
        cout << "" << endl;
          
      }
    
    
    
    
    cout << " " << endl;
    cout << "  ===========================================================   HT   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut27 = 26;
    TCut cut27_1[n_cut27] = { "HT>200000", "HT>210000", "HT>220000", "HT>230000", "HT>240000", "HT>250000", "HT>260000", "HT>270000", "HT>280000", "HT>290000", "HT>300000", "HT>310000", "HT>320000", "HT>330000", "HT>340000", "HT>350000", "HT>360000", "HT>370000", "HT>380000","HT>390000", "HT>400000", "HT>410000", "HT>420000", "HT>430000", "HT>440000", "HT>450000" };
    string cut27_2[n_cut27] = { "HT>200GeV", "HT>210GeV", "HT>220GeV", "HT>230GeV", "HT>240GeV", "HT>250GeV", "HT>260GeV", "HT>270GeV", "HT>280GeV", "HT>290GeV", "HT>300GeV", "HT>310GeV", "HT>320GeV", "HT>330GeV", "HT>340GeV", "HT>350GeV", "HT>360GeV", "HT>370GeV", "HT>380GeV","HT>390GeV", "HT>400GeV", "HT>410GeV", "HT>420GeV", "HT>430GeV", "HT>440GeV", "HT>450GeV" };
    

      TCanvas *canvas27[n_cut27] ;
      canvas27[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas27[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas27[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas27[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas27[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas27[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas27[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas27[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas27[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas27[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas27[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas27[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas27[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas27[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas27[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas27[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas27[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas27[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas27[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas27[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas27[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas27[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas27[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas27[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas27[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas27[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad271[n_cut27];
      pad271[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad271[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad271[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad271[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad271[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad271[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad271[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad271[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad271[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad271[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad271[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad271[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad271[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad271[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad271[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad271[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad271[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad271[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad271[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad271[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad271[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad271[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad271[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad271[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad271[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad271[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad272[n_cut27];
      pad272[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad272[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad272[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad272[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad272[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad272[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad272[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad272[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad272[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad272[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad272[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad272[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad272[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad272[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad272[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad272[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad272[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad272[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad272[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad272[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad272[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad272[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad272[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad272[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad272[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad272[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut27;k++) {
           canvas27[k]->cd();
           pad271[k]->Draw();
           pad272[k]->Draw();
           
           pad271[k]->cd();
           pad271[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut27_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut27_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut27_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut27_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut27_1[k]),  "SAMEHIST");
        }
        
        THStack *hs27 = new THStack("hs27", "");
        for(int i= 0; i<9 ; i++){ hs27->Add(h_hist[i], "hist1"); }
        hs27->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut27_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h271 = new TH1F("h271","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_27 = 0;
       float B_l_27_0 = 0;
       float B_l_27_1 = 0;
       float B_l_27_2 = 0;
       float B_l_27_3 = 0;
       float B_l_27_4 = 0;
       float B_l_27_5 = 0;
       float B_l_27_6 = 0;
       float B_l_27_7 = 0;
       float B_l_27_8 = 0;
        
       float QuadraticSum_l_27 = 0;
       float Sum_l_27 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_27 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_27 << endl;
           B_l_27_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_27_8 << endl;
           B_l_27_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_27_7 << endl;
           B_l_27_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_27_6 << endl;
           B_l_27_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_27_5 << endl;
           B_l_27_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_27_4 << endl;
           B_l_27_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_27_3 << endl;
           B_l_27_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_27_2 << endl;
           B_l_27_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_27_1 << endl;
           B_l_27_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_27_0 << endl;
           
           float B_l_27 = 0;
           for(int i = 0; i<9; i++) { B_l_27 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_27 << endl;
           
           float Bin_l_27 = 0;
           if (B_l_27 > 0){
               Bin_l_27 =  2* ( (S_l_27 + B_l_27) * log(1+S_l_27/B_l_27) - S_l_27 );
               //Bin_l_27 = (S_l_27/sqrt(B_l_27))*(S_l_27/sqrt(B_l_27));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_27) << endl; //
           

           Sum_l_27 += Bin_l_27 ;
           QuadraticSum_l_27 = sqrt(Sum_l_27);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_27 << endl; //

           h271->SetBinContent(j,QuadraticSum_l_27);
           h271->SetLineColor(kBlue-9);
           h271->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h272 = new TH1F("h272","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_27 = 0;
       float B_r_27_0 = 0;
       float B_r_27_1 = 0;
       float B_r_27_2 = 0;
       float B_r_27_3 = 0;
       float B_r_27_4 = 0;
       float B_r_27_5 = 0;
       float B_r_27_6 = 0;
       float B_r_27_7 = 0;
       float B_r_27_8 = 0;
        
       float QuadraticSum_r_27 = 0;
       float Sum_r_27 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_27 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_27 << endl;
          B_r_27_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_27_8 << endl;
          B_r_27_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_27_7 << endl;
          B_r_27_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_27_6 << endl;
          B_r_27_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_27_5 << endl;
          B_r_27_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_27_4 << endl;
          B_r_27_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_27_3 << endl;
          B_r_27_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_27_2 << endl;
          B_r_27_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_27_1 << endl;
          B_r_27_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_27_0 << endl;
          
          float B_r_27 = 0;
          for(int i = 0; i<9; i++) { B_r_27 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_27 << endl;
          
          float Bin_r_27 = 0;
          if (B_r_27 > 0){
              Bin_r_27 =  2* ( (S_r_27 + B_r_27) * log(1+S_r_27/B_r_27) - S_r_27 );
              //Bin_r_27 = (S_r_27/sqrt(B_r_27))*(S_r_27/sqrt(B_r_27));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_27) << endl;
          

          Sum_r_27 += Bin_r_27 ;
          QuadraticSum_r_27 = sqrt(Sum_r_27);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_27 << endl;

          h272->SetBinContent(j,QuadraticSum_r_27);
          h272->SetLineColor(kGreen-9);
          h272->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax27 = 1.1*h271->GetMaximum();
    float scale27 = 5000 / rightmax27;
    h271->Scale(scale27);
    h271->Draw("SAMEHIST");
    
    h272->Scale(scale27);
    h272->Draw("SAMEHIST");
    

    TGaxis*axis27 = new TGaxis(2000,0,2000,5000,0,rightmax27,510,"+L");
    axis27->SetTitle("Quadratic Sum of significance");
    axis27->SetTitleSize(0.03);
    axis27->SetLabelSize(0.025);
    axis27->Draw();
    
    pad272[k]->cd();
    TLegend *leg27 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg27->SetBorderSize(1);
    leg27->SetFillColor(0);
    leg27->SetTextFont(42);
    leg27->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg27->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg27->AddEntry(h271, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg27->AddEntry(h272, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg27->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut27_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_27 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   LepEta_abs   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut28 = 15;
    TCut cut28_1[n_cut28] = { "abs(LepEta)<0.2", "abs(LepEta)<0.4", "abs(LepEta)<0.6", "abs(LepEta)<0.8", "abs(LepEta)<1", "abs(LepEta)<1.2", "abs(LepEta)<1.4", "abs(LepEta)<1.6", "abs(LepEta)<1.8", "abs(LepEta)<2", "abs(LepEta)<2.2", "abs(LepEta)<2.4", "abs(LepEta)<2.6", "abs(LepEta)<2.8", "abs(LepEta)<3" };
    string cut28_2[n_cut28] = { "abs(LepEta)<0.2", "abs(LepEta)<0.4", "abs(LepEta)<0.6", "abs(LepEta)<0.8", "abs(LepEta)<1", "abs(LepEta)<1.2", "abs(LepEta)<1.4", "abs(LepEta)<1.6", "abs(LepEta)<1.8", "abs(LepEta)<2", "abs(LepEta)<2.2", "abs(LepEta)<2.4", "abs(LepEta)<2.6", "abs(LepEta)<2.8", "abs(LepEta)<3" };
    

      TCanvas *canvas28[n_cut28] ;
      canvas28[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas28[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas28[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas28[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas28[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas28[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas28[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas28[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas28[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas28[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas28[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas28[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas28[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas28[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas28[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad281[n_cut28];
      pad281[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad281[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad281[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad281[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad281[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad281[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad281[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad281[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad281[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad281[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad281[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad281[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad281[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad281[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad281[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad282[n_cut28];
      pad282[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad282[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad282[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad282[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad282[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad282[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad282[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad282[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad282[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad282[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad282[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad282[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad282[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad282[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad282[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut28;k++) {
           canvas28[k]->cd();
           pad281[k]->Draw();
           pad282[k]->Draw();
           
           pad281[k]->cd();
           pad281[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut28_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut28_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut28_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut28_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut28_1[k]),  "SAMEHIST");
        }
        
        THStack *hs28 = new THStack("hs28", "");
        for(int i= 0; i<9 ; i++){ hs28->Add(h_hist[i], "hist1"); }
        hs28->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut28_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h281 = new TH1F("h281","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_28 = 0;
       float B_l_28_0 = 0;
       float B_l_28_1 = 0;
       float B_l_28_2 = 0;
       float B_l_28_3 = 0;
       float B_l_28_4 = 0;
       float B_l_28_5 = 0;
       float B_l_28_6 = 0;
       float B_l_28_7 = 0;
       float B_l_28_8 = 0;
        
       float QuadraticSum_l_28 = 0;
       float Sum_l_28 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_28 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_28 << endl;
           B_l_28_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_28_8 << endl;
           B_l_28_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_28_7 << endl;
           B_l_28_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_28_6 << endl;
           B_l_28_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_28_5 << endl;
           B_l_28_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_28_4 << endl;
           B_l_28_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_28_3 << endl;
           B_l_28_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_28_2 << endl;
           B_l_28_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_28_1 << endl;
           B_l_28_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_28_0 << endl;
           
           float B_l_28 = 0;
           for(int i = 0; i<9; i++) { B_l_28 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_28 << endl;
           
           float Bin_l_28 = 0;
           if (B_l_28 > 0){
               Bin_l_28 =  2* ( (S_l_28 + B_l_28) * log(1+S_l_28/B_l_28) - S_l_28 );
               //Bin_l_28 = (S_l_28/sqrt(B_l_28))*(S_l_28/sqrt(B_l_28));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_28) << endl; //
           

           Sum_l_28 += Bin_l_28 ;
           QuadraticSum_l_28 = sqrt(Sum_l_28);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_28 << endl; //

           h281->SetBinContent(j,QuadraticSum_l_28);
           h281->SetLineColor(kBlue-9);
           h281->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h282 = new TH1F("h282","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_28 = 0;
       float B_r_28_0 = 0;
       float B_r_28_1 = 0;
       float B_r_28_2 = 0;
       float B_r_28_3 = 0;
       float B_r_28_4 = 0;
       float B_r_28_5 = 0;
       float B_r_28_6 = 0;
       float B_r_28_7 = 0;
       float B_r_28_8 = 0;
        
       float QuadraticSum_r_28 = 0;
       float Sum_r_28 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_28 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_28 << endl;
          B_r_28_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_28_8 << endl;
          B_r_28_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_28_7 << endl;
          B_r_28_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_28_6 << endl;
          B_r_28_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_28_5 << endl;
          B_r_28_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_28_4 << endl;
          B_r_28_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_28_3 << endl;
          B_r_28_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_28_2 << endl;
          B_r_28_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_28_1 << endl;
          B_r_28_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_28_0 << endl;
          
          float B_r_28 = 0;
          for(int i = 0; i<9; i++) { B_r_28 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_28 << endl;
          
          float Bin_r_28 = 0;
          if (B_r_28 > 0){
              Bin_r_28 =  2* ( (S_r_28 + B_r_28) * log(1+S_r_28/B_r_28) - S_r_28 );
              //Bin_r_28 = (S_r_28/sqrt(B_r_28))*(S_r_28/sqrt(B_r_28));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_28) << endl;
          

          Sum_r_28 += Bin_r_28 ;
          QuadraticSum_r_28 = sqrt(Sum_r_28);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_28 << endl;

          h282->SetBinContent(j,QuadraticSum_r_28);
          h282->SetLineColor(kGreen-9);
          h282->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax28 = 1.1*h281->GetMaximum();
    float scale28 = 5000 / rightmax28;
    h281->Scale(scale28);
    h281->Draw("SAMEHIST");
    
    h282->Scale(scale28);
    h282->Draw("SAMEHIST");
    

    TGaxis*axis28 = new TGaxis(2000,0,2000,5000,0,rightmax28,510,"+L");
    axis28->SetTitle("Quadratic Sum of significance");
    axis28->SetTitleSize(0.03);
    axis28->SetLabelSize(0.025);
    axis28->Draw();
    
    pad282[k]->cd();
    TLegend *leg28 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg28->SetBorderSize(1);
    leg28->SetFillColor(0);
    leg28->SetTextFont(42);
    leg28->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg28->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg28->AddEntry(h281, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg28->AddEntry(h282, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg28->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut28_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_28 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   LepPhi   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut31 = 15;
    TCut cut31_1[n_cut31] = { "LepPhi>0.2", "LepPhi>0.4", "LepPhi>0.6", "LepPhi>0.8", "LepPhi>1", "LepPhi>1.2", "LepPhi>1.4", "LepPhi>1.6", "LepPhi>1.8", "LepPhi>2", "LepPhi>2.2", "LepPhi>2.4", "LepPhi>2.6", "LepPhi>2.8", "LepPhi>3" };
    string cut31_2[n_cut31] = { "LepPhi>0.2", "LepPhi>0.4", "LepPhi>0.6", "LepPhi>0.8", "LepPhi>1", "LepPhi>1.2", "LepPhi>1.4", "LepPhi>1.6", "LepPhi>1.8", "LepPhi>2", "LepPhi>2.2", "LepPhi>2.4", "LepPhi>2.6", "LepPhi>2.8", "LepPhi>3" };
    

      TCanvas *canvas31[n_cut31] ;
      canvas31[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas31[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas31[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas31[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas31[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas31[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas31[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas31[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas31[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas31[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas31[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas31[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas31[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas31[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas31[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad311[n_cut31];
      pad311[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad311[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad311[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad311[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad311[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad311[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad311[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad311[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad311[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad311[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad311[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad311[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad311[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad311[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad311[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad312[n_cut31];
      pad312[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad312[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad312[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad312[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad312[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad312[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad312[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad312[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad312[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad312[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad312[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad312[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad312[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad312[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad312[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut31;k++) {
           canvas31[k]->cd();
           pad311[k]->Draw();
           pad312[k]->Draw();
           
           pad311[k]->cd();
           pad311[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut31_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut31_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut31_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut31_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut31_1[k]),  "SAMEHIST");
        }
        
        THStack *hs31 = new THStack("hs31", "");
        for(int i= 0; i<9 ; i++){ hs31->Add(h_hist[i], "hist1"); }
        hs31->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut31_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h311 = new TH1F("h311","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_31 = 0;
       float B_l_31_0 = 0;
       float B_l_31_1 = 0;
       float B_l_31_2 = 0;
       float B_l_31_3 = 0;
       float B_l_31_4 = 0;
       float B_l_31_5 = 0;
       float B_l_31_6 = 0;
       float B_l_31_7 = 0;
       float B_l_31_8 = 0;
        
       float QuadraticSum_l_31 = 0;
       float Sum_l_31 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_31 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_31 << endl;
           B_l_31_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_31_8 << endl;
           B_l_31_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_31_7 << endl;
           B_l_31_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_31_6 << endl;
           B_l_31_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_31_5 << endl;
           B_l_31_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_31_4 << endl;
           B_l_31_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_31_3 << endl;
           B_l_31_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_31_2 << endl;
           B_l_31_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_31_1 << endl;
           B_l_31_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_31_0 << endl;
           
           float B_l_31 = 0;
           for(int i = 0; i<9; i++) { B_l_31 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_31 << endl;
           
           float Bin_l_31 = 0;
           if (B_l_31 > 0){
               Bin_l_31 =  2* ( (S_l_31 + B_l_31) * log(1+S_l_31/B_l_31) - S_l_31 );
               //Bin_l_31 = (S_l_31/sqrt(B_l_31))*(S_l_31/sqrt(B_l_31));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_31) << endl; //
           

           Sum_l_31 += Bin_l_31 ;
           QuadraticSum_l_31 = sqrt(Sum_l_31);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_31 << endl; //

           h311->SetBinContent(j,QuadraticSum_l_31);
           h311->SetLineColor(kBlue-9);
           h311->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h312 = new TH1F("h312","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_31 = 0;
       float B_r_31_0 = 0;
       float B_r_31_1 = 0;
       float B_r_31_2 = 0;
       float B_r_31_3 = 0;
       float B_r_31_4 = 0;
       float B_r_31_5 = 0;
       float B_r_31_6 = 0;
       float B_r_31_7 = 0;
       float B_r_31_8 = 0;
        
       float QuadraticSum_r_31 = 0;
       float Sum_r_31 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_31 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_31 << endl;
          B_r_31_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_31_8 << endl;
          B_r_31_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_31_7 << endl;
          B_r_31_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_31_6 << endl;
          B_r_31_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_31_5 << endl;
          B_r_31_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_31_4 << endl;
          B_r_31_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_31_3 << endl;
          B_r_31_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_31_2 << endl;
          B_r_31_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_31_1 << endl;
          B_r_31_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_31_0 << endl;
          
          float B_r_31 = 0;
          for(int i = 0; i<9; i++) { B_r_31 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_31 << endl;
          
          float Bin_r_31 = 0;
          if (B_r_31 > 0){
              Bin_r_31 =  2* ( (S_r_31 + B_r_31) * log(1+S_r_31/B_r_31) - S_r_31 );
              //Bin_r_31 = (S_r_31/sqrt(B_r_31))*(S_r_31/sqrt(B_r_31));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_31) << endl;
          

          Sum_r_31 += Bin_r_31 ;
          QuadraticSum_r_31 = sqrt(Sum_r_31);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_31 << endl;

          h312->SetBinContent(j,QuadraticSum_r_31);
          h312->SetLineColor(kGreen-9);
          h312->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax31 = 1.1*h311->GetMaximum();
    float scale31 = 5000 / rightmax31;
    h311->Scale(scale31);
    h311->Draw("SAMEHIST");
    
    h312->Scale(scale31);
    h312->Draw("SAMEHIST");
    

    TGaxis*axis31 = new TGaxis(2000,0,2000,5000,0,rightmax31,510,"+L");
    axis31->SetTitle("Quadratic Sum of significance");
    axis31->SetTitleSize(0.03);
    axis31->SetLabelSize(0.025);
    axis31->Draw();
    
    pad312[k]->cd();
    TLegend *leg31 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg31->SetBorderSize(1);
    leg31->SetFillColor(0);
    leg31->SetTextFont(42);
    leg31->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg31->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg31->AddEntry(h311, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg31->AddEntry(h312, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg31->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut31_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_31 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   LepPt   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut32 = 26;
    TCut cut32_1[n_cut32] = { "LepPt<10", "LepPt<20", "LepPt<30", "LepPt<40", "LepPt<50", "LepPt<60", "LepPt<70", "LepPt<80", "LepPt<90", "LepPt<100", "LepPt<110", "LepPt<120", "LepPt<130", "LepPt<140", "LepPt<150", "LepPt<160", "LepPt<170", "LepPt<180", "LepPt<190","LepPt<200", "LepPt<210", "LepPt<220", "LepPt<230", "LepPt<240", "LepPt<250", "LepPt<260" };
    string cut32_2[n_cut32] = { "LepPt<10GeV", "LepPt<20GeV", "LepPt<30GeV", "LepPt<40GeV", "LepPt<50GeV", "LepPt<60GeV", "LepPt<70GeV", "LepPt<80GeV", "LepPt<90GeV", "LepPt<100GeV", "LepPt<110GeV", "LepPt<120GeV", "LepPt<130GeV", "LepPt<140GeV", "LepPt<150GeV", "LepPt<160GeV", "LepPt<170GeV", "LepPt<180GeV", "LepPt<190GeV","LepPt<200GeV", "LepPt<210GeV", "LepPt<220GeV", "LepPt<230GeV", "LepPt<240GeV", "LepPt<250GeV", "LepPt<260GeV" };
    

      TCanvas *canvas32[n_cut32] ;
      canvas32[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas32[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas32[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas32[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas32[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas32[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas32[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas32[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas32[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas32[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas32[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas32[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas32[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas32[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas32[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas32[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas32[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas32[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas32[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas32[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas32[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas32[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas32[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas32[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas32[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas32[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad321[n_cut32];
      pad321[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad321[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad321[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad321[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad321[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad321[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad321[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad321[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad321[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad321[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad321[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad321[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad321[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad321[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad321[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad321[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad321[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad321[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad321[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad321[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad321[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad321[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad321[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad321[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad321[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad321[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad322[n_cut32];
      pad322[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad322[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad322[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad322[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad322[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad322[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad322[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad322[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad322[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad322[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad322[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad322[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad322[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad322[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad322[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad322[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad322[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad322[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad322[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad322[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad322[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad322[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad322[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad322[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad322[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad322[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut32;k++) {
           canvas32[k]->cd();
           pad321[k]->Draw();
           pad322[k]->Draw();
           
           pad321[k]->cd();
           pad321[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut32_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut32_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut32_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut32_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut32_1[k]),  "SAMEHIST");
        }
        
        THStack *hs32 = new THStack("hs32", "");
        for(int i= 0; i<9 ; i++){ hs32->Add(h_hist[i], "hist1"); }
        hs32->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut32_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h321 = new TH1F("h321","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_32 = 0;
       float B_l_32_0 = 0;
       float B_l_32_1 = 0;
       float B_l_32_2 = 0;
       float B_l_32_3 = 0;
       float B_l_32_4 = 0;
       float B_l_32_5 = 0;
       float B_l_32_6 = 0;
       float B_l_32_7 = 0;
       float B_l_32_8 = 0;
        
       float QuadraticSum_l_32 = 0;
       float Sum_l_32 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_32 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_32 << endl;
           B_l_32_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_32_8 << endl;
           B_l_32_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_32_7 << endl;
           B_l_32_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_32_6 << endl;
           B_l_32_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_32_5 << endl;
           B_l_32_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_32_4 << endl;
           B_l_32_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_32_3 << endl;
           B_l_32_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_32_2 << endl;
           B_l_32_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_32_1 << endl;
           B_l_32_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_32_0 << endl;
           
           float B_l_32 = 0;
           for(int i = 0; i<9; i++) { B_l_32 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_32 << endl;
           
           float Bin_l_32 = 0;
           if (B_l_32 > 0){
               Bin_l_32 =  2* ( (S_l_32 + B_l_32) * log(1+S_l_32/B_l_32) - S_l_32 );
               //Bin_l_32 = (S_l_32/sqrt(B_l_32))*(S_l_32/sqrt(B_l_32));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_32) << endl; //
           

           Sum_l_32 += Bin_l_32 ;
           QuadraticSum_l_32 = sqrt(Sum_l_32);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_32 << endl; //

           h321->SetBinContent(j,QuadraticSum_l_32);
           h321->SetLineColor(kBlue-9);
           h321->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h322 = new TH1F("h322","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_32 = 0;
       float B_r_32_0 = 0;
       float B_r_32_1 = 0;
       float B_r_32_2 = 0;
       float B_r_32_3 = 0;
       float B_r_32_4 = 0;
       float B_r_32_5 = 0;
       float B_r_32_6 = 0;
       float B_r_32_7 = 0;
       float B_r_32_8 = 0;
        
       float QuadraticSum_r_32 = 0;
       float Sum_r_32 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_32 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_32 << endl;
          B_r_32_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_32_8 << endl;
          B_r_32_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_32_7 << endl;
          B_r_32_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_32_6 << endl;
          B_r_32_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_32_5 << endl;
          B_r_32_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_32_4 << endl;
          B_r_32_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_32_3 << endl;
          B_r_32_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_32_2 << endl;
          B_r_32_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_32_1 << endl;
          B_r_32_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_32_0 << endl;
          
          float B_r_32 = 0;
          for(int i = 0; i<9; i++) { B_r_32 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_32 << endl;
          
          float Bin_r_32 = 0;
          if (B_r_32 > 0){
              Bin_r_32 =  2* ( (S_r_32 + B_r_32) * log(1+S_r_32/B_r_32) - S_r_32 );
              //Bin_r_32 = (S_r_32/sqrt(B_r_32))*(S_r_32/sqrt(B_r_32));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_32) << endl;
          

          Sum_r_32 += Bin_r_32 ;
          QuadraticSum_r_32 = sqrt(Sum_r_32);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_32 << endl;

          h322->SetBinContent(j,QuadraticSum_r_32);
          h322->SetLineColor(kGreen-9);
          h322->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax32 = 1.1*h321->GetMaximum();
    float scale32 = 5000 / rightmax32;
    h321->Scale(scale32);
    h321->Draw("SAMEHIST");
    
    h322->Scale(scale32);
    h322->Draw("SAMEHIST");
    

    TGaxis*axis32 = new TGaxis(2000,0,2000,5000,0,rightmax32,510,"+L");
    axis32->SetTitle("Quadratic Sum of significance");
    axis32->SetTitleSize(0.03);
    axis32->SetLabelSize(0.025);
    axis32->Draw();
    
    pad322[k]->cd();
    TLegend *leg32 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg32->SetBorderSize(1);
    leg32->SetFillColor(0);
    leg32->SetTextFont(42);
    leg32->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg32->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg32->AddEntry(h321, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg32->AddEntry(h322, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg32->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut32_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_32 << endl;
        cout << "" << endl;
          
      }
     
     /*
    cout << " " << endl;
    cout << "  ===========================================================   mBB   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut33 = 15;
    TCut cut33_1[n_cut33] = { "mBB>10000", "mBB>20000", "mBB>30000", "mBB>40000", "mBB>50000", "mBB>60000", "mBB>70000", "mBB>80000", "mBB>90000", "mBB>100000", "mBB>110000", "mBB>120000", "mBB>130000", "mBB>140000", "mBB>150000" };
    string cut33_2[n_cut33] = { "mBB>10GeV", "mBB>20GeV", "mBB>30GeV", "mBB>40GeV", "mBB>50GeV", "mBB>60GeV", "mBB>70GeV", "mBB>80GeV", "mBB>90GeV", "mBB>100GeV", "mBB>110GeV", "mBB>120GeV", "mBB>130GeV", "mBB>140GeV", "mBB>150GeV" };
    

      TCanvas *canvas33[n_cut33] ;
      canvas33[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas33[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas33[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas33[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas33[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas33[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas33[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas33[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas33[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas33[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas33[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas33[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas33[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas33[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas33[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad331[n_cut33];
      pad331[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad331[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad331[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad331[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad331[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad331[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad331[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad331[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad331[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad331[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad331[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad331[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad331[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad331[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad331[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad332[n_cut33];
      pad332[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad332[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad332[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad332[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad332[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad332[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad332[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad332[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad332[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad332[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad332[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad332[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad332[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad332[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad332[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut33;k++) {
           canvas33[k]->cd();
           pad331[k]->Draw();
           pad332[k]->Draw();
           
           pad331[k]->cd();
           pad331[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut33_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut33_1[k]),  "SAMEHIST");} //Wlv
          else if( i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut33_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut33_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut33_1[k]),  "SAMEHIST");
        }
        
        THStack *hs33 = new THStack("hs33", "");
        for(int i= 0; i<9 ; i++){ hs33->Add(h_hist[i], "hist1"); }
        hs33->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut33_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h331 = new TH1F("h331","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_33 = 0;
       float B_l_33_0 = 0;
       float B_l_33_1 = 0;
       float B_l_33_2 = 0;
       float B_l_33_3 = 0;
       float B_l_33_4 = 0;
       float B_l_33_5 = 0;
       float B_l_33_6 = 0;
       float B_l_33_7 = 0;
       float B_l_33_8 = 0;
        
       float QuadraticSum_l_33 = 0;
       float Sum_l_33 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_33 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_33 << endl;
           B_l_33_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_33_8 << endl;
           B_l_33_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_33_7 << endl;
           B_l_33_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_33_6 << endl;
           B_l_33_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_33_5 << endl;
           B_l_33_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_33_4 << endl;
           B_l_33_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_33_3 << endl;
           B_l_33_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_33_2 << endl;
           B_l_33_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_33_1 << endl;
           B_l_33_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_33_0 << endl;
           
           float B_l_33 = 0;
           for(int i = 0; i<9; i++) { B_l_33 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_33 << endl;
           
           float Bin_l_33 = 0;
           if (B_l_33 > 0){
               Bin_l_33 =  2* ( (S_l_33 + B_l_33) * log(1+S_l_33/B_l_33) - S_l_33 );
               //Bin_l_33 = (S_l_33/sqrt(B_l_33))*(S_l_33/sqrt(B_l_33));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_33) << endl; //
           

           Sum_l_33 += Bin_l_33 ;
           QuadraticSum_l_33 = sqrt(Sum_l_33);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_33 << endl; //

           h331->SetBinContent(j,QuadraticSum_l_33);
           h331->SetLineColor(kBlue-9);
           h331->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h332 = new TH1F("h332","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_33 = 0;
       float B_r_33_0 = 0;
       float B_r_33_1 = 0;
       float B_r_33_2 = 0;
       float B_r_33_3 = 0;
       float B_r_33_4 = 0;
       float B_r_33_5 = 0;
       float B_r_33_6 = 0;
       float B_r_33_7 = 0;
       float B_r_33_8 = 0;
        
       float QuadraticSum_r_33 = 0;
       float Sum_r_33 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_33 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_33 << endl;
          B_r_33_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_33_8 << endl;
          B_r_33_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_33_7 << endl;
          B_r_33_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_33_6 << endl;
          B_r_33_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_33_5 << endl;
          B_r_33_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_33_4 << endl;
          B_r_33_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_33_3 << endl;
          B_r_33_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_33_2 << endl;
          B_r_33_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_33_1 << endl;
          B_r_33_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_33_0 << endl;
          
          float B_r_33 = 0;
          for(int i = 0; i<9; i++) { B_r_33 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_33 << endl;
          
          float Bin_r_33 = 0;
          if (B_r_33 > 0){
              Bin_r_33 =  2* ( (S_r_33 + B_r_33) * log(1+S_r_33/B_r_33) - S_r_33 );
              //Bin_r_33 = (S_r_33/sqrt(B_r_33))*(S_r_33/sqrt(B_r_33));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_33) << endl;
          

          Sum_r_33 += Bin_r_33 ;
          QuadraticSum_r_33 = sqrt(Sum_r_33);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_33 << endl;

          h332->SetBinContent(j,QuadraticSum_r_33);
          h332->SetLineColor(kGreen-9);
          h332->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax33 = 1.1*h331->GetMaximum();
    float scale33 = 5000 / rightmax33;
    h331->Scale(scale33);
    h331->Draw("SAMEHIST");
    
    h332->Scale(scale33);
    h332->Draw("SAMEHIST");
    

    TGaxis*axis33 = new TGaxis(2000,0,2000,5000,0,rightmax33,510,"+L");
    axis33->SetTitle("Quadratic Sum of significance");
    axis33->SetTitleSize(0.03);
    axis33->SetLabelSize(0.025);
    axis33->Draw();
    
    pad332[k]->cd();
    TLegend *leg33 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg33->SetBorderSize(1);
    leg33->SetFillColor(0);
    leg33->SetTextFont(42);
    leg33->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg33->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg33->AddEntry(h331, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg33->AddEntry(h332, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg33->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut33_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_33 << endl;
        cout << "" << endl;
          
      }
     */
      
    
    cout << " " << endl;
    cout << "  ===========================================================   MET   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut35 = 26;
    TCut cut35_1[n_cut35] = { "MET>10000", "MET>20000", "MET>30000", "MET>40000", "MET>50000", "MET>60000", "MET>70000", "MET>80000", "MET>90000", "MET>100000", "MET>110000", "MET>120000", "MET>130000", "MET>140000", "MET>150000", "MET>160000", "MET>170000", "MET>180000", "MET>190000","MET>200000", "MET>210000", "MET>220000", "MET>230000", "MET>240000", "MET>250000", "MET>260000" };
    string cut35_2[n_cut35] = { "MET>10GeV", "MET>20GeV", "MET>30GeV", "MET>40GeV", "MET>50GeV", "MET>60GeV", "MET>70GeV", "MET>80GeV", "MET>90GeV", "MET>100GeV", "MET>110GeV", "MET>120GeV", "MET>130GeV", "MET>140GeV", "MET>150GeV", "MET>160GeV", "MET>170GeV", "MET>180GeV", "MET>190GeV","MET>200GeV", "MET>210GeV", "MET>220GeV", "MET>230GeV", "MET>240GeV", "MET>250GeV", "MET>260GeV" };
    

      TCanvas *canvas35[n_cut35] ;
      canvas35[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas35[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas35[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas35[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas35[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas35[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas35[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas35[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas35[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas35[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas35[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas35[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas35[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas35[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas35[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas35[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas35[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas35[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas35[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas35[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas35[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas35[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas35[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas35[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas35[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas35[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad351[n_cut35];
      pad351[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad351[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad351[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad351[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad351[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad351[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad351[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad351[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad351[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad351[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad351[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad351[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad351[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad351[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad351[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad351[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad351[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad351[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad351[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad351[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad351[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad351[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad351[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad351[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad351[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad351[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad352[n_cut35];
      pad352[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad352[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad352[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad352[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad352[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad352[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad352[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad352[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad352[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad352[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad352[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad352[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad352[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad352[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad352[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad352[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad352[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad352[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad352[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad352[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad352[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad352[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad352[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad352[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad352[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad352[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut35;k++) {
           canvas35[k]->cd();
           pad351[k]->Draw();
           pad352[k]->Draw();
           
           pad351[k]->cd();
           pad351[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut35_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut35_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut35_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut35_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut35_1[k]),  "SAMEHIST");
        }
        
        THStack *hs35 = new THStack("hs35", "");
        for(int i= 0; i<9 ; i++){ hs35->Add(h_hist[i], "hist1"); }
        hs35->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut35_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h351 = new TH1F("h351","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_35 = 0;
       float B_l_35_0 = 0;
       float B_l_35_1 = 0;
       float B_l_35_2 = 0;
       float B_l_35_3 = 0;
       float B_l_35_4 = 0;
       float B_l_35_5 = 0;
       float B_l_35_6 = 0;
       float B_l_35_7 = 0;
       float B_l_35_8 = 0;
        
       float QuadraticSum_l_35 = 0;
       float Sum_l_35 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_35 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_35 << endl;
           B_l_35_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_35_8 << endl;
           B_l_35_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_35_7 << endl;
           B_l_35_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_35_6 << endl;
           B_l_35_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_35_5 << endl;
           B_l_35_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_35_4 << endl;
           B_l_35_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_35_3 << endl;
           B_l_35_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_35_2 << endl;
           B_l_35_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_35_1 << endl;
           B_l_35_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_35_0 << endl;
           
           float B_l_35 = 0;
           for(int i = 0; i<9; i++) { B_l_35 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_35 << endl;
           
           float Bin_l_35 = 0;
           if (B_l_35 > 0){
               Bin_l_35 =  2* ( (S_l_35 + B_l_35) * log(1+S_l_35/B_l_35) - S_l_35 );
               //Bin_l_35 = (S_l_35/sqrt(B_l_35))*(S_l_35/sqrt(B_l_35));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_35) << endl; //
           

           Sum_l_35 += Bin_l_35 ;
           QuadraticSum_l_35 = sqrt(Sum_l_35);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_35 << endl; //

           h351->SetBinContent(j,QuadraticSum_l_35);
           h351->SetLineColor(kBlue-9);
           h351->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h352 = new TH1F("h352","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_35 = 0;
       float B_r_35_0 = 0;
       float B_r_35_1 = 0;
       float B_r_35_2 = 0;
       float B_r_35_3 = 0;
       float B_r_35_4 = 0;
       float B_r_35_5 = 0;
       float B_r_35_6 = 0;
       float B_r_35_7 = 0;
       float B_r_35_8 = 0;
        
       float QuadraticSum_r_35 = 0;
       float Sum_r_35 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_35 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_35 << endl;
          B_r_35_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_35_8 << endl;
          B_r_35_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_35_7 << endl;
          B_r_35_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_35_6 << endl;
          B_r_35_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_35_5 << endl;
          B_r_35_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_35_4 << endl;
          B_r_35_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_35_3 << endl;
          B_r_35_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_35_2 << endl;
          B_r_35_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_35_1 << endl;
          B_r_35_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_35_0 << endl;
          
          float B_r_35 = 0;
          for(int i = 0; i<9; i++) { B_r_35 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_35 << endl;
          
          float Bin_r_35 = 0;
          if (B_r_35 > 0){
              Bin_r_35 =  2* ( (S_r_35 + B_r_35) * log(1+S_r_35/B_r_35) - S_r_35 );
              //Bin_r_35 = (S_r_35/sqrt(B_r_35))*(S_r_35/sqrt(B_r_35));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_35) << endl;
          

          Sum_r_35 += Bin_r_35 ;
          QuadraticSum_r_35 = sqrt(Sum_r_35);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_35 << endl;

          h352->SetBinContent(j,QuadraticSum_r_35);
          h352->SetLineColor(kGreen-9);
          h352->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax35 = 1.1*h351->GetMaximum();
    float scale35 = 5000 / rightmax35;
    h351->Scale(scale35);
    h351->Draw("SAMEHIST");
    
    h352->Scale(scale35);
    h352->Draw("SAMEHIST");
    

    TGaxis*axis35 = new TGaxis(2000,0,2000,5000,0,rightmax35,510,"+L");
    axis35->SetTitle("Quadratic Sum of significance");
    axis35->SetTitleSize(0.03);
    axis35->SetLabelSize(0.025);
    axis35->Draw();
    
    pad352[k]->cd();
    TLegend *leg35 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg35->SetBorderSize(1);
    leg35->SetFillColor(0);
    leg35->SetTextFont(42);
    leg35->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg35->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg35->AddEntry(h351, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg35->AddEntry(h352, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg35->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut35_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_35 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   METCent   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut36 = 15;
    TCut cut36_1[n_cut36] = { "METCent>-1.5", "METCent>-1.3", "METCent>-1.1", "METCent>-0.9", "METCent>-0.7", "METCent>-0.5", "METCent>-0.3", "METCent>-0.1", "METCent>0.1", "METCent>0.3", "METCent>0.5", "METCent>0.7", "METCent>0.9", "METCent>1.1", "METCent>1.3" };
    string cut36_2[n_cut36] = { "METCent>-1.5", "METCent>-1.3", "METCent>-1.1", "METCent>-0.9", "METCent>-0.7", "METCent>-0.5", "METCent>-0.3", "METCent>-0.1", "METCent>0.1", "METCent>0.3", "METCent>0.5", "METCent>0.7", "METCent>0.9", "METCent>1.1", "METCent>1.3" };
    

      TCanvas *canvas36[n_cut36] ;
      canvas36[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas36[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas36[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas36[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas36[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas36[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas36[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas36[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas36[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas36[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas36[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas36[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas36[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas36[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas36[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad361[n_cut36];
      pad361[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad361[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad361[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad361[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad361[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad361[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad361[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad361[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad361[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad361[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad361[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad361[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad361[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad361[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad361[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad362[n_cut36];
      pad362[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad362[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad362[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad362[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad362[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad362[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad362[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad362[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad362[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad362[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad362[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad362[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad362[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad362[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad362[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut36;k++) {
           canvas36[k]->cd();
           pad361[k]->Draw();
           pad362[k]->Draw();
           
           pad361[k]->cd();
           pad361[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut36_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut36_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut36_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut36_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut36_1[k]),  "SAMEHIST");
        }
        
        THStack *hs36 = new THStack("hs36", "");
        for(int i= 0; i<9 ; i++){ hs36->Add(h_hist[i], "hist1"); }
        hs36->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut36_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h361 = new TH1F("h361","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_36 = 0;
       float B_l_36_0 = 0;
       float B_l_36_1 = 0;
       float B_l_36_2 = 0;
       float B_l_36_3 = 0;
       float B_l_36_4 = 0;
       float B_l_36_5 = 0;
       float B_l_36_6 = 0;
       float B_l_36_7 = 0;
       float B_l_36_8 = 0;
        
       float QuadraticSum_l_36 = 0;
       float Sum_l_36 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_36 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_36 << endl;
           B_l_36_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_36_8 << endl;
           B_l_36_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_36_7 << endl;
           B_l_36_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_36_6 << endl;
           B_l_36_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_36_5 << endl;
           B_l_36_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_36_4 << endl;
           B_l_36_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_36_3 << endl;
           B_l_36_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_36_2 << endl;
           B_l_36_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_36_1 << endl;
           B_l_36_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_36_0 << endl;
           
           float B_l_36 = 0;
           for(int i = 0; i<9; i++) { B_l_36 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_36 << endl;
           
           float Bin_l_36 = 0;
           if (B_l_36 > 0){
               Bin_l_36 =  2* ( (S_l_36 + B_l_36) * log(1+S_l_36/B_l_36) - S_l_36 );
               //Bin_l_36 = (S_l_36/sqrt(B_l_36))*(S_l_36/sqrt(B_l_36));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_36) << endl; //
           

           Sum_l_36 += Bin_l_36 ;
           QuadraticSum_l_36 = sqrt(Sum_l_36);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_36 << endl; //

           h361->SetBinContent(j,QuadraticSum_l_36);
           h361->SetLineColor(kBlue-9);
           h361->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h362 = new TH1F("h362","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_36 = 0;
       float B_r_36_0 = 0;
       float B_r_36_1 = 0;
       float B_r_36_2 = 0;
       float B_r_36_3 = 0;
       float B_r_36_4 = 0;
       float B_r_36_5 = 0;
       float B_r_36_6 = 0;
       float B_r_36_7 = 0;
       float B_r_36_8 = 0;
        
       float QuadraticSum_r_36 = 0;
       float Sum_r_36 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_36 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_36 << endl;
          B_r_36_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_36_8 << endl;
          B_r_36_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_36_7 << endl;
          B_r_36_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_36_6 << endl;
          B_r_36_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_36_5 << endl;
          B_r_36_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_36_4 << endl;
          B_r_36_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_36_3 << endl;
          B_r_36_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_36_2 << endl;
          B_r_36_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_36_1 << endl;
          B_r_36_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_36_0 << endl;
          
          float B_r_36 = 0;
          for(int i = 0; i<9; i++) { B_r_36 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_36 << endl;
          
          float Bin_r_36 = 0;
          if (B_r_36 > 0){
              Bin_r_36 =  2* ( (S_r_36 + B_r_36) * log(1+S_r_36/B_r_36) - S_r_36 );
              //Bin_r_36 = (S_r_36/sqrt(B_r_36))*(S_r_36/sqrt(B_r_36));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_36) << endl;
          

          Sum_r_36 += Bin_r_36 ;
          QuadraticSum_r_36 = sqrt(Sum_r_36);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_36 << endl;

          h362->SetBinContent(j,QuadraticSum_r_36);
          h362->SetLineColor(kGreen-9);
          h362->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax36 = 1.1*h361->GetMaximum();
    float scale36 = 5000 / rightmax36;
    h361->Scale(scale36);
    h361->Draw("SAMEHIST");
    
    h362->Scale(scale36);
    h362->Draw("SAMEHIST");
    

    TGaxis*axis36 = new TGaxis(2000,0,2000,5000,0,rightmax36,510,"+L");
    axis36->SetTitle("Quadratic Sum of significance");
    axis36->SetTitleSize(0.03);
    axis36->SetLabelSize(0.025);
    axis36->Draw();
    
    pad362[k]->cd();
    TLegend *leg36 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg36->SetBorderSize(1);
    leg36->SetFillColor(0);
    leg36->SetTextFont(42);
    leg36->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg36->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg36->AddEntry(h361, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg36->AddEntry(h362, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg36->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut36_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_36 << endl;
        cout << "" << endl;
          
      }
    
     
     
    cout << " " << endl;
    cout << "  ===========================================================   mMMC   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut37 = 13;
    TCut cut37_1[n_cut37] = { "mMMC<80000", "mMMC<90000", "mMMC<100000", "mMMC<110000", "mMMC<120000", "mMMC<130000", "mMMC<140000", "mMMC<150000", "mMMC<160000", "mMMC<170000", "mMMC<180000", "mMMC<190000","mMMC<200000" };
    string cut37_2[n_cut37] = { "mMMC<80GeV", "mMMC<90GeV", "mMMC<100GeV", "mMMC<110GeV", "mMMC<120GeV", "mMMC<130GeV", "mMMC<140GeV", "mMMC<150GeV", "mMMC<160GeV", "mMMC<170GeV", "mMMC<180GeV", "mMMC<190GeV","mMMC<200GeV" };
    

      TCanvas *canvas37[n_cut37] ;
      canvas37[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas37[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas37[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas37[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas37[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas37[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas37[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas37[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas37[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas37[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas37[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas37[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas37[12] = new TCanvas ("c12", "Mhh",980,580);
    
      TPad *pad371[n_cut37];
      pad371[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad371[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad371[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad371[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad371[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad371[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad371[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad371[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad371[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad371[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad371[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad371[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad371[12] = new TPad ("pad12", "", 0,0,0.75,1);
    
      TPad *pad372[n_cut37];
      pad372[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad372[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad372[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad372[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad372[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad372[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad372[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad372[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad372[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad372[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad372[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad372[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad372[12] = new TPad ("pad12", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut37;k++) {
           canvas37[k]->cd();
           pad371[k]->Draw();
           pad372[k]->Draw();
           
           pad371[k]->cd();
           pad371[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut37_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut37_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut37_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut37_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut37_1[k]),  "SAMEHIST");
        }
        
        THStack *hs37 = new THStack("hs37", "");
        for(int i= 0; i<9 ; i++){ hs37->Add(h_hist[i], "hist1"); }
        hs37->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut37_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h371 = new TH1F("h371","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_37 = 0;
       float B_l_37_0 = 0;
       float B_l_37_1 = 0;
       float B_l_37_2 = 0;
       float B_l_37_3 = 0;
       float B_l_37_4 = 0;
       float B_l_37_5 = 0;
       float B_l_37_6 = 0;
       float B_l_37_7 = 0;
       float B_l_37_8 = 0;
        
       float QuadraticSum_l_37 = 0;
       float Sum_l_37 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_37 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_37 << endl;
           B_l_37_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_37_8 << endl;
           B_l_37_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_37_7 << endl;
           B_l_37_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_37_6 << endl;
           B_l_37_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_37_5 << endl;
           B_l_37_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_37_4 << endl;
           B_l_37_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_37_3 << endl;
           B_l_37_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_37_2 << endl;
           B_l_37_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_37_1 << endl;
           B_l_37_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_37_0 << endl;
           
           float B_l_37 = 0;
           for(int i = 0; i<9; i++) { B_l_37 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_37 << endl;
           
           float Bin_l_37 = 0;
           if (B_l_37 > 0){
               Bin_l_37 =  2* ( (S_l_37 + B_l_37) * log(1+S_l_37/B_l_37) - S_l_37 );
               //Bin_l_37 = (S_l_37/sqrt(B_l_37))*(S_l_37/sqrt(B_l_37));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_37) << endl; //
           

           Sum_l_37 += Bin_l_37 ;
           QuadraticSum_l_37 = sqrt(Sum_l_37);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_37 << endl; //

           h371->SetBinContent(j,QuadraticSum_l_37);
           h371->SetLineColor(kBlue-9);
           h371->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h372 = new TH1F("h372","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_37 = 0;
       float B_r_37_0 = 0;
       float B_r_37_1 = 0;
       float B_r_37_2 = 0;
       float B_r_37_3 = 0;
       float B_r_37_4 = 0;
       float B_r_37_5 = 0;
       float B_r_37_6 = 0;
       float B_r_37_7 = 0;
       float B_r_37_8 = 0;
        
       float QuadraticSum_r_37 = 0;
       float Sum_r_37 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_37 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_37 << endl;
          B_r_37_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_37_8 << endl;
          B_r_37_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_37_7 << endl;
          B_r_37_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_37_6 << endl;
          B_r_37_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_37_5 << endl;
          B_r_37_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_37_4 << endl;
          B_r_37_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_37_3 << endl;
          B_r_37_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_37_2 << endl;
          B_r_37_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_37_1 << endl;
          B_r_37_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_37_0 << endl;
          
          float B_r_37 = 0;
          for(int i = 0; i<9; i++) { B_r_37 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_37 << endl;
          
          float Bin_r_37 = 0;
          if (B_r_37 > 0){
              Bin_r_37 =  2* ( (S_r_37 + B_r_37) * log(1+S_r_37/B_r_37) - S_r_37 );
              //Bin_r_37 = (S_r_37/sqrt(B_r_37))*(S_r_37/sqrt(B_r_37));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_37) << endl;
          

          Sum_r_37 += Bin_r_37 ;
          QuadraticSum_r_37 = sqrt(Sum_r_37);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_37 << endl;

          h372->SetBinContent(j,QuadraticSum_r_37);
          h372->SetLineColor(kGreen-9);
          h372->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax37 = 1.1*h371->GetMaximum();
    float scale37 = 5000 / rightmax37;
    h371->Scale(scale37);
    h371->Draw("SAMEHIST");
    
    h372->Scale(scale37);
    h372->Draw("SAMEHIST");
    

    TGaxis*axis37 = new TGaxis(2000,0,2000,5000,0,rightmax37,510,"+L");
    axis37->SetTitle("Quadratic Sum of significance");
    axis37->SetTitleSize(0.03);
    axis37->SetLabelSize(0.025);
    axis37->Draw();
    
    pad372[k]->cd();
    TLegend *leg37 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg37->SetBorderSize(1);
    leg37->SetFillColor(0);
    leg37->SetTextFont(42);
    leg37->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg37->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg37->AddEntry(h371, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg37->AddEntry(h372, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg37->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut37_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_37 << endl;
        cout << "" << endl;
          
      } 
    
     
    cout << " " << endl;
    cout << "  ===========================================================   Mhh   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut38 = 46;
    TCut cut38_1[n_cut38] = { "Mhh>200000", "Mhh>210000", "Mhh>220000", "Mhh>230000", "Mhh>240000", "Mhh>250000", "Mhh>260000", "Mhh>270000", "Mhh>280000", "Mhh>290000", "Mhh>300000", "Mhh>310000", "Mhh>320000", "Mhh>330000", "Mhh>340000", "Mhh>350000", "Mhh>360000", "Mhh>370000", "Mhh>380000", "Mhh>390000", "Mhh>400000", "Mhh>410000", "Mhh>420000", "Mhh>430000", "Mhh>440000", "Mhh>450000", "Mhh>460000", "Mhh>470000", "Mhh>480000", "Mhh>490000", "Mhh>500000", "Mhh>510000", "Mhh>520000", "Mhh>530000", "Mhh>540000", "Mhh>550000", "Mhh>560000", "Mhh>570000", "Mhh>580000", "Mhh>590000", "Mhh>600000", "Mhh>610000", "Mhh>620000", "Mhh>630000", "Mhh>640000", "Mhh>650000" };
    string cut38_2[n_cut38] = { "Mhh>200GeV", "Mhh>210GeV", "Mhh>220GeV", "Mhh>230GeV", "Mhh>240GeV", "Mhh>250GeV", "Mhh>260GeV", "Mhh>270GeV", "Mhh>280GeV", "Mhh>290GeV", "Mhh>300GeV", "Mhh>310GeV", "Mhh>320GeV", "Mhh>330GeV", "Mhh>340GeV", "Mhh>350GeV", "Mhh>360GeV", "Mhh>370GeV", "Mhh>380GeV", "Mhh>390GeV", "Mhh>400GeV", "Mhh>410GeV", "Mhh>420GeV", "Mhh>430GeV", "Mhh>440GeV", "Mhh>450GeV", "Mhh>460GeV", "Mhh>470GeV", "Mhh>480GeV", "Mhh>490GeV", "Mhh>500GeV", "Mhh>510GeV", "Mhh>520GeV", "Mhh>530GeV", "Mhh>540GeV", "Mhh>550GeV", "Mhh>560GeV", "Mhh>570GeV", "Mhh>580GeV", "Mhh>590GeV", "Mhh>600GeV", "Mhh>610GeV", "Mhh>620GeV", "Mhh>630GeV", "Mhh>640GeV", "Mhh>650GeV" };
    

      TCanvas *canvas38[n_cut38] ;
      canvas38[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas38[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas38[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas38[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas38[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas38[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas38[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas38[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas38[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas38[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas38[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas38[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas38[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas38[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas38[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas38[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas38[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas38[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas38[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas38[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas38[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas38[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas38[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas38[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas38[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas38[25] = new TCanvas ("c25", "Mhh",980,580);
      canvas38[26] = new TCanvas ("c26", "Mhh",980,580);
      canvas38[27] = new TCanvas ("c27", "Mhh",980,580);
      canvas38[28] = new TCanvas ("c28", "Mhh",980,580);
      canvas38[29] = new TCanvas ("c29", "Mhh",980,580);
      canvas38[30] = new TCanvas ("c30", "Mhh",980,580);
      canvas38[31] = new TCanvas ("c31", "Mhh",980,580);
      canvas38[32] = new TCanvas ("c32", "Mhh",980,580);
      canvas38[33] = new TCanvas ("c33", "Mhh",980,580);
      canvas38[34] = new TCanvas ("c34", "Mhh",980,580);
      canvas38[35] = new TCanvas ("c35", "Mhh",980,580);
      canvas38[36] = new TCanvas ("c36", "Mhh",980,580);
      canvas38[37] = new TCanvas ("c37", "Mhh",980,580);
      canvas38[38] = new TCanvas ("c38", "Mhh",980,580);
      canvas38[39] = new TCanvas ("c39", "Mhh",980,580);
      canvas38[40] = new TCanvas ("c40", "Mhh",980,580);
      canvas38[41] = new TCanvas ("c41", "Mhh",980,580);
      canvas38[42] = new TCanvas ("c42", "Mhh",980,580);
      canvas38[43] = new TCanvas ("c43", "Mhh",980,580);
      canvas38[44] = new TCanvas ("c44", "Mhh",980,580);
      canvas38[45] = new TCanvas ("c45", "Mhh",980,580);
    
      TPad *pad381[n_cut38];
      pad381[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad381[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad381[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad381[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad381[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad381[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad381[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad381[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad381[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad381[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad381[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad381[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad381[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad381[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad381[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad381[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad381[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad381[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad381[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad381[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad381[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad381[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad381[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad381[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad381[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad381[25] = new TPad ("pad25", "", 0,0,0.75,1);
      pad381[26] = new TPad ("pad26", "", 0,0,0.75,1);
      pad381[27] = new TPad ("pad27", "", 0,0,0.75,1);
      pad381[28] = new TPad ("pad28", "", 0,0,0.75,1);
      pad381[29] = new TPad ("pad29", "", 0,0,0.75,1);
      pad381[30] = new TPad ("pad30", "", 0,0,0.75,1);
      pad381[31] = new TPad ("pad31", "", 0,0,0.75,1);
      pad381[32] = new TPad ("pad32", "", 0,0,0.75,1);
      pad381[33] = new TPad ("pad33", "", 0,0,0.75,1);
      pad381[34] = new TPad ("pad34", "", 0,0,0.75,1);
      pad381[35] = new TPad ("pad35", "", 0,0,0.75,1);
      pad381[36] = new TPad ("pad36", "", 0,0,0.75,1);
      pad381[37] = new TPad ("pad37", "", 0,0,0.75,1);
      pad381[38] = new TPad ("pad38", "", 0,0,0.75,1);
      pad381[39] = new TPad ("pad39", "", 0,0,0.75,1);
      pad381[40] = new TPad ("pad40", "", 0,0,0.75,1);
      pad381[41] = new TPad ("pad41", "", 0,0,0.75,1);
      pad381[42] = new TPad ("pad42", "", 0,0,0.75,1);
      pad381[43] = new TPad ("pad43", "", 0,0,0.75,1);
      pad381[44] = new TPad ("pad44", "", 0,0,0.75,1);
      pad381[45] = new TPad ("pad45", "", 0,0,0.75,1);
    
      TPad *pad382[n_cut38];
      pad382[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad382[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad382[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad382[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad382[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad382[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad382[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad382[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad382[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad382[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad382[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad382[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad382[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad382[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad382[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad382[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad382[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad382[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad382[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad382[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad382[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad382[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad382[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad382[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad382[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad382[25] = new TPad ("pad25", "",0.73,0,1,1);
      pad382[26] = new TPad ("pad26", "", 0.73,0,1,1);
      pad382[27] = new TPad ("pad27", "", 0.73,0,1,1);
      pad382[28] = new TPad ("pad28", "", 0.73,0,1,1);
      pad382[29] = new TPad ("pad29", "", 0.73,0,1,1);
      pad382[30] = new TPad ("pad30", "", 0.73,0,1,1);
      pad382[31] = new TPad ("pad31", "", 0.73,0,1,1);
      pad382[32] = new TPad ("pad32", "", 0.73,0,1,1);
      pad382[33] = new TPad ("pad33", "", 0.73,0,1,1);
      pad382[34] = new TPad ("pad34", "", 0.73,0,1,1);
      pad382[35] = new TPad ("pad35", "", 0.73,0,1,1);
      pad382[36] = new TPad ("pad36", "", 0.73,0,1,1);
      pad382[37] = new TPad ("pad37", "", 0.73,0,1,1);
      pad382[38] = new TPad ("pad38", "", 0.73,0,1,1);
      pad382[39] = new TPad ("pad39", "", 0.73,0,1,1);
      pad382[40] = new TPad ("pad40", "", 0.73,0,1,1);
      pad382[41] = new TPad ("pad41", "", 0.73,0,1,1);
      pad382[42] = new TPad ("pad42", "", 0.73,0,1,1);
      pad382[43] = new TPad ("pad43", "", 0.73,0,1,1);
      pad382[44] = new TPad ("pad44", "", 0.73,0,1,1);
      pad382[45] = new TPad ("pad45", "", 0.73,0,1,1);
      
      for (int k=0;k<n_cut38;k++) {
           canvas38[k]->cd();
           pad381[k]->Draw();
           pad382[k]->Draw();
           
           pad381[k]->cd();
           pad381[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut38_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut38_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut38_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut38_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut38_1[k]),  "SAMEHIST");
        }
        
        THStack *hs38 = new THStack("hs38", "");
        for(int i= 0; i<9 ; i++){ hs38->Add(h_hist[i], "hist1"); }
        hs38->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut38_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h381 = new TH1F("h381","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_38 = 0;
       float B_l_38_0 = 0;
       float B_l_38_1 = 0;
       float B_l_38_2 = 0;
       float B_l_38_3 = 0;
       float B_l_38_4 = 0;
       float B_l_38_5 = 0;
       float B_l_38_6 = 0;
       float B_l_38_7 = 0;
       float B_l_38_8 = 0;
        
       float QuadraticSum_l_38 = 0;
       float Sum_l_38 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_38 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_38 << endl;
           B_l_38_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_38_8 << endl;
           B_l_38_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_38_7 << endl;
           B_l_38_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_38_6 << endl;
           B_l_38_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_38_5 << endl;
           B_l_38_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_38_4 << endl;
           B_l_38_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_38_3 << endl;
           B_l_38_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_38_2 << endl;
           B_l_38_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_38_1 << endl;
           B_l_38_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_38_0 << endl;
           
           float B_l_38 = 0;
           for(int i = 0; i<9; i++) { B_l_38 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_38 << endl;
           
           float Bin_l_38 = 0;
           if (B_l_38 > 0){
               Bin_l_38 =  2* ( (S_l_38 + B_l_38) * log(1+S_l_38/B_l_38) - S_l_38 );
               //Bin_l_38 = (S_l_38/sqrt(B_l_38))*(S_l_38/sqrt(B_l_38));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_38) << endl; //
           

           Sum_l_38 += Bin_l_38 ;
           QuadraticSum_l_38 = sqrt(Sum_l_38);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_38 << endl; //

           h381->SetBinContent(j,QuadraticSum_l_38);
           h381->SetLineColor(kBlue-9);
           h381->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h382 = new TH1F("h382","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_38 = 0;
       float B_r_38_0 = 0;
       float B_r_38_1 = 0;
       float B_r_38_2 = 0;
       float B_r_38_3 = 0;
       float B_r_38_4 = 0;
       float B_r_38_5 = 0;
       float B_r_38_6 = 0;
       float B_r_38_7 = 0;
       float B_r_38_8 = 0;
        
       float QuadraticSum_r_38 = 0;
       float Sum_r_38 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_38 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_38 << endl;
          B_r_38_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_38_8 << endl;
          B_r_38_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_38_7 << endl;
          B_r_38_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_38_6 << endl;
          B_r_38_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_38_5 << endl;
          B_r_38_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_38_4 << endl;
          B_r_38_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_38_3 << endl;
          B_r_38_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_38_2 << endl;
          B_r_38_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_38_1 << endl;
          B_r_38_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_38_0 << endl;
          
          float B_r_38 = 0;
          for(int i = 0; i<9; i++) { B_r_38 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_38 << endl;
          
          float Bin_r_38 = 0;
          if (B_r_38 > 0){
              Bin_r_38 =  2* ( (S_r_38 + B_r_38) * log(1+S_r_38/B_r_38) - S_r_38 );
              //Bin_r_38 = (S_r_38/sqrt(B_r_38))*(S_r_38/sqrt(B_r_38));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_38) << endl;
          

          Sum_r_38 += Bin_r_38 ;
          QuadraticSum_r_38 = sqrt(Sum_r_38);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_38 << endl;

          h382->SetBinContent(j,QuadraticSum_r_38);
          h382->SetLineColor(kGreen-9);
          h382->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax38 = 1.1*h381->GetMaximum();
    float scale38 = 5000 / rightmax38;
    h381->Scale(scale38);
    h381->Draw("SAMEHIST");
    
    h382->Scale(scale38);
    h382->Draw("SAMEHIST");
    

    TGaxis*axis38 = new TGaxis(2000,0,2000,5000,0,rightmax38,510,"+L");
    axis38->SetTitle("Quadratic Sum of significance");
    axis38->SetTitleSize(0.03);
    axis38->SetLabelSize(0.025);
    axis38->Draw();
    
    pad382[k]->cd();
    TLegend *leg38 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg38->SetBorderSize(1);
    leg38->SetFillColor(0);
    leg38->SetTextFont(42);
    leg38->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg38->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg38->AddEntry(h381, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg38->AddEntry(h382, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg38->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut38_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_38 << endl;
        cout << "" << endl;
          
      }
     
    /* 
    cout << " " << endl;
    cout << "  ===========================================================   MT2   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut39 = 24;
    TCut cut39_1[n_cut39] = { "MT2>10000", "MT2>110000", "MT2>120000", "MT2>130000", "MT2>140000", "MT2>150000", "MT2>160000", "MT2>170000", "MT2>180000", "MT2>190000", "MT2>200000", "MT2>210000", "MT2>220000", "MT2>230000", "MT2>240000", "MT2>250000", "MT2>260000", "MT2>270000", "MT2>280000", "MT2>290000", "MT2>300000", "MT2>310000", "MT2>320000", "MT2>330000" };
    string cut39_2[n_cut39] = { "MT2>10GeV", "MT2>110GeV", "MT2>120GeV", "MT2>130GeV", "MT2>140GeV", "MT2>150GeV", "MT2>160GeV", "MT2>170GeV", "MT2>180GeV", "MT2>190GeV", "MT2>200GeV", "MT2>210GeV", "MT2>220GeV", "MT2>230GeV", "MT2>240GeV", "MT2>250GeV", "MT2>260GeV", "MT2>270GeV", "MT2>280GeV", "MT2>290GeV", "MT2>300GeV", "MT2>310GeV", "MT2>320GeV", "MT2>330GeV" };
    

      TCanvas *canvas39[n_cut39] ;
      canvas39[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas39[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas39[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas39[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas39[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas39[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas39[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas39[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas39[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas39[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas39[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas39[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas39[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas39[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas39[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas39[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas39[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas39[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas39[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas39[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas39[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas39[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas39[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas39[23] = new TCanvas ("c23", "Mhh",980,580);
    
      TPad *pad391[n_cut39];
      pad391[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad391[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad391[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad391[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad391[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad391[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad391[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad391[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad391[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad391[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad391[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad391[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad391[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad391[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad391[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad391[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad391[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad391[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad391[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad391[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad391[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad391[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad391[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad391[23] = new TPad ("pad23", "", 0,0,0.75,1);
    
      TPad *pad392[n_cut39];
      pad392[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad392[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad392[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad392[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad392[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad392[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad392[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad392[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad392[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad392[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad392[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad392[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad392[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad392[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad392[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad392[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad392[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad392[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad392[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad392[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad392[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad392[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad392[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad392[23] = new TPad ("pad23", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut39;k++) {
           canvas39[k]->cd();
           pad391[k]->Draw();
           pad392[k]->Draw();
           
           pad391[k]->cd();
           pad391[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut39_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut39_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut39_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut39_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut39_1[k]),  "SAMEHIST");
        }
        
        THStack *hs39 = new THStack("hs39", "");
        for(int i= 0; i<9 ; i++){ hs39->Add(h_hist[i], "hist1"); }
        hs39->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut39_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h391 = new TH1F("h391","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_39 = 0;
       float B_l_39_0 = 0;
       float B_l_39_1 = 0;
       float B_l_39_2 = 0;
       float B_l_39_3 = 0;
       float B_l_39_4 = 0;
       float B_l_39_5 = 0;
       float B_l_39_6 = 0;
       float B_l_39_7 = 0;
       float B_l_39_8 = 0;
        
       float QuadraticSum_l_39 = 0;
       float Sum_l_39 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_39 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_39 << endl;
           B_l_39_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_39_8 << endl;
           B_l_39_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_39_7 << endl;
           B_l_39_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_39_6 << endl;
           B_l_39_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_39_5 << endl;
           B_l_39_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_39_4 << endl;
           B_l_39_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_39_3 << endl;
           B_l_39_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_39_2 << endl;
           B_l_39_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_39_1 << endl;
           B_l_39_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_39_0 << endl;
           
           float B_l_39 = 0;
           for(int i = 0; i<9; i++) { B_l_39 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_39 << endl;
           
           float Bin_l_39 = 0;
           if (B_l_39 > 0){
               Bin_l_39 =  2* ( (S_l_39 + B_l_39) * log(1+S_l_39/B_l_39) - S_l_39 );
               //Bin_l_39 = (S_l_39/sqrt(B_l_39))*(S_l_39/sqrt(B_l_39));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_39) << endl; //
           

           Sum_l_39 += Bin_l_39 ;
           QuadraticSum_l_39 = sqrt(Sum_l_39);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_39 << endl; //

           h391->SetBinContent(j,QuadraticSum_l_39);
           h391->SetLineColor(kBlue-9);
           h391->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h392 = new TH1F("h392","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_39 = 0;
       float B_r_39_0 = 0;
       float B_r_39_1 = 0;
       float B_r_39_2 = 0;
       float B_r_39_3 = 0;
       float B_r_39_4 = 0;
       float B_r_39_5 = 0;
       float B_r_39_6 = 0;
       float B_r_39_7 = 0;
       float B_r_39_8 = 0;
        
       float QuadraticSum_r_39 = 0;
       float Sum_r_39 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_39 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_39 << endl;
          B_r_39_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_39_8 << endl;
          B_r_39_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_39_7 << endl;
          B_r_39_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_39_6 << endl;
          B_r_39_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_39_5 << endl;
          B_r_39_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_39_4 << endl;
          B_r_39_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_39_3 << endl;
          B_r_39_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_39_2 << endl;
          B_r_39_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_39_1 << endl;
          B_r_39_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_39_0 << endl;
          
          float B_r_39 = 0;
          for(int i = 0; i<9; i++) { B_r_39 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_39 << endl;
          
          float Bin_r_39 = 0;
          if (B_r_39 > 0){
              Bin_r_39 =  2* ( (S_r_39 + B_r_39) * log(1+S_r_39/B_r_39) - S_r_39 );
              //Bin_r_39 = (S_r_39/sqrt(B_r_39))*(S_r_39/sqrt(B_r_39));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_39) << endl;
          

          Sum_r_39 += Bin_r_39 ;
          QuadraticSum_r_39 = sqrt(Sum_r_39);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_39 << endl;

          h392->SetBinContent(j,QuadraticSum_r_39);
          h392->SetLineColor(kGreen-9);
          h392->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax39 = 1.1*h391->GetMaximum();
    float scale39 = 5000 / rightmax39;
    h391->Scale(scale39);
    h391->Draw("SAMEHIST");
    
    h392->Scale(scale39);
    h392->Draw("SAMEHIST");
    

    TGaxis*axis39 = new TGaxis(2000,0,2000,5000,0,rightmax39,510,"+L");
    axis39->SetTitle("Quadratic Sum of significance");
    axis39->SetTitleSize(0.03);
    axis39->SetLabelSize(0.025);
    axis39->Draw();
    
    pad392[k]->cd();
    TLegend *leg39 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg39->SetBorderSize(1);
    leg39->SetFillColor(0);
    leg39->SetTextFont(42);
    leg39->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg39->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg39->AddEntry(h391, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg39->AddEntry(h392, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg39->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut39_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_39 << endl;
        cout << "" << endl;
          
      }
    
    */ 
    cout << " " << endl;
    cout << "  ===========================================================   MtW   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut40 = 24;
    TCut cut40_1[n_cut40] = { "MtW<30000", "MtW<40000", "MtW<50000", "MtW<60000", "MtW<70000", "MtW<80000", "MtW<90000", "MtW<100000", "MtW<110000", "MtW<120000", "MtW<130000", "MtW<140000", "MtW<150000", "MtW<160000", "MtW<170000", "MtW<180000", "MtW<190000","MtW<200000", "MtW<210000", "MtW<220000", "MtW<230000", "MtW<240000", "MtW<250000", "MtW<260000" };
    string cut40_2[n_cut40] = { "MtW<30GeV", "MtW<40GeV", "MtW<50GeV", "MtW<60GeV", "MtW<70GeV", "MtW<80GeV", "MtW<90GeV", "MtW<100GeV", "MtW<110GeV", "MtW<120GeV", "MtW<130GeV", "MtW<140GeV", "MtW<150GeV", "MtW<160GeV", "MtW<170GeV", "MtW<180GeV", "MtW<190GeV","MtW<200GeV", "MtW<210GeV", "MtW<220GeV", "MtW<230GeV", "MtW<240GeV", "MtW<250GeV", "MtW<260GeV" };
    

      TCanvas *canvas40[n_cut40] ;
      canvas40[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas40[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas40[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas40[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas40[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas40[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas40[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas40[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas40[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas40[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas40[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas40[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas40[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas40[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas40[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas40[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas40[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas40[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas40[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas40[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas40[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas40[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas40[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas40[23] = new TCanvas ("c23", "Mhh",980,580);
    
      TPad *pad401[n_cut40];
      pad401[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad401[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad401[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad401[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad401[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad401[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad401[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad401[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad401[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad401[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad401[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad401[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad401[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad401[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad401[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad401[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad401[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad401[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad401[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad401[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad401[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad401[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad401[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad401[23] = new TPad ("pad23", "", 0,0,0.75,1);
    
      TPad *pad402[n_cut40];
      pad402[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad402[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad402[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad402[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad402[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad402[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad402[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad402[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad402[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad402[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad402[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad402[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad402[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad402[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad402[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad402[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad402[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad402[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad402[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad402[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad402[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad402[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad402[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad402[23] = new TPad ("pad23", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut40;k++) {
           canvas40[k]->cd();
           pad401[k]->Draw();
           pad402[k]->Draw();
           
           pad401[k]->cd();
           pad401[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut40_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut40_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut40_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut40_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut40_1[k]),  "SAMEHIST");
        }
        
        THStack *hs40 = new THStack("hs40", "");
        for(int i= 0; i<9 ; i++){ hs40->Add(h_hist[i], "hist1"); }
        hs40->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut40_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h401 = new TH1F("h401","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_40 = 0;
       float B_l_40_0 = 0;
       float B_l_40_1 = 0;
       float B_l_40_2 = 0;
       float B_l_40_3 = 0;
       float B_l_40_4 = 0;
       float B_l_40_5 = 0;
       float B_l_40_6 = 0;
       float B_l_40_7 = 0;
       float B_l_40_8 = 0;
        
       float QuadraticSum_l_40 = 0;
       float Sum_l_40 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_40 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_40 << endl;
           B_l_40_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_40_8 << endl;
           B_l_40_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_40_7 << endl;
           B_l_40_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_40_6 << endl;
           B_l_40_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_40_5 << endl;
           B_l_40_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_40_4 << endl;
           B_l_40_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_40_3 << endl;
           B_l_40_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_40_2 << endl;
           B_l_40_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_40_1 << endl;
           B_l_40_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_40_0 << endl;
           
           float B_l_40 = 0;
           for(int i = 0; i<9; i++) { B_l_40 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_40 << endl;
           
           float Bin_l_40 = 0;
           if (B_l_40 > 0){
               Bin_l_40 =  2* ( (S_l_40 + B_l_40) * log(1+S_l_40/B_l_40) - S_l_40 );
               //Bin_l_40 = (S_l_40/sqrt(B_l_40))*(S_l_40/sqrt(B_l_40));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_40) << endl; //
           

           Sum_l_40 += Bin_l_40 ;
           QuadraticSum_l_40 = sqrt(Sum_l_40);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_40 << endl; //

           h401->SetBinContent(j,QuadraticSum_l_40);
           h401->SetLineColor(kBlue-9);
           h401->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h402 = new TH1F("h402","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_40 = 0;
       float B_r_40_0 = 0;
       float B_r_40_1 = 0;
       float B_r_40_2 = 0;
       float B_r_40_3 = 0;
       float B_r_40_4 = 0;
       float B_r_40_5 = 0;
       float B_r_40_6 = 0;
       float B_r_40_7 = 0;
       float B_r_40_8 = 0;
        
       float QuadraticSum_r_40 = 0;
       float Sum_r_40 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_40 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_40 << endl;
          B_r_40_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_40_8 << endl;
          B_r_40_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_40_7 << endl;
          B_r_40_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_40_6 << endl;
          B_r_40_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_40_5 << endl;
          B_r_40_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_40_4 << endl;
          B_r_40_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_40_3 << endl;
          B_r_40_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_40_2 << endl;
          B_r_40_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_40_1 << endl;
          B_r_40_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_40_0 << endl;
          
          float B_r_40 = 0;
          for(int i = 0; i<9; i++) { B_r_40 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_40 << endl;
          
          float Bin_r_40 = 0;
          if (B_r_40 > 0){
              Bin_r_40 =  2* ( (S_r_40 + B_r_40) * log(1+S_r_40/B_r_40) - S_r_40 );
              //Bin_r_40 = (S_r_40/sqrt(B_r_40))*(S_r_40/sqrt(B_r_40));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_40) << endl;
          

          Sum_r_40 += Bin_r_40 ;
          QuadraticSum_r_40 = sqrt(Sum_r_40);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_40 << endl;

          h402->SetBinContent(j,QuadraticSum_r_40);
          h402->SetLineColor(kGreen-9);
          h402->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax40 = 1.1*h401->GetMaximum();
    float scale40 = 5000 / rightmax40;
    h401->Scale(scale40);
    h401->Draw("SAMEHIST");
    
    h402->Scale(scale40);
    h402->Draw("SAMEHIST");
    

    TGaxis*axis40 = new TGaxis(2000,0,2000,5000,0,rightmax40,510,"+L");
    axis40->SetTitle("Quadratic Sum of significance");
    axis40->SetTitleSize(0.03);
    axis40->SetLabelSize(0.025);
    axis40->Draw();
    
    pad402[k]->cd();
    TLegend *leg40 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg40->SetBorderSize(1);
    leg40->SetFillColor(0);
    leg40->SetTextFont(42);
    leg40->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg40->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg40->AddEntry(h401, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg40->AddEntry(h402, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg40->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut40_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_40 << endl;
        cout << "" << endl;
          
      }
    
     /*
    cout << " " << endl;
    cout << "  ===========================================================   mVBFjj   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut41 = 26;
    TCut cut41_1[n_cut41] = { "mVBFjj>50000", "mVBFjj>100000", "mVBFjj>150000", "mVBFjj>200000", "mVBFjj>250000", "mVBFjj>300000", "mVBFjj>350000", "mVBFjj>400000", "mVBFjj>450000", "mVBFjj>500000", "mVBFjj>550000", "mVBFjj>600000", "mVBFjj>650000", "mVBFjj>700000", "mVBFjj>750000", "mVBFjj>800000", "mVBFjj>850000", "mVBFjj>900000", "mVBFjj>950000","mVBFjj>1000000", "mVBFjj>1050000", "mVBFjj>1100000", "mVBFjj>1150000", "mVBFjj>1200000", "mVBFjj>1250000", "mVBFjj>1300000" };
    string cut41_2[n_cut41] = { "mVBFjj>50GeV", "mVBFjj>100GeV", "mVBFjj>150GeV", "mVBFjj>200GeV", "mVBFjj>250GeV", "mVBFjj>300GeV", "mVBFjj>350GeV", "mVBFjj>400GeV", "mVBFjj>450GeV", "mVBFjj>500GeV", "mVBFjj>550GeV", "mVBFjj>600GeV", "mVBFjj>650GeV", "mVBFjj>700GeV", "mVBFjj>750GeV", "mVBFjj>800GeV", "mVBFjj>850GeV", "mVBFjj>900GeV", "mVBFjj>950GeV","mVBFjj>1000GeV", "mVBFjj>1050GeV", "mVBFjj>1100GeV", "mVBFjj>1150GeV", "mVBFjj>1200GeV", "mVBFjj>1250GeV", "mVBFjj>1300GeV" };
    

      TCanvas *canvas41[n_cut41] ;
      canvas41[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas41[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas41[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas41[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas41[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas41[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas41[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas41[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas41[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas41[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas41[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas41[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas41[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas41[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas41[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas41[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas41[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas41[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas41[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas41[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas41[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas41[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas41[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas41[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas41[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas41[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad411[n_cut41];
      pad411[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad411[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad411[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad411[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad411[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad411[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad411[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad411[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad411[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad411[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad411[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad411[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad411[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad411[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad411[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad411[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad411[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad411[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad411[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad411[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad411[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad411[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad411[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad411[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad411[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad411[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad412[n_cut41];
      pad412[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad412[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad412[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad412[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad412[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad412[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad412[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad412[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad412[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad412[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad412[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad412[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad412[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad412[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad412[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad412[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad412[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad412[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad412[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad412[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad412[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad412[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad412[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad412[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad412[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad412[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut41;k++) {
           canvas41[k]->cd();
           pad411[k]->Draw();
           pad412[k]->Draw();
           
           pad411[k]->cd();
           pad411[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut41_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut41_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut41_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut41_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut41_1[k]),  "SAMEHIST");
        }
        
        THStack *hs41 = new THStack("hs41", "");
        for(int i= 0; i<9 ; i++){ hs41->Add(h_hist[i], "hist1"); }
        hs41->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut41_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h411 = new TH1F("h411","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_41 = 0;
       float B_l_41_0 = 0;
       float B_l_41_1 = 0;
       float B_l_41_2 = 0;
       float B_l_41_3 = 0;
       float B_l_41_4 = 0;
       float B_l_41_5 = 0;
       float B_l_41_6 = 0;
       float B_l_41_7 = 0;
       float B_l_41_8 = 0;
        
       float QuadraticSum_l_41 = 0;
       float Sum_l_41 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_41 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_41 << endl;
           B_l_41_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_41_8 << endl;
           B_l_41_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_41_7 << endl;
           B_l_41_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_41_6 << endl;
           B_l_41_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_41_5 << endl;
           B_l_41_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_41_4 << endl;
           B_l_41_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_41_3 << endl;
           B_l_41_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_41_2 << endl;
           B_l_41_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_41_1 << endl;
           B_l_41_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_41_0 << endl;
           
           float B_l_41 = 0;
           for(int i = 0; i<9; i++) { B_l_41 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_41 << endl;
           
           float Bin_l_41 = 0;
           if (B_l_41 > 0){
               Bin_l_41 =  2* ( (S_l_41 + B_l_41) * log(1+S_l_41/B_l_41) - S_l_41 );
               //Bin_l_41 = (S_l_41/sqrt(B_l_41))*(S_l_41/sqrt(B_l_41));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_41) << endl; //
           

           Sum_l_41 += Bin_l_41 ;
           QuadraticSum_l_41 = sqrt(Sum_l_41);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_41 << endl; //

           h411->SetBinContent(j,QuadraticSum_l_41);
           h411->SetLineColor(kBlue-9);
           h411->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h412 = new TH1F("h412","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_41 = 0;
       float B_r_41_0 = 0;
       float B_r_41_1 = 0;
       float B_r_41_2 = 0;
       float B_r_41_3 = 0;
       float B_r_41_4 = 0;
       float B_r_41_5 = 0;
       float B_r_41_6 = 0;
       float B_r_41_7 = 0;
       float B_r_41_8 = 0;
        
       float QuadraticSum_r_41 = 0;
       float Sum_r_41 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_41 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_41 << endl;
          B_r_41_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_41_8 << endl;
          B_r_41_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_41_7 << endl;
          B_r_41_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_41_6 << endl;
          B_r_41_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_41_5 << endl;
          B_r_41_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_41_4 << endl;
          B_r_41_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_41_3 << endl;
          B_r_41_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_41_2 << endl;
          B_r_41_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_41_1 << endl;
          B_r_41_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_41_0 << endl;
          
          float B_r_41 = 0;
          for(int i = 0; i<9; i++) { B_r_41 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_41 << endl;
          
          float Bin_r_41 = 0;
          if (B_r_41 > 0){
              Bin_r_41 =  2* ( (S_r_41 + B_r_41) * log(1+S_r_41/B_r_41) - S_r_41 );
              //Bin_r_41 = (S_r_41/sqrt(B_r_41))*(S_r_41/sqrt(B_r_41));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_41) << endl;
          

          Sum_r_41 += Bin_r_41 ;
          QuadraticSum_r_41 = sqrt(Sum_r_41);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_41 << endl;

          h412->SetBinContent(j,QuadraticSum_r_41);
          h412->SetLineColor(kGreen-9);
          h412->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax41 = 1.1*h411->GetMaximum();
    float scale41 = 5000 / rightmax41;
    h411->Scale(scale41);
    h411->Draw("SAMEHIST");
    
    h412->Scale(scale41);
    h412->Draw("SAMEHIST");
    

    TGaxis*axis41 = new TGaxis(2000,0,2000,5000,0,rightmax41,510,"+L");
    axis41->SetTitle("Quadratic Sum of significance");
    axis41->SetTitleSize(0.03);
    axis41->SetLabelSize(0.025);
    axis41->Draw();
    
    pad412[k]->cd();
    TLegend *leg41 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg41->SetBorderSize(1);
    leg41->SetFillColor(0);
    leg41->SetTextFont(42);
    leg41->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg41->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg41->AddEntry(h411, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg41->AddEntry(h412, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg41->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut41_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_41 << endl;
        cout << "" << endl;
          
      }
     
    */
    /*
    cout << " " << endl;
    cout << "  ===========================================================   Mvis   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut42 = 26;
    TCut cut42_1[n_cut42] = { "Mvis<10000", "Mvis<20000", "Mvis<30000", "Mvis<40000", "Mvis<50000", "Mvis<60000", "Mvis<70000", "Mvis<80000", "Mvis<90000", "Mvis<100000", "Mvis<110000", "Mvis<120000", "Mvis<130000", "Mvis<140000", "Mvis<150000", "Mvis<160000", "Mvis<170000", "Mvis<180000", "Mvis<190000","Mvis<200000", "Mvis<210000", "Mvis<220000", "Mvis<230000", "Mvis<240000", "Mvis<250000", "Mvis<260000" };
    string cut42_2[n_cut42] = { "Mvis<10GeV", "Mvis<20GeV", "Mvis<30GeV", "Mvis<40GeV", "Mvis<50GeV", "Mvis<60GeV", "Mvis<70GeV", "Mvis<80GeV", "Mvis<90GeV", "Mvis<100GeV", "Mvis<110GeV", "Mvis<120GeV", "Mvis<130GeV", "Mvis<140GeV", "Mvis<150GeV", "Mvis<160GeV", "Mvis<170GeV", "Mvis<180GeV", "Mvis<190GeV","Mvis<200GeV", "Mvis<210GeV", "Mvis<220GeV", "Mvis<230GeV", "Mvis<240GeV", "Mvis<250GeV", "Mvis<260GeV" };
    

      TCanvas *canvas42[n_cut42] ;
      canvas42[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas42[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas42[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas42[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas42[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas42[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas42[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas42[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas42[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas42[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas42[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas42[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas42[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas42[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas42[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas42[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas42[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas42[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas42[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas42[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas42[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas42[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas42[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas42[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas42[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas42[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad421[n_cut42];
      pad421[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad421[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad421[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad421[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad421[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad421[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad421[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad421[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad421[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad421[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad421[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad421[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad421[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad421[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad421[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad421[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad421[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad421[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad421[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad421[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad421[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad421[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad421[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad421[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad421[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad421[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad422[n_cut42];
      pad422[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad422[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad422[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad422[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad422[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad422[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad422[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad422[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad422[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad422[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad422[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad422[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad422[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad422[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad422[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad422[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad422[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad422[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad422[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad422[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad422[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad422[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad422[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad422[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad422[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad422[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut42;k++) {
           canvas42[k]->cd();
           pad421[k]->Draw();
           pad422[k]->Draw();
           
           pad421[k]->cd();
           pad421[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut42_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut42_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut42_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut42_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut42_1[k]),  "SAMEHIST");
        }
        
        THStack *hs42 = new THStack("hs42", "");
        for(int i= 0; i<9 ; i++){ hs42->Add(h_hist[i], "hist1"); }
        hs42->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut42_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h421 = new TH1F("h421","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_42 = 0;
       float B_l_42_0 = 0;
       float B_l_42_1 = 0;
       float B_l_42_2 = 0;
       float B_l_42_3 = 0;
       float B_l_42_4 = 0;
       float B_l_42_5 = 0;
       float B_l_42_6 = 0;
       float B_l_42_7 = 0;
       float B_l_42_8 = 0;
        
       float QuadraticSum_l_42 = 0;
       float Sum_l_42 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_42 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_42 << endl;
           B_l_42_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_42_8 << endl;
           B_l_42_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_42_7 << endl;
           B_l_42_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_42_6 << endl;
           B_l_42_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_42_5 << endl;
           B_l_42_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_42_4 << endl;
           B_l_42_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_42_3 << endl;
           B_l_42_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_42_2 << endl;
           B_l_42_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_42_1 << endl;
           B_l_42_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_42_0 << endl;
           
           float B_l_42 = 0;
           for(int i = 0; i<9; i++) { B_l_42 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_42 << endl;
           
           float Bin_l_42 = 0;
           if (B_l_42 > 0){
               Bin_l_42 =  2* ( (S_l_42 + B_l_42) * log(1+S_l_42/B_l_42) - S_l_42 );
               //Bin_l_42 = (S_l_42/sqrt(B_l_42))*(S_l_42/sqrt(B_l_42));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_42) << endl; //
           

           Sum_l_42 += Bin_l_42 ;
           QuadraticSum_l_42 = sqrt(Sum_l_42);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_42 << endl; //

           h421->SetBinContent(j,QuadraticSum_l_42);
           h421->SetLineColor(kBlue-9);
           h421->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h422 = new TH1F("h422","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_42 = 0;
       float B_r_42_0 = 0;
       float B_r_42_1 = 0;
       float B_r_42_2 = 0;
       float B_r_42_3 = 0;
       float B_r_42_4 = 0;
       float B_r_42_5 = 0;
       float B_r_42_6 = 0;
       float B_r_42_7 = 0;
       float B_r_42_8 = 0;
        
       float QuadraticSum_r_42 = 0;
       float Sum_r_42 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_42 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_42 << endl;
          B_r_42_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_42_8 << endl;
          B_r_42_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_42_7 << endl;
          B_r_42_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_42_6 << endl;
          B_r_42_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_42_5 << endl;
          B_r_42_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_42_4 << endl;
          B_r_42_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_42_3 << endl;
          B_r_42_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_42_2 << endl;
          B_r_42_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_42_1 << endl;
          B_r_42_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_42_0 << endl;
          
          float B_r_42 = 0;
          for(int i = 0; i<9; i++) { B_r_42 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_42 << endl;
          
          float Bin_r_42 = 0;
          if (B_r_42 > 0){
              Bin_r_42 =  2* ( (S_r_42 + B_r_42) * log(1+S_r_42/B_r_42) - S_r_42 );
              //Bin_r_42 = (S_r_42/sqrt(B_r_42))*(S_r_42/sqrt(B_r_42));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_42) << endl;
          

          Sum_r_42 += Bin_r_42 ;
          QuadraticSum_r_42 = sqrt(Sum_r_42);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_42 << endl;

          h422->SetBinContent(j,QuadraticSum_r_42);
          h422->SetLineColor(kGreen-9);
          h422->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax42 = 1.1*h421->GetMaximum();
    float scale42 = 5000 / rightmax42;
    h421->Scale(scale42);
    h421->Draw("SAMEHIST");
    
    h422->Scale(scale42);
    h422->Draw("SAMEHIST");
    

    TGaxis*axis42 = new TGaxis(2000,0,2000,5000,0,rightmax42,510,"+L");
    axis42->SetTitle("Quadratic Sum of significance");
    axis42->SetTitleSize(0.03);
    axis42->SetLabelSize(0.025);
    axis42->Draw();
    
    pad422[k]->cd();
    TLegend *leg42 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg42->SetBorderSize(1);
    leg42->SetFillColor(0);
    leg42->SetTextFont(42);
    leg42->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg42->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg42->AddEntry(h421, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg42->AddEntry(h422, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg42->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut42_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_42 << endl;
        cout << "" << endl;
          
      }
    */
     /*
    cout << " " << endl;
    cout << "  ===========================================================   Mw   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut43 = 26;
    TCut cut43_1[n_cut43] = { "Mw>10000", "Mw>20000", "Mw>30000", "Mw>40000", "Mw>50000", "Mw>60000", "Mw>70000", "Mw>80000", "Mw>90000", "Mw>100000", "Mw>110000", "Mw>120000", "Mw>130000", "Mw>140000", "Mw>150000", "Mw>160000", "Mw>170000", "Mw>180000", "Mw>190000","Mw>200000", "Mw>210000", "Mw>220000", "Mw>230000", "Mw>240000", "Mw>250000", "Mw>260000" };
    string cut43_2[n_cut43] = { "Mw>10GeV", "Mw>20GeV", "Mw>30GeV", "Mw>40GeV", "Mw>50GeV", "Mw>60GeV", "Mw>70GeV", "Mw>80GeV", "Mw>90GeV", "Mw>100GeV", "Mw>110GeV", "Mw>120GeV", "Mw>130GeV", "Mw>140GeV", "Mw>150GeV", "Mw>160GeV", "Mw>170GeV", "Mw>180GeV", "Mw>190GeV","Mw>200GeV", "Mw>210GeV", "Mw>220GeV", "Mw>230GeV", "Mw>240GeV", "Mw>250GeV", "Mw>260GeV" };
    

      TCanvas *canvas43[n_cut43] ;
      canvas43[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas43[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas43[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas43[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas43[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas43[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas43[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas43[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas43[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas43[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas43[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas43[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas43[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas43[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas43[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas43[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas43[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas43[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas43[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas43[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas43[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas43[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas43[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas43[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas43[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas43[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad431[n_cut43];
      pad431[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad431[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad431[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad431[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad431[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad431[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad431[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad431[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad431[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad431[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad431[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad431[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad431[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad431[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad431[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad431[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad431[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad431[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad431[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad431[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad431[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad431[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad431[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad431[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad431[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad431[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad432[n_cut43];
      pad432[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad432[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad432[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad432[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad432[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad432[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad432[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad432[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad432[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad432[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad432[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad432[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad432[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad432[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad432[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad432[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad432[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad432[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad432[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad432[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad432[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad432[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad432[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad432[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad432[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad432[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut43;k++) {
           canvas43[k]->cd();
           pad431[k]->Draw();
           pad432[k]->Draw();
           
           pad431[k]->cd();
           pad431[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut43_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut43_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut43_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut43_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut43_1[k]),  "SAMEHIST");
        }
        
        THStack *hs43 = new THStack("hs43", "");
        for(int i= 0; i<9 ; i++){ hs43->Add(h_hist[i], "hist1"); }
        hs43->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut43_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h431 = new TH1F("h431","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_43 = 0;
       float B_l_43_0 = 0;
       float B_l_43_1 = 0;
       float B_l_43_2 = 0;
       float B_l_43_3 = 0;
       float B_l_43_4 = 0;
       float B_l_43_5 = 0;
       float B_l_43_6 = 0;
       float B_l_43_7 = 0;
       float B_l_43_8 = 0;
        
       float QuadraticSum_l_43 = 0;
       float Sum_l_43 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_43 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_43 << endl;
           B_l_43_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_43_8 << endl;
           B_l_43_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_43_7 << endl;
           B_l_43_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_43_6 << endl;
           B_l_43_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_43_5 << endl;
           B_l_43_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_43_4 << endl;
           B_l_43_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_43_3 << endl;
           B_l_43_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_43_2 << endl;
           B_l_43_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_43_1 << endl;
           B_l_43_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_43_0 << endl;
           
           float B_l_43 = 0;
           for(int i = 0; i<9; i++) { B_l_43 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_43 << endl;
           
           float Bin_l_43 = 0;
           if (B_l_43 > 0){
               Bin_l_43 =  2* ( (S_l_43 + B_l_43) * log(1+S_l_43/B_l_43) - S_l_43 );
               //Bin_l_43 = (S_l_43/sqrt(B_l_43))*(S_l_43/sqrt(B_l_43));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_43) << endl; //
           

           Sum_l_43 += Bin_l_43 ;
           QuadraticSum_l_43 = sqrt(Sum_l_43);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_43 << endl; //

           h431->SetBinContent(j,QuadraticSum_l_43);
           h431->SetLineColor(kBlue-9);
           h431->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h432 = new TH1F("h432","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_43 = 0;
       float B_r_43_0 = 0;
       float B_r_43_1 = 0;
       float B_r_43_2 = 0;
       float B_r_43_3 = 0;
       float B_r_43_4 = 0;
       float B_r_43_5 = 0;
       float B_r_43_6 = 0;
       float B_r_43_7 = 0;
       float B_r_43_8 = 0;
        
       float QuadraticSum_r_43 = 0;
       float Sum_r_43 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_43 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_43 << endl;
          B_r_43_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_43_8 << endl;
          B_r_43_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_43_7 << endl;
          B_r_43_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_43_6 << endl;
          B_r_43_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_43_5 << endl;
          B_r_43_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_43_4 << endl;
          B_r_43_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_43_3 << endl;
          B_r_43_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_43_2 << endl;
          B_r_43_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_43_1 << endl;
          B_r_43_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_43_0 << endl;
          
          float B_r_43 = 0;
          for(int i = 0; i<9; i++) { B_r_43 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_43 << endl;
          
          float Bin_r_43 = 0;
          if (B_r_43 > 0){
              Bin_r_43 =  2* ( (S_r_43 + B_r_43) * log(1+S_r_43/B_r_43) - S_r_43 );
              //Bin_r_43 = (S_r_43/sqrt(B_r_43))*(S_r_43/sqrt(B_r_43));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_43) << endl;
          

          Sum_r_43 += Bin_r_43 ;
          QuadraticSum_r_43 = sqrt(Sum_r_43);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_43 << endl;

          h432->SetBinContent(j,QuadraticSum_r_43);
          h432->SetLineColor(kGreen-9);
          h432->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax43 = 1.1*h431->GetMaximum();
    float scale43 = 5000 / rightmax43;
    h431->Scale(scale43);
    h431->Draw("SAMEHIST");
    
    h432->Scale(scale43);
    h432->Draw("SAMEHIST");
    

    TGaxis*axis43 = new TGaxis(2000,0,2000,5000,0,rightmax43,510,"+L");
    axis43->SetTitle("Quadratic Sum of significance");
    axis43->SetTitleSize(0.03);
    axis43->SetLabelSize(0.025);
    axis43->Draw();
    
    pad432[k]->cd();
    TLegend *leg43 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg43->SetBorderSize(1);
    leg43->SetFillColor(0);
    leg43->SetTextFont(42);
    leg43->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg43->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg43->AddEntry(h431, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg43->AddEntry(h432, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg43->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut43_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_43 << endl;
        cout << "" << endl;
          
      }
    */
    
    cout << " " << endl;
    cout << "  ===========================================================   pTB1   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut48 = 26;
    TCut cut48_1[n_cut48] = { "pTB1>10000", "pTB1>20000", "pTB1>30000", "pTB1>40000", "pTB1>50000", "pTB1>60000", "pTB1>70000", "pTB1>80000", "pTB1>90000", "pTB1>100000", "pTB1>110000", "pTB1>120000", "pTB1>130000", "pTB1>140000", "pTB1>150000", "pTB1>160000", "pTB1>170000", "pTB1>180000", "pTB1>190000","pTB1>200000", "pTB1>210000", "pTB1>220000", "pTB1>230000", "pTB1>240000", "pTB1>250000", "pTB1>260000" };
    string cut48_2[n_cut48] = { "pTB1>10GeV", "pTB1>20GeV", "pTB1>30GeV", "pTB1>40GeV", "pTB1>50GeV", "pTB1>60GeV", "pTB1>70GeV", "pTB1>80GeV", "pTB1>90GeV", "pTB1>100GeV", "pTB1>110GeV", "pTB1>120GeV", "pTB1>130GeV", "pTB1>140GeV", "pTB1>150GeV", "pTB1>160GeV", "pTB1>170GeV", "pTB1>180GeV", "pTB1>190GeV","pTB1>200GeV", "pTB1>210GeV", "pTB1>220GeV", "pTB1>230GeV", "pTB1>240GeV", "pTB1>250GeV", "pTB1>260GeV" };
    

      TCanvas *canvas48[n_cut48] ;
      canvas48[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas48[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas48[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas48[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas48[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas48[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas48[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas48[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas48[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas48[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas48[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas48[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas48[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas48[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas48[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas48[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas48[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas48[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas48[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas48[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas48[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas48[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas48[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas48[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas48[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas48[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad481[n_cut48];
      pad481[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad481[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad481[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad481[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad481[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad481[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad481[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad481[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad481[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad481[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad481[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad481[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad481[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad481[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad481[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad481[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad481[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad481[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad481[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad481[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad481[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad481[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad481[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad481[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad481[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad481[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad482[n_cut48];
      pad482[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad482[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad482[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad482[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad482[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad482[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad482[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad482[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad482[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad482[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad482[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad482[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad482[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad482[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad482[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad482[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad482[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad482[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad482[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad482[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad482[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad482[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad482[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad482[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad482[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad482[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut48;k++) {
           canvas48[k]->cd();
           pad481[k]->Draw();
           pad482[k]->Draw();
           
           pad481[k]->cd();
           pad481[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut48_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut48_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut48_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut48_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut48_1[k]),  "SAMEHIST");
        }
        
        THStack *hs48 = new THStack("hs48", "");
        for(int i= 0; i<9 ; i++){ hs48->Add(h_hist[i], "hist1"); }
        hs48->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut48_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h481 = new TH1F("h481","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_48 = 0;
       float B_l_48_0 = 0;
       float B_l_48_1 = 0;
       float B_l_48_2 = 0;
       float B_l_48_3 = 0;
       float B_l_48_4 = 0;
       float B_l_48_5 = 0;
       float B_l_48_6 = 0;
       float B_l_48_7 = 0;
       float B_l_48_8 = 0;
        
       float QuadraticSum_l_48 = 0;
       float Sum_l_48 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_48 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_48 << endl;
           B_l_48_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_48_8 << endl;
           B_l_48_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_48_7 << endl;
           B_l_48_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_48_6 << endl;
           B_l_48_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_48_5 << endl;
           B_l_48_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_48_4 << endl;
           B_l_48_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_48_3 << endl;
           B_l_48_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_48_2 << endl;
           B_l_48_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_48_1 << endl;
           B_l_48_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_48_0 << endl;
           
           float B_l_48 = 0;
           for(int i = 0; i<9; i++) { B_l_48 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_48 << endl;
           
           float Bin_l_48 = 0;
           if (B_l_48 > 0){
               Bin_l_48 =  2* ( (S_l_48 + B_l_48) * log(1+S_l_48/B_l_48) - S_l_48 );
               //Bin_l_48 = (S_l_48/sqrt(B_l_48))*(S_l_48/sqrt(B_l_48));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_48) << endl; //
           

           Sum_l_48 += Bin_l_48 ;
           QuadraticSum_l_48 = sqrt(Sum_l_48);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_48 << endl; //

           h481->SetBinContent(j,QuadraticSum_l_48);
           h481->SetLineColor(kBlue-9);
           h481->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h482 = new TH1F("h482","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_48 = 0;
       float B_r_48_0 = 0;
       float B_r_48_1 = 0;
       float B_r_48_2 = 0;
       float B_r_48_3 = 0;
       float B_r_48_4 = 0;
       float B_r_48_5 = 0;
       float B_r_48_6 = 0;
       float B_r_48_7 = 0;
       float B_r_48_8 = 0;
        
       float QuadraticSum_r_48 = 0;
       float Sum_r_48 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_48 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_48 << endl;
          B_r_48_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_48_8 << endl;
          B_r_48_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_48_7 << endl;
          B_r_48_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_48_6 << endl;
          B_r_48_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_48_5 << endl;
          B_r_48_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_48_4 << endl;
          B_r_48_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_48_3 << endl;
          B_r_48_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_48_2 << endl;
          B_r_48_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_48_1 << endl;
          B_r_48_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_48_0 << endl;
          
          float B_r_48 = 0;
          for(int i = 0; i<9; i++) { B_r_48 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_48 << endl;
          
          float Bin_r_48 = 0;
          if (B_r_48 > 0){
              Bin_r_48 =  2* ( (S_r_48 + B_r_48) * log(1+S_r_48/B_r_48) - S_r_48 );
              //Bin_r_48 = (S_r_48/sqrt(B_r_48))*(S_r_48/sqrt(B_r_48));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_48) << endl;
          

          Sum_r_48 += Bin_r_48 ;
          QuadraticSum_r_48 = sqrt(Sum_r_48);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_48 << endl;

          h482->SetBinContent(j,QuadraticSum_r_48);
          h482->SetLineColor(kGreen-9);
          h482->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax48 = 1.1*h481->GetMaximum();
    float scale48 = 5000 / rightmax48;
    h481->Scale(scale48);
    h481->Draw("SAMEHIST");
    
    h482->Scale(scale48);
    h482->Draw("SAMEHIST");
    

    TGaxis*axis48 = new TGaxis(2000,0,2000,5000,0,rightmax48,510,"+L");
    axis48->SetTitle("Quadratic Sum of significance");
    axis48->SetTitleSize(0.03);
    axis48->SetLabelSize(0.025);
    axis48->Draw();
    
    pad482[k]->cd();
    TLegend *leg48 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg48->SetBorderSize(1);
    leg48->SetFillColor(0);
    leg48->SetTextFont(42);
    leg48->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg48->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg48->AddEntry(h481, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg48->AddEntry(h482, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg48->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut48_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_48 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   pTB2   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut49 = 21;
    TCut cut49_1[n_cut49] = { "pTB2>30000", "pTB2>40000", "pTB2>50000", "pTB2>60000", "pTB2>70000", "pTB2>80000", "pTB2>90000", "pTB2>100000", "pTB2>110000", "pTB2>120000", "pTB2>130000", "pTB2>140000", "pTB2>150000", "pTB2>160000", "pTB2>170000", "pTB2>180000", "pTB2>190000","pTB2>200000", "pTB2>210000", "pTB2>220000", "pTB2>230000" };
    string cut49_2[n_cut49] = { "pTB2>30GeV", "pTB2>40GeV", "pTB2>50GeV", "pTB2>60GeV", "pTB2>70GeV", "pTB2>80GeV", "pTB2>90GeV", "pTB2>100GeV", "pTB2>110GeV", "pTB2>120GeV", "pTB2>130GeV", "pTB2>140GeV", "pTB2>150GeV", "pTB2>160GeV", "pTB2>170GeV", "pTB2>180GeV", "pTB2>190GeV","pTB2>200GeV", "pTB2>210GeV", "pTB2>220GeV", "pTB2>230GeV" };
    

      TCanvas *canvas49[n_cut49] ;
      canvas49[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas49[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas49[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas49[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas49[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas49[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas49[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas49[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas49[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas49[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas49[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas49[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas49[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas49[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas49[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas49[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas49[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas49[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas49[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas49[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas49[20] = new TCanvas ("c20", "Mhh",980,580);
    
      TPad *pad491[n_cut49];
      pad491[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad491[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad491[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad491[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad491[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad491[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad491[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad491[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad491[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad491[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad491[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad491[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad491[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad491[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad491[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad491[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad491[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad491[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad491[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad491[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad491[20] = new TPad ("pad20", "", 0,0,0.75,1);
    
      TPad *pad492[n_cut49];
      pad492[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad492[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad492[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad492[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad492[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad492[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad492[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad492[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad492[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad492[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad492[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad492[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad492[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad492[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad492[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad492[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad492[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad492[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad492[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad492[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad492[20] = new TPad ("pad20", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut49;k++) {
           canvas49[k]->cd();
           pad491[k]->Draw();
           pad492[k]->Draw();
           
           pad491[k]->cd();
           pad491[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut49_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut49_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut49_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut49_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut49_1[k]),  "SAMEHIST");
        }
        
        THStack *hs49 = new THStack("hs49", "");
        for(int i= 0; i<9 ; i++){ hs49->Add(h_hist[i], "hist1"); }
        hs49->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut49_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h491 = new TH1F("h491","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_49 = 0;
       float B_l_49_0 = 0;
       float B_l_49_1 = 0;
       float B_l_49_2 = 0;
       float B_l_49_3 = 0;
       float B_l_49_4 = 0;
       float B_l_49_5 = 0;
       float B_l_49_6 = 0;
       float B_l_49_7 = 0;
       float B_l_49_8 = 0;
        
       float QuadraticSum_l_49 = 0;
       float Sum_l_49 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_49 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_49 << endl;
           B_l_49_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_49_8 << endl;
           B_l_49_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_49_7 << endl;
           B_l_49_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_49_6 << endl;
           B_l_49_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_49_5 << endl;
           B_l_49_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_49_4 << endl;
           B_l_49_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_49_3 << endl;
           B_l_49_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_49_2 << endl;
           B_l_49_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_49_1 << endl;
           B_l_49_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_49_0 << endl;
           
           float B_l_49 = 0;
           for(int i = 0; i<9; i++) { B_l_49 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_49 << endl;
           
           float Bin_l_49 = 0;
           if (B_l_49 > 0){
               Bin_l_49 =  2* ( (S_l_49 + B_l_49) * log(1+S_l_49/B_l_49) - S_l_49 );
               //Bin_l_49 = (S_l_49/sqrt(B_l_49))*(S_l_49/sqrt(B_l_49));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_49) << endl; //
           

           Sum_l_49 += Bin_l_49 ;
           QuadraticSum_l_49 = sqrt(Sum_l_49);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_49 << endl; //

           h491->SetBinContent(j,QuadraticSum_l_49);
           h491->SetLineColor(kBlue-9);
           h491->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h492 = new TH1F("h492","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_49 = 0;
       float B_r_49_0 = 0;
       float B_r_49_1 = 0;
       float B_r_49_2 = 0;
       float B_r_49_3 = 0;
       float B_r_49_4 = 0;
       float B_r_49_5 = 0;
       float B_r_49_6 = 0;
       float B_r_49_7 = 0;
       float B_r_49_8 = 0;
        
       float QuadraticSum_r_49 = 0;
       float Sum_r_49 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_49 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_49 << endl;
          B_r_49_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_49_8 << endl;
          B_r_49_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_49_7 << endl;
          B_r_49_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_49_6 << endl;
          B_r_49_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_49_5 << endl;
          B_r_49_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_49_4 << endl;
          B_r_49_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_49_3 << endl;
          B_r_49_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_49_2 << endl;
          B_r_49_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_49_1 << endl;
          B_r_49_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_49_0 << endl;
          
          float B_r_49 = 0;
          for(int i = 0; i<9; i++) { B_r_49 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_49 << endl;
          
          float Bin_r_49 = 0;
          if (B_r_49 > 0){
              Bin_r_49 =  2* ( (S_r_49 + B_r_49) * log(1+S_r_49/B_r_49) - S_r_49 );
              //Bin_r_49 = (S_r_49/sqrt(B_r_49))*(S_r_49/sqrt(B_r_49));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_49) << endl;
          

          Sum_r_49 += Bin_r_49 ;
          QuadraticSum_r_49 = sqrt(Sum_r_49);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_49 << endl;

          h492->SetBinContent(j,QuadraticSum_r_49);
          h492->SetLineColor(kGreen-9);
          h492->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax49 = 1.1*h491->GetMaximum();
    float scale49 = 5000 / rightmax49;
    h491->Scale(scale49);
    h491->Draw("SAMEHIST");
    
    h492->Scale(scale49);
    h492->Draw("SAMEHIST");
    

    TGaxis*axis49 = new TGaxis(2000,0,2000,5000,0,rightmax49,510,"+L");
    axis49->SetTitle("Quadratic Sum of significance");
    axis49->SetTitleSize(0.03);
    axis49->SetLabelSize(0.025);
    axis49->Draw();
    
    pad492[k]->cd();
    TLegend *leg49 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg49->SetBorderSize(1);
    leg49->SetFillColor(0);
    leg49->SetTextFont(42);
    leg49->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg49->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg49->AddEntry(h491, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg49->AddEntry(h492, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg49->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut49_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_49 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   pTBB   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut50 = 26;
    TCut cut50_1[n_cut50] = { "pTBB>10000", "pTBB>20000", "pTBB>30000", "pTBB>40000", "pTBB>50000", "pTBB>60000", "pTBB>70000", "pTBB>80000", "pTBB>90000", "pTBB>100000", "pTBB>110000", "pTBB>120000", "pTBB>130000", "pTBB>140000", "pTBB>150000", "pTBB>160000", "pTBB>170000", "pTBB>180000", "pTBB>190000","pTBB>200000", "pTBB>210000", "pTBB>220000", "pTBB>230000", "pTBB>240000", "pTBB>250000", "pTBB>260000" };
    string cut50_2[n_cut50] = { "pTBB>10GeV", "pTBB>20GeV", "pTBB>30GeV", "pTBB>40GeV", "pTBB>50GeV", "pTBB>60GeV", "pTBB>70GeV", "pTBB>80GeV", "pTBB>90GeV", "pTBB>100GeV", "pTBB>110GeV", "pTBB>120GeV", "pTBB>130GeV", "pTBB>140GeV", "pTBB>150GeV", "pTBB>160GeV", "pTBB>170GeV", "pTBB>180GeV", "pTBB>190GeV","pTBB>200GeV", "pTBB>210GeV", "pTBB>220GeV", "pTBB>230GeV", "pTBB>240GeV", "pTBB>250GeV", "pTBB>260GeV" };
    

      TCanvas *canvas50[n_cut50] ;
      canvas50[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas50[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas50[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas50[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas50[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas50[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas50[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas50[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas50[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas50[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas50[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas50[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas50[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas50[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas50[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas50[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas50[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas50[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas50[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas50[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas50[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas50[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas50[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas50[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas50[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas50[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad501[n_cut50];
      pad501[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad501[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad501[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad501[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad501[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad501[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad501[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad501[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad501[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad501[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad501[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad501[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad501[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad501[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad501[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad501[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad501[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad501[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad501[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad501[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad501[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad501[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad501[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad501[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad501[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad501[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad502[n_cut50];
      pad502[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad502[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad502[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad502[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad502[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad502[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad502[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad502[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad502[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad502[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad502[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad502[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad502[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad502[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad502[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad502[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad502[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad502[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad502[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad502[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad502[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad502[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad502[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad502[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad502[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad502[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut50;k++) {
           canvas50[k]->cd();
           pad501[k]->Draw();
           pad502[k]->Draw();
           
           pad501[k]->cd();
           pad501[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut50_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut50_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut50_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut50_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut50_1[k]),  "SAMEHIST");
        }
        
        THStack *hs50 = new THStack("hs50", "");
        for(int i= 0; i<9 ; i++){ hs50->Add(h_hist[i], "hist1"); }
        hs50->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut50_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h501 = new TH1F("h501","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_50 = 0;
       float B_l_50_0 = 0;
       float B_l_50_1 = 0;
       float B_l_50_2 = 0;
       float B_l_50_3 = 0;
       float B_l_50_4 = 0;
       float B_l_50_5 = 0;
       float B_l_50_6 = 0;
       float B_l_50_7 = 0;
       float B_l_50_8 = 0;
        
       float QuadraticSum_l_50 = 0;
       float Sum_l_50 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_50 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_50 << endl;
           B_l_50_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_50_8 << endl;
           B_l_50_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_50_7 << endl;
           B_l_50_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_50_6 << endl;
           B_l_50_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_50_5 << endl;
           B_l_50_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_50_4 << endl;
           B_l_50_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_50_3 << endl;
           B_l_50_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_50_2 << endl;
           B_l_50_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_50_1 << endl;
           B_l_50_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_50_0 << endl;
           
           float B_l_50 = 0;
           for(int i = 0; i<9; i++) { B_l_50 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_50 << endl;
           
           float Bin_l_50 = 0;
           if (B_l_50 > 0){
               Bin_l_50 =  2* ( (S_l_50 + B_l_50) * log(1+S_l_50/B_l_50) - S_l_50 );
               //Bin_l_50 = (S_l_50/sqrt(B_l_50))*(S_l_50/sqrt(B_l_50));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_50) << endl; //
           

           Sum_l_50 += Bin_l_50 ;
           QuadraticSum_l_50 = sqrt(Sum_l_50);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_50 << endl; //

           h501->SetBinContent(j,QuadraticSum_l_50);
           h501->SetLineColor(kBlue-9);
           h501->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h502 = new TH1F("h502","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_50 = 0;
       float B_r_50_0 = 0;
       float B_r_50_1 = 0;
       float B_r_50_2 = 0;
       float B_r_50_3 = 0;
       float B_r_50_4 = 0;
       float B_r_50_5 = 0;
       float B_r_50_6 = 0;
       float B_r_50_7 = 0;
       float B_r_50_8 = 0;
        
       float QuadraticSum_r_50 = 0;
       float Sum_r_50 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_50 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_50 << endl;
          B_r_50_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_50_8 << endl;
          B_r_50_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_50_7 << endl;
          B_r_50_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_50_6 << endl;
          B_r_50_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_50_5 << endl;
          B_r_50_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_50_4 << endl;
          B_r_50_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_50_3 << endl;
          B_r_50_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_50_2 << endl;
          B_r_50_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_50_1 << endl;
          B_r_50_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_50_0 << endl;
          
          float B_r_50 = 0;
          for(int i = 0; i<9; i++) { B_r_50 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_50 << endl;
          
          float Bin_r_50 = 0;
          if (B_r_50 > 0){
              Bin_r_50 =  2* ( (S_r_50 + B_r_50) * log(1+S_r_50/B_r_50) - S_r_50 );
              //Bin_r_50 = (S_r_50/sqrt(B_r_50))*(S_r_50/sqrt(B_r_50));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_50) << endl;
          

          Sum_r_50 += Bin_r_50 ;
          QuadraticSum_r_50 = sqrt(Sum_r_50);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_50 << endl;

          h502->SetBinContent(j,QuadraticSum_r_50);
          h502->SetLineColor(kGreen-9);
          h502->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax50 = 1.1*h501->GetMaximum();
    float scale50 = 5000 / rightmax50;
    h501->Scale(scale50);
    h501->Draw("SAMEHIST");
    
    h502->Scale(scale50);
    h502->Draw("SAMEHIST");
    

    TGaxis*axis50 = new TGaxis(2000,0,2000,5000,0,rightmax50,510,"+L");
    axis50->SetTitle("Quadratic Sum of significance");
    axis50->SetTitleSize(0.03);
    axis50->SetLabelSize(0.025);
    axis50->Draw();
    
    pad502[k]->cd();
    TLegend *leg50 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg50->SetBorderSize(1);
    leg50->SetFillColor(0);
    leg50->SetTextFont(42);
    leg50->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg50->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg50->AddEntry(h501, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg50->AddEntry(h502, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg50->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut50_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_50 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   pTtautau   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut52 = 24;
    TCut cut52_1[n_cut52] = { "pTtautau>30000", "pTtautau>40000", "pTtautau>50000", "pTtautau>60000", "pTtautau>70000", "pTtautau>80000", "pTtautau>90000", "pTtautau>100000", "pTtautau>110000", "pTtautau>120000", "pTtautau>130000", "pTtautau>140000", "pTtautau>150000", "pTtautau>160000", "pTtautau>170000", "pTtautau>180000", "pTtautau>190000","pTtautau>200000", "pTtautau>210000", "pTtautau>220000", "pTtautau>230000", "pTtautau>240000", "pTtautau>250000", "pTtautau>260000" };
    string cut52_2[n_cut52] = { "pTtautau>30GeV", "pTtautau>40GeV", "pTtautau>50GeV", "pTtautau>60GeV", "pTtautau>70GeV", "pTtautau>80GeV", "pTtautau>90GeV", "pTtautau>100GeV", "pTtautau>110GeV", "pTtautau>120GeV", "pTtautau>130GeV", "pTtautau>140GeV", "pTtautau>150GeV", "pTtautau>160GeV", "pTtautau>170GeV", "pTtautau>180GeV", "pTtautau>190GeV","pTtautau>200GeV", "pTtautau>210GeV", "pTtautau>220GeV", "pTtautau>230GeV", "pTtautau>240GeV", "pTtautau>250GeV", "pTtautau>260GeV" };
    

      TCanvas *canvas52[n_cut52] ;
      canvas52[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas52[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas52[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas52[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas52[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas52[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas52[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas52[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas52[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas52[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas52[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas52[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas52[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas52[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas52[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas52[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas52[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas52[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas52[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas52[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas52[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas52[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas52[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas52[23] = new TCanvas ("c23", "Mhh",980,580);
    
      TPad *pad521[n_cut52];
      pad521[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad521[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad521[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad521[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad521[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad521[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad521[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad521[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad521[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad521[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad521[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad521[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad521[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad521[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad521[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad521[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad521[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad521[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad521[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad521[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad521[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad521[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad521[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad521[23] = new TPad ("pad23", "", 0,0,0.75,1);
    
      TPad *pad522[n_cut52];
      pad522[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad522[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad522[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad522[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad522[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad522[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad522[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad522[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad522[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad522[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad522[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad522[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad522[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad522[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad522[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad522[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad522[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad522[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad522[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad522[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad522[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad522[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad522[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad522[23] = new TPad ("pad23", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut52;k++) {
           canvas52[k]->cd();
           pad521[k]->Draw();
           pad522[k]->Draw();
           
           pad521[k]->cd();
           pad521[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut52_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut52_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut52_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut52_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut52_1[k]),  "SAMEHIST");
        }
        
        THStack *hs52 = new THStack("hs52", "");
        for(int i= 0; i<9 ; i++){ hs52->Add(h_hist[i], "hist1"); }
        hs52->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut52_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h521 = new TH1F("h521","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_52 = 0;
       float B_l_52_0 = 0;
       float B_l_52_1 = 0;
       float B_l_52_2 = 0;
       float B_l_52_3 = 0;
       float B_l_52_4 = 0;
       float B_l_52_5 = 0;
       float B_l_52_6 = 0;
       float B_l_52_7 = 0;
       float B_l_52_8 = 0;
        
       float QuadraticSum_l_52 = 0;
       float Sum_l_52 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_52 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_52 << endl;
           B_l_52_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_52_8 << endl;
           B_l_52_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_52_7 << endl;
           B_l_52_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_52_6 << endl;
           B_l_52_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_52_5 << endl;
           B_l_52_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_52_4 << endl;
           B_l_52_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_52_3 << endl;
           B_l_52_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_52_2 << endl;
           B_l_52_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_52_1 << endl;
           B_l_52_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_52_0 << endl;
           
           float B_l_52 = 0;
           for(int i = 0; i<9; i++) { B_l_52 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_52 << endl;
           
           float Bin_l_52 = 0;
           if (B_l_52 > 0){
               Bin_l_52 =  2* ( (S_l_52 + B_l_52) * log(1+S_l_52/B_l_52) - S_l_52 );
               //Bin_l_52 = (S_l_52/sqrt(B_l_52))*(S_l_52/sqrt(B_l_52));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_52) << endl; //
           

           Sum_l_52 += Bin_l_52 ;
           QuadraticSum_l_52 = sqrt(Sum_l_52);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_52 << endl; //

           h521->SetBinContent(j,QuadraticSum_l_52);
           h521->SetLineColor(kBlue-9);
           h521->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h522 = new TH1F("h522","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_52 = 0;
       float B_r_52_0 = 0;
       float B_r_52_1 = 0;
       float B_r_52_2 = 0;
       float B_r_52_3 = 0;
       float B_r_52_4 = 0;
       float B_r_52_5 = 0;
       float B_r_52_6 = 0;
       float B_r_52_7 = 0;
       float B_r_52_8 = 0;
        
       float QuadraticSum_r_52 = 0;
       float Sum_r_52 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_52 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_52 << endl;
          B_r_52_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_52_8 << endl;
          B_r_52_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_52_7 << endl;
          B_r_52_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_52_6 << endl;
          B_r_52_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_52_5 << endl;
          B_r_52_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_52_4 << endl;
          B_r_52_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_52_3 << endl;
          B_r_52_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_52_2 << endl;
          B_r_52_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_52_1 << endl;
          B_r_52_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_52_0 << endl;
          
          float B_r_52 = 0;
          for(int i = 0; i<9; i++) { B_r_52 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_52 << endl;
          
          float Bin_r_52 = 0;
          if (B_r_52 > 0){
              Bin_r_52 =  2* ( (S_r_52 + B_r_52) * log(1+S_r_52/B_r_52) - S_r_52 );
              //Bin_r_52 = (S_r_52/sqrt(B_r_52))*(S_r_52/sqrt(B_r_52));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_52) << endl;
          

          Sum_r_52 += Bin_r_52 ;
          QuadraticSum_r_52 = sqrt(Sum_r_52);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_52 << endl;

          h522->SetBinContent(j,QuadraticSum_r_52);
          h522->SetLineColor(kGreen-9);
          h522->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax52 = 1.1*h521->GetMaximum();
    float scale52 = 5000 / rightmax52;
    h521->Scale(scale52);
    h521->Draw("SAMEHIST");
    
    h522->Scale(scale52);
    h522->Draw("SAMEHIST");
    

    TGaxis*axis52 = new TGaxis(2000,0,2000,5000,0,rightmax52,510,"+L");
    axis52->SetTitle("Quadratic Sum of significance");
    axis52->SetTitleSize(0.03);
    axis52->SetLabelSize(0.025);
    axis52->Draw();
    
    pad522[k]->cd();
    TLegend *leg52 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg52->SetBorderSize(1);
    leg52->SetFillColor(0);
    leg52->SetTextFont(42);
    leg52->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg52->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg52->AddEntry(h521, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg52->AddEntry(h522, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg52->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut52_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_52 << endl;
        cout << "" << endl;
          
      }
     
     
    cout << " " << endl;
    cout << "  ===========================================================   pTVBFj1   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut53 = 26;
    TCut cut53_1[n_cut53] = { "pTVBFj1>10000", "pTVBFj1>20000", "pTVBFj1>30000", "pTVBFj1>40000", "pTVBFj1>50000", "pTVBFj1>60000", "pTVBFj1>70000", "pTVBFj1>80000", "pTVBFj1>90000", "pTVBFj1>100000", "pTVBFj1>110000", "pTVBFj1>120000", "pTVBFj1>130000", "pTVBFj1>140000", "pTVBFj1>150000", "pTVBFj1>160000", "pTVBFj1>170000", "pTVBFj1>180000", "pTVBFj1>190000","pTVBFj1>200000", "pTVBFj1>210000", "pTVBFj1>220000", "pTVBFj1>230000", "pTVBFj1>240000", "pTVBFj1>250000", "pTVBFj1>260000" };
    string cut53_2[n_cut53] = { "pTVBFj1>10GeV", "pTVBFj1>20GeV", "pTVBFj1>30GeV", "pTVBFj1>40GeV", "pTVBFj1>50GeV", "pTVBFj1>60GeV", "pTVBFj1>70GeV", "pTVBFj1>80GeV", "pTVBFj1>90GeV", "pTVBFj1>100GeV", "pTVBFj1>110GeV", "pTVBFj1>120GeV", "pTVBFj1>130GeV", "pTVBFj1>140GeV", "pTVBFj1>150GeV", "pTVBFj1>160GeV", "pTVBFj1>170GeV", "pTVBFj1>180GeV", "pTVBFj1>190GeV","pTVBFj1>200GeV", "pTVBFj1>210GeV", "pTVBFj1>220GeV", "pTVBFj1>230GeV", "pTVBFj1>240GeV", "pTVBFj1>250GeV", "pTVBFj1>260GeV" };
    

      TCanvas *canvas53[n_cut53] ;
      canvas53[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas53[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas53[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas53[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas53[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas53[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas53[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas53[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas53[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas53[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas53[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas53[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas53[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas53[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas53[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas53[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas53[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas53[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas53[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas53[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas53[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas53[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas53[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas53[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas53[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas53[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad531[n_cut53];
      pad531[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad531[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad531[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad531[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad531[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad531[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad531[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad531[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad531[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad531[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad531[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad531[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad531[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad531[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad531[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad531[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad531[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad531[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad531[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad531[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad531[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad531[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad531[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad531[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad531[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad531[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad532[n_cut53];
      pad532[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad532[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad532[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad532[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad532[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad532[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad532[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad532[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad532[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad532[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad532[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad532[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad532[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad532[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad532[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad532[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad532[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad532[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad532[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad532[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad532[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad532[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad532[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad532[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad532[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad532[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut53;k++) {
           canvas53[k]->cd();
           pad531[k]->Draw();
           pad532[k]->Draw();
           
           pad531[k]->cd();
           pad531[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut53_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut53_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut53_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut53_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut53_1[k]),  "SAMEHIST");
        }
        
        THStack *hs53 = new THStack("hs53", "");
        for(int i= 0; i<9 ; i++){ hs53->Add(h_hist[i], "hist1"); }
        hs53->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut53_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h531 = new TH1F("h531","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_53 = 0;
       float B_l_53_0 = 0;
       float B_l_53_1 = 0;
       float B_l_53_2 = 0;
       float B_l_53_3 = 0;
       float B_l_53_4 = 0;
       float B_l_53_5 = 0;
       float B_l_53_6 = 0;
       float B_l_53_7 = 0;
       float B_l_53_8 = 0;
        
       float QuadraticSum_l_53 = 0;
       float Sum_l_53 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_53 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_53 << endl;
           B_l_53_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_53_8 << endl;
           B_l_53_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_53_7 << endl;
           B_l_53_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_53_6 << endl;
           B_l_53_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_53_5 << endl;
           B_l_53_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_53_4 << endl;
           B_l_53_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_53_3 << endl;
           B_l_53_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_53_2 << endl;
           B_l_53_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_53_1 << endl;
           B_l_53_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_53_0 << endl;
           
           float B_l_53 = 0;
           for(int i = 0; i<9; i++) { B_l_53 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_53 << endl;
           
           float Bin_l_53 = 0;
           if (B_l_53 > 0){
               Bin_l_53 =  2* ( (S_l_53 + B_l_53) * log(1+S_l_53/B_l_53) - S_l_53 );
               //Bin_l_53 = (S_l_53/sqrt(B_l_53))*(S_l_53/sqrt(B_l_53));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_53) << endl; //
           

           Sum_l_53 += Bin_l_53 ;
           QuadraticSum_l_53 = sqrt(Sum_l_53);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_53 << endl; //

           h531->SetBinContent(j,QuadraticSum_l_53);
           h531->SetLineColor(kBlue-9);
           h531->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h532 = new TH1F("h532","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_53 = 0;
       float B_r_53_0 = 0;
       float B_r_53_1 = 0;
       float B_r_53_2 = 0;
       float B_r_53_3 = 0;
       float B_r_53_4 = 0;
       float B_r_53_5 = 0;
       float B_r_53_6 = 0;
       float B_r_53_7 = 0;
       float B_r_53_8 = 0;
        
       float QuadraticSum_r_53 = 0;
       float Sum_r_53 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_53 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_53 << endl;
          B_r_53_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_53_8 << endl;
          B_r_53_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_53_7 << endl;
          B_r_53_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_53_6 << endl;
          B_r_53_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_53_5 << endl;
          B_r_53_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_53_4 << endl;
          B_r_53_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_53_3 << endl;
          B_r_53_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_53_2 << endl;
          B_r_53_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_53_1 << endl;
          B_r_53_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_53_0 << endl;
          
          float B_r_53 = 0;
          for(int i = 0; i<9; i++) { B_r_53 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_53 << endl;
          
          float Bin_r_53 = 0;
          if (B_r_53 > 0){
              Bin_r_53 =  2* ( (S_r_53 + B_r_53) * log(1+S_r_53/B_r_53) - S_r_53 );
              //Bin_r_53 = (S_r_53/sqrt(B_r_53))*(S_r_53/sqrt(B_r_53));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_53) << endl;
          

          Sum_r_53 += Bin_r_53 ;
          QuadraticSum_r_53 = sqrt(Sum_r_53);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_53 << endl;

          h532->SetBinContent(j,QuadraticSum_r_53);
          h532->SetLineColor(kGreen-9);
          h532->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax53 = 1.1*h531->GetMaximum();
    float scale53 = 5000 / rightmax53;
    h531->Scale(scale53);
    h531->Draw("SAMEHIST");
    
    h532->Scale(scale53);
    h532->Draw("SAMEHIST");
    

    TGaxis*axis53 = new TGaxis(2000,0,2000,5000,0,rightmax53,510,"+L");
    axis53->SetTitle("Quadratic Sum of significance");
    axis53->SetTitleSize(0.03);
    axis53->SetLabelSize(0.025);
    axis53->Draw();
    
    pad532[k]->cd();
    TLegend *leg53 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg53->SetBorderSize(1);
    leg53->SetFillColor(0);
    leg53->SetTextFont(42);
    leg53->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg53->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg53->AddEntry(h531, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg53->AddEntry(h532, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg53->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut53_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_53 << endl;
        cout << "" << endl;
          
      }
     
     
    cout << " " << endl;
    cout << "  ===========================================================   pTVBFj2   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut54 = 26;
    TCut cut54_1[n_cut54] = { "pTVBFj2>10000", "pTVBFj2>20000", "pTVBFj2>30000", "pTVBFj2>40000", "pTVBFj2>50000", "pTVBFj2>60000", "pTVBFj2>70000", "pTVBFj2>80000", "pTVBFj2>90000", "pTVBFj2>100000", "pTVBFj2>110000", "pTVBFj2>120000", "pTVBFj2>130000", "pTVBFj2>140000", "pTVBFj2>150000", "pTVBFj2>160000", "pTVBFj2>170000", "pTVBFj2>180000", "pTVBFj2>190000","pTVBFj2>200000", "pTVBFj2>210000", "pTVBFj2>220000", "pTVBFj2>230000", "pTVBFj2>240000", "pTVBFj2>250000", "pTVBFj2>260000" };
    string cut54_2[n_cut54] = { "pTVBFj2>10GeV", "pTVBFj2>20GeV", "pTVBFj2>30GeV", "pTVBFj2>40GeV", "pTVBFj2>50GeV", "pTVBFj2>60GeV", "pTVBFj2>70GeV", "pTVBFj2>80GeV", "pTVBFj2>90GeV", "pTVBFj2>100GeV", "pTVBFj2>110GeV", "pTVBFj2>120GeV", "pTVBFj2>130GeV", "pTVBFj2>140GeV", "pTVBFj2>150GeV", "pTVBFj2>160GeV", "pTVBFj2>170GeV", "pTVBFj2>180GeV", "pTVBFj2>190GeV","pTVBFj2>200GeV", "pTVBFj2>210GeV", "pTVBFj2>220GeV", "pTVBFj2>230GeV", "pTVBFj2>240GeV", "pTVBFj2>250GeV", "pTVBFj2>260GeV" };
    

      TCanvas *canvas54[n_cut54] ;
      canvas54[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas54[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas54[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas54[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas54[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas54[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas54[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas54[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas54[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas54[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas54[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas54[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas54[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas54[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas54[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas54[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas54[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas54[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas54[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas54[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas54[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas54[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas54[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas54[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas54[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas54[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad541[n_cut54];
      pad541[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad541[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad541[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad541[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad541[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad541[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad541[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad541[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad541[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad541[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad541[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad541[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad541[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad541[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad541[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad541[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad541[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad541[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad541[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad541[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad541[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad541[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad541[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad541[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad541[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad541[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad542[n_cut54];
      pad542[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad542[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad542[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad542[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad542[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad542[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad542[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad542[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad542[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad542[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad542[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad542[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad542[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad542[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad542[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad542[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad542[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad542[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad542[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad542[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad542[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad542[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad542[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad542[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad542[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad542[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut54;k++) {
           canvas54[k]->cd();
           pad541[k]->Draw();
           pad542[k]->Draw();
           
           pad541[k]->cd();
           pad541[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut54_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut54_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut54_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut54_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut54_1[k]),  "SAMEHIST");
        }
        
        THStack *hs54 = new THStack("hs54", "");
        for(int i= 0; i<9 ; i++){ hs54->Add(h_hist[i], "hist1"); }
        hs54->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut54_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h541 = new TH1F("h541","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_54 = 0;
       float B_l_54_0 = 0;
       float B_l_54_1 = 0;
       float B_l_54_2 = 0;
       float B_l_54_3 = 0;
       float B_l_54_4 = 0;
       float B_l_54_5 = 0;
       float B_l_54_6 = 0;
       float B_l_54_7 = 0;
       float B_l_54_8 = 0;
        
       float QuadraticSum_l_54 = 0;
       float Sum_l_54 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_54 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_54 << endl;
           B_l_54_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_54_8 << endl;
           B_l_54_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_54_7 << endl;
           B_l_54_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_54_6 << endl;
           B_l_54_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_54_5 << endl;
           B_l_54_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_54_4 << endl;
           B_l_54_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_54_3 << endl;
           B_l_54_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_54_2 << endl;
           B_l_54_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_54_1 << endl;
           B_l_54_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_54_0 << endl;
           
           float B_l_54 = 0;
           for(int i = 0; i<9; i++) { B_l_54 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_54 << endl;
           
           float Bin_l_54 = 0;
           if (B_l_54 > 0){
               Bin_l_54 =  2* ( (S_l_54 + B_l_54) * log(1+S_l_54/B_l_54) - S_l_54 );
               //Bin_l_54 = (S_l_54/sqrt(B_l_54))*(S_l_54/sqrt(B_l_54));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_54) << endl; //
           

           Sum_l_54 += Bin_l_54 ;
           QuadraticSum_l_54 = sqrt(Sum_l_54);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_54 << endl; //

           h541->SetBinContent(j,QuadraticSum_l_54);
           h541->SetLineColor(kBlue-9);
           h541->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h542 = new TH1F("h542","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_54 = 0;
       float B_r_54_0 = 0;
       float B_r_54_1 = 0;
       float B_r_54_2 = 0;
       float B_r_54_3 = 0;
       float B_r_54_4 = 0;
       float B_r_54_5 = 0;
       float B_r_54_6 = 0;
       float B_r_54_7 = 0;
       float B_r_54_8 = 0;
        
       float QuadraticSum_r_54 = 0;
       float Sum_r_54 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_54 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_54 << endl;
          B_r_54_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_54_8 << endl;
          B_r_54_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_54_7 << endl;
          B_r_54_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_54_6 << endl;
          B_r_54_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_54_5 << endl;
          B_r_54_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_54_4 << endl;
          B_r_54_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_54_3 << endl;
          B_r_54_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_54_2 << endl;
          B_r_54_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_54_1 << endl;
          B_r_54_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_54_0 << endl;
          
          float B_r_54 = 0;
          for(int i = 0; i<9; i++) { B_r_54 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_54 << endl;
          
          float Bin_r_54 = 0;
          if (B_r_54 > 0){
              Bin_r_54 =  2* ( (S_r_54 + B_r_54) * log(1+S_r_54/B_r_54) - S_r_54 );
              //Bin_r_54 = (S_r_54/sqrt(B_r_54))*(S_r_54/sqrt(B_r_54));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_54) << endl;
          

          Sum_r_54 += Bin_r_54 ;
          QuadraticSum_r_54 = sqrt(Sum_r_54);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_54 << endl;

          h542->SetBinContent(j,QuadraticSum_r_54);
          h542->SetLineColor(kGreen-9);
          h542->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax54 = 1.1*h541->GetMaximum();
    float scale54 = 5000 / rightmax54;
    h541->Scale(scale54);
    h541->Draw("SAMEHIST");
    
    h542->Scale(scale54);
    h542->Draw("SAMEHIST");
    

    TGaxis*axis54 = new TGaxis(2000,0,2000,5000,0,rightmax54,510,"+L");
    axis54->SetTitle("Quadratic Sum of significance");
    axis54->SetTitleSize(0.03);
    axis54->SetLabelSize(0.025);
    axis54->Draw();
    
    pad542[k]->cd();
    TLegend *leg54 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg54->SetBorderSize(1);
    leg54->SetFillColor(0);
    leg54->SetTextFont(42);
    leg54->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg54->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg54->AddEntry(h541, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg54->AddEntry(h542, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg54->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut54_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_54 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   TauEta_abs   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut55 = 15;
    TCut cut55_1[n_cut55] = { "abs(TauEta)>0.2", "abs(TauEta)>0.4", "abs(TauEta)>0.6", "abs(TauEta)>0.8", "abs(TauEta)>1", "abs(TauEta)>1.2", "abs(TauEta)>1.4", "abs(TauEta)>1.6", "abs(TauEta)>1.8", "abs(TauEta)>2", "abs(TauEta)>2.2", "abs(TauEta)>2.4", "abs(TauEta)>2.6", "abs(TauEta)>2.8", "abs(TauEta)>3" };
    string cut55_2[n_cut55] = { "abs(TauEta)>0.2", "abs(TauEta)>0.4", "abs(TauEta)>0.6", "abs(TauEta)>0.8", "abs(TauEta)>1", "abs(TauEta)>1.2", "abs(TauEta)>1.4", "abs(TauEta)>1.6", "abs(TauEta)>1.8", "abs(TauEta)>2", "abs(TauEta)>2.2", "abs(TauEta)>2.4", "abs(TauEta)>2.6", "abs(TauEta)>2.8", "abs(TauEta)>3" };
    

      TCanvas *canvas55[n_cut55] ;
      canvas55[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas55[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas55[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas55[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas55[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas55[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas55[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas55[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas55[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas55[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas55[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas55[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas55[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas55[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas55[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad551[n_cut55];
      pad551[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad551[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad551[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad551[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad551[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad551[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad551[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad551[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad551[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad551[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad551[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad551[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad551[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad551[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad551[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad552[n_cut55];
      pad552[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad552[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad552[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad552[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad552[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad552[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad552[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad552[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad552[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad552[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad552[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad552[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad552[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad552[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad552[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut55;k++) {
           canvas55[k]->cd();
           pad551[k]->Draw();
           pad552[k]->Draw();
           
           pad551[k]->cd();
           pad551[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut55_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut55_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut55_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut55_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut55_1[k]),  "SAMEHIST");
        }
        
        THStack *hs55 = new THStack("hs55", "");
        for(int i= 0; i<9 ; i++){ hs55->Add(h_hist[i], "hist1"); }
        hs55->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut55_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h551 = new TH1F("h551","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_55 = 0;
       float B_l_55_0 = 0;
       float B_l_55_1 = 0;
       float B_l_55_2 = 0;
       float B_l_55_3 = 0;
       float B_l_55_4 = 0;
       float B_l_55_5 = 0;
       float B_l_55_6 = 0;
       float B_l_55_7 = 0;
       float B_l_55_8 = 0;
        
       float QuadraticSum_l_55 = 0;
       float Sum_l_55 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_55 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_55 << endl;
           B_l_55_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_55_8 << endl;
           B_l_55_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_55_7 << endl;
           B_l_55_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_55_6 << endl;
           B_l_55_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_55_5 << endl;
           B_l_55_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_55_4 << endl;
           B_l_55_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_55_3 << endl;
           B_l_55_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_55_2 << endl;
           B_l_55_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_55_1 << endl;
           B_l_55_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_55_0 << endl;
           
           float B_l_55 = 0;
           for(int i = 0; i<9; i++) { B_l_55 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_55 << endl;
           
           float Bin_l_55 = 0;
           if (B_l_55 > 0){
               Bin_l_55 =  2* ( (S_l_55 + B_l_55) * log(1+S_l_55/B_l_55) - S_l_55 );
               //Bin_l_55 = (S_l_55/sqrt(B_l_55))*(S_l_55/sqrt(B_l_55));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_55) << endl; //
           

           Sum_l_55 += Bin_l_55 ;
           QuadraticSum_l_55 = sqrt(Sum_l_55);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_55 << endl; //

           h551->SetBinContent(j,QuadraticSum_l_55);
           h551->SetLineColor(kBlue-9);
           h551->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h552 = new TH1F("h552","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_55 = 0;
       float B_r_55_0 = 0;
       float B_r_55_1 = 0;
       float B_r_55_2 = 0;
       float B_r_55_3 = 0;
       float B_r_55_4 = 0;
       float B_r_55_5 = 0;
       float B_r_55_6 = 0;
       float B_r_55_7 = 0;
       float B_r_55_8 = 0;
        
       float QuadraticSum_r_55 = 0;
       float Sum_r_55 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_55 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_55 << endl;
          B_r_55_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_55_8 << endl;
          B_r_55_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_55_7 << endl;
          B_r_55_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_55_6 << endl;
          B_r_55_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_55_5 << endl;
          B_r_55_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_55_4 << endl;
          B_r_55_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_55_3 << endl;
          B_r_55_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_55_2 << endl;
          B_r_55_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_55_1 << endl;
          B_r_55_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_55_0 << endl;
          
          float B_r_55 = 0;
          for(int i = 0; i<9; i++) { B_r_55 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_55 << endl;
          
          float Bin_r_55 = 0;
          if (B_r_55 > 0){
              Bin_r_55 =  2* ( (S_r_55 + B_r_55) * log(1+S_r_55/B_r_55) - S_r_55 );
              //Bin_r_55 = (S_r_55/sqrt(B_r_55))*(S_r_55/sqrt(B_r_55));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_55) << endl;
          

          Sum_r_55 += Bin_r_55 ;
          QuadraticSum_r_55 = sqrt(Sum_r_55);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_55 << endl;

          h552->SetBinContent(j,QuadraticSum_r_55);
          h552->SetLineColor(kGreen-9);
          h552->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax55 = 1.1*h551->GetMaximum();
    float scale55 = 5000 / rightmax55;
    h551->Scale(scale55);
    h551->Draw("SAMEHIST");
    
    h552->Scale(scale55);
    h552->Draw("SAMEHIST");
    

    TGaxis*axis55 = new TGaxis(2000,0,2000,5000,0,rightmax55,510,"+L");
    axis55->SetTitle("Quadratic Sum of significance");
    axis55->SetTitleSize(0.03);
    axis55->SetLabelSize(0.025);
    axis55->Draw();
    
    pad552[k]->cd();
    TLegend *leg55 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg55->SetBorderSize(1);
    leg55->SetFillColor(0);
    leg55->SetTextFont(42);
    leg55->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg55->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg55->AddEntry(h551, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg55->AddEntry(h552, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg55->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut55_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_55 << endl;
        cout << "" << endl;
          
      }
    
    
    
    cout << " " << endl;
    cout << "  ===========================================================   TauPhi   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut58 = 15;
    TCut cut58_1[n_cut58] = { "TauPhi<0.2", "TauPhi<0.4", "TauPhi<0.6", "TauPhi<0.8", "TauPhi<1", "TauPhi<1.2", "TauPhi<1.4", "TauPhi<1.6", "TauPhi<1.8", "TauPhi<2", "TauPhi<2.2", "TauPhi<2.4", "TauPhi<2.6", "TauPhi<2.8", "TauPhi<3" };
    string cut58_2[n_cut58] = { "TauPhi<0.2", "TauPhi<0.4", "TauPhi<0.6", "TauPhi<0.8", "TauPhi<1", "TauPhi<1.2", "TauPhi<1.4", "TauPhi<1.6", "TauPhi<1.8", "TauPhi<2", "TauPhi<2.2", "TauPhi<2.4", "TauPhi<2.6", "TauPhi<2.8", "TauPhi<3" };
    

      TCanvas *canvas58[n_cut58] ;
      canvas58[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas58[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas58[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas58[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas58[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas58[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas58[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas58[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas58[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas58[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas58[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas58[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas58[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas58[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas58[14] = new TCanvas ("c14", "Mhh",980,580);
    
      TPad *pad581[n_cut58];
      pad581[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad581[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad581[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad581[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad581[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad581[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad581[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad581[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad581[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad581[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad581[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad581[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad581[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad581[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad581[14] = new TPad ("pad14", "", 0,0,0.75,1);
    
      TPad *pad582[n_cut58];
      pad582[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad582[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad582[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad582[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad582[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad582[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad582[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad582[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad582[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad582[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad582[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad582[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad582[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad582[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad582[14] = new TPad ("pad14", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut58;k++) {
           canvas58[k]->cd();
           pad581[k]->Draw();
           pad582[k]->Draw();
           
           pad581[k]->cd();
           pad581[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut58_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut58_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut58_1[k]), "SAMEHIST");} //ttbar
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut58_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut58_1[k]),  "SAMEHIST");
        }
        
        THStack *hs58 = new THStack("hs58", "");
        for(int i= 0; i<9 ; i++){ hs58->Add(h_hist[i], "hist1"); }
        hs58->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut58_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h581 = new TH1F("h581","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_58 = 0;
       float B_l_58_0 = 0;
       float B_l_58_1 = 0;
       float B_l_58_2 = 0;
       float B_l_58_3 = 0;
       float B_l_58_4 = 0;
       float B_l_58_5 = 0;
       float B_l_58_6 = 0;
       float B_l_58_7 = 0;
       float B_l_58_8 = 0;
        
       float QuadraticSum_l_58 = 0;
       float Sum_l_58 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_58 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_58 << endl;
           B_l_58_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_58_8 << endl;
           B_l_58_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_58_7 << endl;
           B_l_58_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_58_6 << endl;
           B_l_58_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_58_5 << endl;
           B_l_58_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_58_4 << endl;
           B_l_58_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_58_3 << endl;
           B_l_58_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_58_2 << endl;
           B_l_58_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_58_1 << endl;
           B_l_58_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_58_0 << endl;
           
           float B_l_58 = 0;
           for(int i = 0; i<9; i++) { B_l_58 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_58 << endl;
           
           float Bin_l_58 = 0;
           if (B_l_58 > 0){
               Bin_l_58 =  2* ( (S_l_58 + B_l_58) * log(1+S_l_58/B_l_58) - S_l_58 );
               //Bin_l_58 = (S_l_58/sqrt(B_l_58))*(S_l_58/sqrt(B_l_58));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_58) << endl; //
           

           Sum_l_58 += Bin_l_58 ;
           QuadraticSum_l_58 = sqrt(Sum_l_58);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_58 << endl; //

           h581->SetBinContent(j,QuadraticSum_l_58);
           h581->SetLineColor(kBlue-9);
           h581->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h582 = new TH1F("h582","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_58 = 0;
       float B_r_58_0 = 0;
       float B_r_58_1 = 0;
       float B_r_58_2 = 0;
       float B_r_58_3 = 0;
       float B_r_58_4 = 0;
       float B_r_58_5 = 0;
       float B_r_58_6 = 0;
       float B_r_58_7 = 0;
       float B_r_58_8 = 0;
        
       float QuadraticSum_r_58 = 0;
       float Sum_r_58 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_58 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_58 << endl;
          B_r_58_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_58_8 << endl;
          B_r_58_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_58_7 << endl;
          B_r_58_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_58_6 << endl;
          B_r_58_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_58_5 << endl;
          B_r_58_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_58_4 << endl;
          B_r_58_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_58_3 << endl;
          B_r_58_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_58_2 << endl;
          B_r_58_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_58_1 << endl;
          B_r_58_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_58_0 << endl;
          
          float B_r_58 = 0;
          for(int i = 0; i<9; i++) { B_r_58 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_58 << endl;
          
          float Bin_r_58 = 0;
          if (B_r_58 > 0){
              Bin_r_58 =  2* ( (S_r_58 + B_r_58) * log(1+S_r_58/B_r_58) - S_r_58 );
              //Bin_r_58 = (S_r_58/sqrt(B_r_58))*(S_r_58/sqrt(B_r_58));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_58) << endl;
          

          Sum_r_58 += Bin_r_58 ;
          QuadraticSum_r_58 = sqrt(Sum_r_58);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_58 << endl;

          h582->SetBinContent(j,QuadraticSum_r_58);
          h582->SetLineColor(kGreen-9);
          h582->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax58 = 1.1*h581->GetMaximum();
    float scale58 = 5000 / rightmax58;
    h581->Scale(scale58);
    h581->Draw("SAMEHIST");
    
    h582->Scale(scale58);
    h582->Draw("SAMEHIST");
    

    TGaxis*axis58 = new TGaxis(2000,0,2000,5000,0,rightmax58,510,"+L");
    axis58->SetTitle("Quadratic Sum of significance");
    axis58->SetTitleSize(0.03);
    axis58->SetLabelSize(0.025);
    axis58->Draw();
    
    pad582[k]->cd();
    TLegend *leg58 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg58->SetBorderSize(1);
    leg58->SetFillColor(0);
    leg58->SetTextFont(42);
    leg58->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg58->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg58->AddEntry(h581, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg58->AddEntry(h582, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg58->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut58_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_58 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   TauPt   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut59 = 26;
    TCut cut59_1[n_cut59] = { "TauPt<10", "TauPt<20", "TauPt<30", "TauPt<40", "TauPt<50", "TauPt<60", "TauPt<70", "TauPt<80", "TauPt<90", "TauPt<100", "TauPt<110", "TauPt<120", "TauPt<130", "TauPt<140", "TauPt<150", "TauPt<160", "TauPt<170", "TauPt<180", "TauPt<190","TauPt<200", "TauPt<210", "TauPt<220", "TauPt<230", "TauPt<240", "TauPt<250", "TauPt<260" };
    string cut59_2[n_cut59] = { "TauPt<10GeV", "TauPt<20GeV", "TauPt<30GeV", "TauPt<40GeV", "TauPt<50GeV", "TauPt<60GeV", "TauPt<70GeV", "TauPt<80GeV", "TauPt<90GeV", "TauPt<100GeV", "TauPt<110GeV", "TauPt<120GeV", "TauPt<130GeV", "TauPt<140GeV", "TauPt<150GeV", "TauPt<160GeV", "TauPt<170GeV", "TauPt<180GeV", "TauPt<190GeV","TauPt<200GeV", "TauPt<210GeV", "TauPt<220GeV", "TauPt<230GeV", "TauPt<240GeV", "TauPt<250GeV", "TauPt<260GeV" };
    

      TCanvas *canvas59[n_cut59] ;
      canvas59[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas59[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas59[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas59[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas59[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas59[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas59[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas59[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas59[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas59[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas59[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas59[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas59[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas59[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas59[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas59[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas59[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas59[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas59[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas59[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas59[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas59[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas59[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas59[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas59[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas59[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad591[n_cut59];
      pad591[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad591[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad591[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad591[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad591[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad591[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad591[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad591[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad591[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad591[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad591[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad591[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad591[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad591[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad591[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad591[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad591[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad591[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad591[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad591[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad591[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad591[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad591[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad591[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad591[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad591[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      TPad *pad592[n_cut59];
      pad592[0] = new TPad ("pad0", "",0.73,0,1,1);
      pad592[1] = new TPad ("pad1", "",0.73,0,1,1);
      pad592[2] = new TPad ("pad2", "",0.73,0,1,1);
      pad592[3] = new TPad ("pad3", "",0.73,0,1,1);
      pad592[4] = new TPad ("pad4", "",0.73,0,1,1);
      pad592[5] = new TPad ("pad5", "",0.73,0,1,1);
      pad592[6] = new TPad ("pad6", "",0.73,0,1,1);
      pad592[7] = new TPad ("pad7", "",0.73,0,1,1);
      pad592[8] = new TPad ("pad8", "",0.73,0,1,1);
      pad592[9] = new TPad ("pad9", "",0.73,0,1,1);
      pad592[10] = new TPad ("pad10", "",0.73,0,1,1);
      pad592[11] = new TPad ("pad11", "",0.73,0,1,1);
      pad592[12] = new TPad ("pad12", "",0.73,0,1,1);
      pad592[13] = new TPad ("pad13", "",0.73,0,1,1);
      pad592[14] = new TPad ("pad14", "",0.73,0,1,1);
      pad592[15] = new TPad ("pad15", "",0.73,0,1,1);
      pad592[16] = new TPad ("pad16", "",0.73,0,1,1);
      pad592[17] = new TPad ("pad17", "",0.73,0,1,1);
      pad592[18] = new TPad ("pad18", "",0.73,0,1,1);
      pad592[19] = new TPad ("pad19", "",0.73,0,1,1);
      pad592[20] = new TPad ("pad20", "",0.73,0,1,1);
      pad592[21] = new TPad ("pad21", "",0.73,0,1,1);
      pad592[22] = new TPad ("pad22", "",0.73,0,1,1);
      pad592[23] = new TPad ("pad23", "",0.73,0,1,1);
      pad592[24] = new TPad ("pad24", "",0.73,0,1,1);
      pad592[25] = new TPad ("pad25", "",0.73,0,1,1);
      
      for (int k=0;k<n_cut59;k++) {
           canvas59[k]->cd();
           pad591[k]->Draw();
           pad592[k]->Draw();
           
           pad591[k]->cd();
           pad591[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
        }
        
        h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
        h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
        h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
        h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake
        h_hist[4]->SetLineColor(kMagenta); h_hist[4]->SetMarkerColor(kMagenta); h_hist[4]->SetFillColor(kMagenta); //Zll
        h_hist[5]->SetLineColor(kGreen-6); h_hist[5]->SetMarkerColor(kGreen-6); h_hist[5]->SetFillColor(kGreen-6); //Wlv
        h_hist[6]->SetLineColor(kAzure+3); h_hist[6]->SetMarkerColor(kAzure+3); h_hist[6]->SetFillColor(kAzure+3); //Ztautau
        h_hist[7]->SetLineColor(kOrange-1); h_hist[7]->SetMarkerColor(kOrange-1); h_hist[7]->SetFillColor(kOrange-1); //singletop
        h_hist[8]->SetLineColor(kOrange); h_hist[8]->SetMarkerColor(kOrange); h_hist[8]->SetFillColor(kOrange); //ttbar
        h_hist[9]->SetLineColor(kRed); h_hist[9]->SetMarkerColor(kRed); //VBF101

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mt*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if (i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && FakeTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut59_1[k]),  "SAMEHIST");} //Fake
          else if (i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut59_1[k]),  "SAMEHIST");} //Wlv
          else if(i == 8){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && TrueTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut59_1[k]), "SAMEHIST");} //ttbar
          else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut59_1[k]), "SAMEHIST");} //VBF101
          else chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut59_1[k]),  "SAMEHIST");
        }
        
        THStack *hs59 = new THStack("hs59", "");
        for(int i= 0; i<9 ; i++){ hs59->Add(h_hist[i], "hist1"); }
        hs59->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), factor*weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && dRLepTau && mBB && mVBFjj && dPhiLep0MET && Mvis && Mw && etaVBFj1 && cut59_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h591 = new TH1F("h591","Quadratic Sum from left",40,0,2000); //left
        
       float S_l_59 = 0;
       float B_l_59_0 = 0;
       float B_l_59_1 = 0;
       float B_l_59_2 = 0;
       float B_l_59_3 = 0;
       float B_l_59_4 = 0;
       float B_l_59_5 = 0;
       float B_l_59_6 = 0;
       float B_l_59_7 = 0;
       float B_l_59_8 = 0;
        
       float QuadraticSum_l_59 = 0;
       float Sum_l_59 = 0;
         
        for (int j=1; j<=40; j++) {
            
           S_l_59 = h_hist[9]->GetBinContent(j); //VBF101
           //cout << " S of each bin = " << S_l_59 << endl;
           B_l_59_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_l_59_8 << endl;
           B_l_59_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_l_59_7 << endl;
           B_l_59_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_l_59_6 << endl;
           B_l_59_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_l_59_5 << endl;
           B_l_59_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_l_59_4 << endl;
           B_l_59_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake of each bin = " << B_l_59_3 << endl;
           B_l_59_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_l_59_2 << endl;
           B_l_59_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_l_59_1 << endl;
           B_l_59_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_l_59_0 << endl;
           
           float B_l_59 = 0;
           for(int i = 0; i<9; i++) { B_l_59 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_l_59 << endl;
           
           float Bin_l_59 = 0;
           if (B_l_59 > 0){
               Bin_l_59 =  2* ( (S_l_59 + B_l_59) * log(1+S_l_59/B_l_59) - S_l_59 );
               //Bin_l_59 = (S_l_59/sqrt(B_l_59))*(S_l_59/sqrt(B_l_59));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_l_59) << endl; //
           

           Sum_l_59 += Bin_l_59 ;
           QuadraticSum_l_59 = sqrt(Sum_l_59);
           //cout << " Quadratic sum from left = " << QuadraticSum_l_59 << endl; //

           h591->SetBinContent(j,QuadraticSum_l_59);
           h591->SetLineColor(kBlue-9);
           h591->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
       }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
      TH1F *h592 = new TH1F("h592","Quadratic Sum from right",40,0,2000); //right
        
       float S_r_59 = 0;
       float B_r_59_0 = 0;
       float B_r_59_1 = 0;
       float B_r_59_2 = 0;
       float B_r_59_3 = 0;
       float B_r_59_4 = 0;
       float B_r_59_5 = 0;
       float B_r_59_6 = 0;
       float B_r_59_7 = 0;
       float B_r_59_8 = 0;
        
       float QuadraticSum_r_59 = 0;
       float Sum_r_59 = 0;
        
        for (int j=40; j>=1; j--) {
            
          S_r_59 = h_hist[9]->GetBinContent(j); //VBF101
          //cout << " S of each bin = " << S_r_59 << endl;
          B_r_59_8 = h_hist[8]->GetBinContent(j);
          //cout << " B of ttbar of each bin = " << B_r_59_8 << endl;
          B_r_59_7 = h_hist[7]->GetBinContent(j);
          //cout << " B of single top of each bin = " << B_r_59_7 << endl;
          B_r_59_6 = h_hist[6]->GetBinContent(j);
          //cout << " B of Ztt of each bin = " << B_r_59_6 << endl;
          B_r_59_5 = h_hist[5]->GetBinContent(j);
          //cout << " B of Wlv of each bin = " << B_r_59_5 << endl;
          B_r_59_4 = h_hist[4]->GetBinContent(j);
          //cout << " B of Z of each bin = " << B_r_59_4 << endl;
          B_r_59_3 = h_hist[3]->GetBinContent(j);
          //cout << " B of Fake of each bin = " << B_r_59_3 << endl;
          B_r_59_2 = h_hist[2]->GetBinContent(j);
          //cout << " B of DY of each bin = " << B_r_59_2 << endl;
          B_r_59_1 = h_hist[1]->GetBinContent(j);
          //cout << " B of diboson of each bin = " << B_r_59_1 << endl;
          B_r_59_0 = h_hist[0]->GetBinContent(j);
          //cout << " B of SM H of each bin = " << B_r_59_0 << endl;
          
          float B_r_59 = 0;
          for(int i = 0; i<9; i++) { B_r_59 += h_hist[i]->GetBinContent(j); }
          //cout << " B of each bin = " << B_r_59 << endl;
          
          float Bin_r_59 = 0;
          if (B_r_59 > 0){
              Bin_r_59 =  2* ( (S_r_59 + B_r_59) * log(1+S_r_59/B_r_59) - S_r_59 );
              //Bin_r_59 = (S_r_59/sqrt(B_r_59))*(S_r_59/sqrt(B_r_59));
              }
          //cout << " Bin = " << j << endl;
          //cout << " significance of each bin = " << sqrt(Bin_r_59) << endl;
          

          Sum_r_59 += Bin_r_59 ;
          QuadraticSum_r_59 = sqrt(Sum_r_59);
          //cout << " Quadratic sum from right = " << QuadraticSum_r_59 << endl;

          h592->SetBinContent(j,QuadraticSum_r_59);
          h592->SetLineColor(kGreen-9);
          h592->SetLineStyle(2);
          
          //cout << " ************************************ " << endl;
       }
       
    float rightmax59 = 1.1*h591->GetMaximum();
    float scale59 = 5000 / rightmax59;
    h591->Scale(scale59);
    h591->Draw("SAMEHIST");
    
    h592->Scale(scale59);
    h592->Draw("SAMEHIST");
    

    TGaxis*axis59 = new TGaxis(2000,0,2000,5000,0,rightmax59,510,"+L");
    axis59->SetTitle("Quadratic Sum of significance");
    axis59->SetTitleSize(0.03);
    axis59->SetLabelSize(0.025);
    axis59->Draw();
    
    pad592[k]->cd();
    TLegend *leg59 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg59->SetBorderSize(1);
    leg59->SetFillColor(0);
    leg59->SetTextFont(42);
    leg59->SetTextSize(0.053);
    
    for(int i= 9; i>=0 ; i--)
    {
        leg59->AddEntry(h_hist[i], h_titles[i].c_str());
    }
    leg59->AddEntry(h591, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg59->AddEntry(h592, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg59->Draw();
          
          
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut59_2[k] << endl;
        cout << "Mt =" << QuadraticSum_l_59 << endl;
        cout << "" << endl;
          
      }
    
  }

