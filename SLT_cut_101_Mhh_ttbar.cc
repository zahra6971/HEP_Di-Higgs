#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TTree.h"
#include "TLegend.h"
#include "TChain.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TPad.h"
#include "TMath.h"
#include <iostream>
using namespace std;
string itoa(int num);

void SLT_cut_101_Mhh_ttbar(){

  const int n_smp = 2;
  string smp_tree[n_smp] = { "ttbar", "VBF101" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "FullRun2_SLT/"; // path to input files
  string ana_tag = "FinalNtuple.TauLH.";
  string smp_names[n_smp] = { "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv0cv1." };
 
  for (int i=0; i<n_smp; i++)
    {
      smp = pwd + ana_tag + smp_names[i] +".0.root";
      cout<<smp<<endl;
      chain_smp[i] = new TChain(smp_tree[i].c_str());
      chain_smp[i]->Add(smp.c_str());
    }
  
  string h_titles[n_smp] = { "ttbar", "VBF101" };  // only for legend

  string h_title[n_smp] = { "ttbar", "VBF101" };
    
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];

    TCut weight = "weight";
    TCut TwoBTaggedJets = "BTag==2";
    TCut TwoOppositeSignTau = "LepQ*TauQ<0";
    
    // SM + X_HH
    TCut X_HH = "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.3";
    TCut MtW = "MtW<60000";
    TCut Xwt = "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.7";
    TCut dPhiHBB = "dPhiHBB>0.2";
    TCut Mw = "Mw>50000";
    TCut dPhiHttMET = "dPhiHttMET<1";
    TCut mVBFjj = "mVBFjj>50000";
    
    TCut MT2 = "MT2>260000";
     
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
    
    for (int k=0;k<n_cut1;k++) {
         canvas1[k]->cd();
         pad11[k]->Draw();
        
         pad11[k]->cd();
         pad11[k]->SetTickx();

         gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
          h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
      }
       
      for (int i=0; i<n_smp; i++){ hist_draw[i]=("Mhh*0.001>>"+h_title[i]); }
      
      for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut1_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut1_1[k]), "SAMEHIST");} //VBF101
        }
        
     // =================  Significance  =================
      
    TH1F *h11 = new TH1F("h11","Quadratic Sum from left",70,0,3500); //left
      
     double QuadraticSum_1 = 0;
     double R_1 = 0;
     double E_1 = 0;
     double EE_1 = 0;
       
      for (int j=1; j<=70; j++) {
        
          double S = h_hist[1]->GetBinContent(j);
          double dS = h_hist[1]->GetBinError(j);
          double B = h_hist[0]->GetBinContent(j);
          double dB = h_hist[0]->GetBinError(j);

         if ( B>0 && S>0 ){
             double LSB = log(1 + S/B);
             R_1 +=  2* ( (S+B) * LSB - S );
             E_1 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
         }
          
         QuadraticSum_1 = sqrt(R_1);
          if(R_1 > 0) { EE_1 = sqrt(E_1) / QuadraticSum_1; }
      }
         

      // =================  Significance  =================
        
      cout << "" << endl;
      cout << cut1_2[k] << endl;
      cout << " Mhh : " <<" S = " << QuadraticSum_1 << " E = " << EE_1 << endl;
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
      
      for (int k=0;k<n_cut2;k++) {
           canvas2[k]->cd();
           pad21[k]->Draw();
           
           pad21[k]->cd();
           pad21[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
         
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut2_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut2_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h21 = new TH1F("h21","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_2 = 0;
       double R_2 = 0;
       double E_2 = 0;
       double EE_2 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_2 +=  2* ( (S+B) * LSB - S );
               E_2 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_2 = sqrt(R_2);
            if(R_2 > 0) { EE_2 = sqrt(E_2) / QuadraticSum_2; }
        }
           
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut2_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_2 << " E = " << EE_2 << endl;
        cout << "" << endl;
          
      }
        
    
      
    cout << " " << endl;
    cout << "  ===========================================================   dEtaLepTau   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut3 = 24;
    TCut cut3_1[n_cut3] = { "dEtaLepTau<0.2", "dEtaLepTau<0.4", "dEtaLepTau<0.6", "dEtaLepTau<0.8", "dEtaLepTau<1 ", "dEtaLepTau<1.2", "dEtaLepTau<1.4", "dEtaLepTau<1.6", "dEtaLepTau<1.8", "dEtaLepTau<2", "dEtaLepTau<2.2", "dEtaLepTau<2.4", "dEtaLepTau<2.6", "dEtaLepTau<2.8", "dEtaLepTau<3", "dEtaLepTau<3.2", "dEtaLepTau<3.4", "dEtaLepTau<3.6", "dEtaLepTau<3.8", "dEtaLepTau<4", "dEtaLepTau<4.2", "dEtaLepTau<4.4", "dEtaLepTau<4.6","dEtaLepTau<4.8" };
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
    
      
      for (int k=0;k<n_cut3;k++) {
           canvas3[k]->cd();
           pad31[k]->Draw();
           
           pad31[k]->cd();
           pad31[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut3_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut3_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h31 = new TH1F("h31","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_3 = 0;
       double R_3 = 0;
       double E_3 = 0;
       double EE_3 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_3 +=  2* ( (S+B) * LSB - S );
               E_3 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_3 = sqrt(R_3);
            if(R_3 > 0) { EE_3 = sqrt(E_3) / QuadraticSum_3; }
        }
           
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut3_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_3 << " E = " << EE_3 << endl;
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
      
      for (int k=0;k<n_cut4;k++) {
           canvas4[k]->cd();
           pad41[k]->Draw();
           
           pad41[k]->cd();
           pad41[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut4_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut4_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h41 = new TH1F("h41","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_4 = 0;
       double R_4 = 0;
       double E_4 = 0;
       double EE_4 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_4 +=  2* ( (S+B) * LSB - S );
               E_4 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_4 = sqrt(R_4);
            if(R_4 > 0) { EE_4 = sqrt(E_4) / QuadraticSum_4; }
        }
           
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut4_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_4 << " E = " << EE_4 << endl;
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
    

      for (int k=0;k<n_cut5;k++) {
           canvas5[k]->cd();
           pad51[k]->Draw();
           
           pad51[k]->cd();
           pad51[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut5_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut5_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h51 = new TH1F("h51","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_5 = 0;
       double R_5 = 0;
       double E_5 = 0;
       double EE_5 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_5 +=  2* ( (S+B) * LSB - S );
               E_5 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_5 = sqrt(R_5);
            if(R_5 > 0) { EE_5 = sqrt(E_5) / QuadraticSum_5; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut5_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_5 << " E = " << EE_5 << endl;
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

      
      for (int k=0;k<n_cut6;k++) {
           canvas6[k]->cd();
           pad61[k]->Draw();
           
           pad61[k]->cd();
           pad61[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut6_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut6_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h61 = new TH1F("h61","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_6 = 0;
       double R_6 = 0;
       double E_6 = 0;
       double EE_6 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_6 +=  2* ( (S+B) * LSB - S );
               E_6 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_6 = sqrt(R_6);
            if(R_6 > 0) { EE_6 = sqrt(E_6) / QuadraticSum_6; }
        }
           
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut6_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_6 << " E = " << EE_6 << endl;
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
    
      for (int k=0;k<n_cut7;k++) {
           canvas7[k]->cd();
           pad71[k]->Draw();
           
           pad71[k]->cd();
           pad71[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut7_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut7_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h71 = new TH1F("h71","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_7 = 0;
       double R_7 = 0;
       double E_7 = 0;
       double EE_7 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_7 +=  2* ( (S+B) * LSB - S );
               E_7 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_7 = sqrt(R_7);
            if(R_7 > 0) { EE_7 = sqrt(E_7) / QuadraticSum_7; }
        }
           
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut7_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_7 << " E = " << EE_7 << endl;
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
    
      for (int k=0;k<n_cut8;k++) {
           canvas8[k]->cd();
           pad81[k]->Draw();
           
           pad81[k]->cd();
           pad81[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut8_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut8_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h81 = new TH1F("h81","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_8 = 0;
       double R_8 = 0;
       double E_8 = 0;
       double EE_8 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_8 +=  2* ( (S+B) * LSB - S );
               E_8 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_8 = sqrt(R_8);
            if(R_8 > 0) { EE_8 = sqrt(E_8) / QuadraticSum_8; }
        }
           
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut8_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_8 << " E = " << EE_8 << endl;
        cout << "" << endl;
          
      }
      
     
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
      
      for (int k=0;k<n_cut9;k++) {
           canvas9[k]->cd();
           pad91[k]->Draw();
           
           pad91[k]->cd();
           pad91[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut9_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut9_1[k]), "SAMEHIST");} //VBF101
        }
    

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h91 = new TH1F("h91","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_9 = 0;
       double R_9 = 0;
       double E_9 = 0;
       double EE_9 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_9 +=  2* ( (S+B) * LSB - S );
               E_9 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_9 = sqrt(R_9);
            if(R_9 > 0) { EE_9 = sqrt(E_9) / QuadraticSum_9; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut9_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_9 << " E = " << EE_9 << endl;
        cout << "" << endl;
          
      }
    
     
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
    
      
      for (int k=0;k<n_cut10;k++) {
           canvas10[k]->cd();
           pad101[k]->Draw();
           
           pad101[k]->cd();
           pad101[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut10_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut10_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h101 = new TH1F("h101","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_10 = 0;
       double R_10 = 0;
       double E_10 = 0;
       double EE_10 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_10 +=  2* ( (S+B) * LSB - S );
               E_10 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_10 = sqrt(R_10);
            if(R_10 > 0) { EE_10 = sqrt(E_10) / QuadraticSum_10; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut10_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_10 << " E = " << EE_10 << endl;
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
    
      
      for (int k=0;k<n_cut11;k++) {
           canvas11[k]->cd();
           pad111[k]->Draw();
           
           pad111[k]->cd();
           pad111[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut11_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut11_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h111 = new TH1F("h111","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_11 = 0;
       double R_11 = 0;
       double E_11 = 0;
       double EE_11 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_11 +=  2* ( (S+B) * LSB - S );
               E_11 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_11 = sqrt(R_11);
            if(R_11 > 0) { EE_11 = sqrt(E_11) / QuadraticSum_11; }
        }
           
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut11_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_11 << " E = " << EE_11 << endl;
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
    
      for (int k=0;k<n_cut13;k++) {
           canvas13[k]->cd();
           pad131[k]->Draw();
           
           pad131[k]->cd();
           pad131[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut13_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut13_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h131 = new TH1F("h131","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_13 = 0;
       double R_13 = 0;
       double E_13 = 0;
       double EE_13 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_13 +=  2* ( (S+B) * LSB - S );
               E_13 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_13 = sqrt(R_13);
            if(R_13 > 0) { EE_13 = sqrt(E_13) / QuadraticSum_13; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut13_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_13 << " E = " << EE_13 << endl;
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
      
      for (int k=0;k<n_cut16;k++) {
           canvas16[k]->cd();
           pad161[k]->Draw();
           
           pad161[k]->cd();
           pad161[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut16_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut16_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h161 = new TH1F("h161","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_16 = 0;
       double R_16 = 0;
       double E_16 = 0;
       double EE_16 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_16 +=  2* ( (S+B) * LSB - S );
               E_16 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_16 = sqrt(R_16);
            if(R_16 > 0) { EE_16 = sqrt(E_16) / QuadraticSum_16; }
        }
           

        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut16_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_16 << " E = " << EE_16 << endl;
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
      
      for (int k=0;k<n_cut17;k++) {
           canvas17[k]->cd();
           pad171[k]->Draw();
           
           pad171[k]->cd();
           pad171[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut17_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut17_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h171 = new TH1F("h171","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_17 = 0;
       double R_17 = 0;
       double E_17 = 0;
       double EE_17 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_17 +=  2* ( (S+B) * LSB - S );
               E_17 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_17 = sqrt(R_17);
            if(R_17 > 0) { EE_17 = sqrt(E_17) / QuadraticSum_17; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut17_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_17 << " E = " << EE_17 << endl;
        cout << "" << endl;
          
      }
        
     
    cout << " " << endl;
    cout << "  ===========================================================   dRLepTau   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut18 = 26;
    TCut cut18_1[n_cut18] = { "dRLepTau<1 ", "dRLepTau<1.2", "dRLepTau<1.4", "dRLepTau<1.6", "dRLepTau<1.8", "dRLepTau<2", "dRLepTau<2.2", "dRLepTau<2.4", "dRLepTau<2.6", "dRLepTau<2.8", "dRLepTau<3", "dRLepTau<3.2", "dRLepTau<3.4", "dRLepTau<3.6", "dRLepTau<3.8", "dRLepTau<4", "dRLepTau<4.2", "dRLepTau<4.4", "dRLepTau<4.6","dRLepTau<4.8", "dRLepTau<5", "dRLepTau<5.2", "dRLepTau<5.4", "dRLepTau<0.4", "dRLepTau<0.6", "dRLepTau<0.8" };
    string cut18_2[n_cut18] = { "dRLepTau<1 ", "dRLepTau<1.2", "dRLepTau<1.4", "dRLepTau<1.6", "dRLepTau<1.8", "dRLepTau<2", "dRLepTau<2.2", "dRLepTau<2.4", "dRLepTau<2.6", "dRLepTau<2.8", "dRLepTau<3", "dRLepTau<3.2", "dRLepTau<3.4", "dRLepTau<3.6", "dRLepTau<3.8", "dRLepTau<4", "dRLepTau<4.2", "dRLepTau<4.4", "dRLepTau<4.6","dRLepTau<4.8", "dRLepTau<5", "dRLepTau<5.2", "dRLepTau<5.4", "dRLepTau<0.4", "dRLepTau<0.6", "dRLepTau<0.8" };
    

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
      
      for (int k=0;k<n_cut18;k++) {
           canvas18[k]->cd();
           pad181[k]->Draw();
           
           pad181[k]->cd();
           pad181[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut18_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut18_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h181 = new TH1F("h181","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_18 = 0;
       double R_18 = 0;
       double E_18 = 0;
       double EE_18 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_18 +=  2* ( (S+B) * LSB - S );
               E_18 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_18 = sqrt(R_18);
            if(R_18 > 0) { EE_18 = sqrt(E_18) / QuadraticSum_18; }
        }
           

        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut18_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_18 << " E = " << EE_18 << endl;
        cout << "" << endl;
          
      }
     
       
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
    
      for (int k=0;k<n_cut19;k++) {
           canvas19[k]->cd();
           pad191[k]->Draw();
           
           pad191[k]->cd();
           pad191[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut19_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut19_1[k]), "SAMEHIST");} //VBF101
        }


       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h191 = new TH1F("h191","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_19 = 0;
       double R_19 = 0;
       double E_19 = 0;
       double EE_19 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_19 +=  2* ( (S+B) * LSB - S );
               E_19 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_19 = sqrt(R_19);
            if(R_19 > 0) { EE_19 = sqrt(E_19) / QuadraticSum_19; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut19_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_19 << " E = " << EE_19 << endl;
        cout << "" << endl;
          
      }
     
      
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
    
      for (int k=0;k<n_cut21;k++) {
           canvas21[k]->cd();
           pad211[k]->Draw();
           
           pad211[k]->cd();
           pad211[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut21_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut21_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h211 = new TH1F("h211","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_21 = 0;
       double R_21 = 0;
       double E_21 = 0;
       double EE_21 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_21 +=  2* ( (S+B) * LSB - S );
               E_21 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_21 = sqrt(R_21);
            if(R_21 > 0) { EE_21 = sqrt(E_21) / QuadraticSum_21; }
        }
           

        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut21_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_21 << " E = " << EE_21 << endl;
        cout << "" << endl;
          
      }
      
     
      
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
    
      for (int k=0;k<n_cut24;k++) {
           canvas24[k]->cd();
           pad241[k]->Draw();
           
           pad241[k]->cd();
           pad241[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut24_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut24_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h241 = new TH1F("h241","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_24 = 0;
       double R_24 = 0;
       double E_24 = 0;
       double EE_24 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_24 +=  2* ( (S+B) * LSB - S );
               E_24 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_24 = sqrt(R_24);
            if(R_24 > 0) { EE_24 = sqrt(E_24) / QuadraticSum_24; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut24_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_24 << " E = " << EE_24 << endl;
        cout << "" << endl;
          
      }
      
    
       
    cout << " " << endl;
    cout << "  ===========================================================   HT   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut27 = 26;
    TCut cut27_1[n_cut27] = { "HT>200000", "HT>220000", "HT>240000", "HT>260000", "HT>280000", "HT>300000", "HT>320000", "HT>340000", "HT>360000", "HT>380000", "HT>400000", "HT>420000", "HT>440000", "HT>460000", "HT>480000", "HT>500000", "HT>520000", "HT>540000", "HT>560000","HT>580000", "HT>600000", "HT>620000", "HT>640000", "HT>680000", "HT>700000", "HT>720000" };
    string cut27_2[n_cut27] = { "HT>200GeV", "HT>220GeV", "HT>240GeV", "HT>260GeV", "HT>280GeV", "HT>300GeV", "HT>320GeV", "HT>340GeV", "HT>360GeV", "HT>380GeV", "HT>400GeV", "HT>420GeV", "HT>440GeV", "HT>460GeV", "HT>480GeV", "HT>500GeV", "HT>520GeV", "HT>540GeV", "HT>560GeV","HT>580GeV", "HT>600GeV", "HT>620GeV", "HT>640GeV", "HT>680GeV", "HT>700GeV", "HT>720GeV" };
    

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
    
      for (int k=0;k<n_cut27;k++) {
           canvas27[k]->cd();
           pad271[k]->Draw();
           
           pad271[k]->cd();
           pad271[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut27_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut27_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h271 = new TH1F("h271","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_27 = 0;
       double R_27 = 0;
       double E_27 = 0;
       double EE_27 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_27 +=  2* ( (S+B) * LSB - S );
               E_27 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_27 = sqrt(R_27);
            if(R_27 > 0) { EE_27 = sqrt(E_27) / QuadraticSum_27; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut27_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_27 << " E = " << EE_27 << endl;
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
    
      for (int k=0;k<n_cut28;k++) {
           canvas28[k]->cd();
           pad281[k]->Draw();
           
           pad281[k]->cd();
           pad281[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut28_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut28_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h281 = new TH1F("h281","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_28 = 0;
       double R_28 = 0;
       double E_28 = 0;
       double EE_28 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_28 +=  2* ( (S+B) * LSB - S );
               E_28 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_28 = sqrt(R_28);
            if(R_28 > 0) { EE_28 = sqrt(E_28) / QuadraticSum_28; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut28_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_28 << " E = " << EE_28 << endl;
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
    
      for (int k=0;k<n_cut32;k++) {
           canvas32[k]->cd();
           pad321[k]->Draw();
           
           pad321[k]->cd();
           pad321[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut32_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut32_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h321 = new TH1F("h321","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_32 = 0;
       double R_32 = 0;
       double E_32 = 0;
       double EE_32 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_32 +=  2* ( (S+B) * LSB - S );
               E_32 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_32 = sqrt(R_32);
            if(R_32 > 0) { EE_32 = sqrt(E_32) / QuadraticSum_32; }
        }
           

        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut32_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_32 << " E = " << EE_32 << endl;
        cout << "" << endl;
          
      }
    
          
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
    
      for (int k=0;k<n_cut33;k++) {
           canvas33[k]->cd();
           pad331[k]->Draw();
           
           pad331[k]->cd();
           pad331[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if( i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut33_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut33_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h331 = new TH1F("h331","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_33 = 0;
       double R_33 = 0;
       double E_33 = 0;
       double EE_33 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_33 +=  2* ( (S+B) * LSB - S );
               E_33 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_33 = sqrt(R_33);
            if(R_33 > 0) { EE_33 = sqrt(E_33) / QuadraticSum_33; }
        }
           
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut33_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_33 << " E = " << EE_33 << endl;
        cout << "" << endl;
          
      }
          
     
     
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
     
      for (int k=0;k<n_cut35;k++) {
           canvas35[k]->cd();
           pad351[k]->Draw();
           
           pad351[k]->cd();
           pad351[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut35_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut35_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h351 = new TH1F("h351","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_35 = 0;
       double R_35 = 0;
       double E_35 = 0;
       double EE_35 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_35 +=  2* ( (S+B) * LSB - S );
               E_35 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_35 = sqrt(R_35);
            if(R_35 > 0) { EE_35 = sqrt(E_35) / QuadraticSum_35; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut35_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_35 << " E = " << EE_35 << endl;
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
    
      for (int k=0;k<n_cut36;k++) {
           canvas36[k]->cd();
           pad361[k]->Draw();
           
           pad361[k]->cd();
           pad361[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut36_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut36_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h361 = new TH1F("h361","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_36 = 0;
       double R_36 = 0;
       double E_36 = 0;
       double EE_36 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_36 +=  2* ( (S+B) * LSB - S );
               E_36 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_36 = sqrt(R_36);
            if(R_36 > 0) { EE_36 = sqrt(E_36) / QuadraticSum_36; }
        }
           

        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut36_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_36 << " E = " << EE_36 << endl;
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
    
      for (int k=0;k<n_cut37;k++) {
           canvas37[k]->cd();
           pad371[k]->Draw();
           
           pad371[k]->cd();
           pad371[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut37_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut37_1[k]), "SAMEHIST");} //VBF101
        }
    

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h371 = new TH1F("h371","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_37 = 0;
       double R_37 = 0;
       double E_37 = 0;
       double EE_37 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_37 +=  2* ( (S+B) * LSB - S );
               E_37 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_37 = sqrt(R_37);
            if(R_37 > 0) { EE_37 = sqrt(E_37) / QuadraticSum_37; }
        }
           

        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut37_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_37 << " E = " << EE_37 << endl;
        cout << "" << endl;
          
      }
       

       
    cout << " " << endl;
    cout << "  ===========================================================   Mt   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut38 = 26;
    TCut cut38_1[n_cut38] = { "Mt>50000", "Mt>100000", "Mt>150000", "Mt>200000", "Mt>250000", "Mt>300000", "Mt>350000", "Mt>400000", "Mt>450000", "Mt>500000", "Mt>550000", "Mt>600000", "Mt>650000", "Mt>700000", "Mt>750000", "Mt>800000", "Mt>850000", "Mt>900000", "Mt>950000","Mt>1000000", "Mt>1050000", "Mt>1100000", "Mt>1150000", "Mt>1200000", "Mt>1250000", "Mt>1300000" };
    string cut38_2[n_cut38] = { "Mt>50GeV", "Mt>100GeV", "Mt>150GeV", "Mt>200GeV", "Mt>250GeV", "Mt>300GeV", "Mt>350GeV", "Mt>400GeV", "Mt>450GeV", "Mt>500GeV", "Mt>550GeV", "Mt>600GeV", "Mt>650GeV", "Mt>700GeV", "Mt>750GeV", "Mt>800GeV", "Mt>850GeV", "Mt>900GeV", "Mt>950GeV","Mt>1000GeV", "Mt>1050GeV", "Mt>1100GeV", "Mt>1150GeV", "Mt>1200GeV", "Mt>1250GeV", "Mt>1300GeV" };
    

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
    
      for (int k=0;k<n_cut38;k++) {
           canvas38[k]->cd();
           pad381[k]->Draw();
           
           pad381[k]->cd();
           pad381[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut38_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut38_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h381 = new TH1F("h381","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_38 = 0;
       double R_38 = 0;
       double E_38 = 0;
       double EE_38 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_38 +=  2* ( (S+B) * LSB - S );
               E_38 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_38 = sqrt(R_38);
            if(R_38 > 0) { EE_38 = sqrt(E_38) / QuadraticSum_38; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut38_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_38 << " E = " << EE_38 << endl;
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
    
      for (int k=0;k<n_cut39;k++) {
           canvas39[k]->cd();
           pad391[k]->Draw();
           
           pad391[k]->cd();
           pad391[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut39_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut39_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h391 = new TH1F("h391","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_39 = 0;
       double R_39 = 0;
       double E_39 = 0;
       double EE_39 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_39 +=  2* ( (S+B) * LSB - S );
               E_39 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_39 = sqrt(R_39);
            if(R_39 > 0) { EE_39 = sqrt(E_39) / QuadraticSum_39; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut39_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_39 << " E = " << EE_39 << endl;
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
    
      for (int k=0;k<n_cut40;k++) {
           canvas40[k]->cd();
           pad401[k]->Draw();
           
           pad401[k]->cd();
           pad401[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut40_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut40_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h401 = new TH1F("h401","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_40 = 0;
       double R_40 = 0;
       double E_40 = 0;
       double EE_40 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_40 +=  2* ( (S+B) * LSB - S );
               E_40 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_40 = sqrt(R_40);
      if(R_40 > 0) { EE_40 = sqrt(E_40) / QuadraticSum_40; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut40_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_40 << " E = " << EE_40 << endl;
        cout << "" << endl;
          
      }
           
              
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
    
      for (int k=0;k<n_cut41;k++) {
           canvas41[k]->cd();
           pad411[k]->Draw();
           
           pad411[k]->cd();
           pad411[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
         

      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut41_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut41_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h411 = new TH1F("h411","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_41 = 0;
       double R_41 = 0;
       double E_41 = 0;
       double EE_41 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_41 +=  2* ( (S+B) * LSB - S );
               E_41 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_41 = sqrt(R_41);
            if(R_41 > 0) { EE_41 = sqrt(E_41) / QuadraticSum_41; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut41_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_41 << " E = " << EE_41 << endl;
        cout << "" << endl;
          
      }
          
           
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
    
      for (int k=0;k<n_cut42;k++) {
           canvas42[k]->cd();
           pad421[k]->Draw();
           
           pad421[k]->cd();
           pad421[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut42_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut42_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h421 = new TH1F("h421","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_42 = 0;
       double R_42 = 0;
       double E_42 = 0;
       double EE_42 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_42 +=  2* ( (S+B) * LSB - S );
               E_42 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_42 = sqrt(R_42);
            if(R_42 > 0) { EE_42 = sqrt(E_42) / QuadraticSum_42; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut42_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_42 << " E = " << EE_42 << endl;
        cout << "" << endl;
          
      }
        
         
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
      
      for (int k=0;k<n_cut43;k++) {
           canvas43[k]->cd();
           pad431[k]->Draw();
           
           pad431[k]->cd();
           pad431[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut43_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut43_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h431 = new TH1F("h431","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_43 = 0;
       double R_43 = 0;
       double E_43 = 0;
       double EE_43 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_43 +=  2* ( (S+B) * LSB - S );
               E_43 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_43 = sqrt(R_43);
            if(R_43 > 0) { EE_43 = sqrt(E_43) / QuadraticSum_43; }
        }
           
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut43_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_43 << " E = " << EE_43 << endl;
        cout << "" << endl;
          
      }
           
     
     
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
      
      for (int k=0;k<n_cut48;k++) {
           canvas48[k]->cd();
           pad481[k]->Draw();
           
           pad481[k]->cd();
           pad481[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut48_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut48_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h481 = new TH1F("h481","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_48 = 0;
       double R_48 = 0;
       double E_48 = 0;
       double EE_48 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_48 +=  2* ( (S+B) * LSB - S );
               E_48 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_48 = sqrt(R_48);
            if(R_48 > 0) { EE_48 = sqrt(E_48) / QuadraticSum_48; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut48_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_48 << " E = " << EE_48 << endl;
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
      
      for (int k=0;k<n_cut49;k++) {
           canvas49[k]->cd();
           pad491[k]->Draw();
           
           pad491[k]->cd();
           pad491[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut49_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut49_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h491 = new TH1F("h491","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_49 = 0;
       double R_49 = 0;
       double E_49 = 0;
       double EE_49 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_49 +=  2* ( (S+B) * LSB - S );
               E_49 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_49 = sqrt(R_49);
            if(R_49 > 0) { EE_49 = sqrt(E_49) / QuadraticSum_49; }
        }
           

        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut49_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_49 << " E = " << EE_49 << endl;
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
    
      for (int k=0;k<n_cut50;k++) {
           canvas50[k]->cd();
           pad501[k]->Draw();
           
           pad501[k]->cd();
           pad501[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut50_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut50_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h501 = new TH1F("h501","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_50 = 0;
       double R_50 = 0;
       double E_50 = 0;
       double EE_50 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_50 +=  2* ( (S+B) * LSB - S );
               E_50 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_50 = sqrt(R_50);
            if(R_50 > 0) { EE_50 = sqrt(E_50) / QuadraticSum_50; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut50_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_50 << " E = " << EE_50 << endl;
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
      
      for (int k=0;k<n_cut52;k++) {
           canvas52[k]->cd();
           pad521[k]->Draw();
           
           pad521[k]->cd();
           pad521[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut52_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut52_1[k]), "SAMEHIST");} //VBF101
        }
          
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h521 = new TH1F("h521","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_52 = 0;
       double R_52 = 0;
       double E_52 = 0;
       double EE_52 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_52 +=  2* ( (S+B) * LSB - S );
               E_52 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_52 = sqrt(R_52);
            if(R_52 > 0) { EE_52 = sqrt(E_52) / QuadraticSum_52; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut52_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_52 << " E = " << EE_52 << endl;
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
    
      for (int k=0;k<n_cut53;k++) {
           canvas53[k]->cd();
           pad531[k]->Draw();
           
           pad531[k]->cd();
           pad531[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut53_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut53_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h531 = new TH1F("h531","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_53 = 0;
       double R_53 = 0;
       double E_53 = 0;
       double EE_53 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_53 +=  2* ( (S+B) * LSB - S );
               E_53 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_53 = sqrt(R_53);
            if(R_53 > 0) { EE_53 = sqrt(E_53) / QuadraticSum_53; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut53_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_53 << " E = " << EE_53 << endl;
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
      
      for (int k=0;k<n_cut54;k++) {
           canvas54[k]->cd();
           pad541[k]->Draw();
           
           pad541[k]->cd();
           pad541[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut54_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut54_1[k]), "SAMEHIST");} //VBF101
        }
        
       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h541 = new TH1F("h541","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_54 = 0;
       double R_54 = 0;
       double E_54 = 0;
       double EE_54 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_54 +=  2* ( (S+B) * LSB - S );
               E_54 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_54 = sqrt(R_54);
            if(R_54 > 0) { EE_54 = sqrt(E_54) / QuadraticSum_54; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut54_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_54 << " E = " << EE_54 << endl;
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
    
      for (int k=0;k<n_cut55;k++) {
           canvas55[k]->cd();
           pad551[k]->Draw();
           
           pad551[k]->cd();
           pad551[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut55_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut55_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h551 = new TH1F("h551","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_55 = 0;
       double R_55 = 0;
       double E_55 = 0;
       double EE_55 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_55 +=  2* ( (S+B) * LSB - S );
               E_55 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_55 = sqrt(R_55);
            if(R_55 > 0) { EE_55 = sqrt(E_55) / QuadraticSum_55; }
        }
           

        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut55_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_55 << " E = " << EE_55 << endl;
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
      
      for (int k=0;k<n_cut59;k++) {
           canvas59[k]->cd();
           pad591[k]->Draw();
           
           pad591[k]->cd();
           pad591[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut59_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut59_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h591 = new TH1F("h591","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_59 = 0;
       double R_59 = 0;
       double E_59 = 0;
       double EE_59 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_59 +=  2* ( (S+B) * LSB - S );
               E_59 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_59 = sqrt(R_59);
            if(R_59 > 0) { EE_59 = sqrt(E_59) / QuadraticSum_59; }
        }
        
        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut59_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_59 << " E = " << EE_59 << endl;
        cout << "" << endl;
          
      }
    
    
    cout << " " << endl;
    cout << "  ===========================================================   dPhiVBFjj   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut60 = 16;
    TCut cut60_1[n_cut60] = { "dPhiVBFjj<0.2", "dPhiVBFjj<0.4", "dPhiVBFjj<0.6", "dPhiVBFjj<0.8", "dPhiVBFjj<1", "dPhiVBFjj<1.2", "dPhiVBFjj<1.4", "dPhiVBFjj<1.6", "dPhiVBFjj<1.8", "dPhiVBFjj<2", "dPhiVBFjj<2.2", "dPhiVBFjj<2.4", "dPhiVBFjj<2.6", "dPhiVBFjj<2.8", "dPhiVBFjj<3", "dPhiVBFjj<3.2" };
    string cut60_2[n_cut60] = { "dPhiVBFjj<0.2", "dPhiVBFjj<0.4", "dPhiVBFjj<0.6", "dPhiVBFjj<0.8", "dPhiVBFjj<1", "dPhiVBFjj<1.2", "dPhiVBFjj<1.4", "dPhiVBFjj<1.6", "dPhiVBFjj<1.8", "dPhiVBFjj<2", "dPhiVBFjj<2.2", "dPhiVBFjj<2.4", "dPhiVBFjj<2.6", "dPhiVBFjj<2.8", "dPhiVBFjj<3", "dPhiVBFjj<3.2" };
    

      TCanvas *canvas60[n_cut60] ;
      canvas60[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas60[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas60[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas60[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas60[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas60[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas60[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas60[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas60[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas60[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas60[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas60[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas60[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas60[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas60[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas60[15] = new TCanvas ("c15", "Mhh",980,580);
    
      TPad *pad601[n_cut5];
      pad601[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad601[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad601[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad601[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad601[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad601[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad601[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad601[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad601[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad601[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad601[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad601[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad601[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad601[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad601[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad601[15] = new TPad ("pad15", "", 0,0,0.75,1);
    

      for (int k=0;k<n_cut60;k++) {
           canvas60[k]->cd();
           pad601[k]->Draw();
           
           pad601[k]->cd();
           pad601[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut60_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut60_1[k]), "SAMEHIST");} //VBF101
        }

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h601 = new TH1F("h601","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_60 = 0;
       double R_60 = 0;
       double E_60 = 0;
       double EE_60 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_60 +=  2* ( (S+B) * LSB - S );
               E_60 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_60 = sqrt(R_60);
            if(R_60 > 0) { EE_60 = sqrt(E_60) / QuadraticSum_60; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut60_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_60 << " E = " << EE_60 << endl;
        cout << "" << endl;
          
      }
    
      
    cout << " " << endl;
    cout << "  ===========================================================   MtTotal   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut61 = 26;
    TCut cut61_1[n_cut61] = { "MtTotal<10000", "MtTotal<20000", "MtTotal<30000", "MtTotal<40000", "MtTotal<50000", "MtTotal<60000", "MtTotal<70000", "MtTotal<80000", "MtTotal<90000", "MtTotal<100000", "MtTotal<110000", "MtTotal<120000", "MtTotal<130000", "MtTotal<140000", "MtTotal<150000", "MtTotal<160000", "MtTotal<170000", "MtTotal<180000", "MtTotal<190000","MtTotal<200000", "MtTotal<210000", "MtTotal<220000", "MtTotal<230000", "MtTotal<240000", "MtTotal<250000", "MtTotal<260000" };
    string cut61_2[n_cut61] = { "MtTotal<10GeV", "MtTotal<20GeV", "MtTotal<30GeV", "MtTotal<40GeV", "MtTotal<50GeV", "MtTotal<60GeV", "MtTotal<70GeV", "MtTotal<80GeV", "MtTotal<90GeV", "MtTotal<100GeV", "MtTotal<110GeV", "MtTotal<120GeV", "MtTotal<130GeV", "MtTotal<140GeV", "MtTotal<150GeV", "MtTotal<160GeV", "MtTotal<170GeV", "MtTotal<180GeV", "MtTotal<190GeV","MtTotal<200GeV", "MtTotal<210GeV", "MtTotal<220GeV", "MtTotal<230GeV", "MtTotal<240GeV", "MtTotal<250GeV", "MtTotal<260GeV" };
    

      TCanvas *canvas61[n_cut61] ;
      canvas61[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas61[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas61[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas61[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas61[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas61[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas61[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas61[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas61[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas61[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas61[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas61[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas61[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas61[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas61[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas61[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas61[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas61[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas61[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas61[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas61[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas61[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas61[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas61[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas61[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas61[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad611[n_cut61];
      pad611[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad611[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad611[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad611[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad611[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad611[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad611[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad611[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad611[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad611[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad611[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad611[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad611[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad611[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad611[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad611[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad611[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad611[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad611[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad611[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad611[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad611[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad611[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad611[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad611[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad611[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      for (int k=0;k<n_cut61;k++) {
           canvas61[k]->cd();
           pad611[k]->Draw();
           
           pad611[k]->cd();
           pad611[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut61_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut61_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h611 = new TH1F("h611","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_61 = 0;
       double R_61 = 0;
       double E_61 = 0;
       double EE_61 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_61 +=  2* ( (S+B) * LSB - S );
               E_61 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_61 = sqrt(R_61);
            if(R_61 > 0) { EE_61 = sqrt(E_61) / QuadraticSum_61; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut61_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_61 << " E = " << EE_61 << endl;
        cout << "" << endl;
          
      }
        
    
    cout << " " << endl;
    cout << "  ===========================================================   MtWLep1   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut62 = 26;
    TCut cut62_1[n_cut62] = { "MtWLep1<10000", "MtWLep1<20000", "MtWLep1<30000", "MtWLep1<40000", "MtWLep1<50000", "MtWLep1<60000", "MtWLep1<70000", "MtWLep1<80000", "MtWLep1<90000", "MtWLep1<100000", "MtWLep1<110000", "MtWLep1<120000", "MtWLep1<130000", "MtWLep1<140000", "MtWLep1<150000", "MtWLep1<160000", "MtWLep1<170000", "MtWLep1<180000", "MtWLep1<190000","MtWLep1<200000", "MtWLep1<210000", "MtWLep1<220000", "MtWLep1<230000", "MtWLep1<240000", "MtWLep1<250000", "MtWLep1<260000" };
    string cut62_2[n_cut62] = { "MtWLep1<10GeV", "MtWLep1<20GeV", "MtWLep1<30GeV", "MtWLep1<40GeV", "MtWLep1<50GeV", "MtWLep1<60GeV", "MtWLep1<70GeV", "MtWLep1<80GeV", "MtWLep1<90GeV", "MtWLep1<100GeV", "MtWLep1<110GeV", "MtWLep1<120GeV", "MtWLep1<130GeV", "MtWLep1<140GeV", "MtWLep1<150GeV", "MtWLep1<160GeV", "MtWLep1<170GeV", "MtWLep1<180GeV", "MtWLep1<190GeV","MtWLep1<200GeV", "MtWLep1<210GeV", "MtWLep1<220GeV", "MtWLep1<230GeV", "MtWLep1<240GeV", "MtWLep1<250GeV", "MtWLep1<260GeV" };
    

      TCanvas *canvas62[n_cut62] ;
      canvas62[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas62[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas62[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas62[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas62[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas62[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas62[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas62[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas62[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas62[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas62[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas62[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas62[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas62[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas62[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas62[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas62[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas62[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas62[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas62[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas62[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas62[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas62[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas62[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas62[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas62[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad621[n_cut62];
      pad621[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad621[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad621[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad621[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad621[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad621[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad621[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad621[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad621[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad621[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad621[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad621[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad621[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad621[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad621[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad621[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad621[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad621[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad621[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad621[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad621[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad621[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad621[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad621[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad621[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad621[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      for (int k=0;k<n_cut62;k++) {
           canvas62[k]->cd();
           pad621[k]->Draw();
           
           pad621[k]->cd();
           pad621[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut62_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut62_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h621 = new TH1F("h621","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_62 = 0;
       double R_62 = 0;
       double E_62 = 0;
       double EE_62 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_62 +=  2* ( (S+B) * LSB - S );
               E_62 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_62 = sqrt(R_62);
            if(R_62 > 0) { EE_62 = sqrt(E_62) / QuadraticSum_62; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut62_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_62 << " E = " << EE_62 << endl;
        cout << "" << endl;
          
      }
      
         
    cout << " " << endl;
    cout << "  ===========================================================   Xwt   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut63 = 26;
    TCut cut63_1[n_cut63] = { "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>0.2", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>0.3", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>0.4", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>0.5", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>0.6", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>0.7", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>0.8", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>0.9", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>1", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.1", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.2", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.3", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.4", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.5", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.6", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.7", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.8", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<1.9","sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.1", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.2", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.3", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.4", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.5", "sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.6" };
    string cut63_2[n_cut63] = { "Xwt>0.2", "Xwt>0.3", "Xwt>0.4", "Xwt>0.5", "Xwt>0.6", "Xwt>0.7", "Xwt>0.8", "Xwt>0.9", "Xwt>1", "Xwt<1", "Xwt<1.1 ", "Xwt<1.2 ", "Xwt<1.3 ", "Xwt<1.4 ", "Xwt<1.5 ", "Xwt<1.6 ", "Xwt<1.7 ", "Xwt<1.8 ", "Xwt<1.9 ","Xwt<2.0 ", "Xwt<2.1 ", "Xwt<2.2 ", "Xwt<2.3 ", "Xwt<2.4 ", "Xwt<2.5 ", "Xwt<2.6 " };
    

      TCanvas *canvas63[n_cut63] ;
      canvas63[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas63[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas63[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas63[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas63[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas63[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas63[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas63[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas63[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas63[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas63[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas63[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas63[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas63[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas63[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas63[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas63[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas63[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas63[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas63[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas63[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas63[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas63[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas63[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas63[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas63[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad631[n_cut63];
      pad631[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad631[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad631[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad631[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad631[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad631[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad631[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad631[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad631[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad631[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad631[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad631[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad631[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad631[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad631[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad631[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad631[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad631[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad631[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad631[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad631[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad631[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad631[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad631[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad631[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad631[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      for (int k=0;k<n_cut63;k++) {
           canvas63[k]->cd();
           pad631[k]->Draw();
           
           pad631[k]->cd();
           pad631[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut63_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut63_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h631 = new TH1F("h631","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_63 = 0;
       double R_63 = 0;
       double E_63 = 0;
       double EE_63 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_63 +=  2* ( (S+B) * LSB - S );
               E_63 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_63 = sqrt(R_63);
           if(R_63 > 0) { EE_63 = sqrt(E_63) / QuadraticSum_63; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut63_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_63 << " E = " << EE_63 << endl;
        cout << "" << endl;
          
      }
          
           
    cout << " " << endl;
    cout << "  ===========================================================   X_HH   =========================================================== " << endl;
    cout << " " << endl;
    
    const int n_cut64 = 26;
    TCut cut64_1[n_cut64] = { "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.2", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.3", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.4", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.5", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.6", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.7", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.8", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.9", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.1", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.2", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.3", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.4", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.5", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.6", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.7", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.8", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<1.9","sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<2", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<2.1", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<2.2", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<2.3", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<2.4", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<2.5", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<2.6", "sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<2.7" };
    string cut64_2[n_cut64] = { "X_HH<0.2", "X_HH<0.3", "X_HH<0.4", "X_HH<0.5", "X_HH<0.6", "X_HH<0.7", "X_HH<0.8", "X_HH<0.9", "X_HH<1", "X_HH<1.1 ", "X_HH<1.2 ", "X_HH<1.3 ", "X_HH<1.4 ", "X_HH<1.5 ", "X_HH<1.6 ", "X_HH<1.7 ", "X_HH<1.8 ", "X_HH<1.9 ","X_HH<2.0 ", "X_HH<2.1 ", "X_HH<2.2 ", "X_HH<2.3 ", "X_HH<2.4 ", "X_HH<2.5 ", "X_HH<2.6 ", "X_HH<2.7 " };
    

      TCanvas *canvas64[n_cut64] ;
      canvas64[0] = new TCanvas ("c0", "Mhh",980,580);
      canvas64[1] = new TCanvas ("c1", "Mhh",980,580);
      canvas64[2] = new TCanvas ("c2", "Mhh",980,580);
      canvas64[3] = new TCanvas ("c3", "Mhh",980,580);
      canvas64[4] = new TCanvas ("c4", "Mhh",980,580);
      canvas64[5] = new TCanvas ("c5", "Mhh",980,580);
      canvas64[6] = new TCanvas ("c6", "Mhh",980,580);
      canvas64[7] = new TCanvas ("c7", "Mhh",980,580);
      canvas64[8] = new TCanvas ("c8", "Mhh",980,580);
      canvas64[9] = new TCanvas ("c9", "Mhh",980,580);
      canvas64[10] = new TCanvas ("c10", "Mhh",980,580);
      canvas64[11] = new TCanvas ("c11", "Mhh",980,580);
      canvas64[12] = new TCanvas ("c12", "Mhh",980,580);
      canvas64[13] = new TCanvas ("c13", "Mhh",980,580);
      canvas64[14] = new TCanvas ("c14", "Mhh",980,580);
      canvas64[15] = new TCanvas ("c15", "Mhh",980,580);
      canvas64[16] = new TCanvas ("c16", "Mhh",980,580);
      canvas64[17] = new TCanvas ("c17", "Mhh",980,580);
      canvas64[18] = new TCanvas ("c18", "Mhh",980,580);
      canvas64[19] = new TCanvas ("c19", "Mhh",980,580);
      canvas64[20] = new TCanvas ("c20", "Mhh",980,580);
      canvas64[21] = new TCanvas ("c21", "Mhh",980,580);
      canvas64[22] = new TCanvas ("c22", "Mhh",980,580);
      canvas64[23] = new TCanvas ("c23", "Mhh",980,580);
      canvas64[24] = new TCanvas ("c24", "Mhh",980,580);
      canvas64[25] = new TCanvas ("c25", "Mhh",980,580);
    
      TPad *pad641[n_cut64];
      pad641[0] = new TPad ("pad0", "", 0,0,0.75,1);
      pad641[1] = new TPad ("pad1", "", 0,0,0.75,1);
      pad641[2] = new TPad ("pad2", "", 0,0,0.75,1);
      pad641[3] = new TPad ("pad3", "", 0,0,0.75,1);
      pad641[4] = new TPad ("pad4", "", 0,0,0.75,1);
      pad641[5] = new TPad ("pad5", "", 0,0,0.75,1);
      pad641[6] = new TPad ("pad6", "", 0,0,0.75,1);
      pad641[7] = new TPad ("pad7", "", 0,0,0.75,1);
      pad641[8] = new TPad ("pad8", "", 0,0,0.75,1);
      pad641[9] = new TPad ("pad9", "", 0,0,0.75,1);
      pad641[10] = new TPad ("pad10", "", 0,0,0.75,1);
      pad641[11] = new TPad ("pad11", "", 0,0,0.75,1);
      pad641[12] = new TPad ("pad12", "", 0,0,0.75,1);
      pad641[13] = new TPad ("pad13", "", 0,0,0.75,1);
      pad641[14] = new TPad ("pad14", "", 0,0,0.75,1);
      pad641[15] = new TPad ("pad15", "", 0,0,0.75,1);
      pad641[16] = new TPad ("pad16", "", 0,0,0.75,1);
      pad641[17] = new TPad ("pad17", "", 0,0,0.75,1);
      pad641[18] = new TPad ("pad18", "", 0,0,0.75,1);
      pad641[19] = new TPad ("pad19", "", 0,0,0.75,1);
      pad641[20] = new TPad ("pad20", "", 0,0,0.75,1);
      pad641[21] = new TPad ("pad21", "", 0,0,0.75,1);
      pad641[22] = new TPad ("pad22", "", 0,0,0.75,1);
      pad641[23] = new TPad ("pad23", "", 0,0,0.75,1);
      pad641[24] = new TPad ("pad24", "", 0,0,0.75,1);
      pad641[25] = new TPad ("pad25", "", 0,0,0.75,1);
    
      for (int k=0;k<n_cut64;k++) {
           canvas64[k]->cd();
           pad641[k]->Draw();
           
           pad641[k]->cd();
           pad641[k]->SetTickx();

           gStyle->SetOptStat(kFALSE);
        
        for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",70,0,3500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
        }
        
        for (int i=0; i<n_smp; i++){
            hist_draw[i]=("Mhh*0.001>>"+h_title[i]);
        }
        
        for(int i = 0; i<n_smp; i++){
          if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut64_1[k]), "SAMEHIST");} //ttbar
          else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), weight*(TwoBTaggedJets && TwoOppositeSignTau && MT2 && cut64_1[k]), "SAMEHIST");} //VBF101
        }
        

       //cout << " ============== significance From left ============== " << endl;
        
      TH1F *h641 = new TH1F("h641","Quadratic Sum from left",70,0,3500); //left
        
       double QuadraticSum_64 = 0;
       double R_64 = 0;
       double E_64 = 0;
       double EE_64 = 0;
         
        for (int j=1; j<=70; j++) {
          
           double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

           if ( B>0 && S>0 ){
               double LSB = log(1 + S/B);
               R_64 +=  2* ( (S+B) * LSB - S );
               E_64 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }
            
           QuadraticSum_64 = sqrt(R_64);
           if(R_64 > 0) { EE_64 = sqrt(E_64) / QuadraticSum_64; }
        }
           

        // =================  Significance  =================
          
        cout << "" << endl;
        cout << cut64_2[k] << endl;
        cout << " Mhh : " <<" S = " << QuadraticSum_64 << " E = " << EE_64 << endl;
        cout << "" << endl;
          
      }
         
  }

