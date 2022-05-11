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

void SLT_plot_SM_OnlyMhh(){

    
  const int n_smp = 12;
  string smp_tree[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM", "data" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "FullRun2_AddRNN/";
  //string pwd = "SLT_job_SR_data18/Ntuple/"; // path to input files
  string ana_tag = "FinalNtuple.TauLH.";
  string smp_names[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Zll", "W", "Ztautau", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1.", "data_13TeV" };
  //string smp_names[n_smp] = { "SM_H", "diboson", "DY", "ttbar", "W", "Zll", "W", "Ztautau1", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
    
  for (int i=0; i<n_smp; i++)
    {
      smp = pwd + ana_tag + smp_names[i] +".0.root";
      cout<<smp<<endl;
      chain_smp[i] = new TChain(smp_tree[i].c_str());
      chain_smp[i]->Add(smp.c_str());
    }
  
  string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake_ttbar", "Fake_W", "Zee/#mu#mu", "W", "Z#tau#tau", "single top", "ttbar", "VBFSM", "data" };  // only for legend
    
  string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake_ttbar", "Fake_W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM", "data" };
    
  TH1::SetDefaultSumw2();
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];


        //   ===========================================================   Mhh   ===========================================================
          
    
          TCanvas *c36 = new TCanvas ("c36", "Mhh",980,580);
            
          TPad *pad361 = new TPad("pad361","",0,0,0.75,1);
          TPad *pad362 = new TPad("pad362","",0.73,0,1,1);
          pad361->Draw();
          pad362->Draw();
            
          pad361->cd();
          pad361->SetTickx();
          //gStyle->SetOptStat(kFALSE);
          //gPad->SetLogy();
          
          for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",30,0,3000);
            //h_hist[i]->GetXaxis()->SetTitle("m_{hh} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 100 GeV");
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            //h_hist[i]->GetYaxis()->SetRangeUser(1, 6000); //B:6000, P:2800
          }
        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="Mhh*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1)&&(mBB>90000)&&(mMMC<160000))",  "SAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1)&&(mBB>90000)&&(mMMC<160000))",  "SAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0)&&(mBB>90000)&&(mMMC<160000))",  "SAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0)&&(mBB>90000)&&(mMMC<160000))", "SAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(mBB>90000)&&(mMMC<160000))", "SAMEHIST");} //VBFSM
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(mBB>90000)&&(mMMC<160000))",  "SAMEHIST");
            
          }
          
          THStack *hs36 = new THStack("hs36", "");
          for(int i= 0; i<10 ; i++){ hs36->Add(h_hist[i], "hist36"); }
          hs36->Draw("SAMEHIST");


    TFile *f1 = new TFile("Mhh_new_BulbasaurFullRun2_80.root","recreate");
    f1 -> cd();

    for (int i=0; i<n_smp; i++){
        hist_draw[i]="Mhh*0.001>>"+h_title[i];
        h_hist[i]->Write();
    }

    f1->Close();
    */
    

    auto f1 = new TFile("Mhh_new_BulbasaurFullRun2_80.root","UPDATE");
   
    TH1F *h1; f1->GetObject("Fake_ttbar",h1);
    if(h1){ h1->SetName("Fake"); }

    TH1F *h2; f1->GetObject("Fake_W",h2);
    if(h2){ h1->SetName("WFake"); }

    TH1F *h3; f1->GetObject("SMH",h3);
    if(h3){ h3->SetName("WHbb"); }
    
    TH1F *h4; f1->GetObject("SMH",h4);
    if(h4){ h4->SetName("WHtautau"); }
    
    TH1F *h5; f1->GetObject("SMH",h5);
    if(h5){ h5->SetName("ZHbb"); }
    
    TH1F *h6; f1->GetObject("SMH",h6);
    if(h6){ h6->SetName("ZHtautau"); }
    
    TH1F *h7; f1->GetObject("SMH",h7);
    if(h7){ h7->SetName("ttH"); }

    TH1F *h8; f1->GetObject("diboson",h8);
    if(h8){ h8->SetName("WW"); }
    
    TH1F *h9; f1->GetObject("diboson",h9);
    if(h9){ h9->SetName("WZ"); }
    
    TH1F *h10; f1->GetObject("diboson",h10);
    if(h10){ h10->SetName("ZZ"); }

    TH1F *h11; f1->GetObject("DY",h11);
    if(h11){ h11->SetName("DYtt"); }

    TH1F *h12; f1->GetObject("Z",h12);
    if(h12){ h12->SetName("Zbb"); }
    
    TH1F *h13; f1->GetObject("Z",h13);
    if(h13){ h13->SetName("Zbc"); }
    
    TH1F *h14; f1->GetObject("Z",h14);
    if(h14){ h14->SetName("Zbl"); }
    
    TH1F *h15; f1->GetObject("Z",h15);
    if(h15){ h15->SetName("Zcc"); }
    
    TH1F *h16; f1->GetObject("Z",h16);
    if(h16){ h16->SetName("Zcl"); }
    
    TH1F *h17; f1->GetObject("Z",h17);
    if(h17){ h17->SetName("Zl"); }

    TH1F *h18; f1->GetObject("W",h18);
    if(h18){ h18->SetName("Wtt"); }
    
    TH1F *h19; f1->GetObject("W",h19);
    if(h19){ h19->SetName("WttFake"); }

    TH1F *h20; f1->GetObject("Ztt",h20);
    if(h20){ h20->SetName("Zttbb"); }
    
    TH1F *h21; f1->GetObject("Ztt",h21);
    if(h21){ h21->SetName("Zttbc"); }
    
    TH1F *h22; f1->GetObject("Ztt",h22);
    if(h22){ h22->SetName("Zttbl"); }
    
    TH1F *h23; f1->GetObject("Ztt",h23);
    if(h23){ h23->SetName("Zttcc"); }
    
    TH1F *h24; f1->GetObject("Ztt",h24);
    if(h24){ h24->SetName("Zttcl"); }
    
    TH1F *h25; f1->GetObject("Ztt",h25);
    if(h25){ h25->SetName("Zttl"); }

    TH1F *h26; f1->GetObject("singletop",h26);
    if(h26){ h26->SetName("stopWt"); }
    
    TH1F *h27; f1->GetObject("singletop",h27);
    if(h27){ h27->SetName("stops"); }
    
    TH1F *h28; f1->GetObject("singletop",h28);
    if(h28){ h28->SetName("stopt"); }

    TH1F *h29; f1->GetObject("VBFSM",h29);
    if(h29){ h29->SetName("VBFHtautau"); }
   
    f1->Write();

    
}
