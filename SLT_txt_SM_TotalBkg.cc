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
void SLT_txt_SM_TotalBkg(){

    /*
  const int n_smp = 10;
  string smp_tree[n_smp] = { "SMH", "diboson", "DY", "fake", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM" };
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
  
  string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake", "Z", "Wl#nu", "Z#tau#tau", "single top", "ttbar", "VBFSM x 248634.031", };  // only for legend
    
  string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM", };
    
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];*/
    
    const int n_smp = 11;
    string smp_tree[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM" };
    string smp;
    TChain  *chain_smp[n_smp];
    
    string pwd = "FullRun2_SLT/";
    //string pwd = "SLT_job_SR_data18/Ntuple/"; // path to input files
    string ana_tag = "FinalNtuple.TauLH.";
    string smp_names[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Zll", "W", "Ztautau", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
    //string smp_names[n_smp] = { "SM_H", "diboson", "DY", "ttbar", "W", "Zll", "W", "Ztautau1", "singletop", "ttbar", "VBF.hh_bbtt_vbf_lh_l1cvv1cv1." };
      
    for (int i=0; i<n_smp; i++)
      {
        smp = pwd + ana_tag + smp_names[i] +".0.root";
        cout<<smp<<endl;
        chain_smp[i] = new TChain(smp_tree[i].c_str());
        chain_smp[i]->Add(smp.c_str());
      }
    
    string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake_ttbar", "Fake_W", "Zee/#mu#mu", "W", "Z#tau#tau", "single top", "ttbar", "VBFSM x 248633.791", };  // only for legend
      
    string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake_ttbar", "Fake_W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM", };
      
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
      
      if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1)&&(sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.3)&&(mVBFjj>350000)&&(Mvis<120000)&&(sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.3)&&(dEtaLepTau<1.8)&&(dEtaBB<2.2))",  "SAMEHIST");} //Fake
      else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1)&&(sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.3)&&(mVBFjj>350000)&&(Mvis<120000)&&(sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.3)&&(dEtaLepTau<1.8)&&(dEtaBB<2.2))",  "SAMEHIST");} //Fake_W
      else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0)&&(sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.3)&&(mVBFjj>350000)&&(Mvis<120000)&&(sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.3)&&(dEtaLepTau<1.8)&&(dEtaBB<2.2))",  "SAMEHIST");} //Wlv
      else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0)&&(sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.3)&&(mVBFjj>350000)&&(Mvis<120000)&&(sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.3)&&(dEtaLepTau<1.8)&&(dEtaBB<2.2))", "SAMEHIST");} //ttbar
      else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.3)&&(mVBFjj>350000)&&(Mvis<120000)&&(sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.3)&&(dEtaLepTau<1.8)&&(dEtaBB<2.2))", "SAMEHIST");} //VBFSM
      else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(sqrt( ((mMMC*0.001-118)/(mMMC*0.001)) * ((mMMC*0.001-118)/(mMMC*0.001)) + ((mBB*0.001-120)/(mBB*0.001)) * ((mBB*0.001-120)/(mBB*0.001)) )<0.3)&&(mVBFjj>350000)&&(Mvis<120000)&&(sqrt( ((Mw*0.001-80.4)/(Mw*0.001)) * ((Mw*0.001-80.4)/(Mw*0.001)) + ((Mt*0.001-172.5)/(Mt*0.001)) * ((Mt*0.001-172.5)/(Mt*0.001)) )<2.3)&&(dEtaLepTau<1.8)&&(dEtaBB<2.2))",  "SAMEHIST");
      
    }
    
  THStack *hs1 = new THStack("hs1", "");
  for(int i= 0; i<10 ; i++){ hs1->Add(h_hist[i], "hist1"); }
  hs1->Draw("SAMEHIST");
    
  int entries;
  int entries_VBFSM;
  float yields;
  float yields_VBFSM;
  int sum_entries;
  int sum_entries_noVBFSM;
  float sum_yields_noVBFSM;
  float sum_yields;
    
  ofstream myfile;
  myfile.open ("Yields_SM_TotalBkg.txt");
  myfile <<"---------------------------------------------------"<<endl;
  myfile <<"                                                                                    "<<endl;
  myfile <<"        Sample          Entries         Yields             "<<endl;
  myfile <<"                                                                                    "<<endl;
  
  for(int i= 10; i>=0 ; i--)
  {
   entries_VBFSM = h_hist[10]->GetEntries();
      yields_VBFSM = h_hist[10]->Integral();
  }
    myfile<<"\t" <<h_title[10] <<"\t \t"<<entries_VBFSM<<"\t \t"<<yields_VBFSM<<endl;
    myfile <<"                                                                                   "<<endl;
    
    for(int i= 9; i>=0 ; i--)
    {
        entries = h_hist[i]->GetEntries();
        yields =  h_hist[i]->Integral();
   myfile<<"\t" <<h_title[i] <<"\t \t"<<entries<<"\t \t"<<yields<<endl;
   myfile <<"                                                                                   "<<endl;
   
   sum_yields_noVBFSM += yields;
   sum_entries_noVBFSM += entries;
  }
    
  myfile<<"\t" << "Bkg :" <<"\t \t"<< sum_entries_noVBFSM <<"\t \t"<<sum_yields_noVBFSM<<endl;
  myfile <<"                                                                                   "<<endl;
  myfile <<"---------------------------------------------------"<<endl;
  myfile.close();

    
  }

