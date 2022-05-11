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
void SLT_txt_001_TotalBkg(){

    /*
  const int n_smp = 10;
  string smp_tree[n_smp] = { "SMH", "diboson", "DY", "fake", "Z", "W", "Ztt", "singletop", "ttbar", "VBF001" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "job_SR_data18/Ntuple/"; // path to input files
  string ana_tag = "FinalNtuple.TauLH.";
  string smp_names[n_smp] = { "SM_H", "diboson", "DY", "fake", "Z", "W", "Ztt", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
    
  for (int i=0; i<n_smp; i++)
    {
      smp = pwd + ana_tag + smp_names[i] +".0.root";
      cout<<smp<<endl;
      chain_smp[i] = new TChain(smp_tree[i].c_str());
      chain_smp[i]->Add(smp.c_str());
    }
  
  string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake", "Z", "Wl#nu", "Z#tau#tau", "single top", "ttbar", "VBF001 x 248634.031", };  // only for legend
    
  string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake", "Z", "W", "Ztt", "singletop", "ttbar", "VBF001", };
    
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];*/
    
    const int n_smp = 11;
    string smp_tree[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Z", "W", "Ztt", "singletop", "ttbar", "VBF001" };
    string smp;
    TChain  *chain_smp[n_smp];
    
    string pwd = "FullRun2_SLT/";
    //string pwd = "SLT_job_SR_data18/Ntuple/"; // path to input files
    string ana_tag = "FinalNtuple.TauLH.";
    string smp_names[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Zll", "W", "Ztautau", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l0cvv0cv1." };
    //string smp_names[n_smp] = { "SM_H", "diboson", "DY", "ttbar", "W", "Zll", "W", "Ztautau1", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
      
    for (int i=0; i<n_smp; i++)
      {
        smp = pwd + ana_tag + smp_names[i] +".0.root";
        cout<<smp<<endl;
        chain_smp[i] = new TChain(smp_tree[i].c_str());
        chain_smp[i]->Add(smp.c_str());
      }
    
    string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake_ttbar", "Fake_W", "Zee/#mu#mu", "W", "Z#tau#tau", "single top", "ttbar", "VBF001 x 248633.791", };  // only for legend
      
    string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake_ttbar", "Fake_W", "Z", "W", "Ztt", "singletop", "ttbar", "VBF001", };
      
    TH1F * h_hist[n_smp];
    const char *h_nm;
    string hist_draw[n_smp];
    

  //   ===========================================================   Mhh   ===========================================================
  
  TCanvas *c1 = new TCanvas ("c1", "Mhh",980,580);
    
  TPad *pad11 = new TPad("pad1","",0,0,0.75,1);
  TPad *pad12 = new TPad("pad2","",0.73,0,1,1);
  pad11->Draw();
  pad12->Draw();
    
  pad11->cd();
  pad11->SetTickx();
  gStyle->SetOptStat(kFALSE);
  
  for (int i=0; i<n_smp; i++){
    h_nm = h_title[i].c_str();
    h_hist[i] = new TH1F(h_nm, "",70,0,3500);
    h_hist[i]->GetXaxis()->SetTitle("m_{hh} [GeV]");
    h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");
    //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
    h_hist[i]->GetYaxis()->SetRangeUser(0, 11000);
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
  h_hist[10]->SetLineColor(kRed); h_hist[10]->SetMarkerColor(kRed); //VBF_SM
  
  
    for (int i=0; i<n_smp; i++){
        hist_draw[i]="Mhh*0.001>>"+h_title[i];
    }
    
    for(int i = 0; i<n_smp; i++){
      
      if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake
      else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1))",  "SAMEHIST");} //Fake_W
      else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))",  "SAMEHIST");} //Wlv
      else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0))", "SAMEHIST");} //ttbar
      else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))", "SAMEHIST");} //VBF001
      else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0))",  "SAMEHIST");
      
    }
    
  THStack *hs1 = new THStack("hs1", "");
  for(int i= 0; i<10 ; i++){ hs1->Add(h_hist[i], "hist1"); }
  hs1->Draw("SAMEHIST");
    
    //cout << " ============== significance From left ============== " << endl;
         
       TH1F *h1_1 = new TH1F("h1_1","Quadratic Sum from left",70,0,3500); //left
       
       double QuadraticSum_l_1 = 0;
       double R_l_1 = 0;
       double E_l_1 = 0;
       double EE_l_1 = 0;
          
         for (int j=1; j<=70; j++) {
             
             double S = h_hist[10]->GetBinContent(j);
             double dS = h_hist[10]->GetBinError(j);
             double B = 0;   for(int i = 0; i<10; i++) { B += h_hist[i]->GetBinContent(j); }
             double dB = 0;   for(int i = 0; i<10; i++) { dB += h_hist[i]->GetBinError(j); }
            
             if( B > 0 && S > 0) {
                 double LSB = log(1+S/B);
                 R_l_1 +=  2* ( (S + B) * LSB - S );
                 E_l_1 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
             }

                 QuadraticSum_l_1 = sqrt(R_l_1);
                 if(R_l_1 > 0) { EE_l_1 = sqrt(E_l_1) / QuadraticSum_l_1; }
             
            h1_1->SetBinContent(j,QuadraticSum_l_1);
            h1_1->SetLineColor(kBlue-9);
            h1_1->SetLineStyle(2);
            
         }
   
        //cout << " " << endl;
        //cout << " ============== significance From right ============== " << endl;
        //cout << " " << endl;
         
       TH1F *h1_2 = new TH1F("h1_2","Quadratic Sum from right",70,0,3500); //right
         
       double QuadraticSum_r_1 = 0;
       double R_r_1 = 0;
       double E_r_1 = 0;
       double EE_r_1 = 0;
        
         for (int j=70; j>=1; j--) {
           
             double S = h_hist[10]->GetBinContent(j);
             double dS = h_hist[10]->GetBinError(j);
             double B = 0;   for(int i = 0; i<10; i++) { B += h_hist[i]->GetBinContent(j); }
             double dB = 0;   for(int i = 0; i<10; i++) { dB += h_hist[i]->GetBinError(j); }
             
              if( B > 0 && S > 0) {
                  double LSB = log(1+S/B);
                  R_r_1 +=  2* ( (S + B) * LSB - S );
                  E_r_1 += LSB * LSB * dS * dS + (LSB - S/B) * (LSB - S/B) * dB * dB;
              }

                  QuadraticSum_r_1 = sqrt(R_r_1);
                  if(R_r_1 > 0) { EE_r_1 = sqrt(E_r_1) / QuadraticSum_r_1; }
              
             h1_2->SetBinContent(j,QuadraticSum_r_1);
             h1_2->SetLineColor(kGreen-9);
             h1_2->SetLineStyle(2);
             
          }
         
         
         float rightmax1 = 1.1*h1_1->GetMaximum();
         float scale1 = 11000 / rightmax1;
         h1_1->Scale(scale1);
         h1_1->Draw("SAMEHIST");
         
         h1_2->Scale(scale1);
         h1_2->Draw("SAMEHIST");
         
       
         TGaxis*axis1 = new TGaxis(3500,0,3500,11000,0,rightmax1,510,"+L");
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
         
         for(int i= 10; i>=0 ; i--) { leg1->AddEntry(h_hist[i], h_titles[i].c_str()); }
         leg1->AddEntry(h1_1, "Quadratic Sum of #frac{S}{#sqrt{B}} from left");
         leg1->AddEntry(h1_2, "Quadratic Sum of #frac{S}{#sqrt{B}} from right");
         leg1->Draw();
         
       //c1 -> SaveAs("Mhh_SM.pdf");
    
    cout << " Mhh : " <<" S = " << QuadraticSum_r_1 << " E = " << EE_r_1 << endl;
    
  int entries;
  int entries_VBF001;
  float yields;
  float yields_VBF001;
  int sum_entries;
  int sum_entries_noVBF001;
  float sum_yields_noVBF001;
  float sum_yields;
    
  ofstream myfile;
  myfile.open ("Yields_001_TotalBkg.txt");
  myfile <<"---------------------------------------------------"<<endl;
  myfile <<"                                                                                    "<<endl;
  myfile <<"        Sample          Entries         Yields             "<<endl;
  myfile <<"                                                                                    "<<endl;
  
  for(int i= 10; i>=0 ; i--)
  {
   entries_VBF001 = h_hist[10]->GetEntries();
      yields_VBF001 = h_hist[10]->Integral();
  }
    myfile<<"\t" <<h_title[10] <<"\t \t"<<entries_VBF001<<"\t \t"<<yields_VBF001<<endl;
    myfile <<"                                                                                   "<<endl;
    
    for(int i= 9; i>=0 ; i--)
    {
        entries = h_hist[i]->GetEntries();
        yields =  h_hist[i]->Integral();
   myfile<<"\t" <<h_title[i] <<"\t \t"<<entries<<"\t \t"<<yields<<endl;
   myfile <<"                                                                                   "<<endl;
   
   sum_yields_noVBF001 += yields;
   sum_entries_noVBF001 += entries;
  }
    
  myfile<<"\t" << "Bkg :" <<"\t \t"<< sum_entries_noVBF001 <<"\t \t"<<sum_yields_noVBF001<<endl;
  myfile <<"                                                                                   "<<endl;
  myfile <<"---------------------------------------------------"<<endl;
  myfile.close();

    
  }

