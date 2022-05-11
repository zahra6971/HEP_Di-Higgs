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
#include <iostream>
using namespace std;
string itoa(int num);

void SLT_Mhh_plot_k_varied_ttbar(){

  const int n_smp = 4;
  //const int n_smp = 8;
  //const int n_smp = 5;
    
  string smp_tree[n_smp] = { "ttbar", "VBF111p5", "VBF110p5", "VBFSM" };
  //string smp_tree[n_smp] = { "ttbar", "VBF001", "VBF131", "VBF121", "VBF11p51", "VBF10p51", "VBF101", "VBFSM" };
  //string smp_tree[n_smp] = { "ttbar", "VBF1011", "VBF211", "VBF011", "VBFSM" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "FullRun2_SLT/"; // path to input files
  string ana_tag = "FinalNtuple.TauLH.";
  string smp_names[n_smp] = { "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1p5.", "VBF.hh_bbtt_vbf_lh_l1cvv1cv0p5.", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
  //string smp_names[n_smp] = { "ttbar", "VBF.hh_bbtt_vbf_lh_l0cvv0cv1.", "VBF.hh_bbtt_vbf_lh_l1cvv3cv1.", "VBF.hh_bbtt_vbf_lh_l1cvv2cv1.", "VBF.hh_bbtt_vbf_lh_l1cvv1p5cv1.", "VBF.hh_bbtt_vbf_lh_l1cvv0p5cv1.", "VBF.hh_bbtt_vbf_lh_l1cvv0cv1.", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
  //string smp_names[n_smp] = { "ttbar", "VBF.hh_bbtt_vbf_lh_l10cvv1cv1.", "VBF.hh_bbtt_vbf_lh_l2cvv1cv1.", "VBF.hh_bbtt_vbf_lh_l0cvv1cv1.", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
    
  for (int i=0; i<n_smp; i++)
    {
      smp = pwd + ana_tag + smp_names[i] +".0.root";
      cout<<smp<<endl;
      chain_smp[i] = new TChain(smp_tree[i].c_str());
      chain_smp[i]->Add(smp.c_str());
    }
  
  string h_titles[n_smp] = { "ttbar", "VBF111p5 x 2919.53", "VBF110p5 x 13577.81", "VBFSM x 233468.06" };  // only for legend
  string h_title[n_smp] = { "ttbar", "VBF111p5", "VBF110p5", "VBFSM" };
    
  //string h_titles[n_smp] = { "ttbar", "VBF001 x 4918.26", "VBF131 x 2147.21", "VBF121 x 9543.95", "VBF11p51 x 42439.38", "VBF10p51 x 19889.81", "VBF101 x 6230.85", "VBFSM x 233468.06" };  // only for legend
  //string h_title[n_smp] = { "ttbar", "VBF001", "VBF131", "VBF121", "VBF11p51", "VBF10p51", "VBF101", "VBFSM" };
    
  //string h_titles[n_smp] = { "ttbar", "VBF1011 x 2923.67", "VBF211 x 215040.95", "VBF011 x 67936.96", "VBFSM x 233468.06" };  // only for legend
  //string h_title[n_smp] = { "ttbar", "VBF1011", "VBF211", "VBF011", "VBFSM" };
    
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];
  

    //   ===========================================================   Mhh   ===========================================================
      
      TCanvas *c36 = new TCanvas ("c36", "Mhh",980,580);
        
      TPad *pad361 = new TPad("pad361","",0,0,0.85,1);
      TPad *pad362 = new TPad("pad362","",0.8,0,1,1);
      pad361->Draw();
      pad362->Draw();
        
      pad361->cd();
      pad361->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,800);
          h_hist[i]->GetXaxis()->SetTitle("m_{T}^{2} [GeV]");
          h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
          //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
      }
    
    h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
    
    h_hist[1]->SetLineColor(kMagenta+2); h_hist[1]->SetMarkerColor(kMagenta+2); //VBF_111p5
    h_hist[2]->SetLineColor(kMagenta); h_hist[2]->SetMarkerColor(kMagenta); //VBF_110p5
    h_hist[3]->SetLineColor(kRed); h_hist[3]->SetMarkerColor(kRed); //VBF_SM
    
    /*h_hist[1]->SetLineColor(kGreen); h_hist[1]->SetMarkerColor(kGreen); //VBF_001
    h_hist[2]->SetLineColor(kBlue-2); h_hist[2]->SetMarkerColor(kBlue-2); //VBF_131
    h_hist[3]->SetLineColor(kBlue-1); h_hist[3]->SetMarkerColor(kBlue-1); //VBF_121
    h_hist[4]->SetLineColor(kBlue+2); h_hist[4]->SetMarkerColor(kBlue+2); //VBF_11p51
    h_hist[5]->SetLineColor(kBlue+1); h_hist[5]->SetMarkerColor(kBlue+1); //VBF_10p51
    h_hist[6]->SetLineColor(kBlue); h_hist[6]->SetMarkerColor(kBlue); //VBF_101
    h_hist[7]->SetLineColor(kRed); h_hist[7]->SetMarkerColor(kRed); //VBF_SM*/
   
    /*h_hist[1]->SetLineColor(kGreen-1); h_hist[1]->SetMarkerColor(kGreen-1); //VBF_1011
    h_hist[2]->SetLineColor(kGreen+1); h_hist[2]->SetMarkerColor(kGreen+1); //VBF_211
    h_hist[3]->SetLineColor(kGreen); h_hist[3]->SetMarkerColor(kGreen); //VBF_011
    h_hist[4]->SetLineColor(kRed); h_hist[4]->SetMarkerColor(kRed); //VBF_SM*/
      
      for (int i=0; i<n_smp; i++){ hist_draw[i]="MT2*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "2919.53*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF111p5
        else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "13577.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF110p5
        else if(i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), "233468.06*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          
          /*else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "4918.26*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF001
        else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "2147.21*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF131
        else if(i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), "9543.95*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF121
        else if(i == 4){chain_smp[i]->Draw(hist_draw[i].c_str(), "42439.38*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF11p51
        else if(i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        else if(i == 6){chain_smp[i]->Draw(hist_draw[i].c_str(), "6230.85*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF101
        else if(i == 7){chain_smp[i]->Draw(hist_draw[i].c_str(), "233468.06*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM*/
          
        /*else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "2923.67*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF1011
        else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "215040.95*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF211
        else if(i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), "67936.96*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF011
        else if(i == 4){chain_smp[i]->Draw(hist_draw[i].c_str(), "233468.06*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM*/
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "2919.53*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF111p5
        else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "13577.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF110p5
        else if(i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), "233468.06*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          
        /*if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "4918.26*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF001
        else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "2147.21*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF131
        else if(i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), "9543.95*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF121
        else if(i == 4){chain_smp[i]->Draw(hist_draw[i].c_str(), "42439.38*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF11p51
        else if(i == 5){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        else if(i == 6){chain_smp[i]->Draw(hist_draw[i].c_str(), "6230.85*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF101
        else if(i == 7){chain_smp[i]->Draw(hist_draw[i].c_str(), "233468.06*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM*/
          
        /*if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "2923.67*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF1011
        else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "215040.95*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF211
        else if(i == 3){chain_smp[i]->Draw(hist_draw[i].c_str(), "67936.96*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF011
        else if(i == 4){chain_smp[i]->Draw(hist_draw[i].c_str(), "233468.06*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM*/
    }
    
    /*
     //cout << " ============== S/sqrt(B) From left ============== " << endl;
      
    TH1F *h36_1 = new TH1F("h36_1","Quadratic Sum from left",70,0,3500); //left

     double QuadraticSum_l_36 = 0;
     double R_l_36 = 0;
     double E_l_36 = 0;
     double EE_l_36 = 0;
       
      for (int j=1; j<=70; j++) {
        
         double S = h_hist[1]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double B = h_hist[0]->GetBinContent(j);
         double dB = h_hist[0]->GetBinError(j);
         
         if ( B>0 && S>0 ){
             double LSB = log(1 + S/B);
             R_l_36 +=  2* ( (S+B) * LSB - S );
             E_l_36 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
         }
          
         QuadraticSum_l_36 = sqrt(R_l_36);
         if(R_l_36 > 0) { EE_l_36 = sqrt(E_l_36) / QuadraticSum_l_36; }
          
         h36_1->SetBinContent(j,QuadraticSum_l_36);
         h36_1->SetLineColor(kBlue-9);
         h36_1->SetLineStyle(2);
         
      }

     //cout << " ============== S/sqrt(B) From right ============== " << endl;
      
    TH1F *h36_2 = new TH1F("h36_2","Quadratic Sum from right",70,0,3500); //right
      
    double QuadraticSum_r_36 = 0;
    double R_r_36 = 0;
    double E_r_36 = 0;
    double EE_r_36 = 0;
      
     for (int j=70; j>=1; j--) {
       
        double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);
        
        if ( B>0 && S>0 ){
            double LSB = log(1 + S/B);
            R_r_36 +=  2* ( (S+B) * LSB - S );
            E_r_36 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }
         
        QuadraticSum_r_36 = sqrt(R_r_36);
        if(R_r_36 > 0) { EE_r_36 = sqrt(E_r_36) / QuadraticSum_r_36; }
         
        h36_2->SetBinContent(j,QuadraticSum_r_36);
        h36_2->SetLineColor(kGreen-9);
        h36_2->SetLineStyle(2);
        
     }*/

      pad362->cd();
      TLegend *leg36 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg36->SetBorderSize(1);
      leg36->SetFillColor(0);
      leg36->SetTextFont(42);
      leg36->SetTextSize(0.055);
      
      for(int i= 3; i>=0 ; i--){ leg36->AddEntry(h_hist[i], h_titles[i].c_str()); }
      //for(int i= 7; i>=0 ; i--){ leg36->AddEntry(h_hist[i], h_titles[i].c_str()); }
      //for(int i= 4; i>=0 ; i--){ leg36->AddEntry(h_hist[i], h_titles[i].c_str()); }
      //leg36->AddEntry(h36_1, "Quadratic Sum of significance from left");
      //leg36->AddEntry(h36_2, "Quadratic Sum of significance from right");
      leg36->Draw();
    
      c36 -> SaveAs("MT2_kv.pdf");
      
      //cout << " Mhh 001 : " <<" S = " << QuadraticSum_r_36 << " E = " << EE_r_36 << endl;
    
  }

