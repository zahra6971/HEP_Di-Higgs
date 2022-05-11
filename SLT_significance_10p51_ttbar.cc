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

void SLT_significance_10p51_ttbar(){

  const int n_smp = 2;
  string smp_tree[n_smp] = { "ttbar", "VBF10p51" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "FullRun2_SLT/"; // path to input files
  string ana_tag = "FinalNtuple.TauLH.";
  string smp_names[n_smp] = { "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv0p5cv1." };
    
  for (int i=0; i<n_smp; i++)
    {
      smp = pwd + ana_tag + smp_names[i] +".0.root";
      cout<<smp<<endl;
      chain_smp[i] = new TChain(smp_tree[i].c_str());
      chain_smp[i]->Add(smp.c_str());
    }
  
  string h_titles[n_smp] = { "ttbar", "VBF10p51 x 19889.81" };  // only for legend 19889.81
    
  string h_title[n_smp] = { "ttbar", "VBF10p51" };
    
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
    gStyle->SetOptStat(kFALSE);
    
    for (int i=0; i<n_smp; i++){
      h_nm = h_title[i].c_str();
      h_hist[i] = new TH1F(h_nm, "",60,0,1200);
      h_hist[i]->GetXaxis()->SetTitle("p_{T}^{BB} [GeV]");
      h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
      //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
      h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
    }
    
    h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
    h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM
  
  
    for (int i=0; i<n_smp; i++){ hist_draw[i]="pTBB*0.001>>"+h_title[i]; }
    
    for(int i = 0; i<n_smp; i++){

      if(i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
      else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51

    }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }

   //cout << " ============== significance From left ============== " << endl;
   //cout << " " << endl;
    
   TH1F *h1_1 = new TH1F("h1_1","Quadratic Sum from left",60,0,1200); //left
    
    double QuadraticSum_l_1 = 0;
    double R_l_1 = 0;
    double E_l_1 = 0;
    double EE_l_1 = 0;
      
     for (int j=1; j<=60; j++) {
       
        double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);
        
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
       

   //cout << " ============== significance From right ============== " << endl;
    
   TH1F *h1_2 = new TH1F("h1_2","Quadratic Sum from right",60,0,1200); //right
    
    double QuadraticSum_r_1 = 0;
    double R_r_1 = 0;
    double E_r_1 = 0;
    double EE_r_1 = 0;
      
     for (int j=60; j>=1; j--) {
       
        double S = h_hist[1]->GetBinContent(j);
        double B = h_hist[0]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double dB = h_hist[0]->GetBinError(j);
        
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
    float scale1 = 10000 / rightmax1;
    h1_1->Scale(scale1);
    h1_1->Draw("SAMEHIST");
    
    h1_2->Scale(scale1);
    h1_2->Draw("SAMEHIST");
    

    TGaxis*axis1 = new TGaxis(1200,0,1200,10000,0,rightmax1,510,"+L");
    axis1->SetTitle("Quadratic Sum of significance");
    axis1->SetTitleSize(0.03);
    axis1->SetLabelSize(0.025);
    axis1->Draw();
    
    pad12->cd();
    TLegend *leg1 = new TLegend(0.008, 0.1, 0.985,0.9);
    leg1->SetBorderSize(1);
    leg1->SetFillColor(0);
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.053);
    
    for(int i= 1; i>=0 ; i--){ leg1->AddEntry(h_hist[i], h_titles[i].c_str()); }
    leg1->AddEntry(h1_1, "Quadratic Sum of significance from left");
    leg1->AddEntry(h1_2, "Quadratic Sum of significance from right");
    leg1->Draw();
    
    c1 -> SaveAs("pTBB_10p51.pdf");
     
    //   ===========================================================   pTB1   ===========================================================
      
      TCanvas *c2 = new TCanvas ("c2", "pTB1",980,580);
        
      TPad *pad21 = new TPad("pad21","",0,0,0.75,1);
      TPad *pad22 = new TPad("pad22","",0.73,0,1,1);
      pad21->Draw();
      pad22->Draw();
        
      pad21->cd();
      pad21->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",55,0,1100);
        h_hist[i]->GetXaxis()->SetTitle("p_{T}^{B1} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 12000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM
    
    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="pTB1*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
      
    TH1F *h2_1 = new TH1F("h2_1","Quadratic Sum from left",55,0,1100); //left

     double QuadraticSum_l_2 = 0;
     double R_l_2 = 0;
     double E_l_2 = 0;
     double EE_l_2 = 0;
       
      for (int j=1; j<=55; j++) {
        
         double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);
         
         if ( B>0 && S>0 ){
             double LSB = log(1 + S/B);
             R_l_2 +=  2* ( (S+B) * LSB - S );
             E_l_2 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
         }
          
         QuadraticSum_l_2 = sqrt(R_l_2);
         if(R_l_2 > 0) { EE_l_2 = sqrt(E_l_2) / QuadraticSum_l_2; }
          
         h2_1->SetBinContent(j,QuadraticSum_l_2);
         h2_1->SetLineColor(kBlue-9);
         h2_1->SetLineStyle(2);
         
      }
        

    //cout << " ============== significance From right ============== " << endl;
     
    TH1F *h2_2 = new TH1F("h2_2","Quadratic Sum from right",55,0,1100); //right

     double QuadraticSum_r_2 = 0;
     double R_r_2 = 0;
     double E_r_2 = 0;
     double EE_r_2 = 0;
       
      for (int j=55; j>=1; j--) {
        
         double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);
         
         if ( B>0 && S>0 ){
             double LSB = log(1 + S/B);
             R_r_2 +=  2* ( (S+B) * LSB - S );
             E_r_2 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
         }
          
         QuadraticSum_r_2 = sqrt(R_r_2);
         if(R_r_2 > 0) { EE_r_2 = sqrt(E_r_2) / QuadraticSum_r_2; }

       h2_2->SetBinContent(j,QuadraticSum_r_2);
       h2_2->SetLineColor(kGreen-9);
       h2_2->SetLineStyle(2);
          
      }
       
      float rightmax2 = 1.1*h2_1->GetMaximum();
      float scale2 = 12000 / rightmax2;
      h2_1->Scale(scale2);
      h2_1->Draw("SAMEHIST");
      
      h2_2->Scale(scale2);
      h2_2->Draw("SAMEHIST");
      

      TGaxis*axis2 = new TGaxis(1100,0,1100,12000,0,rightmax2,510,"+L");
      axis2->SetTitle("Quadratic Sum of significance");
      axis2->SetTitleSize(0.03);
      axis2->SetLabelSize(0.025);
      axis2->Draw();
      
      pad22->cd();
      TLegend *leg2 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg2->SetBorderSize(1);
      leg2->SetFillColor(0);
      leg2->SetTextFont(42);
      leg2->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg2->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg2->AddEntry(h2_1, "Quadratic Sum of significance from left");
      leg2->AddEntry(h2_2, "Quadratic Sum of significance from right");
      leg2->Draw();
      
      c2 -> SaveAs("pTB1_10p51.pdf");
    
    
    //   ===========================================================   pTB2   ===========================================================
      
      TCanvas *c3 = new TCanvas ("c3", "pTB2",980,580);
        
      TPad *pad31 = new TPad("pad31","",0,0,0.75,1);
      TPad *pad32 = new TPad("pad32","",0.73,0,1,1);
      pad31->Draw();
      pad32->Draw();
        
      pad31->cd();
      pad31->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",34,0,340);
        h_hist[i]->GetXaxis()->SetTitle("p_{T}^{B2} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 10 GeV");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM
    
    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="pTB2*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h3_1 = new TH1F("h3_1","Quadratic Sum from left",34,0,340); //left
      
    double QuadraticSum_l_3 = 0;
    double R_l_3 = 0;
    double E_l_3 = 0;
    double EE_l_3 = 0;

    for (int j=1; j<=34; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

    if( B > 0 && S > 0) {
        double LSB = log(1+S/B);
        R_l_3 +=  2* ( (S + B) * LSB - S );
        E_l_3 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
    }

        QuadraticSum_l_3 = sqrt(R_l_3);
        if(R_l_3 > 0) { EE_l_3 = sqrt(E_l_3) / QuadraticSum_l_3; }

        h3_1->SetBinContent(j,QuadraticSum_l_3);
        h3_1->SetLineColor(kBlue-9);
        h3_1->SetLineStyle(2);

    }
         
     //cout << " ============== significance From right ============== " << endl;

     TH1F *h3_2 = new TH1F("h3_2","Quadratic Sum from right",34,0,340); //right
      
    double QuadraticSum_r_3 = 0;
    double R_r_3 = 0;
    double E_r_3 = 0;
    double EE_r_3 = 0;

    for (int j=34; j>=1; j--) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_r_3 +=  2* ( (S + B) * LSB - S );
            E_r_3 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_r_3 = sqrt(R_r_3);
        if(R_r_3 > 0) { EE_r_3 = sqrt(E_r_3) / QuadraticSum_r_3; }

        h3_2->SetBinContent(j,QuadraticSum_r_3);
        h3_2->SetLineColor(kGreen-9);
        h3_2->SetLineStyle(2);

    }
     
      
      float rightmax3 = 1.1*h3_1->GetMaximum();
      float scale3 = 10000 / rightmax3;
      h3_1->Scale(scale3);
      h3_1->Draw("SAMEHIST");
      
      h3_2->Scale(scale3);
      h3_2->Draw("SAMEHIST");
      

      TGaxis*axis3 = new TGaxis(340,0,340,10000,0,rightmax3,510,"+L");
      axis3->SetTitle("Quadratic Sum of significance");
      axis3->SetTitleSize(0.03);
      axis3->SetLabelSize(0.025);
      axis3->Draw();
      
      pad32->cd();
      TLegend *leg3 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg3->SetBorderSize(1);
      leg3->SetFillColor(0);
      leg3->SetTextFont(42);
      leg3->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg3->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg3->AddEntry(h3_1, "Quadratic Sum of significance from left");
      leg3->AddEntry(h3_2, "Quadratic Sum of significance from right");
      leg3->Draw();
      
      c3 -> SaveAs("pTB2_10p51.pdf");
    
    
    //   ===========================================================   mBB   ===========================================================
      
      TCanvas *c4 = new TCanvas ("c4", "mBB",980,580);
        
      TPad *pad41 = new TPad("pad41","",0,0,0.75,1);
      TPad *pad42 = new TPad("pad42","",0.73,0,1,1);
      pad41->Draw();
      pad42->Draw();
        
      pad41->cd();
      pad41->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",25,0,500);
        h_hist[i]->GetXaxis()->SetTitle("m_{BB} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
      }
      
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM
    

      for (int i=0; i<n_smp; i++){ hist_draw[i]="mBB*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
  
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h4_1 = new TH1F("h4_1","Quadratic Sum from left",25,0,500); //left
      
    double QuadraticSum_l_4 = 0;
    double R_l_4 = 0;
    double E_l_4 = 0;
    double EE_l_4 = 0;

    for (int j=1; j<=25; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_l_4 +=  2* ( (S + B) * LSB - S );
            E_l_4 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_l_4 = sqrt(R_l_4);
        if(R_l_4 > 0) { EE_l_4 = sqrt(E_l_4) / QuadraticSum_l_4; }

        h4_1->SetBinContent(j,QuadraticSum_l_4);
        h4_1->SetLineColor(kBlue-9);
        h4_1->SetLineStyle(2);

    }
         
     //cout << " ============== significance From right ============== " << endl;

     TH1F *h4_2 = new TH1F("h4_2","Quadratic Sum from right",25,0,500); //right
      
    double QuadraticSum_r_4 = 0;
    double R_r_4 = 0;
    double E_r_4 = 0;
    double EE_r_4 = 0;

    for (int j=25; j>=1; j--) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_r_4 +=  2* ( (S + B) * LSB - S );
            E_r_4 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_r_4 = sqrt(R_r_4);
        if(R_r_4 > 0) { EE_r_4 = sqrt(E_r_4) / QuadraticSum_r_4; }

        h4_2->SetBinContent(j,QuadraticSum_r_4);
        h4_2->SetLineColor(kGreen-9);
        h4_2->SetLineStyle(2);

    }
     
      float rightmax4 = 1.1*h4_1->GetMaximum();
      float scale4 = 10000 / rightmax4;
      h4_1->Scale(scale4);
      h4_1->Draw("SAMEHIST");
      
      h4_2->Scale(scale4);
      h4_2->Draw("SAMEHIST");
      

      TGaxis*axis4 = new TGaxis(500,0,500,10000,0,rightmax4,510,"+L");
      axis4->SetTitle("Quadratic Sum of significance");
      axis4->SetTitleSize(0.03);
      axis4->SetLabelSize(0.025);
      axis4->Draw();
      
      pad42->cd();
      TLegend *leg4 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg4->SetBorderSize(1);
      leg4->SetFillColor(0);
      leg4->SetTextFont(42);
      leg4->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg4->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg4->AddEntry(h4_1, "Quadratic Sum of significance from left");
      leg4->AddEntry(h4_2, "Quadratic Sum of significance from right");
      leg4->Draw();
      
      c4 -> SaveAs("mBB_10p51.pdf");
    
      
    //   ===========================================================   dPhiBB   ===========================================================
      
      TCanvas *c5 = new TCanvas ("c5", "dPhiBB",980,580);
        
      TPad *pad51 = new TPad("pad51","",0,0,0.75,1);
      TPad *pad52 = new TPad("pad52","",0.73,0,1,1);
      pad51->Draw();
      pad52->Draw();
        
      pad51->cd();
      pad51->SetTickx();
      gStyle->SetOptStat(kFALSE);

      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
        h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (B,B)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2500);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM
 
    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPhiBB>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51

      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
  
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h5_1 = new TH1F("h5_1","Quadratic Sum from left",20,0,3.5); //left
      
    double QuadraticSum_l_5 = 0;
    double R_l_5 = 0;
    double E_l_5 = 0;
    double EE_l_5 = 0;

    for (int j=1; j<=20; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_l_5 +=  2* ( (S + B) * LSB - S );
            E_l_5 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_l_5 = sqrt(R_l_5);
        if(R_l_5 > 0) { EE_l_5 = sqrt(E_l_5) / QuadraticSum_l_5; }

        h5_1->SetBinContent(j,QuadraticSum_l_5);
        h5_1->SetLineColor(kBlue-9);
        h5_1->SetLineStyle(2);

    }

     //cout << " ============== significance From right ============== " << endl;
      
     TH1F *h5_2 = new TH1F("h5_2","Quadratic Sum from right",20,0,3.5); //right
      
    double QuadraticSum_r_5 = 0;
    double R_r_5 = 0;
    double E_r_5 = 0;
    double EE_r_5 = 0;

    for (int j=20; j>=1; j--) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_r_5 +=  2* ( (S + B) * LSB - S );
            E_r_5 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_r_5 = sqrt(R_r_5);
        if(R_r_5 > 0) { EE_r_5 = sqrt(E_r_5) / QuadraticSum_r_5; }

        h5_2->SetBinContent(j,QuadraticSum_r_5);
        h5_2->SetLineColor(kGreen-9);
        h5_2->SetLineStyle(2);

    }
      
      float rightmax5 = 1.1*h5_1->GetMaximum();
      float scale5 = 2500 / rightmax5;
      h5_1->Scale(scale5);
      h5_1->Draw("SAMEHIST");
      
      h5_2->Scale(scale5);
      h5_2->Draw("SAMEHIST");
      

      TGaxis*axis5 = new TGaxis(3.5,0,3.5,2500,0,rightmax5,510,"+L");
      axis5->SetTitle("Quadratic Sum of significance");
      axis5->SetTitleSize(0.03);
      axis5->SetLabelSize(0.025);
      axis5->Draw();
      
      pad52->cd();
      TLegend *leg5 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg5->SetBorderSize(1);
      leg5->SetFillColor(0);
      leg5->SetTextFont(42);
      leg5->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg5->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg5->AddEntry(h5_1, "Quadratic Sum of significance from left");
      leg5->AddEntry(h5_2, "Quadratic Sum of significance from right");
      leg5->Draw();
      
      c5 -> SaveAs("dPhiBB_10p51.pdf");
      
    
    //   ===========================================================   dEtaBB   ===========================================================
      
      TCanvas *c6 = new TCanvas ("c6", "dEtaBB",980,580);
        
      TPad *pad61 = new TPad("pad61","",0,0,0.75,1);
      TPad *pad62 = new TPad("pad62","",0.73,0,1,1);
      pad61->Draw();
      pad62->Draw();
        
      pad61->cd();
      pad61->SetTickx();
      gStyle->SetOptStat(kFALSE);

      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",45,0,9);
        h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (B,B)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 6000);
      }

      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM
    

      for (int i=0; i<n_smp; i++){ hist_draw[i]="dEtaBB>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51

      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h6_1 = new TH1F("h6_1","Quadratic Sum from left",45,0,9); //left
      
    double QuadraticSum_l_6 = 0;
    double R_l_6 = 0;
    double E_l_6 = 0;
    double EE_l_6 = 0;

    for (int j=1; j<=45; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_l_6 +=  2* ( (S + B) * LSB - S );
            E_l_6 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_l_6 = sqrt(R_l_6);
        if(R_l_6 > 0) { EE_l_6 = sqrt(E_l_6) / QuadraticSum_l_6; }

        h6_1->SetBinContent(j,QuadraticSum_l_6);
        h6_1->SetLineColor(kBlue-9);
        h6_1->SetLineStyle(2);

    }
     
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h6_2 = new TH1F("h6_2","Quadratic Sum from right",45,0,9); //right
      
    double QuadraticSum_r_6 = 0;
    double R_r_6 = 0;
    double E_r_6 = 0;
    double EE_r_6 = 0;

    for (int j=45; j>=1; j--) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_r_6 +=  2* ( (S + B) * LSB - S );
            E_r_6 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_r_6 = sqrt(R_r_6);
        if(R_r_6 > 0) { EE_r_6 = sqrt(E_r_6) / QuadraticSum_r_6; }

        h6_2->SetBinContent(j,QuadraticSum_r_6);
        h6_2->SetLineColor(kGreen-9);
        h6_2->SetLineStyle(2);

    }
      
      float rightmax6 = 1.1*h6_1->GetMaximum();
      float scale6 = 6000 / rightmax6;
      h6_1->Scale(scale6);
      h6_1->Draw("SAMEHIST");
      
      h6_2->Scale(scale6);
      h6_2->Draw("SAMEHIST");
      

      TGaxis*axis6 = new TGaxis(9,0,9,6000,0,rightmax6,510,"+L");
      axis6->SetTitle("Quadratic Sum of significance");
      axis6->SetTitleSize(0.03);
      axis6->SetLabelSize(0.025);
      axis6->Draw();
      
      pad62->cd();
      TLegend *leg6 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg6->SetBorderSize(1);
      leg6->SetFillColor(0);
      leg6->SetTextFont(42);
      leg6->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg6->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg6->AddEntry(h6_1, "Quadratic Sum of significance from left");
      leg6->AddEntry(h6_2, "Quadratic Sum of significance from right");
      leg6->Draw();
      
      c6 -> SaveAs("dEtaBB_10p51.pdf");

    
    //   ===========================================================   dRBB   ===========================================================
      
      TCanvas *c7 = new TCanvas ("c7", "dRBB",980,580);
        
      TPad *pad71 = new TPad("pad71","",0,0,0.75,1);
      TPad *pad72 = new TPad("pad72","",0.73,0,1,1);
      pad71->Draw();
      pad72->Draw();
        
      pad71->cd();
      pad71->SetTickx();
      gStyle->SetOptStat(kFALSE);

      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",22,0,4.4);
        h_hist[i]->GetXaxis()->SetTitle("#DeltaR (B,B)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4000);
      }
     
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM
    
    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dRBB>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h7_1 = new TH1F("h7_1","Quadratic Sum from left",22,0,4.4); //left
      
    double QuadraticSum_l_7 = 0;
    double R_l_7 = 0;
    double E_l_7 = 0;
    double EE_l_7 = 0;

    for (int j=1; j<=22; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_l_7 +=  2* ( (S + B) * LSB - S );
            E_l_7 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_l_7 = sqrt(R_l_7);
        if(R_l_7 > 0) { EE_l_7 = sqrt(E_l_7) / QuadraticSum_l_7; }

        h7_1->SetBinContent(j,QuadraticSum_l_7);
        h7_1->SetLineColor(kBlue-9);
        h7_1->SetLineStyle(2);

    }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h7_2 = new TH1F("h7_2","Quadratic Sum from right",22,0,4.4); //right
      
    double QuadraticSum_r_7 = 0;
    double R_r_7 = 0;
    double E_r_7 = 0;
    double EE_r_7 = 0;

    for (int j=22; j>=1; j--) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_r_7 +=  2* ( (S + B) * LSB - S );
            E_r_7 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_r_7 = sqrt(R_r_7);
        if(R_r_7 > 0) { EE_r_7 = sqrt(E_r_7) / QuadraticSum_r_7; }

        h7_2->SetBinContent(j,QuadraticSum_r_7);
        h7_2->SetLineColor(kGreen-9);
        h7_2->SetLineStyle(2);

    }
      
      float rightmax7 = 1.1*h7_1->GetMaximum();
      float scale7 = 4000 / rightmax7;
      h7_1->Scale(scale7);
      h7_1->Draw("SAMEHIST");
      
      h7_2->Scale(scale7);
      h7_2->Draw("SAMEHIST");
      

      TGaxis*axis7 = new TGaxis(4.4,0,4.4,4000,0,rightmax7,510,"+L");
      axis7->SetTitle("Quadratic Sum of significance");
      axis7->SetTitleSize(0.03);
      axis7->SetLabelSize(0.025);
      axis7->Draw();
      
      pad72->cd();
      TLegend *leg7 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg7->SetBorderSize(1);
      leg7->SetFillColor(0);
      leg7->SetTextFont(42);
      leg7->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg7->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg7->AddEntry(h7_1, "Quadratic Sum of significance from left");
      leg7->AddEntry(h7_2, "Quadratic Sum of significance from right");
      leg7->Draw();
      
      c7 -> SaveAs("dRBB_10p51.pdf");
    
    
    //   ===========================================================   pTtautau   ===========================================================
      
      TCanvas *c8 = new TCanvas ("c8", "pTtautau",980,580);
        
      TPad *pad81 = new TPad("pad81","",0,0,0.75,1);
      TPad *pad82 = new TPad("pad82","",0.73,0,1,1);
      pad81->Draw();
      pad82->Draw();
        
      pad81->cd();
      pad81->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",75,0,1500);
        h_hist[i]->GetXaxis()->SetTitle("p_{T}^{#tau#tau} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5500);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="pTtautau*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h8_1 = new TH1F("h8_1","Quadratic Sum from left",75,0,1500); //left
      
    double QuadraticSum_l_8 = 0;
    double R_l_8 = 0;
    double E_l_8 = 0;
    double EE_l_8 = 0;

    for (int j=1; j<=75; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_l_8 +=  2* ( (S + B) * LSB - S );
            E_l_8 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_l_8 = sqrt(R_l_8);
        if(R_l_8 > 0) { EE_l_8 = sqrt(E_l_8) / QuadraticSum_l_8; }

        h8_1->SetBinContent(j,QuadraticSum_l_8);
        h8_1->SetLineColor(kBlue-9);
        h8_1->SetLineStyle(2);

    }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h8_2 = new TH1F("h8_2","Quadratic Sum from right",75,0,1500); //right
      
    double QuadraticSum_r_8 = 0;
    double R_r_8 = 0;
    double E_r_8 = 0;
    double EE_r_8 = 0;

    for (int j=75; j>=1; j--) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_r_8 +=  2* ( (S + B) * LSB - S );
            E_r_8 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_r_8 = sqrt(R_r_8);
        if(R_r_8 > 0) { EE_r_8 = sqrt(E_r_8) / QuadraticSum_r_8; }

        h8_2->SetBinContent(j,QuadraticSum_r_8);
        h8_2->SetLineColor(kGreen-9);
        h8_2->SetLineStyle(2);

    }
      
      float rightmax8 = 1.1*h8_1->GetMaximum();
      float scale8 = 5500 / rightmax8;
      h8_1->Scale(scale8);
      h8_1->Draw("SAMEHIST");
      
      h8_2->Scale(scale8);
      h8_2->Draw("SAMEHIST");
      

    
      TGaxis*axis8 = new TGaxis(1500,0,1500,5500,0,rightmax8,510,"+L");
      axis8->SetTitle("Quadratic Sum of significance");
      axis8->SetTitleSize(0.03);
      axis8->SetLabelSize(0.025);
      axis8->Draw();
      
      pad82->cd();
      TLegend *leg8 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg8->SetBorderSize(1);
      leg8->SetFillColor(0);
      leg8->SetTextFont(42);
      leg8->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg8->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg8->AddEntry(h8_1, "Quadratic Sum of significance from left");
      leg8->AddEntry(h8_2, "Quadratic Sum of significance from right");
      leg8->Draw();
      
      c8 -> SaveAs("pTtautau_10p51.pdf");
    
    
    //   ===========================================================   dPtLepTau   ===========================================================
      
      TCanvas *c19 = new TCanvas ("c19", "dPtLepTau",980,580);
        
      TPad *pad191 = new TPad("pad191","",0,0,0.75,1);
      TPad *pad192 = new TPad("pad192","",0.73,0,1,1);
      pad191->Draw();
      pad192->Draw();
        
      pad191->cd();
      pad191->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",60,0,1200);
        h_hist[i]->GetXaxis()->SetTitle("#Deltap_{T} (#tau,#tau) [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPtLepTau*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h19_1 = new TH1F("h19_1","Quadratic Sum from left",60,0,1200); //left
      
    double QuadraticSum_l_19 = 0;
    double R_l_19 = 0;
    double E_l_19 = 0;
    double EE_l_19 = 0;

    for (int j=1; j<=60; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_l_19 +=  2* ( (S + B) * LSB - S );
            E_l_19 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_l_19 = sqrt(R_l_19);
        if(R_l_19 > 0) { EE_l_19 = sqrt(E_l_19) / QuadraticSum_l_19; }

        h19_1->SetBinContent(j,QuadraticSum_l_19);
        h19_1->SetLineColor(kBlue-9);
        h19_1->SetLineStyle(2);

    }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h19_2 = new TH1F("h19_2","Quadratic Sum from right",60,0,1200); //right
      
    double QuadraticSum_r_19 = 0;
    double R_r_19 = 0;
    double E_r_19 = 0;
    double EE_r_19 = 0;

    for (int j=60; j>=1; j--) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_r_19 +=  2* ( (S + B) * LSB - S );
            E_r_19 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_r_19 = sqrt(R_r_19);
        if(R_r_19 > 0) { EE_r_19 = sqrt(E_r_19) / QuadraticSum_r_19; }

        h19_2->SetBinContent(j,QuadraticSum_r_19);
        h19_2->SetLineColor(kGreen-9);
        h19_2->SetLineStyle(2);

    }
      
      float rightmax19 = 1.1*h19_1->GetMaximum();
      float scale19 = 10000 / rightmax19;
      h19_1->Scale(scale19);
      h19_1->Draw("SAMEHIST");
      
      h19_2->Scale(scale19);
      h19_2->Draw("SAMEHIST");
      

    
      TGaxis*axis19 = new TGaxis(1200,0,1200,10000,0,rightmax19,510,"+L");
      axis19->SetTitle("Quadratic Sum of significance");
      axis19->SetTitleSize(0.03);
      axis19->SetLabelSize(0.025);
      axis19->Draw();
      
      pad192->cd();
      TLegend *leg19 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg19->SetBorderSize(1);
      leg19->SetFillColor(0);
      leg19->SetTextFont(42);
      leg19->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg19->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg19->AddEntry(h19_1, "Quadratic Sum of significance from left");
      leg19->AddEntry(h19_2, "Quadratic Sum of significance from right");
      leg19->Draw();
      
      c19 -> SaveAs("dPtLepTau_10p51.pdf");
     
    
    //   ===========================================================   TauPt   ===========================================================
      
      TCanvas *c9 = new TCanvas ("c9", "TauPt",980,580);
        
      TPad *pad91 = new TPad("pad91","",0,0,0.75,1);
      TPad *pad92 = new TPad("pad92","",0.73,0,1,1);
      pad91->Draw();
      pad92->Draw();
        
      pad91->cd();
      pad91->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",60,0,1200);
        h_hist[i]->GetXaxis()->SetTitle("p_{T}^{#tau_{h}} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 20000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="TauPt>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
    
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h9_1 = new TH1F("h9_1","Quadratic Sum from left",60,0,1200); //left
      
    double QuadraticSum_l_9 = 0;
    double R_l_9 = 0;
    double E_l_9 = 0;
    double EE_l_9 = 0;

    for (int j=1; j<=60; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_l_9 +=  2* ( (S + B) * LSB - S );
            E_l_9 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_l_9 = sqrt(R_l_9);
        if(R_l_9 > 0) { EE_l_9 = sqrt(E_l_9) / QuadraticSum_l_9; }

        h9_1->SetBinContent(j,QuadraticSum_l_9);
        h9_1->SetLineColor(kBlue-9);
        h9_1->SetLineStyle(2);

    }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h9_2 = new TH1F("h9_2","Quadratic Sum from right",60,0,1200); //right
      
    double QuadraticSum_r_9 = 0;
    double R_r_9 = 0;
    double E_r_9 = 0;
    double EE_r_9 = 0;

    for (int j=60; j>=1; j--) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_r_9 +=  2* ( (S + B) * LSB - S );
            E_r_9 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_r_9 = sqrt(R_r_9);
        if(R_r_9 > 0) { EE_r_9 = sqrt(E_r_9) / QuadraticSum_r_9; }

        h9_2->SetBinContent(j,QuadraticSum_r_9);
        h9_2->SetLineColor(kGreen-9);
        h9_2->SetLineStyle(2);

    }
      
      float rightmax9 = 1.1*h9_1->GetMaximum();
      float scale9 = 20000 / rightmax9;
      h9_1->Scale(scale9);
      h9_1->Draw("SAMEHIST");
      
      h9_2->Scale(scale9);
      h9_2->Draw("SAMEHIST");
      
    
      TGaxis*axis9 = new TGaxis(1200,0,1200,20000,0,rightmax9,510,"+L");
      axis9->SetTitle("Quadratic Sum of significance");
      axis9->SetTitleSize(0.03);
      axis9->SetLabelSize(0.025);
      axis9->Draw();
      
      pad92->cd();
      TLegend *leg9 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg9->SetBorderSize(1);
      leg9->SetFillColor(0);
      leg9->SetTextFont(42);
      leg9->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg9->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg9->AddEntry(h9_1, "Quadratic Sum of significance from left");
      leg9->AddEntry(h9_2, "Quadratic Sum of significance from right");
      leg9->Draw();
      
      c9 -> SaveAs("TauPt_10p51.pdf");
    
    
    //   ===========================================================   LepPt   ===========================================================
      
      TCanvas *c10 = new TCanvas ("c10", "LepPt",980,580);
        
      TPad *pad101 = new TPad("pad101","",0,0,0.75,1);
      TPad *pad102 = new TPad("pad102","",0.73,0,1,1);
      pad101->Draw();
      pad102->Draw();
        
      pad101->cd();
      pad101->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",55,0,1100);
        h_hist[i]->GetXaxis()->SetTitle("p_{T}^{#tau_{l}} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 12000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="LepPt>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h10_1 = new TH1F("h10_1","Quadratic Sum from left",55,0,1100); //left
      
    double QuadraticSum_l_10 = 0;
    double R_l_10 = 0;
    double E_l_10 = 0;
    double EE_l_10 = 0;

    for (int j=1; j<=55; j++) {

        double S = h_hist[1]->GetBinContent(j);
         double B = h_hist[0]->GetBinContent(j);
         double dS = h_hist[1]->GetBinError(j);
         double dB = h_hist[0]->GetBinError(j);

        if( B > 0 && S > 0) {
            double LSB = log(1+S/B);
            R_l_10 +=  2* ( (S + B) * LSB - S );
            E_l_10 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
        }

        QuadraticSum_l_10 = sqrt(R_l_10);
        if(R_l_10 > 0) { EE_l_10 = sqrt(E_l_10) / QuadraticSum_l_10; }

        h10_1->SetBinContent(j,QuadraticSum_l_10);
        h10_1->SetLineColor(kBlue-9);
        h10_1->SetLineStyle(2);

    }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h10_2 = new TH1F("h10_2","Quadratic Sum from right",55,0,1100); //right

       double QuadraticSum_r_10 = 0;
       double R_r_10 = 0;
       double E_r_10 = 0;
       double EE_r_10 = 0;

       for (int j=55; j>=1; j--) {

           double S = h_hist[1]->GetBinContent(j);
            double B = h_hist[0]->GetBinContent(j);
            double dS = h_hist[1]->GetBinError(j);
            double dB = h_hist[0]->GetBinError(j);

           if( B > 0 && S > 0) {
               double LSB = log(1+S/B);
               R_r_10 +=  2* ( (S + B) * LSB - S );
               E_r_10 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
           }

           QuadraticSum_r_10 = sqrt(R_r_10);
           if(R_r_10 > 0) { EE_r_10 = sqrt(E_r_10) / QuadraticSum_r_10; }

           h10_2->SetBinContent(j,QuadraticSum_r_10);
           h10_2->SetLineColor(kGreen-9);
           h10_2->SetLineStyle(2);

       }
      
      
      float rightmax10 = 1.1*h10_1->GetMaximum();
      float scale10 = 12000 / rightmax10;
      h10_1->Scale(scale10);
      h10_1->Draw("SAMEHIST");
      
      h10_2->Scale(scale10);
      h10_2->Draw("SAMEHIST");
      
    
    TGaxis*axis10 = new TGaxis(1100,0,1100,12000,0,rightmax10,510,"+L");
      axis10->SetTitle("Quadratic Sum of significance");
      axis10->SetTitleSize(0.03);
      axis10->SetLabelSize(0.025);
      axis10->Draw();
      
      pad102->cd();
      TLegend *leg10 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg10->SetBorderSize(1);
      leg10->SetFillColor(0);
      leg10->SetTextFont(42);
      leg10->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg10->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg10->AddEntry(h10_1, "Quadratic Sum of significance from left");
      leg10->AddEntry(h10_2, "Quadratic Sum of significance from right");
      leg10->Draw();
      
      c10 -> SaveAs("LepPt_10p51.pdf");
    
    
    //   ===========================================================   mMMC   ===========================================================
      
      TCanvas *c11 = new TCanvas ("c11", "mMMC",980,580);
        
      TPad *pad111 = new TPad("pad111","",0,0,0.75,1);
      TPad *pad112 = new TPad("pad112","",0.73,0,1,1);
      pad111->Draw();
      pad112->Draw();
        
      pad111->cd();
      pad111->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",100,0,5000);
        h_hist[i]->GetXaxis()->SetTitle("m_{MMC} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 6000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="mMMC*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h11_1 = new TH1F("h11_1","Quadratic Sum from left",100,0,5000); //left
      
          double QuadraticSum_l_11 = 0;
          double R_l_11 = 0;
          double E_l_11 = 0;
          double EE_l_11 = 0;

          for (int j=1; j<=100; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_11 +=  2* ( (S + B) * LSB - S );
                  E_l_11 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_11 = sqrt(R_l_11);
              if(R_l_11 > 0) { EE_l_11 = sqrt(E_l_11) / QuadraticSum_l_11; }

              h11_1->SetBinContent(j,QuadraticSum_l_11);
              h11_1->SetLineColor(kBlue-9);
              h11_1->SetLineStyle(2);

          }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h11_2 = new TH1F("h11_2","Quadratic Sum from right",100,0,5000); //right
      
          double QuadraticSum_r_11 = 0;
          double R_r_11 = 0;
          double E_r_11 = 0;
          double EE_r_11 = 0;

          for (int j=100; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_11 +=  2* ( (S + B) * LSB - S );
                  E_r_11 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_11 = sqrt(R_r_11);
              if(R_r_11 > 0) { EE_r_11 = sqrt(E_r_11) / QuadraticSum_r_11; }

              h11_2->SetBinContent(j,QuadraticSum_r_11);
              h11_2->SetLineColor(kGreen-9);
              h11_2->SetLineStyle(2);

          }
     
      
      
      float rightmax11 = 1.1*h11_1->GetMaximum();
      float scale11 = 6000 / rightmax11;
      h11_1->Scale(scale11);
      h11_1->Draw("SAMEHIST");
      
      h11_2->Scale(scale11);
      h11_2->Draw("SAMEHIST");
      
    
      TGaxis*axis11 = new TGaxis(5000,0,5000,6000,0,rightmax11,510,"+L");
      axis11->SetTitle("Quadratic Sum of significance");
      axis11->SetTitleSize(0.03);
      axis11->SetLabelSize(0.025);
      axis11->Draw();
      
      pad112->cd();
      TLegend *leg11 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg11->SetBorderSize(1);
      leg11->SetFillColor(0);
      leg11->SetTextFont(42);
      leg11->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg11->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg11->AddEntry(h11_1, "Quadratic Sum of significance from left");
      leg11->AddEntry(h11_2, "Quadratic Sum of significance from right");
      leg11->Draw();
      
      c11 -> SaveAs("mMMC_10p51.pdf");
    
     
    //   ===========================================================   dPhiLepTau   ===========================================================
      
      TCanvas *c12 = new TCanvas ("c12", "dPhiLepTau",980,580);
        
      TPad *pad121 = new TPad("pad121","",0,0,0.75,1);
      TPad *pad122 = new TPad("pad122","",0.73,0,1,1);
      pad121->Draw();
      pad122->Draw();
        
      pad121->cd();
      pad121->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
        h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (#tau,#tau)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 1500);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPhiLepTau>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h12_1 = new TH1F("h12_1","Quadratic Sum from left",20,0,3.5); //left
      
          double QuadraticSum_l_12 = 0;
          double R_l_12 = 0;
          double E_l_12 = 0;
          double EE_l_12 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_12 +=  2* ( (S + B) * LSB - S );
                  E_l_12 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_12 = sqrt(R_l_12);
              if(R_l_12 > 0) { EE_l_12 = sqrt(E_l_12) / QuadraticSum_l_12; }

              h12_1->SetBinContent(j,QuadraticSum_l_12);
              h12_1->SetLineColor(kBlue-9);
              h12_1->SetLineStyle(2);

          }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h12_2 = new TH1F("h12_2","Quadratic Sum from right",20,0,3.5); //right
      
          double QuadraticSum_r_12 = 0;
          double R_r_12 = 0;
          double E_r_12 = 0;
          double EE_r_12 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_12 +=  2* ( (S + B) * LSB - S );
                  E_r_12 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_12 = sqrt(R_r_12);
              if(R_r_12 > 0) { EE_r_12 = sqrt(E_r_12) / QuadraticSum_r_12; }

              h12_2->SetBinContent(j,QuadraticSum_r_12);
              h12_2->SetLineColor(kGreen-9);
              h12_2->SetLineStyle(2);

          }
      
      float rightmax12 = 1.1*h12_1->GetMaximum();
      float scale12 = 1500 / rightmax12;
      h12_1->Scale(scale12);
      h12_1->Draw("SAMEHIST");
      
      h12_2->Scale(scale12);
      h12_2->Draw("SAMEHIST");
      
    
      TGaxis*axis12 = new TGaxis(3.5,0,3.5,1500,0,rightmax12,510,"+L");
      axis12->SetTitle("Quadratic Sum of significance");
      axis12->SetTitleSize(0.03);
      axis12->SetLabelSize(0.025);
      axis12->Draw();
      
      pad122->cd();
      TLegend *leg12 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg12->SetBorderSize(1);
      leg12->SetFillColor(0);
      leg12->SetTextFont(42);
      leg12->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg12->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg12->AddEntry(h12_1, "Quadratic Sum of significance from left");
      leg12->AddEntry(h12_2, "Quadratic Sum of significance from right");
      leg12->Draw();
      
      c12 -> SaveAs("dPhiLepTau_10p51.pdf");
    
    
    //   ===========================================================   TauPhi   ===========================================================
      
      TCanvas *c13 = new TCanvas ("c13", "TauPhi",980,580);
        
      TPad *pad131 = new TPad("pad131","",0,0,0.75,1);
      TPad *pad132 = new TPad("pad132","",0.73,0,1,1);
      pad131->Draw();
      pad132->Draw();
        
      pad131->cd();
      pad131->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
        h_hist[i]->GetXaxis()->SetTitle("#phi_{#tau_{h}}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 1000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="TauPhi>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h13_1 = new TH1F("h13_1","Quadratic Sum from left",20,0,3.5); //left
      
          double QuadraticSum_l_13 = 0;
          double R_l_13 = 0;
          double E_l_13 = 0;
          double EE_l_13 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_13 +=  2* ( (S + B) * LSB - S );
                  E_l_13 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_13 = sqrt(R_l_13);
              if(R_l_13 > 0) { EE_l_13 = sqrt(E_l_13) / QuadraticSum_l_13; }

              h13_1->SetBinContent(j,QuadraticSum_l_13);
              h13_1->SetLineColor(kBlue-9);
              h13_1->SetLineStyle(2);

          }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h13_2 = new TH1F("h13_2","Quadratic Sum from right",20,0,3.5); //right
      
          double QuadraticSum_r_13 = 0;
          double R_r_13 = 0;
          double E_r_13 = 0;
          double EE_r_13 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_13 +=  2* ( (S + B) * LSB - S );
                  E_r_13 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_13 = sqrt(R_r_13);
              if(R_r_13 > 0) { EE_r_13 = sqrt(E_r_13) / QuadraticSum_r_13; }

              h13_2->SetBinContent(j,QuadraticSum_r_13);
              h13_2->SetLineColor(kGreen-9);
              h13_2->SetLineStyle(2);

          }
      
      float rightmax13 = 1.1*h13_1->GetMaximum();
      float scale13 = 1000 / rightmax13;
      h13_1->Scale(scale13);
      h13_1->Draw("SAMEHIST");
      
      h13_2->Scale(scale13);
      h13_2->Draw("SAMEHIST");
      
    
      TGaxis*axis13 = new TGaxis(3.5,0,3.5,1000,0,rightmax13,510,"+L");
      axis13->SetTitle("Quadratic Sum of significance");
      axis13->SetTitleSize(0.03);
      axis13->SetLabelSize(0.025);
      axis13->Draw();
      
      pad132->cd();
      TLegend *leg13 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg13->SetBorderSize(1);
      leg13->SetFillColor(0);
      leg13->SetTextFont(42);
      leg13->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg13->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg13->AddEntry(h13_1, "Quadratic Sum of significance from left");
      leg13->AddEntry(h13_2, "Quadratic Sum of significance from right");
      leg13->Draw();
      
      c13 -> SaveAs("TauPhi_10p51.pdf");
    
    
    //   ===========================================================   LepPhi   ===========================================================
      
      TCanvas *c14 = new TCanvas ("c14", "LepPhi",980,580);
        
      TPad *pad141 = new TPad("pad141","",0,0,0.75,1);
      TPad *pad142 = new TPad("pad142","",0.73,0,1,1);
      pad141->Draw();
      pad142->Draw();
        
      pad141->cd();
      pad141->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
        h_hist[i]->GetXaxis()->SetTitle("#phi_{#tau_{l}}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 1000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="LepPhi>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
      
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
    
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h14_1 = new TH1F("h14_1","Quadratic Sum from left",20,0,3.5); //left
      
          double QuadraticSum_l_14 = 0;
          double R_l_14 = 0;
          double E_l_14 = 0;
          double EE_l_14 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_14 +=  2* ( (S + B) * LSB - S );
                  E_l_14 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_14 = sqrt(R_l_14);
              if(R_l_14 > 0) { EE_l_14 = sqrt(E_l_14) / QuadraticSum_l_14; }

              h14_1->SetBinContent(j,QuadraticSum_l_14);
              h14_1->SetLineColor(kBlue-9);
              h14_1->SetLineStyle(2);

          }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h14_2 = new TH1F("h14_2","Quadratic Sum from right",20,0,3.5); //right
      
          double QuadraticSum_r_14 = 0;
          double R_r_14 = 0;
          double E_r_14 = 0;
          double EE_r_14 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_14 +=  2* ( (S + B) * LSB - S );
                  E_r_14 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_14 = sqrt(R_r_14);
              if(R_r_14 > 0) { EE_r_14 = sqrt(E_r_14) / QuadraticSum_r_14; }

              h14_2->SetBinContent(j,QuadraticSum_r_14);
              h14_2->SetLineColor(kGreen-9);
              h14_2->SetLineStyle(2);

          }
      
      float rightmax14 = 1.1*h14_1->GetMaximum();
      float scale14 = 1000 / rightmax14;
      h14_1->Scale(scale14);
      h14_1->Draw("SAMEHIST");
      
      h14_2->Scale(scale14);
      h14_2->Draw("SAMEHIST");
      
    
      TGaxis*axis14 = new TGaxis(3.5,0,3.5,1000,0,rightmax14,510,"+L");
      axis14->SetTitle("Quadratic Sum of significance");
      axis14->SetTitleSize(0.03);
      axis14->SetLabelSize(0.025);
      axis14->Draw();
      
      pad142->cd();
      TLegend *leg14 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg14->SetBorderSize(1);
      leg14->SetFillColor(0);
      leg14->SetTextFont(42);
      leg14->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg14->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg14->AddEntry(h14_1, "Quadratic Sum of significance from left");
      leg14->AddEntry(h14_2, "Quadratic Sum of significance from right");
      leg14->Draw();
      
      c14 -> SaveAs("LepPhi_10p51.pdf");
     
    
    //   ===========================================================   dEtaLepTau   ===========================================================
      
      TCanvas *c15 = new TCanvas ("c15", "dEtaLepTau",980,580);
        
      TPad *pad151 = new TPad("pad151","",0,0,0.75,1);
      TPad *pad152 = new TPad("pad152","",0.73,0,1,1);
      pad151->Draw();
      pad152->Draw();
        
      pad151->cd();
      pad151->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",25,0,5);
        h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (#tau,#tau)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4000);
      }
     
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="abs(TauEta-LepEta)>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }

    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
    
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h15_1 = new TH1F("h15_1","Quadratic Sum from left",25,0,5); //left
      
          double QuadraticSum_l_15 = 0;
          double R_l_15 = 0;
          double E_l_15 = 0;
          double EE_l_15 = 0;

          for (int j=1; j<=25; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_15 +=  2* ( (S + B) * LSB - S );
                  E_l_15 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_15 = sqrt(R_l_15);
              if(R_l_15 > 0) { EE_l_15 = sqrt(E_l_15) / QuadraticSum_l_15; }

              h15_1->SetBinContent(j,QuadraticSum_l_15);
              h15_1->SetLineColor(kBlue-9);
              h15_1->SetLineStyle(2);

          }

     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h15_2 = new TH1F("h15_2","Quadratic Sum from right",25,0,5); //right
      
          double QuadraticSum_r_15 = 0;
          double R_r_15 = 0;
          double E_r_15 = 0;
          double EE_r_15 = 0;

          for (int j=25; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_15 +=  2* ( (S + B) * LSB - S );
                  E_r_15 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_15 = sqrt(R_r_15);
              if(R_r_15 > 0) { EE_r_15 = sqrt(E_r_15) / QuadraticSum_r_15; }

              h15_2->SetBinContent(j,QuadraticSum_r_15);
              h15_2->SetLineColor(kGreen-9);
              h15_2->SetLineStyle(2);

          }
      
      float rightmax15 = 1.1*h15_1->GetMaximum();
      float scale15 = 4000 / rightmax15;
      h15_1->Scale(scale15);
      h15_1->Draw("SAMEHIST");
      
      h15_2->Scale(scale15);
      h15_2->Draw("SAMEHIST");
      
    
      TGaxis*axis15 = new TGaxis(5,0,5,4000,0,rightmax15,510,"+L");
      axis15->SetTitle("Quadratic Sum of significance");
      axis15->SetTitleSize(0.03);
      axis15->SetLabelSize(0.025);
      axis15->Draw();
      
      pad152->cd();
      TLegend *leg15 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg15->SetBorderSize(1);
      leg15->SetFillColor(0);
      leg15->SetTextFont(42);
      leg15->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg15->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg15->AddEntry(h15_1, "Quadratic Sum of significance from left");
      leg15->AddEntry(h15_2, "Quadratic Sum of significance from right");
      leg15->Draw();
      
      c15 -> SaveAs("dEtaLepTau_10p51.pdf");
 
    //   ===========================================================   TauEta   ===========================================================
      
      TCanvas *c16 = new TCanvas ("c16", "TauEta",980,580);
        
      TPad *pad161 = new TPad("pad161","",0,0,0.75,1);
      TPad *pad162 = new TPad("pad162","",0.73,0,1,1);
      pad161->Draw();
      pad162->Draw();
        
      pad161->cd();
      pad161->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",25,-2.5,2.5);
        h_hist[i]->GetXaxis()->SetTitle("#eta_{#tau_{h}}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3000);
      }
    
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="TauEta>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h16_1 = new TH1F("h16_1","Quadratic Sum from left",25,-2.5,2.5); //left
      
          double QuadraticSum_l_16 = 0;
          double R_l_16 = 0;
          double E_l_16 = 0;
          double EE_l_16 = 0;

          for (int j=1; j<=25; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_16 +=  2* ( (S + B) * LSB - S );
                  E_l_16 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_16 = sqrt(R_l_16);
              if(R_l_16 > 0) { EE_l_16 = sqrt(E_l_16) / QuadraticSum_l_16; }

              h16_1->SetBinContent(j,QuadraticSum_l_16);
              h16_1->SetLineColor(kBlue-9);
              h16_1->SetLineStyle(2);

          }
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h16_2 = new TH1F("h16_2","Quadratic Sum from right",25,-2.5,2.5); //right
      
          double QuadraticSum_r_16 = 0;
          double R_r_16 = 0;
          double E_r_16 = 0;
          double EE_r_16 = 0;

          for (int j=25; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_16 +=  2* ( (S + B) * LSB - S );
                  E_r_16 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_16 = sqrt(R_r_16);
              if(R_r_16 > 0) { EE_r_16 = sqrt(E_r_16) / QuadraticSum_r_16; }

              h16_2->SetBinContent(j,QuadraticSum_r_16);
              h16_2->SetLineColor(kGreen-9);
              h16_2->SetLineStyle(2);

          }
      
      float rightmax16 = 1.1*h16_1->GetMaximum();
      float scale16 = 3000 / rightmax16;
      h16_1->Scale(scale16);
      h16_1->Draw("SAMEHIST");
      
      h16_2->Scale(scale16);
      h16_2->Draw("SAMEHIST");
      
    
      TGaxis*axis16 = new TGaxis(2.5,0,2.5,3000,0,rightmax16,510,"+L");
      axis16->SetTitle("Quadratic Sum of significance");
      axis16->SetTitleSize(0.03);
      axis16->SetLabelSize(0.025);
      axis16->Draw();
      
      pad162->cd();
      TLegend *leg16 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg16->SetBorderSize(1);
      leg16->SetFillColor(0);
      leg16->SetTextFont(42);
      leg16->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg16->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg16->AddEntry(h16_1, "Quadratic Sum of significance from left");
      leg16->AddEntry(h16_2, "Quadratic Sum of significance from right");
      leg16->Draw();
      
      c16 -> SaveAs("TauEta_10p51.pdf");
    
    
    //   ===========================================================   LepEta   ===========================================================
      
      TCanvas *c17 = new TCanvas ("c17", "LepEta",980,580);
        
      TPad *pad171 = new TPad("pad171","",0,0,0.75,1);
      TPad *pad172 = new TPad("pad172","",0.73,0,1,1);
      pad171->Draw();
      pad172->Draw();
        
      pad171->cd();
      pad171->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",30,-3,3);
        h_hist[i]->GetXaxis()->SetTitle("#eta_{#tau_{l}}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3000);
      }
     
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="LepEta>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
         
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h17_1 = new TH1F("h17_1","Quadratic Sum from left",30,-3,3); //left
      
          double QuadraticSum_l_17 = 0;
          double R_l_17 = 0;
          double E_l_17 = 0;
          double EE_l_17 = 0;

          for (int j=1; j<=30; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_17 +=  2* ( (S + B) * LSB - S );
                  E_l_17 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_17 = sqrt(R_l_17);
              if(R_l_17 > 0) { EE_l_17 = sqrt(E_l_17) / QuadraticSum_l_17; }

              h17_1->SetBinContent(j,QuadraticSum_l_17);
              h17_1->SetLineColor(kBlue-9);
              h17_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h17_2 = new TH1F("h17_2","Quadratic Sum from right",30,-3,3); //right
      
          double QuadraticSum_r_17 = 0;
          double R_r_17 = 0;
          double E_r_17 = 0;
          double EE_r_17 = 0;

          for (int j=30; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_17 +=  2* ( (S + B) * LSB - S );
                  E_r_17 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_17 = sqrt(R_r_17);
              if(R_r_17 > 0) { EE_r_17 = sqrt(E_r_17) / QuadraticSum_r_17; }

              h17_2->SetBinContent(j,QuadraticSum_r_17);
              h17_2->SetLineColor(kGreen-9);
              h17_2->SetLineStyle(2);

          }
      
      
      float rightmax17 = 1.1*h17_1->GetMaximum();
      float scale17 = 3000 / rightmax17;
      h17_1->Scale(scale17);
      h17_1->Draw("SAMEHIST");
      
      h17_2->Scale(scale17);
      h17_2->Draw("SAMEHIST");
      
    
      TGaxis*axis17 = new TGaxis(3,0,3,3000,0,rightmax17,510,"+L");
      axis17->SetTitle("Quadratic Sum of significance");
      axis17->SetTitleSize(0.03);
      axis17->SetLabelSize(0.025);
      axis17->Draw();
      
      pad172->cd();
      TLegend *leg17 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg17->SetBorderSize(1);
      leg17->SetFillColor(0);
      leg17->SetTextFont(42);
      leg17->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg17->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg17->AddEntry(h17_1, "Quadratic Sum of significance from left");
      leg17->AddEntry(h17_2, "Quadratic Sum of significance from right");
      leg17->Draw();
      
      c17 -> SaveAs("LepEta_10p51.pdf");
    
    
    //   ===========================================================   dRLepTau   ===========================================================
      
      TCanvas *c18 = new TCanvas ("c18", "dRLepTau",980,580);
        
      TPad *pad181 = new TPad("pad181","",0,0,0.75,1);
      TPad *pad182 = new TPad("pad182","",0.73,0,1,1);
      pad181->Draw();
      pad182->Draw();
        
      pad181->cd();
      pad181->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",30,0,6);
        h_hist[i]->GetXaxis()->SetTitle("#DeltaR (#tau,#tau)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4500);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dRLepTau>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h18_1 = new TH1F("h18_1","Quadratic Sum from left",30,0,6); //left
      
          double QuadraticSum_l_18 = 0;
          double R_l_18 = 0;
          double E_l_18 = 0;
          double EE_l_18 = 0;

          for (int j=1; j<=30; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_18 +=  2* ( (S + B) * LSB - S );
                  E_l_18 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_18 = sqrt(R_l_18);
              if(R_l_18 > 0) { EE_l_18 = sqrt(E_l_18) / QuadraticSum_l_18; }

              h18_1->SetBinContent(j,QuadraticSum_l_18);
              h18_1->SetLineColor(kBlue-9);
              h18_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h18_2 = new TH1F("h18_2","Quadratic Sum from right",30,0,6); //right
      
          double QuadraticSum_r_18 = 0;
          double R_r_18 = 0;
          double E_r_18 = 0;
          double EE_r_18 = 0;

          for (int j=30; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_18 +=  2* ( (S + B) * LSB - S );
                  E_r_18 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_18 = sqrt(R_r_18);
              if(R_r_18 > 0) { EE_r_18 = sqrt(E_r_18) / QuadraticSum_r_18; }

              h18_2->SetBinContent(j,QuadraticSum_r_18);
              h18_2->SetLineColor(kGreen-9);
              h18_2->SetLineStyle(2);

          }
      
      
      float rightmax18 = 1.1*h18_1->GetMaximum();
      float scale18 = 4500 / rightmax18;
      h18_1->Scale(scale18);
      h18_1->Draw("SAMEHIST");
      
      h18_2->Scale(scale18);
      h18_2->Draw("SAMEHIST");
      
    
      TGaxis*axis18 = new TGaxis(6,0,6,4500,0,rightmax18,510,"+L");
      axis18->SetTitle("Quadratic Sum of significance");
      axis18->SetTitleSize(0.03);
      axis18->SetLabelSize(0.025);
      axis18->Draw();
      
      pad182->cd();
      TLegend *leg18 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg18->SetBorderSize(1);
      leg18->SetFillColor(0);
      leg18->SetTextFont(42);
      leg18->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg18->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg18->AddEntry(h18_1, "Quadratic Sum of significance from left");
      leg18->AddEntry(h18_2, "Quadratic Sum of significance from right");
      leg18->Draw();
      
      c18 -> SaveAs("dRLepTau_10p51.pdf");
    
    
    //   ===========================================================   MT2   ===========================================================
      
      TCanvas *c20 = new TCanvas ("c20", "MT2",980,580);
        
      TPad *pad201 = new TPad("pad201","",0,0,0.75,1);
      TPad *pad202 = new TPad("pad202","",0.73,0,1,1);
      pad201->Draw();
      pad202->Draw();
        
      pad201->cd();
      pad201->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",40,0,800);
        h_hist[i]->GetXaxis()->SetTitle("m_{T}^{2} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="MT2*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h20_1 = new TH1F("h20_1","Quadratic Sum from left",40,0,800); //left
      
          double QuadraticSum_l_20 = 0;
          double R_l_20 = 0;
          double E_l_20 = 0;
          double EE_l_20 = 0;

          for (int j=1; j<=40; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

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
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h20_2 = new TH1F("h20_2","Quadratic Sum from right",40,0,800); //right
      
          double QuadraticSum_r_20 = 0;
          double R_r_20 = 0;
          double E_r_20 = 0;
          double EE_r_20 = 0;

          for (int j=40; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

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
      axis20->SetTitle("Quadratic Sum of significance");
      axis20->SetTitleSize(0.03);
      axis20->SetLabelSize(0.025);
      axis20->Draw();
      
      pad202->cd();
      TLegend *leg20 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg20->SetBorderSize(1);
      leg20->SetFillColor(0);
      leg20->SetTextFont(42);
      leg20->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg20->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg20->AddEntry(h20_1, "Quadratic Sum of significance from left");
      leg20->AddEntry(h20_2, "Quadratic Sum of significance from right");
      leg20->Draw();
      
      c20 -> SaveAs("MT2_10p51.pdf");
    
    
    //   ===========================================================   pTVBFj1   ===========================================================
      
      TCanvas *c21 = new TCanvas ("c21", "pTVBFj1",980,580);
        
      TPad *pad10p51 = new TPad("pad10p51","",0,0,0.75,1);
      TPad *pad212 = new TPad("pad212","",0.73,0,1,1);
      pad10p51->Draw();
      pad212->Draw();
        
      pad10p51->cd();
      pad10p51->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",40,0,2000);
        h_hist[i]->GetXaxis()->SetTitle("VBF p_{T}^{j1} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 8000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="pTVBFj1*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h21_1 = new TH1F("h21_1","Quadratic Sum from left",40,0,2000); //left
      
          double QuadraticSum_l_21 = 0;
          double R_l_21 = 0;
          double E_l_21 = 0;
          double EE_l_21 = 0;

          for (int j=1; j<=40; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_21 +=  2* ( (S + B) * LSB - S );
                  E_l_21 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_21 = sqrt(R_l_21);
              if(R_l_21 > 0) { EE_l_21 = sqrt(E_l_21) / QuadraticSum_l_21; }

              h21_1->SetBinContent(j,QuadraticSum_l_21);
              h21_1->SetLineColor(kBlue-9);
              h21_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h21_2 = new TH1F("h21_2","Quadratic Sum from right",40,0,2000); //right
      
          double QuadraticSum_r_21 = 0;
          double R_r_21 = 0;
          double E_r_21 = 0;
          double EE_r_21 = 0;

          for (int j=40; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_21 +=  2* ( (S + B) * LSB - S );
                  E_r_21 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_21 = sqrt(R_r_21);
              if(R_r_21 > 0) { EE_r_21 = sqrt(E_r_21) / QuadraticSum_r_21; }

              h21_2->SetBinContent(j,QuadraticSum_r_21);
              h21_2->SetLineColor(kGreen-9);
              h21_2->SetLineStyle(2);

          }
      
      float rightmax21 = 1.1*h21_1->GetMaximum();
      float scale21 = 8000 / rightmax21;
      h21_1->Scale(scale21);
      h21_1->Draw("SAMEHIST");
      
      h21_2->Scale(scale21);
      h21_2->Draw("SAMEHIST");
      
    
      TGaxis*axis21 = new TGaxis(2000,0,2000,8000,0,rightmax21,510,"+L");
      axis21->SetTitle("Quadratic Sum of significance");
      axis21->SetTitleSize(0.03);
      axis21->SetLabelSize(0.025);
      axis21->Draw();
      
      pad212->cd();
      TLegend *leg21 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg21->SetBorderSize(1);
      leg21->SetFillColor(0);
      leg21->SetTextFont(42);
      leg21->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg21->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg21->AddEntry(h21_1, "Quadratic Sum of significance from left");
      leg21->AddEntry(h21_2, "Quadratic Sum of significance from right");
      leg21->Draw();
      
      c21 -> SaveAs("pTVBFj1_10p51.pdf");
    
    
    //   ===========================================================   pTVBFj2   ===========================================================
      
      TCanvas *c22 = new TCanvas ("c22", "pTVBFj2",980,580);
        
      TPad *pad221 = new TPad("pad221","",0,0,0.75,1);
      TPad *pad222 = new TPad("pad222","",0.73,0,1,1);
      pad221->Draw();
      pad222->Draw();
        
      pad221->cd();
      pad221->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",75,0,1500);
        h_hist[i]->GetXaxis()->SetTitle("VBF p_{T}^{j2} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 15000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="pTVBFj2*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h22_1 = new TH1F("h22_1","Quadratic Sum from left",75,0,1500); //left
      
          double QuadraticSum_l_22 = 0;
          double R_l_22 = 0;
          double E_l_22 = 0;
          double EE_l_22 = 0;

          for (int j=1; j<=75; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_22 +=  2* ( (S + B) * LSB - S );
                  E_l_22 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_22 = sqrt(R_l_22);
              if(R_l_22 > 0) { EE_l_22 = sqrt(E_l_22) / QuadraticSum_l_22; }

              h22_1->SetBinContent(j,QuadraticSum_l_22);
              h22_1->SetLineColor(kBlue-9);
              h22_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h22_2 = new TH1F("h22_2","Quadratic Sum from right",75,0,1500); //right
      
          double QuadraticSum_r_22 = 0;
          double R_r_22 = 0;
          double E_r_22 = 0;
          double EE_r_22 = 0;

          for (int j=75; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_22 +=  2* ( (S + B) * LSB - S );
                  E_r_22 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_22 = sqrt(R_r_22);
              if(R_r_22 > 0) { EE_r_22 = sqrt(E_r_22) / QuadraticSum_r_22; }

              h22_2->SetBinContent(j,QuadraticSum_r_22);
              h22_2->SetLineColor(kGreen-9);
              h22_2->SetLineStyle(2);

          }
      
      float rightmax22 = 1.1*h22_1->GetMaximum();
      float scale22 = 15000 / rightmax22;
      h22_1->Scale(scale22);
      h22_1->Draw("SAMEHIST");
      
      h22_2->Scale(scale22);
      h22_2->Draw("SAMEHIST");
      
    
      TGaxis*axis22 = new TGaxis(1500,0,1500,15000,0,rightmax22,510,"+L");
      axis22->SetTitle("Quadratic Sum of significance");
      axis22->SetTitleSize(0.03);
      axis22->SetLabelSize(0.025);
      axis22->Draw();
      
      pad222->cd();
      TLegend *leg22 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg22->SetBorderSize(1);
      leg22->SetFillColor(0);
      leg22->SetTextFont(42);
      leg22->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg22->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg22->AddEntry(h22_1, "Quadratic Sum of significance from left");
      leg22->AddEntry(h22_2, "Quadratic Sum of significance from right");
      leg22->Draw();
      
      c22 -> SaveAs("pTVBFj2_10p51.pdf");
    
     
    //   ===========================================================   mVBFjj   ===========================================================
      
      TCanvas *c23 = new TCanvas ("c23", "mVBFjj",980,580);
        
      TPad *pad231 = new TPad("pad231","",0,0,0.75,1);
      TPad *pad232 = new TPad("pad232","",0.73,0,1,1);
      pad231->Draw();
      pad232->Draw();
        
      pad231->cd();
      pad231->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
        h_hist[i] = new TH1F(h_nm, "",35,0,7000);
        h_hist[i]->GetXaxis()->SetTitle("VBF m_{jj} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 200 [GeV]");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 13000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="mVBFjj*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h23_1 = new TH1F("h23_1","Quadratic Sum from left",35,0,7000); //left
      
          double QuadraticSum_l_23 = 0;
          double R_l_23 = 0;
          double E_l_23 = 0;
          double EE_l_23 = 0;

          for (int j=1; j<=35; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_23 +=  2* ( (S + B) * LSB - S );
                  E_l_23 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_23 = sqrt(R_l_23);
              if(R_l_23 > 0) { EE_l_23 = sqrt(E_l_23) / QuadraticSum_l_23; }

              h23_1->SetBinContent(j,QuadraticSum_l_23);
              h23_1->SetLineColor(kBlue-9);
              h23_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h23_2 = new TH1F("h23_2","Quadratic Sum from right",35,0,7000); //right
      
          double QuadraticSum_r_23 = 0;
          double R_r_23 = 0;
          double E_r_23 = 0;
          double EE_r_23 = 0;

          for (int j=35; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_23 +=  2* ( (S + B) * LSB - S );
                  E_r_23 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_23 = sqrt(R_r_23);
              if(R_r_23 > 0) { EE_r_23 = sqrt(E_r_23) / QuadraticSum_r_23; }

              h23_2->SetBinContent(j,QuadraticSum_r_23);
              h23_2->SetLineColor(kGreen-9);
              h23_2->SetLineStyle(2);

          }
      
      float rightmax23 = 1.1*h23_1->GetMaximum();
      float scale23 = 13000 / rightmax23;
      h23_1->Scale(scale23);
      h23_1->Draw("SAMEHIST");
      
      h23_2->Scale(scale23);
      h23_2->Draw("SAMEHIST");
      
    
      TGaxis*axis23 = new TGaxis(7000,0,7000,13000,0,rightmax23,510,"+L");
      axis23->SetTitle("Quadratic Sum of significance");
      axis23->SetTitleSize(0.03);
      axis23->SetLabelSize(0.025);
      axis23->Draw();
      
      pad232->cd();
      TLegend *leg23 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg23->SetBorderSize(1);
      leg23->SetFillColor(0);
      leg23->SetTextFont(42);
      leg23->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg23->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg23->AddEntry(h23_1, "Quadratic Sum of significance from left");
      leg23->AddEntry(h23_2, "Quadratic Sum of significance from right");
      leg23->Draw();
      
      c23 -> SaveAs("mVBFjj_10p51.pdf");
    

    //   ===========================================================   phiVBFj1   ===========================================================
      
      TCanvas *c24 = new TCanvas ("c24", "phiVBFj1",980,580);
        
      TPad *pad241 = new TPad("pad241","",0,0,0.75,1);
      TPad *pad242 = new TPad("pad242","",0.73,0,1,1);
      pad241->Draw();
      pad242->Draw();
        
      pad241->cd();
      pad241->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",35,-3.5,3.5);
        h_hist[i]->GetXaxis()->SetTitle("VBF #phi_{j_{1}}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 1400);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="phiVBFj1>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h24_1 = new TH1F("h24_1","Quadratic Sum from left",35,-3.5,3.5); //left
      
          double QuadraticSum_l_24 = 0;
          double R_l_24 = 0;
          double E_l_24 = 0;
          double EE_l_24 = 0;

          for (int j=1; j<=35; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_24 +=  2* ( (S + B) * LSB - S );
                  E_l_24 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_24 = sqrt(R_l_24);
              if(R_l_24 > 0) { EE_l_24 = sqrt(E_l_24) / QuadraticSum_l_24; }

              h24_1->SetBinContent(j,QuadraticSum_l_24);
              h24_1->SetLineColor(kBlue-9);
              h24_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h24_2 = new TH1F("h24_2","Quadratic Sum from right",35,-3.5,3.5); //right
      
          double QuadraticSum_r_24 = 0;
          double R_r_24 = 0;
          double E_r_24 = 0;
          double EE_r_24 = 0;

          for (int j=35; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_24 +=  2* ( (S + B) * LSB - S );
                  E_r_24 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_24 = sqrt(R_r_24);
              if(R_r_24 > 0) { EE_r_24 = sqrt(E_r_24) / QuadraticSum_r_24; }

              h24_2->SetBinContent(j,QuadraticSum_r_24);
              h24_2->SetLineColor(kGreen-9);
              h24_2->SetLineStyle(2);

          }
     
      
      
      float rightmax24 = 1.1*h24_1->GetMaximum();
      float scale24 = 1400 / rightmax24;
      h24_1->Scale(scale24);
      h24_1->Draw("SAMEHIST");
      
      h24_2->Scale(scale24);
      h24_2->Draw("SAMEHIST");
      
    
    TGaxis*axis24 = new TGaxis(3.5,0,3.5,1400,0,rightmax24,510,"+L");
      axis24->SetTitle("Quadratic Sum of significance");
      axis24->SetTitleSize(0.03);
      axis24->SetLabelSize(0.025);
      axis24->Draw();
      
      pad242->cd();
      TLegend *leg24 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg24->SetBorderSize(1);
      leg24->SetFillColor(0);
      leg24->SetTextFont(42);
      leg24->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg24->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg24->AddEntry(h24_1, "Quadratic Sum of significance from left");
      leg24->AddEntry(h24_2, "Quadratic Sum of significance from right");
      leg24->Draw();
      
      c24 -> SaveAs("phiVBFj1_10p51.pdf");
    
    
    //   ===========================================================   phiVBFj2   ===========================================================
      
      TCanvas *c25 = new TCanvas ("c25", "phiVBFj2",980,580);
        
      TPad *pad251 = new TPad("pad251","",0,0,0.75,1);
      TPad *pad252 = new TPad("pad252","",0.73,0,1,1);
      pad251->Draw();
      pad252->Draw();
        
      pad251->cd();
      pad251->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",35,-3.5,3.5);
        h_hist[i]->GetXaxis()->SetTitle("VBF #phi_{j_{2}}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 1400);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="phiVBFj2>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h25_1 = new TH1F("h25_1","Quadratic Sum from left",35,-3.5,3.5); //left
      
          double QuadraticSum_l_25 = 0;
          double R_l_25 = 0;
          double E_l_25 = 0;
          double EE_l_25 = 0;

          for (int j=1; j<=35; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_25 +=  2* ( (S + B) * LSB - S );
                  E_l_25 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_25 = sqrt(R_l_25);
              if(R_l_25 > 0) { EE_l_25 = sqrt(E_l_25) / QuadraticSum_l_25; }

              h25_1->SetBinContent(j,QuadraticSum_l_25);
              h25_1->SetLineColor(kBlue-9);
              h25_1->SetLineStyle(2);

          }
    
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h25_2 = new TH1F("h25_2","Quadratic Sum from right",35,-3.5,3.5); //right
      
          double QuadraticSum_r_25 = 0;
          double R_r_25 = 0;
          double E_r_25 = 0;
          double EE_r_25 = 0;

          for (int j=35; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_25 +=  2* ( (S + B) * LSB - S );
                  E_r_25 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_25 = sqrt(R_r_25);
              if(R_r_25 > 0) { EE_r_25 = sqrt(E_r_25) / QuadraticSum_r_25; }

              h25_2->SetBinContent(j,QuadraticSum_r_25);
              h25_2->SetLineColor(kGreen-9);
              h25_2->SetLineStyle(2);

          }
      
      
      float rightmax25 = 1.1*h25_1->GetMaximum();
      float scale25 = 1400 / rightmax25;
      h25_1->Scale(scale25);
      h25_1->Draw("SAMEHIST");
      
      h25_2->Scale(scale25);
      h25_2->Draw("SAMEHIST");
      
    
    TGaxis*axis25 = new TGaxis(3.5,0,3.5,1400,0,rightmax25,510,"+L");
      axis25->SetTitle("Quadratic Sum of significance");
      axis25->SetTitleSize(0.03);
      axis25->SetLabelSize(0.025);
      axis25->Draw();
      
      pad252->cd();
      TLegend *leg25 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg25->SetBorderSize(1);
      leg25->SetFillColor(0);
      leg25->SetTextFont(42);
      leg25->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg25->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg25->AddEntry(h25_1, "Quadratic Sum of significance from left");
      leg25->AddEntry(h25_2, "Quadratic Sum of significance from right");
      leg25->Draw();
      
      c25 -> SaveAs("phiVBFj2_10p51.pdf");
    

    //   ===========================================================   dEtaVBFjj   ===========================================================
      
      TCanvas *c26 = new TCanvas ("c26", "dEtaVBFjj",980,580);
        
      TPad *pad261 = new TPad("pad261","",0,0,0.75,1);
      TPad *pad262 = new TPad("pad262","",0.73,0,1,1);
      pad261->Draw();
      pad262->Draw();
        
      pad261->cd();
      pad261->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,0,10);
        h_hist[i]->GetXaxis()->SetTitle("VBF #Delta#eta (j,j)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4500);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dEtaVBFjj>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h26_1 = new TH1F("h26_1","Quadratic Sum from left",20,0,10); //left
      
          double QuadraticSum_l_26 = 0;
          double R_l_26 = 0;
          double E_l_26 = 0;
          double EE_l_26 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_26 +=  2* ( (S + B) * LSB - S );
                  E_l_26 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_26 = sqrt(R_l_26);
              if(R_l_26 > 0) { EE_l_26 = sqrt(E_l_26) / QuadraticSum_l_26; }

              h26_1->SetBinContent(j,QuadraticSum_l_26);
              h26_1->SetLineColor(kBlue-9);
              h26_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h26_2 = new TH1F("h26_2","Quadratic Sum from right",20,0,10); //right
      
          double QuadraticSum_r_26 = 0;
          double R_r_26 = 0;
          double E_r_26 = 0;
          double EE_r_26 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_26 +=  2* ( (S + B) * LSB - S );
                  E_r_26 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_26 = sqrt(R_r_26);
              if(R_r_26 > 0) { EE_r_26 = sqrt(E_r_26) / QuadraticSum_r_26; }

              h26_2->SetBinContent(j,QuadraticSum_r_26);
              h26_2->SetLineColor(kGreen-9);
              h26_2->SetLineStyle(2);

          }
      
      float rightmax26 = 1.1*h26_1->GetMaximum();
      float scale26 = 4500 / rightmax26;
      h26_1->Scale(scale26);
      h26_1->Draw("SAMEHIST");
      
      h26_2->Scale(scale26);
      h26_2->Draw("SAMEHIST");
      
    
    TGaxis*axis26 = new TGaxis(10,0,10,4500,0,rightmax26,510,"+L");
      axis26->SetTitle("Quadratic Sum of significance");
      axis26->SetTitleSize(0.03);
      axis26->SetLabelSize(0.025);
      axis26->Draw();
      
      pad262->cd();
      TLegend *leg26 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg26->SetBorderSize(1);
      leg26->SetFillColor(0);
      leg26->SetTextFont(42);
      leg26->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg26->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg26->AddEntry(h26_1, "Quadratic Sum of significance from left");
      leg26->AddEntry(h26_2, "Quadratic Sum of significance from right");
      leg26->Draw();
      
      c26 -> SaveAs("dEtaVBFjj_10p51.pdf");
    
    
    //   ===========================================================   etaVBFj1   ===========================================================
      
      TCanvas *c27 = new TCanvas ("c27", "etaVBFj1",980,580);
        
      TPad *pad271 = new TPad("pad271","",0,0,0.75,1);
      TPad *pad272 = new TPad("pad272","",0.73,0,1,1);
      pad271->Draw();
      pad272->Draw();
        
      pad271->cd();
      pad271->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",21,-5.04,5.04);
        h_hist[i]->GetXaxis()->SetTitle("VBF #eta_{j_{1}}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.48");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3200);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="etaVBFj1>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h27_1 = new TH1F("h27_1","Quadratic Sum from left",21,-5.04,5.04); //left
      
          double QuadraticSum_l_27 = 0;
          double R_l_27 = 0;
          double E_l_27 = 0;
          double EE_l_27 = 0;

          for (int j=1; j<=21; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_27 +=  2* ( (S + B) * LSB - S );
                  E_l_27 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_27 = sqrt(R_l_27);
              if(R_l_27 > 0) { EE_l_27 = sqrt(E_l_27) / QuadraticSum_l_27; }

              h27_1->SetBinContent(j,QuadraticSum_l_27);
              h27_1->SetLineColor(kBlue-9);
              h27_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h27_2 = new TH1F("h27_2","Quadratic Sum from right",21,-5.04,5.04); //right
      
          double QuadraticSum_r_27 = 0;
          double R_r_27 = 0;
          double E_r_27 = 0;
          double EE_r_27 = 0;

          for (int j=21; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_27 +=  2* ( (S + B) * LSB - S );
                  E_r_27 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_27 = sqrt(R_r_27);
              if(R_r_27 > 0) { EE_r_27 = sqrt(E_r_27) / QuadraticSum_r_27; }

              h27_2->SetBinContent(j,QuadraticSum_r_27);
              h27_2->SetLineColor(kGreen-9);
              h27_2->SetLineStyle(2);

          }
     
      
      
      float rightmax27 = 1.1*h27_1->GetMaximum();
      float scale27 = 3200 / rightmax27;
      h27_1->Scale(scale27);
      h27_1->Draw("SAMEHIST");
      
      h27_2->Scale(scale27);
      h27_2->Draw("SAMEHIST");
      
    
    TGaxis*axis27 = new TGaxis(5.04,0,5.04,3200,0,rightmax27,510,"+L");
      axis27->SetTitle("Quadratic Sum of significance");
      axis27->SetTitleSize(0.03);
      axis27->SetLabelSize(0.025);
      axis27->Draw();
      
      pad272->cd();
      TLegend *leg27 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg27->SetBorderSize(1);
      leg27->SetFillColor(0);
      leg27->SetTextFont(42);
      leg27->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg27->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg27->AddEntry(h27_1, "Quadratic Sum of significance from left");
      leg27->AddEntry(h27_2, "Quadratic Sum of significance from right");
      leg27->Draw();
      
      c27 -> SaveAs("etaVBFj1_10p51.pdf");
    
    
    //   ===========================================================   etaVBFj2   ===========================================================
      
      TCanvas *c28 = new TCanvas ("c28", "etaVBFj2",980,580);
        
      TPad *pad281 = new TPad("pad281","",0,0,0.75,1);
      TPad *pad282 = new TPad("pad282","",0.73,0,1,1);
      pad281->Draw();
      pad282->Draw();
        
      pad281->cd();
      pad281->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",21,-5.04,5.04);
        h_hist[i]->GetXaxis()->SetTitle("VBF #eta_{j_{2}}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.48");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3200);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="etaVBFj2>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h28_1 = new TH1F("h28_1","Quadratic Sum from left",21,-5.04,5.04); //left
      
          double QuadraticSum_l_28 = 0;
          double R_l_28 = 0;
          double E_l_28 = 0;
          double EE_l_28 = 0;

          for (int j=1; j<=21; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_28 +=  2* ( (S + B) * LSB - S );
                  E_l_28 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_28 = sqrt(R_l_28);
              if(R_l_28 > 0) { EE_l_28 = sqrt(E_l_28) / QuadraticSum_l_28; }

              h28_1->SetBinContent(j,QuadraticSum_l_28);
              h28_1->SetLineColor(kBlue-9);
              h28_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h28_2 = new TH1F("h28_2","Quadratic Sum from right",21,-5.04,5.04); //right
      
          double QuadraticSum_r_28 = 0;
          double R_r_28 = 0;
          double E_r_28 = 0;
          double EE_r_28 = 0;

          for (int j=21; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_28 +=  2* ( (S + B) * LSB - S );
                  E_r_28 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_28 = sqrt(R_r_28);
              if(R_r_28 > 0) { EE_r_28 = sqrt(E_r_28) / QuadraticSum_r_28; }

              h28_2->SetBinContent(j,QuadraticSum_r_28);
              h28_2->SetLineColor(kGreen-9);
              h28_2->SetLineStyle(2);

          }
      
      float rightmax28 = 1.1*h28_1->GetMaximum();
      float scale28 = 3200 / rightmax28;
      h28_1->Scale(scale28);
      h28_1->Draw("SAMEHIST");
      
      h28_2->Scale(scale28);
      h28_2->Draw("SAMEHIST");
      
    
    TGaxis*axis28 = new TGaxis(5.04,0,5.04,3200,0,rightmax28,510,"+L");
      axis28->SetTitle("Quadratic Sum of significance");
      axis28->SetTitleSize(0.03);
      axis28->SetLabelSize(0.025);
      axis28->Draw();
      
      pad282->cd();
      TLegend *leg28 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg28->SetBorderSize(1);
      leg28->SetFillColor(0);
      leg28->SetTextFont(42);
      leg28->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg28->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg28->AddEntry(h28_1, "Quadratic Sum of significance from left");
      leg28->AddEntry(h28_2, "Quadratic Sum of significance from right");
      leg28->Draw();
      
      c28 -> SaveAs("etaVBFj2_10p51.pdf");
    
    
    //   ===========================================================   dRVBFjj   ===========================================================
      
      TCanvas *c29 = new TCanvas ("c29", "dRVBFjj",980,580);
        
      TPad *pad291 = new TPad("pad291","",0,0,0.75,1);
      TPad *pad292 = new TPad("pad292","",0.73,0,1,1);
      pad291->Draw();
      pad292->Draw();
        
      pad291->cd();
      pad291->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",25,0,10);
        h_hist[i]->GetXaxis()->SetTitle("VBF #DeltaR (j,j)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.4");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4500);
      }
     
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dRVBFjj>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h29_1 = new TH1F("h29_1","Quadratic Sum from left",25,0,10); //left
      
          double QuadraticSum_l_29 = 0;
          double R_l_29 = 0;
          double E_l_29 = 0;
          double EE_l_29 = 0;

          for (int j=1; j<=25; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_29 +=  2* ( (S + B) * LSB - S );
                  E_l_29 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_29 = sqrt(R_l_29);
              if(R_l_29 > 0) { EE_l_29 = sqrt(E_l_29) / QuadraticSum_l_29; }

              h29_1->SetBinContent(j,QuadraticSum_l_29);
              h29_1->SetLineColor(kBlue-9);
              h29_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h29_2 = new TH1F("h29_2","Quadratic Sum from right",25,0,10); //right
      
          double QuadraticSum_r_29 = 0;
          double R_r_29 = 0;
          double E_r_29 = 0;
          double EE_r_29 = 0;

          for (int j=25; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_29 +=  2* ( (S + B) * LSB - S );
                  E_r_29 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_29 = sqrt(R_r_29);
              if(R_r_29 > 0) { EE_r_29 = sqrt(E_r_29) / QuadraticSum_r_29; }

              h29_2->SetBinContent(j,QuadraticSum_r_29);
              h29_2->SetLineColor(kGreen-9);
              h29_2->SetLineStyle(2);

          }
     
      
      float rightmax29 = 1.1*h29_1->GetMaximum();
      float scale29 = 4500 / rightmax29;
      h29_1->Scale(scale29);
      h29_1->Draw("SAMEHIST");
      
      h29_2->Scale(scale29);
      h29_2->Draw("SAMEHIST");
      
    
    TGaxis*axis29 = new TGaxis(10,0,10,4500,0,rightmax29,510,"+L");
      axis29->SetTitle("Quadratic Sum of significance");
      axis29->SetTitleSize(0.03);
      axis29->SetLabelSize(0.025);
      axis29->Draw();
      
      pad292->cd();
      TLegend *leg29 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg29->SetBorderSize(1);
      leg29->SetFillColor(0);
      leg29->SetTextFont(42);
      leg29->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg29->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg29->AddEntry(h29_1, "Quadratic Sum of significance from left");
      leg29->AddEntry(h29_2, "Quadratic Sum of significance from right");
      leg29->Draw();
      
      c29 -> SaveAs("dRVBFjj_10p51.pdf");
    
    
    //   ===========================================================   MET   ===========================================================
      
      TCanvas *c30 = new TCanvas ("c30", "MET",980,580);
        
      TPad *pad301 = new TPad("pad301","",0,0,0.75,1);
      TPad *pad302 = new TPad("pad302","",0.73,0,1,1);
      pad301->Draw();
      pad302->Draw();
        
      pad301->cd();
      pad301->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",45,0,900);
        h_hist[i]->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 8000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="MET*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h30_1 = new TH1F("h30_1","Quadratic Sum from left",45,0,900); //left
      
          double QuadraticSum_l_30 = 0;
          double R_l_30 = 0;
          double E_l_30 = 0;
          double EE_l_30 = 0;

          for (int j=1; j<=45; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_30 +=  2* ( (S + B) * LSB - S );
                  E_l_30 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_30 = sqrt(R_l_30);
              if(R_l_30 > 0) { EE_l_30 = sqrt(E_l_30) / QuadraticSum_l_30; }

              h30_1->SetBinContent(j,QuadraticSum_l_30);
              h30_1->SetLineColor(kBlue-9);
              h30_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h30_2 = new TH1F("h30_2","Quadratic Sum from right",45,0,900); //right
      
          double QuadraticSum_r_30 = 0;
          double R_r_30 = 0;
          double E_r_30 = 0;
          double EE_r_30 = 0;

          for (int j=45; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_30 +=  2* ( (S + B) * LSB - S );
                  E_r_30 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_30 = sqrt(R_r_30);
              if(R_r_30 > 0) { EE_r_30 = sqrt(E_r_30) / QuadraticSum_r_30; }

              h30_2->SetBinContent(j,QuadraticSum_r_30);
              h30_2->SetLineColor(kGreen-9);
              h30_2->SetLineStyle(2);

          }
      
      float rightmax30 = 1.1*h30_1->GetMaximum();
      float scale30 = 8000 / rightmax30;
      h30_1->Scale(scale30);
      h30_1->Draw("SAMEHIST");
      
      h30_2->Scale(scale30);
      h30_2->Draw("SAMEHIST");
      
    
    TGaxis*axis30 = new TGaxis(900,0,900,8000,0,rightmax30,510,"+L");
      axis30->SetTitle("Quadratic Sum of significance");
      axis30->SetTitleSize(0.03);
      axis30->SetLabelSize(0.025);
      axis30->Draw();
      
      pad302->cd();
      TLegend *leg30 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg30->SetBorderSize(1);
      leg30->SetFillColor(0);
      leg30->SetTextFont(42);
      leg30->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg30->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg30->AddEntry(h30_1, "Quadratic Sum of significance from left");
      leg30->AddEntry(h30_2, "Quadratic Sum of significance from right");
      leg30->Draw();
      
      c30 -> SaveAs("MET_10p51.pdf");
    
    
    //   ===========================================================   METCent   ===========================================================
      
      TCanvas *c31 = new TCanvas ("c31", "METCent",980,580);
        
      TPad *pad311 = new TPad("pad311","",0,0,0.75,1);
      TPad *pad312 = new TPad("pad312","",0.73,0,1,1);
      pad311->Draw();
      pad312->Draw();
        
      pad311->cd();
      pad311->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",48,-1.5,1.5);
        h_hist[i]->GetXaxis()->SetTitle("MET #phi centrality");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.0625");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 7000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="METCent>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h31_1 = new TH1F("h31_1","Quadratic Sum from left",48,-1.5,1.5); //left
      
          double QuadraticSum_l_31 = 0;
          double R_l_31 = 0;
          double E_l_31 = 0;
          double EE_l_31 = 0;

          for (int j=1; j<=48; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_31 +=  2* ( (S + B) * LSB - S );
                  E_l_31 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_31 = sqrt(R_l_31);
              if(R_l_31 > 0) { EE_l_31 = sqrt(E_l_31) / QuadraticSum_l_31; }

              h31_1->SetBinContent(j,QuadraticSum_l_31);
              h31_1->SetLineColor(kBlue-9);
              h31_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h31_2 = new TH1F("h31_2","Quadratic Sum from right",48,-1.5,1.5); //right
      
          double QuadraticSum_r_31 = 0;
          double R_r_31 = 0;
          double E_r_31 = 0;
          double EE_r_31 = 0;

          for (int j=48; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_31 +=  2* ( (S + B) * LSB - S );
                  E_r_31 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_31 = sqrt(R_r_31);
              if(R_r_31 > 0) { EE_r_31 = sqrt(E_r_31) / QuadraticSum_r_31; }

              h31_2->SetBinContent(j,QuadraticSum_r_31);
              h31_2->SetLineColor(kGreen-9);
              h31_2->SetLineStyle(2);

          }
     
      
      
      float rightmax31 = 1.1*h31_1->GetMaximum();
      float scale31 = 7000 / rightmax31;
      h31_1->Scale(scale31);
      h31_1->Draw("SAMEHIST");
      
      h31_2->Scale(scale31);
      h31_2->Draw("SAMEHIST");
      
    
    TGaxis*axis31 = new TGaxis(1.5,0,1.5,7000,0,rightmax31,510,"+L");
      axis31->SetTitle("Quadratic Sum of significance");
      axis31->SetTitleSize(0.03);
      axis31->SetLabelSize(0.025);
      axis31->Draw();
      
      pad312->cd();
      TLegend *leg31 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg31->SetBorderSize(1);
      leg31->SetFillColor(0);
      leg31->SetTextFont(42);
      leg31->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg31->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg31->AddEntry(h31_1, "Quadratic Sum of significance from left");
      leg31->AddEntry(h31_2, "Quadratic Sum of significance from right");
      leg31->Draw();
      
      c31 -> SaveAs("METCent_10p51.pdf");
    
    
    //   ===========================================================   dPhiLep0MET   ===========================================================
      
      TCanvas *c32 = new TCanvas ("c32", "dPhiLep0MET",980,580);
        
      TPad *pad321 = new TPad("pad321","",0,0,0.75,1);
      TPad *pad322 = new TPad("pad322","",0.73,0,1,1);
      pad321->Draw();
      pad322->Draw();
        
      pad321->cd();
      pad321->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (#tau_{l},E_{T}^{miss})");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPhiLep0MET>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h32_1 = new TH1F("h32_1","Quadratic Sum from left",20,0,3.5); //left
      
          double QuadraticSum_l_32 = 0;
          double R_l_32 = 0;
          double E_l_32 = 0;
          double EE_l_32 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_32 +=  2* ( (S + B) * LSB - S );
                  E_l_32 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_32 = sqrt(R_l_32);
              if(R_l_32 > 0) { EE_l_32 = sqrt(E_l_32) / QuadraticSum_l_32; }

              h32_1->SetBinContent(j,QuadraticSum_l_32);
              h32_1->SetLineColor(kBlue-9);
              h32_1->SetLineStyle(2);

          }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h32_2 = new TH1F("h32_2","Quadratic Sum from right",20,0,3.5); //right
      
          double QuadraticSum_r_32 = 0;
          double R_r_32 = 0;
          double E_r_32 = 0;
          double EE_r_32 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_32 +=  2* ( (S + B) * LSB - S );
                  E_r_32 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_32 = sqrt(R_r_32);
              if(R_r_32 > 0) { EE_r_32 = sqrt(E_r_32) / QuadraticSum_r_32; }

              h32_2->SetBinContent(j,QuadraticSum_r_32);
              h32_2->SetLineColor(kGreen-9);
              h32_2->SetLineStyle(2);

          }
      
      float rightmax32 = 1.1*h32_1->GetMaximum();
      float scale32 = 3000 / rightmax32;
      h32_1->Scale(scale32);
      h32_1->Draw("SAMEHIST");
      
      h32_2->Scale(scale32);
      h32_2->Draw("SAMEHIST");
      
    
    TGaxis*axis32 = new TGaxis(3.5,0,3.5,3000,0,rightmax32,510,"+L");
      axis32->SetTitle("Quadratic Sum of significance");
      axis32->SetTitleSize(0.03);
      axis32->SetLabelSize(0.025);
      axis32->Draw();
      
      pad322->cd();
      TLegend *leg32 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg32->SetBorderSize(1);
      leg32->SetFillColor(0);
      leg32->SetTextFont(42);
      leg32->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg32->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg32->AddEntry(h32_1, "Quadratic Sum of significance from left");
      leg32->AddEntry(h32_2, "Quadratic Sum of significance from right");
      leg32->Draw();
      
      c32 -> SaveAs("dPhiLep0MET_10p51.pdf");
    
     
    //   ===========================================================   dPhiLep1MET   ===========================================================
      
      TCanvas *c33 = new TCanvas ("c33", "dPhiLep1MET",980,580);
        
      TPad *pad331 = new TPad("pad331","",0,0,0.75,1);
      TPad *pad332 = new TPad("pad332","",0.73,0,1,1);
      pad331->Draw();
      pad332->Draw();
        
      pad331->cd();
      pad331->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (#tau_{h},E_{T}^{miss})");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3500);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPhiLep1MET>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h33_1 = new TH1F("h33_1","Quadratic Sum from left",20,0,3.5); //left
      
          double QuadraticSum_l_33 = 0;
          double R_l_33 = 0;
          double E_l_33 = 0;
          double EE_l_33 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_33 +=  2* ( (S + B) * LSB - S );
                  E_l_33 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_33 = sqrt(R_l_33);
              if(R_l_33 > 0) { EE_l_33 = sqrt(E_l_33) / QuadraticSum_l_33; }

              h33_1->SetBinContent(j,QuadraticSum_l_33);
              h33_1->SetLineColor(kBlue-9);
              h33_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
     TH1F *h33_2 = new TH1F("h33_2","Quadratic Sum from right",20,0,3.5); //right
      
          double QuadraticSum_r_33 = 0;
          double R_r_33 = 0;
          double E_r_33 = 0;
          double EE_r_33 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_33 +=  2* ( (S + B) * LSB - S );
                  E_r_33 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_33 = sqrt(R_r_33);
              if(R_r_33 > 0) { EE_r_33 = sqrt(E_r_33) / QuadraticSum_r_33; }

              h33_2->SetBinContent(j,QuadraticSum_r_33);
              h33_2->SetLineColor(kGreen-9);
              h33_2->SetLineStyle(2);

          }
      
      float rightmax33 = 1.1*h33_1->GetMaximum();
      float scale33 = 3500 / rightmax33;
      h33_1->Scale(scale33);
      h33_1->Draw("SAMEHIST");
      
      h33_2->Scale(scale33);
      h33_2->Draw("SAMEHIST");
      
    
    TGaxis*axis33 = new TGaxis(3.5,0,3.5,3500,0,rightmax33,510,"+L");
      axis33->SetTitle("Quadratic Sum of significance");
      axis33->SetTitleSize(0.03);
      axis33->SetLabelSize(0.025);
      axis33->Draw();
      
      pad332->cd();
      TLegend *leg33 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg33->SetBorderSize(1);
      leg33->SetFillColor(0);
      leg33->SetTextFont(42);
      leg33->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg33->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg33->AddEntry(h33_1, "Quadratic Sum of significance from left");
      leg33->AddEntry(h33_2, "Quadratic Sum of significance from right");
      leg33->Draw();
      
      c33 -> SaveAs("dPhiLep1MET_10p51.pdf");
    
    
    //   ===========================================================   dPhiHttMET   ===========================================================
      
      TCanvas *c34 = new TCanvas ("c34", "dPhiHttMET",980,580);
        
      TPad *pad341 = new TPad("pad341","",0,0,0.75,1);
      TPad *pad342 = new TPad("pad342","",0.73,0,1,1);
      pad341->Draw();
      pad342->Draw();
        
      pad341->cd();
      pad341->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (H_{#tau#tau},E_{T}^{miss})");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPhiHttMET>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h34_1 = new TH1F("h34_1","Quadratic Sum from left",20,0,3.5); //left
      
          double QuadraticSum_l_34 = 0;
          double R_l_34 = 0;
          double E_l_34 = 0;
          double EE_l_34 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_34 +=  2* ( (S + B) * LSB - S );
                  E_l_34 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_34 = sqrt(R_l_34);
              if(R_l_34 > 0) { EE_l_34 = sqrt(E_l_34) / QuadraticSum_l_34; }

              h34_1->SetBinContent(j,QuadraticSum_l_34);
              h34_1->SetLineColor(kBlue-9);
              h34_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h34_2 = new TH1F("h34_2","Quadratic Sum from right",20,0,3.5); //right
      
          double QuadraticSum_r_34 = 0;
          double R_r_34 = 0;
          double E_r_34 = 0;
          double EE_r_34 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_34 +=  2* ( (S + B) * LSB - S );
                  E_r_34 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_34 = sqrt(R_r_34);
              if(R_r_34 > 0) { EE_r_34 = sqrt(E_r_34) / QuadraticSum_r_34; }

              h34_2->SetBinContent(j,QuadraticSum_r_34);
              h34_2->SetLineColor(kGreen-9);
              h34_2->SetLineStyle(2);

          }
      
      float rightmax34 = 1.1*h34_1->GetMaximum();
      float scale34 = 4000 / rightmax34;
      h34_1->Scale(scale34);
      h34_1->Draw("SAMEHIST");
      
      h34_2->Scale(scale34);
      h34_2->Draw("SAMEHIST");
      
    
    TGaxis*axis34 = new TGaxis(3.5,0,3.5,4000,0,rightmax34,510,"+L");
      axis34->SetTitle("Quadratic Sum of significance");
      axis34->SetTitleSize(0.03);
      axis34->SetLabelSize(0.025);
      axis34->Draw();
      
      pad342->cd();
      TLegend *leg34 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg34->SetBorderSize(1);
      leg34->SetFillColor(0);
      leg34->SetTextFont(42);
      leg34->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg34->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg34->AddEntry(h34_1, "Quadratic Sum of significance from left");
      leg34->AddEntry(h34_2, "Quadratic Sum of significance from right");
      leg34->Draw();
      
      c34 -> SaveAs("dPhiHttMET_10p51.pdf");
    
    
    //   ===========================================================   dPhiHbbMET   ===========================================================
      
      TCanvas *c35 = new TCanvas ("c35", "dPhiHbbMET",980,580);
        
      TPad *pad351 = new TPad("pad351","",0,0,0.75,1);
      TPad *pad352 = new TPad("pad352","",0.73,0,1,1);
      pad351->Draw();
      pad352->Draw();
        
      pad351->cd();
      pad351->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (H_{BB},E_{T}^{miss})");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4200);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPhiHbbMET>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h35_1 = new TH1F("h35_1","Quadratic Sum from left",20,0,3.5); //left
      
          double QuadraticSum_l_35 = 0;
          double R_l_35 = 0;
          double E_l_35 = 0;
          double EE_l_35 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_35 +=  2* ( (S + B) * LSB - S );
                  E_l_35 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_35 = sqrt(R_l_35);
              if(R_l_35 > 0) { EE_l_35 = sqrt(E_l_35) / QuadraticSum_l_35; }

              h35_1->SetBinContent(j,QuadraticSum_l_35);
              h35_1->SetLineColor(kBlue-9);
              h35_1->SetLineStyle(2);

          }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h35_2 = new TH1F("h35_2","Quadratic Sum from right",20,0,3.5); //right
      
          double QuadraticSum_r_35 = 0;
          double R_r_35 = 0;
          double E_r_35 = 0;
          double EE_r_35 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_35 +=  2* ( (S + B) * LSB - S );
                  E_r_35 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_35 = sqrt(R_r_35);
              if(R_r_35 > 0) { EE_r_35 = sqrt(E_r_35) / QuadraticSum_r_35; }

              h35_2->SetBinContent(j,QuadraticSum_r_35);
              h35_2->SetLineColor(kGreen-9);
              h35_2->SetLineStyle(2);

          }
      
      
      float rightmax35 = 1.1*h35_1->GetMaximum();
      float scale35 = 4200 / rightmax35;
      h35_1->Scale(scale35);
      h35_1->Draw("SAMEHIST");
      
      h35_2->Scale(scale35);
      h35_2->Draw("SAMEHIST");
      
    
    TGaxis*axis35 = new TGaxis(3.5,0,3.5,4200,0,rightmax35,510,"+L");
      axis35->SetTitle("Quadratic Sum of significance");
      axis35->SetTitleSize(0.03);
      axis35->SetLabelSize(0.025);
      axis35->Draw();
      
      pad352->cd();
      TLegend *leg35 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg35->SetBorderSize(1);
      leg35->SetFillColor(0);
      leg35->SetTextFont(42);
      leg35->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg35->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg35->AddEntry(h35_1, "Quadratic Sum of significance from left");
      leg35->AddEntry(h35_2, "Quadratic Sum of significance from right");
      leg35->Draw();
      
      c35 -> SaveAs("dPhiHbbMET_10p51.pdf");
    
      
    //   ===========================================================   Mhh   ===========================================================
      
      TCanvas *c36 = new TCanvas ("c36", "Mhh",980,580);
        
      TPad *pad361 = new TPad("pad361","",0,0,0.75,1);
      TPad *pad362 = new TPad("pad362","",0.73,0,1,1);
      pad361->Draw();
      pad362->Draw();
        
      pad361->cd();
      pad361->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetXaxis()->SetTitle("m_{hh} [GeV]");
          h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
          //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
      }
    
    h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
    h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM
      
      for (int i=0; i<n_smp; i++){ hist_draw[i]="Mhh*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
    
     //cout << " ============== significance From left ============== " << endl;
      
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

     //cout << " ============== significance From right ============== " << endl;
      
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
        
     }
      
      float rightmax36 = 1.1*h36_1->GetMaximum();
      float scale36 = 11000 / rightmax36;
      h36_1->Scale(scale36);
      h36_1->Draw("SAMEHIST");
      
      h36_2->Scale(scale36);
      h36_2->Draw("SAMEHIST");
      
    
      TGaxis*axis36 = new TGaxis(3500,0,3500,11000,0,rightmax36,510,"+L");
      axis36->SetTitle("Quadratic Sum of significance");
      axis36->SetTitleSize(0.03);
      axis36->SetLabelSize(0.025);
      axis36->Draw();
      
      pad362->cd();
      TLegend *leg36 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg36->SetBorderSize(1);
      leg36->SetFillColor(0);
      leg36->SetTextFont(42);
      leg36->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg36->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg36->AddEntry(h36_1, "Quadratic Sum of significance from left");
      leg36->AddEntry(h36_2, "Quadratic Sum of significance from right");
      leg36->Draw();
    
    //c36 -> SaveAs("Mhh_10p51.pdf");
      
       
    //   ===========================================================   HT   ===========================================================
      
      TCanvas *c37 = new TCanvas ("c37", "HT",980,580);
        
      TPad *pad371 = new TPad("pad371","",0,0,0.75,1);
      TPad *pad372 = new TPad("pad372","",0.73,0,1,1);
      pad371->Draw();
      pad372->Draw();
        
      pad371->cd();
      pad371->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",88,0,4400);
          h_hist[i]->GetXaxis()->SetTitle("HT [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 6000);
      }
    
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="HT*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h37_1 = new TH1F("h37_1","Quadratic Sum from left",88,0,4400); //left
      
          double QuadraticSum_l_37 = 0;
          double R_l_37 = 0;
          double E_l_37 = 0;
          double EE_l_37 = 0;

          for (int j=1; j<=88; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_37 +=  2* ( (S + B) * LSB - S );
                  E_l_37 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_37 = sqrt(R_l_37);
              if(R_l_37 > 0) { EE_l_37 = sqrt(E_l_37) / QuadraticSum_l_37; }

              h37_1->SetBinContent(j,QuadraticSum_l_37);
              h37_1->SetLineColor(kBlue-9);
              h37_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h37_2 = new TH1F("h37_2","Quadratic Sum from right",88,0,4400); //right
      
          double QuadraticSum_r_37 = 0;
          double R_r_37 = 0;
          double E_r_37 = 0;
          double EE_r_37 = 0;

          for (int j=88; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_37 +=  2* ( (S + B) * LSB - S );
                  E_r_37 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_37 = sqrt(R_r_37);
              if(R_r_37 > 0) { EE_r_37 = sqrt(E_r_37) / QuadraticSum_r_37; }

              h37_2->SetBinContent(j,QuadraticSum_r_37);
              h37_2->SetLineColor(kGreen-9);
              h37_2->SetLineStyle(2);

          }
      
      
      float rightmax37 = 1.1*h37_1->GetMaximum();
      float scale37 = 6000 / rightmax37;
      h37_1->Scale(scale37);
      h37_1->Draw("SAMEHIST");
      
      h37_2->Scale(scale37);
      h37_2->Draw("SAMEHIST");
      
    
    TGaxis*axis37 = new TGaxis(4400,0,4400,6000,0,rightmax37,510,"+L");
      axis37->SetTitle("Quadratic Sum of significance");
      axis37->SetTitleSize(0.03);
      axis37->SetLabelSize(0.025);
      axis37->Draw();
      
      pad372->cd();
      TLegend *leg37 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg37->SetBorderSize(1);
      leg37->SetFillColor(0);
      leg37->SetTextFont(42);
      leg37->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg37->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg37->AddEntry(h37_1, "Quadratic Sum of significance from left");
      leg37->AddEntry(h37_2, "Quadratic Sum of significance from right");
      leg37->Draw();
      
      c37 -> SaveAs("HT_10p51.pdf");
    
    
    //   ===========================================================   dPhiHBB   ===========================================================
      
      TCanvas *c38 = new TCanvas ("c38", "dPhiHBB",980,580);
        
      TPad *pad381 = new TPad("pad381","",0,0,0.75,1);
      TPad *pad382 = new TPad("pad382","",0.73,0,1,1);
      pad381->Draw();
      pad382->Draw();
        
      pad381->cd();
      pad381->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,0,3.5);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (H,BB)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPhiHBB>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h38_1 = new TH1F("h38_1","Quadratic Sum from left",20,0,3.5); //left
      
          double QuadraticSum_l_38 = 0;
          double R_l_38 = 0;
          double E_l_38 = 0;
          double EE_l_38 = 0;

          for (int j=1; j<=20; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_38 +=  2* ( (S + B) * LSB - S );
                  E_l_38 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_38 = sqrt(R_l_38);
              if(R_l_38 > 0) { EE_l_38 = sqrt(E_l_38) / QuadraticSum_l_38; }

              h38_1->SetBinContent(j,QuadraticSum_l_38);
              h38_1->SetLineColor(kBlue-9);
              h38_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h38_2 = new TH1F("h38_2","Quadratic Sum from right",20,0,3.5); //right
      
          double QuadraticSum_r_38 = 0;
          double R_r_38 = 0;
          double E_r_38 = 0;
          double EE_r_38 = 0;

          for (int j=20; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_38 +=  2* ( (S + B) * LSB - S );
                  E_r_38 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_38 = sqrt(R_r_38);
              if(R_r_38 > 0) { EE_r_38 = sqrt(E_r_38) / QuadraticSum_r_38; }

              h38_2->SetBinContent(j,QuadraticSum_r_38);
              h38_2->SetLineColor(kGreen-9);
              h38_2->SetLineStyle(2);

          }
      
      float rightmax38 = 1.1*h38_1->GetMaximum();
      float scale38 = 4000 / rightmax38;
      h38_1->Scale(scale38);
      h38_1->Draw("SAMEHIST");
      
      h38_2->Scale(scale38);
      h38_2->Draw("SAMEHIST");
      
    
    TGaxis*axis38 = new TGaxis(3.5,0,3.5,4000,0,rightmax38,510,"+L");
      axis38->SetTitle("Quadratic Sum of significance");
      axis38->SetTitleSize(0.03);
      axis38->SetLabelSize(0.025);
      axis38->Draw();
      
      pad382->cd();
      TLegend *leg38 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg38->SetBorderSize(1);
      leg38->SetFillColor(0);
      leg38->SetTextFont(42);
      leg38->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg38->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg38->AddEntry(h38_1, "Quadratic Sum of significance from left");
      leg38->AddEntry(h38_2, "Quadratic Sum of significance from right");
      leg38->Draw();
      
      c38 -> SaveAs("dPhiHBB_10p51.pdf");
    
    
    //   ===========================================================   dEtaHBB   ===========================================================
      
      TCanvas *c39 = new TCanvas ("c39", "dEtaHBB",980,580);
        
      TPad *pad391 = new TPad("pad391","",0,0,0.75,1);
      TPad *pad392 = new TPad("pad392","",0.73,0,1,1);
      pad391->Draw();
      pad392->Draw();
        
      pad391->cd();
      pad391->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",45,0,9);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (H,BB)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dEtaHBB>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h39_1 = new TH1F("h39_1","Quadratic Sum from left",45,0,9); //left
      
          double QuadraticSum_l_39 = 0;
          double R_l_39 = 0;
          double E_l_39 = 0;
          double EE_l_39 = 0;

          for (int j=1; j<=45; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_39 +=  2* ( (S + B) * LSB - S );
                  E_l_39 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_39 = sqrt(R_l_39);
              if(R_l_39 > 0) { EE_l_39 = sqrt(E_l_39) / QuadraticSum_l_39; }

              h39_1->SetBinContent(j,QuadraticSum_l_39);
              h39_1->SetLineColor(kBlue-9);
              h39_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h39_2 = new TH1F("h39_2","Quadratic Sum from right",45,0,9); //right
      
          double QuadraticSum_r_39 = 0;
          double R_r_39 = 0;
          double E_r_39 = 0;
          double EE_r_39 = 0;

          for (int j=45; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_39 +=  2* ( (S + B) * LSB - S );
                  E_r_39 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_39 = sqrt(R_r_39);
              if(R_r_39 > 0) { EE_r_39 = sqrt(E_r_39) / QuadraticSum_r_39; }

              h39_2->SetBinContent(j,QuadraticSum_r_39);
              h39_2->SetLineColor(kGreen-9);
              h39_2->SetLineStyle(2);

          }
     
      
      
      float rightmax39 = 1.1*h39_1->GetMaximum();
      float scale39 = 5000 / rightmax39;
      h39_1->Scale(scale39);
      h39_1->Draw("SAMEHIST");
      
      h39_2->Scale(scale39);
      h39_2->Draw("SAMEHIST");
      
    
    TGaxis*axis39 = new TGaxis(9,0,9,5000,0,rightmax39,510,"+L");
      axis39->SetTitle("Quadratic Sum of significance");
      axis39->SetTitleSize(0.03);
      axis39->SetLabelSize(0.025);
      axis39->Draw();
      
      pad392->cd();
      TLegend *leg39 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg39->SetBorderSize(1);
      leg39->SetFillColor(0);
      leg39->SetTextFont(42);
      leg39->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg39->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg39->AddEntry(h39_1, "Quadratic Sum of significance from left");
      leg39->AddEntry(h39_2, "Quadratic Sum of significance from right");
      leg39->Draw();
      
      c39 -> SaveAs("dEtaHBB_10p51.pdf");
    
     
    //   ===========================================================   dRHH   ===========================================================
      
      TCanvas *c40 = new TCanvas ("c40", "dRHH",980,580);
        
      TPad *pad401 = new TPad("pad401","",0,0,0.75,1);
      TPad *pad402 = new TPad("pad402","",0.73,0,1,1);
      pad401->Draw();
      pad402->Draw();
        
      pad401->cd();
      pad401->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",45,0,9);
          h_hist[i]->GetXaxis()->SetTitle("#DeltaR (H,H)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dRHH>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h40_1 = new TH1F("h40_1","Quadratic Sum from left",45,0,9); //left
      
          double QuadraticSum_l_40 = 0;
          double R_l_40 = 0;
          double E_l_40 = 0;
          double EE_l_40 = 0;

          for (int j=1; j<=45; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_40 +=  2* ( (S + B) * LSB - S );
                  E_l_40 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_40 = sqrt(R_l_40);
              if(R_l_40 > 0) { EE_l_40 = sqrt(E_l_40) / QuadraticSum_l_40; }

              h40_1->SetBinContent(j,QuadraticSum_l_40);
              h40_1->SetLineColor(kBlue-9);
              h40_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h40_2 = new TH1F("h40_2","Quadratic Sum from right",45,0,9); //right
      
          double QuadraticSum_r_40 = 0;
          double R_r_40 = 0;
          double E_r_40 = 0;
          double EE_r_40 = 0;

          for (int j=45; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_40 +=  2* ( (S + B) * LSB - S );
                  E_r_40 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_40 = sqrt(R_r_40);
              if(R_r_40 > 0) { EE_r_40 = sqrt(E_r_40) / QuadraticSum_r_40; }

              h40_2->SetBinContent(j,QuadraticSum_r_40);
              h40_2->SetLineColor(kGreen-9);
              h40_2->SetLineStyle(2);

          }
      
      
      float rightmax40 = 1.1*h40_1->GetMaximum();
      float scale40 = 5000 / rightmax40;
      h40_1->Scale(scale40);
      h40_1->Draw("SAMEHIST");
      
      h40_2->Scale(scale40);
      h40_2->Draw("SAMEHIST");
      
    
    TGaxis*axis40 = new TGaxis(9,0,9,5000,0,rightmax40,510,"+L");
      axis40->SetTitle("Quadratic Sum of significance");
      axis40->SetTitleSize(0.03);
      axis40->SetLabelSize(0.025);
      axis40->Draw();
      
      pad402->cd();
      TLegend *leg40 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg40->SetBorderSize(1);
      leg40->SetFillColor(0);
      leg40->SetTextFont(42);
      leg40->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg40->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg40->AddEntry(h40_1, "Quadratic Sum of significance from left");
      leg40->AddEntry(h40_2, "Quadratic Sum of significance from right");
      leg40->Draw();
      
      c40 -> SaveAs("dRHH_10p51.pdf");
    
    
    //   ===========================================================   MtW   ===========================================================
      
      TCanvas *c41 = new TCanvas ("c41", "MtW",980,580);
        
      TPad *pad411 = new TPad("pad411","",0,0,0.75,1);
      TPad *pad412 = new TPad("pad412","",0.73,0,1,1);
      pad411->Draw();
      pad412->Draw();
        
      pad411->cd();
      pad411->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",85,0,850);
          h_hist[i]->GetXaxis()->SetTitle("M_{T}^{w} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 10 GeV");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="MtW*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h41_1 = new TH1F("h41_1","Quadratic Sum from left",85,0,850); //left
      
          double QuadraticSum_l_41 = 0;
          double R_l_41 = 0;
          double E_l_41 = 0;
          double EE_l_41 = 0;

          for (int j=1; j<=85; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_41 +=  2* ( (S + B) * LSB - S );
                  E_l_41 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_41 = sqrt(R_l_41);
              if(R_l_41 > 0) { EE_l_41 = sqrt(E_l_41) / QuadraticSum_l_41; }

              h41_1->SetBinContent(j,QuadraticSum_l_41);
              h41_1->SetLineColor(kBlue-9);
              h41_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h41_2 = new TH1F("h41_2","Quadratic Sum from right",85,0,850); //right
      
          double QuadraticSum_r_41 = 0;
          double R_r_41 = 0;
          double E_r_41 = 0;
          double EE_r_41 = 0;

          for (int j=85; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_41 +=  2* ( (S + B) * LSB - S );
                  E_r_41 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_41 = sqrt(R_r_41);
              if(R_r_41 > 0) { EE_r_41 = sqrt(E_r_41) / QuadraticSum_r_41; }

              h41_2->SetBinContent(j,QuadraticSum_r_41);
              h41_2->SetLineColor(kGreen-9);
              h41_2->SetLineStyle(2);

          }
     
      
      
      float rightmax41 = 1.1*h41_1->GetMaximum();
      float scale41 = 4000 / rightmax41;
      h41_1->Scale(scale41);
      h41_1->Draw("SAMEHIST");
      
      h41_2->Scale(scale41);
      h41_2->Draw("SAMEHIST");
      
    
    TGaxis*axis41 = new TGaxis(850,0,850,4000,0,rightmax41,510,"+L");
      axis41->SetTitle("Quadratic Sum of significance");
      axis41->SetTitleSize(0.03);
      axis41->SetLabelSize(0.025);
      axis41->Draw();
      
      pad412->cd();
      TLegend *leg41 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg41->SetBorderSize(1);
      leg41->SetFillColor(0);
      leg41->SetTextFont(42);
      leg41->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg41->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg41->AddEntry(h41_1, "Quadratic Sum of significance from left");
      leg41->AddEntry(h41_2, "Quadratic Sum of significance from right");
      leg41->Draw();
      
      c41 -> SaveAs("MtW_10p51.pdf");
    
    
    //   ===========================================================   Mvis   ===========================================================
      
      TCanvas *c42 = new TCanvas ("c42", "Mvis",980,580);
        
      TPad *pad421 = new TPad("pad421","",0,0,0.75,1);
      TPad *pad422 = new TPad("pad422","",0.73,0,1,1);
      pad421->Draw();
      pad422->Draw();
        
      pad421->cd();
      pad421->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",100,0,2000);
          h_hist[i]->GetXaxis()->SetTitle("m_{vis} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 8000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="Mvis*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h42_1 = new TH1F("h42_1","Quadratic Sum from left",100,0,2000); //left
      
          double QuadraticSum_l_42 = 0;
          double R_l_42 = 0;
          double E_l_42 = 0;
          double EE_l_42 = 0;

          for (int j=1; j<=100; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_l_42 +=  2* ( (S + B) * LSB - S );
                  E_l_42 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_l_42 = sqrt(R_l_42);
              if(R_l_42 > 0) { EE_l_42 = sqrt(E_l_42) / QuadraticSum_l_42; }

              h42_1->SetBinContent(j,QuadraticSum_l_42);
              h42_1->SetLineColor(kBlue-9);
              h42_1->SetLineStyle(2);

          }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h42_2 = new TH1F("h42_2","Quadratic Sum from right",100,0,2000); //right
      
          double QuadraticSum_r_42 = 0;
          double R_r_42 = 0;
          double E_r_42 = 0;
          double EE_r_42 = 0;

          for (int j=100; j>=1; j--) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_42 +=  2* ( (S + B) * LSB - S );
                  E_r_42 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

              QuadraticSum_r_42 = sqrt(R_r_42);
              if(R_r_42 > 0) { EE_r_42 = sqrt(E_r_42) / QuadraticSum_r_42; }

              h42_2->SetBinContent(j,QuadraticSum_r_42);
              h42_2->SetLineColor(kGreen-9);
              h42_2->SetLineStyle(2);

          }
     
      
      
      float rightmax42 = 1.1*h42_1->GetMaximum();
      float scale42 = 8000 / rightmax42;
      h42_1->Scale(scale42);
      h42_1->Draw("SAMEHIST");
      
      h42_2->Scale(scale42);
      h42_2->Draw("SAMEHIST");
      
    
    TGaxis*axis42 = new TGaxis(2000,0,2000,8000,0,rightmax42,510,"+L");
      axis42->SetTitle("Quadratic Sum of significance");
      axis42->SetTitleSize(0.03);
      axis42->SetLabelSize(0.025);
      axis42->Draw();
      
      pad422->cd();
      TLegend *leg42 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg42->SetBorderSize(1);
      leg42->SetFillColor(0);
      leg42->SetTextFont(42);
      leg42->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg42->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg42->AddEntry(h42_1, "Quadratic Sum of significance from left");
      leg42->AddEntry(h42_2, "Quadratic Sum of significance from right");
      leg42->Draw();
      
      c42 -> SaveAs("Mvis_10p51.pdf");
     
    
    //   ===========================================================   Mw   ===========================================================
      
      TCanvas *c43 = new TCanvas ("c43", "Mw",980,580);
        
      TPad *pad431 = new TPad("pad431","",0,0,0.75,1);
      TPad *pad432 = new TPad("pad432","",0.73,0,1,1);
      pad431->Draw();
      pad432->Draw();
        
      pad431->cd();
      pad431->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",60,0,1200);
          h_hist[i]->GetXaxis()->SetTitle("m_{w} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 9000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="Mw*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h43_1 = new TH1F("h43_1","Quadratic Sum from left",60,0,1200); //left
      
          double QuadraticSum_l_43 = 0;
          double R_l_43 = 0;
          double E_l_43 = 0;
          double EE_l_43 = 0;

          for (int j=1; j<=60; j++) {

              double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

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
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h43_2 = new TH1F("h43_2","Quadratic Sum from right",60,0,1200); //right

             double QuadraticSum_r_43 = 0;
             double R_r_43 = 0;
             double E_r_43 = 0;
             double EE_r_43 = 0;

             for (int j=60; j>=1; j--) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

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
      axis43->SetTitle("Quadratic Sum of significance");
      axis43->SetTitleSize(0.03);
      axis43->SetLabelSize(0.025);
      axis43->Draw();
      
      pad432->cd();
      TLegend *leg43 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg43->SetBorderSize(1);
      leg43->SetFillColor(0);
      leg43->SetTextFont(42);
      leg43->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg43->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg43->AddEntry(h43_1, "Quadratic Sum of significance from left");
      leg43->AddEntry(h43_2, "Quadratic Sum of significance from right");
      leg43->Draw();
      
      c43 -> SaveAs("Mw_10p51.pdf");
    
     
    //   ===========================================================   Mt   ===========================================================
      
      TCanvas *c44 = new TCanvas ("c44", "Mt",980,580);
        
      TPad *pad441 = new TPad("pad441","",0,0,0.75,1);
      TPad *pad442 = new TPad("pad442","",0.73,0,1,1);
      pad441->Draw();
      pad442->Draw();
        
      pad441->cd();
      pad441->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",70,0,3500);
          h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 12000);
      }
    
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="Mt*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h44_1 = new TH1F("h44_1","Quadratic Sum from left",70,0,3500); //left
                
             double QuadraticSum_l_44 = 0;
             double R_l_44 = 0;
             double E_l_44 = 0;
             double EE_l_44 = 0;

             for (int j=1; j<=70; j++) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

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
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h44_2 = new TH1F("h44_2","Quadratic Sum from right",70,0,3500); //right

             double QuadraticSum_r_44 = 0;
             double R_r_44 = 0;
             double E_r_44 = 0;
             double EE_r_44 = 0;

             for (int j=70; j>=1; j--) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

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
      axis44->SetTitle("Quadratic Sum of significance");
      axis44->SetTitleSize(0.03);
      axis44->SetLabelSize(0.025);
      axis44->Draw();
      
      pad442->cd();
      TLegend *leg44 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg44->SetBorderSize(1);
      leg44->SetFillColor(0);
      leg44->SetTextFont(42);
      leg44->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg44->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg44->AddEntry(h44_1, "Quadratic Sum of significance from left");
      leg44->AddEntry(h44_2, "Quadratic Sum of significance from right");
      leg44->Draw();
      
      c44 -> SaveAs("Mt_10p51.pdf");
    
     
    //   ===========================================================   MtTotal   ===========================================================
      
      TCanvas *c45 = new TCanvas ("c45", "MtTotal",980,580);
        
      TPad *pad451 = new TPad("pad451","",0,0,0.75,1);
      TPad *pad452 = new TPad("pad452","",0.73,0,1,1);
      pad451->Draw();
      pad452->Draw();
        
      pad451->cd();
      pad451->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",75,0,1500);
          h_hist[i]->GetXaxis()->SetTitle("M_{T, total}^{w} [GeV]");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 7000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="MtTotal*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
       
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h45_1 = new TH1F("h45_1","Quadratic Sum from left",75,0,1500); //left
                
             double QuadraticSum_l_45 = 0;
             double R_l_45 = 0;
             double E_l_45 = 0;
             double EE_l_45 = 0;

             for (int j=1; j<=75; j++) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_l_45 +=  2* ( (S + B) * LSB - S );
                     E_l_45 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_l_45 = sqrt(R_l_45);
                 if(R_l_45 > 0) { EE_l_45 = sqrt(E_l_45) / QuadraticSum_l_45; }

                 h45_1->SetBinContent(j,QuadraticSum_l_45);
                 h45_1->SetLineColor(kBlue-9);
                 h45_1->SetLineStyle(2);

             }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h45_2 = new TH1F("h45_2","Quadratic Sum from right",75,0,1500); //right

             double QuadraticSum_r_45 = 0;
             double R_r_45 = 0;
             double E_r_45 = 0;
             double EE_r_45 = 0;

             for (int j=75; j>=1; j--) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_r_45 +=  2* ( (S + B) * LSB - S );
                     E_r_45 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_r_45 = sqrt(R_r_45);
                 if(R_r_45 > 0) { EE_r_45 = sqrt(E_r_45) / QuadraticSum_r_45; }

                 h45_2->SetBinContent(j,QuadraticSum_r_45);
                 h45_2->SetLineColor(kGreen-9);
                 h45_2->SetLineStyle(2);

             }
      
      float rightmax45 = 1.1*h45_1->GetMaximum();
      float scale45 = 7000 / rightmax45;
      h45_1->Scale(scale45);
      h45_1->Draw("SAMEHIST");
      
      h45_2->Scale(scale45);
      h45_2->Draw("SAMEHIST");
      
    
      TGaxis*axis45 = new TGaxis(1500,0,1500,7000,0,rightmax45,510,"+L");
      axis45->SetTitle("Quadratic Sum of significance");
      axis45->SetTitleSize(0.03);
      axis45->SetLabelSize(0.025);
      axis45->Draw();
      
      pad452->cd();
      TLegend *leg45 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg45->SetBorderSize(1);
      leg45->SetFillColor(0);
      leg45->SetTextFont(42);
      leg45->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg45->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg45->AddEntry(h45_1, "Quadratic Sum of significance from left");
      leg45->AddEntry(h45_2, "Quadratic Sum of significance from right");
      leg45->Draw();
      
      c45 -> SaveAs("MtTotal_10p51.pdf");
    
    
    //   ===========================================================   MtWLep1   ===========================================================
      
      TCanvas *c47 = new TCanvas ("c47", "MtWLep1",980,580);
        
      TPad *pad471 = new TPad("pad471","",0,0,0.75,1);
      TPad *pad472 = new TPad("pad472","",0.73,0,1,1);
      pad471->Draw();
      pad472->Draw();
        
      pad471->cd();
      pad471->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",100,0,2000);
          h_hist[i]->GetXaxis()->SetTitle("MtW_{Lep1}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="MtWLep1*0.001>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h47_1 = new TH1F("h47_1","Quadratic Sum from left",100,0,2000); //left
                
             double QuadraticSum_l_47 = 0;
             double R_l_47 = 0;
             double E_l_47 = 0;
             double EE_l_47 = 0;

             for (int j=1; j<=100; j++) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_l_47 +=  2* ( (S + B) * LSB - S );
                     E_l_47 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_l_47 = sqrt(R_l_47);
                 if(R_l_47 > 0) { EE_l_47 = sqrt(E_l_47) / QuadraticSum_l_47; }

                 h47_1->SetBinContent(j,QuadraticSum_l_47);
                 h47_1->SetLineColor(kBlue-9);
                 h47_1->SetLineStyle(2);

             }

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h47_2 = new TH1F("h47_2","Quadratic Sum from right",100,0,2000); //right

             double QuadraticSum_r_47 = 0;
             double R_r_47 = 0;
             double E_r_47 = 0;
             double EE_r_47 = 0;

             for (int j=100; j>=1; j--) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_r_47 +=  2* ( (S + B) * LSB - S );
                     E_r_47 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_r_47 = sqrt(R_r_47);
                 if(R_r_47 > 0) { EE_r_47 = sqrt(E_r_47) / QuadraticSum_r_47; }

                 h47_2->SetBinContent(j,QuadraticSum_r_47);
                 h47_2->SetLineColor(kGreen-9);
                 h47_2->SetLineStyle(2);

             }
      
      
      float rightmax47 = 1.1*h47_1->GetMaximum();
      float scale47 = 4000 / rightmax47;
      h47_1->Scale(scale47);
      h47_1->Draw("SAMEHIST");
      
      h47_2->Scale(scale47);
      h47_2->Draw("SAMEHIST");
      
    
      TGaxis*axis47 = new TGaxis(2000,0,2000,4000,0,rightmax47,510,"+L");
      axis47->SetTitle("Quadratic Sum of significance");
      axis47->SetTitleSize(0.03);
      axis47->SetLabelSize(0.025);
      axis47->Draw();
      
      pad472->cd();
      TLegend *leg47 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg47->SetBorderSize(1);
      leg47->SetFillColor(0);
      leg47->SetTextFont(42);
      leg47->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg47->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg47->AddEntry(h47_1, "Quadratic Sum of significance from left");
      leg47->AddEntry(h47_2, "Quadratic Sum of significance from right");
      leg47->Draw();
      
      c47 -> SaveAs("MtWLep1_10p51.pdf");
    
    
    //   ===========================================================   dPhiVBFjj   ===========================================================
      
      TCanvas *c48 = new TCanvas ("c48", "dPhiVBFjj",980,580);
        
      TPad *pad481 = new TPad("pad481","",0,0,0.75,1);
      TPad *pad482 = new TPad("pad482","",0.73,0,1,1);
      pad481->Draw();
      pad482->Draw();
        
      pad481->cd();
      pad481->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",35,0,7);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#phi VBFjj");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dPhiVBFjj>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
      
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      
     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h48_1 = new TH1F("h48_1","Quadratic Sum from left",35,0,7); //left
                
             double QuadraticSum_l_48 = 0;
             double R_l_48 = 0;
             double E_l_48 = 0;
             double EE_l_48 = 0;

             for (int j=1; j<=35; j++) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_l_48 +=  2* ( (S + B) * LSB - S );
                     E_l_48 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_l_48 = sqrt(R_l_48);
                 if(R_l_48 > 0) { EE_l_48 = sqrt(E_l_48) / QuadraticSum_l_48; }

                 h48_1->SetBinContent(j,QuadraticSum_l_48);
                 h48_1->SetLineColor(kBlue-9);
                 h48_1->SetLineStyle(2);

             }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h48_2 = new TH1F("h48_2","Quadratic Sum from right",35,0,7); //right

             double QuadraticSum_r_48 = 0;
             double R_r_48 = 0;
             double E_r_48 = 0;
             double EE_r_48 = 0;

             for (int j=35; j>=1; j--) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_r_48 +=  2* ( (S + B) * LSB - S );
                     E_r_48 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_r_48 = sqrt(R_r_48);
                 if(R_r_48 > 0) { EE_r_48 = sqrt(E_r_48) / QuadraticSum_r_48; }

                 h48_2->SetBinContent(j,QuadraticSum_r_48);
                 h48_2->SetLineColor(kGreen-9);
                 h48_2->SetLineStyle(2);

             }
      
      
      float rightmax48 = 1.1*h48_1->GetMaximum();
      float scale48 = 2000 / rightmax48;
      h48_1->Scale(scale48);
      h48_1->Draw("SAMEHIST");
      
      h48_2->Scale(scale48);
      h48_2->Draw("SAMEHIST");
      
    
      TGaxis*axis48 = new TGaxis(7,0,7,2000,0,rightmax48,510,"+L");
      axis48->SetTitle("Quadratic Sum of significance");
      axis48->SetTitleSize(0.03);
      axis48->SetLabelSize(0.025);
      axis48->Draw();
      
      pad482->cd();
      TLegend *leg48 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg48->SetBorderSize(1);
      leg48->SetFillColor(0);
      leg48->SetTextFont(42);
      leg48->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg48->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg48->AddEntry(h48_1, "Quadratic Sum of significance from left");
      leg48->AddEntry(h48_2, "Quadratic Sum of significance from right");
      leg48->Draw();
      
      c48 -> SaveAs("dPhiVBFjj_10p51.pdf");
    
    
    //   ===========================================================   dEtaHH   ===========================================================
      
      TCanvas *c49 = new TCanvas ("c49", "dEtaHH",980,580);
        
      TPad *pad491 = new TPad("pad491","",0,0,0.75,1);
      TPad *pad492 = new TPad("pad492","",0.73,0,1,1);
      pad491->Draw();
      pad492->Draw();
        
      pad491->cd();
      pad491->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",45,0,9);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (H,H)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 5000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="dEtaHH>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h49_1 = new TH1F("h49_1","Quadratic Sum from left",45,0,9); //left
                
             double QuadraticSum_l_49 = 0;
             double R_l_49 = 0;
             double E_l_49 = 0;
             double EE_l_49 = 0;

             for (int j=1; j<=45; j++) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_l_49 +=  2* ( (S + B) * LSB - S );
                     E_l_49 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_l_49 = sqrt(R_l_49);
                 if(R_l_49 > 0) { EE_l_49 = sqrt(E_l_49) / QuadraticSum_l_49; }

                 h49_1->SetBinContent(j,QuadraticSum_l_49);
                 h49_1->SetLineColor(kBlue-9);
                 h49_1->SetLineStyle(2);

             }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h49_2 = new TH1F("h49_2","Quadratic Sum from right",45,0,9); //right

             double QuadraticSum_r_49 = 0;
             double R_r_49 = 0;
             double E_r_49 = 0;
             double EE_r_49 = 0;

             for (int j=45; j>=1; j--) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_r_49 +=  2* ( (S + B) * LSB - S );
                     E_r_49 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_r_49 = sqrt(R_r_49);
                 if(R_r_49 > 0) { EE_r_49 = sqrt(E_r_49) / QuadraticSum_r_49; }

                 h49_2->SetBinContent(j,QuadraticSum_r_49);
                 h49_2->SetLineColor(kGreen-9);
                 h49_2->SetLineStyle(2);

             }
      
      
      float rightmax49 = 1.1*h49_1->GetMaximum();
      float scale49 = 5000 / rightmax49;
      h49_1->Scale(scale49);
      h49_1->Draw("SAMEHIST");
      
      h49_2->Scale(scale49);
      h49_2->Draw("SAMEHIST");
      
    
      TGaxis*axis49 = new TGaxis(9,0,9,5000,0,rightmax49,510,"+L");
      axis49->SetTitle("Quadratic Sum of significance");
      axis49->SetTitleSize(0.03);
      axis49->SetLabelSize(0.025);
      axis49->Draw();
      
      pad492->cd();
      TLegend *leg49 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg49->SetBorderSize(1);
      leg49->SetFillColor(0);
      leg49->SetTextFont(42);
      leg49->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg49->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg49->AddEntry(h49_1, "Quadratic Sum of significance from left");
      leg49->AddEntry(h49_2, "Quadratic Sum of significance from right");
      leg49->Draw();
      
      c49 -> SaveAs("dEtaHH_10p51.pdf");
      
      
    //   ===========================================================   Xwt   ===========================================================
      
      TCanvas *c50 = new TCanvas ("c50", "Xwt",980,580);
        
      TPad *pad501 = new TPad("pad501","",0,0,0.75,1);
      TPad *pad502 = new TPad("pad502","",0.73,0,1,1);
      pad501->Draw();
      pad502->Draw();
        
      pad501->cd();
      pad501->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,6);
          h_hist[i]->GetXaxis()->SetTitle("Xwt");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.15");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 6000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h50_1 = new TH1F("h50_1","Quadratic Sum from left",40,0,6); //left
                
             double QuadraticSum_l_50 = 0;
             double R_l_50 = 0;
             double E_l_50 = 0;
             double EE_l_50 = 0;

             for (int j=1; j<=40; j++) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_l_50 +=  2* ( (S + B) * LSB - S );
                     E_l_50 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_l_50 = sqrt(R_l_50);
                 if(R_l_50 > 0) { EE_l_50 = sqrt(E_l_50) / QuadraticSum_l_50; }

                 h50_1->SetBinContent(j,QuadraticSum_l_50);
                 h50_1->SetLineColor(kBlue-9);
                 h50_1->SetLineStyle(2);

             }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h50_2 = new TH1F("h50_2","Quadratic Sum from right",40,0,6); //right

             double QuadraticSum_r_50 = 0;
             double R_r_50 = 0;
             double E_r_50 = 0;
             double EE_r_50 = 0;

             for (int j=40; j>=1; j--) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_r_50 +=  2* ( (S + B) * LSB - S );
                     E_r_50 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_r_50 = sqrt(R_r_50);
                 if(R_r_50 > 0) { EE_r_50 = sqrt(E_r_50) / QuadraticSum_r_50; }

                 h50_2->SetBinContent(j,QuadraticSum_r_50);
                 h50_2->SetLineColor(kGreen-9);
                 h50_2->SetLineStyle(2);

             }
      
      
      float rightmax50 = 1.1*h50_1->GetMaximum();
      float scale50 = 6000 / rightmax50;
      h50_1->Scale(scale50);
      h50_1->Draw("SAMEHIST");
      
      h50_2->Scale(scale50);
      h50_2->Draw("SAMEHIST");
      
    
      TGaxis*axis50 = new TGaxis(6,0,6,6000,0,rightmax50,510,"+L");
      axis50->SetTitle("Quadratic Sum of significance");
      axis50->SetTitleSize(0.03);
      axis50->SetLabelSize(0.025);
      axis50->Draw();
      
      pad502->cd();
      TLegend *leg50 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg50->SetBorderSize(1);
      leg50->SetFillColor(0);
      leg50->SetTextFont(42);
      leg50->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg50->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg50->AddEntry(h50_1, "Quadratic Sum of significance from left");
      leg50->AddEntry(h50_2, "Quadratic Sum of significance from right");
      leg50->Draw();
      
      c50 -> SaveAs("Xwt_10p51.pdf");
     
     
      
    //   ===========================================================   Xhh   ===========================================================
      
      TCanvas *c51 = new TCanvas ("c51", "X_HH",980,580);
        
      TPad *pad511 = new TPad("pad511","",0,0,0.75,1);
      TPad *pad512 = new TPad("pad512","",0.73,0,1,1);
      pad511->Draw();
      pad512->Draw();
        
      pad511->cd();
      pad511->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,4.48);
          h_hist[i]->GetXaxis()->SetTitle("X_{HH}");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.112");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 14000);
      }
      
      h_hist[0]->SetLineColor(kOrange); h_hist[0]->SetMarkerColor(kOrange); h_hist[0]->SetFillColor(kOrange); //ttbar
      h_hist[1]->SetLineColor(kRed); h_hist[1]->SetMarkerColor(kRed); //VBF_SM

    
      for (int i=0; i<n_smp; i++){ hist_draw[i]="sqrt( ((mMMC*0.001-125)/(mMMC*0.001)) * ((mMMC*0.001-125)/(mMMC*0.001)) + ((mBB*0.001-125)/(mBB*0.001)) * ((mBB*0.001-125)/(mBB*0.001)) )>>"+h_title[i]; }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 0){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //ttbar
        else if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
        
      }
    
    for(int i = 0; i<n_smp; i++){
        if(i == 1){chain_smp[i]->Draw(hist_draw[i].c_str(), "19889.81*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF10p51
    }
      

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h51_1 = new TH1F("h51_1","Quadratic Sum from left",40,0,4.48); //left
                
             double QuadraticSum_l_51 = 0;
             double R_l_51 = 0;
             double E_l_51 = 0;
             double EE_l_51 = 0;

             for (int j=1; j<=40; j++) {

                 double S = h_hist[1]->GetBinContent(j);
                 double dS = h_hist[1]->GetBinError(j);
                 double B = h_hist[0]->GetBinContent(j);
                 double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_l_51 +=  2* ( (S + B) * LSB - S );
                     E_l_51 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_l_51 = sqrt(R_l_51);
                 if(R_l_51 > 0) { EE_l_51 = sqrt(E_l_51) / QuadraticSum_l_51; }

                 h51_1->SetBinContent(j,QuadraticSum_l_51);
                 h51_1->SetLineColor(kBlue-9);
                 h51_1->SetLineStyle(2);

             }
          
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
          TH1F *h51_2 = new TH1F("h51_2","Quadratic Sum from right",40,0,4.48); //right

             double QuadraticSum_r_51 = 0;
             double R_r_51 = 0;
             double E_r_51 = 0;
             double EE_r_51 = 0;

             for (int j=40; j>=1; j--) {

                 double S = h_hist[1]->GetBinContent(j);
        double dS = h_hist[1]->GetBinError(j);
        double B = h_hist[0]->GetBinContent(j);
        double dB = h_hist[0]->GetBinError(j);

                 if( B > 0 && S > 0) {
                     double LSB = log(1+S/B);
                     R_r_51 +=  2* ( (S + B) * LSB - S );
                     E_r_51 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
                 }

                 QuadraticSum_r_51 = sqrt(R_r_51);
                 if(R_r_51 > 0) { EE_r_51 = sqrt(E_r_51) / QuadraticSum_r_51; }

                 h51_2->SetBinContent(j,QuadraticSum_r_51);
                 h51_2->SetLineColor(kGreen-9);
                 h51_2->SetLineStyle(2);

             }
      
      
      float rightmax51 = 1.1*h51_1->GetMaximum();
      float scale51 = 14000 / rightmax51;
      h51_1->Scale(scale51);
      h51_1->Draw("SAMEHIST");
      
      h51_2->Scale(scale51);
      h51_2->Draw("SAMEHIST");
      
    
      TGaxis*axis51 = new TGaxis(4.48,0,4.48,14000,0,rightmax51,510,"+L");
      axis51->SetTitle("Quadratic Sum of significance");
      axis51->SetTitleSize(0.03);
      axis51->SetLabelSize(0.025);
      axis51->Draw();
      
      pad512->cd();
      TLegend *leg51 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg51->SetBorderSize(1);
      leg51->SetFillColor(0);
      leg51->SetTextFont(42);
      leg51->SetTextSize(0.053);
      
      for(int i= 1; i>=0 ; i--){ leg51->AddEntry(h_hist[i], h_titles[i].c_str()); }
      leg51->AddEntry(h51_1, "Quadratic Sum of significance from left");
      leg51->AddEntry(h51_2, "Quadratic Sum of significance from right");
      leg51->Draw();
      
      c51 -> SaveAs("X_HH_10p51.pdf");
       
    
     
    // =================  Significance of each variable  =================
   
    cout << " pTBB : " <<" S = " << QuadraticSum_r_1 << " E = " << EE_r_1 << endl;
    cout << " pTB1 : " <<" S = " << QuadraticSum_r_2 << " E = " << EE_r_2 << endl;
    cout << " pTB2 : " <<" S = " << QuadraticSum_r_3 << " E = " << EE_r_3 << endl;
    
    cout << " " << endl;
    
    cout << " mBB : " <<" S = " << QuadraticSum_r_4 << " E = " << EE_r_4 << endl;
    cout << " dPhiBB : " <<" S = " << QuadraticSum_r_5 << " E = " << EE_r_5 << endl;
    cout << " dEtaBB : " <<" S = " << QuadraticSum_r_6 << " E = " << EE_r_6 << endl;
    cout << " dRBB : " <<" S = " << QuadraticSum_r_7 << " E = " << EE_r_7 << endl;
    
    cout << " " << endl;
    
    cout << " pTtautau : " <<" S = " << QuadraticSum_r_8 << " E = " << EE_r_8 << endl;
    cout << " dPtLepTau : " <<" S = " << QuadraticSum_r_19 << " E = " << EE_r_19 << endl;
    cout << " TauPt : " <<" S = " << QuadraticSum_r_9 << " E = " << EE_r_9 << endl;
    cout << " LepPt : " <<" S = " << QuadraticSum_r_10 << " E = " << EE_r_10 << endl;
    cout << " mMMC : " <<" S = " << QuadraticSum_r_11 << " E = " << EE_r_11 << endl;
    
    cout << " " << endl;

    cout << " dPhiLepTau : " <<" S = " << QuadraticSum_r_12 << " E = " << EE_r_12 << endl;
    cout << " TauPhi : " <<" S = " << QuadraticSum_r_13 << " E = " << EE_r_13 << endl;
    cout << " LepPhi : " <<" S = " << QuadraticSum_r_14 << " E = " << EE_r_14 << endl;
    
    cout << " " << endl;
    
    cout << " dEtaLepTau : " <<" S = " << QuadraticSum_r_15 << " E = " << EE_r_15 << endl;
    cout << " TauEta : " <<" S = " << QuadraticSum_r_16 << " E = " << EE_r_16 << endl;
    cout << " LepEta : " <<" S = " << QuadraticSum_r_17 << " E = " << EE_r_17 << endl;
    cout << " dRLepTau : " <<" S = " << QuadraticSum_r_18 << " E = " << EE_r_18 << endl;
    
    cout << " " << endl;

    cout << " MT2 : " <<" S = " << QuadraticSum_r_20 << " E = " << EE_r_20 << endl;
    
    cout << " pTVBFj1 : " <<" S = " << QuadraticSum_r_21 << " E = " << EE_r_21 << endl;
    cout << " pTVBFj2 : " <<" S = " << QuadraticSum_r_22 << " E = " << EE_r_22 << endl;
    cout << " mVBFjj : " <<" S = " << QuadraticSum_r_23 << " E = " << EE_r_23 << endl;
    
    cout << " " << endl;
    
    cout << " phiVBFj1 : " <<" S = " << QuadraticSum_r_24 << " E = " << EE_r_24 << endl;
    cout << " phiVBFj2 : " <<" S = " << QuadraticSum_r_25 << " E = " << EE_r_25 << endl;
    cout << " dPhiVBFjj : " <<" S = " << QuadraticSum_r_48 << " E = " << EE_r_48 << endl;
    
    cout << " " << endl;

    cout << " etaVBFj1 : " <<" S = " << QuadraticSum_r_27 << " E = " << EE_r_27 << endl;
    cout << " etaVBFj2 : " <<" S = " << QuadraticSum_r_28 << " E = " << EE_r_28 << endl;
    cout << " dEtaVBFjj : " <<" S = " << QuadraticSum_r_26 << " E = " << EE_r_26 << endl;
    
    cout << " dRVBFjj : " <<" S = " << QuadraticSum_r_29 << " E = " << EE_r_29 << endl;
    
    cout << " " << endl;
    
    cout << " MET : " <<" S = " << QuadraticSum_r_30 << " E = " << EE_r_30 << endl;
    cout << " METCent : " <<" S = " << QuadraticSum_r_31 << " E = " << EE_r_31 << endl;
    cout << " dPhiLep0MET : " <<" S = " << QuadraticSum_r_32 << " E = " << EE_r_32 << endl;
    cout << " dPhiLep1MET : " <<" S = " << QuadraticSum_r_33 << " E = " << EE_r_33 << endl;
    cout << " dPhiHttMET : " <<" S = " << QuadraticSum_r_34 << " E = " << EE_r_34 << endl;
    cout << " dPhiHbbMET : " <<" S = " << QuadraticSum_r_35 << " E = " << EE_r_35 << endl;
    
    cout << " " << endl;
     
    cout << " Mhh : " <<" S = " << QuadraticSum_r_36 << " E = " << EE_r_36 << endl;
    cout << " HT : " <<" S = " << QuadraticSum_r_37 << " E = " << EE_r_37 << endl;
    cout << " dPhiHBB : " <<" S = " << QuadraticSum_r_38 << " E = " << EE_r_38 << endl;
    cout << " dEtaHBB : " <<" S = " << QuadraticSum_r_39 << " E = " << EE_r_39 << endl;
    cout << " dEtaHH : " <<" S = " << QuadraticSum_r_49 << " E = " << EE_r_49 << endl;
    cout << " dRHH : " <<" S = " << QuadraticSum_r_40 << " E = " << EE_r_40 << endl;
    
    cout << " " << endl;
    
    cout << " MtW : " <<" S = " << QuadraticSum_r_41 << " E = " << EE_r_41 << endl;
    cout << " MtWLep1 : " <<" S = " << QuadraticSum_r_47 << " E = " << EE_r_47 << endl;
    cout << " MtTotal : " <<" S = " << QuadraticSum_r_45 << " E = " << EE_r_45 << endl;
    cout << " Mvis : " <<" S = " << QuadraticSum_r_42 << " E = " << EE_r_42 << endl;
    cout << " Mw : " <<" S = " << QuadraticSum_r_43 << " E = " << EE_r_43 << endl;
    cout << " Mt : " <<" S = " << QuadraticSum_r_44 << " E = " << EE_r_44 << endl;
    
    cout << " Xwt : " <<" S = " << QuadraticSum_r_50 << " E = " << EE_r_50 << endl;
    cout << " Xhh : " <<" S = " << QuadraticSum_r_51 << " E = " << EE_r_51 << endl;
     
     //  ----------------------------- ps file -----------------------------
     
       
     TPostScript *ps = new TPostScript("S_sqrt(B)_ttbar.ps",112);

    ps->NewPage();
    c1->Draw();
    ps->NewPage();
    c2->Draw();
    ps->NewPage();
    c3->Draw();
    ps->NewPage();
    c4->Draw();
    ps->NewPage();
    c5->Draw();
    ps->NewPage();
    c6->Draw();
    ps->NewPage();
    c7->Draw();
    ps->NewPage();
    c8->Draw();
    ps->NewPage();
    c19->Draw();
    ps->NewPage();
    c9->Draw();
    ps->NewPage();
    c10->Draw();
    ps->NewPage();
    c11->Draw();
    ps->NewPage();
    c12->Draw();
    ps->NewPage();
    c13->Draw();
    ps->NewPage();
    c14->Draw();
    ps->NewPage();
    c15->Draw();
    ps->NewPage();
    c16->Draw();
    ps->NewPage();
    c17->Draw();
    ps->NewPage();
    c18->Draw();
    ps->NewPage();
    c20->Draw();
    ps->NewPage();
    c21->Draw();
    ps->NewPage();
    c22->Draw();
    ps->NewPage();
    c23->Draw();
    ps->NewPage();
    c24->Draw();
    ps->NewPage();
    c25->Draw();
    ps->NewPage();
    c48->Draw();
    ps->NewPage();
    c27->Draw();
    ps->NewPage();
    c28->Draw();
    ps->NewPage();
    c26->Draw();
    ps->NewPage();
    c29->Draw();
    ps->NewPage();
    c30->Draw();
    ps->NewPage();
    c31->Draw();
    ps->NewPage();
    c32->Draw();
    ps->NewPage();
    c33->Draw();
    ps->NewPage();
    c34->Draw();
    ps->NewPage();
    c35->Draw();
    ps->NewPage();
    c36->Draw();
    ps->NewPage();
    c37->Draw();
    ps->NewPage();
    c38->Draw();
    ps->NewPage();
    c39->Draw();
    ps->NewPage();
    c49->Draw();
    ps->NewPage();
    c40->Draw();
    ps->NewPage();
    c41->Draw();
    ps->NewPage();
    c47->Draw();
    ps->NewPage();
    c45->Draw();
    ps->NewPage();
    c42->Draw();
    ps->NewPage();
    c43->Draw();
    ps->NewPage();
    c44->Draw();
    ps->NewPage();
    c50->Draw();
    ps->NewPage();
    c51->Draw();
      
    // =====================================================================================================================
        /*
    int entries;
    int entries_VBF10p51;
    float yields;
    float yields_VBF10p51;
    int sum_entries;
    int sum_entries_noVBF10p51;
    float sum_yields_noVBF10p51;
    float sum_yields;
      
    ofstream myfile;
    myfile.open ("Yields_SM_Only_ttbar.txt");
    myfile <<"---------------------------------------------------"<<endl;
    myfile <<"                                                                                    "<<endl;
    myfile <<"        Sample          Entries         Yields             "<<endl;
    myfile <<"                                                                                    "<<endl;
    

     entries_VBF10p51 = h_hist[1]->GetEntries();
     yields_VBF10p51 = h_hist[1]->Integral() / 19889.81; // multiply this factor on VBF10p51 (plot)
     myfile<<"\t" <<h_title[1] <<"\t \t"<<entries_VBF10p51<<"\t \t"<<yields_VBF10p51<<endl;
     myfile <<"                                                                                   "<<endl;
      
     entries = h_hist[0]->GetEntries();
     yields =  h_hist[0]->Integral();
     myfile<<"\t" <<h_title[0] <<"\t \t"<<entries<<"\t \t"<<yields<<endl;
     myfile <<"                                                                                   "<<endl;
      
    myfile <<"                                                                                   "<<endl;
    myfile <<"---------------------------------------------------"<<endl;
    myfile.close();
        */
            
  }

