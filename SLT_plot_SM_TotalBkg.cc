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

void SLT_plot_SM_TotalBkg(){

  //const int n_smp = 12;
  const int n_smp = 11;
  //string smp_tree[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM", "data" };
  string smp_tree[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "FullRun2_AddRNN/";
  //string pwd = "SLT_job_SR_data18/Ntuple/"; // path to input files
  string ana_tag = "FinalNtuple.TauLH.";
  //string smp_names[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Zll", "W", "Ztautau", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1.", "data_13TeV" };
  string smp_names[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Zll", "W", "Ztautau", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
    
  for (int i=0; i<n_smp; i++)
    {
      smp = pwd + ana_tag + smp_names[i] +".0.root";
      cout<<smp<<endl;
      chain_smp[i] = new TChain(smp_tree[i].c_str());
      chain_smp[i]->Add(smp.c_str());
    }
  
  //string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake_ttbar", "Fake_W", "Zee/#mu#mu", "W", "Z#tau#tau", "single top", "ttbar", "VBFSM x 248633.79", "data" };  // only for legend
  string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake_ttbar", "Fake_W", "Zee/#mu#mu", "W", "Z#tau#tau", "single top", "ttbar", "VBFSM x 248633.79" };  // only for legend
    
  //string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake_ttbar", "Fake_W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM", "data" };
  string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake_ttbar", "Fake_W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM" };
    
  TH1::SetDefaultSumw2();
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];
      
       /*
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
          h_hist[i] = new TH1F(h_nm, "",42,0,840);
          h_hist[i]->GetXaxis()->SetTitle("p_{T}^{BB} [GeV]");
          h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
          //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
          h_hist[i]->GetYaxis()->SetRangeUser(0, 6500); //3200
        }
        
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);
      
      
        for (int i=0; i<n_smp; i++){
            hist_draw[i]="pTBB*0.001>>"+h_title[i];
        }
        
        for(int i = 0; i<n_smp; i++){
          
          if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
          
        }
        
        THStack *hs1 = new THStack("hs1", "");
        for(int i= 0; i<10 ; i++){ hs1->Add(h_hist[i], "hist1"); }
        hs1->Draw("SAMEHIST");
      
        for(int i = 0; i<n_smp; i++){
            if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
        }
    
        // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

       //cout << " ============== significance From left ============== " << endl;
       //cout << " " << endl;
        
       TH1F *h1_1 = new TH1F("h1_1","Quadratic Sum from left",42,0,840); //left
        
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
         float B_l_1_9 = 0;
    
         float error_l_1_0 = 0;
         float error_l_1_1 = 0;
         float error_l_1_2 = 0;
         float error_l_1_3 = 0;
         float error_l_1_4 = 0;
         float error_l_1_5 = 0;
         float error_l_1_6 = 0;
         float error_l_1_7 = 0;
         float error_l_1_8 = 0;
         float error_l_1_9 = 0;
          
         float QuadraticSum_l_1 = 0;
         float Sum_l_1 = 0;
         float QuadraticSum_dB_l_1 = 0;
         float Sum_dB_l_1 = 0;
           
          for (int j=1; j<=42; j++) {
              
             S_l_1 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_1 << endl;
             B_l_1_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_1_9 << endl;
             B_l_1_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_1_8 << endl;
             B_l_1_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_1_7 << endl;
             B_l_1_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_1_6 << endl;
             B_l_1_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_1_5 << endl;
             B_l_1_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_1_4 << endl;
             B_l_1_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_1_3 << endl;
             B_l_1_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_1_2 << endl;
             B_l_1_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_1_1 << endl;
             B_l_1_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_1_0 << endl;
              
             error_l_1_9 = h_hist[9]->GetBinError(j);
             //cout << " error of ttbar of each bin = " << error_l_1_9 << endl;
             error_l_1_8 = h_hist[8]->GetBinError(j);
             //cout << " error of single top of each bin = " << error_l_1_8 << endl;
             error_l_1_7 = h_hist[7]->GetBinError(j);
             //cout << " error of Ztt of each bin = " << error_l_1_7 << endl;
             error_l_1_6 = h_hist[6]->GetBinError(j);
             //cout << " error of Wlv of each bin = " << error_l_1_6 << endl;
             error_l_1_5 = h_hist[5]->GetBinError(j);
             //cout << " error of Z of each bin = " << error_l_1_5 << endl;
             error_l_1_4 = h_hist[4]->GetBinError(j);
             //cout << " error of Fake_W of each bin = " << error_l_1_4 << endl;
             error_l_1_3 = h_hist[3]->GetBinError(j);
             //cout << " error of Fake_ttbar of each bin = " << error_l_1_3 << endl;
             error_l_1_2 = h_hist[2]->GetBinError(j);
             //cout << " error of DY of each bin = " << error_l_1_2 << endl;
             error_l_1_1 = h_hist[1]->GetBinError(j);
             //cout << " error of diboson of each bin = " << error_l_1_1 << endl;
             error_l_1_0 = h_hist[0]->GetBinError(j);
             //cout << " error of SMH of each bin = " << error_l_1_0 << endl;
             
             float B_l_1 = 0;
             for(int i = 0; i<10; i++) { B_l_1 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_1 << endl;
             
             float dB_l_1 = 0;
             for(int i = 0; i<10; i++) { dB_l_1 += h_hist[i]->GetBinError(j); }
             //cout << " Error of each bin = " << dB_l_1 << endl;
             
              if( B_l_1 > 0 && S_l_1 > 0) {
                  
                   double T_l_1 = S_l_1 + B_l_1 ;
                   double bE_l_1 = B_l_1 + ( dB_l_1 * dB_l_1 ) ;
                   double L1a_l_1 = T_l_1 * bE_l_1 ;
                   double L1b_l_1 = ( B_l_1 * B_l_1 ) + ( T_l_1 * dB_l_1 * dB_l_1 ) ;
                   double L2b_l_1 = B_l_1 * ( B_l_1 + ( dB_l_1 * dB_l_1 ) ) ;

                   double L1_l_1 = 0;
                   double L2_l_1 = 0;
                   if (fabs(L1b_l_1) > 0) {L1_l_1 = L1a_l_1/L1b_l_1; }
                   if (fabs(L2b_l_1) > 0) {L2_l_1 = 1 + ( ( dB_l_1 * dB_l_1 * S_l_1 ) / L2b_l_1 );}

                   double R_l_1 = 0;
                  
                   if ( (L1_l_1 > 0) && (L2_l_1 > 0) && ( fabs(dB_l_1) > 0) ) {
                       
                     double TL_l_1 = 2 * ( T_l_1 * log( L1_l_1 ) - ( ( B_l_1 * B_l_1 ) / ( dB_l_1 * dB_l_1 ) ) * log ( L2_l_1 ) );
                     if (TL_l_1 < 0) {TL_l_1 = 0;}
                     R_l_1 = TL_l_1;
                       
                   }
                       
                  //if (B_l_1 > 0){ Bin_l_1 =  2* ( (S_l_1 + B_l_1) * log(1+S_l_1/B_l_1) - S_l_1 ); }
                  //if (B_l_1 > 0){ Bin_l_1 = (S_l_1/sqrt(B_l_1))*(S_l_1/sqrt(B_l_1)); }
                   
                   //cout << " Bin = " << j << endl;
                   //cout << " significance of each bin = " << sqrt(Bin_l_1) << endl;

                  Sum_l_1 += R_l_1 ;
                  QuadraticSum_l_1 = sqrt(Sum_l_1);
                  //cout << " Quadratic sum from left = " << QuadraticSum_l_1 << endl;
                   
                  Sum_dB_l_1 += dB_l_1 ;
                  QuadraticSum_dB_l_1 = sqrt(Sum_dB_l_1);
                  //cout << " Quadratic sum from left = " << QuadraticSum_dB_l_1 << endl;
                  
              }
              
             h1_1->SetBinContent(j,QuadraticSum_l_1);
             h1_1->SetLineColor(kBlue-9);
             h1_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
              
            
         }
           

       // ------------------------------------------------------------
       
       //cout << " " << endl;
       //cout << " ============== significance From right ============== " << endl;
       //cout << " " << endl;
        
       TH1F *h1_2 = new TH1F("h1_2","Quadratic Sum from right",42,0,840); //right
        
         float S_r_1 = 0;
         float B_r_1_0 = 0;
         float B_r_1_1 = 0;
         float B_r_1_2 = 0;
         float B_r_1_3 = 0;
         float B_r_1_4 = 0;
         float B_r_1_5 = 0;
         float B_r_1_6 = 0;
         float B_r_1_7 = 0;
         float B_r_1_8 = 0;
         float B_r_1_9 = 0;
    
         float error_r_1_0 = 0;
         float error_r_1_1 = 0;
         float error_r_1_2 = 0;
         float error_r_1_3 = 0;
         float error_r_1_4 = 0;
         float error_r_1_5 = 0;
         float error_r_1_6 = 0;
         float error_r_1_7 = 0;
         float error_r_1_8 = 0;
         float error_r_1_9 = 0;
          
         float QuadraticSum_r_1 = 0;
         float Sum_r_1 = 0;
         float QuadraticSum_dB_r_1 = 0;
         float Sum_dB_r_1 = 0;
         
          for (int j=42; j>=1; j--) {
              
             S_r_1 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_r_1 << endl;
             B_r_1_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_r_1_9 << endl;
             B_r_1_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_r_1_8 << endl;
             B_r_1_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_r_1_7 << endl;
             B_r_1_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_r_1_6 << endl;
             B_r_1_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_r_1_5 << endl;
             B_r_1_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_r_1_4 << endl;
             B_r_1_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_r_1_3 << endl;
             B_r_1_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_r_1_2 << endl;
             B_r_1_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_r_1_1 << endl;
             B_r_1_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_r_1_0 << endl;
              
             error_r_1_9 = h_hist[9]->GetBinError(j);
             //cout << " error of ttbar of each bin = " << error_r_1_9 << endl;
             error_r_1_8 = h_hist[8]->GetBinError(j);
             //cout << " error of single top of each bin = " << error_r_1_8 << endl;
             error_r_1_7 = h_hist[7]->GetBinError(j);
             //cout << " error of Ztt of each bin = " << error_r_1_7 << endl;
             error_r_1_6 = h_hist[6]->GetBinError(j);
             //cout << " error of Wlv of each bin = " << error_r_1_6 << endl;
             error_r_1_5 = h_hist[5]->GetBinError(j);
             //cout << " error of Z of each bin = " << error_r_1_5 << endl;
             error_r_1_4 = h_hist[4]->GetBinError(j);
             //cout << " error of Fake_W of each bin = " << error_r_1_4 << endl;
             error_r_1_3 = h_hist[3]->GetBinError(j);
             //cout << " error of Fake_ttbar of each bin = " << error_r_1_3 << endl;
             error_r_1_2 = h_hist[2]->GetBinError(j);
             //cout << " error of DY of each bin = " << error_r_1_2 << endl;
             error_r_1_1 = h_hist[1]->GetBinError(j);
             //cout << " error of diboson of each bin = " << error_r_1_1 << endl;
             error_r_1_0 = h_hist[0]->GetBinError(j);
             //cout << " error of SMH of each bin = " << error_r_1_0 << endl;
             
             float B_r_1 = 0;
             for(int i = 0; i<10; i++) { B_r_1 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_r_1 << endl;
             
             float dB_r_1 = 0;
             for(int i = 0; i<10; i++) { dB_r_1 += h_hist[i]->GetBinError(j); }
             //cout << " Error of each bin = " << dB_r_1 << endl;
             
             if( B_r_1 > 0 && S_r_1 > 0) {
                 
                  double T_r_1 = S_r_1 + B_r_1 ;
                  double bE_r_1 = B_r_1 + ( dB_r_1 * dB_r_1 ) ;
                  double L1a_r_1 = T_r_1 * bE_r_1 ;
                  double L1b_r_1 = ( B_r_1 * B_r_1 ) + ( T_r_1 * dB_r_1 * dB_r_1 ) ;
                  double L2b_r_1 = B_r_1 * ( B_r_1 + ( dB_r_1 * dB_r_1 ) ) ;

                  double L1_r_1 = 0;
                  double L2_r_1 = 0;
                  if (fabs(L1b_r_1) > 0) {L1_r_1 = L1a_r_1/L1b_r_1; }
                  if (fabs(L2b_r_1) > 0) {L2_r_1 = 1 + ( ( dB_r_1 * dB_r_1 * S_r_1 ) / L2b_r_1 );}

                  double R_r_1 = 0;
                 
                  if ( (L1_r_1 > 0) && (L2_r_1 > 0) && ( fabs(dB_r_1) > 0) ) {
                      
                    double TL_r_1 = 2 * ( T_r_1 * log( L1_r_1 ) - ( ( B_r_1 * B_r_1 ) / ( dB_r_1 * dB_r_1 ) ) * log ( L2_r_1 ) );
                    if (TL_r_1 < 0) {TL_r_1 = 0;}
                    R_r_1 = TL_r_1;
                      
                  }
                      
                  //if (B_r_1 > 0){ Bin_r_1 =  2* ( (S_r_1 + B_r_1) * log(1+S_r_1/B_r_1) - S_r_1 ); }
                  //if (B_r_1 > 0){ Bin_r_1 = (S_r_1/sqrt(B_r_1))*(S_r_1/sqrt(B_r_1)); }
                  
                  //cout << " Bin = " << j << endl;
                  //cout << " significance of each bin = " << sqrt(Bin_r_1) << endl;

                 Sum_r_1 += R_r_1 ;
                 QuadraticSum_r_1 = sqrt(Sum_r_1);
                 //cout << " Quadratic sum from left = " << QuadraticSum_r_1 << endl;
                  
                 Sum_dB_r_1 += dB_r_1 ;
                 QuadraticSum_dB_r_1 = sqrt(Sum_dB_r_1);
                 //cout << " Quadratic sum from left = " << QuadraticSum_dB_r_1 << endl;
                 
             }

            h1_2->SetBinContent(j,QuadraticSum_r_1);
            h1_2->SetLineColor(kGreen-9);
            h1_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
       
        
        
        float rightmax1 = 1.1*h1_1->GetMaximum();
        float scale1 = 6500 / rightmax1;
        h1_1->Scale(scale1);
        h1_1->Draw("SAMEHIST");
        
        h1_2->Scale(scale1);
        h1_2->Draw("SAMEHIST");
        

        TGaxis*axis1 = new TGaxis(840,0,840,6500,0,rightmax1,510,"+L");
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
        
        for(int i= 10; i>=0 ; i--)
        {
            leg1->AddEntry(h_hist[i], h_titles[i].c_str());
        }
        leg1->AddEntry(h1_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
        leg1->AddEntry(h1_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
        leg1->Draw();
        
        c1 -> SaveAs("pTBB_SM.pdf");

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
            h_hist[i] = new TH1F(h_nm, "",37,0,740);
            h_hist[i]->GetXaxis()->SetTitle("p_{T}^{B1} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 12000); //5000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);
        
        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="pTB1*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs2 = new THStack("hs2", "");
          for(int i= 0; i<10 ; i++){ hs2->Add(h_hist[i], "hist2"); }
          hs2->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h2_1 = new TH1F("h2_1","Quadratic Sum from left",37,0,740); //left
          
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
         float B_l_2_9 = 0;
    
         float error_l_2_0 = 0;
         float error_l_2_1 = 0;
         float error_l_2_2 = 0;
         float error_l_2_3 = 0;
         float error_l_2_4 = 0;
         float error_l_2_5 = 0;
         float error_l_2_6 = 0;
         float error_l_2_7 = 0;
         float error_l_2_8 = 0;
         float error_l_2_9 = 0;
          
         float QuadraticSum_l_2 = 0;
         float Sum_l_2 = 0;
         float QuadraticSum_dB_l_2 = 0;
         float Sum_dB_l_2 = 0;
           
          for (int j=1; j<=37; j++) {
              
             S_l_2 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_2 << endl;
             B_l_2_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_2_9 << endl;
             B_l_2_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_2_8 << endl;
             B_l_2_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_2_7 << endl;
             B_l_2_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_2_6 << endl;
             B_l_2_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_2_5 << endl;
             B_l_2_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_2_4 << endl;
             B_l_2_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_2_3 << endl;
             B_l_2_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_2_2 << endl;
             B_l_2_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_2_1 << endl;
             B_l_2_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_2_0 << endl;
              
             error_l_2_9 = h_hist[9]->GetBinError(j);
             //cout << " error of ttbar of each bin = " << error_l_2_9 << endl;
             error_l_2_8 = h_hist[8]->GetBinError(j);
             //cout << " error of single top of each bin = " << error_l_2_8 << endl;
             error_l_2_7 = h_hist[7]->GetBinError(j);
             //cout << " error of Ztt of each bin = " << error_l_2_7 << endl;
             error_l_2_6 = h_hist[6]->GetBinError(j);
             //cout << " error of Wlv of each bin = " << error_l_2_6 << endl;
             error_l_2_5 = h_hist[5]->GetBinError(j);
             //cout << " error of Z of each bin = " << error_l_2_5 << endl;
             error_l_2_4 = h_hist[4]->GetBinError(j);
             //cout << " error of Fake_W of each bin = " << error_l_2_4 << endl;
             error_l_2_3 = h_hist[3]->GetBinError(j);
             //cout << " error of Fake_ttbar of each bin = " << error_l_2_3 << endl;
             error_l_2_2 = h_hist[2]->GetBinError(j);
             //cout << " error of DY of each bin = " << error_l_2_2 << endl;
             error_l_2_1 = h_hist[1]->GetBinError(j);
             //cout << " error of diboson of each bin = " << error_l_2_1 << endl;
             error_l_2_0 = h_hist[0]->GetBinError(j);
             //cout << " error of SMH of each bin = " << error_l_2_0 << endl;
             
             float B_l_2 = 0;
             for(int i = 0; i<10; i++) { B_l_2 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_2 << endl;
             
             float dB_l_2 = 0;
             for(int i = 0; i<10; i++) { dB_l_2 += h_hist[i]->GetBinError(j); }
             //cout << " Error of each bin = " << dB_l_2 << endl;
             
              if( B_l_2 > 0 && S_l_2 > 0) {
                  
                   double T_l_2 = S_l_2 + B_l_2 ;
                   double bE_l_2 = B_l_2 + ( dB_l_2 * dB_l_2 ) ;
                   double L1a_l_2 = T_l_2 * bE_l_2 ;
                   double L1b_l_2 = ( B_l_2 * B_l_2 ) + ( T_l_2 * dB_l_2 * dB_l_2 ) ;
                   double L2b_l_2 = B_l_2 * ( B_l_2 + ( dB_l_2 * dB_l_2 ) ) ;

                   double L1_l_2 = 0;
                   double L2_l_2 = 0;
                   if (fabs(L1b_l_2) > 0) {L1_l_2 = L1a_l_2/L1b_l_2; }
                   if (fabs(L2b_l_2) > 0) {L2_l_2 = 1 + ( ( dB_l_2 * dB_l_2 * S_l_2 ) / L2b_l_2 );}

                   double R_l_2 = 0;
                  
                   if ( (L1_l_2 > 0) && (L2_l_2 > 0) && ( fabs(dB_l_2) > 0) ) {
                       
                     double TL_l_2 = 2 * ( T_l_2 * log( L1_l_2 ) - ( ( B_l_2 * B_l_2 ) / ( dB_l_2 * dB_l_2 ) ) * log ( L2_l_2 ) );
                     if (TL_l_2 < 0) {TL_l_2 = 0;}
                     R_l_2 = TL_l_2;
                       
                   }
                       
                  //if (B_l_2 > 0){ Bin_l_2 =  2* ( (S_l_2 + B_l_2) * log(1+S_l_2/B_l_2) - S_l_2 ); }
                  //if (B_l_2 > 0){ Bin_l_2 = (S_l_2/sqrt(B_l_2))*(S_l_2/sqrt(B_l_2)); }
                   
                   //cout << " Bin = " << j << endl;
                   //cout << " significance of each bin = " << sqrt(Bin_l_2) << endl;

                  Sum_l_2 += R_l_2 ;
                  QuadraticSum_l_2 = sqrt(Sum_l_2);
                  //cout << " Quadratic sum from left = " << QuadraticSum_l_2 << endl;
                   
                  Sum_dB_l_2 += dB_l_2 ;
                  QuadraticSum_dB_l_2 = sqrt(Sum_dB_l_2);
                  //cout << " Quadratic sum from left = " << QuadraticSum_dB_l_2 << endl;
                  
              }

             h2_1->SetBinContent(j,QuadraticSum_l_2);
             h2_1->SetLineColor(kBlue-9);
             h2_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h2_2 = new TH1F("h2_2","Quadratic Sum from right",37,0,740); //right
          
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
         float B_r_2_9 = 0;
    
         float error_r_2_0 = 0;
         float error_r_2_1 = 0;
         float error_r_2_2 = 0;
         float error_r_2_3 = 0;
         float error_r_2_4 = 0;
         float error_r_2_5 = 0;
         float error_r_2_6 = 0;
         float error_r_2_7 = 0;
         float error_r_2_8 = 0;
         float error_r_2_9 = 0;
          
         float QuadraticSum_r_2 = 0;
         float Sum_r_2 = 0;
         float QuadraticSum_dB_r_2 = 0;
         float Sum_dB_r_2 = 0;
           
          for (int j=37; j>=1; j--) {
              
             S_r_2 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_r_2 << endl;
             B_r_2_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_r_2_9 << endl;
             B_r_2_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_r_2_8 << endl;
             B_r_2_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_r_2_7 << endl;
             B_r_2_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_r_2_6 << endl;
             B_r_2_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_r_2_5 << endl;
             B_r_2_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_r_2_4 << endl;
             B_r_2_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_r_2_3 << endl;
             B_r_2_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_r_2_2 << endl;
             B_r_2_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_r_2_1 << endl;
             B_r_2_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_r_2_0 << endl;
              
             error_r_2_9 = h_hist[9]->GetBinError(j);
             //cout << " error of ttbar of each bin = " << error_r_2_9 << endl;
             error_r_2_8 = h_hist[8]->GetBinError(j);
             //cout << " error of single top of each bin = " << error_r_2_8 << endl;
             error_r_2_7 = h_hist[7]->GetBinError(j);
             //cout << " error of Ztt of each bin = " << error_r_2_7 << endl;
             error_r_2_6 = h_hist[6]->GetBinError(j);
             //cout << " error of Wlv of each bin = " << error_r_2_6 << endl;
             error_r_2_5 = h_hist[5]->GetBinError(j);
             //cout << " error of Z of each bin = " << error_r_2_5 << endl;
             error_r_2_4 = h_hist[4]->GetBinError(j);
             //cout << " error of Fake_W of each bin = " << error_r_2_4 << endl;
             error_r_2_3 = h_hist[3]->GetBinError(j);
             //cout << " error of Fake_ttbar of each bin = " << error_r_2_3 << endl;
             error_r_2_2 = h_hist[2]->GetBinError(j);
             //cout << " error of DY of each bin = " << error_r_2_2 << endl;
             error_r_2_1 = h_hist[1]->GetBinError(j);
             //cout << " error of diboson of each bin = " << error_r_2_1 << endl;
             error_r_2_0 = h_hist[0]->GetBinError(j);
             //cout << " error of SMH of each bin = " << error_r_2_0 << endl;
             
             float B_r_2 = 0;
             for(int i = 0; i<10; i++) { B_r_2 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_r_2 << endl;
             
             float dB_r_2 = 0;
             for(int i = 0; i<10; i++) { dB_r_2 += h_hist[i]->GetBinError(j); }
             //cout << " Error of each bin = " << dB_r_2 << endl;
             
              if( B_r_2 > 0 && S_r_2 > 0) {
                  
                   double T_r_2 = S_r_2 + B_r_2 ;
                   double bE_r_2 = B_r_2 + ( dB_r_2 * dB_r_2 ) ;
                   double L1a_r_2 = T_r_2 * bE_r_2 ;
                   double L1b_r_2 = ( B_r_2 * B_r_2 ) + ( T_r_2 * dB_r_2 * dB_r_2 ) ;
                   double L2b_r_2 = B_r_2 * ( B_r_2 + ( dB_r_2 * dB_r_2 ) ) ;

                   double L1_r_2 = 0;
                   double L2_r_2 = 0;
                   if (fabs(L1b_r_2) > 0) {L1_r_2 = L1a_r_2/L1b_r_2; }
                   if (fabs(L2b_r_2) > 0) {L2_r_2 = 1 + ( ( dB_r_2 * dB_r_2 * S_r_2 ) / L2b_r_2 );}

                   double R_r_2 = 0;
                  
                   if ( (L1_r_2 > 0) && (L2_r_2 > 0) && ( fabs(dB_r_2) > 0) ) {
                       
                     double TL_r_2 = 2 * ( T_r_2 * log( L1_r_2 ) - ( ( B_r_2 * B_r_2 ) / ( dB_r_2 * dB_r_2 ) ) * log ( L2_r_2 ) );
                     if (TL_r_2 < 0) {TL_r_2 = 0;}
                     R_r_2 = TL_r_2;
                       
                   }
                       
                  //if (B_r_2 > 0){ Bin_r_2 =  2* ( (S_r_2 + B_r_2) * log(1+S_r_2/B_r_2) - S_r_2 ); }
                  //if (B_r_2 > 0){ Bin_r_2 = (S_r_2/sqrt(B_r_2))*(S_r_2/sqrt(B_r_2)); }
                   
                   //cout << " Bin = " << j << endl;
                   //cout << " significance of each bin = " << sqrt(Bin_r_2) << endl;

                  Sum_r_2 += R_r_2 ;
                  QuadraticSum_r_2 = sqrt(Sum_r_2);
                  //cout << " Quadratic sum from left = " << QuadraticSum_r_2 << endl;
                   
                  Sum_dB_r_2 += dB_r_2 ;
                  QuadraticSum_dB_r_2 = sqrt(Sum_dB_r_2);
                  //cout << " Quadratic sum from left = " << QuadraticSum_dB_r_2 << endl;
                  
              }

            h2_2->SetBinContent(j,QuadraticSum_r_2);
            h2_2->SetLineColor(kGreen-9);
            h2_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax2 = 1.1*h2_1->GetMaximum();
          float scale2 = 12000 / rightmax2;
          h2_1->Scale(scale2);
          h2_1->Draw("SAMEHIST");
          
          h2_2->Scale(scale2);
          h2_2->Draw("SAMEHIST");
          

          TGaxis*axis2 = new TGaxis(740,0,740,12000,0,rightmax2,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg2->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg2->AddEntry(h2_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg2->AddEntry(h2_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg2->Draw();
          
          c2 -> SaveAs("pTB1_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",30,0,300);
            h_hist[i]->GetXaxis()->SetTitle("p_{T}^{B2} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 10 GeV");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 8500); //7200
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);
        
        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="pTB2*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs3 = new THStack("hs3", "");
          for(int i= 0; i<10 ; i++){ hs3->Add(h_hist[i], "hist3"); }
          hs3->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h3_1 = new TH1F("h3_1","Quadratic Sum from left",30,0,300); //left
          
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
         float B_l_3_9 = 0;
          
         float QuadraticSum_l_3 = 0;
         float Sum_l_3 = 0;
           
          for (int j=1; j<=30; j++) {
              
             S_l_3 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_3 << endl;
             B_l_3_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_3_9 << endl;
             B_l_3_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_3_8 << endl;
             B_l_3_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_3_7 << endl;
             B_l_3_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_3_6 << endl;
             B_l_3_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_3_5 << endl;
             B_l_3_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_3_4 << endl;
             B_l_3_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_3_3 << endl;
             B_l_3_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_3_2 << endl;
             B_l_3_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_3_1 << endl;
             B_l_3_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_3_0 << endl;
             
             float B_l_3 = 0;
             for(int i = 0; i<10; i++) { B_l_3 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_3 << endl;

             h3_1->SetBinContent(j,QuadraticSum_l_3);
             h3_1->SetLineColor(kBlue-9);
             h3_1->SetLineStyle(2);
              
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h3_2 = new TH1F("h3_2","Quadratic Sum from right",30,0,300); //right
          
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
         float B_r_3_9 = 0;
          
         float QuadraticSum_r_3 = 0;
         float Sum_r_3 = 0;
          
          for (int j=30; j>=1; j--) {
              
            S_r_3 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_3 << endl;
            B_r_3_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_3_9 << endl;
            B_r_3_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_3_8 << endl;
            B_r_3_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_3_7 << endl;
            B_r_3_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_3_6 << endl;
            B_r_3_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_3_5 << endl;
            B_r_3_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_3_4 << endl;
            B_r_3_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_3_3 << endl;
            B_r_3_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_3_2 << endl;
            B_r_3_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_3_1 << endl;
            B_r_3_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_3_0 << endl;
            
            float B_r_3 = 0;
            for(int i = 0; i<10; i++) { B_r_3 += h_hist[i]->GetBinContent(j); }
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

            h3_2->SetBinContent(j,QuadraticSum_r_3);
            h3_2->SetLineColor(kGreen-9);
            h3_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax3 = 1.1*h3_1->GetMaximum();
          float scale3 = 8500 / rightmax3;
          h3_1->Scale(scale3);
          h3_1->Draw("SAMEHIST");
          
          h3_2->Scale(scale3);
          h3_2->Draw("SAMEHIST");
          

          TGaxis*axis3 = new TGaxis(300,0,300,8500,0,rightmax3,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg3->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg3->AddEntry(h3_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg3->AddEntry(h3_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg3->Draw();
          
          c3 -> SaveAs("pTB2_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 15000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);
        

          for (int i=0; i<n_smp; i++){
              hist_draw[i]="mBB*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs4 = new THStack("hs4", "");
          for(int i= 0; i<10 ; i++){ hs4->Add(h_hist[i], "hist5"); }
          hs4->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h4_1 = new TH1F("h4_1","Quadratic Sum from left",25,0,500); //left
          
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
         float B_l_4_9 = 0;
          
         float QuadraticSum_l_4 = 0;
         float Sum_l_4 = 0;
           
          for (int j=1; j<=25; j++) {
              
             S_l_4 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_4 << endl;
             B_l_4_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_4_9 << endl;
             B_l_4_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_4_8 << endl;
             B_l_4_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_4_7 << endl;
             B_l_4_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_4_6 << endl;
             B_l_4_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_4_5 << endl;
             B_l_4_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_4_4 << endl;
             B_l_4_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_4_3 << endl;
             B_l_4_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_4_2 << endl;
             B_l_4_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_4_1 << endl;
             B_l_4_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_4_0 << endl;
             
             float B_l_4 = 0;
             for(int i = 0; i<10; i++) { B_l_4 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_4 << endl;

             h4_1->SetBinContent(j,QuadraticSum_l_4);
             h4_1->SetLineColor(kBlue-9);
             h4_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h4_2 = new TH1F("h4_2","Quadratic Sum from right",25,0,500); //right
          
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
         float B_r_4_9 = 0;
          
         float QuadraticSum_r_4 = 0;
         float Sum_r_4 = 0;
          
          for (int j=25; j>=1; j--) {
              
            S_r_4 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_4 << endl;
            B_r_4_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_4_9 << endl;
            B_r_4_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_4_8 << endl;
            B_r_4_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_4_7 << endl;
            B_r_4_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_4_6 << endl;
            B_r_4_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_4_5 << endl;
            B_r_4_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_4_4 << endl;
            B_r_4_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_4_3 << endl;
            B_r_4_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_4_2 << endl;
            B_r_4_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_4_1 << endl;
            B_r_4_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_4_0 << endl;
            
            float B_r_4 = 0;
            for(int i = 0; i<10; i++) { B_r_4 += h_hist[i]->GetBinContent(j); }
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

            h4_2->SetBinContent(j,QuadraticSum_r_4);
            h4_2->SetLineColor(kGreen-9);
            h4_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax4 = 1.1*h4_1->GetMaximum();
          float scale4 = 15000 / rightmax4;
          h4_1->Scale(scale4);
          h4_1->Draw("SAMEHIST");
          
          h4_2->Scale(scale4);
          h4_2->Draw("SAMEHIST");
          

          TGaxis*axis4 = new TGaxis(500,0,500,15000,0,rightmax4,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg4->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg4->AddEntry(h4_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg4->AddEntry(h4_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg4->Draw();
          
          c4 -> SaveAs("mBB_SM.pdf");
        
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);
     
        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dPhiBB>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs5 = new THStack("hs5", "");
          for(int i= 0; i<10 ; i++){ hs5->Add(h_hist[i], "hist5"); }
          hs5->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h5_1 = new TH1F("h5_1","Quadratic Sum from left",20,0,3.5); //left
          
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
         float B_l_5_9 = 0;
          
         float QuadraticSum_l_5 = 0;
         float Sum_l_5 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_5 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_5 << endl;
             B_l_5_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_5_9 << endl;
             B_l_5_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_5_8 << endl;
             B_l_5_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_5_7 << endl;
             B_l_5_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_5_6 << endl;
             B_l_5_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_5_5 << endl;
             B_l_5_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_5_4 << endl;
             B_l_5_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_5_3 << endl;
             B_l_5_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_5_2 << endl;
             B_l_5_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_5_1 << endl;
             B_l_5_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_5_0 << endl;
             
             float B_l_5 = 0;
             for(int i = 0; i<10; i++) { B_l_5 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_5 << endl;

             h5_1->SetBinContent(j,QuadraticSum_l_5);
             h5_1->SetLineColor(kBlue-9);
             h5_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h5_2 = new TH1F("h5_2","Quadratic Sum from right",20,0,3.5); //right
          
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
         float B_r_5_9 = 0;
          
         float QuadraticSum_r_5 = 0;
         float Sum_r_5 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_5 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_5 << endl;
            B_r_5_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_5_9 << endl;
            B_r_5_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_5_8 << endl;
            B_r_5_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_5_7 << endl;
            B_r_5_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_5_6 << endl;
            B_r_5_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_5_5 << endl;
            B_r_5_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_5_4 << endl;
            B_r_5_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_5_3 << endl;
            B_r_5_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_5_2 << endl;
            B_r_5_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_5_1 << endl;
            B_r_5_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_5_0 << endl;
            
            float B_r_5 = 0;
            for(int i = 0; i<10; i++) { B_r_5 += h_hist[i]->GetBinContent(j); }
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

            h5_2->SetBinContent(j,QuadraticSum_r_5);
            h5_2->SetLineColor(kGreen-9);
            h5_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg5->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg5->AddEntry(h5_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg5->AddEntry(h5_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg5->Draw();
          
          c5 -> SaveAs("dPhiBB_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",15,0,3);
            h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (B,B)");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 6000); //3200
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);
        

          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dEtaBB>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs6 = new THStack("hs6", "");
          for(int i= 0; i<10 ; i++){ hs6->Add(h_hist[i], "hist6"); }
          hs6->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h6_1 = new TH1F("h6_1","Quadratic Sum from left",15,0,3); //left
          
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
         float B_l_6_9 = 0;
          
         float QuadraticSum_l_6 = 0;
         float Sum_l_6 = 0;
           
          for (int j=1; j<=15; j++) {
              
             S_l_6 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_6 << endl;
             B_l_6_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_6_9 << endl;
             B_l_6_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_6_8 << endl;
             B_l_6_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_6_7 << endl;
             B_l_6_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_6_6 << endl;
             B_l_6_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_6_5 << endl;
             B_l_6_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_6_4 << endl;
             B_l_6_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_6_3 << endl;
             B_l_6_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_6_2 << endl;
             B_l_6_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_6_1 << endl;
             B_l_6_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_6_0 << endl;
             
             float B_l_6 = 0;
             for(int i = 0; i<10; i++) { B_l_6 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_6 << endl;

             h6_1->SetBinContent(j,QuadraticSum_l_6);
             h6_1->SetLineColor(kBlue-9);
             h6_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h6_2 = new TH1F("h6_2","Quadratic Sum from right",15,0,3); //right
          
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
         float B_r_6_9 = 0;
          
         float QuadraticSum_r_6 = 0;
         float Sum_r_6 = 0;
          
          for (int j=15; j>=1; j--) {
              
            S_r_6 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_6 << endl;
            B_r_6_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_6_9 << endl;
            B_r_6_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_6_8 << endl;
            B_r_6_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_6_7 << endl;
            B_r_6_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_6_6 << endl;
            B_r_6_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_6_5 << endl;
            B_r_6_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_6_4 << endl;
            B_r_6_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_6_3 << endl;
            B_r_6_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_6_2 << endl;
            B_r_6_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_6_1 << endl;
            B_r_6_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_6_0 << endl;
            
            float B_r_6 = 0;
            for(int i = 0; i<10; i++) { B_r_6 += h_hist[i]->GetBinContent(j); }
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

            h6_2->SetBinContent(j,QuadraticSum_r_6);
            h6_2->SetLineColor(kGreen-9);
            h6_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax6 = 1.1*h6_1->GetMaximum();
          float scale6 = 6000 / rightmax6;
          h6_1->Scale(scale6);
          h6_1->Draw("SAMEHIST");
          
          h6_2->Scale(scale6);
          h6_2->Draw("SAMEHIST");
          

          TGaxis*axis6 = new TGaxis(3,0,3,6000,0,rightmax6,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg6->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg6->AddEntry(h6_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg6->AddEntry(h6_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg6->Draw();
          
          c6 -> SaveAs("dEtaBB_SM.pdf");

        
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
            h_hist[i] = new TH1F(h_nm, "",20,0,4);
            h_hist[i]->GetXaxis()->SetTitle("#DeltaR (B,B)");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 4000); //2200
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);
        
        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dRBB>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs7 = new THStack("hs7", "");
          for(int i= 0; i<10 ; i++){ hs7->Add(h_hist[i], "hist7"); }
          hs7->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h7_1 = new TH1F("h7_1","Quadratic Sum from left",20,0,4); //left
          
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
         float B_l_7_9 = 0;
          
         float QuadraticSum_l_7 = 0;
         float Sum_l_7 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_7 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_7 << endl;
             B_l_7_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_7_9 << endl;
             B_l_7_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_7_8 << endl;
             B_l_7_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_7_7 << endl;
             B_l_7_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_7_6 << endl;
             B_l_7_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_7_5 << endl;
             B_l_7_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_7_4 << endl;
             B_l_7_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_7_3 << endl;
             B_l_7_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_7_2 << endl;
             B_l_7_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_7_1 << endl;
             B_l_7_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_7_0 << endl;
             
             float B_l_7 = 0;
             for(int i = 0; i<10; i++) { B_l_7 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_7 << endl;

             h7_1->SetBinContent(j,QuadraticSum_l_7);
             h7_1->SetLineColor(kBlue-9);
             h7_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h7_2 = new TH1F("h7_2","Quadratic Sum from right",20,0,4); //right
          
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
         float B_r_7_9 = 0;
          
         float QuadraticSum_r_7 = 0;
         float Sum_r_7 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_7 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_7 << endl;
            B_r_7_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_7_9 << endl;
            B_r_7_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_7_8 << endl;
            B_r_7_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_7_7 << endl;
            B_r_7_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_7_6 << endl;
            B_r_7_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_7_5 << endl;
            B_r_7_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_7_4 << endl;
            B_r_7_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_7_3 << endl;
            B_r_7_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_7_2 << endl;
            B_r_7_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_7_1 << endl;
            B_r_7_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_7_0 << endl;
            
            float B_r_7 = 0;
            for(int i = 0; i<10; i++) { B_r_7 += h_hist[i]->GetBinContent(j); }
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

            h7_2->SetBinContent(j,QuadraticSum_r_7);
            h7_2->SetLineColor(kGreen-9);
            h7_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax7 = 1.1*h7_1->GetMaximum();
          float scale7 = 4000 / rightmax7;
          h7_1->Scale(scale7);
          h7_1->Draw("SAMEHIST");
          
          h7_2->Scale(scale7);
          h7_2->Draw("SAMEHIST");
          

          TGaxis*axis7 = new TGaxis(4,0,4,4000,0,rightmax7,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg7->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg7->AddEntry(h7_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg7->AddEntry(h7_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg7->Draw();
          
          c7 -> SaveAs("dRBB_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",48,0,960);
            h_hist[i]->GetXaxis()->SetTitle("p_{T}^{#tau#tau} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 5500); //2400
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="pTtautau*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs8 = new THStack("hs8", "");
          for(int i= 0; i<10 ; i++){ hs8->Add(h_hist[i], "hist8"); }
          hs8->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h8_1 = new TH1F("h8_1","Quadratic Sum from left",48,0,960); //left
          
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
         float B_l_8_9 = 0;
          
         float QuadraticSum_l_8 = 0;
         float Sum_l_8 = 0;
           
          for (int j=1; j<=48; j++) {
              
             S_l_8 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_8 << endl;
             B_l_8_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_8_9 << endl;
             B_l_8_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_8_8 << endl;
             B_l_8_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_8_7 << endl;
             B_l_8_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_8_6 << endl;
             B_l_8_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_8_5 << endl;
             B_l_8_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_8_4 << endl;
             B_l_8_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_8_3 << endl;
             B_l_8_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_8_2 << endl;
             B_l_8_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_8_1 << endl;
             B_l_8_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_8_0 << endl;
             
             float B_l_8 = 0;
             for(int i = 0; i<10; i++) { B_l_8 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_8 << endl;

             h8_1->SetBinContent(j,QuadraticSum_l_8);
             h8_1->SetLineColor(kBlue-9);
             h8_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h8_2 = new TH1F("h8_2","Quadratic Sum from right",48,0,960); //right
          
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
         float B_r_8_9 = 0;
          
         float QuadraticSum_r_8 = 0;
         float Sum_r_8 = 0;
          
          for (int j=48; j>=1; j--) {
              
            S_r_8 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_8 << endl;
            B_r_8_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_8_9 << endl;
            B_r_8_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_8_8 << endl;
            B_r_8_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_8_7 << endl;
            B_r_8_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_8_6 << endl;
            B_r_8_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_8_5 << endl;
            B_r_8_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_8_4 << endl;
            B_r_8_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_8_3 << endl;
            B_r_8_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_8_2 << endl;
            B_r_8_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_8_1 << endl;
            B_r_8_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_8_0 << endl;
            
            float B_r_8 = 0;
            for(int i = 0; i<10; i++) { B_r_8 += h_hist[i]->GetBinContent(j); }
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

            h8_2->SetBinContent(j,QuadraticSum_r_8);
            h8_2->SetLineColor(kGreen-9);
            h8_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax8 = 1.1*h8_1->GetMaximum();
          float scale8 = 5500 / rightmax8;
          h8_1->Scale(scale8);
          h8_1->Draw("SAMEHIST");
          
          h8_2->Scale(scale8);
          h8_2->Draw("SAMEHIST");
          

        
          TGaxis*axis8 = new TGaxis(960,0,960,5500,0,rightmax8,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg8->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg8->AddEntry(h8_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg8->AddEntry(h8_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg8->Draw();
          
          c8 -> SaveAs("pTtautau_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",23,0,460);
            h_hist[i]->GetXaxis()->SetTitle("#Deltap_{T} (#tau,#tau) [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 10000); //4500
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dPtLepTau*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs19 = new THStack("hs19", "");
          for(int i= 0; i<10 ; i++){ hs19->Add(h_hist[i], "hist19"); }
          hs19->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h19_1 = new TH1F("h19_1","Quadratic Sum from left",23,0,460); //left
          
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
         float B_l_19_9 = 0;
          
         float QuadraticSum_l_19 = 0;
         float Sum_l_19 = 0;
           
          for (int j=1; j<=23; j++) {
              
             S_l_19 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_19 << endl;
             B_l_19_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_19_9 << endl;
             B_l_19_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_19_8 << endl;
             B_l_19_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_19_7 << endl;
             B_l_19_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_19_6 << endl;
             B_l_19_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_19_5 << endl;
             B_l_19_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_19_4 << endl;
             B_l_19_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_19_3 << endl;
             B_l_19_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_19_2 << endl;
             B_l_19_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_19_1 << endl;
             B_l_19_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_19_0 << endl;
             
             float B_l_19 = 0;
             for(int i = 0; i<10; i++) { B_l_19 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_19 << endl;

             h19_1->SetBinContent(j,QuadraticSum_l_19);
             h19_1->SetLineColor(kBlue-9);
             h19_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h19_2 = new TH1F("h19_2","Quadratic Sum from right",23,0,460); //right
          
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
         float B_r_19_9 = 0;
          
         float QuadraticSum_r_19 = 0;
         float Sum_r_19 = 0;
          
          for (int j=23; j>=1; j--) {
              
            S_r_19 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_19 << endl;
            B_r_19_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_19_9 << endl;
            B_r_19_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_19_8 << endl;
            B_r_19_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_19_7 << endl;
            B_r_19_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_19_6 << endl;
            B_r_19_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_19_5 << endl;
            B_r_19_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_19_4 << endl;
            B_r_19_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_19_3 << endl;
            B_r_19_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_19_2 << endl;
            B_r_19_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_19_1 << endl;
            B_r_19_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_19_0 << endl;
            
            float B_r_19 = 0;
            for(int i = 0; i<10; i++) { B_r_19 += h_hist[i]->GetBinContent(j); }
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

            h19_2->SetBinContent(j,QuadraticSum_r_19);
            h19_2->SetLineColor(kGreen-9);
            h19_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax19 = 1.1*h19_1->GetMaximum();
          float scale19 = 10000 / rightmax19;
          h19_1->Scale(scale19);
          h19_1->Draw("SAMEHIST");
          
          h19_2->Scale(scale19);
          h19_2->Draw("SAMEHIST");
          

        
          TGaxis*axis19 = new TGaxis(460,0,460,10000,0,rightmax19,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg19->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg19->AddEntry(h19_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg19->AddEntry(h19_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg19->Draw();
          
          c19 -> SaveAs("dPtLepTau_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",35,0,700);
            h_hist[i]->GetXaxis()->SetTitle("p_{T}^{#tau_{h}} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 20000); //9000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="TauPt>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs9 = new THStack("hs9", "");
          for(int i= 0; i<10 ; i++){ hs9->Add(h_hist[i], "hist9"); }
          hs9->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h9_1 = new TH1F("h9_1","Quadratic Sum from left",35,0,700); //left
          
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
         float B_l_9_9 = 0;
          
         float QuadraticSum_l_9 = 0;
         float Sum_l_9 = 0;
           
          for (int j=1; j<=35; j++) {
              
             S_l_9 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_9 << endl;
             B_l_9_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_9_9 << endl;
             B_l_9_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_9_8 << endl;
             B_l_9_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_9_7 << endl;
             B_l_9_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_9_6 << endl;
             B_l_9_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_9_5 << endl;
             B_l_9_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_9_4 << endl;
             B_l_9_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_9_3 << endl;
             B_l_9_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_9_2 << endl;
             B_l_9_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_9_1 << endl;
             B_l_9_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_9_0 << endl;
             
             float B_l_9 = 0;
             for(int i = 0; i<10; i++) { B_l_9 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_9 << endl;

             h9_1->SetBinContent(j,QuadraticSum_l_9);
             h9_1->SetLineColor(kBlue-9);
             h9_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h9_2 = new TH1F("h9_2","Quadratic Sum from right",35,0,700); //right
          
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
         float B_r_9_9 = 0;
          
         float QuadraticSum_r_9 = 0;
         float Sum_r_9 = 0;
          
          for (int j=35; j>=1; j--) {
              
            S_r_9 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_9 << endl;
            B_r_9_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_9_9 << endl;
            B_r_9_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_9_8 << endl;
            B_r_9_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_9_7 << endl;
            B_r_9_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_9_6 << endl;
            B_r_9_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_9_5 << endl;
            B_r_9_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_9_4 << endl;
            B_r_9_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_9_3 << endl;
            B_r_9_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_9_2 << endl;
            B_r_9_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_9_1 << endl;
            B_r_9_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_9_0 << endl;
            
            float B_r_9 = 0;
            for(int i = 0; i<10; i++) { B_r_9 += h_hist[i]->GetBinContent(j); }
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

            h9_2->SetBinContent(j,QuadraticSum_r_9);
            h9_2->SetLineColor(kGreen-9);
            h9_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax9 = 1.1*h9_1->GetMaximum();
          float scale9 = 20000 / rightmax9;
          h9_1->Scale(scale9);
          h9_1->Draw("SAMEHIST");
          
          h9_2->Scale(scale9);
          h9_2->Draw("SAMEHIST");
          
        
          TGaxis*axis9 = new TGaxis(700,0,700,20000,0,rightmax9,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg9->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg9->AddEntry(h9_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg9->AddEntry(h9_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg9->Draw();
          
          c9 -> SaveAs("TauPt_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",25,0,500);
            h_hist[i]->GetXaxis()->SetTitle("p_{T}^{#tau_{l}} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 15000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="LepPt>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs10 = new THStack("hs10", "");
          for(int i= 0; i<10 ; i++){ hs10->Add(h_hist[i], "hist10"); }
          hs10->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h10_1 = new TH1F("h10_1","Quadratic Sum from left",25,0,500); //left
          
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
         float B_l_10_9 = 0;
          
         float QuadraticSum_l_10 = 0;
         float Sum_l_10 = 0;
           
          for (int j=1; j<=25; j++) {
              
             S_l_10 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_10 << endl;
             B_l_10_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_10_9 << endl;
             B_l_10_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_10_8 << endl;
             B_l_10_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_10_7 << endl;
             B_l_10_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_10_6 << endl;
             B_l_10_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_10_5 << endl;
             B_l_10_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_10_4 << endl;
             B_l_10_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_10_3 << endl;
             B_l_10_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_10_2 << endl;
             B_l_10_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_10_1 << endl;
             B_l_10_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_10_0 << endl;
             
             float B_l_10 = 0;
             for(int i = 0; i<10; i++) { B_l_10 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_10 << endl;

             h10_1->SetBinContent(j,QuadraticSum_l_10);
             h10_1->SetLineColor(kBlue-9);
             h10_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h10_2 = new TH1F("h10_2","Quadratic Sum from right",25,0,500); //right
          
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
         float B_r_10_9 = 0;
          
         float QuadraticSum_r_10 = 0;
         float Sum_r_10 = 0;
          
          for (int j=25; j>=1; j--) {
              
            S_r_10 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_10 << endl;
            B_r_10_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_10_9 << endl;
            B_r_10_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_10_8 << endl;
            B_r_10_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_10_7 << endl;
            B_r_10_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_10_6 << endl;
            B_r_10_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_10_5 << endl;
            B_r_10_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_10_4 << endl;
            B_r_10_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_10_3 << endl;
            B_r_10_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_10_2 << endl;
            B_r_10_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_10_1 << endl;
            B_r_10_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_10_0 << endl;
            
            float B_r_10 = 0;
            for(int i = 0; i<10; i++) { B_r_10 += h_hist[i]->GetBinContent(j); }
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

            h10_2->SetBinContent(j,QuadraticSum_r_10);
            h10_2->SetLineColor(kGreen-9);
            h10_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax10 = 1.1*h10_1->GetMaximum();
          float scale10 = 15000 / rightmax10;
          h10_1->Scale(scale10);
          h10_1->Draw("SAMEHIST");
          
          h10_2->Scale(scale10);
          h10_2->Draw("SAMEHIST");
          
        
        TGaxis*axis10 = new TGaxis(500,0,500,15000,0,rightmax10,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg10->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg10->AddEntry(h10_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg10->AddEntry(h10_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg10->Draw();
          
          c10 -> SaveAs("LepPt_SM.pdf");
         
        
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
            h_hist[i] = new TH1F(h_nm, "",30,0,600);
            h_hist[i]->GetXaxis()->SetTitle("m_{MMC} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 14000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="mMMC*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs11 = new THStack("hs11", "");
          for(int i= 0; i<10 ; i++){ hs11->Add(h_hist[i], "hist11"); }
          hs11->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h11_1 = new TH1F("h11_1","Quadratic Sum from left",30,0,600); //left
          
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
         float B_l_11_9 = 0;
          
         float QuadraticSum_l_11 = 0;
         float Sum_l_11 = 0;
           
          for (int j=1; j<=30; j++) {
              
             S_l_11 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_11 << endl;
             B_l_11_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_11_9 << endl;
             B_l_11_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_11_8 << endl;
             B_l_11_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_11_7 << endl;
             B_l_11_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_11_6 << endl;
             B_l_11_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_11_5 << endl;
             B_l_11_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_11_4 << endl;
             B_l_11_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_11_3 << endl;
             B_l_11_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_11_2 << endl;
             B_l_11_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_11_1 << endl;
             B_l_11_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_11_0 << endl;
             
             float B_l_11 = 0;
             for(int i = 0; i<10; i++) { B_l_11 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_11 << endl;

             h11_1->SetBinContent(j,QuadraticSum_l_11);
             h11_1->SetLineColor(kBlue-9);
             h11_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h11_2 = new TH1F("h11_2","Quadratic Sum from right",30,0,600); //right
          
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
         float B_r_11_9 = 0;
          
         float QuadraticSum_r_11 = 0;
         float Sum_r_11 = 0;
          
          for (int j=30; j>=1; j--) {
              
            S_r_11 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_11 << endl;
            B_r_11_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_11_9 << endl;
            B_r_11_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_11_8 << endl;
            B_r_11_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_11_7 << endl;
            B_r_11_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_11_6 << endl;
            B_r_11_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_11_5 << endl;
            B_r_11_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_11_4 << endl;
            B_r_11_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_11_3 << endl;
            B_r_11_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_11_2 << endl;
            B_r_11_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_11_1 << endl;
            B_r_11_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_11_0 << endl;
            
            float B_r_11 = 0;
            for(int i = 0; i<10; i++) { B_r_11 += h_hist[i]->GetBinContent(j); }
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

            h11_2->SetBinContent(j,QuadraticSum_r_11);
            h11_2->SetLineColor(kGreen-9);
            h11_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax11 = 1.1*h11_1->GetMaximum();
          float scale11 = 14000 / rightmax11;
          h11_1->Scale(scale11);
          h11_1->Draw("SAMEHIST");
          
          h11_2->Scale(scale11);
          h11_2->Draw("SAMEHIST");
          
        
          TGaxis*axis11 = new TGaxis(600,0,600,14000,0,rightmax11,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg11->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg11->AddEntry(h11_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg11->AddEntry(h11_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg11->Draw();
          
          c11 -> SaveAs("mMMC_SM.pdf");
        
         
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 1500); //800
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dPhiLepTau>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs12 = new THStack("hs12", "");
          for(int i= 0; i<10 ; i++){ hs12->Add(h_hist[i], "hist12"); }
          hs12->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h12_1 = new TH1F("h12_1","Quadratic Sum from left",20,0,3.5); //left
          
         float S_l_12 = 0;
         float B_l_12_0 = 0;
         float B_l_12_1 = 0;
         float B_l_12_2 = 0;
         float B_l_12_3 = 0;
         float B_l_12_4 = 0;
         float B_l_12_5 = 0;
         float B_l_12_6 = 0;
         float B_l_12_7 = 0;
         float B_l_12_8 = 0;
         float B_l_12_9 = 0;
          
         float QuadraticSum_l_12 = 0;
         float Sum_l_12 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_12 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_12 << endl;
             B_l_12_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_12_9 << endl;
             B_l_12_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_12_8 << endl;
             B_l_12_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_12_7 << endl;
             B_l_12_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_12_6 << endl;
             B_l_12_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_12_5 << endl;
             B_l_12_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_12_4 << endl;
             B_l_12_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_12_3 << endl;
             B_l_12_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_12_2 << endl;
             B_l_12_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_12_1 << endl;
             B_l_12_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_12_0 << endl;
             
             float B_l_12 = 0;
             for(int i = 0; i<10; i++) { B_l_12 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_12 << endl;
             
             float Bin_l_12 = 0;
             if (B_l_12 > 0){
                 Bin_l_12 =  2* ( (S_l_12 + B_l_12) * log(1+S_l_12/B_l_12) - S_l_12 );
                 //Bin_l_12 = (S_l_12/sqrt(B_l_12))*(S_l_12/sqrt(B_l_12));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_12) << endl; //
             

             Sum_l_12 += Bin_l_12 ;
             QuadraticSum_l_12 = sqrt(Sum_l_12);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_12 << endl;

             h12_1->SetBinContent(j,QuadraticSum_l_12);
             h12_1->SetLineColor(kBlue-9);
             h12_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h12_2 = new TH1F("h12_2","Quadratic Sum from right",20,0,3.5); //right
          
         float S_r_12 = 0;
         float B_r_12_0 = 0;
         float B_r_12_1 = 0;
         float B_r_12_2 = 0;
         float B_r_12_3 = 0;
         float B_r_12_4 = 0;
         float B_r_12_5 = 0;
         float B_r_12_6 = 0;
         float B_r_12_7 = 0;
         float B_r_12_8 = 0;
         float B_r_12_9 = 0;
          
         float QuadraticSum_r_12 = 0;
         float Sum_r_12 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_12 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_12 << endl;
            B_r_12_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_12_9 << endl;
            B_r_12_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_12_8 << endl;
            B_r_12_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_12_7 << endl;
            B_r_12_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_12_6 << endl;
            B_r_12_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_12_5 << endl;
            B_r_12_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_12_4 << endl;
            B_r_12_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_12_3 << endl;
            B_r_12_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_12_2 << endl;
            B_r_12_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_12_1 << endl;
            B_r_12_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_12_0 << endl;
            
            float B_r_12 = 0;
            for(int i = 0; i<10; i++) { B_r_12 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_12 << endl;
            
            float Bin_r_12 = 0;
            if (B_r_12 > 0){
                Bin_r_12 =  2* ( (S_r_12 + B_r_12) * log(1+S_r_12/B_r_12) - S_r_12 );
                //Bin_r_12 = (S_r_12/sqrt(B_r_12))*(S_r_12/sqrt(B_r_12));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_12) << endl;
            

            Sum_r_12 += Bin_r_12 ;
            QuadraticSum_r_12 = sqrt(Sum_r_12);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_12 << endl;

            h12_2->SetBinContent(j,QuadraticSum_r_12);
            h12_2->SetLineColor(kGreen-9);
            h12_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg12->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg12->AddEntry(h12_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg12->AddEntry(h12_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg12->Draw();
          
          c12 -> SaveAs("dPhiLepTau_SM.pdf");
        
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="TauPhi>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs13 = new THStack("hs13", "");
          for(int i= 0; i<10 ; i++){ hs13->Add(h_hist[i], "hist13"); }
          hs13->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h13_1 = new TH1F("h13_1","Quadratic Sum from left",20,0,3.5); //left
          
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
         float B_l_13_9 = 0;
          
         float QuadraticSum_l_13 = 0;
         float Sum_l_13 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_13 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_13 << endl;
             B_l_13_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_13_9 << endl;
             B_l_13_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_13_8 << endl;
             B_l_13_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_13_7 << endl;
             B_l_13_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_13_6 << endl;
             B_l_13_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_13_5 << endl;
             B_l_13_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_13_4 << endl;
             B_l_13_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_13_3 << endl;
             B_l_13_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_13_2 << endl;
             B_l_13_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_13_1 << endl;
             B_l_13_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_13_0 << endl;
             
             float B_l_13 = 0;
             for(int i = 0; i<10; i++) { B_l_13 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_13 << endl;

             h13_1->SetBinContent(j,QuadraticSum_l_13);
             h13_1->SetLineColor(kBlue-9);
             h13_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h13_2 = new TH1F("h13_2","Quadratic Sum from right",20,0,3.5); //right
          
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
         float B_r_13_9 = 0;
          
         float QuadraticSum_r_13 = 0;
         float Sum_r_13 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_13 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_13 << endl;
            B_r_13_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_13_9 << endl;
            B_r_13_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_13_8 << endl;
            B_r_13_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_13_7 << endl;
            B_r_13_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_13_6 << endl;
            B_r_13_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_13_5 << endl;
            B_r_13_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_13_4 << endl;
            B_r_13_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_13_3 << endl;
            B_r_13_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_13_2 << endl;
            B_r_13_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_13_1 << endl;
            B_r_13_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_13_0 << endl;
            
            float B_r_13 = 0;
            for(int i = 0; i<10; i++) { B_r_13 += h_hist[i]->GetBinContent(j); }
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

            h13_2->SetBinContent(j,QuadraticSum_r_13);
            h13_2->SetLineColor(kGreen-9);
            h13_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg13->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg13->AddEntry(h13_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg13->AddEntry(h13_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg13->Draw();
          
          c13 -> SaveAs("TauPhi_SM.pdf");
        
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="LepPhi>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs14 = new THStack("hs14", "");
          for(int i= 0; i<10 ; i++){ hs14->Add(h_hist[i], "hist14"); }
          hs14->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h14_1 = new TH1F("h14_1","Quadratic Sum from left",20,0,3.5); //left
          
         float S_l_14 = 0;
         float B_l_14_0 = 0;
         float B_l_14_1 = 0;
         float B_l_14_2 = 0;
         float B_l_14_3 = 0;
         float B_l_14_4 = 0;
         float B_l_14_5 = 0;
         float B_l_14_6 = 0;
         float B_l_14_7 = 0;
         float B_l_14_8 = 0;
         float B_l_14_9 = 0;
          
         float QuadraticSum_l_14 = 0;
         float Sum_l_14 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_14 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_14 << endl;
             B_l_14_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_14_9 << endl;
             B_l_14_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_14_8 << endl;
             B_l_14_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_14_7 << endl;
             B_l_14_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_14_6 << endl;
             B_l_14_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_14_5 << endl;
             B_l_14_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_14_4 << endl;
             B_l_14_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_14_3 << endl;
             B_l_14_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_14_2 << endl;
             B_l_14_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_14_1 << endl;
             B_l_14_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_14_0 << endl;
             
             float B_l_14 = 0;
             for(int i = 0; i<10; i++) { B_l_14 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_14 << endl;
             
             float Bin_l_14 = 0;
             if (B_l_14 > 0){
                 Bin_l_14 =  2* ( (S_l_14 + B_l_14) * log(1+S_l_14/B_l_14) - S_l_14 );
                 //Bin_l_14 = (S_l_14/sqrt(B_l_14))*(S_l_14/sqrt(B_l_14));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_14) << endl; //
             

             Sum_l_14 += Bin_l_14 ;
             QuadraticSum_l_14 = sqrt(Sum_l_14);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_14 << endl;

             h14_1->SetBinContent(j,QuadraticSum_l_14);
             h14_1->SetLineColor(kBlue-9);
             h14_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h14_2 = new TH1F("h14_2","Quadratic Sum from right",20,0,3.5); //right
          
         float S_r_14 = 0;
         float B_r_14_0 = 0;
         float B_r_14_1 = 0;
         float B_r_14_2 = 0;
         float B_r_14_3 = 0;
         float B_r_14_4 = 0;
         float B_r_14_5 = 0;
         float B_r_14_6 = 0;
         float B_r_14_7 = 0;
         float B_r_14_8 = 0;
         float B_r_14_9 = 0;
          
         float QuadraticSum_r_14 = 0;
         float Sum_r_14 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_14 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_14 << endl;
            B_r_14_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_14_9 << endl;
            B_r_14_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_14_8 << endl;
            B_r_14_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_14_7 << endl;
            B_r_14_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_14_6 << endl;
            B_r_14_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_14_5 << endl;
            B_r_14_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_14_4 << endl;
            B_r_14_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_14_3 << endl;
            B_r_14_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_14_2 << endl;
            B_r_14_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_14_1 << endl;
            B_r_14_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_14_0 << endl;
            
            float B_r_14 = 0;
            for(int i = 0; i<10; i++) { B_r_14 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_14 << endl;
            
            float Bin_r_14 = 0;
            if (B_r_14 > 0){
                Bin_r_14 =  2* ( (S_r_14 + B_r_14) * log(1+S_r_14/B_r_14) - S_r_14 );
                //Bin_r_14 = (S_r_14/sqrt(B_r_14))*(S_r_14/sqrt(B_r_14));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_14) << endl;
            

            Sum_r_14 += Bin_r_14 ;
            QuadraticSum_r_14 = sqrt(Sum_r_14);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_14 << endl;

            h14_2->SetBinContent(j,QuadraticSum_r_14);
            h14_2->SetLineColor(kGreen-9);
            h14_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg14->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg14->AddEntry(h14_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg14->AddEntry(h14_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg14->Draw();
          
          c14 -> SaveAs("LepPhi_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 6000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dEtaLepTau>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs15 = new THStack("hs15", "");
          for(int i= 0; i<10 ; i++){ hs15->Add(h_hist[i], "hist15"); }
          hs15->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h15_1 = new TH1F("h15_1","Quadratic Sum from left",25,0,5); //left
          
         float S_l_15 = 0;
         float B_l_15_0 = 0;
         float B_l_15_1 = 0;
         float B_l_15_2 = 0;
         float B_l_15_3 = 0;
         float B_l_15_4 = 0;
         float B_l_15_5 = 0;
         float B_l_15_6 = 0;
         float B_l_15_7 = 0;
         float B_l_15_8 = 0;
         float B_l_15_9 = 0;
          
         float QuadraticSum_l_15 = 0;
         float Sum_l_15 = 0;
           
          for (int j=1; j<=25; j++) {
              
             S_l_15 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_15 << endl;
             B_l_15_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_15_9 << endl;
             B_l_15_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_15_8 << endl;
             B_l_15_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_15_7 << endl;
             B_l_15_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_15_6 << endl;
             B_l_15_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_15_5 << endl;
             B_l_15_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_15_4 << endl;
             B_l_15_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_15_3 << endl;
             B_l_15_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_15_2 << endl;
             B_l_15_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_15_1 << endl;
             B_l_15_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_15_0 << endl;
             
             float B_l_15 = 0;
             for(int i = 0; i<10; i++) { B_l_15 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_15 << endl;
             
             float Bin_l_15 = 0;
             if (B_l_15 > 0){
                 Bin_l_15 =  2* ( (S_l_15 + B_l_15) * log(1+S_l_15/B_l_15) - S_l_15 );
                 //Bin_l_15 = (S_l_15/sqrt(B_l_15))*(S_l_15/sqrt(B_l_15));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_15) << endl; //
             

             Sum_l_15 += Bin_l_15 ;
             QuadraticSum_l_15 = sqrt(Sum_l_15);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_15 << endl;

             h15_1->SetBinContent(j,QuadraticSum_l_15);
             h15_1->SetLineColor(kBlue-9);
             h15_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h15_2 = new TH1F("h15_2","Quadratic Sum from right",25,0,5); //right
          
         float S_r_15 = 0;
         float B_r_15_0 = 0;
         float B_r_15_1 = 0;
         float B_r_15_2 = 0;
         float B_r_15_3 = 0;
         float B_r_15_4 = 0;
         float B_r_15_5 = 0;
         float B_r_15_6 = 0;
         float B_r_15_7 = 0;
         float B_r_15_8 = 0;
         float B_r_15_9 = 0;
          
         float QuadraticSum_r_15 = 0;
         float Sum_r_15 = 0;
          
          for (int j=25; j>=1; j--) {
              
            S_r_15 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_15 << endl;
            B_r_15_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_15_9 << endl;
            B_r_15_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_15_8 << endl;
            B_r_15_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_15_7 << endl;
            B_r_15_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_15_6 << endl;
            B_r_15_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_15_5 << endl;
            B_r_15_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_15_4 << endl;
            B_r_15_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_15_3 << endl;
            B_r_15_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_15_2 << endl;
            B_r_15_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_15_1 << endl;
            B_r_15_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_15_0 << endl;
            
            float B_r_15 = 0;
            for(int i = 0; i<10; i++) { B_r_15 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_15 << endl;
            
            float Bin_r_15 = 0;
            if (B_r_15 > 0){
                Bin_r_15 =  2* ( (S_r_15 + B_r_15) * log(1+S_r_15/B_r_15) - S_r_15 );
                //Bin_r_15 = (S_r_15/sqrt(B_r_15))*(S_r_15/sqrt(B_r_15));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_15) << endl;
            

            Sum_r_15 += Bin_r_15 ;
            QuadraticSum_r_15 = sqrt(Sum_r_15);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_15 << endl;

            h15_2->SetBinContent(j,QuadraticSum_r_15);
            h15_2->SetLineColor(kGreen-9);
            h15_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax15 = 1.1*h15_1->GetMaximum();
          float scale15 = 6000 / rightmax15;
          h15_1->Scale(scale15);
          h15_1->Draw("SAMEHIST");
          
          h15_2->Scale(scale15);
          h15_2->Draw("SAMEHIST");
          
        
          TGaxis*axis15 = new TGaxis(5,0,5,6000,0,rightmax15,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg15->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg15->AddEntry(h15_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg15->AddEntry(h15_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg15->Draw();
          
          c15 -> SaveAs("dEtaLepTau_SM.pdf");
        
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="TauEta>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs16 = new THStack("hs16", "");
          for(int i= 0; i<10 ; i++){ hs16->Add(h_hist[i], "hist16"); }
          hs16->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h16_1 = new TH1F("h16_1","Quadratic Sum from left",25,-2.5,2.5); //left
          
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
         float B_l_16_9 = 0;
          
         float QuadraticSum_l_16 = 0;
         float Sum_l_16 = 0;
           
          for (int j=1; j<=25; j++) {
              
             S_l_16 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_16 << endl;
             B_l_16_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_16_9 << endl;
             B_l_16_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_16_8 << endl;
             B_l_16_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_16_7 << endl;
             B_l_16_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_16_6 << endl;
             B_l_16_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_16_5 << endl;
             B_l_16_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_16_4 << endl;
             B_l_16_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_16_3 << endl;
             B_l_16_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_16_2 << endl;
             B_l_16_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_16_1 << endl;
             B_l_16_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_16_0 << endl;
             
             float B_l_16 = 0;
             for(int i = 0; i<10; i++) { B_l_16 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_16 << endl;

             h16_1->SetBinContent(j,QuadraticSum_l_16);
             h16_1->SetLineColor(kBlue-9);
             h16_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h16_2 = new TH1F("h16_2","Quadratic Sum from right",25,-2.5,2.5); //right
          
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
         float B_r_16_9 = 0;
          
         float QuadraticSum_r_16 = 0;
         float Sum_r_16 = 0;
          
          for (int j=25; j>=1; j--) {
              
            S_r_16 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_16 << endl;
            B_r_16_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_16_9 << endl;
            B_r_16_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_16_8 << endl;
            B_r_16_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_16_7 << endl;
            B_r_16_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_16_6 << endl;
            B_r_16_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_16_5 << endl;
            B_r_16_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_16_4 << endl;
            B_r_16_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_16_3 << endl;
            B_r_16_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_16_2 << endl;
            B_r_16_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_16_1 << endl;
            B_r_16_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_16_0 << endl;
            
            float B_r_16 = 0;
            for(int i = 0; i<10; i++) { B_r_16 += h_hist[i]->GetBinContent(j); }
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

            h16_2->SetBinContent(j,QuadraticSum_r_16);
            h16_2->SetLineColor(kGreen-9);
            h16_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg16->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg16->AddEntry(h16_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg16->AddEntry(h16_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg16->Draw();
          
          c16 -> SaveAs("TauEta_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 3000); //1200
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="LepEta>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs17 = new THStack("hs17", "");
          for(int i= 0; i<10 ; i++){ hs17->Add(h_hist[i], "hist17"); }
          hs17->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h17_1 = new TH1F("h17_1","Quadratic Sum from left",30,-3,3); //left
          
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
         float B_l_17_9 = 0;
          
         float QuadraticSum_l_17 = 0;
         float Sum_l_17 = 0;
           
          for (int j=1; j<=30; j++) {
              
             S_l_17 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_17 << endl;
             B_l_17_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_17_9 << endl;
             B_l_17_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_17_8 << endl;
             B_l_17_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_17_7 << endl;
             B_l_17_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_17_6 << endl;
             B_l_17_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_17_5 << endl;
             B_l_17_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_17_4 << endl;
             B_l_17_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_17_3 << endl;
             B_l_17_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_17_2 << endl;
             B_l_17_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_17_1 << endl;
             B_l_17_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_17_0 << endl;
             
             float B_l_17 = 0;
             for(int i = 0; i<10; i++) { B_l_17 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_17 << endl;

             h17_1->SetBinContent(j,QuadraticSum_l_17);
             h17_1->SetLineColor(kBlue-9);
             h17_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h17_2 = new TH1F("h17_2","Quadratic Sum from right",30,-3,3); //right
          
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
         float B_r_17_9 = 0;
          
         float QuadraticSum_r_17 = 0;
         float Sum_r_17 = 0;
          
          for (int j=30; j>=1; j--) {
              
            S_r_17 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_17 << endl;
            B_r_17_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_17_9 << endl;
            B_r_17_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_17_8 << endl;
            B_r_17_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_17_7 << endl;
            B_r_17_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_17_6 << endl;
            B_r_17_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_17_5 << endl;
            B_r_17_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_17_4 << endl;
            B_r_17_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_17_3 << endl;
            B_r_17_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_17_2 << endl;
            B_r_17_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_17_1 << endl;
            B_r_17_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_17_0 << endl;
            
            float B_r_17 = 0;
            for(int i = 0; i<10; i++) { B_r_17 += h_hist[i]->GetBinContent(j); }
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

            h17_2->SetBinContent(j,QuadraticSum_r_17);
            h17_2->SetLineColor(kGreen-9);
            h17_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg17->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg17->AddEntry(h17_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg17->AddEntry(h17_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg17->Draw();
          
          c17 -> SaveAs("LepEta_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 4500); //2000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dRLepTau>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs18 = new THStack("hs18", "");
          for(int i= 0; i<10 ; i++){ hs18->Add(h_hist[i], "hist18"); }
          hs18->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h18_1 = new TH1F("h18_1","Quadratic Sum from left",30,0,6); //left
          
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
         float B_l_18_9 = 0;
          
         float QuadraticSum_l_18 = 0;
         float Sum_l_18 = 0;
           
          for (int j=1; j<=30; j++) {
              
             S_l_18 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_18 << endl;
             B_l_18_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_18_9 << endl;
             B_l_18_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_18_8 << endl;
             B_l_18_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_18_7 << endl;
             B_l_18_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_18_6 << endl;
             B_l_18_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_18_5 << endl;
             B_l_18_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_18_4 << endl;
             B_l_18_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_18_3 << endl;
             B_l_18_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_18_2 << endl;
             B_l_18_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_18_1 << endl;
             B_l_18_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_18_0 << endl;
             
             float B_l_18 = 0;
             for(int i = 0; i<10; i++) { B_l_18 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_18 << endl;

             h18_1->SetBinContent(j,QuadraticSum_l_18);
             h18_1->SetLineColor(kBlue-9);
             h18_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h18_2 = new TH1F("h18_2","Quadratic Sum from right",30,0,6); //right
          
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
         float B_r_18_9 = 0;
          
         float QuadraticSum_r_18 = 0;
         float Sum_r_18 = 0;
          
          for (int j=30; j>=1; j--) {
              
            S_r_18 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_18 << endl;
            B_r_18_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_18_9 << endl;
            B_r_18_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_18_8 << endl;
            B_r_18_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_18_7 << endl;
            B_r_18_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_18_6 << endl;
            B_r_18_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_18_5 << endl;
            B_r_18_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_18_4 << endl;
            B_r_18_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_18_3 << endl;
            B_r_18_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_18_2 << endl;
            B_r_18_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_18_1 << endl;
            B_r_18_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_18_0 << endl;
            
            float B_r_18 = 0;
            for(int i = 0; i<10; i++) { B_r_18 += h_hist[i]->GetBinContent(j); }
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

            h18_2->SetBinContent(j,QuadraticSum_r_18);
            h18_2->SetLineColor(kGreen-9);
            h18_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg18->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg18->AddEntry(h18_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg18->AddEntry(h18_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg18->Draw();
          
          c18 -> SaveAs("dRLepTau_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",35,0,700);
            h_hist[i]->GetXaxis()->SetTitle("m_{T}^{2} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 10000); //5000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="MT2*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs20 = new THStack("hs20", "");
          for(int i= 0; i<10 ; i++){ hs20->Add(h_hist[i], "hist20"); }
          hs20->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h20_1 = new TH1F("h20_1","Quadratic Sum from left",35,0,700); //left
          
         float S_l_20 = 0;
         float B_l_20_0 = 0;
         float B_l_20_1 = 0;
         float B_l_20_2 = 0;
         float B_l_20_3 = 0;
         float B_l_20_4 = 0;
         float B_l_20_5 = 0;
         float B_l_20_6 = 0;
         float B_l_20_7 = 0;
         float B_l_20_8 = 0;
         float B_l_20_9 = 0;
          
         float QuadraticSum_l_20 = 0;
         float Sum_l_20 = 0;
           
          for (int j=1; j<=35; j++) {
              
             S_l_20 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_20 << endl;
             B_l_20_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_20_9 << endl;
             B_l_20_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_20_8 << endl;
             B_l_20_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_20_7 << endl;
             B_l_20_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_20_6 << endl;
             B_l_20_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_20_5 << endl;
             B_l_20_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_20_4 << endl;
             B_l_20_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_20_3 << endl;
             B_l_20_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_20_2 << endl;
             B_l_20_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_20_1 << endl;
             B_l_20_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_20_0 << endl;
             
             float B_l_20 = 0;
             for(int i = 0; i<10; i++) { B_l_20 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_20 << endl;
             
             float Bin_l_20 = 0;
             if (B_l_20 > 0){
                 Bin_l_20 =  2* ( (S_l_20 + B_l_20) * log(1+S_l_20/B_l_20) - S_l_20 );
                 //Bin_l_20 = (S_l_20/sqrt(B_l_20))*(S_l_20/sqrt(B_l_20));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_20) << endl; //
             

             Sum_l_20 += Bin_l_20 ;
             QuadraticSum_l_20 = sqrt(Sum_l_20);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_20 << endl;

             h20_1->SetBinContent(j,QuadraticSum_l_20);
             h20_1->SetLineColor(kBlue-9);
             h20_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h20_2 = new TH1F("h20_2","Quadratic Sum from right",35,0,700); //right
          
         float S_r_20 = 0;
         float B_r_20_0 = 0;
         float B_r_20_1 = 0;
         float B_r_20_2 = 0;
         float B_r_20_3 = 0;
         float B_r_20_4 = 0;
         float B_r_20_5 = 0;
         float B_r_20_6 = 0;
         float B_r_20_7 = 0;
         float B_r_20_8 = 0;
         float B_r_20_9 = 0;
          
         float QuadraticSum_r_20 = 0;
         float Sum_r_20 = 0;
          
          for (int j=35; j>=1; j--) {
              
            S_r_20 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_20 << endl;
            B_r_20_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_20_9 << endl;
            B_r_20_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_20_8 << endl;
            B_r_20_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_20_7 << endl;
            B_r_20_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_20_6 << endl;
            B_r_20_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_20_5 << endl;
            B_r_20_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_20_4 << endl;
            B_r_20_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_20_3 << endl;
            B_r_20_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_20_2 << endl;
            B_r_20_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_20_1 << endl;
            B_r_20_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_20_0 << endl;
            
            float B_r_20 = 0;
            for(int i = 0; i<10; i++) { B_r_20 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_20 << endl;
            
            float Bin_r_20 = 0;
            if (B_r_20 > 0){
                Bin_r_20 =  2* ( (S_r_20 + B_r_20) * log(1+S_r_20/B_r_20) - S_r_20 );
                //Bin_r_20 = (S_r_20/sqrt(B_r_20))*(S_r_20/sqrt(B_r_20));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_20) << endl;
            

            Sum_r_20 += Bin_r_20 ;
            QuadraticSum_r_20 = sqrt(Sum_r_20);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_20 << endl;

            h20_2->SetBinContent(j,QuadraticSum_r_20);
            h20_2->SetLineColor(kGreen-9);
            h20_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax20 = 1.1*h20_1->GetMaximum();
          float scale20 = 10000 / rightmax20;
          h20_1->Scale(scale20);
          h20_1->Draw("SAMEHIST");
          
          h20_2->Scale(scale20);
          h20_2->Draw("SAMEHIST");
          
        
          TGaxis*axis20 = new TGaxis(700,0,700,10000,0,rightmax20,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg20->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg20->AddEntry(h20_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg20->AddEntry(h20_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg20->Draw();
          
          c20 -> SaveAs("MT2_SM.pdf");
        
        
        //   ===========================================================   pTVBFj1   ===========================================================
          
          TCanvas *c21 = new TCanvas ("c21", "pTVBFj1",980,580);
            
          TPad *pad211 = new TPad("pad211","",0,0,0.75,1);
          TPad *pad212 = new TPad("pad212","",0.73,0,1,1);
          pad211->Draw();
          pad212->Draw();
            
          pad211->cd();
          pad211->SetTickx();
          gStyle->SetOptStat(kFALSE);
          
          for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",43,0,860);
            h_hist[i]->GetXaxis()->SetTitle("VBF p_{T}^{j1} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 [GeV]");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 850);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 8000); //4000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="pTVBFj1*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs21 = new THStack("hs21", "");
          for(int i= 0; i<10 ; i++){ hs21->Add(h_hist[i], "hist21"); }
          hs21->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h21_1 = new TH1F("h21_1","Quadratic Sum from left",43,0,860); //left
          
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
         float B_l_21_9 = 0;
          
         float QuadraticSum_l_21 = 0;
         float Sum_l_21 = 0;
           
          for (int j=1; j<=43; j++) {
              
             S_l_21 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_21 << endl;
             B_l_21_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_21_9 << endl;
             B_l_21_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_21_8 << endl;
             B_l_21_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_21_7 << endl;
             B_l_21_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_21_6 << endl;
             B_l_21_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_21_5 << endl;
             B_l_21_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_21_4 << endl;
             B_l_21_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_21_3 << endl;
             B_l_21_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_21_2 << endl;
             B_l_21_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_21_1 << endl;
             B_l_21_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_21_0 << endl;
             
             float B_l_21 = 0;
             for(int i = 0; i<10; i++) { B_l_21 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_21 << endl;

             h21_1->SetBinContent(j,QuadraticSum_l_21);
             h21_1->SetLineColor(kBlue-9);
             h21_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h21_2 = new TH1F("h21_2","Quadratic Sum from right",43,0,860); //right
          
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
         float B_r_21_9 = 0;
          
         float QuadraticSum_r_21 = 0;
         float Sum_r_21 = 0;
          
          for (int j=43; j>=1; j--) {
              
            S_r_21 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_21 << endl;
            B_r_21_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_21_9 << endl;
            B_r_21_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_21_8 << endl;
            B_r_21_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_21_7 << endl;
            B_r_21_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_21_6 << endl;
            B_r_21_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_21_5 << endl;
            B_r_21_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_21_4 << endl;
            B_r_21_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_21_3 << endl;
            B_r_21_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_21_2 << endl;
            B_r_21_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_21_1 << endl;
            B_r_21_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_21_0 << endl;
            
            float B_r_21 = 0;
            for(int i = 0; i<10; i++) { B_r_21 += h_hist[i]->GetBinContent(j); }
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

            h21_2->SetBinContent(j,QuadraticSum_r_21);
            h21_2->SetLineColor(kGreen-9);
            h21_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax21 = 1.1*h21_1->GetMaximum();
          float scale21 = 8000 / rightmax21;
          h21_1->Scale(scale21);
          h21_1->Draw("SAMEHIST");
          
          h21_2->Scale(scale21);
          h21_2->Draw("SAMEHIST");
          
        
          TGaxis*axis21 = new TGaxis(860,0,860,8000,0,rightmax21,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg21->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg21->AddEntry(h21_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg21->AddEntry(h21_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg21->Draw();
          
          c21 -> SaveAs("pTVBFj1_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",36,0,360);
            h_hist[i]->GetXaxis()->SetTitle("VBF p_{T}^{j2} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 10 [GeV]");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 350);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 15000); //6500
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="pTVBFj2*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs22 = new THStack("hs22", "");
          for(int i= 0; i<10 ; i++){ hs22->Add(h_hist[i], "hist22"); }
          hs22->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h22_1 = new TH1F("h22_1","Quadratic Sum from left",36,0,360); //left
          
         float S_l_22 = 0;
         float B_l_22_0 = 0;
         float B_l_22_1 = 0;
         float B_l_22_2 = 0;
         float B_l_22_3 = 0;
         float B_l_22_4 = 0;
         float B_l_22_5 = 0;
         float B_l_22_6 = 0;
         float B_l_22_7 = 0;
         float B_l_22_8 = 0;
         float B_l_22_9 = 0;
          
         float QuadraticSum_l_22 = 0;
         float Sum_l_22 = 0;
           
          for (int j=1; j<=36; j++) {
              
             S_l_22 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_22 << endl;
             B_l_22_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_22_9 << endl;
             B_l_22_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_22_8 << endl;
             B_l_22_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_22_7 << endl;
             B_l_22_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_22_6 << endl;
             B_l_22_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_22_5 << endl;
             B_l_22_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_22_4 << endl;
             B_l_22_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_22_3 << endl;
             B_l_22_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_22_2 << endl;
             B_l_22_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_22_1 << endl;
             B_l_22_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_22_0 << endl;
             
             float B_l_22 = 0;
             for(int i = 0; i<10; i++) { B_l_22 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_22 << endl;
             
             float Bin_l_22 = 0;
             if (B_l_22 > 0){
                 Bin_l_22 =  2* ( (S_l_22 + B_l_22) * log(1+S_l_22/B_l_22) - S_l_22 );
                 //Bin_l_22 = (S_l_22/sqrt(B_l_22))*(S_l_22/sqrt(B_l_22));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_22) << endl; //
             

             Sum_l_22 += Bin_l_22 ;
             QuadraticSum_l_22 = sqrt(Sum_l_22);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_22 << endl;

             h22_1->SetBinContent(j,QuadraticSum_l_22);
             h22_1->SetLineColor(kBlue-9);
             h22_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h22_2 = new TH1F("h22_2","Quadratic Sum from right",36,0,360); //right
          
         float S_r_22 = 0;
         float B_r_22_0 = 0;
         float B_r_22_1 = 0;
         float B_r_22_2 = 0;
         float B_r_22_3 = 0;
         float B_r_22_4 = 0;
         float B_r_22_5 = 0;
         float B_r_22_6 = 0;
         float B_r_22_7 = 0;
         float B_r_22_8 = 0;
         float B_r_22_9 = 0;
          
         float QuadraticSum_r_22 = 0;
         float Sum_r_22 = 0;
          
          for (int j=36; j>=1; j--) {
              
            S_r_22 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_22 << endl;
            B_r_22_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_22_9 << endl;
            B_r_22_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_22_8 << endl;
            B_r_22_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_22_7 << endl;
            B_r_22_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_22_6 << endl;
            B_r_22_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_22_5 << endl;
            B_r_22_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_22_4 << endl;
            B_r_22_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_22_3 << endl;
            B_r_22_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_22_2 << endl;
            B_r_22_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_22_1 << endl;
            B_r_22_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_22_0 << endl;
            
            float B_r_22 = 0;
            for(int i = 0; i<10; i++) { B_r_22 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_22 << endl;
            
            float Bin_r_22 = 0;
            if (B_r_22 > 0){
                Bin_r_22 =  2* ( (S_r_22 + B_r_22) * log(1+S_r_22/B_r_22) - S_r_22 );
                //Bin_r_22 = (S_r_22/sqrt(B_r_22))*(S_r_22/sqrt(B_r_22));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_22) << endl;
            

            Sum_r_22 += Bin_r_22 ;
            QuadraticSum_r_22 = sqrt(Sum_r_22);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_22 << endl;

            h22_2->SetBinContent(j,QuadraticSum_r_22);
            h22_2->SetLineColor(kGreen-9);
            h22_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax22 = 1.1*h22_1->GetMaximum();
          float scale22 = 15000 / rightmax22;
          h22_1->Scale(scale22);
          h22_1->Draw("SAMEHIST");
          
          h22_2->Scale(scale22);
          h22_2->Draw("SAMEHIST");
          
        
          TGaxis*axis22 = new TGaxis(360,0,360,15000,0,rightmax22,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg22->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg22->AddEntry(h22_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg22->AddEntry(h22_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg22->Draw();
          
          c22 -> SaveAs("pTVBFj2_SM.pdf");
        
        
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
            h_hist[i] = new TH1F(h_nm, "",33,0,6600);
            h_hist[i]->GetXaxis()->SetTitle("VBF m_{jj} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 200 [GeV]");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 13000); //6000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="mVBFjj*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs23 = new THStack("hs23", "");
          for(int i= 0; i<10 ; i++){ hs23->Add(h_hist[i], "hist23"); }
          hs23->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h23_1 = new TH1F("h23_1","Quadratic Sum from left",33,0,6600); //left
          
         float S_l_23 = 0;
         float B_l_23_0 = 0;
         float B_l_23_1 = 0;
         float B_l_23_2 = 0;
         float B_l_23_3 = 0;
         float B_l_23_4 = 0;
         float B_l_23_5 = 0;
         float B_l_23_6 = 0;
         float B_l_23_7 = 0;
         float B_l_23_8 = 0;
         float B_l_23_9 = 0;
          
         float QuadraticSum_l_23 = 0;
         float Sum_l_23 = 0;
           
          for (int j=1; j<=33; j++) {
              
             S_l_23 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_23 << endl;
             B_l_23_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_23_9 << endl;
             B_l_23_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_23_8 << endl;
             B_l_23_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_23_7 << endl;
             B_l_23_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_23_6 << endl;
             B_l_23_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_23_5 << endl;
             B_l_23_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_23_4 << endl;
             B_l_23_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_23_3 << endl;
             B_l_23_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_23_2 << endl;
             B_l_23_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_23_1 << endl;
             B_l_23_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_23_0 << endl;
             
             float B_l_23 = 0;
             for(int i = 0; i<10; i++) { B_l_23 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_23 << endl;
             
             float Bin_l_23 = 0;
             if (B_l_23 > 0){
                 Bin_l_23 =  2* ( (S_l_23 + B_l_23) * log(1+S_l_23/B_l_23) - S_l_23 );
                 //Bin_l_23 = (S_l_23/sqrt(B_l_23))*(S_l_23/sqrt(B_l_23));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_23) << endl; //
             

             Sum_l_23 += Bin_l_23 ;
             QuadraticSum_l_23 = sqrt(Sum_l_23);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_23 << endl;

             h23_1->SetBinContent(j,QuadraticSum_l_23);
             h23_1->SetLineColor(kBlue-9);
             h23_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h23_2 = new TH1F("h23_2","Quadratic Sum from right",33,0,6600); //right
          
         float S_r_23 = 0;
         float B_r_23_0 = 0;
         float B_r_23_1 = 0;
         float B_r_23_2 = 0;
         float B_r_23_3 = 0;
         float B_r_23_4 = 0;
         float B_r_23_5 = 0;
         float B_r_23_6 = 0;
         float B_r_23_7 = 0;
         float B_r_23_8 = 0;
         float B_r_23_9 = 0;
          
         float QuadraticSum_r_23 = 0;
         float Sum_r_23 = 0;
          
          for (int j=33; j>=1; j--) {
              
            S_r_23 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_23 << endl;
            B_r_23_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_23_9 << endl;
            B_r_23_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_23_8 << endl;
            B_r_23_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_23_7 << endl;
            B_r_23_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_23_6 << endl;
            B_r_23_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_23_5 << endl;
            B_r_23_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_23_4 << endl;
            B_r_23_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_23_3 << endl;
            B_r_23_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_23_2 << endl;
            B_r_23_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_23_1 << endl;
            B_r_23_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_23_0 << endl;
            
            float B_r_23 = 0;
            for(int i = 0; i<10; i++) { B_r_23 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_23 << endl;
            
            float Bin_r_23 = 0;
            if (B_r_23 > 0){
                Bin_r_23 =  2* ( (S_r_23 + B_r_23) * log(1+S_r_23/B_r_23) - S_r_23 );
                //Bin_r_23 = (S_r_23/sqrt(B_r_23))*(S_r_23/sqrt(B_r_23));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_23) << endl;
            

            Sum_r_23 += Bin_r_23 ;
            QuadraticSum_r_23 = sqrt(Sum_r_23);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_23 << endl;

            h23_2->SetBinContent(j,QuadraticSum_r_23);
            h23_2->SetLineColor(kGreen-9);
            h23_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax23 = 1.1*h23_1->GetMaximum();
          float scale23 = 13000 / rightmax23;
          h23_1->Scale(scale23);
          h23_1->Draw("SAMEHIST");
          
          h23_2->Scale(scale23);
          h23_2->Draw("SAMEHIST");
          
        
          TGaxis*axis23 = new TGaxis(6600,0,6600,13000,0,rightmax23,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg23->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg23->AddEntry(h23_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg23->AddEntry(h23_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg23->Draw();
          
          c23 -> SaveAs("mVBFjj_SM.pdf");
       
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="phiVBFj1>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs24 = new THStack("hs24", "");
          for(int i= 0; i<10 ; i++){ hs24->Add(h_hist[i], "hist24"); }
          hs24->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h24_1 = new TH1F("h24_1","Quadratic Sum from left",35,-3.5,3.5); //left
          
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
         float B_l_24_9 = 0;
          
         float QuadraticSum_l_24 = 0;
         float Sum_l_24 = 0;
           
          for (int j=1; j<=35; j++) {
              
             S_l_24 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_24 << endl;
             B_l_24_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_24_9 << endl;
             B_l_24_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_24_8 << endl;
             B_l_24_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_24_7 << endl;
             B_l_24_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_24_6 << endl;
             B_l_24_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_24_5 << endl;
             B_l_24_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_24_4 << endl;
             B_l_24_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_24_3 << endl;
             B_l_24_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_24_2 << endl;
             B_l_24_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_24_1 << endl;
             B_l_24_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_24_0 << endl;
             
             float B_l_24 = 0;
             for(int i = 0; i<10; i++) { B_l_24 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_24 << endl;

             h24_1->SetBinContent(j,QuadraticSum_l_24);
             h24_1->SetLineColor(kBlue-9);
             h24_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h24_2 = new TH1F("h24_2","Quadratic Sum from right",35,-3.5,3.5); //right
          
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
         float B_r_24_9 = 0;
          
         float QuadraticSum_r_24 = 0;
         float Sum_r_24 = 0;
          
          for (int j=35; j>=1; j--) {
              
            S_r_24 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_24 << endl;
            B_r_24_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_24_9 << endl;
            B_r_24_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_24_8 << endl;
            B_r_24_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_24_7 << endl;
            B_r_24_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_24_6 << endl;
            B_r_24_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_24_5 << endl;
            B_r_24_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_24_4 << endl;
            B_r_24_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_24_3 << endl;
            B_r_24_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_24_2 << endl;
            B_r_24_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_24_1 << endl;
            B_r_24_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_24_0 << endl;
            
            float B_r_24 = 0;
            for(int i = 0; i<10; i++) { B_r_24 += h_hist[i]->GetBinContent(j); }
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

            h24_2->SetBinContent(j,QuadraticSum_r_24);
            h24_2->SetLineColor(kGreen-9);
            h24_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg24->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg24->AddEntry(h24_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg24->AddEntry(h24_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg24->Draw();
          
          c24 -> SaveAs("phiVBFj1_SM.pdf");
        
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="phiVBFj2>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs25 = new THStack("hs25", "");
          for(int i= 0; i<10 ; i++){ hs25->Add(h_hist[i], "hist25"); }
          hs25->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h25_1 = new TH1F("h25_1","Quadratic Sum from left",35,-3.5,3.5); //left
          
         float S_l_25 = 0;
         float B_l_25_0 = 0;
         float B_l_25_1 = 0;
         float B_l_25_2 = 0;
         float B_l_25_3 = 0;
         float B_l_25_4 = 0;
         float B_l_25_5 = 0;
         float B_l_25_6 = 0;
         float B_l_25_7 = 0;
         float B_l_25_8 = 0;
         float B_l_25_9 = 0;
          
         float QuadraticSum_l_25 = 0;
         float Sum_l_25 = 0;
           
          for (int j=1; j<=35; j++) {
              
             S_l_25 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_25 << endl;
             B_l_25_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_25_9 << endl;
             B_l_25_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_25_8 << endl;
             B_l_25_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_25_7 << endl;
             B_l_25_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_25_6 << endl;
             B_l_25_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_25_5 << endl;
             B_l_25_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_25_4 << endl;
             B_l_25_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_25_3 << endl;
             B_l_25_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_25_2 << endl;
             B_l_25_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_25_1 << endl;
             B_l_25_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_25_0 << endl;
             
             float B_l_25 = 0;
             for(int i = 0; i<10; i++) { B_l_25 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_25 << endl;
             
             float Bin_l_25 = 0;
             if (B_l_25 > 0){
                 Bin_l_25 =  2* ( (S_l_25 + B_l_25) * log(1+S_l_25/B_l_25) - S_l_25 );
                 //Bin_l_25 = (S_l_25/sqrt(B_l_25))*(S_l_25/sqrt(B_l_25));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_25) << endl; //
             

             Sum_l_25 += Bin_l_25 ;
             QuadraticSum_l_25 = sqrt(Sum_l_25);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_25 << endl;

             h25_1->SetBinContent(j,QuadraticSum_l_25);
             h25_1->SetLineColor(kBlue-9);
             h25_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h25_2 = new TH1F("h25_2","Quadratic Sum from right",35,-3.5,3.5); //right
          
         float S_r_25 = 0;
         float B_r_25_0 = 0;
         float B_r_25_1 = 0;
         float B_r_25_2 = 0;
         float B_r_25_3 = 0;
         float B_r_25_4 = 0;
         float B_r_25_5 = 0;
         float B_r_25_6 = 0;
         float B_r_25_7 = 0;
         float B_r_25_8 = 0;
         float B_r_25_9 = 0;
          
         float QuadraticSum_r_25 = 0;
         float Sum_r_25 = 0;
          
          for (int j=35; j>=1; j--) {
              
            S_r_25 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_25 << endl;
            B_r_25_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_25_9 << endl;
            B_r_25_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_25_8 << endl;
            B_r_25_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_25_7 << endl;
            B_r_25_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_25_6 << endl;
            B_r_25_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_25_5 << endl;
            B_r_25_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_25_4 << endl;
            B_r_25_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_25_3 << endl;
            B_r_25_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_25_2 << endl;
            B_r_25_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_25_1 << endl;
            B_r_25_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_25_0 << endl;
            
            float B_r_25 = 0;
            for(int i = 0; i<10; i++) { B_r_25 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_25 << endl;
            
            float Bin_r_25 = 0;
            if (B_r_25 > 0){
                Bin_r_25 =  2* ( (S_r_25 + B_r_25) * log(1+S_r_25/B_r_25) - S_r_25 );
                //Bin_r_25 = (S_r_25/sqrt(B_r_25))*(S_r_25/sqrt(B_r_25));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_25) << endl;
            

            Sum_r_25 += Bin_r_25 ;
            QuadraticSum_r_25 = sqrt(Sum_r_25);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_25 << endl;

            h25_2->SetBinContent(j,QuadraticSum_r_25);
            h25_2->SetLineColor(kGreen-9);
            h25_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg25->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg25->AddEntry(h25_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg25->AddEntry(h25_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg25->Draw();
          
          c25 -> SaveAs("phiVBFj2_SM.pdf");
        

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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 4500); //2200
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dEtaVBFjj>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs26 = new THStack("hs26", "");
          for(int i= 0; i<10 ; i++){ hs26->Add(h_hist[i], "hist26"); }
          hs26->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h26_1 = new TH1F("h26_1","Quadratic Sum from left",20,0,10); //left
          
         float S_l_26 = 0;
         float B_l_26_0 = 0;
         float B_l_26_1 = 0;
         float B_l_26_2 = 0;
         float B_l_26_3 = 0;
         float B_l_26_4 = 0;
         float B_l_26_5 = 0;
         float B_l_26_6 = 0;
         float B_l_26_7 = 0;
         float B_l_26_8 = 0;
         float B_l_26_9 = 0;
          
         float QuadraticSum_l_26 = 0;
         float Sum_l_26 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_26 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_26 << endl;
             B_l_26_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_26_9 << endl;
             B_l_26_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_26_8 << endl;
             B_l_26_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_26_7 << endl;
             B_l_26_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_26_6 << endl;
             B_l_26_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_26_5 << endl;
             B_l_26_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_26_4 << endl;
             B_l_26_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_26_3 << endl;
             B_l_26_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_26_2 << endl;
             B_l_26_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_26_1 << endl;
             B_l_26_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_26_0 << endl;
             
             float B_l_26 = 0;
             for(int i = 0; i<10; i++) { B_l_26 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_26 << endl;
             
             float Bin_l_26 = 0;
             if (B_l_26 > 0){
                 Bin_l_26 =  2* ( (S_l_26 + B_l_26) * log(1+S_l_26/B_l_26) - S_l_26 );
                 //Bin_l_26 = (S_l_26/sqrt(B_l_26))*(S_l_26/sqrt(B_l_26));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_26) << endl; //
             

             Sum_l_26 += Bin_l_26 ;
             QuadraticSum_l_26 = sqrt(Sum_l_26);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_26 << endl;

             h26_1->SetBinContent(j,QuadraticSum_l_26);
             h26_1->SetLineColor(kBlue-9);
             h26_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h26_2 = new TH1F("h26_2","Quadratic Sum from right",20,0,10); //right
          
         float S_r_26 = 0;
         float B_r_26_0 = 0;
         float B_r_26_1 = 0;
         float B_r_26_2 = 0;
         float B_r_26_3 = 0;
         float B_r_26_4 = 0;
         float B_r_26_5 = 0;
         float B_r_26_6 = 0;
         float B_r_26_7 = 0;
         float B_r_26_8 = 0;
         float B_r_26_9 = 0;
          
         float QuadraticSum_r_26 = 0;
         float Sum_r_26 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_26 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_26 << endl;
            B_r_26_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_26_9 << endl;
            B_r_26_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_26_8 << endl;
            B_r_26_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_26_7 << endl;
            B_r_26_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_26_6 << endl;
            B_r_26_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_26_5 << endl;
            B_r_26_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_26_4 << endl;
            B_r_26_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_26_3 << endl;
            B_r_26_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_26_2 << endl;
            B_r_26_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_26_1 << endl;
            B_r_26_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_26_0 << endl;
            
            float B_r_26 = 0;
            for(int i = 0; i<10; i++) { B_r_26 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_26 << endl;
            
            float Bin_r_26 = 0;
            if (B_r_26 > 0){
                Bin_r_26 =  2* ( (S_r_26 + B_r_26) * log(1+S_r_26/B_r_26) - S_r_26 );
                //Bin_r_26 = (S_r_26/sqrt(B_r_26))*(S_r_26/sqrt(B_r_26));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_26) << endl;
            

            Sum_r_26 += Bin_r_26 ;
            QuadraticSum_r_26 = sqrt(Sum_r_26);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_26 << endl;

            h26_2->SetBinContent(j,QuadraticSum_r_26);
            h26_2->SetLineColor(kGreen-9);
            h26_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg26->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg26->AddEntry(h26_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg26->AddEntry(h26_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg26->Draw();
          
          c26 -> SaveAs("dEtaVBFjj_SM.pdf");
        
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="etaVBFj1>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs27 = new THStack("hs27", "");
          for(int i= 0; i<10 ; i++){ hs27->Add(h_hist[i], "hist27"); }
          hs27->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h27_1 = new TH1F("h27_1","Quadratic Sum from left",21,-5.04,5.04); //left
          
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
         float B_l_27_9 = 0;
          
         float QuadraticSum_l_27 = 0;
         float Sum_l_27 = 0;
           
          for (int j=1; j<=21; j++) {
              
             S_l_27 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_27 << endl;
             B_l_27_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_27_9 << endl;
             B_l_27_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_27_8 << endl;
             B_l_27_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_27_7 << endl;
             B_l_27_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_27_6 << endl;
             B_l_27_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_27_5 << endl;
             B_l_27_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_27_4 << endl;
             B_l_27_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_27_3 << endl;
             B_l_27_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_27_2 << endl;
             B_l_27_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_27_1 << endl;
             B_l_27_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_27_0 << endl;
             
             float B_l_27 = 0;
             for(int i = 0; i<10; i++) { B_l_27 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_27 << endl;

             h27_1->SetBinContent(j,QuadraticSum_l_27);
             h27_1->SetLineColor(kBlue-9);
             h27_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h27_2 = new TH1F("h27_2","Quadratic Sum from right",21,-5.04,5.04); //right
          
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
         float B_r_27_9 = 0;
          
         float QuadraticSum_r_27 = 0;
         float Sum_r_27 = 0;
          
          for (int j=21; j>=1; j--) {
              
            S_r_27 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_27 << endl;
            B_r_27_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_27_9 << endl;
            B_r_27_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_27_8 << endl;
            B_r_27_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_27_7 << endl;
            B_r_27_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_27_6 << endl;
            B_r_27_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_27_5 << endl;
            B_r_27_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_27_4 << endl;
            B_r_27_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_27_3 << endl;
            B_r_27_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_27_2 << endl;
            B_r_27_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_27_1 << endl;
            B_r_27_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_27_0 << endl;
            
            float B_r_27 = 0;
            for(int i = 0; i<10; i++) { B_r_27 += h_hist[i]->GetBinContent(j); }
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

            h27_2->SetBinContent(j,QuadraticSum_r_27);
            h27_2->SetLineColor(kGreen-9);
            h27_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg27->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg27->AddEntry(h27_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg27->AddEntry(h27_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg27->Draw();
          
          c27 -> SaveAs("etaVBFj1_SM.pdf");
        
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="etaVBFj2>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs28 = new THStack("hs28", "");
          for(int i= 0; i<10 ; i++){ hs28->Add(h_hist[i], "hist28"); }
          hs28->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h28_1 = new TH1F("h28_1","Quadratic Sum from left",21,-5.04,5.04); //left
          
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
         float B_l_28_9 = 0;
          
         float QuadraticSum_l_28 = 0;
         float Sum_l_28 = 0;
           
          for (int j=1; j<=21; j++) {
              
             S_l_28 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_28 << endl;
             B_l_28_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_28_9 << endl;
             B_l_28_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_28_8 << endl;
             B_l_28_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_28_7 << endl;
             B_l_28_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_28_6 << endl;
             B_l_28_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_28_5 << endl;
             B_l_28_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_28_4 << endl;
             B_l_28_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_28_3 << endl;
             B_l_28_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_28_2 << endl;
             B_l_28_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_28_1 << endl;
             B_l_28_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_28_0 << endl;
             
             float B_l_28 = 0;
             for(int i = 0; i<10; i++) { B_l_28 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_28 << endl;

             h28_1->SetBinContent(j,QuadraticSum_l_28);
             h28_1->SetLineColor(kBlue-9);
             h28_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h28_2 = new TH1F("h28_2","Quadratic Sum from right",21,-5.04,5.04); //right
          
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
         float B_r_28_9 = 0;
          
         float QuadraticSum_r_28 = 0;
         float Sum_r_28 = 0;
          
          for (int j=21; j>=1; j--) {
              
            S_r_28 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_28 << endl;
            B_r_28_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_28_9 << endl;
            B_r_28_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_28_8 << endl;
            B_r_28_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_28_7 << endl;
            B_r_28_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_28_6 << endl;
            B_r_28_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_28_5 << endl;
            B_r_28_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_28_4 << endl;
            B_r_28_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_28_3 << endl;
            B_r_28_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_28_2 << endl;
            B_r_28_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_28_1 << endl;
            B_r_28_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_28_0 << endl;
            
            float B_r_28 = 0;
            for(int i = 0; i<10; i++) { B_r_28 += h_hist[i]->GetBinContent(j); }
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

            h28_2->SetBinContent(j,QuadraticSum_r_28);
            h28_2->SetLineColor(kGreen-9);
            h28_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg28->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg28->AddEntry(h28_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg28->AddEntry(h28_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg28->Draw();
          
          c28 -> SaveAs("etaVBFj2_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 4500); //2200
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dRVBFjj>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs29 = new THStack("hs29", "");
          for(int i= 0; i<10 ; i++){ hs29->Add(h_hist[i], "hist29"); }
          hs29->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h29_1 = new TH1F("h29_1","Quadratic Sum from left",25,0,10); //left
          
         float S_l_29 = 0;
         float B_l_29_0 = 0;
         float B_l_29_1 = 0;
         float B_l_29_2 = 0;
         float B_l_29_3 = 0;
         float B_l_29_4 = 0;
         float B_l_29_5 = 0;
         float B_l_29_6 = 0;
         float B_l_29_7 = 0;
         float B_l_29_8 = 0;
         float B_l_29_9 = 0;
          
         float QuadraticSum_l_29 = 0;
         float Sum_l_29 = 0;
           
          for (int j=1; j<=25; j++) {
              
             S_l_29 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_29 << endl;
             B_l_29_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_29_9 << endl;
             B_l_29_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_29_8 << endl;
             B_l_29_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_29_7 << endl;
             B_l_29_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_29_6 << endl;
             B_l_29_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_29_5 << endl;
             B_l_29_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_29_4 << endl;
             B_l_29_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_29_3 << endl;
             B_l_29_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_29_2 << endl;
             B_l_29_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_29_1 << endl;
             B_l_29_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_29_0 << endl;
             
             float B_l_29 = 0;
             for(int i = 0; i<10; i++) { B_l_29 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_29 << endl;
             
             float Bin_l_29 = 0;
             if (B_l_29 > 0){
                 Bin_l_29 =  2* ( (S_l_29 + B_l_29) * log(1+S_l_29/B_l_29) - S_l_29 );
                 //Bin_l_29 = (S_l_29/sqrt(B_l_29))*(S_l_29/sqrt(B_l_29));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_29) << endl; //
             

             Sum_l_29 += Bin_l_29 ;
             QuadraticSum_l_29 = sqrt(Sum_l_29);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_29 << endl;

             h29_1->SetBinContent(j,QuadraticSum_l_29);
             h29_1->SetLineColor(kBlue-9);
             h29_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h29_2 = new TH1F("h29_2","Quadratic Sum from right",25,0,10); //right
          
         float S_r_29 = 0;
         float B_r_29_0 = 0;
         float B_r_29_1 = 0;
         float B_r_29_2 = 0;
         float B_r_29_3 = 0;
         float B_r_29_4 = 0;
         float B_r_29_5 = 0;
         float B_r_29_6 = 0;
         float B_r_29_7 = 0;
         float B_r_29_8 = 0;
         float B_r_29_9 = 0;
          
         float QuadraticSum_r_29 = 0;
         float Sum_r_29 = 0;
          
          for (int j=25; j>=1; j--) {
              
            S_r_29 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_29 << endl;
            B_r_29_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_29_9 << endl;
            B_r_29_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_29_8 << endl;
            B_r_29_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_29_7 << endl;
            B_r_29_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_29_6 << endl;
            B_r_29_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_29_5 << endl;
            B_r_29_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_29_4 << endl;
            B_r_29_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_29_3 << endl;
            B_r_29_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_29_2 << endl;
            B_r_29_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_29_1 << endl;
            B_r_29_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_29_0 << endl;
            
            float B_r_29 = 0;
            for(int i = 0; i<10; i++) { B_r_29 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_29 << endl;
            
            float Bin_r_29 = 0;
            if (B_r_29 > 0){
                Bin_r_29 =  2* ( (S_r_29 + B_r_29) * log(1+S_r_29/B_r_29) - S_r_29 );
                //Bin_r_29 = (S_r_29/sqrt(B_r_29))*(S_r_29/sqrt(B_r_29));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_29) << endl;
            

            Sum_r_29 += Bin_r_29 ;
            QuadraticSum_r_29 = sqrt(Sum_r_29);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_29 << endl;

            h29_2->SetBinContent(j,QuadraticSum_r_29);
            h29_2->SetLineColor(kGreen-9);
            h29_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg29->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg29->AddEntry(h29_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg29->AddEntry(h29_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg29->Draw();
          
          c29 -> SaveAs("dRVBFjj_SM.pdf");
        
        
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
              h_hist[i] = new TH1F(h_nm, "",35,0,700);
            h_hist[i]->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 700);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 8000); //4000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="MET*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs30 = new THStack("hs30", "");
          for(int i= 0; i<10 ; i++){ hs30->Add(h_hist[i], "hist30"); }
          hs30->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h30_1 = new TH1F("h30_1","Quadratic Sum from left",35,0,700); //left
          
         float S_l_30 = 0;
         float B_l_30_0 = 0;
         float B_l_30_1 = 0;
         float B_l_30_2 = 0;
         float B_l_30_3 = 0;
         float B_l_30_4 = 0;
         float B_l_30_5 = 0;
         float B_l_30_6 = 0;
         float B_l_30_7 = 0;
         float B_l_30_8 = 0;
         float B_l_30_9 = 0;
          
         float QuadraticSum_l_30 = 0;
         float Sum_l_30 = 0;
           
          for (int j=1; j<=35; j++) {
              
             S_l_30 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_30 << endl;
             B_l_30_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_30_9 << endl;
             B_l_30_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_30_8 << endl;
             B_l_30_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_30_7 << endl;
             B_l_30_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_30_6 << endl;
             B_l_30_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_30_5 << endl;
             B_l_30_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_30_4 << endl;
             B_l_30_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_30_3 << endl;
             B_l_30_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_30_2 << endl;
             B_l_30_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_30_1 << endl;
             B_l_30_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_30_0 << endl;
             
             float B_l_30 = 0;
             for(int i = 0; i<10; i++) { B_l_30 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_30 << endl;
             
             float Bin_l_30 = 0;
             if (B_l_30 > 0){
                 Bin_l_30 =  2* ( (S_l_30 + B_l_30) * log(1+S_l_30/B_l_30) - S_l_30 );
                 //Bin_l_30 = (S_l_30/sqrt(B_l_30))*(S_l_30/sqrt(B_l_30));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_30) << endl; //
             

             Sum_l_30 += Bin_l_30 ;
             QuadraticSum_l_30 = sqrt(Sum_l_30);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_30 << endl;

             h30_1->SetBinContent(j,QuadraticSum_l_30);
             h30_1->SetLineColor(kBlue-9);
             h30_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h30_2 = new TH1F("h30_2","Quadratic Sum from right",35,0,700); //right
          
         float S_r_30 = 0;
         float B_r_30_0 = 0;
         float B_r_30_1 = 0;
         float B_r_30_2 = 0;
         float B_r_30_3 = 0;
         float B_r_30_4 = 0;
         float B_r_30_5 = 0;
         float B_r_30_6 = 0;
         float B_r_30_7 = 0;
         float B_r_30_8 = 0;
         float B_r_30_9 = 0;
          
         float QuadraticSum_r_30 = 0;
         float Sum_r_30 = 0;
          
          for (int j=35; j>=1; j--) {
              
            S_r_30 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_30 << endl;
            B_r_30_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_30_9 << endl;
            B_r_30_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_30_8 << endl;
            B_r_30_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_30_7 << endl;
            B_r_30_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_30_6 << endl;
            B_r_30_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_30_5 << endl;
            B_r_30_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_30_4 << endl;
            B_r_30_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_30_3 << endl;
            B_r_30_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_30_2 << endl;
            B_r_30_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_30_1 << endl;
            B_r_30_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_30_0 << endl;
            
            float B_r_30 = 0;
            for(int i = 0; i<10; i++) { B_r_30 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_30 << endl;
            
            float Bin_r_30 = 0;
            if (B_r_30 > 0){
                Bin_r_30 =  2* ( (S_r_30 + B_r_30) * log(1+S_r_30/B_r_30) - S_r_30 );
                //Bin_r_30 = (S_r_30/sqrt(B_r_30))*(S_r_30/sqrt(B_r_30));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_30) << endl;
            

            Sum_r_30 += Bin_r_30 ;
            QuadraticSum_r_30 = sqrt(Sum_r_30);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_30 << endl;

            h30_2->SetBinContent(j,QuadraticSum_r_30);
            h30_2->SetLineColor(kGreen-9);
            h30_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax30 = 1.1*h30_1->GetMaximum();
          float scale30 = 8000 / rightmax30;
          h30_1->Scale(scale30);
          h30_1->Draw("SAMEHIST");
          
          h30_2->Scale(scale30);
          h30_2->Draw("SAMEHIST");
          
        
        TGaxis*axis30 = new TGaxis(700,0,700,8000,0,rightmax30,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg30->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg30->AddEntry(h30_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg30->AddEntry(h30_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg30->Draw();
          
          c30 -> SaveAs("MET_SM.pdf");
        
        
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="METCent>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs31 = new THStack("hs31", "");
          for(int i= 0; i<10 ; i++){ hs31->Add(h_hist[i], "hist31"); }
          hs31->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h31_1 = new TH1F("h31_1","Quadratic Sum from left",48,-1.5,1.5); //left
          
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
         float B_l_31_9 = 0;
          
         float QuadraticSum_l_31 = 0;
         float Sum_l_31 = 0;
           
          for (int j=1; j<=48; j++) {
              
             S_l_31 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_31 << endl;
             B_l_31_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_31_9 << endl;
             B_l_31_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_31_8 << endl;
             B_l_31_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_31_7 << endl;
             B_l_31_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_31_6 << endl;
             B_l_31_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_31_5 << endl;
             B_l_31_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_31_4 << endl;
             B_l_31_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_31_3 << endl;
             B_l_31_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_31_2 << endl;
             B_l_31_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_31_1 << endl;
             B_l_31_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_31_0 << endl;
             
             float B_l_31 = 0;
             for(int i = 0; i<10; i++) { B_l_31 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_31 << endl;

             h31_1->SetBinContent(j,QuadraticSum_l_31);
             h31_1->SetLineColor(kBlue-9);
             h31_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h31_2 = new TH1F("h31_2","Quadratic Sum from right",48,-1.5,1.5); //right
          
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
         float B_r_31_9 = 0;
          
         float QuadraticSum_r_31 = 0;
         float Sum_r_31 = 0;
          
          for (int j=48; j>=1; j--) {
              
            S_r_31 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_31 << endl;
            B_r_31_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_31_9 << endl;
            B_r_31_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_31_8 << endl;
            B_r_31_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_31_7 << endl;
            B_r_31_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_31_6 << endl;
            B_r_31_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_31_5 << endl;
            B_r_31_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_31_4 << endl;
            B_r_31_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_31_3 << endl;
            B_r_31_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_31_2 << endl;
            B_r_31_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_31_1 << endl;
            B_r_31_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_31_0 << endl;
            
            float B_r_31 = 0;
            for(int i = 0; i<10; i++) { B_r_31 += h_hist[i]->GetBinContent(j); }
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

            h31_2->SetBinContent(j,QuadraticSum_r_31);
            h31_2->SetLineColor(kGreen-9);
            h31_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg31->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg31->AddEntry(h31_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg31->AddEntry(h31_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg31->Draw();
          
          c31 -> SaveAs("METCent_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dPhiLep0MET>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs32 = new THStack("hs32", "");
          for(int i= 0; i<10 ; i++){ hs32->Add(h_hist[i], "hist32"); }
          hs32->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h32_1 = new TH1F("h32_1","Quadratic Sum from left",20,0,3.5); //left
          
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
         float B_l_32_9 = 0;
          
         float QuadraticSum_l_32 = 0;
         float Sum_l_32 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_32 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_32 << endl;
             B_l_32_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_32_9 << endl;
             B_l_32_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_32_8 << endl;
             B_l_32_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_32_7 << endl;
             B_l_32_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_32_6 << endl;
             B_l_32_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_32_5 << endl;
             B_l_32_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_32_4 << endl;
             B_l_32_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_32_3 << endl;
             B_l_32_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_32_2 << endl;
             B_l_32_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_32_1 << endl;
             B_l_32_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_32_0 << endl;
             
             float B_l_32 = 0;
             for(int i = 0; i<10; i++) { B_l_32 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_32 << endl;

             h32_1->SetBinContent(j,QuadraticSum_l_32);
             h32_1->SetLineColor(kBlue-9);
             h32_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h32_2 = new TH1F("h32_2","Quadratic Sum from right",20,0,3.5); //right
          
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
         float B_r_32_9 = 0;
          
         float QuadraticSum_r_32 = 0;
         float Sum_r_32 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_32 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_32 << endl;
            B_r_32_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_32_9 << endl;
            B_r_32_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_32_8 << endl;
            B_r_32_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_32_7 << endl;
            B_r_32_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_32_6 << endl;
            B_r_32_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_32_5 << endl;
            B_r_32_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_32_4 << endl;
            B_r_32_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_32_3 << endl;
            B_r_32_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_32_2 << endl;
            B_r_32_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_32_1 << endl;
            B_r_32_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_32_0 << endl;
            
            float B_r_32 = 0;
            for(int i = 0; i<10; i++) { B_r_32 += h_hist[i]->GetBinContent(j); }
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

            h32_2->SetBinContent(j,QuadraticSum_r_32);
            h32_2->SetLineColor(kGreen-9);
            h32_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax32 = 1.1*h32_1->GetMaximum();
          float scale32 = 10000 / rightmax32;
          h32_1->Scale(scale32);
          h32_1->Draw("SAMEHIST");
          
          h32_2->Scale(scale32);
          h32_2->Draw("SAMEHIST");
          
        
        TGaxis*axis32 = new TGaxis(3.5,0,3.5,10000,0,rightmax32,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg32->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg32->AddEntry(h32_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg32->AddEntry(h32_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg32->Draw();
          
          c32 -> SaveAs("dPhiLep0MET_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 4500);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dPhiLep1MET>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs33 = new THStack("hs33", "");
          for(int i= 0; i<10 ; i++){ hs33->Add(h_hist[i], "hist33"); }
          hs33->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h33_1 = new TH1F("h33_1","Quadratic Sum from left",20,0,3.5); //left
          
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
         float B_l_33_9 = 0;
          
         float QuadraticSum_l_33 = 0;
         float Sum_l_33 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_33 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_33 << endl;
             B_l_33_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_33_9 << endl;
             B_l_33_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_33_8 << endl;
             B_l_33_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_33_7 << endl;
             B_l_33_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_33_6 << endl;
             B_l_33_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_33_5 << endl;
             B_l_33_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_33_4 << endl;
             B_l_33_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_33_3 << endl;
             B_l_33_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_33_2 << endl;
             B_l_33_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_33_1 << endl;
             B_l_33_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_33_0 << endl;
             
             float B_l_33 = 0;
             for(int i = 0; i<10; i++) { B_l_33 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_33 << endl;

             h33_1->SetBinContent(j,QuadraticSum_l_33);
             h33_1->SetLineColor(kBlue-9);
             h33_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
         TH1F *h33_2 = new TH1F("h33_2","Quadratic Sum from right",20,0,3.5); //right
          
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
         float B_r_33_9 = 0;
          
         float QuadraticSum_r_33 = 0;
         float Sum_r_33 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_33 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_33 << endl;
            B_r_33_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_33_9 << endl;
            B_r_33_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_33_8 << endl;
            B_r_33_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_33_7 << endl;
            B_r_33_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_33_6 << endl;
            B_r_33_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_33_5 << endl;
            B_r_33_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_33_4 << endl;
            B_r_33_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_33_3 << endl;
            B_r_33_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_33_2 << endl;
            B_r_33_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_33_1 << endl;
            B_r_33_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_33_0 << endl;
            
            float B_r_33 = 0;
            for(int i = 0; i<10; i++) { B_r_33 += h_hist[i]->GetBinContent(j); }
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

            h33_2->SetBinContent(j,QuadraticSum_r_33);
            h33_2->SetLineColor(kGreen-9);
            h33_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax33 = 1.1*h33_1->GetMaximum();
          float scale33 = 4500 / rightmax33;
          h33_1->Scale(scale33);
          h33_1->Draw("SAMEHIST");
          
          h33_2->Scale(scale33);
          h33_2->Draw("SAMEHIST");
          
        
        TGaxis*axis33 = new TGaxis(3.5,0,3.5,4500,0,rightmax33,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg33->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg33->AddEntry(h33_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg33->AddEntry(h33_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg33->Draw();
          
          c33 -> SaveAs("dPhiLep1MET_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 13000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dPhiHttMET>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs34 = new THStack("hs34", "");
          for(int i= 0; i<10 ; i++){ hs34->Add(h_hist[i], "hist34"); }
          hs34->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h34_1 = new TH1F("h34_1","Quadratic Sum from left",20,0,3.5); //left
          
         float S_l_34 = 0;
         float B_l_34_0 = 0;
         float B_l_34_1 = 0;
         float B_l_34_2 = 0;
         float B_l_34_3 = 0;
         float B_l_34_4 = 0;
         float B_l_34_5 = 0;
         float B_l_34_6 = 0;
         float B_l_34_7 = 0;
         float B_l_34_8 = 0;
         float B_l_34_9 = 0;
          
         float QuadraticSum_l_34 = 0;
         float Sum_l_34 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_34 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_34 << endl;
             B_l_34_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_34_9 << endl;
             B_l_34_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_34_8 << endl;
             B_l_34_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_34_7 << endl;
             B_l_34_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_34_6 << endl;
             B_l_34_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_34_5 << endl;
             B_l_34_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_34_4 << endl;
             B_l_34_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_34_3 << endl;
             B_l_34_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_34_2 << endl;
             B_l_34_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_34_1 << endl;
             B_l_34_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_34_0 << endl;
             
             float B_l_34 = 0;
             for(int i = 0; i<10; i++) { B_l_34 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_34 << endl;
             
             float Bin_l_34 = 0;
             if (B_l_34 > 0){
                 Bin_l_34 =  2* ( (S_l_34 + B_l_34) * log(1+S_l_34/B_l_34) - S_l_34 );
                 //Bin_l_34 = (S_l_34/sqrt(B_l_34))*(S_l_34/sqrt(B_l_34));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_34) << endl; //
             

             Sum_l_34 += Bin_l_34 ;
             QuadraticSum_l_34 = sqrt(Sum_l_34);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_34 << endl;

             h34_1->SetBinContent(j,QuadraticSum_l_34);
             h34_1->SetLineColor(kBlue-9);
             h34_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h34_2 = new TH1F("h34_2","Quadratic Sum from right",20,0,3.5); //right
          
         float S_r_34 = 0;
         float B_r_34_0 = 0;
         float B_r_34_1 = 0;
         float B_r_34_2 = 0;
         float B_r_34_3 = 0;
         float B_r_34_4 = 0;
         float B_r_34_5 = 0;
         float B_r_34_6 = 0;
         float B_r_34_7 = 0;
         float B_r_34_8 = 0;
         float B_r_34_9 = 0;
          
         float QuadraticSum_r_34 = 0;
         float Sum_r_34 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_34 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_34 << endl;
            B_r_34_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_34_9 << endl;
            B_r_34_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_34_8 << endl;
            B_r_34_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_34_7 << endl;
            B_r_34_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_34_6 << endl;
            B_r_34_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_34_5 << endl;
            B_r_34_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_34_4 << endl;
            B_r_34_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_34_3 << endl;
            B_r_34_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_34_2 << endl;
            B_r_34_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_34_1 << endl;
            B_r_34_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_34_0 << endl;
            
            float B_r_34 = 0;
            for(int i = 0; i<10; i++) { B_r_34 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_34 << endl;
            
            float Bin_r_34 = 0;
            if (B_r_34 > 0){
                Bin_r_34 =  2* ( (S_r_34 + B_r_34) * log(1+S_r_34/B_r_34) - S_r_34 );
                //Bin_r_34 = (S_r_34/sqrt(B_r_34))*(S_r_34/sqrt(B_r_34));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_34) << endl;
            

            Sum_r_34 += Bin_r_34 ;
            QuadraticSum_r_34 = sqrt(Sum_r_34);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_34 << endl;

            h34_2->SetBinContent(j,QuadraticSum_r_34);
            h34_2->SetLineColor(kGreen-9);
            h34_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax34 = 1.1*h34_1->GetMaximum();
          float scale34 = 13000 / rightmax34;
          h34_1->Scale(scale34);
          h34_1->Draw("SAMEHIST");
          
          h34_2->Scale(scale34);
          h34_2->Draw("SAMEHIST");
          
        
        TGaxis*axis34 = new TGaxis(3.5,0,3.5,13000,0,rightmax34,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg34->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg34->AddEntry(h34_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg34->AddEntry(h34_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg34->Draw();
          
          c34 -> SaveAs("dPhiHttMET_SM.pdf");
        
     
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
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dPhiHbbMET>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs35 = new THStack("hs35", "");
          for(int i= 0; i<10 ; i++){ hs35->Add(h_hist[i], "hist35"); }
          hs35->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h35_1 = new TH1F("h35_1","Quadratic Sum from left",20,0,3.5); //left
          
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
         float B_l_35_9 = 0;
          
         float QuadraticSum_l_35 = 0;
         float Sum_l_35 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_35 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_35 << endl;
             B_l_35_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_35_9 << endl;
             B_l_35_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_35_8 << endl;
             B_l_35_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_35_7 << endl;
             B_l_35_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_35_6 << endl;
             B_l_35_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_35_5 << endl;
             B_l_35_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_35_4 << endl;
             B_l_35_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_35_3 << endl;
             B_l_35_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_35_2 << endl;
             B_l_35_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_35_1 << endl;
             B_l_35_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_35_0 << endl;
             
             float B_l_35 = 0;
             for(int i = 0; i<10; i++) { B_l_35 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_35 << endl;

             h35_1->SetBinContent(j,QuadraticSum_l_35);
             h35_1->SetLineColor(kBlue-9);
             h35_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h35_2 = new TH1F("h35_2","Quadratic Sum from right",20,0,3.5); //right
          
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
         float B_r_35_9 = 0;
          
         float QuadraticSum_r_35 = 0;
         float Sum_r_35 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_35 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_35 << endl;
            B_r_35_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_35_9 << endl;
            B_r_35_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_35_8 << endl;
            B_r_35_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_35_7 << endl;
            B_r_35_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_35_6 << endl;
            B_r_35_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_35_5 << endl;
            B_r_35_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_35_4 << endl;
            B_r_35_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_35_3 << endl;
            B_r_35_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_35_2 << endl;
            B_r_35_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_35_1 << endl;
            B_r_35_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_35_0 << endl;
            
            float B_r_35 = 0;
            for(int i = 0; i<10; i++) { B_r_35 += h_hist[i]->GetBinContent(j); }
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

            h35_2->SetBinContent(j,QuadraticSum_r_35);
            h35_2->SetLineColor(kGreen-9);
            h35_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg35->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg35->AddEntry(h35_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg35->AddEntry(h35_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg35->Draw();
          
          c35 -> SaveAs("dPhiHbbMET_SM.pdf");
           */
         
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
              h_hist[i] = new TH1F(h_nm, "",30,0,3000);
              h_hist[i]->GetXaxis()->SetTitle("m_{hh} [GeV]");
              h_hist[i]->GetYaxis()->SetTitle("Events/ 100 GeV");
              //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
              h_hist[i]->GetYaxis()->SetRangeUser(0, 16000); //16000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);


          for (int i=0; i<n_smp; i++){
              hist_draw[i]="Mhh*0.001>>"+h_title[i];
          }
    
          
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_ttbar
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs36 = new THStack("hs36", "");
          for(int i= 0; i<10 ; i++){ hs36->Add(h_hist[i], "hist36"); }
          hs36->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }
    
        

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h36_1 = new TH1F("h36_1","Quadratic Sum from left",30,0,3000); //left
        
         float QuadraticSum_l_36 = 0;
         float Sum_l_36 = 0;
         float QuadraticSum_dB_l_36 = 0;
         float Sum_dB_l_36 = 0;
           
          for (int j=1; j<=30; j++) {
              
             float S = h_hist[10]->GetBinContent(j);   //cout << " S of each bin = " << S << endl;
             float B_9 = h_hist[9]->GetBinContent(j);   //cout << " B of ttbar of each bin = " << B_9 << endl;
             float B_8 = h_hist[8]->GetBinContent(j);   //cout << " B of single top of each bin = " << B_8 << endl;
             float B_7 = h_hist[7]->GetBinContent(j);   //cout << " B of Ztt of each bin = " << B_7 << endl;
             float B_6 = h_hist[6]->GetBinContent(j);   //cout << " B of Wlv of each bin = " << B_6 << endl;
             float B_5 = h_hist[5]->GetBinContent(j);   //cout << " B of Z of each bin = " << B_5 << endl;
             float B_4 = h_hist[4]->GetBinContent(j);   //cout << " B of Fake_W of each bin = " << B_4 << endl;
             float B_3 = h_hist[3]->GetBinContent(j);   //cout << " B of Fake_ttbar of each bin = " << B_3 << endl;
             float B_2 = h_hist[2]->GetBinContent(j);   //cout << " B of DY of each bin = " << B_2 << endl;
             float B_1 = h_hist[1]->GetBinContent(j);   //cout << " B of diboson of each bin = " << B_1 << endl;
             float B_0 = h_hist[0]->GetBinContent(j);   //cout << " B of SMH of each bin = " << B_0 << endl;
              
             float error_9 = h_hist[9]->GetBinError(j);   //cout << " error of ttbar of each bin = " << error_9 << endl;
             float error_8 = h_hist[8]->GetBinError(j);   //cout << " error of single top of each bin = " << error_8 << endl;
             float error_7 = h_hist[7]->GetBinError(j);   //cout << " error of Ztt of each bin = " << error_7 << endl;
             float error_6 = h_hist[6]->GetBinError(j);   //cout << " error of Wlv of each bin = " << error_6 << endl;
             float error_5 = h_hist[5]->GetBinError(j);   //cout << " error of Z of each bin = " << error_5 << endl;
             float error_4 = h_hist[4]->GetBinError(j);   //cout << " error of Fake_W of each bin = " << error_4 << endl;
             float error_3 = h_hist[3]->GetBinError(j);   //cout << " error of Fake_ttbar of each bin = " << error_3 << endl;
             float error_2 = h_hist[2]->GetBinError(j);   //cout << " error of DY of each bin = " << error_2 << endl;
             float error_1 = h_hist[1]->GetBinError(j);   //cout << " error of diboson of each bin = " << error_1 << endl;
             float error_0 = h_hist[0]->GetBinError(j);   //cout << " error of SMH of each bin = " << error_0 << endl;
             
             float B = 0;   for(int i = 0; i<10; i++) { B += h_hist[i]->GetBinContent(j); }   //cout << " B of each bin = " << B << endl;
             float dB = 0;   for(int i = 0; i<10; i++) { dB += h_hist[i]->GetBinError(j); }   //cout << " Error of each bin = " << dB << endl;
             
              if( B > 0 && S > 0) {
                  
                  double R = 0;
                  if (B > 0){ R =  2* ( (S + B) * log(1+S/B) - S ); }
                  //if (B > 0){ B = (S/sqrt(B))*(S/sqrt(B)); }
                   
                   //cout << " Bin = " << j << endl;
                   //cout << " significance of each bin = " << sqrt(B) << endl;

                  
                  Sum_l_36 += R ;
                  QuadraticSum_l_36 = sqrt(Sum_l_36);
                  //cout << " Quadratic sum from left = " << QuadraticSum_l_36 << endl;
                   
                  Sum_dB_l_36 += dB ;
                  QuadraticSum_dB_l_36 = sqrt(Sum_dB_l_36);
                  //cout << " Quadratic sum from left = " << QuadraticSum_dB_l_36 << endl;
                  
              }
              
             h36_1->SetBinContent(j,QuadraticSum_l_36);
             h36_1->SetLineColor(kBlue-9);
             h36_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
          }
    
            cout << " Significance of Mhh = " << QuadraticSum_l_36 << endl;
            cout << " Uncertainty of Mhh = " << QuadraticSum_dB_l_36 << endl;
              

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h36_2 = new TH1F("h36_2","Quadratic Sum from right",30,0,3000); //right
          
         float QuadraticSum_r_36 = 0;
         float Sum_r_36 = 0;
         float QuadraticSum_dB_r_36 = 0;
         float Sum_dB_r_36 = 0;
         
          for (int j=30; j>=1; j--) {
            
            float S = h_hist[10]->GetBinContent(j);   //cout << " S of each bin = " << S << endl;
            float B_9 = h_hist[9]->GetBinContent(j);   //cout << " B of ttbar of each bin = " << B_9 << endl;
            float B_8 = h_hist[8]->GetBinContent(j);   //cout << " B of single top of each bin = " << B_8 << endl;
            float B_7 = h_hist[7]->GetBinContent(j);   //cout << " B of Ztt of each bin = " << B_7 << endl;
            float B_6 = h_hist[6]->GetBinContent(j);   //cout << " B of Wlv of each bin = " << B_6 << endl;
            float B_5 = h_hist[5]->GetBinContent(j);   //cout << " B of Z of each bin = " << B_5 << endl;
            float B_4 = h_hist[4]->GetBinContent(j);   //cout << " B of Fake_W of each bin = " << B_4 << endl;
            float B_3 = h_hist[3]->GetBinContent(j);   //cout << " B of Fake_ttbar of each bin = " << B_3 << endl;
            float B_2 = h_hist[2]->GetBinContent(j);   //cout << " B of DY of each bin = " << B_2 << endl;
            float B_1 = h_hist[1]->GetBinContent(j);   //cout << " B of diboson of each bin = " << B_1 << endl;
            float B_0 = h_hist[0]->GetBinContent(j);   //cout << " B of SMH of each bin = " << B_0 << endl;
             
            float error_9 = h_hist[9]->GetBinError(j);   //cout << " error of ttbar of each bin = " << error_9 << endl;
            float error_8 = h_hist[8]->GetBinError(j);   //cout << " error of single top of each bin = " << error_8 << endl;
            float error_7 = h_hist[7]->GetBinError(j);   //cout << " error of Ztt of each bin = " << error_7 << endl;
            float error_6 = h_hist[6]->GetBinError(j);   //cout << " error of Wlv of each bin = " << error_6 << endl;
            float error_5 = h_hist[5]->GetBinError(j);   //cout << " error of Z of each bin = " << error_5 << endl;
            float error_4 = h_hist[4]->GetBinError(j);   //cout << " error of Fake_W of each bin = " << error_4 << endl;
            float error_3 = h_hist[3]->GetBinError(j);   //cout << " error of Fake_ttbar of each bin = " << error_3 << endl;
            float error_2 = h_hist[2]->GetBinError(j);   //cout << " error of DY of each bin = " << error_2 << endl;
            float error_1 = h_hist[1]->GetBinError(j);   //cout << " error of diboson of each bin = " << error_1 << endl;
            float error_0 = h_hist[0]->GetBinError(j);   //cout << " error of SMH of each bin = " << error_0 << endl;
            
            float B = 0;   for(int i = 0; i<10; i++) { B += h_hist[i]->GetBinContent(j); }   //cout << " B of each bin = " << B << endl;
            float dB = 0;   for(int i = 0; i<10; i++) { dB += h_hist[i]->GetBinError(j); }   //cout << " Error of each bin = " << dB << endl;
            
             if( B > 0 && S > 0) {
                 
                  double R = 0;
                 
                 if (B > 0){ R =  2* ( (S + B) * log(1+S/B) - S ); }
                 //if (B > 0){ R = (S/sqrt(B))*(S/sqrt(B)); }
                  
                  //cout << " Bin = " << j << endl;
                  //cout << " significance of each bin = " << sqrt(R) << endl;

                 
                 Sum_r_36 += R ;
                 QuadraticSum_r_36 = sqrt(Sum_r_36);
                 //cout << " Quadratic sum from left = " << QuadraticSum_r_36 << endl;
                  
                 Sum_dB_r_36 += dB ;
                 QuadraticSum_dB_r_36 = sqrt(Sum_dB_r_36);
                 //cout << " Quadratic sum from left = " << QuadraticSum_dB_r_36 << endl;
                 
             }

            h36_2->SetBinContent(j,QuadraticSum_r_36);
            h36_2->SetLineColor(kGreen-9);
            h36_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax36 = 1.1*h36_1->GetMaximum();
          float scale36 = 16000 / rightmax36;
          h36_1->Scale(scale36);
          h36_1->Draw("SAMEHIST");
          
          h36_2->Scale(scale36);
          h36_2->Draw("SAMEHIST");
          
        
          TGaxis*axis36 = new TGaxis(3000,0,3000,16000,0,rightmax36,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--) { leg36->AddEntry(h_hist[i], h_titles[i].c_str()); }
          leg36->AddEntry(h36_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg36->AddEntry(h36_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg36->Draw();
          
        /*
             
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
              h_hist[i] = new TH1F(h_nm, "",50,0,2500);
              h_hist[i]->GetXaxis()->SetTitle("HT [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 6000); //3000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="HT*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs37 = new THStack("hs37", "");
          for(int i= 0; i<10 ; i++){ hs37->Add(h_hist[i], "hist37"); }
          hs37->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h37_1 = new TH1F("h37_1","Quadratic Sum from left",50,0,2500); //left
          
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
         float B_l_37_9 = 0;
          
         float QuadraticSum_l_37 = 0;
         float Sum_l_37 = 0;
           
          for (int j=1; j<=50; j++) {
              
             S_l_37 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_37 << endl;
             B_l_37_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_37_9 << endl;
             B_l_37_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_37_8 << endl;
             B_l_37_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_37_7 << endl;
             B_l_37_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_37_6 << endl;
             B_l_37_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_37_5 << endl;
             B_l_37_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_37_4 << endl;
             B_l_37_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_37_3 << endl;
             B_l_37_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_37_2 << endl;
             B_l_37_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_37_1 << endl;
             B_l_37_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_37_0 << endl;
             
             float B_l_37 = 0;
             for(int i = 0; i<10; i++) { B_l_37 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_37 << endl;

             h37_1->SetBinContent(j,QuadraticSum_l_37);
             h37_1->SetLineColor(kBlue-9);
             h37_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h37_2 = new TH1F("h37_2","Quadratic Sum from right",50,0,2500); //right
          
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
         float B_r_37_9 = 0;
          
         float QuadraticSum_r_37 = 0;
         float Sum_r_37 = 0;
          
          for (int j=50; j>=1; j--) {
              
            S_r_37 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_37 << endl;
            B_r_37_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_37_9 << endl;
            B_r_37_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_37_8 << endl;
            B_r_37_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_37_7 << endl;
            B_r_37_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_37_6 << endl;
            B_r_37_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_37_5 << endl;
            B_r_37_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_37_4 << endl;
            B_r_37_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_37_3 << endl;
            B_r_37_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_37_2 << endl;
            B_r_37_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_37_1 << endl;
            B_r_37_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_37_0 << endl;
            
            float B_r_37 = 0;
            for(int i = 0; i<10; i++) { B_r_37 += h_hist[i]->GetBinContent(j); }
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

            h37_2->SetBinContent(j,QuadraticSum_r_37);
            h37_2->SetLineColor(kGreen-9);
            h37_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax37 = 1.1*h37_1->GetMaximum();
          float scale37 = 6000 / rightmax37;
          h37_1->Scale(scale37);
          h37_1->Draw("SAMEHIST");
          
          h37_2->Scale(scale37);
          h37_2->Draw("SAMEHIST");
          
        
        TGaxis*axis37 = new TGaxis(2500,0,2500,6000,0,rightmax37,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg37->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg37->AddEntry(h37_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg37->AddEntry(h37_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg37->Draw();
          
          c37 -> SaveAs("HT_SM.pdf");
        
        
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
            h_hist[i]->GetYaxis()->SetRangeUser(0, 5000); //3000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dPhiHBB>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs38 = new THStack("hs38", "");
          for(int i= 0; i<10 ; i++){ hs38->Add(h_hist[i], "hist38"); }
          hs38->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h38_1 = new TH1F("h38_1","Quadratic Sum from left",20,0,3.5); //left
          
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
         float B_l_38_9 = 0;
          
         float QuadraticSum_l_38 = 0;
         float Sum_l_38 = 0;
           
          for (int j=1; j<=20; j++) {
              
             S_l_38 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_38 << endl;
             B_l_38_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_38_9 << endl;
             B_l_38_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_38_8 << endl;
             B_l_38_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_38_7 << endl;
             B_l_38_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_38_6 << endl;
             B_l_38_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_38_5 << endl;
             B_l_38_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_38_4 << endl;
             B_l_38_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_38_3 << endl;
             B_l_38_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_38_2 << endl;
             B_l_38_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_38_1 << endl;
             B_l_38_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_38_0 << endl;
             
             float B_l_38 = 0;
             for(int i = 0; i<10; i++) { B_l_38 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_38 << endl;

             h38_1->SetBinContent(j,QuadraticSum_l_38);
             h38_1->SetLineColor(kBlue-9);
             h38_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h38_2 = new TH1F("h38_2","Quadratic Sum from right",20,0,3.5); //right
          
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
         float B_r_38_9 = 0;
          
         float QuadraticSum_r_38 = 0;
         float Sum_r_38 = 0;
          
          for (int j=20; j>=1; j--) {
              
            S_r_38 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_38 << endl;
            B_r_38_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_38_9 << endl;
            B_r_38_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_38_8 << endl;
            B_r_38_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_38_7 << endl;
            B_r_38_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_38_6 << endl;
            B_r_38_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_38_5 << endl;
            B_r_38_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_38_4 << endl;
            B_r_38_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_38_3 << endl;
            B_r_38_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_38_2 << endl;
            B_r_38_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_38_1 << endl;
            B_r_38_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_38_0 << endl;
            
            float B_r_38 = 0;
            for(int i = 0; i<10; i++) { B_r_38 += h_hist[i]->GetBinContent(j); }
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

            h38_2->SetBinContent(j,QuadraticSum_r_38);
            h38_2->SetLineColor(kGreen-9);
            h38_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax38 = 1.1*h38_1->GetMaximum();
          float scale38 = 5000 / rightmax38;
          h38_1->Scale(scale38);
          h38_1->Draw("SAMEHIST");
          
          h38_2->Scale(scale38);
          h38_2->Draw("SAMEHIST");
          
        
        TGaxis*axis38 = new TGaxis(3.5,0,3.5,5000,0,rightmax38,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg38->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg38->AddEntry(h38_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg38->AddEntry(h38_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg38->Draw();
          
          c38 -> SaveAs("dPhiHBB_SM.pdf");
        
        
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
              h_hist[i] = new TH1F(h_nm, "",35,0,7);
              h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (H,BB)");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 7);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 5000); //2500
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dEtaHBB>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs39 = new THStack("hs39", "");
          for(int i= 0; i<10 ; i++){ hs39->Add(h_hist[i], "hist39"); }
          hs39->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h39_1 = new TH1F("h39_1","Quadratic Sum from left",35,0,7); //left
          
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
         float B_l_39_9 = 0;
          
         float QuadraticSum_l_39 = 0;
         float Sum_l_39 = 0;
           
          for (int j=1; j<=35; j++) {
              
             S_l_39 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_39 << endl;
             B_l_39_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_39_9 << endl;
             B_l_39_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_39_8 << endl;
             B_l_39_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_39_7 << endl;
             B_l_39_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_39_6 << endl;
             B_l_39_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_39_5 << endl;
             B_l_39_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_39_4 << endl;
             B_l_39_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_39_3 << endl;
             B_l_39_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_39_2 << endl;
             B_l_39_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_39_1 << endl;
             B_l_39_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_39_0 << endl;
             
             float B_l_39 = 0;
             for(int i = 0; i<10; i++) { B_l_39 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_39 << endl;

             h39_1->SetBinContent(j,QuadraticSum_l_39);
             h39_1->SetLineColor(kBlue-9);
             h39_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h39_2 = new TH1F("h39_2","Quadratic Sum from right",35,0,7); //right
          
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
         float B_r_39_9 = 0;
          
         float QuadraticSum_r_39 = 0;
         float Sum_r_39 = 0;
          
          for (int j=35; j>=1; j--) {
              
            S_r_39 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_39 << endl;
            B_r_39_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_39_9 << endl;
            B_r_39_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_39_8 << endl;
            B_r_39_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_39_7 << endl;
            B_r_39_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_39_6 << endl;
            B_r_39_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_39_5 << endl;
            B_r_39_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_39_4 << endl;
            B_r_39_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_39_3 << endl;
            B_r_39_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_39_2 << endl;
            B_r_39_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_39_1 << endl;
            B_r_39_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_39_0 << endl;
            
            float B_r_39 = 0;
            for(int i = 0; i<10; i++) { B_r_39 += h_hist[i]->GetBinContent(j); }
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

            h39_2->SetBinContent(j,QuadraticSum_r_39);
            h39_2->SetLineColor(kGreen-9);
            h39_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax39 = 1.1*h39_1->GetMaximum();
          float scale39 = 5000 / rightmax39;
          h39_1->Scale(scale39);
          h39_1->Draw("SAMEHIST");
          
          h39_2->Scale(scale39);
          h39_2->Draw("SAMEHIST");
          
        
        TGaxis*axis39 = new TGaxis(7,0,7,5000,0,rightmax39,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg39->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg39->AddEntry(h39_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg39->AddEntry(h39_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg39->Draw();
          
          c39 -> SaveAs("dEtaHBB_SM.pdf");
        
        
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
              h_hist[i] = new TH1F(h_nm, "",40,0,8);
              h_hist[i]->GetXaxis()->SetTitle("#DeltaR (H,H)");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 5000); //2500
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dRHH>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs40 = new THStack("hs40", "");
          for(int i= 0; i<10 ; i++){ hs40->Add(h_hist[i], "hist40"); }
          hs40->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h40_1 = new TH1F("h40_1","Quadratic Sum from left",40,0,8); //left
          
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
         float B_l_40_9 = 0;
          
         float QuadraticSum_l_40 = 0;
         float Sum_l_40 = 0;
           
          for (int j=1; j<=40; j++) {
              
             S_l_40 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_40 << endl;
             B_l_40_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_40_9 << endl;
             B_l_40_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_40_8 << endl;
             B_l_40_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_40_7 << endl;
             B_l_40_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_40_6 << endl;
             B_l_40_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_40_5 << endl;
             B_l_40_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_40_4 << endl;
             B_l_40_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_40_3 << endl;
             B_l_40_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_40_2 << endl;
             B_l_40_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_40_1 << endl;
             B_l_40_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_40_0 << endl;
             
             float B_l_40 = 0;
             for(int i = 0; i<10; i++) { B_l_40 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_40 << endl;

             h40_1->SetBinContent(j,QuadraticSum_l_40);
             h40_1->SetLineColor(kBlue-9);
             h40_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h40_2 = new TH1F("h40_2","Quadratic Sum from right",40,0,8); //right
          
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
         float B_r_40_9 = 0;
          
         float QuadraticSum_r_40 = 0;
         float Sum_r_40 = 0;
          
          for (int j=40; j>=1; j--) {
              
            S_r_40 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_40 << endl;
            B_r_40_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_40_9 << endl;
            B_r_40_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_40_8 << endl;
            B_r_40_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_40_7 << endl;
            B_r_40_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_40_6 << endl;
            B_r_40_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_40_5 << endl;
            B_r_40_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_40_4 << endl;
            B_r_40_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_40_3 << endl;
            B_r_40_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_40_2 << endl;
            B_r_40_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_40_1 << endl;
            B_r_40_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_40_0 << endl;
            
            float B_r_40 = 0;
            for(int i = 0; i<10; i++) { B_r_40 += h_hist[i]->GetBinContent(j); }
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

            h40_2->SetBinContent(j,QuadraticSum_r_40);
            h40_2->SetLineColor(kGreen-9);
            h40_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax40 = 1.1*h40_1->GetMaximum();
          float scale40 = 5000 / rightmax40;
          h40_1->Scale(scale40);
          h40_1->Draw("SAMEHIST");
          
          h40_2->Scale(scale40);
          h40_2->Draw("SAMEHIST");
          
        
        TGaxis*axis40 = new TGaxis(8,0,8,5000,0,rightmax40,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg40->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg40->AddEntry(h40_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg40->AddEntry(h40_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg40->Draw();
          
          c40 -> SaveAs("dRHH_SM.pdf");
        
        
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
              h_hist[i] = new TH1F(h_nm, "",30,0,300);
              h_hist[i]->GetXaxis()->SetTitle("M_{T}^{w} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 10 GeV");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 8500);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="MtW*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs41 = new THStack("hs41", "");
          for(int i= 0; i<10 ; i++){ hs41->Add(h_hist[i], "hist41"); }
          hs41->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h41_1 = new TH1F("h41_1","Quadratic Sum from left",30,0,300); //left
          
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
         float B_l_41_9 = 0;
          
         float QuadraticSum_l_41 = 0;
         float Sum_l_41 = 0;
           
          for (int j=1; j<=30; j++) {
              
             S_l_41 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_41 << endl;
             B_l_41_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_41_9 << endl;
             B_l_41_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_41_8 << endl;
             B_l_41_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_41_7 << endl;
             B_l_41_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_41_6 << endl;
             B_l_41_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_41_5 << endl;
             B_l_41_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_41_4 << endl;
             B_l_41_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_41_3 << endl;
             B_l_41_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_41_2 << endl;
             B_l_41_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_41_1 << endl;
             B_l_41_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_41_0 << endl;
             
             float B_l_41 = 0;
             for(int i = 0; i<10; i++) { B_l_41 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_41 << endl;

             h41_1->SetBinContent(j,QuadraticSum_l_41);
             h41_1->SetLineColor(kBlue-9);
             h41_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h41_2 = new TH1F("h41_2","Quadratic Sum from right",30,0,300); //right
          
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
         float B_r_41_9 = 0;
          
         float QuadraticSum_r_41 = 0;
         float Sum_r_41 = 0;
          
          for (int j=30; j>=1; j--) {
              
            S_r_41 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_41 << endl;
            B_r_41_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_41_9 << endl;
            B_r_41_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_41_8 << endl;
            B_r_41_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_41_7 << endl;
            B_r_41_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_41_6 << endl;
            B_r_41_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_41_5 << endl;
            B_r_41_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_41_4 << endl;
            B_r_41_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_41_3 << endl;
            B_r_41_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_41_2 << endl;
            B_r_41_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_41_1 << endl;
            B_r_41_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_41_0 << endl;
            
            float B_r_41 = 0;
            for(int i = 0; i<10; i++) { B_r_41 += h_hist[i]->GetBinContent(j); }
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

            h41_2->SetBinContent(j,QuadraticSum_r_41);
            h41_2->SetLineColor(kGreen-9);
            h41_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax41 = 1.1*h41_1->GetMaximum();
          float scale41 = 8500 / rightmax41;
          h41_1->Scale(scale41);
          h41_1->Draw("SAMEHIST");
          
          h41_2->Scale(scale41);
          h41_2->Draw("SAMEHIST");
          
        
        TGaxis*axis41 = new TGaxis(300,0,300,8500,0,rightmax41,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg41->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg41->AddEntry(h41_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg41->AddEntry(h41_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg41->Draw();
          
          c41 -> SaveAs("MtW_SM.pdf");
        
        
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
              h_hist[i] = new TH1F(h_nm, "",25,0,500);
              h_hist[i]->GetXaxis()->SetTitle("m_{vis} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 13000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="Mvis*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs42 = new THStack("hs42", "");
          for(int i= 0; i<10 ; i++){ hs42->Add(h_hist[i], "hist42"); }
          hs42->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h42_1 = new TH1F("h42_1","Quadratic Sum from left",25,0,500); //left
          
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
         float B_l_42_9 = 0;
          
         float QuadraticSum_l_42 = 0;
         float Sum_l_42 = 0;
           
          for (int j=1; j<=25; j++) {
              
             S_l_42 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_42 << endl;
             B_l_42_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_42_9 << endl;
             B_l_42_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_42_8 << endl;
             B_l_42_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_42_7 << endl;
             B_l_42_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_42_6 << endl;
             B_l_42_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_42_5 << endl;
             B_l_42_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_42_4 << endl;
             B_l_42_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_42_3 << endl;
             B_l_42_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_42_2 << endl;
             B_l_42_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_42_1 << endl;
             B_l_42_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_42_0 << endl;
             
             float B_l_42 = 0;
             for(int i = 0; i<10; i++) { B_l_42 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_42 << endl;

             h42_1->SetBinContent(j,QuadraticSum_l_42);
             h42_1->SetLineColor(kBlue-9);
             h42_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h42_2 = new TH1F("h42_2","Quadratic Sum from right",25,0,500); //right
          
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
         float B_r_42_9 = 0;
          
         float QuadraticSum_r_42 = 0;
         float Sum_r_42 = 0;
          
          for (int j=25; j>=1; j--) {
              
            S_r_42 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_42 << endl;
            B_r_42_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_42_9 << endl;
            B_r_42_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_42_8 << endl;
            B_r_42_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_42_7 << endl;
            B_r_42_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_42_6 << endl;
            B_r_42_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_42_5 << endl;
            B_r_42_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_42_4 << endl;
            B_r_42_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_42_3 << endl;
            B_r_42_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_42_2 << endl;
            B_r_42_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_42_1 << endl;
            B_r_42_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_42_0 << endl;
            
            float B_r_42 = 0;
            for(int i = 0; i<10; i++) { B_r_42 += h_hist[i]->GetBinContent(j); }
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

            h42_2->SetBinContent(j,QuadraticSum_r_42);
            h42_2->SetLineColor(kGreen-9);
            h42_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax42 = 1.1*h42_1->GetMaximum();
          float scale42 = 13000 / rightmax42;
          h42_1->Scale(scale42);
          h42_1->Draw("SAMEHIST");
          
          h42_2->Scale(scale42);
          h42_2->Draw("SAMEHIST");
          
        
        TGaxis*axis42 = new TGaxis(500,0,500,13000,0,rightmax42,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg42->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg42->AddEntry(h42_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg42->AddEntry(h42_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg42->Draw();
          
          c42 -> SaveAs("Mvis_SM.pdf");
        
        
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
              h_hist[i] = new TH1F(h_nm, "",45,0,900);
              h_hist[i]->GetXaxis()->SetTitle("m_{w} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 9000); //4000
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="Mw*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs43 = new THStack("hs43", "");
          for(int i= 0; i<10 ; i++){ hs43->Add(h_hist[i], "hist43"); }
          hs43->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h43_1 = new TH1F("h43_1","Quadratic Sum from left",45,0,900); //left
          
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
         float B_l_43_9 = 0;
          
         float QuadraticSum_l_43 = 0;
         float Sum_l_43 = 0;
           
          for (int j=1; j<=45; j++) {
              
             S_l_43 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_43 << endl;
             B_l_43_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_43_9 << endl;
             B_l_43_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_43_8 << endl;
             B_l_43_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_43_7 << endl;
             B_l_43_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_43_6 << endl;
             B_l_43_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_43_5 << endl;
             B_l_43_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_43_4 << endl;
             B_l_43_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_43_3 << endl;
             B_l_43_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_43_2 << endl;
             B_l_43_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_43_1 << endl;
             B_l_43_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_43_0 << endl;
             
             float B_l_43 = 0;
             for(int i = 0; i<10; i++) { B_l_43 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_43 << endl;

             h43_1->SetBinContent(j,QuadraticSum_l_43);
             h43_1->SetLineColor(kBlue-9);
             h43_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h43_2 = new TH1F("h43_2","Quadratic Sum from right",45,0,900); //right
          
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
         float B_r_43_9 = 0;
          
         float QuadraticSum_r_43 = 0;
         float Sum_r_43 = 0;
          
          for (int j=45; j>=1; j--) {
              
            S_r_43 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_43 << endl;
            B_r_43_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_43_9 << endl;
            B_r_43_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_43_8 << endl;
            B_r_43_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_43_7 << endl;
            B_r_43_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_43_6 << endl;
            B_r_43_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_43_5 << endl;
            B_r_43_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_43_4 << endl;
            B_r_43_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_43_3 << endl;
            B_r_43_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_43_2 << endl;
            B_r_43_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_43_1 << endl;
            B_r_43_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_43_0 << endl;
            
            float B_r_43 = 0;
            for(int i = 0; i<10; i++) { B_r_43 += h_hist[i]->GetBinContent(j); }
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

            h43_2->SetBinContent(j,QuadraticSum_r_43);
            h43_2->SetLineColor(kGreen-9);
            h43_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax43 = 1.1*h43_1->GetMaximum();
          float scale43 = 9000 / rightmax43;
          h43_1->Scale(scale43);
          h43_1->Draw("SAMEHIST");
          
          h43_2->Scale(scale43);
          h43_2->Draw("SAMEHIST");
          
        
          TGaxis*axis43 = new TGaxis(900,0,900,9000,0,rightmax43,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg43->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg43->AddEntry(h43_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg43->AddEntry(h43_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg43->Draw();
          
          c43 -> SaveAs("Mw_SM.pdf");
      
           
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
              h_hist[i] = new TH1F(h_nm, "",40,0,2000);
              h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 14000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="Mt*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs44 = new THStack("hs44", "");
          for(int i= 0; i<10 ; i++){ hs44->Add(h_hist[i], "hist44"); }
          hs44->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h44_1 = new TH1F("h44_1","Quadratic Sum from left",40,0,2000); //left
          
         float S_l_44 = 0;
         float B_l_44_0 = 0;
         float B_l_44_1 = 0;
         float B_l_44_2 = 0;
         float B_l_44_3 = 0;
         float B_l_44_4 = 0;
         float B_l_44_5 = 0;
         float B_l_44_6 = 0;
         float B_l_44_7 = 0;
         float B_l_44_8 = 0;
         float B_l_44_9 = 0;
          
         float QuadraticSum_l_44 = 0;
         float Sum_l_44 = 0;
           
          for (int j=1; j<=40; j++) {
              
             S_l_44 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_44 << endl;
             B_l_44_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_44_9 << endl;
             B_l_44_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_44_8 << endl;
             B_l_44_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_44_7 << endl;
             B_l_44_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_44_6 << endl;
             B_l_44_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_44_5 << endl;
             B_l_44_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_44_4 << endl;
             B_l_44_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_44_3 << endl;
             B_l_44_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_44_2 << endl;
             B_l_44_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_44_1 << endl;
             B_l_44_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_44_0 << endl;
             
             float B_l_44 = 0;
             for(int i = 0; i<10; i++) { B_l_44 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_44 << endl;
             
             
            float Bin_l_44 = 0;
            if (B_l_44 > 0){
                Bin_l_44 =  2* ( (S_l_44 + B_l_44) * log(1+S_l_44/B_l_44) - S_l_44 );
                //Bin_l_44 = (S_l_44/sqrt(B_l_44))*(S_l_44/sqrt(B_l_44));
                }
              
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_44) << endl; //
             

             Sum_l_44 += Bin_l_44 ;
             QuadraticSum_l_44 = sqrt(Sum_l_44);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_44 << endl;

             h44_1->SetBinContent(j,QuadraticSum_l_44);
             h44_1->SetLineColor(kBlue-9);
             h44_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h44_2 = new TH1F("h44_2","Quadratic Sum from right",40,0,2000); //right
          
         float S_r_44 = 0;
         float B_r_44_0 = 0;
         float B_r_44_1 = 0;
         float B_r_44_2 = 0;
         float B_r_44_3 = 0;
         float B_r_44_4 = 0;
         float B_r_44_5 = 0;
         float B_r_44_6 = 0;
         float B_r_44_7 = 0;
         float B_r_44_8 = 0;
         float B_r_44_9 = 0;
          
         float QuadraticSum_r_44 = 0;
         float Sum_r_44 = 0;
          
          for (int j=40; j>=1; j--) {
              
            S_r_44 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_44 << endl;
            B_r_44_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_44_9 << endl;
            B_r_44_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_44_8 << endl;
            B_r_44_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_44_7 << endl;
            B_r_44_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_44_6 << endl;
            B_r_44_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_44_5 << endl;
            B_r_44_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake of each bin = " << B_r_44_4 << endl;
            B_r_44_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake of each bin = " << B_r_44_3 << endl;
            B_r_44_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_44_2 << endl;
            B_r_44_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_44_1 << endl;
            B_r_44_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SM H of each bin = " << B_r_44_0 << endl;
            
            float B_r_44 = 0;
            for(int i = 0; i<10; i++) { B_r_44 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_44 << endl;
            
            float Bin_r_44 = 0;
            if (B_r_44 > 0){
                Bin_r_44 =  2* ( (S_r_44 + B_r_44) * log(1+S_r_44/B_r_44) - S_r_44 );
                //Bin_r_44 = 2* ( (S_r_44 + B_r_44) * log(1+S_r_44/B_r_44) - S_r_44 ) ;
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_44) << endl;
            

            Sum_r_44 += Bin_r_44 ;
            QuadraticSum_r_44 = sqrt(Sum_r_44);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_44 << endl;

            h44_2->SetBinContent(j,QuadraticSum_r_44);
            h44_2->SetLineColor(kGreen-9);
            h44_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax44 = 1.1*h44_1->GetMaximum();
          float scale44 = 14000 / rightmax44;
          h44_1->Scale(scale44);
          h44_1->Draw("SAMEHIST");
          
          h44_2->Scale(scale44);
          h44_2->Draw("SAMEHIST");
          
        
          TGaxis*axis44 = new TGaxis(2000,0,2000,14000,0,rightmax44,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg44->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg44->AddEntry(h44_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg44->AddEntry(h44_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg44->Draw();
          
          c44 -> SaveAs("Mt_SM.pdf");
          
          
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
              h_hist[i] = new TH1F(h_nm, "",30,0,600);
              h_hist[i]->GetXaxis()->SetTitle("M_{T, total}^{w} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 10000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="MtTotal*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs45 = new THStack("hs45", "");
          for(int i= 0; i<10 ; i++){ hs45->Add(h_hist[i], "hist45"); }
          hs45->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h45_1 = new TH1F("h45_1","Quadratic Sum from left",30,0,600); //left
          
         float S_l_45 = 0;
         float B_l_45_0 = 0;
         float B_l_45_1 = 0;
         float B_l_45_2 = 0;
         float B_l_45_3 = 0;
         float B_l_45_4 = 0;
         float B_l_45_5 = 0;
         float B_l_45_6 = 0;
         float B_l_45_7 = 0;
         float B_l_45_8 = 0;
         float B_l_45_9 = 0;
          
         float QuadraticSum_l_45 = 0;
         float Sum_l_45 = 0;
           
          for (int j=1; j<=30; j++) {
              
             S_l_45 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_45 << endl;
             B_l_45_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_45_9 << endl;
             B_l_45_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_45_8 << endl;
             B_l_45_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_45_7 << endl;
             B_l_45_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_45_6 << endl;
             B_l_45_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_45_5 << endl;
             B_l_45_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_45_4 << endl;
             B_l_45_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_45_3 << endl;
             B_l_45_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_45_2 << endl;
             B_l_45_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_45_1 << endl;
             B_l_45_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_45_0 << endl;
             
             float B_l_45 = 0;
             for(int i = 0; i<10; i++) { B_l_45 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_45 << endl;
             
             float Bin_l_45 = 0;
             if (B_l_45 > 0){
                 Bin_l_45 =  2* ( (S_l_45 + B_l_45) * log(1+S_l_45/B_l_45) - S_l_45 );
                 //Bin_l_45 = (S_l_45/sqrt(B_l_45))*(S_l_45/sqrt(B_l_45));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_45) << endl; //
             

             Sum_l_45 += Bin_l_45 ;
             QuadraticSum_l_45 = sqrt(Sum_l_45);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_45 << endl;

             h45_1->SetBinContent(j,QuadraticSum_l_45);
             h45_1->SetLineColor(kBlue-9);
             h45_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h45_2 = new TH1F("h45_2","Quadratic Sum from right",30,0,600); //right
          
         float S_r_45 = 0;
         float B_r_45_0 = 0;
         float B_r_45_1 = 0;
         float B_r_45_2 = 0;
         float B_r_45_3 = 0;
         float B_r_45_4 = 0;
         float B_r_45_5 = 0;
         float B_r_45_6 = 0;
         float B_r_45_7 = 0;
         float B_r_45_8 = 0;
         float B_r_45_9 = 0;
          
         float QuadraticSum_r_45 = 0;
         float Sum_r_45 = 0;
          
          for (int j=30; j>=1; j--) {
              
            S_r_45 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_45 << endl;
            B_r_45_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_45_9 << endl;
            B_r_45_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_45_8 << endl;
            B_r_45_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_45_7 << endl;
            B_r_45_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_45_6 << endl;
            B_r_45_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_45_5 << endl;
            B_r_45_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_45_4 << endl;
            B_r_45_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_45_3 << endl;
            B_r_45_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_45_2 << endl;
            B_r_45_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_45_1 << endl;
            B_r_45_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_45_0 << endl;
            
            float B_r_45 = 0;
            for(int i = 0; i<10; i++) { B_r_45 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_45 << endl;
            
            float Bin_r_45 = 0;
            if (B_r_45 > 0){
                Bin_r_45 =  2* ( (S_r_45 + B_r_45) * log(1+S_r_45/B_r_45) - S_r_45 );
                //Bin_r_45 = (S_r_45/sqrt(B_r_45))*(S_r_45/sqrt(B_r_45));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_45) << endl;
            

            Sum_r_45 += Bin_r_45 ;
            QuadraticSum_r_45 = sqrt(Sum_r_45);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_45 << endl;

            h45_2->SetBinContent(j,QuadraticSum_r_45);
            h45_2->SetLineColor(kGreen-9);
            h45_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax45 = 1.1*h45_1->GetMaximum();
          float scale45 = 10000 / rightmax45;
          h45_1->Scale(scale45);
          h45_1->Draw("SAMEHIST");
          
          h45_2->Scale(scale45);
          h45_2->Draw("SAMEHIST");
          
        
          TGaxis*axis45 = new TGaxis(600,0,600,10000,0,rightmax45,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg45->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg45->AddEntry(h45_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg45->AddEntry(h45_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg45->Draw();
          
          c45 -> SaveAs("MtTotal_SM.pdf");
         
        
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
              h_hist[i] = new TH1F(h_nm, "",30,0,300);
              h_hist[i]->GetXaxis()->SetTitle("MtW_{Lep1}");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 20 GeV");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 4000);
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="MtWLep1*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs47 = new THStack("hs47", "");
          for(int i= 0; i<10 ; i++){ hs47->Add(h_hist[i], "hist47"); }
          hs47->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h47_1 = new TH1F("h47_1","Quadratic Sum from left",30,0,300); //left
          
         float S_l_47 = 0;
         float B_l_47_0 = 0;
         float B_l_47_1 = 0;
         float B_l_47_2 = 0;
         float B_l_47_3 = 0;
         float B_l_47_4 = 0;
         float B_l_47_5 = 0;
         float B_l_47_6 = 0;
         float B_l_47_7 = 0;
         float B_l_47_8 = 0;
         float B_l_47_9 = 0;
          
         float QuadraticSum_l_47 = 0;
         float Sum_l_47 = 0;
           
          for (int j=1; j<=30; j++) {
              
             S_l_47 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_47 << endl;
             B_l_47_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_47_9 << endl;
             B_l_47_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_47_8 << endl;
             B_l_47_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_47_7 << endl;
             B_l_47_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_47_6 << endl;
             B_l_47_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_47_5 << endl;
             B_l_47_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_47_4 << endl;
             B_l_47_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_47_3 << endl;
             B_l_47_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_47_2 << endl;
             B_l_47_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_47_1 << endl;
             B_l_47_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_47_0 << endl;
             
             float B_l_47 = 0;
             for(int i = 0; i<10; i++) { B_l_47 += h_hist[i]->GetBinContent(j); }
             //cout << " B of each bin = " << B_l_47 << endl;
             
             float Bin_l_47 = 0;
             if (B_l_47 > 0){
                 Bin_l_47 =  2* ( (S_l_47 + B_l_47) * log(1+S_l_47/B_l_47) - S_l_47 );
                 //Bin_l_47 = (S_l_47/sqrt(B_l_47))*(S_l_47/sqrt(B_l_47));
                 }
             //cout << " Bin = " << j << endl;
             //cout << " significance of each bin = " << sqrt(Bin_l_47) << endl; //
             

             Sum_l_47 += Bin_l_47 ;
             QuadraticSum_l_47 = sqrt(Sum_l_47);
             //cout << " Quadratic sum from left = " << QuadraticSum_l_47 << endl;

             h47_1->SetBinContent(j,QuadraticSum_l_47);
             h47_1->SetLineColor(kBlue-9);
             h47_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h47_2 = new TH1F("h47_2","Quadratic Sum from right",30,0,300); //right
          
         float S_r_47 = 0;
         float B_r_47_0 = 0;
         float B_r_47_1 = 0;
         float B_r_47_2 = 0;
         float B_r_47_3 = 0;
         float B_r_47_4 = 0;
         float B_r_47_5 = 0;
         float B_r_47_6 = 0;
         float B_r_47_7 = 0;
         float B_r_47_8 = 0;
         float B_r_47_9 = 0;
          
         float QuadraticSum_r_47 = 0;
         float Sum_r_47 = 0;
          
          for (int j=30; j>=1; j--) {
              
            S_r_47 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_47 << endl;
            B_r_47_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_47_9 << endl;
            B_r_47_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_47_8 << endl;
            B_r_47_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_47_7 << endl;
            B_r_47_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_47_6 << endl;
            B_r_47_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_47_5 << endl;
            B_r_47_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_47_4 << endl;
            B_r_47_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_47_3 << endl;
            B_r_47_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_47_2 << endl;
            B_r_47_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_47_1 << endl;
            B_r_47_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_47_0 << endl;
            
            float B_r_47 = 0;
            for(int i = 0; i<10; i++) { B_r_47 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_r_47 << endl;
            
            float Bin_r_47 = 0;
            if (B_r_47 > 0){
                Bin_r_47 =  2* ( (S_r_47 + B_r_47) * log(1+S_r_47/B_r_47) - S_r_47 );
                //Bin_r_47 = (S_r_47/sqrt(B_r_47))*(S_r_47/sqrt(B_r_47));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_r_47) << endl;
            

            Sum_r_47 += Bin_r_47 ;
            QuadraticSum_r_47 = sqrt(Sum_r_47);
            //cout << " Quadratic sum from right = " << QuadraticSum_r_47 << endl;

            h47_2->SetBinContent(j,QuadraticSum_r_47);
            h47_2->SetLineColor(kGreen-9);
            h47_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax47 = 1.1*h47_1->GetMaximum();
          float scale47 = 4000 / rightmax47;
          h47_1->Scale(scale47);
          h47_1->Draw("SAMEHIST");
          
          h47_2->Scale(scale47);
          h47_2->Draw("SAMEHIST");
          
        
          TGaxis*axis47 = new TGaxis(300,0,300,4000,0,rightmax47,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg47->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg47->AddEntry(h47_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg47->AddEntry(h47_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg47->Draw();
          
          c47 -> SaveAs("MtWLep1_SM.pdf");
        
         
        //   ===========================================================   METSig   ===========================================================
          
          TCanvas *c48 = new TCanvas ("c48", "METSig",980,580);
            
          TPad *pad481 = new TPad("pad481","",0,0,0.75,1);
          TPad *pad482 = new TPad("pad482","",0.73,0,1,1);
          pad481->Draw();
          pad482->Draw();
            
          pad481->cd();
          pad481->SetTickx();
          gStyle->SetOptStat(kFALSE);
          
          for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
              h_hist[i] = new TH1F(h_nm, "",24,0,24);
              h_hist[i]->GetXaxis()->SetTitle("METSig");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 1");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 9000); //1100
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="METSig>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs48 = new THStack("hs48", "");
          for(int i= 0; i<10 ; i++){ hs48->Add(h_hist[i], "hist48"); }
          hs48->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h48_1 = new TH1F("h48_1","Quadratic Sum from left",24,0,24); //left
          
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
         float B_l_48_9 = 0;
          
         float QuadraticSum_l_48 = 0;
         float Sum_l_48 = 0;
           
          for (int j=1; j<=24; j++) {
              
             S_l_48 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_48 << endl;
             B_l_48_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_48_9 << endl;
             B_l_48_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_48_8 << endl;
             B_l_48_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_48_7 << endl;
             B_l_48_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_48_6 << endl;
             B_l_48_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_48_5 << endl;
             B_l_48_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_48_4 << endl;
             B_l_48_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_48_3 << endl;
             B_l_48_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_48_2 << endl;
             B_l_48_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_48_1 << endl;
             B_l_48_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_48_0 << endl;
             
             float B_l_48 = 0;
             for(int i = 0; i<10; i++) { B_l_48 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_48 << endl;

             h48_1->SetBinContent(j,QuadraticSum_l_48);
             h48_1->SetLineColor(kBlue-9);
             h48_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h48_2 = new TH1F("h48_2","Quadratic Sum from right",24,0,24); //right
          
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
         float B_r_48_9 = 0;
          
         float QuadraticSum_r_48 = 0;
         float Sum_r_48 = 0;
          
          for (int j=24; j>=1; j--) {
              
            S_r_48 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_48 << endl;
            B_r_48_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_48_9 << endl;
            B_r_48_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_48_8 << endl;
            B_r_48_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_48_7 << endl;
            B_r_48_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_48_6 << endl;
            B_r_48_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_48_5 << endl;
            B_r_48_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_48_4 << endl;
            B_r_48_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_48_3 << endl;
            B_r_48_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_48_2 << endl;
            B_r_48_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_48_1 << endl;
            B_r_48_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_48_0 << endl;
            
            float B_r_48 = 0;
            for(int i = 0; i<10; i++) { B_r_48 += h_hist[i]->GetBinContent(j); }
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

            h48_2->SetBinContent(j,QuadraticSum_r_48);
            h48_2->SetLineColor(kGreen-9);
            h48_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax48 = 1.1*h48_1->GetMaximum();
          float scale48 = 9000 / rightmax48;
          h48_1->Scale(scale48);
          h48_1->Draw("SAMEHIST");
          
          h48_2->Scale(scale48);
          h48_2->Draw("SAMEHIST");
          
        
          TGaxis*axis48 = new TGaxis(24,0,24,9000,0,rightmax48,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg48->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg48->AddEntry(h48_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg48->AddEntry(h48_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg48->Draw();
          
          c48 -> SaveAs("METSig_SM.pdf");
         
        
        //   ===========================================================   dRVBFj1Lep0   ===========================================================
          
          TCanvas *c49 = new TCanvas ("c49", "dRVBFj1Lep0",980,580);
            
          TPad *pad491 = new TPad("pad491","",0,0,0.75,1);
          TPad *pad492 = new TPad("pad492","",0.73,0,1,1);
          pad491->Draw();
          pad492->Draw();
            
          pad491->cd();
          pad491->SetTickx();
          gStyle->SetOptStat(kFALSE);
          
          for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
              h_hist[i] = new TH1F(h_nm, "",40,0,8);
              h_hist[i]->GetXaxis()->SetTitle("dRVBFj1Lep");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 3500); //900
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dRVBFj1Lep0>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs49 = new THStack("hs49", "");
          for(int i= 0; i<10 ; i++){ hs49->Add(h_hist[i], "hist49"); }
          hs49->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h49_1 = new TH1F("h49_1","Quadratic Sum from left",40,0,8); //left
          
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
         float B_l_49_9 = 0;
          
         float QuadraticSum_l_49 = 0;
         float Sum_l_49 = 0;
           
          for (int j=1; j<=40; j++) {
              
             S_l_49 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_49 << endl;
             B_l_49_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_49_9 << endl;
             B_l_49_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_49_8 << endl;
             B_l_49_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_49_7 << endl;
             B_l_49_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_49_6 << endl;
             B_l_49_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_49_5 << endl;
             B_l_49_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_49_4 << endl;
             B_l_49_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_49_3 << endl;
             B_l_49_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_49_2 << endl;
             B_l_49_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_49_1 << endl;
             B_l_49_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_49_0 << endl;
             
             float B_l_49 = 0;
             for(int i = 0; i<10; i++) { B_l_49 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_49 << endl;

             h49_1->SetBinContent(j,QuadraticSum_l_49);
             h49_1->SetLineColor(kBlue-9);
             h49_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h49_2 = new TH1F("h49_2","Quadratic Sum from right",40,0,8); //right
          
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
         float B_r_49_9 = 0;
          
         float QuadraticSum_r_49 = 0;
         float Sum_r_49 = 0;
          
          for (int j=40; j>=1; j--) {
              
            S_r_49 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_49 << endl;
            B_r_49_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_49_9 << endl;
            B_r_49_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_49_8 << endl;
            B_r_49_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_49_7 << endl;
            B_r_49_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_49_6 << endl;
            B_r_49_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_49_5 << endl;
            B_r_49_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_49_4 << endl;
            B_r_49_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_49_3 << endl;
            B_r_49_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_49_2 << endl;
            B_r_49_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_49_1 << endl;
            B_r_49_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_49_0 << endl;
            
            float B_r_49 = 0;
            for(int i = 0; i<10; i++) { B_r_49 += h_hist[i]->GetBinContent(j); }
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

            h49_2->SetBinContent(j,QuadraticSum_r_49);
            h49_2->SetLineColor(kGreen-9);
            h49_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax49 = 1.1*h49_1->GetMaximum();
          float scale49 = 3500 / rightmax49;
          h49_1->Scale(scale49);
          h49_1->Draw("SAMEHIST");
          
          h49_2->Scale(scale49);
          h49_2->Draw("SAMEHIST");
          
        
          TGaxis*axis49 = new TGaxis(8,0,8,3500,0,rightmax49,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg49->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg49->AddEntry(h49_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg49->AddEntry(h49_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg49->Draw();
          
          c49 -> SaveAs("dRVBFj1Lep0_SM.pdf");
    
    
    //   ===========================================================   dRVBFj2Lep0   ===========================================================
      
      TCanvas *c53 = new TCanvas ("c53", "dRVBFj2Lep0",980,580);
        
      TPad *pad531 = new TPad("pad531","",0,0,0.75,1);
      TPad *pad532 = new TPad("pad532","",0.73,0,1,1);
      pad531->Draw();
      pad532->Draw();
        
      pad531->cd();
      pad531->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,8);
          h_hist[i]->GetXaxis()->SetTitle("dRVBFj2Lep");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2800); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="dRVBFj2Lep0>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs53 = new THStack("hs53", "");
      for(int i= 0; i<10 ; i++){ hs53->Add(h_hist[i], "hist53"); }
      hs53->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h53_1 = new TH1F("h53_1","Quadratic Sum from left",40,0,8); //left
      
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
     float B_l_53_9 = 0;
      
     float QuadraticSum_l_53 = 0;
     float Sum_l_53 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_53 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_53 << endl;
         B_l_53_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_53_9 << endl;
         B_l_53_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_53_8 << endl;
         B_l_53_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_53_7 << endl;
         B_l_53_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_53_6 << endl;
         B_l_53_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_53_5 << endl;
         B_l_53_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_53_4 << endl;
         B_l_53_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_53_3 << endl;
         B_l_53_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_53_2 << endl;
         B_l_53_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_53_1 << endl;
         B_l_53_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_53_0 << endl;
         
         float B_l_53 = 0;
         for(int i = 0; i<10; i++) { B_l_53 += h_hist[i]->GetBinContent(j); }
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
         //cout << " Quadratic sum from left = " << QuadraticSum_l_53 << endl;

         h53_1->SetBinContent(j,QuadraticSum_l_53);
         h53_1->SetLineColor(kBlue-9);
         h53_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h53_2 = new TH1F("h53_2","Quadratic Sum from right",40,0,8); //right
      
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
     float B_r_53_9 = 0;
      
     float QuadraticSum_r_53 = 0;
     float Sum_r_53 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_53 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_53 << endl;
        B_r_53_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_53_9 << endl;
        B_r_53_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_53_8 << endl;
        B_r_53_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_53_7 << endl;
        B_r_53_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_53_6 << endl;
        B_r_53_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_53_5 << endl;
        B_r_53_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_53_4 << endl;
        B_r_53_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_53_3 << endl;
        B_r_53_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_53_2 << endl;
        B_r_53_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_53_1 << endl;
        B_r_53_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_53_0 << endl;
        
        float B_r_53 = 0;
        for(int i = 0; i<10; i++) { B_r_53 += h_hist[i]->GetBinContent(j); }
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

        h53_2->SetBinContent(j,QuadraticSum_r_53);
        h53_2->SetLineColor(kGreen-9);
        h53_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax53 = 1.1*h53_1->GetMaximum();
      float scale53 = 2800 / rightmax53;
      h53_1->Scale(scale53);
      h53_1->Draw("SAMEHIST");
      
      h53_2->Scale(scale53);
      h53_2->Draw("SAMEHIST");
      
    
      TGaxis*axis53 = new TGaxis(8,0,8,2800,0,rightmax53,510,"+L");
      axis53->SetTitle("Quadratic Sum of significance");
      axis53->SetTitleSize(0.03);
      axis53->SetLabelSize(0.025);
      axis53->Draw();
      
      pad532->cd();
      TLegend *leg53 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg53->SetBorderSize(1);
      leg53->SetFillColor(0);
      leg53->SetTextFont(42);
      leg53->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg53->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg53->AddEntry(h53_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg53->AddEntry(h53_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg53->Draw();
      
      c53 -> SaveAs("dRVBFj2Lep0_SM.pdf");
    
    
    //   ===========================================================   dRVBFj1Tau   ===========================================================
      
      TCanvas *c54 = new TCanvas ("c54", "dRVBFj1Tau",980,580);
        
      TPad *pad541 = new TPad("pad541","",0,0,0.75,1);
      TPad *pad542 = new TPad("pad542","",0.73,0,1,1);
      pad541->Draw();
      pad542->Draw();
        
      pad541->cd();
      pad541->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,8);
          h_hist[i]->GetXaxis()->SetTitle("dRVBFj1Tau");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3500); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="dRVBFj1Tau>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs54 = new THStack("hs54", "");
      for(int i= 0; i<10 ; i++){ hs54->Add(h_hist[i], "hist54"); }
      hs54->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h54_1 = new TH1F("h54_1","Quadratic Sum from left",40,0,8); //left
      
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
     float B_l_54_9 = 0;
      
     float QuadraticSum_l_54 = 0;
     float Sum_l_54 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_54 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_54 << endl;
         B_l_54_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_54_9 << endl;
         B_l_54_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_54_8 << endl;
         B_l_54_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_54_7 << endl;
         B_l_54_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_54_6 << endl;
         B_l_54_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_54_5 << endl;
         B_l_54_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_54_4 << endl;
         B_l_54_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_54_3 << endl;
         B_l_54_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_54_2 << endl;
         B_l_54_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_54_1 << endl;
         B_l_54_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_54_0 << endl;
         
         float B_l_54 = 0;
         for(int i = 0; i<10; i++) { B_l_54 += h_hist[i]->GetBinContent(j); }
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
         //cout << " Quadratic sum from left = " << QuadraticSum_l_54 << endl;

         h54_1->SetBinContent(j,QuadraticSum_l_54);
         h54_1->SetLineColor(kBlue-9);
         h54_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h54_2 = new TH1F("h54_2","Quadratic Sum from right",40,0,8); //right
      
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
     float B_r_54_9 = 0;
      
     float QuadraticSum_r_54 = 0;
     float Sum_r_54 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_54 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_54 << endl;
        B_r_54_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_54_9 << endl;
        B_r_54_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_54_8 << endl;
        B_r_54_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_54_7 << endl;
        B_r_54_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_54_6 << endl;
        B_r_54_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_54_5 << endl;
        B_r_54_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_54_4 << endl;
        B_r_54_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_54_3 << endl;
        B_r_54_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_54_2 << endl;
        B_r_54_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_54_1 << endl;
        B_r_54_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_54_0 << endl;
        
        float B_r_54 = 0;
        for(int i = 0; i<10; i++) { B_r_54 += h_hist[i]->GetBinContent(j); }
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

        h54_2->SetBinContent(j,QuadraticSum_r_54);
        h54_2->SetLineColor(kGreen-9);
        h54_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax54 = 1.1*h54_1->GetMaximum();
      float scale54 = 3500 / rightmax54;
      h54_1->Scale(scale54);
      h54_1->Draw("SAMEHIST");
      
      h54_2->Scale(scale54);
      h54_2->Draw("SAMEHIST");
      
    
      TGaxis*axis54 = new TGaxis(8,0,8,3500,0,rightmax54,510,"+L");
      axis54->SetTitle("Quadratic Sum of significance");
      axis54->SetTitleSize(0.03);
      axis54->SetLabelSize(0.025);
      axis54->Draw();
      
      pad542->cd();
      TLegend *leg54 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg54->SetBorderSize(1);
      leg54->SetFillColor(0);
      leg54->SetTextFont(42);
      leg54->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg54->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg54->AddEntry(h54_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg54->AddEntry(h54_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg54->Draw();
      
      c54 -> SaveAs("dRVBFj1Tau_SM.pdf");
    
    
    //   ===========================================================   dRVBFj2Tau   ===========================================================
      
      TCanvas *c55 = new TCanvas ("c55", "dRVBFj2Tau",980,580);
        
      TPad *pad551 = new TPad("pad551","",0,0,0.75,1);
      TPad *pad552 = new TPad("pad552","",0.73,0,1,1);
      pad551->Draw();
      pad552->Draw();
        
      pad551->cd();
      pad551->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,8);
          h_hist[i]->GetXaxis()->SetTitle("dRVBFj2Tau");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2800); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="dRVBFj2Tau>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs55 = new THStack("hs55", "");
      for(int i= 0; i<10 ; i++){ hs55->Add(h_hist[i], "hist55"); }
      hs55->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h55_1 = new TH1F("h55_1","Quadratic Sum from left",40,0,8); //left
      
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
     float B_l_55_9 = 0;
      
     float QuadraticSum_l_55 = 0;
     float Sum_l_55 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_55 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_55 << endl;
         B_l_55_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_55_9 << endl;
         B_l_55_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_55_8 << endl;
         B_l_55_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_55_7 << endl;
         B_l_55_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_55_6 << endl;
         B_l_55_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_55_5 << endl;
         B_l_55_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_55_4 << endl;
         B_l_55_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_55_3 << endl;
         B_l_55_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_55_2 << endl;
         B_l_55_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_55_1 << endl;
         B_l_55_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_55_0 << endl;
         
         float B_l_55 = 0;
         for(int i = 0; i<10; i++) { B_l_55 += h_hist[i]->GetBinContent(j); }
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
         //cout << " Quadratic sum from left = " << QuadraticSum_l_55 << endl;

         h55_1->SetBinContent(j,QuadraticSum_l_55);
         h55_1->SetLineColor(kBlue-9);
         h55_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h55_2 = new TH1F("h55_2","Quadratic Sum from right",40,0,8); //right
      
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
     float B_r_55_9 = 0;
      
     float QuadraticSum_r_55 = 0;
     float Sum_r_55 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_55 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_55 << endl;
        B_r_55_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_55_9 << endl;
        B_r_55_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_55_8 << endl;
        B_r_55_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_55_7 << endl;
        B_r_55_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_55_6 << endl;
        B_r_55_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_55_5 << endl;
        B_r_55_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_55_4 << endl;
        B_r_55_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_55_3 << endl;
        B_r_55_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_55_2 << endl;
        B_r_55_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_55_1 << endl;
        B_r_55_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_55_0 << endl;
        
        float B_r_55 = 0;
        for(int i = 0; i<10; i++) { B_r_55 += h_hist[i]->GetBinContent(j); }
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

        h55_2->SetBinContent(j,QuadraticSum_r_55);
        h55_2->SetLineColor(kGreen-9);
        h55_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax55 = 1.1*h55_1->GetMaximum();
      float scale55 = 2800 / rightmax55;
      h55_1->Scale(scale55);
      h55_1->Draw("SAMEHIST");
      
      h55_2->Scale(scale55);
      h55_2->Draw("SAMEHIST");
      
    
      TGaxis*axis55 = new TGaxis(8,0,8,2800,0,rightmax55,510,"+L");
      axis55->SetTitle("Quadratic Sum of significance");
      axis55->SetTitleSize(0.03);
      axis55->SetLabelSize(0.025);
      axis55->Draw();
      
      pad552->cd();
      TLegend *leg55 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg55->SetBorderSize(1);
      leg55->SetFillColor(0);
      leg55->SetTextFont(42);
      leg55->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg55->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg55->AddEntry(h55_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg55->AddEntry(h55_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg55->Draw();
      
      c55 -> SaveAs("dRVBFj2Tau_SM.pdf");
    
    
    //   ===========================================================   dRVBFj1B1   ===========================================================
      
      TCanvas *c56 = new TCanvas ("c56", "dRVBFj1B1",980,580);
        
      TPad *pad561 = new TPad("pad561","",0,0,0.75,1);
      TPad *pad562 = new TPad("pad562","",0.73,0,1,1);
      pad561->Draw();
      pad562->Draw();
        
      pad561->cd();
      pad561->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,8);
          h_hist[i]->GetXaxis()->SetTitle("dRVBFj1B1");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3200); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="dRVBFj1B1>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs56 = new THStack("hs56", "");
      for(int i= 0; i<10 ; i++){ hs56->Add(h_hist[i], "hist56"); }
      hs56->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h56_1 = new TH1F("h56_1","Quadratic Sum from left",40,0,8); //left
      
     float S_l_56 = 0;
     float B_l_56_0 = 0;
     float B_l_56_1 = 0;
     float B_l_56_2 = 0;
     float B_l_56_3 = 0;
     float B_l_56_4 = 0;
     float B_l_56_5 = 0;
     float B_l_56_6 = 0;
     float B_l_56_7 = 0;
     float B_l_56_8 = 0;
     float B_l_56_9 = 0;
      
     float QuadraticSum_l_56 = 0;
     float Sum_l_56 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_56 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_56 << endl;
         B_l_56_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_56_9 << endl;
         B_l_56_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_56_8 << endl;
         B_l_56_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_56_7 << endl;
         B_l_56_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_56_6 << endl;
         B_l_56_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_56_5 << endl;
         B_l_56_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_56_4 << endl;
         B_l_56_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_56_3 << endl;
         B_l_56_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_56_2 << endl;
         B_l_56_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_56_1 << endl;
         B_l_56_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_56_0 << endl;
         
         float B_l_56 = 0;
         for(int i = 0; i<10; i++) { B_l_56 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_56 << endl;
         
         float Bin_l_56 = 0;
         if (B_l_56 > 0){
             Bin_l_56 =  2* ( (S_l_56 + B_l_56) * log(1+S_l_56/B_l_56) - S_l_56 );
             //Bin_l_56 = (S_l_56/sqrt(B_l_56))*(S_l_56/sqrt(B_l_56));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_56) << endl; //
         

         Sum_l_56 += Bin_l_56 ;
         QuadraticSum_l_56 = sqrt(Sum_l_56);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_56 << endl;

         h56_1->SetBinContent(j,QuadraticSum_l_56);
         h56_1->SetLineColor(kBlue-9);
         h56_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h56_2 = new TH1F("h56_2","Quadratic Sum from right",40,0,8); //right
      
     float S_r_56 = 0;
     float B_r_56_0 = 0;
     float B_r_56_1 = 0;
     float B_r_56_2 = 0;
     float B_r_56_3 = 0;
     float B_r_56_4 = 0;
     float B_r_56_5 = 0;
     float B_r_56_6 = 0;
     float B_r_56_7 = 0;
     float B_r_56_8 = 0;
     float B_r_56_9 = 0;
      
     float QuadraticSum_r_56 = 0;
     float Sum_r_56 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_56 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_56 << endl;
        B_r_56_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_56_9 << endl;
        B_r_56_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_56_8 << endl;
        B_r_56_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_56_7 << endl;
        B_r_56_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_56_6 << endl;
        B_r_56_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_56_5 << endl;
        B_r_56_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_56_4 << endl;
        B_r_56_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_56_3 << endl;
        B_r_56_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_56_2 << endl;
        B_r_56_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_56_1 << endl;
        B_r_56_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_56_0 << endl;
        
        float B_r_56 = 0;
        for(int i = 0; i<10; i++) { B_r_56 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_56 << endl;
        
        float Bin_r_56 = 0;
        if (B_r_56 > 0){
            Bin_r_56 =  2* ( (S_r_56 + B_r_56) * log(1+S_r_56/B_r_56) - S_r_56 );
            //Bin_r_56 = (S_r_56/sqrt(B_r_56))*(S_r_56/sqrt(B_r_56));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_56) << endl;
        

        Sum_r_56 += Bin_r_56 ;
        QuadraticSum_r_56 = sqrt(Sum_r_56);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_56 << endl;

        h56_2->SetBinContent(j,QuadraticSum_r_56);
        h56_2->SetLineColor(kGreen-9);
        h56_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax56 = 1.1*h56_1->GetMaximum();
      float scale56 = 3200 / rightmax56;
      h56_1->Scale(scale56);
      h56_1->Draw("SAMEHIST");
      
      h56_2->Scale(scale56);
      h56_2->Draw("SAMEHIST");
      
    
      TGaxis*axis56 = new TGaxis(8,0,8,3200,0,rightmax56,510,"+L");
      axis56->SetTitle("Quadratic Sum of significance");
      axis56->SetTitleSize(0.03);
      axis56->SetLabelSize(0.025);
      axis56->Draw();
      
      pad562->cd();
      TLegend *leg56 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg56->SetBorderSize(1);
      leg56->SetFillColor(0);
      leg56->SetTextFont(42);
      leg56->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg56->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg56->AddEntry(h56_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg56->AddEntry(h56_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg56->Draw();
      
      c56 -> SaveAs("dRVBFj1B1_SM.pdf");
    
    
    //   ===========================================================   dRVBFj1B2   ===========================================================
      
      TCanvas *c57 = new TCanvas ("c57", "dRVBFj1B2",980,580);
        
      TPad *pad571 = new TPad("pad571","",0,0,0.75,1);
      TPad *pad572 = new TPad("pad572","",0.73,0,1,1);
      pad571->Draw();
      pad572->Draw();
        
      pad571->cd();
      pad571->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,8);
          h_hist[i]->GetXaxis()->SetTitle("dRVBFj1B2");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2800); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="dRVBFj1B2>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs57 = new THStack("hs57", "");
      for(int i= 0; i<10 ; i++){ hs57->Add(h_hist[i], "hist57"); }
      hs57->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h57_1 = new TH1F("h57_1","Quadratic Sum from left",40,0,8); //left
      
     float S_l_57 = 0;
     float B_l_57_0 = 0;
     float B_l_57_1 = 0;
     float B_l_57_2 = 0;
     float B_l_57_3 = 0;
     float B_l_57_4 = 0;
     float B_l_57_5 = 0;
     float B_l_57_6 = 0;
     float B_l_57_7 = 0;
     float B_l_57_8 = 0;
     float B_l_57_9 = 0;
      
     float QuadraticSum_l_57 = 0;
     float Sum_l_57 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_57 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_57 << endl;
         B_l_57_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_57_9 << endl;
         B_l_57_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_57_8 << endl;
         B_l_57_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_57_7 << endl;
         B_l_57_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_57_6 << endl;
         B_l_57_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_57_5 << endl;
         B_l_57_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_57_4 << endl;
         B_l_57_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_57_3 << endl;
         B_l_57_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_57_2 << endl;
         B_l_57_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_57_1 << endl;
         B_l_57_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_57_0 << endl;
         
         float B_l_57 = 0;
         for(int i = 0; i<10; i++) { B_l_57 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_57 << endl;
         
         float Bin_l_57 = 0;
         if (B_l_57 > 0){
             Bin_l_57 =  2* ( (S_l_57 + B_l_57) * log(1+S_l_57/B_l_57) - S_l_57 );
             //Bin_l_57 = (S_l_57/sqrt(B_l_57))*(S_l_57/sqrt(B_l_57));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_57) << endl; //
         

         Sum_l_57 += Bin_l_57 ;
         QuadraticSum_l_57 = sqrt(Sum_l_57);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_57 << endl;

         h57_1->SetBinContent(j,QuadraticSum_l_57);
         h57_1->SetLineColor(kBlue-9);
         h57_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h57_2 = new TH1F("h57_2","Quadratic Sum from right",40,0,8); //right
      
     float S_r_57 = 0;
     float B_r_57_0 = 0;
     float B_r_57_1 = 0;
     float B_r_57_2 = 0;
     float B_r_57_3 = 0;
     float B_r_57_4 = 0;
     float B_r_57_5 = 0;
     float B_r_57_6 = 0;
     float B_r_57_7 = 0;
     float B_r_57_8 = 0;
     float B_r_57_9 = 0;
      
     float QuadraticSum_r_57 = 0;
     float Sum_r_57 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_57 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_57 << endl;
        B_r_57_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_57_9 << endl;
        B_r_57_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_57_8 << endl;
        B_r_57_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_57_7 << endl;
        B_r_57_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_57_6 << endl;
        B_r_57_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_57_5 << endl;
        B_r_57_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_57_4 << endl;
        B_r_57_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_57_3 << endl;
        B_r_57_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_57_2 << endl;
        B_r_57_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_57_1 << endl;
        B_r_57_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_57_0 << endl;
        
        float B_r_57 = 0;
        for(int i = 0; i<10; i++) { B_r_57 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_57 << endl;
        
        float Bin_r_57 = 0;
        if (B_r_57 > 0){
            Bin_r_57 =  2* ( (S_r_57 + B_r_57) * log(1+S_r_57/B_r_57) - S_r_57 );
            //Bin_r_57 = (S_r_57/sqrt(B_r_57))*(S_r_57/sqrt(B_r_57));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_57) << endl;
        

        Sum_r_57 += Bin_r_57 ;
        QuadraticSum_r_57 = sqrt(Sum_r_57);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_57 << endl;

        h57_2->SetBinContent(j,QuadraticSum_r_57);
        h57_2->SetLineColor(kGreen-9);
        h57_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax57 = 1.1*h57_1->GetMaximum();
      float scale57 = 2800 / rightmax57;
      h57_1->Scale(scale57);
      h57_1->Draw("SAMEHIST");
      
      h57_2->Scale(scale57);
      h57_2->Draw("SAMEHIST");
      
    
      TGaxis*axis57 = new TGaxis(8,0,8,2800,0,rightmax57,510,"+L");
      axis57->SetTitle("Quadratic Sum of significance");
      axis57->SetTitleSize(0.03);
      axis57->SetLabelSize(0.025);
      axis57->Draw();
      
      pad572->cd();
      TLegend *leg57 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg57->SetBorderSize(1);
      leg57->SetFillColor(0);
      leg57->SetTextFont(42);
      leg57->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg57->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg57->AddEntry(h57_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg57->AddEntry(h57_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg57->Draw();
      
      c57 -> SaveAs("dRVBFj1B2_SM.pdf");
    
    
    //   ===========================================================   dRVBFj2B1   ===========================================================
      
      TCanvas *c58 = new TCanvas ("c58", "dRVBFj2B1",980,580);
        
      TPad *pad581 = new TPad("pad581","",0,0,0.75,1);
      TPad *pad582 = new TPad("pad582","",0.73,0,1,1);
      pad581->Draw();
      pad582->Draw();
        
      pad581->cd();
      pad581->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,8);
          h_hist[i]->GetXaxis()->SetTitle("dRVBFj2B1");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2800); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="dRVBFj2B1>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs58 = new THStack("hs58", "");
      for(int i= 0; i<10 ; i++){ hs58->Add(h_hist[i], "hist58"); }
      hs58->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h58_1 = new TH1F("h58_1","Quadratic Sum from left",40,0,8); //left
      
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
     float B_l_58_9 = 0;
      
     float QuadraticSum_l_58 = 0;
     float Sum_l_58 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_58 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_58 << endl;
         B_l_58_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_58_9 << endl;
         B_l_58_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_58_8 << endl;
         B_l_58_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_58_7 << endl;
         B_l_58_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_58_6 << endl;
         B_l_58_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_58_5 << endl;
         B_l_58_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_58_4 << endl;
         B_l_58_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_58_3 << endl;
         B_l_58_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_58_2 << endl;
         B_l_58_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_58_1 << endl;
         B_l_58_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_58_0 << endl;
         
         float B_l_58 = 0;
         for(int i = 0; i<10; i++) { B_l_58 += h_hist[i]->GetBinContent(j); }
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
         //cout << " Quadratic sum from left = " << QuadraticSum_l_58 << endl;

         h58_1->SetBinContent(j,QuadraticSum_l_58);
         h58_1->SetLineColor(kBlue-9);
         h58_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h58_2 = new TH1F("h58_2","Quadratic Sum from right",40,0,8); //right
      
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
     float B_r_58_9 = 0;
      
     float QuadraticSum_r_58 = 0;
     float Sum_r_58 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_58 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_58 << endl;
        B_r_58_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_58_9 << endl;
        B_r_58_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_58_8 << endl;
        B_r_58_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_58_7 << endl;
        B_r_58_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_58_6 << endl;
        B_r_58_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_58_5 << endl;
        B_r_58_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_58_4 << endl;
        B_r_58_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_58_3 << endl;
        B_r_58_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_58_2 << endl;
        B_r_58_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_58_1 << endl;
        B_r_58_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_58_0 << endl;
        
        float B_r_58 = 0;
        for(int i = 0; i<10; i++) { B_r_58 += h_hist[i]->GetBinContent(j); }
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

        h58_2->SetBinContent(j,QuadraticSum_r_58);
        h58_2->SetLineColor(kGreen-9);
        h58_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax58 = 1.1*h58_1->GetMaximum();
      float scale58 = 2800 / rightmax58;
      h58_1->Scale(scale58);
      h58_1->Draw("SAMEHIST");
      
      h58_2->Scale(scale58);
      h58_2->Draw("SAMEHIST");
      
    
      TGaxis*axis58 = new TGaxis(8,0,8,2800,0,rightmax58,510,"+L");
      axis58->SetTitle("Quadratic Sum of significance");
      axis58->SetTitleSize(0.03);
      axis58->SetLabelSize(0.025);
      axis58->Draw();
      
      pad582->cd();
      TLegend *leg58 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg58->SetBorderSize(1);
      leg58->SetFillColor(0);
      leg58->SetTextFont(42);
      leg58->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg58->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg58->AddEntry(h58_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg58->AddEntry(h58_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg58->Draw();
      
      c58 -> SaveAs("dRVBFj2B1_SM.pdf");
    
    
    //   ===========================================================   dRVBFj2B2   ===========================================================
      
      TCanvas *c59 = new TCanvas ("c59", "dRVBFj2B2",980,580);
        
      TPad *pad591 = new TPad("pad591","",0,0,0.75,1);
      TPad *pad592 = new TPad("pad592","",0.73,0,1,1);
      pad591->Draw();
      pad592->Draw();
        
      pad591->cd();
      pad591->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,8);
          h_hist[i]->GetXaxis()->SetTitle("dRVBFj2B2");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2800); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="dRVBFj2B2>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs59 = new THStack("hs59", "");
      for(int i= 0; i<10 ; i++){ hs59->Add(h_hist[i], "hist59"); }
      hs59->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h59_1 = new TH1F("h59_1","Quadratic Sum from left",40,0,8); //left
      
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
     float B_l_59_9 = 0;
      
     float QuadraticSum_l_59 = 0;
     float Sum_l_59 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_59 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_59 << endl;
         B_l_59_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_59_9 << endl;
         B_l_59_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_59_8 << endl;
         B_l_59_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_59_7 << endl;
         B_l_59_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_59_6 << endl;
         B_l_59_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_59_5 << endl;
         B_l_59_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_59_4 << endl;
         B_l_59_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_59_3 << endl;
         B_l_59_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_59_2 << endl;
         B_l_59_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_59_1 << endl;
         B_l_59_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_59_0 << endl;
         
         float B_l_59 = 0;
         for(int i = 0; i<10; i++) { B_l_59 += h_hist[i]->GetBinContent(j); }
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
         //cout << " Quadratic sum from left = " << QuadraticSum_l_59 << endl;

         h59_1->SetBinContent(j,QuadraticSum_l_59);
         h59_1->SetLineColor(kBlue-9);
         h59_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h59_2 = new TH1F("h59_2","Quadratic Sum from right",40,0,8); //right
      
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
     float B_r_59_9 = 0;
      
     float QuadraticSum_r_59 = 0;
     float Sum_r_59 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_59 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_59 << endl;
        B_r_59_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_59_9 << endl;
        B_r_59_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_59_8 << endl;
        B_r_59_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_59_7 << endl;
        B_r_59_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_59_6 << endl;
        B_r_59_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_59_5 << endl;
        B_r_59_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_59_4 << endl;
        B_r_59_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_59_3 << endl;
        B_r_59_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_59_2 << endl;
        B_r_59_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_59_1 << endl;
        B_r_59_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_59_0 << endl;
        
        float B_r_59 = 0;
        for(int i = 0; i<10; i++) { B_r_59 += h_hist[i]->GetBinContent(j); }
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

        h59_2->SetBinContent(j,QuadraticSum_r_59);
        h59_2->SetLineColor(kGreen-9);
        h59_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax59 = 1.1*h59_1->GetMaximum();
      float scale59 = 2800 / rightmax59;
      h59_1->Scale(scale59);
      h59_1->Draw("SAMEHIST");
      
      h59_2->Scale(scale59);
      h59_2->Draw("SAMEHIST");
      
    
      TGaxis*axis59 = new TGaxis(8,0,8,2800,0,rightmax59,510,"+L");
      axis59->SetTitle("Quadratic Sum of significance");
      axis59->SetTitleSize(0.03);
      axis59->SetLabelSize(0.025);
      axis59->Draw();
      
      pad592->cd();
      TLegend *leg59 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg59->SetBorderSize(1);
      leg59->SetFillColor(0);
      leg59->SetTextFont(42);
      leg59->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg59->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg59->AddEntry(h59_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg59->AddEntry(h59_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg59->Draw();
      
      c59 -> SaveAs("dRVBFj2B2_SM.pdf");
     
    
    //   ===========================================================   dPhiVBFjj   ===========================================================
         
         TCanvas *c60 = new TCanvas ("c60", "dPhiVBFjj",980,580);
           
         TPad *pad601 = new TPad("pad601","",0,0,0.75,1);
         TPad *pad602 = new TPad("pad602","",0.73,0,1,1);
         pad601->Draw();
         pad602->Draw();
           
         pad601->cd();
         pad601->SetTickx();
         gStyle->SetOptStat(kFALSE);
         
         for (int i=0; i<n_smp; i++){
           h_nm = h_title[i].c_str();
             h_hist[i] = new TH1F(h_nm, "",35,0,7);
             h_hist[i]->GetXaxis()->SetTitle("#Delta#phi VBFjj");
           h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
           //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
           h_hist[i]->GetYaxis()->SetRangeUser(0, 2500); //900
         }
         
         h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
         h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
         h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
         h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
         h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
         h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
         h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
         h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
         h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
         h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
         h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

       
         for (int i=0; i<n_smp; i++){
             hist_draw[i]="dPhiVBFjj>>"+h_title[i];
         }
         
         for(int i = 0; i<n_smp; i++){
           
           if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
           else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
           else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
           else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
           else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
           else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
           
         }
         
         THStack *hs60 = new THStack("hs60", "");
         for(int i= 0; i<10 ; i++){ hs60->Add(h_hist[i], "hist60"); }
         hs60->Draw("SAMEHIST");
       
         for(int i = 0; i<n_smp; i++){
             if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
         }
    
        // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

        //cout << " ============== significance From left ============== " << endl;
        //cout << " " << endl;
         
       TH1F *h60_1 = new TH1F("h60_1","Quadratic Sum from left",35,0,7); //left
         
        float S_l_60 = 0;
        float B_l_60_0 = 0;
        float B_l_60_1 = 0;
        float B_l_60_2 = 0;
        float B_l_60_3 = 0;
        float B_l_60_4 = 0;
        float B_l_60_5 = 0;
        float B_l_60_6 = 0;
        float B_l_60_7 = 0;
        float B_l_60_8 = 0;
        float B_l_60_9 = 0;
         
        float QuadraticSum_l_60 = 0;
        float Sum_l_60 = 0;
          
         for (int j=1; j<=35; j++) {
             
            S_l_60 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_l_60 << endl;
            B_l_60_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_l_60_9 << endl;
            B_l_60_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_l_60_8 << endl;
            B_l_60_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_l_60_7 << endl;
            B_l_60_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_l_60_6 << endl;
            B_l_60_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_l_60_5 << endl;
            B_l_60_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_l_60_4 << endl;
            B_l_60_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_l_60_3 << endl;
            B_l_60_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_l_60_2 << endl;
            B_l_60_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_l_60_1 << endl;
            B_l_60_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_l_60_0 << endl;
            
            float B_l_60 = 0;
            for(int i = 0; i<10; i++) { B_l_60 += h_hist[i]->GetBinContent(j); }
            //cout << " B of each bin = " << B_l_60 << endl;
            
            float Bin_l_60 = 0;
            if (B_l_60 > 0){
                Bin_l_60 =  2* ( (S_l_60 + B_l_60) * log(1+S_l_60/B_l_60) - S_l_60 );
                //Bin_l_60 = (S_l_60/sqrt(B_l_60))*(S_l_60/sqrt(B_l_60));
                }
            //cout << " Bin = " << j << endl;
            //cout << " significance of each bin = " << sqrt(Bin_l_60) << endl; //
            

            Sum_l_60 += Bin_l_60 ;
            QuadraticSum_l_60 = sqrt(Sum_l_60);
            //cout << " Quadratic sum from left = " << QuadraticSum_l_60 << endl;

            h60_1->SetBinContent(j,QuadraticSum_l_60);
            h60_1->SetLineColor(kBlue-9);
            h60_1->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
        }
            

        // ------------------------------------------------------------
        
        //cout << " " << endl;
        //cout << " ============== significance From right ============== " << endl;
        //cout << " " << endl;
         
       TH1F *h60_2 = new TH1F("h60_2","Quadratic Sum from right",35,0,7); //right
         
        float S_r_60 = 0;
        float B_r_60_0 = 0;
        float B_r_60_1 = 0;
        float B_r_60_2 = 0;
        float B_r_60_3 = 0;
        float B_r_60_4 = 0;
        float B_r_60_5 = 0;
        float B_r_60_6 = 0;
        float B_r_60_7 = 0;
        float B_r_60_8 = 0;
        float B_r_60_9 = 0;
         
        float QuadraticSum_r_60 = 0;
        float Sum_r_60 = 0;
         
         for (int j=35; j>=1; j--) {
             
           S_r_60 = h_hist[10]->GetBinContent(j); //VBFSM
           //cout << " S of each bin = " << S_r_60 << endl;
           B_r_60_9 = h_hist[9]->GetBinContent(j);
           //cout << " B of ttbar of each bin = " << B_r_60_9 << endl;
           B_r_60_8 = h_hist[8]->GetBinContent(j);
           //cout << " B of single top of each bin = " << B_r_60_8 << endl;
           B_r_60_7 = h_hist[7]->GetBinContent(j);
           //cout << " B of Ztt of each bin = " << B_r_60_7 << endl;
           B_r_60_6 = h_hist[6]->GetBinContent(j);
           //cout << " B of Wlv of each bin = " << B_r_60_6 << endl;
           B_r_60_5 = h_hist[5]->GetBinContent(j);
           //cout << " B of Z of each bin = " << B_r_60_5 << endl;
           B_r_60_4 = h_hist[4]->GetBinContent(j);
           //cout << " B of Fake_W of each bin = " << B_r_60_4 << endl;
           B_r_60_3 = h_hist[3]->GetBinContent(j);
           //cout << " B of Fake_ttbar of each bin = " << B_r_60_3 << endl;
           B_r_60_2 = h_hist[2]->GetBinContent(j);
           //cout << " B of DY of each bin = " << B_r_60_2 << endl;
           B_r_60_1 = h_hist[1]->GetBinContent(j);
           //cout << " B of diboson of each bin = " << B_r_60_1 << endl;
           B_r_60_0 = h_hist[0]->GetBinContent(j);
           //cout << " B of SMH of each bin = " << B_r_60_0 << endl;
           
           float B_r_60 = 0;
           for(int i = 0; i<10; i++) { B_r_60 += h_hist[i]->GetBinContent(j); }
           //cout << " B of each bin = " << B_r_60 << endl;
           
           float Bin_r_60 = 0;
           if (B_r_60 > 0){
               Bin_r_60 =  2* ( (S_r_60 + B_r_60) * log(1+S_r_60/B_r_60) - S_r_60 );
               //Bin_r_60 = (S_r_60/sqrt(B_r_60))*(S_r_60/sqrt(B_r_60));
               }
           //cout << " Bin = " << j << endl;
           //cout << " significance of each bin = " << sqrt(Bin_r_60) << endl;
           

           Sum_r_60 += Bin_r_60 ;
           QuadraticSum_r_60 = sqrt(Sum_r_60);
           //cout << " Quadratic sum from right = " << QuadraticSum_r_60 << endl;

           h60_2->SetBinContent(j,QuadraticSum_r_60);
           h60_2->SetLineColor(kGreen-9);
           h60_2->SetLineStyle(2);
           
           //cout << " ************************************ " << endl;
        }
        
         
         
         float rightmax60 = 1.1*h60_1->GetMaximum();
         float scale60 = 2500 / rightmax60;
         h60_1->Scale(scale60);
         h60_1->Draw("SAMEHIST");
         
         h60_2->Scale(scale60);
         h60_2->Draw("SAMEHIST");
         
       
         TGaxis*axis60 = new TGaxis(7,0,7,2500,0,rightmax60,510,"+L");
         axis60->SetTitle("Quadratic Sum of significance");
         axis60->SetTitleSize(0.03);
         axis60->SetLabelSize(0.025);
         axis60->Draw();
         
         pad602->cd();
         TLegend *leg60 = new TLegend(0.008, 0.1, 0.985,0.9);
         leg60->SetBorderSize(1);
         leg60->SetFillColor(0);
         leg60->SetTextFont(42);
         leg60->SetTextSize(0.053);
         
         for(int i= 10; i>=0 ; i--)
         {
             leg60->AddEntry(h_hist[i], h_titles[i].c_str());
         }
         leg60->AddEntry(h60_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
         leg60->AddEntry(h60_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
         leg60->Draw();
         
         c60 -> SaveAs("dPhiVBFjj_SM.pdf");
         
            
        //   ===========================================================   dEtaHH   ===========================================================
          
          TCanvas *c50 = new TCanvas ("c50", "dEtaHH",980,580);
            
          TPad *pad501 = new TPad("pad501","",0,0,0.75,1);
          TPad *pad502 = new TPad("pad502","",0.73,0,1,1);
          pad501->Draw();
          pad502->Draw();
            
          pad501->cd();
          pad501->SetTickx();
          gStyle->SetOptStat(kFALSE);
          
          for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
              h_hist[i] = new TH1F(h_nm, "",40,0,8);
              h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (H,H)");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 0.2");//
            h_hist[i]->GetXaxis()->SetRangeUser(0, 7);
            h_hist[i]->GetYaxis()->SetRangeUser(0, 5000); //2500
          }
          
          h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
          h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
          h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
          h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
          h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
          h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
          h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
          h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
          h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
          h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
          h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="dEtaHH>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
            
          }
          
          THStack *hs50 = new THStack("hs50", "");
          for(int i= 0; i<10 ; i++){ hs50->Add(h_hist[i], "hist50"); }
          hs50->Draw("SAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h50_1 = new TH1F("h50_1","Quadratic Sum from left",40,0,8); //left
          
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
         float B_l_50_9 = 0;
          
         float QuadraticSum_l_50 = 0;
         float Sum_l_50 = 0;
           
          for (int j=1; j<=40; j++) {
              
             S_l_50 = h_hist[10]->GetBinContent(j); //VBFSM
             //cout << " S of each bin = " << S_l_50 << endl;
             B_l_50_9 = h_hist[9]->GetBinContent(j);
             //cout << " B of ttbar of each bin = " << B_l_50_9 << endl;
             B_l_50_8 = h_hist[8]->GetBinContent(j);
             //cout << " B of single top of each bin = " << B_l_50_8 << endl;
             B_l_50_7 = h_hist[7]->GetBinContent(j);
             //cout << " B of Ztt of each bin = " << B_l_50_7 << endl;
             B_l_50_6 = h_hist[6]->GetBinContent(j);
             //cout << " B of Wlv of each bin = " << B_l_50_6 << endl;
             B_l_50_5 = h_hist[5]->GetBinContent(j);
             //cout << " B of Z of each bin = " << B_l_50_5 << endl;
             B_l_50_4 = h_hist[4]->GetBinContent(j);
             //cout << " B of Fake_W of each bin = " << B_l_50_4 << endl;
             B_l_50_3 = h_hist[3]->GetBinContent(j);
             //cout << " B of Fake_ttbar of each bin = " << B_l_50_3 << endl;
             B_l_50_2 = h_hist[2]->GetBinContent(j);
             //cout << " B of DY of each bin = " << B_l_50_2 << endl;
             B_l_50_1 = h_hist[1]->GetBinContent(j);
             //cout << " B of diboson of each bin = " << B_l_50_1 << endl;
             B_l_50_0 = h_hist[0]->GetBinContent(j);
             //cout << " B of SMH of each bin = " << B_l_50_0 << endl;
             
             float B_l_50 = 0;
             for(int i = 0; i<10; i++) { B_l_50 += h_hist[i]->GetBinContent(j); }
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
             //cout << " Quadratic sum from left = " << QuadraticSum_l_50 << endl;

             h50_1->SetBinContent(j,QuadraticSum_l_50);
             h50_1->SetLineColor(kBlue-9);
             h50_1->SetLineStyle(2);
             
             //cout << " ************************************ " << endl;
         }
             

         // ------------------------------------------------------------
         
         //cout << " " << endl;
         //cout << " ============== significance From right ============== " << endl;
         //cout << " " << endl;
          
        TH1F *h50_2 = new TH1F("h50_2","Quadratic Sum from right",40,0,8); //right
          
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
         float B_r_50_9 = 0;
          
         float QuadraticSum_r_50 = 0;
         float Sum_r_50 = 0;
          
          for (int j=40; j>=1; j--) {
              
            S_r_50 = h_hist[10]->GetBinContent(j); //VBFSM
            //cout << " S of each bin = " << S_r_50 << endl;
            B_r_50_9 = h_hist[9]->GetBinContent(j);
            //cout << " B of ttbar of each bin = " << B_r_50_9 << endl;
            B_r_50_8 = h_hist[8]->GetBinContent(j);
            //cout << " B of single top of each bin = " << B_r_50_8 << endl;
            B_r_50_7 = h_hist[7]->GetBinContent(j);
            //cout << " B of Ztt of each bin = " << B_r_50_7 << endl;
            B_r_50_6 = h_hist[6]->GetBinContent(j);
            //cout << " B of Wlv of each bin = " << B_r_50_6 << endl;
            B_r_50_5 = h_hist[5]->GetBinContent(j);
            //cout << " B of Z of each bin = " << B_r_50_5 << endl;
            B_r_50_4 = h_hist[4]->GetBinContent(j);
            //cout << " B of Fake_W of each bin = " << B_r_50_4 << endl;
            B_r_50_3 = h_hist[3]->GetBinContent(j);
            //cout << " B of Fake_ttbar of each bin = " << B_r_50_3 << endl;
            B_r_50_2 = h_hist[2]->GetBinContent(j);
            //cout << " B of DY of each bin = " << B_r_50_2 << endl;
            B_r_50_1 = h_hist[1]->GetBinContent(j);
            //cout << " B of diboson of each bin = " << B_r_50_1 << endl;
            B_r_50_0 = h_hist[0]->GetBinContent(j);
            //cout << " B of SMH of each bin = " << B_r_50_0 << endl;
            
            float B_r_50 = 0;
            for(int i = 0; i<10; i++) { B_r_50 += h_hist[i]->GetBinContent(j); }
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

            h50_2->SetBinContent(j,QuadraticSum_r_50);
            h50_2->SetLineColor(kGreen-9);
            h50_2->SetLineStyle(2);
            
            //cout << " ************************************ " << endl;
         }
         
          
          
          float rightmax50 = 1.1*h50_1->GetMaximum();
          float scale50 = 5000 / rightmax50;
          h50_1->Scale(scale50);
          h50_1->Draw("SAMEHIST");
          
          h50_2->Scale(scale50);
          h50_2->Draw("SAMEHIST");
          
        
          TGaxis*axis50 = new TGaxis(7,0,7,5000,0,rightmax50,510,"+L");
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
          
          for(int i= 10; i>=0 ; i--)
          {
              leg50->AddEntry(h_hist[i], h_titles[i].c_str());
          }
          leg50->AddEntry(h50_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
          leg50->AddEntry(h50_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
          leg50->Draw();
          
          c50 -> SaveAs("dEtaHH_SM.pdf");
      
    
    //   ===========================================================   helicityAngles1   ===========================================================
      
      TCanvas *c51 = new TCanvas ("c51", "helicityAngles1",980,580);
        
      TPad *pad511 = new TPad("pad511","",0,0,0.75,1);
      TPad *pad512 = new TPad("pad512","",0.73,0,1,1);
      pad511->Draw();
      pad512->Draw();
        
      pad511->cd();
      pad511->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,-1,1);
          h_hist[i]->GetXaxis()->SetTitle("helicity angles 1");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.1");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 7);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 3000); //2500
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="helicityAngles1>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs51 = new THStack("hs51", "");
      for(int i= 0; i<10 ; i++){ hs51->Add(h_hist[i], "hist51"); }
      hs51->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h51_1 = new TH1F("h51_1","Quadratic Sum from left",20,-1,1); //left
      
     float S_l_51 = 0;
     float B_l_51_0 = 0;
     float B_l_51_1 = 0;
     float B_l_51_2 = 0;
     float B_l_51_3 = 0;
     float B_l_51_4 = 0;
     float B_l_51_5 = 0;
     float B_l_51_6 = 0;
     float B_l_51_7 = 0;
     float B_l_51_8 = 0;
     float B_l_51_9 = 0;
      
     float QuadraticSum_l_51 = 0;
     float Sum_l_51 = 0;
       
      for (int j=1; j<=20; j++) {
          
         S_l_51 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_51 << endl;
         B_l_51_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_51_9 << endl;
         B_l_51_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_51_8 << endl;
         B_l_51_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_51_7 << endl;
         B_l_51_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_51_6 << endl;
         B_l_51_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_51_5 << endl;
         B_l_51_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_51_4 << endl;
         B_l_51_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_51_3 << endl;
         B_l_51_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_51_2 << endl;
         B_l_51_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_51_1 << endl;
         B_l_51_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_51_0 << endl;
         
         float B_l_51 = 0;
         for(int i = 0; i<10; i++) { B_l_51 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_51 << endl;
         
         float Bin_l_51 = 0;
         if (B_l_51 > 0){
             Bin_l_51 =  2* ( (S_l_51 + B_l_51) * log(1+S_l_51/B_l_51) - S_l_51 );
             //Bin_l_51 = (S_l_51/sqrt(B_l_51))*(S_l_51/sqrt(B_l_51));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_51) << endl; //
         

         Sum_l_51 += Bin_l_51 ;
         QuadraticSum_l_51 = sqrt(Sum_l_51);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_51 << endl;

         h51_1->SetBinContent(j,QuadraticSum_l_51);
         h51_1->SetLineColor(kBlue-9);
         h51_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h51_2 = new TH1F("h51_2","Quadratic Sum from right",20,-1,1); //right
      
     float S_r_51 = 0;
     float B_r_51_0 = 0;
     float B_r_51_1 = 0;
     float B_r_51_2 = 0;
     float B_r_51_3 = 0;
     float B_r_51_4 = 0;
     float B_r_51_5 = 0;
     float B_r_51_6 = 0;
     float B_r_51_7 = 0;
     float B_r_51_8 = 0;
     float B_r_51_9 = 0;
      
     float QuadraticSum_r_51 = 0;
     float Sum_r_51 = 0;
      
      for (int j=20; j>=1; j--) {
          
        S_r_51 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_51 << endl;
        B_r_51_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_51_9 << endl;
        B_r_51_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_51_8 << endl;
        B_r_51_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_51_7 << endl;
        B_r_51_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_51_6 << endl;
        B_r_51_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_51_5 << endl;
        B_r_51_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_51_4 << endl;
        B_r_51_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_51_3 << endl;
        B_r_51_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_51_2 << endl;
        B_r_51_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_51_1 << endl;
        B_r_51_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_51_0 << endl;
        
        float B_r_51 = 0;
        for(int i = 0; i<10; i++) { B_r_51 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_51 << endl;
        
        float Bin_r_51 = 0;
        if (B_r_51 > 0){
            Bin_r_51 =  2* ( (S_r_51 + B_r_51) * log(1+S_r_51/B_r_51) - S_r_51 );
            //Bin_r_51 = (S_r_51/sqrt(B_r_51))*(S_r_51/sqrt(B_r_51));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_51) << endl;
        

        Sum_r_51 += Bin_r_51 ;
        QuadraticSum_r_51 = sqrt(Sum_r_51);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_51 << endl;

        h51_2->SetBinContent(j,QuadraticSum_r_51);
        h51_2->SetLineColor(kGreen-9);
        h51_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax51 = 1.1*h51_1->GetMaximum();
      float scale51 = 3000 / rightmax51;
      h51_1->Scale(scale51);
      h51_1->Draw("SAMEHIST");
      
      h51_2->Scale(scale51);
      h51_2->Draw("SAMEHIST");
      
    
      TGaxis*axis51 = new TGaxis(7,0,7,3000,0,rightmax51,510,"+L");
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
      
      for(int i= 10; i>=0 ; i--)
      {
          leg51->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg51->AddEntry(h51_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg51->AddEntry(h51_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg51->Draw();
      
      c51 -> SaveAs("helicityAngles1_SM.pdf");
    
    
    //   ===========================================================   helicityAngles2   ===========================================================
      
      TCanvas *c52 = new TCanvas ("c52", "helicityAngles2",980,580);
        
      TPad *pad521 = new TPad("pad521","",0,0,0.75,1);
      TPad *pad522 = new TPad("pad522","",0.73,0,1,1);
      pad521->Draw();
      pad522->Draw();
        
      pad521->cd();
      pad521->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",20,-1,1);
          h_hist[i]->GetXaxis()->SetTitle("helicity angles 2");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.1");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 7);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 4000); //2500
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="helicityAngles2>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs52 = new THStack("hs52", "");
      for(int i= 0; i<10 ; i++){ hs52->Add(h_hist[i], "hist52"); }
      hs52->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h52_1 = new TH1F("h52_1","Quadratic Sum from left",20,-1,1); //left
      
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
     float B_l_52_9 = 0;
      
     float QuadraticSum_l_52 = 0;
     float Sum_l_52 = 0;
       
      for (int j=1; j<=20; j++) {
          
         S_l_52 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_52 << endl;
         B_l_52_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_52_9 << endl;
         B_l_52_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_52_8 << endl;
         B_l_52_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_52_7 << endl;
         B_l_52_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_52_6 << endl;
         B_l_52_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_52_5 << endl;
         B_l_52_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_52_4 << endl;
         B_l_52_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_52_3 << endl;
         B_l_52_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_52_2 << endl;
         B_l_52_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_52_1 << endl;
         B_l_52_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_52_0 << endl;
         
         float B_l_52 = 0;
         for(int i = 0; i<10; i++) { B_l_52 += h_hist[i]->GetBinContent(j); }
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
         //cout << " Quadratic sum from left = " << QuadraticSum_l_52 << endl;

         h52_1->SetBinContent(j,QuadraticSum_l_52);
         h52_1->SetLineColor(kBlue-9);
         h52_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h52_2 = new TH1F("h52_2","Quadratic Sum from right",20,-1,1); //right
      
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
     float B_r_52_9 = 0;
      
     float QuadraticSum_r_52 = 0;
     float Sum_r_52 = 0;
      
      for (int j=20; j>=1; j--) {
          
        S_r_52 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_52 << endl;
        B_r_52_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_52_9 << endl;
        B_r_52_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_52_8 << endl;
        B_r_52_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_52_7 << endl;
        B_r_52_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_52_6 << endl;
        B_r_52_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_52_5 << endl;
        B_r_52_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_52_4 << endl;
        B_r_52_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_52_3 << endl;
        B_r_52_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_52_2 << endl;
        B_r_52_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_52_1 << endl;
        B_r_52_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_52_0 << endl;
        
        float B_r_52 = 0;
        for(int i = 0; i<10; i++) { B_r_52 += h_hist[i]->GetBinContent(j); }
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

        h52_2->SetBinContent(j,QuadraticSum_r_52);
        h52_2->SetLineColor(kGreen-9);
        h52_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax52 = 1.1*h52_1->GetMaximum();
      float scale52 = 4000 / rightmax52;
      h52_1->Scale(scale52);
      h52_1->Draw("SAMEHIST");
      
      h52_2->Scale(scale52);
      h52_2->Draw("SAMEHIST");
      
    
      TGaxis*axis52 = new TGaxis(7,0,7,4000,0,rightmax52,510,"+L");
      axis52->SetTitle("Quadratic Sum of significance");
      axis52->SetTitleSize(0.03);
      axis52->SetLabelSize(0.025);
      axis52->Draw();
      
      pad522->cd();
      TLegend *leg52 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg52->SetBorderSize(1);
      leg52->SetFillColor(0);
      leg52->SetTextFont(42);
      leg52->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg52->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg52->AddEntry(h52_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg52->AddEntry(h52_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg52->Draw();
      
      c52 -> SaveAs("helicityAngles2_SM.pdf");
    
    
    //   ===========================================================   dPhiVBFj1MET   ===========================================================
      
      TCanvas *c61 = new TCanvas ("c61", "dPhiVBFj1MET",980,580);
        
      TPad *pad611 = new TPad("pad611","",0,0,0.75,1);
      TPad *pad612 = new TPad("pad612","",0.73,0,1,1);
      pad611->Draw();
      pad612->Draw();
        
      pad611->cd();
      pad611->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,7);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (VBFj1,MET)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2500); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="abs(phiVBFj1-METPhi)>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs61 = new THStack("hs61", "");
      for(int i= 0; i<10 ; i++){ hs61->Add(h_hist[i], "hist61"); }
      hs61->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h61_1 = new TH1F("h61_1","Quadratic Sum from left",40,0,7); //left
      
     float S_l_61 = 0;
     float B_l_61_0 = 0;
     float B_l_61_1 = 0;
     float B_l_61_2 = 0;
     float B_l_61_3 = 0;
     float B_l_61_4 = 0;
     float B_l_61_5 = 0;
     float B_l_61_6 = 0;
     float B_l_61_7 = 0;
     float B_l_61_8 = 0;
     float B_l_61_9 = 0;
      
     float QuadraticSum_l_61 = 0;
     float Sum_l_61 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_61 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_61 << endl;
         B_l_61_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_61_9 << endl;
         B_l_61_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_61_8 << endl;
         B_l_61_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_61_7 << endl;
         B_l_61_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_61_6 << endl;
         B_l_61_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_61_5 << endl;
         B_l_61_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_61_4 << endl;
         B_l_61_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_61_3 << endl;
         B_l_61_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_61_2 << endl;
         B_l_61_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_61_1 << endl;
         B_l_61_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_61_0 << endl;
         
         float B_l_61 = 0;
         for(int i = 0; i<10; i++) { B_l_61 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_61 << endl;
         
         float Bin_l_61 = 0;
         if (B_l_61 > 0){
             Bin_l_61 =  2* ( (S_l_61 + B_l_61) * log(1+S_l_61/B_l_61) - S_l_61 );
             //Bin_l_61 = (S_l_61/sqrt(B_l_61))*(S_l_61/sqrt(B_l_61));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_61) << endl; //
         

         Sum_l_61 += Bin_l_61 ;
         QuadraticSum_l_61 = sqrt(Sum_l_61);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_61 << endl;

         h61_1->SetBinContent(j,QuadraticSum_l_61);
         h61_1->SetLineColor(kBlue-9);
         h61_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h61_2 = new TH1F("h61_2","Quadratic Sum from right",40,0,7); //right
      
     float S_r_61 = 0;
     float B_r_61_0 = 0;
     float B_r_61_1 = 0;
     float B_r_61_2 = 0;
     float B_r_61_3 = 0;
     float B_r_61_4 = 0;
     float B_r_61_5 = 0;
     float B_r_61_6 = 0;
     float B_r_61_7 = 0;
     float B_r_61_8 = 0;
     float B_r_61_9 = 0;
      
     float QuadraticSum_r_61 = 0;
     float Sum_r_61 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_61 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_61 << endl;
        B_r_61_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_61_9 << endl;
        B_r_61_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_61_8 << endl;
        B_r_61_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_61_7 << endl;
        B_r_61_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_61_6 << endl;
        B_r_61_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_61_5 << endl;
        B_r_61_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_61_4 << endl;
        B_r_61_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_61_3 << endl;
        B_r_61_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_61_2 << endl;
        B_r_61_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_61_1 << endl;
        B_r_61_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_61_0 << endl;
        
        float B_r_61 = 0;
        for(int i = 0; i<10; i++) { B_r_61 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_61 << endl;
        
        float Bin_r_61 = 0;
        if (B_r_61 > 0){
            Bin_r_61 =  2* ( (S_r_61 + B_r_61) * log(1+S_r_61/B_r_61) - S_r_61 );
            //Bin_r_61 = (S_r_61/sqrt(B_r_61))*(S_r_61/sqrt(B_r_61));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_61) << endl;
        

        Sum_r_61 += Bin_r_61 ;
        QuadraticSum_r_61 = sqrt(Sum_r_61);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_61 << endl;

        h61_2->SetBinContent(j,QuadraticSum_r_61);
        h61_2->SetLineColor(kGreen-9);
        h61_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax61 = 1.1*h61_1->GetMaximum();
      float scale61 = 2500 / rightmax61;
      h61_1->Scale(scale61);
      h61_1->Draw("SAMEHIST");
      
      h61_2->Scale(scale61);
      h61_2->Draw("SAMEHIST");
      
    
    TGaxis*axis61 = new TGaxis(7,0,7,2500,0,rightmax61,510,"+L");
      axis61->SetTitle("Quadratic Sum of significance");
      axis61->SetTitleSize(0.03);
      axis61->SetLabelSize(0.025);
      axis61->Draw();
      
      pad612->cd();
      TLegend *leg61 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg61->SetBorderSize(1);
      leg61->SetFillColor(0);
      leg61->SetTextFont(42);
      leg61->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg61->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg61->AddEntry(h61_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg61->AddEntry(h61_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg61->Draw();
      
      c61 -> SaveAs("dPhiVBFj1MET_SM.pdf");
    
    
    //   ===========================================================   dPhiVBFj2MET   ===========================================================
      
      TCanvas *c62 = new TCanvas ("c62", "dPhiVBFj2MET",980,580);
        
      TPad *pad621 = new TPad("pad621","",0,0,0.75,1);
      TPad *pad622 = new TPad("pad622","",0.73,0,1,1);
      pad621->Draw();
      pad622->Draw();
        
      pad621->cd();
      pad621->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,7);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#phi (VBFj2,MET)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 1800); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="abs(phiVBFj2-METPhi)>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs62 = new THStack("hs62", "");
      for(int i= 0; i<10 ; i++){ hs62->Add(h_hist[i], "hist62"); }
      hs62->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h62_1 = new TH1F("h62_1","Quadratic Sum from left",40,0,7); //left
      
     float S_l_62 = 0;
     float B_l_62_0 = 0;
     float B_l_62_1 = 0;
     float B_l_62_2 = 0;
     float B_l_62_3 = 0;
     float B_l_62_4 = 0;
     float B_l_62_5 = 0;
     float B_l_62_6 = 0;
     float B_l_62_7 = 0;
     float B_l_62_8 = 0;
     float B_l_62_9 = 0;
      
     float QuadraticSum_l_62 = 0;
     float Sum_l_62 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_62 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_62 << endl;
         B_l_62_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_62_9 << endl;
         B_l_62_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_62_8 << endl;
         B_l_62_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_62_7 << endl;
         B_l_62_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_62_6 << endl;
         B_l_62_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_62_5 << endl;
         B_l_62_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_62_4 << endl;
         B_l_62_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_62_3 << endl;
         B_l_62_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_62_2 << endl;
         B_l_62_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_62_1 << endl;
         B_l_62_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_62_0 << endl;
         
         float B_l_62 = 0;
         for(int i = 0; i<10; i++) { B_l_62 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_62 << endl;
         
         float Bin_l_62 = 0;
         if (B_l_62 > 0){
             Bin_l_62 =  2* ( (S_l_62 + B_l_62) * log(1+S_l_62/B_l_62) - S_l_62 );
             //Bin_l_62 = (S_l_62/sqrt(B_l_62))*(S_l_62/sqrt(B_l_62));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_62) << endl; //
         

         Sum_l_62 += Bin_l_62 ;
         QuadraticSum_l_62 = sqrt(Sum_l_62);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_62 << endl;

         h62_1->SetBinContent(j,QuadraticSum_l_62);
         h62_1->SetLineColor(kBlue-9);
         h62_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h62_2 = new TH1F("h62_2","Quadratic Sum from right",40,0,7); //right
      
     float S_r_62 = 0;
     float B_r_62_0 = 0;
     float B_r_62_1 = 0;
     float B_r_62_2 = 0;
     float B_r_62_3 = 0;
     float B_r_62_4 = 0;
     float B_r_62_5 = 0;
     float B_r_62_6 = 0;
     float B_r_62_7 = 0;
     float B_r_62_8 = 0;
     float B_r_62_9 = 0;
      
     float QuadraticSum_r_62 = 0;
     float Sum_r_62 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_62 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_62 << endl;
        B_r_62_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_62_9 << endl;
        B_r_62_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_62_8 << endl;
        B_r_62_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_62_7 << endl;
        B_r_62_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_62_6 << endl;
        B_r_62_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_62_5 << endl;
        B_r_62_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_62_4 << endl;
        B_r_62_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_62_3 << endl;
        B_r_62_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_62_2 << endl;
        B_r_62_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_62_1 << endl;
        B_r_62_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_62_0 << endl;
        
        float B_r_62 = 0;
        for(int i = 0; i<10; i++) { B_r_62 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_62 << endl;
        
        float Bin_r_62 = 0;
        if (B_r_62 > 0){
            Bin_r_62 =  2* ( (S_r_62 + B_r_62) * log(1+S_r_62/B_r_62) - S_r_62 );
            //Bin_r_62 = (S_r_62/sqrt(B_r_62))*(S_r_62/sqrt(B_r_62));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_62) << endl;
        

        Sum_r_62 += Bin_r_62 ;
        QuadraticSum_r_62 = sqrt(Sum_r_62);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_62 << endl;

        h62_2->SetBinContent(j,QuadraticSum_r_62);
        h62_2->SetLineColor(kGreen-9);
        h62_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax62 = 1.1*h62_1->GetMaximum();
      float scale62 = 1800 / rightmax62;
      h62_1->Scale(scale62);
      h62_1->Draw("SAMEHIST");
      
      h62_2->Scale(scale62);
      h62_2->Draw("SAMEHIST");
      
    
    TGaxis*axis62 = new TGaxis(7,0,7,1800,0,rightmax62,510,"+L");
      axis62->SetTitle("Quadratic Sum of significance");
      axis62->SetTitleSize(0.03);
      axis62->SetLabelSize(0.025);
      axis62->Draw();
      
      pad622->cd();
      TLegend *leg62 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg62->SetBorderSize(1);
      leg62->SetFillColor(0);
      leg62->SetTextFont(42);
      leg62->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg62->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg62->AddEntry(h62_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg62->AddEntry(h62_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg62->Draw();
      
      c62 -> SaveAs("dPhiVBFj2MET_SM.pdf");
    
    
    //   ===========================================================   dEtaLepVBFj1   ===========================================================
      
      TCanvas *c63 = new TCanvas ("c63", "dEtaLepVBFj1",980,580);
        
      TPad *pad631 = new TPad("pad631","",0,0,0.75,1);
      TPad *pad632 = new TPad("pad632","",0.73,0,1,1);
      pad631->Draw();
      pad632->Draw();
        
      pad631->cd();
      pad631->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,7);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (VBFj1,Lep)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2000); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="abs(etaVBFj1-LepEta)>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs63 = new THStack("hs63", "");
      for(int i= 0; i<10 ; i++){ hs63->Add(h_hist[i], "hist63"); }
      hs63->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h63_1 = new TH1F("h63_1","Quadratic Sum from left",40,0,7); //left
      
     float S_l_63 = 0;
     float B_l_63_0 = 0;
     float B_l_63_1 = 0;
     float B_l_63_2 = 0;
     float B_l_63_3 = 0;
     float B_l_63_4 = 0;
     float B_l_63_5 = 0;
     float B_l_63_6 = 0;
     float B_l_63_7 = 0;
     float B_l_63_8 = 0;
     float B_l_63_9 = 0;
      
     float QuadraticSum_l_63 = 0;
     float Sum_l_63 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_63 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_63 << endl;
         B_l_63_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_63_9 << endl;
         B_l_63_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_63_8 << endl;
         B_l_63_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_63_7 << endl;
         B_l_63_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_63_6 << endl;
         B_l_63_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_63_5 << endl;
         B_l_63_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_63_4 << endl;
         B_l_63_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_63_3 << endl;
         B_l_63_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_63_2 << endl;
         B_l_63_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_63_1 << endl;
         B_l_63_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_63_0 << endl;
         
         float B_l_63 = 0;
         for(int i = 0; i<10; i++) { B_l_63 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_63 << endl;
         
         float Bin_l_63 = 0;
         if (B_l_63 > 0){
             Bin_l_63 =  2* ( (S_l_63 + B_l_63) * log(1+S_l_63/B_l_63) - S_l_63 );
             //Bin_l_63 = (S_l_63/sqrt(B_l_63))*(S_l_63/sqrt(B_l_63));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_63) << endl; //
         

         Sum_l_63 += Bin_l_63 ;
         QuadraticSum_l_63 = sqrt(Sum_l_63);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_63 << endl;

         h63_1->SetBinContent(j,QuadraticSum_l_63);
         h63_1->SetLineColor(kBlue-9);
         h63_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h63_2 = new TH1F("h63_2","Quadratic Sum from right",40,0,7); //right
      
     float S_r_63 = 0;
     float B_r_63_0 = 0;
     float B_r_63_1 = 0;
     float B_r_63_2 = 0;
     float B_r_63_3 = 0;
     float B_r_63_4 = 0;
     float B_r_63_5 = 0;
     float B_r_63_6 = 0;
     float B_r_63_7 = 0;
     float B_r_63_8 = 0;
     float B_r_63_9 = 0;
      
     float QuadraticSum_r_63 = 0;
     float Sum_r_63 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_63 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_63 << endl;
        B_r_63_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_63_9 << endl;
        B_r_63_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_63_8 << endl;
        B_r_63_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_63_7 << endl;
        B_r_63_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_63_6 << endl;
        B_r_63_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_63_5 << endl;
        B_r_63_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_63_4 << endl;
        B_r_63_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_63_3 << endl;
        B_r_63_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_63_2 << endl;
        B_r_63_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_63_1 << endl;
        B_r_63_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_63_0 << endl;
        
        float B_r_63 = 0;
        for(int i = 0; i<10; i++) { B_r_63 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_63 << endl;
        
        float Bin_r_63 = 0;
        if (B_r_63 > 0){
            Bin_r_63 =  2* ( (S_r_63 + B_r_63) * log(1+S_r_63/B_r_63) - S_r_63 );
            //Bin_r_63 = (S_r_63/sqrt(B_r_63))*(S_r_63/sqrt(B_r_63));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_63) << endl;
        

        Sum_r_63 += Bin_r_63 ;
        QuadraticSum_r_63 = sqrt(Sum_r_63);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_63 << endl;

        h63_2->SetBinContent(j,QuadraticSum_r_63);
        h63_2->SetLineColor(kGreen-9);
        h63_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax63 = 1.1*h63_1->GetMaximum();
      float scale63 = 2000 / rightmax63;
      h63_1->Scale(scale63);
      h63_1->Draw("SAMEHIST");
      
      h63_2->Scale(scale63);
      h63_2->Draw("SAMEHIST");
      
    
    TGaxis*axis63 = new TGaxis(7,0,7,2000,0,rightmax63,510,"+L");
      axis63->SetTitle("Quadratic Sum of significance");
      axis63->SetTitleSize(0.03);
      axis63->SetLabelSize(0.025);
      axis63->Draw();
      
      pad632->cd();
      TLegend *leg63 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg63->SetBorderSize(1);
      leg63->SetFillColor(0);
      leg63->SetTextFont(42);
      leg63->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg63->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg63->AddEntry(h63_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg63->AddEntry(h63_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg63->Draw();
      
      c63 -> SaveAs("dEtaLepVBFj1_SM.pdf");
    
    
    //   ===========================================================   dEtaLepVBFj2   ===========================================================
      
      TCanvas *c64 = new TCanvas ("c64", "dEtaLepVBFj2",980,580);
        
      TPad *pad641 = new TPad("pad641","",0,0,0.75,1);
      TPad *pad642 = new TPad("pad642","",0.73,0,1,1);
      pad641->Draw();
      pad642->Draw();
        
      pad641->cd();
      pad641->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,7);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (VBFj2,Lep)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 1800); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="abs(etaVBFj2-LepEta)>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs64 = new THStack("hs64", "");
      for(int i= 0; i<10 ; i++){ hs64->Add(h_hist[i], "hist64"); }
      hs64->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h64_1 = new TH1F("h64_1","Quadratic Sum from left",40,0,7); //left
      
     float S_l_64 = 0;
     float B_l_64_0 = 0;
     float B_l_64_1 = 0;
     float B_l_64_2 = 0;
     float B_l_64_3 = 0;
     float B_l_64_4 = 0;
     float B_l_64_5 = 0;
     float B_l_64_6 = 0;
     float B_l_64_7 = 0;
     float B_l_64_8 = 0;
     float B_l_64_9 = 0;
      
     float QuadraticSum_l_64 = 0;
     float Sum_l_64 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_64 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_64 << endl;
         B_l_64_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_64_9 << endl;
         B_l_64_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_64_8 << endl;
         B_l_64_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_64_7 << endl;
         B_l_64_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_64_6 << endl;
         B_l_64_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_64_5 << endl;
         B_l_64_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_64_4 << endl;
         B_l_64_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_64_3 << endl;
         B_l_64_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_64_2 << endl;
         B_l_64_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_64_1 << endl;
         B_l_64_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_64_0 << endl;
         
         float B_l_64 = 0;
         for(int i = 0; i<10; i++) { B_l_64 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_64 << endl;
         
         float Bin_l_64 = 0;
         if (B_l_64 > 0){
             Bin_l_64 =  2* ( (S_l_64 + B_l_64) * log(1+S_l_64/B_l_64) - S_l_64 );
             //Bin_l_64 = (S_l_64/sqrt(B_l_64))*(S_l_64/sqrt(B_l_64));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_64) << endl; //
         

         Sum_l_64 += Bin_l_64 ;
         QuadraticSum_l_64 = sqrt(Sum_l_64);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_64 << endl;

         h64_1->SetBinContent(j,QuadraticSum_l_64);
         h64_1->SetLineColor(kBlue-9);
         h64_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h64_2 = new TH1F("h64_2","Quadratic Sum from right",40,0,7); //right
      
     float S_r_64 = 0;
     float B_r_64_0 = 0;
     float B_r_64_1 = 0;
     float B_r_64_2 = 0;
     float B_r_64_3 = 0;
     float B_r_64_4 = 0;
     float B_r_64_5 = 0;
     float B_r_64_6 = 0;
     float B_r_64_7 = 0;
     float B_r_64_8 = 0;
     float B_r_64_9 = 0;
      
     float QuadraticSum_r_64 = 0;
     float Sum_r_64 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_64 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_64 << endl;
        B_r_64_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_64_9 << endl;
        B_r_64_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_64_8 << endl;
        B_r_64_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_64_7 << endl;
        B_r_64_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_64_6 << endl;
        B_r_64_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_64_5 << endl;
        B_r_64_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_64_4 << endl;
        B_r_64_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_64_3 << endl;
        B_r_64_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_64_2 << endl;
        B_r_64_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_64_1 << endl;
        B_r_64_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_64_0 << endl;
        
        float B_r_64 = 0;
        for(int i = 0; i<10; i++) { B_r_64 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_64 << endl;
        
        float Bin_r_64 = 0;
        if (B_r_64 > 0){
            Bin_r_64 =  2* ( (S_r_64 + B_r_64) * log(1+S_r_64/B_r_64) - S_r_64 );
            //Bin_r_64 = (S_r_64/sqrt(B_r_64))*(S_r_64/sqrt(B_r_64));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_64) << endl;
        

        Sum_r_64 += Bin_r_64 ;
        QuadraticSum_r_64 = sqrt(Sum_r_64);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_64 << endl;

        h64_2->SetBinContent(j,QuadraticSum_r_64);
        h64_2->SetLineColor(kGreen-9);
        h64_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax64 = 1.1*h64_1->GetMaximum();
      float scale64 = 1800 / rightmax64;
      h64_1->Scale(scale64);
      h64_1->Draw("SAMEHIST");
      
      h64_2->Scale(scale64);
      h64_2->Draw("SAMEHIST");
      
    
    TGaxis*axis64 = new TGaxis(7,0,7,1800,0,rightmax64,510,"+L");
      axis64->SetTitle("Quadratic Sum of significance");
      axis64->SetTitleSize(0.03);
      axis64->SetLabelSize(0.025);
      axis64->Draw();
      
      pad642->cd();
      TLegend *leg64 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg64->SetBorderSize(1);
      leg64->SetFillColor(0);
      leg64->SetTextFont(42);
      leg64->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg64->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg64->AddEntry(h64_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg64->AddEntry(h64_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg64->Draw();
      
      c64 -> SaveAs("dEtaLepVBFj2_SM.pdf");
     
    
    //   ===========================================================   dEtaTauVBFj1   ===========================================================
      
      TCanvas *c65 = new TCanvas ("c65", "dEtaTauVBFj1",980,580);
        
      TPad *pad651 = new TPad("pad651","",0,0,0.75,1);
      TPad *pad652 = new TPad("pad652","",0.73,0,1,1);
      pad651->Draw();
      pad652->Draw();
        
      pad651->cd();
      pad651->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,7);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (VBFj1,Tau)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2000); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="abs(etaVBFj1-TauEta)>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs65 = new THStack("hs65", "");
      for(int i= 0; i<10 ; i++){ hs65->Add(h_hist[i], "hist65"); }
      hs65->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h65_1 = new TH1F("h65_1","Quadratic Sum from left",40,0,7); //left
      
     float S_l_65 = 0;
     float B_l_65_0 = 0;
     float B_l_65_1 = 0;
     float B_l_65_2 = 0;
     float B_l_65_3 = 0;
     float B_l_65_4 = 0;
     float B_l_65_5 = 0;
     float B_l_65_6 = 0;
     float B_l_65_7 = 0;
     float B_l_65_8 = 0;
     float B_l_65_9 = 0;
      
     float QuadraticSum_l_65 = 0;
     float Sum_l_65 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_65 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_65 << endl;
         B_l_65_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_65_9 << endl;
         B_l_65_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_65_8 << endl;
         B_l_65_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_65_7 << endl;
         B_l_65_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_65_6 << endl;
         B_l_65_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_65_5 << endl;
         B_l_65_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_65_4 << endl;
         B_l_65_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_65_3 << endl;
         B_l_65_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_65_2 << endl;
         B_l_65_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_65_1 << endl;
         B_l_65_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_65_0 << endl;
         
         float B_l_65 = 0;
         for(int i = 0; i<10; i++) { B_l_65 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_65 << endl;
         
         float Bin_l_65 = 0;
         if (B_l_65 > 0){
             Bin_l_65 =  2* ( (S_l_65 + B_l_65) * log(1+S_l_65/B_l_65) - S_l_65 );
             //Bin_l_65 = (S_l_65/sqrt(B_l_65))*(S_l_65/sqrt(B_l_65));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_65) << endl; //
         

         Sum_l_65 += Bin_l_65 ;
         QuadraticSum_l_65 = sqrt(Sum_l_65);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_65 << endl;

         h65_1->SetBinContent(j,QuadraticSum_l_65);
         h65_1->SetLineColor(kBlue-9);
         h65_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h65_2 = new TH1F("h65_2","Quadratic Sum from right",40,0,7); //right
      
     float S_r_65 = 0;
     float B_r_65_0 = 0;
     float B_r_65_1 = 0;
     float B_r_65_2 = 0;
     float B_r_65_3 = 0;
     float B_r_65_4 = 0;
     float B_r_65_5 = 0;
     float B_r_65_6 = 0;
     float B_r_65_7 = 0;
     float B_r_65_8 = 0;
     float B_r_65_9 = 0;
      
     float QuadraticSum_r_65 = 0;
     float Sum_r_65 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_65 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_65 << endl;
        B_r_65_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_65_9 << endl;
        B_r_65_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_65_8 << endl;
        B_r_65_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_65_7 << endl;
        B_r_65_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_65_6 << endl;
        B_r_65_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_65_5 << endl;
        B_r_65_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_65_4 << endl;
        B_r_65_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_65_3 << endl;
        B_r_65_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_65_2 << endl;
        B_r_65_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_65_1 << endl;
        B_r_65_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_65_0 << endl;
        
        float B_r_65 = 0;
        for(int i = 0; i<10; i++) { B_r_65 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_65 << endl;
        
        float Bin_r_65 = 0;
        if (B_r_65 > 0){
            Bin_r_65 =  2* ( (S_r_65 + B_r_65) * log(1+S_r_65/B_r_65) - S_r_65 );
            //Bin_r_65 = (S_r_65/sqrt(B_r_65))*(S_r_65/sqrt(B_r_65));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_65) << endl;
        

        Sum_r_65 += Bin_r_65 ;
        QuadraticSum_r_65 = sqrt(Sum_r_65);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_65 << endl;

        h65_2->SetBinContent(j,QuadraticSum_r_65);
        h65_2->SetLineColor(kGreen-9);
        h65_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax65 = 1.1*h65_1->GetMaximum();
      float scale65 = 2000 / rightmax65;
      h65_1->Scale(scale65);
      h65_1->Draw("SAMEHIST");
      
      h65_2->Scale(scale65);
      h65_2->Draw("SAMEHIST");
      
    
    TGaxis*axis65 = new TGaxis(7,0,7,2000,0,rightmax65,510,"+L");
      axis65->SetTitle("Quadratic Sum of significance");
      axis65->SetTitleSize(0.03);
      axis65->SetLabelSize(0.025);
      axis65->Draw();
      
      pad652->cd();
      TLegend *leg65 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg65->SetBorderSize(1);
      leg65->SetFillColor(0);
      leg65->SetTextFont(42);
      leg65->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg65->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg65->AddEntry(h65_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg65->AddEntry(h65_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg65->Draw();
      
      c65 -> SaveAs("dEtaTauVBFj1_SM.pdf");
    
    
    //   ===========================================================   dEtaTauVBFj2   ===========================================================
      
      TCanvas *c66 = new TCanvas ("c66", "dEtaTauVBFj2",980,580);
        
      TPad *pad661 = new TPad("pad661","",0,0,0.75,1);
      TPad *pad662 = new TPad("pad662","",0.73,0,1,1);
      pad661->Draw();
      pad662->Draw();
        
      pad661->cd();
      pad661->SetTickx();
      gStyle->SetOptStat(kFALSE);
      
      for (int i=0; i<n_smp; i++){
        h_nm = h_title[i].c_str();
          h_hist[i] = new TH1F(h_nm, "",40,0,7);
          h_hist[i]->GetXaxis()->SetTitle("#Delta#eta (VBFj2,Tau)");
        h_hist[i]->GetYaxis()->SetTitle("Events/ 0.175");//
        //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
        h_hist[i]->GetYaxis()->SetRangeUser(0, 2000); //900
      }
      
      h_hist[0]->SetLineColor(kOrange+7); h_hist[0]->SetMarkerColor(kOrange+7); h_hist[0]->SetFillColor(kOrange+7); //SM_H
      h_hist[1]->SetLineColor(kGray+1); h_hist[1]->SetMarkerColor(kGray+1); h_hist[1]->SetFillColor(kGray+1); //diboson
      h_hist[2]->SetLineColor(kOrange+1); h_hist[2]->SetMarkerColor(kOrange+1); h_hist[2]->SetFillColor(kOrange+1); //DY
      h_hist[3]->SetLineColor(kPink+1); h_hist[3]->SetMarkerColor(kPink+1); h_hist[3]->SetFillColor(kPink+1); //Fake_ttbar
      h_hist[4]->SetLineColor(kPink-1); h_hist[4]->SetMarkerColor(kPink-1); h_hist[4]->SetFillColor(kPink-1); //Fake_W
      h_hist[5]->SetLineColor(kAzure+7); h_hist[5]->SetMarkerColor(kAzure+7); h_hist[5]->SetFillColor(kAzure+7); //Zll
      h_hist[6]->SetLineColor(kGreen-6); h_hist[6]->SetMarkerColor(kGreen-6); h_hist[6]->SetFillColor(kGreen-6); //Wlv
      h_hist[7]->SetLineColor(kAzure+3); h_hist[7]->SetMarkerColor(kAzure+3); h_hist[7]->SetFillColor(kAzure+3); //Ztautau
      h_hist[8]->SetLineColor(kOrange-1); h_hist[8]->SetMarkerColor(kOrange-1); h_hist[8]->SetFillColor(kOrange-1); //singletop
      h_hist[9]->SetLineColor(kOrange); h_hist[9]->SetMarkerColor(kOrange); h_hist[9]->SetFillColor(kOrange); //ttbar
      h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBFSM
          //h_hist[11]->SetMarkerStyle(20); h_hist[11]->SetMarkerSize(0.8); h_hist[11]->SetLineColor(kBlack);

    
      for (int i=0; i<n_smp; i++){
          hist_draw[i]="abs(etaVBFj2-TauEta)>>"+h_title[i];
      }
      
      for(int i = 0; i<n_smp; i++){
        
        if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
        else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
        else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
        else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
            //else if (i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data
        else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
        
      }
      
      THStack *hs66 = new THStack("hs66", "");
      for(int i= 0; i<10 ; i++){ hs66->Add(h_hist[i], "hist66"); }
      hs66->Draw("SAMEHIST");
    
      for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(248633.79)*(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBFSM
          }
    
          // for(int i = 0; i<n_smp; i++){ if(i == 11){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "ESAMEHISTP");} //data }

     //cout << " ============== significance From left ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h66_1 = new TH1F("h66_1","Quadratic Sum from left",40,0,7); //left
      
     float S_l_66 = 0;
     float B_l_66_0 = 0;
     float B_l_66_1 = 0;
     float B_l_66_2 = 0;
     float B_l_66_3 = 0;
     float B_l_66_4 = 0;
     float B_l_66_5 = 0;
     float B_l_66_6 = 0;
     float B_l_66_7 = 0;
     float B_l_66_8 = 0;
     float B_l_66_9 = 0;
      
     float QuadraticSum_l_66 = 0;
     float Sum_l_66 = 0;
       
      for (int j=1; j<=40; j++) {
          
         S_l_66 = h_hist[10]->GetBinContent(j); //VBFSM
         //cout << " S of each bin = " << S_l_66 << endl;
         B_l_66_9 = h_hist[9]->GetBinContent(j);
         //cout << " B of ttbar of each bin = " << B_l_66_9 << endl;
         B_l_66_8 = h_hist[8]->GetBinContent(j);
         //cout << " B of single top of each bin = " << B_l_66_8 << endl;
         B_l_66_7 = h_hist[7]->GetBinContent(j);
         //cout << " B of Ztt of each bin = " << B_l_66_7 << endl;
         B_l_66_6 = h_hist[6]->GetBinContent(j);
         //cout << " B of Wlv of each bin = " << B_l_66_6 << endl;
         B_l_66_5 = h_hist[5]->GetBinContent(j);
         //cout << " B of Z of each bin = " << B_l_66_5 << endl;
         B_l_66_4 = h_hist[4]->GetBinContent(j);
         //cout << " B of Fake_W of each bin = " << B_l_66_4 << endl;
         B_l_66_3 = h_hist[3]->GetBinContent(j);
         //cout << " B of Fake_ttbar of each bin = " << B_l_66_3 << endl;
         B_l_66_2 = h_hist[2]->GetBinContent(j);
         //cout << " B of DY of each bin = " << B_l_66_2 << endl;
         B_l_66_1 = h_hist[1]->GetBinContent(j);
         //cout << " B of diboson of each bin = " << B_l_66_1 << endl;
         B_l_66_0 = h_hist[0]->GetBinContent(j);
         //cout << " B of SMH of each bin = " << B_l_66_0 << endl;
         
         float B_l_66 = 0;
         for(int i = 0; i<10; i++) { B_l_66 += h_hist[i]->GetBinContent(j); }
         //cout << " B of each bin = " << B_l_66 << endl;
         
         float Bin_l_66 = 0;
         if (B_l_66 > 0){
             Bin_l_66 =  2* ( (S_l_66 + B_l_66) * log(1+S_l_66/B_l_66) - S_l_66 );
             //Bin_l_66 = (S_l_66/sqrt(B_l_66))*(S_l_66/sqrt(B_l_66));
             }
         //cout << " Bin = " << j << endl;
         //cout << " significance of each bin = " << sqrt(Bin_l_66) << endl; //
         

         Sum_l_66 += Bin_l_66 ;
         QuadraticSum_l_66 = sqrt(Sum_l_66);
         //cout << " Quadratic sum from left = " << QuadraticSum_l_66 << endl;

         h66_1->SetBinContent(j,QuadraticSum_l_66);
         h66_1->SetLineColor(kBlue-9);
         h66_1->SetLineStyle(2);
         
         //cout << " ************************************ " << endl;
     }
         

     // ------------------------------------------------------------
     
     //cout << " " << endl;
     //cout << " ============== significance From right ============== " << endl;
     //cout << " " << endl;
      
    TH1F *h66_2 = new TH1F("h66_2","Quadratic Sum from right",40,0,7); //right
      
     float S_r_66 = 0;
     float B_r_66_0 = 0;
     float B_r_66_1 = 0;
     float B_r_66_2 = 0;
     float B_r_66_3 = 0;
     float B_r_66_4 = 0;
     float B_r_66_5 = 0;
     float B_r_66_6 = 0;
     float B_r_66_7 = 0;
     float B_r_66_8 = 0;
     float B_r_66_9 = 0;
      
     float QuadraticSum_r_66 = 0;
     float Sum_r_66 = 0;
      
      for (int j=40; j>=1; j--) {
          
        S_r_66 = h_hist[10]->GetBinContent(j); //VBFSM
        //cout << " S of each bin = " << S_r_66 << endl;
        B_r_66_9 = h_hist[9]->GetBinContent(j);
        //cout << " B of ttbar of each bin = " << B_r_66_9 << endl;
        B_r_66_8 = h_hist[8]->GetBinContent(j);
        //cout << " B of single top of each bin = " << B_r_66_8 << endl;
        B_r_66_7 = h_hist[7]->GetBinContent(j);
        //cout << " B of Ztt of each bin = " << B_r_66_7 << endl;
        B_r_66_6 = h_hist[6]->GetBinContent(j);
        //cout << " B of Wlv of each bin = " << B_r_66_6 << endl;
        B_r_66_5 = h_hist[5]->GetBinContent(j);
        //cout << " B of Z of each bin = " << B_r_66_5 << endl;
        B_r_66_4 = h_hist[4]->GetBinContent(j);
        //cout << " B of Fake_W of each bin = " << B_r_66_4 << endl;
        B_r_66_3 = h_hist[3]->GetBinContent(j);
        //cout << " B of Fake_ttbar of each bin = " << B_r_66_3 << endl;
        B_r_66_2 = h_hist[2]->GetBinContent(j);
        //cout << " B of DY of each bin = " << B_r_66_2 << endl;
        B_r_66_1 = h_hist[1]->GetBinContent(j);
        //cout << " B of diboson of each bin = " << B_r_66_1 << endl;
        B_r_66_0 = h_hist[0]->GetBinContent(j);
        //cout << " B of SMH of each bin = " << B_r_66_0 << endl;
        
        float B_r_66 = 0;
        for(int i = 0; i<10; i++) { B_r_66 += h_hist[i]->GetBinContent(j); }
        //cout << " B of each bin = " << B_r_66 << endl;
        
        float Bin_r_66 = 0;
        if (B_r_66 > 0){
            Bin_r_66 =  2* ( (S_r_66 + B_r_66) * log(1+S_r_66/B_r_66) - S_r_66 );
            //Bin_r_66 = (S_r_66/sqrt(B_r_66))*(S_r_66/sqrt(B_r_66));
            }
        //cout << " Bin = " << j << endl;
        //cout << " significance of each bin = " << sqrt(Bin_r_66) << endl;
        

        Sum_r_66 += Bin_r_66 ;
        QuadraticSum_r_66 = sqrt(Sum_r_66);
        //cout << " Quadratic sum from right = " << QuadraticSum_r_66 << endl;

        h66_2->SetBinContent(j,QuadraticSum_r_66);
        h66_2->SetLineColor(kGreen-9);
        h66_2->SetLineStyle(2);
        
        //cout << " ************************************ " << endl;
     }
     
      
      
      float rightmax66 = 1.1*h66_1->GetMaximum();
      float scale66 = 2000 / rightmax66;
      h66_1->Scale(scale66);
      h66_1->Draw("SAMEHIST");
      
      h66_2->Scale(scale66);
      h66_2->Draw("SAMEHIST");
      
    
    TGaxis*axis66 = new TGaxis(7,0,7,2000,0,rightmax66,510,"+L");
      axis66->SetTitle("Quadratic Sum of significance");
      axis66->SetTitleSize(0.03);
      axis66->SetLabelSize(0.025);
      axis66->Draw();
      
      pad662->cd();
      TLegend *leg66 = new TLegend(0.008, 0.1, 0.985,0.9);
      leg66->SetBorderSize(1);
      leg66->SetFillColor(0);
      leg66->SetTextFont(42);
      leg66->SetTextSize(0.053);
      
      for(int i= 10; i>=0 ; i--)
      {
          leg66->AddEntry(h_hist[i], h_titles[i].c_str());
      }
      leg66->AddEntry(h66_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
      leg66->AddEntry(h66_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
      leg66->Draw();
      
      c66 -> SaveAs("dEtaTauVBFj2_SM.pdf");
        
        //  ----------------------------- ps file -----------------------------
        
          
        TPostScript *ps = new TPostScript("VBF_plots_total_bkg_SM.ps",112);

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
        c26->Draw();
        ps->NewPage();
        c27->Draw();
        ps->NewPage();
        c28->Draw();
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
        c40->Draw();
        ps->NewPage();
        c41->Draw();
        ps->NewPage();
        c42->Draw();
        ps->NewPage();
        c43->Draw();
        ps->NewPage();
        c44->Draw();
        ps->NewPage();
        c45->Draw();
        ps->NewPage();
        c47->Draw();
        ps->NewPage();
        c48->Draw();
        ps->NewPage();
        c49->Draw();
        ps->NewPage();
        c50->Draw();
        ps->NewPage();
        c51->Draw();
        ps->NewPage();
        c52->Draw();
        ps->NewPage();
        c53->Draw();
        ps->NewPage();
        c54->Draw();
        ps->NewPage();
        c55->Draw();
        ps->NewPage();
        c56->Draw();
        ps->NewPage();
        c57->Draw();
        ps->NewPage();
        c58->Draw();
        ps->NewPage();
        c59->Draw();
        ps->NewPage();
        c60->Draw();
        ps->NewPage();
        c61->Draw();
        ps->NewPage();
        c62->Draw();
        ps->NewPage();
        c63->Draw();
        ps->NewPage();
        c64->Draw();
        ps->NewPage();
        c65->Draw();
        ps->NewPage();
        c66->Draw();
        
        
        // =================  Significance of each variable  =================
        
        cout << " pTBB = " << QuadraticSum_l_1 << endl;
        cout << " pTB1 = " << QuadraticSum_l_2 << endl;
        cout << " pTB2 = " << QuadraticSum_l_3 << endl;
        cout << " mBB = " << QuadraticSum_l_4 << endl;
        cout << " dPhiBB = " << QuadraticSum_l_5 << endl;
        cout << " dEtaBB = " << QuadraticSum_l_6 << endl;
        cout << " dRBB = " << QuadraticSum_l_7 << endl;
        
        cout << " " << endl;
        
        cout << " pTtautau = " << QuadraticSum_l_8 << endl;
        cout << " dPtLepTau = " << QuadraticSum_l_19 << endl;
        cout << " TauPt = " << QuadraticSum_l_9 << endl;
        cout << " LepPt = " << QuadraticSum_l_10 << endl;
        cout << " mMMC = " << QuadraticSum_l_11 << endl;
    
        cout << " dPhiLepTau = " << QuadraticSum_l_12 << endl;
        cout << " TauPhi = " << QuadraticSum_l_13 << endl;
        cout << " LepPhi = " << QuadraticSum_l_14 << endl;
    
        cout << " dEtaLepTau = " << QuadraticSum_l_15 << endl;
        cout << " TauEta = " << QuadraticSum_l_16 << endl;
        cout << " LepEta = " << QuadraticSum_l_17 << endl;
    
        cout << " dRLepTau = " << QuadraticSum_l_18 << endl;
        cout << " MT2 = " << QuadraticSum_l_20 << endl;
        
        cout << " " << endl;
        
        cout << " pTVBFj1 = " << QuadraticSum_l_21 << endl;
        cout << " pTVBFj2 = " << QuadraticSum_l_22 << endl;
        cout << " mVBFjj = " << QuadraticSum_l_23 << endl;
    
        cout << " phiVBFj1 = " << QuadraticSum_l_24 << endl;
        cout << " phiVBFj2 = " << QuadraticSum_l_25 << endl;
        cout << " dPhiVBFjj = " << QuadraticSum_l_60 << endl;
        
        cout << " etaVBFj1 = " << QuadraticSum_l_27 << endl;
        cout << " etaVBFj2 = " << QuadraticSum_l_28 << endl;
        cout << " dEtaVBFjj = " << QuadraticSum_l_26 << endl;
    
        cout << " dRVBFjj = " << QuadraticSum_l_29 << endl;
        
        cout << " " << endl;
        
        cout << " MET = " << QuadraticSum_l_30 << endl;
        cout << " METCent = " << QuadraticSum_l_31 << endl;
        cout << " dPhiLep0MET = " << QuadraticSum_l_32 << endl;
        cout << " dPhiLep1MET = " << QuadraticSum_l_33 << endl;
        cout << " dPhiHttMET = " << QuadraticSum_l_34 << endl;
        cout << " dPhiHbbMET = " << QuadraticSum_l_35 << endl;
        
        cout << " " << endl;
            
        cout << " HT = " << QuadraticSum_l_37 << endl;
        cout << " dPhiHBB = " << QuadraticSum_l_38 << endl;
        cout << " dEtaHBB = " << QuadraticSum_l_39 << endl;
        cout << " dEtaHH = " << QuadraticSum_l_50 << endl;
        cout << " dRHH = " << QuadraticSum_l_40 << endl;
        
        cout << " " << endl;
        
        cout << " MtW = " << QuadraticSum_l_41 << endl;
        cout << " Mvis = " << QuadraticSum_l_42 << endl;
        cout << " Mw = " << QuadraticSum_l_43 << endl;
        cout << " Mt = " << QuadraticSum_l_44 << endl;
           
        cout << " " << endl;
         
        cout << " MtTotal = " << QuadraticSum_l_45 << endl;
        cout << " MtWLep1 = " << QuadraticSum_l_47 << endl;
        cout << " METSig = " << QuadraticSum_l_48 << endl;
        cout << " helicityAngles1 = " << QuadraticSum_l_51 << endl;
        cout << " helicityAngles2 = " << QuadraticSum_l_52 << endl;
     
        cout << " " << endl;
    
        cout << " dRVBFj1Lep0 = " << QuadraticSum_l_49 << endl;
        cout << " dRVBFj2Lep0 = " << QuadraticSum_l_53 << endl;
        cout << " dRVBFj1Tau = " << QuadraticSum_l_54 << endl;
        cout << " dRVBFj2Tau = " << QuadraticSum_l_55 << endl;
    
        cout << " dRVBFj1B1 = " << QuadraticSum_l_56 << endl;
        cout << " dRVBFj1B2 = " << QuadraticSum_l_57 << endl;
        cout << " dRVBFj2B1 = " << QuadraticSum_l_58 << endl;
        cout << " dRVBFj2B2 = " << QuadraticSum_l_59 << endl;
     
        cout << " " << endl;
    
        cout << " dPhiVBFj1MET = " << QuadraticSum_l_61 << endl;
        cout << " dPhiVBFj2MET = " << QuadraticSum_l_62 << endl;
        
        cout << " dEtaLepVBFj1 = " << QuadraticSum_l_63 << endl;
        cout << " dEtaLepVBFj2 = " << QuadraticSum_l_64 << endl;
         

        cout << " dEtaTauVBFj1 = " << QuadraticSum_l_65 << endl;
        cout << " dEtaTauVBFj2 = " << QuadraticSum_l_66 << endl;
          */
     
      }

