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

void SLT_plot_SM_OnlyMt(){

  const int n_smp = 11;
  string smp_tree[n_smp] = { "SMH", "diboson", "DY", "ttbar", "W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM" };
  string smp;
  TChain  *chain_smp[n_smp];
  
  string pwd = "FullRun2_Bulbasaur/";
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
  
  string h_titles[n_smp] = { "SM H", "diboson", "DY", "Fake_ttbar", "Fake_W", "Zee/#mu#mu", "W", "Z#tau#tau", "single top", "ttbar", "VBFSM", };  // only for legend
    
  string h_title[n_smp] = { "SMH", "diboson", "DY", "Fake_ttbar", "Fake_W", "Z", "W", "Ztt", "singletop", "ttbar", "VBFSM", };
    
  TH1::SetDefaultSumw2();
  TH1F * h_hist[n_smp];
  const char *h_nm;
  string hist_draw[n_smp];
    

        //   ===========================================================   Mt   ===========================================================
          
          TCanvas *c44 = new TCanvas ("c44", "Mt",980,580);
            
          TPad *pad441 = new TPad("pad441","",0,0,0.75,1);
          TPad *pad442 = new TPad("pad442","",0.73,0,1,1);
          pad441->Draw();
          pad442->Draw();
            
          pad441->cd();
          pad441->SetTickx();
          //gStyle->SetOptStat(kFALSE);
          
          for (int i=0; i<n_smp; i++){
            h_nm = h_title[i].c_str();
            h_hist[i] = new TH1F(h_nm, "",40,0,2000);
            h_hist[i]->GetXaxis()->SetTitle("m_{t} [GeV]");
            h_hist[i]->GetYaxis()->SetTitle("Events/ 50 GeV");//
            //h_hist[i]->GetXaxis()->SetRangeUser(0, 500);
            //h_hist[i]->GetYaxis()->SetRangeUser(1, 4200); //B:4200, P:1800
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

        
          for (int i=0; i<n_smp; i++){
              hist_draw[i]="Mt*0.001>>"+h_title[i];
          }
          
          for(int i = 0; i<n_smp; i++){
            
            if (i == 3 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1)&&(mMMC<160000)&&(mBB>70000)&&(dRHH>1.2)&&(abs(TauEta-LepEta)<1.8)&&(MtW<110000))",  "ESAMEHIST");} //Fake
            else if (i == 4 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==1)&&(mMMC<160000)&&(mBB>70000)&&(dRHH>1.2)&&(abs(TauEta-LepEta)<1.8)&&(MtW<110000))",  "ESAMEHIST");} //Fake_W
            else if (i == 6 ){chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0)&&(mMMC<160000)&&(mBB>70000)&&(dRHH>1.2)&&(abs(TauEta-LepEta)<1.8)&&(MtW<110000))",  "ESAMEHIST");} //Wlv
            else if(i == 9){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(isFakeTau==0)&&(mMMC<160000)&&(mBB>70000)&&(dRHH>1.2)&&(abs(TauEta-LepEta)<1.8)&&(MtW<110000))", "ESAMEHIST");} //ttbar
            else if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(mMMC<160000)&&(mBB>70000)&&(dRHH>1.2)&&(abs(TauEta-LepEta)<1.8)&&(MtW<110000))", "ESAMEHIST");} //VBFSM
            else chain_smp[i]->Draw(hist_draw[i].c_str(),"(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(mMMC<160000)&&(mBB>70000)&&(dRHH>1.2)&&(abs(TauEta-LepEta)<1.8)&&(MtW<110000))",  "ESAMEHIST");
            
          }
          
          THStack *hs44 = new THStack("hs44", "");
          for(int i= 0; i<10 ; i++){ hs44->Add(h_hist[i], "hist44"); }
          hs44->Draw("ESAMEHIST");
        
          for(int i = 0; i<n_smp; i++){
              if(i == 10){chain_smp[i]->Draw(hist_draw[i].c_str(), "(weight)*((BTag==2)&&((LepQ)*(TauQ)<0)&&(mMMC<160000)&&(mBB>70000)&&(dRHH>1.2)&&(abs(TauEta-LepEta)<1.8)&&(MtW<110000))", "ESAMEHIST");} //VBFSM
          }

         //cout << " ============== significance From left ============== " << endl;
         //cout << " " << endl;
          /*
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
          float scale44 = 1800 / rightmax44;
          h44_1->Scale(scale44);
          h44_1->Draw("SAMEHIST");
          
          h44_2->Scale(scale44);
          h44_2->Draw("SAMEHIST");
          
        
          TGaxis*axis44 = new TGaxis(2000,0,2000,1800,0,rightmax44,510,"+L");
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
          
          //c44 -> SaveAs("Mt_SM.pdf");
        
    
        cout << " Mt = " << QuadraticSum_l_44 << endl;
        */
    
    TFile *f1 = new TFile("Mt_new_BulbasaurFullRun2_NoRange.root","recreate");
    //TFile *f1 = new TFile("Mt_old_PikachuOnly2018.root","recreate");
    f1 -> cd();
    
    //c44->Write("Mt");
    
    for (int i=0; i<n_smp; i++){
        hist_draw[i]="Mt*0.001>>"+h_title[i];
        h_hist[i]->Write();
    }
    
    //h44_1->Write("Quadratic Sum from left of Mt");
    //h44_2->Write("Quadratic Sum from right of Mt");
    
    f1->Close();
    
    
      }
