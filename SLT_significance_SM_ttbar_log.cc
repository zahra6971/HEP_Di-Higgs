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

void SLT_significance_SM_ttbar_log(){

  const int n_smp = 3;
  string smp_tree[n_smp] = { "ttbar","ttbar", "VBFSM" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "FullRun2_SLT/"; // path to input files
  string ana_tag = "FinalNtuple.TauLH.";
  string smp_names[n_smp] = { "ttbar","ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
    
  for (int i=0; i<n_smp; i++)
    {
      smp = pwd + ana_tag + smp_names[i] +".0.root";
      cout<<smp<<endl;
      chain_smp[i] = new TChain(smp_tree[i].c_str());
      chain_smp[i]->Add(smp.c_str());
    }
  
  string h_titles[n_smp] = { "ttbar_true","ttbar_fake", "VBFSM" };  // only for legend
    
  string h_title[n_smp] = { "ttbar_true","ttbar_fake", "VBFSM" };
    
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];
  
    
  //   ===========================================================   pTBB   ===========================================================
    
    TCanvas *c1 = new TCanvas ("c1", "pTBB",980,580);
      
    TPad *pad11 = new TPad("pad1","",0,0,0.75,1);
    TPad *pad12 = new TPad("pad2","",0.73,0,1,1);
    pad11->Draw();
    pad12->Draw();
      
    pad11->cd();
    pad11->SetTickx();
    //pad11->SetLogy();
    gStyle->SetOptStat(kFALSE);
    
    for (int i=0; i<n_smp; i++){
      h_nm = h_title[i].c_str();
      h_hist[i] = new TH1F(h_nm, "",60,0,1200);
      h_hist[i]->GetXaxis()->SetTitle("p_{T}^{BB} [GeV]");
      h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
      //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
      h_hist[i]->GetYaxis()->SetRangeUser(0, 7000);
        //h_hist[i]->SetMaximum(10000);
    }
    
    h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar_true
    h_hist[1]->SetLineColor(kPink+1); h_hist[1]->SetMarkerColor(kPink+1); h_hist[1]->SetFillColor(kPink+1); //ttbar_fake
    h_hist[2]->SetLineColor(kRed); h_hist[2]->SetMarkerColor(kRed); //VBF_SM
  
  
    for (int i=0; i<n_smp; i++){ hist_draw[i]="pTBB*0.001>>"+h_title[i]; }
    
    for(int i = 0; i<n_smp; i++){

      if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar_true
      else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))", "SAMEHIST");} //ttbar_fake
      else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM

    }

    THStack *hs1 = new THStack("hs1", "");
    for(int i= 2; i>=0 ; i--){ hs1->Add(h_hist[i], "hist1"); }
    hs1->Draw("SAMEHIST");
    
    for(int i = 0; i<n_smp; i++){
        if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
    }

   //cout << " ============== S/sqrt(B) From left ============== " << endl;
   //cout << " " << endl;
    
   TH1F *h1_1 = new TH1F("h1_1","Quadratic Sum from left",60,0,1200); //left
    
    double QuadraticSum_l_1 = 0;
    double R_l_1 = 0;
    double E_l_1 = 0;
    double EE_l_1 = 0;
      
     for (int j=1; j<=60; j++) {
       
        double S = h_hist[2]->GetBinContent(j);
        double dS = h_hist[2]->GetBinError(j);
        double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
            double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }
        
        if ( B>0 && S>0 ){
            double LSB = log(1 + S/B);
            R_l_1 +=  2* ( (S+B) * LSB - S );
            E_l_1 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }
         
        QuadraticSum_l_1 = sqrt(R_l_1);
        if(R_l_1 > 0) { EE_l_1 = sqrt(E_l_1) / QuadraticSum_l_1; }
         
        h1_1->SetBinContent(j,QuadraticSum_l_1);
        h1_1->SetLineColor(kBlue-9);
        h1_1->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
    
     }
       

   //cout << " ============== S/sqrt(B) From right ============== " << endl;
    
   TH1F *h1_2 = new TH1F("h1_2","Quadratic Sum from right",60,0,1200); //right
    
    double QuadraticSum_r_1 = 0;
    double R_r_1 = 0;
    double E_r_1 = 0;
    double EE_r_1 = 0;
      
     for (int j=60; j>=1; j--) {
       
         double S = h_hist[2]->GetBinContent(j);
         double dS = h_hist[2]->GetBinError(j);
         double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
             double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }
        
        if ( B>0 && S>0 ){
            double LSB = log(1 + S/B);
            R_r_1 +=  2* ( (S+B) * LSB - S );
            E_r_1 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }
         
        QuadraticSum_r_1 = sqrt(R_r_1);
        if(R_r_1 > 0) { EE_r_1 = sqrt(E_r_1) / QuadraticSum_r_1; }

      h1_2->SetBinContent(j,QuadraticSum_r_1);
      h1_2->SetLineColor(kGreen-9);
      h1_2->SetLineStyle(2);
      
      //cout << " ************************************ " << endl;
     }
   

    float rightmax1 = 1.1*h1_1->GetMaximum();
    float scale1 = 7000 / rightmax1;
    h1_1->Scale(scale1);
    h1_1->Draw("SAMEHIST");
    
    h1_2->Scale(scale1);
    h1_2->Draw("SAMEHIST");
    

    TGaxis*axis1 = new TGaxis(1200,0,1200,7000,0,rightmax1,510,"+L");
    axis1->SetTitle("Quadratic Sum of S/sqrt(B)");
    axis1->SetTitleSize(0.03);
    axis1->SetLabelSize(0.025);
    axis1->Draw();
    
    pad12->cd();
    TLegend *leg1 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg1->SetBorderSize(1);
    leg1->SetFillColor(0);
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.053);
    
    for(int i= 2; i>=0 ; i--){ leg1->AddEntry(h_hist[i], h_titles[i].c_str()); }
    leg1->AddEntry(h1_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
    leg1->AddEntry(h1_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
    leg1->Draw();
    
    c1 -> SaveAs("pTBB.pdf");

    
    //   ===========================================================   MT2   ===========================================================
      
      TCanvas *c20 = new TCanvas ("c20", "MT2",980,580);
        
      TPad *pad201 = new TPad("pad201","",0,0,0.75,1);
      TPad *pad202 = new TPad("pad202","",0.73,0,1,1);
      pad201->Draw();
      pad202->Draw();
        
      pad201->cd();
      pad201->SetTickx();
      //pad201->SetLogy();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",40,0,800);
        h_hist[i]->GetXaxis()->SetTitle("m_{T}^{2} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
          //h_hist[i]->SetMaximum(10000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar_true
    h_hist[1]->SetLineColor(kPink+1); h_hist[1]->SetMarkerColor(kPink+1); h_hist[1]->SetFillColor(kPink+1); //ttbar_fake
    h_hist[2]->SetLineColor(kRed); h_hist[2]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="MT2*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar_true
      else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))", "SAMEHIST");} //ttbar_fake
      else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
       
      }
    
    THStack *hs2 = new THStack("hs2", "");
    for(int i= 2; i>=0 ; i--){ hs2->Add(h_hist[i], "hist2"); }
    hs2->Draw("SAMEHIST");
    
    for(int i = 0; i<n_smp; i++){
        if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
    }
      

     //cout << " ============== S/sqrt(B) From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h20_1 = new TH1F("h20_1","Quadratic Sum from left",40,0,800); //left
      
          double QuadraticSum_l_20 = 0;
          double R_l_20 = 0;
          double E_l_20 = 0;
          double EE_l_20 = 0;

          for (int j=1; j<=40; j++) {

              double S = h_hist[2]->GetBinContent(j);
        double dS = h_hist[2]->GetBinError(j);
        double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
            double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_20 +=  2* ( (S + B) * LSB - S );
                  E_l_20 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_20 = sqrt(R_l_20);
              if(R_l_20 > 0) { EE_l_20 = sqrt(E_l_20) / QuadraticSum_l_20; }

              h20_1->SetBinContent(j,QuadraticSum_l_20);
              h20_1->SetLineColor(kBlue-9);
              h20_1->SetLineStyle(2);

          }
          
     //cout << " ============== S/sqrt(B) From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h20_2 = new TH1F("h20_2","Quadratic Sum from right",40,0,800); //right
      
          double QuadraticSum_r_20 = 0;
          double R_r_20 = 0;
          double E_r_20 = 0;
          double EE_r_20 = 0;

          for (int j=40; j>=1; j--) {

              double S = h_hist[2]->GetBinContent(j);
        double dS = h_hist[2]->GetBinError(j);
        double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
            double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_20 +=  2* ( (S + B) * LSB - S );
                  E_r_20 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_20 = sqrt(R_r_20);
              if(R_r_20 > 0) { EE_r_20 = sqrt(E_r_20) / QuadraticSum_r_20; }

              h20_2->SetBinContent(j,QuadraticSum_r_20);
              h20_2->SetLineColor(kGreen-9);
              h20_2->SetLineStyle(2);

          }
      
      
      float rightmax20 = 1.1*h20_1->GetMaximum();
      float scale20 = 10000 / rightmax20;
      h20_1->Scale(scale20);
      h20_1->Draw("SAMEHIST");
      
      h20_2->Scale(scale20);
      h20_2->Draw("SAMEHIST");
      
    
      TGaxis*axis20 = new TGaxis(800,0,800,10000,0,rightmax20,510,"+L");
      axis20->SetTitle("Quadratic Sum of S/sqrt(B)");
      axis20->SetTitleSize(0.03);
      axis20->SetLabelSize(0.025);
      axis20->Draw();
      
      pad202->cd();
      TLegend *leg20 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg20->SetBorderSize(1);
      leg20->SetFillColor(0);
      leg20->SetTextFont(42);
      leg20->SetTextSize(0.053);
      
      for(int i= 2; i>=0 ; i--){ leg20->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg20->AddEntry(h20_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg20->AddEntry(h20_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg20->Draw();
      
      c20 -> SaveAs("MT2.pdf");

    //   ===========================================================   Mhh   ===========================================================
      
      TCanvas *c36 = new TCanvas ("c36", "Mhh",980,580);
        
      TPad *pad361 = new TPad("pad361","",0,0,0.75,1);
      TPad *pad362 = new TPad("pad362","",0.73,0,1,1);
      pad361->Draw();
      pad362->Draw();
        
      pad361->cd();
      pad361->SetTickx();
      //pad361->SetLogy();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetXaxis()->SetTitle("m_{hh} [GeV]");
          h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
          //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
          //h_hist[i]->SetMaximum(11000);
      }
    
    h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar_true
        h_hist[1]->SetLineColor(kPink+1); h_hist[1]->SetMarkerColor(kPink+1); h_hist[1]->SetFillColor(kPink+1); //ttbar_fake
        h_hist[2]->SetLineColor(kRed); h_hist[2]->SetMarkerColor(kRed); //VBF_SM
      
      for (int i=0; i<n_smp; i++){ hist_draw[i]="Mhh*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar_true
      else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))", "SAMEHIST");} //ttbar_fake
      else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
       
      }
    
    THStack *hs3 = new THStack("hs3", "");
    for(int i= 2; i>=0 ; i--){ hs3->Add(h_hist[i], "hist3"); }
    hs3->Draw("SAMEHIST");
    
    for(int i = 0; i<n_smp; i++){
        if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
    }
    
     //cout << " ============== S/sqrt(B) From left ============== " << endl;
      
    TH1F *h36_1 = new TH1F("h36_1","Quadratic Sum from left",70,0,3500); //left

     double QuadraticSum_l_36 = 0;
     double R_l_36 = 0;
     double E_l_36 = 0;
     double EE_l_36 = 0;
       
      for (int j=1; j<=70; j++) {
        
         double S = h_hist[2]->GetBinContent(j);
         double dS = h_hist[2]->GetBinError(j);
          double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
          double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }
         
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
       
        double S = h_hist[2]->GetBinContent(j);
        double dS = h_hist[2]->GetBinError(j);
         double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
         double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }
        
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
        
     }
      
      float rightmax36 = 1.1*h36_1->GetMaximum();
      float scale36 = 11000 / rightmax36;
      h36_1->Scale(scale36);
      h36_1->Draw("SAMEHIST");
      
      h36_2->Scale(scale36);
      h36_2->Draw("SAMEHIST");
      
    
      TGaxis*axis36 = new TGaxis(3500,0,3500,11000,0,rightmax36,510,"+L");
      axis36->SetTitle("Quadratic Sum of S/sqrt(B)");
      axis36->SetTitleSize(0.03);
      axis36->SetLabelSize(0.025);
      axis36->Draw();
      
      pad362->cd();
      TLegend *leg36 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg36->SetBorderSize(1);
      leg36->SetFillColor(0);
      leg36->SetTextFont(42);
      leg36->SetTextSize(0.053);
      
      for(int i= 2; i>=0 ; i--){ leg36->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg36->AddEntry(h36_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg36->AddEntry(h36_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg36->Draw();
    
    c36 -> SaveAs("Mhh.pdf");
      
    
    //   ===========================================================   Mw   ===========================================================
      
      TCanvas *c43 = new TCanvas ("c43", "Mw",980,580);
        
      TPad *pad431 = new TPad("pad431","",0,0,0.75,1);
      TPad *pad432 = new TPad("pad432","",0.73,0,1,1);
      pad431->Draw();
      pad432->Draw();
        
      pad431->cd();
      pad431->SetTickx();
      //pad431->SetLogy();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",60,0,1200);
          h_hist[i]->GetXaxis()->SetTitle("m_{w} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 9000);
          //h_hist[i]->SetMaximum(9000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar_true
    h_hist[1]->SetLineColor(kPink+1); h_hist[1]->SetMarkerColor(kPink+1); h_hist[1]->SetFillColor(kPink+1); //ttbar_fake
    h_hist[2]->SetLineColor(kRed); h_hist[2]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="Mw*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar_true
      else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))", "SAMEHIST");} //ttbar_fake
      else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
       
      }
    
    THStack *hs4 = new THStack("hs4", "");
    for(int i= 2; i>=0 ; i--){ hs4->Add(h_hist[i], "hist4"); }
    hs4->Draw("SAMEHIST");
    
    for(int i = 0; i<n_smp; i++){
        if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
    }
      

     //cout << " ============== S/sqrt(B) From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h43_1 = new TH1F("h43_1","Quadratic Sum from left",60,0,1200); //left
      
          double QuadraticSum_l_43 = 0;
          double R_l_43 = 0;
          double E_l_43 = 0;
          double EE_l_43 = 0;

          for (int j=1; j<=60; j++) {

              double S = h_hist[2]->GetBinContent(j);
        double dS = h_hist[2]->GetBinError(j);
        double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
            double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_43 +=  2* ( (S + B) * LSB - S );
                  E_l_43 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_43 = sqrt(R_l_43);
              if(R_l_43 > 0) { EE_l_43 = sqrt(E_l_43) / QuadraticSum_l_43; }

              h43_1->SetBinContent(j,QuadraticSum_l_43);
              h43_1->SetLineColor(kBlue-9);
              h43_1->SetLineStyle(2);

          }
          
     //cout << " ============== S/sqrt(B) From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h43_2 = new TH1F("h43_2","Quadratic Sum from right",60,0,1200); //right

             double QuadraticSum_r_43 = 0;
             double R_r_43 = 0;
             double E_r_43 = 0;
             double EE_r_43 = 0;

             for (int j=60; j>=1; j--) {

                 double S = h_hist[2]->GetBinContent(j);
        double dS = h_hist[2]->GetBinError(j);
        double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
            double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_r_43 +=  2* ( (S + B) * LSB - S );
                     E_r_43 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_r_43 = sqrt(R_r_43);
                 if(R_r_43 > 0) { EE_r_43 = sqrt(E_r_43) / QuadraticSum_r_43; }

                 h43_2->SetBinContent(j,QuadraticSum_r_43);
                 h43_2->SetLineColor(kGreen-9);
                 h43_2->SetLineStyle(2);

             }
      
      float rightmax43 = 1.1*h43_1->GetMaximum();
      float scale43 = 9000 / rightmax43;
      h43_1->Scale(scale43);
      h43_1->Draw("SAMEHIST");
      
      h43_2->Scale(scale43);
      h43_2->Draw("SAMEHIST");
      
    
      TGaxis*axis43 = new TGaxis(1200,0,1200,9000,0,rightmax43,510,"+L");
      axis43->SetTitle("Quadratic Sum of S/sqrt(B)");
      axis43->SetTitleSize(0.03);
      axis43->SetLabelSize(0.025);
      axis43->Draw();
      
      pad432->cd();
      TLegend *leg43 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg43->SetBorderSize(1);
      leg43->SetFillColor(0);
      leg43->SetTextFont(42);
      leg43->SetTextSize(0.053);
      
      for(int i= 2; i>=0 ; i--){ leg43->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg43->AddEntry(h43_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg43->AddEntry(h43_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg43->Draw();
      
      c43 -> SaveAs("Mw.pdf");
    
    
    //   ===========================================================   Mt   ===========================================================
      
      TCanvas *c44 = new TCanvas ("c44", "Mt",980,580);
        
      TPad *pad441 = new TPad("pad441","",0,0,0.75,1);
      TPad *pad442 = new TPad("pad442","",0.73,0,1,1);
      pad441->Draw();
      pad442->Draw();
        
      pad441->cd();
      pad441->SetTickx();
      //pad441->SetLogy();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 12000);
          //h_hist[i]->SetMaximum(12000);
      }
    
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar_true
    h_hist[1]->SetLineColor(kPink+1); h_hist[1]->SetMarkerColor(kPink+1); h_hist[1]->SetFillColor(kPink+1); //ttbar_fake
    h_hist[2]->SetLineColor(kRed); h_hist[2]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="Mt*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar_true
      else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))", "SAMEHIST");} //ttbar_fake
      else if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
       
      }
    
    THStack *hs5 = new THStack("hs5", "");
    for(int i= 2; i>=0 ; i--){ hs5->Add(h_hist[i], "hist5"); }
    hs5->Draw("SAMEHIST");
    
    for(int i = 0; i<n_smp; i++){
        if(i == 2){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
    }
      

     //cout << " ============== S/sqrt(B) From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h44_1 = new TH1F("h44_1","Quadratic Sum from left",70,0,3500); //left
                
             double QuadraticSum_l_44 = 0;
             double R_l_44 = 0;
             double E_l_44 = 0;
             double EE_l_44 = 0;

             for (int j=1; j<=70; j++) {

                 double S = h_hist[2]->GetBinContent(j);
        double dS = h_hist[2]->GetBinError(j);
        double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
            double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_l_44 +=  2* ( (S + B) * LSB - S );
                     E_l_44 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_l_44 = sqrt(R_l_44);
                 if(R_l_44 > 0) { EE_l_44 = sqrt(E_l_44) / QuadraticSum_l_44; }

                 h44_1->SetBinContent(j,QuadraticSum_l_44);
                 h44_1->SetLineColor(kBlue-9);
                 h44_1->SetLineStyle(2);

             }
          
     //cout << " ============== S/sqrt(B) From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h44_2 = new TH1F("h44_2","Quadratic Sum from right",70,0,3500); //right

             double QuadraticSum_r_44 = 0;
             double R_r_44 = 0;
             double E_r_44 = 0;
             double EE_r_44 = 0;

             for (int j=70; j>=1; j--) {

                 double S = h_hist[2]->GetBinContent(j);
        double dS = h_hist[2]->GetBinError(j);
        double B = 0;   for(int i = 0; i<2; i++) { B += h_hist[i]->GetBinContent(j); }
            double dB = 0;   for(int i = 0; i<2; i++) { dB += h_hist[i]->GetBinError(j); }

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_r_44 +=  2* ( (S + B) * LSB - S );
                     E_r_44 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_r_44 = sqrt(R_r_44);
                 if(R_r_44 > 0) { EE_r_44 = sqrt(E_r_44) / QuadraticSum_r_44; }

                 h44_2->SetBinContent(j,QuadraticSum_r_44);
                 h44_2->SetLineColor(kGreen-9);
                 h44_2->SetLineStyle(2);

             }
      
      float rightmax44 = 1.1*h44_1->GetMaximum();
      float scale44 = 12000 / rightmax44;
      h44_1->Scale(scale44);
      h44_1->Draw("SAMEHIST");
      
      h44_2->Scale(scale44);
      h44_2->Draw("SAMEHIST");
      
    
      TGaxis*axis44 = new TGaxis(3500,0,3500,12000,0,rightmax44,510,"+L");
      axis44->SetTitle("Quadratic Sum of S/sqrt(B)");
      axis44->SetTitleSize(0.03);
      axis44->SetLabelSize(0.025);
      axis44->Draw();
      
      pad442->cd();
      TLegend *leg44 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg44->SetBorderSize(1);
      leg44->SetFillColor(0);
      leg44->SetTextFont(42);
      leg44->SetTextSize(0.053);
      
      for(int i= 2; i>=0 ; i--){ leg44->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg44->AddEntry(h44_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg44->AddEntry(h44_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg44->Draw();
      
      c44 -> SaveAs("Mt.pdf");
    
     
    // =================  Significance of each variable  =================
   
    cout << " pTBB : " <<" S = " << QuadraticSum_r_1 << " E = " << EE_r_1 << endl;
    cout << " MT2 : " <<" S = " << QuadraticSum_r_20 << " E = " << EE_r_20 << endl;
    cout << " Mhh : " <<" S = " << QuadraticSum_r_36 << " E = " << EE_r_36 << endl;
    cout << " Mw : " <<" S = " << QuadraticSum_r_43 << " E = " << EE_r_43 << endl;
    cout << " Mt : " <<" S = " << QuadraticSum_r_44 << " E = " << EE_r_44 << endl;

    
  }

