#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TPostScript.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TF1.h"
#include "TMath.h"
#include "TAxis.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLatex.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TTree.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TChain.h"
#include "Rtypes.h"
using namespace std;
void title()
{
  TFile *f1 =  TFile::Open("Mhh_new_BulbasaurFullRun2.root");
  TIter next(gDirectory->GetListOfKeys());
 int i = 0; 
 TH1F *h1[40];
 std::vector<string> v_histname;
 TKey *key;
  while ((key = (TKey*)next())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    cout<<i<<"  "<<key->GetName()<<endl;
    i++;
    v_histname.push_back(key->GetName());
    //h1[i]= (TH1F*)key->Clone();
    
  }
 int v_histname_size;
 v_histname_size = v_histname.size();
 cout<<"Size of Vector = "<<v_histname_size<<endl;
 string keywords[40];
 string h_tit[40];
 
 for(int j = 0; j<v_histname_size; j++)
    {
	keywords[j] = v_histname.at(j);
	h_tit[j] =keywords[j]+"_2tag2pjet_0ptv_SM_NN";

	cout<<" names =  "<<h_tit[j]<<endl;	
	h1[j] = (TH1F*)f1->Get(keywords[j].c_str()); 
	if(j!=17)h1[j]->SetTitle(h_tit[j].c_str());
   }
h1[16]->Draw();

}
