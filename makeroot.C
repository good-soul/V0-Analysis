#if !defined( __CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <fstream.h>
#include <sstream>
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TStopwatch.h"

#include "AliESD.h"
#endif
// using namespace std;

extern TStyle *gStyle;

void mytry(){
	gStyle->SetOptStat(111110);
	gStyle->SetOptFit(1);
	/*TString filename = "cernstaff.root";
	TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
	cout <<dir<<endl;
	cout<<".............."<<endl;
	dir.ReplaceAll("/./","/");
	dir.ReplaceAll("mytry.C","");
	/*ifstream in1;
	ifstream in2;
	in1.open(Form("%scentroid_data(CPV).txt",dir.Data()));
	in2.open(Form("%scentroid_data(PRE).txt",dir.Data()));*/

	Double_t sigma_x, sigma_y,ADC_CPV, ADC_PRE;
	Int_t  ncellCPV, ncellPRE;
	TFile *f = new TFile("TMVA/basic.root","RECREATE");
	cout<<"Im here 1"<<endl;
	TTree* ts = new TTree("ts","a signal Tree with simple variables");
	TTree* tb = new TTree("tb","a background Tree with simple variables");


	ts->Branch("sigma_x",&sigma_x,"sigma_x/D");
	ts->Branch("sigma_y",&sigma_y,"sigma_y/D");
	ts->Branch("ADC_CPV",&ADC_CPV,"ADC_CPV/D");
	ts->Branch("ncellCPV",&ncellCPV,"ncellCPV/I");
	ts->Branch("ADC_PRE",&ADC_PRE,"ADC_PRE/D");
	ts->Branch("ncellPRE",&ncellPRE,"ncellPRE/I");

	tb->Branch("sigma_x",&sigma_x,"sigma_x/D");
	tb->Branch("sigma_y",&sigma_y,"sigma_y/D");
	tb->Branch("ADC_CPV",&ADC_CPV,"ADC_CPV/D");
	tb->Branch("ncellCPV",&ncellCPV,"ncellCPV/I");
	tb->Branch("ADC_PRE",&ADC_PRE,"ADC_PRE/D");
	tb->Branch("ncellPRE",&ncellPRE,"ncellPRE/I");

// fill the tree
	Int_t count1 = 0;
	Int_t count2 = 0;
	ifstream fin1("DBSCAN-output/gamma_file");
	while(fin1>>sigma_x>>sigma_y>>ncellCPV>>ncellPRE>>ADC_CPV>>ADC_PRE){
		count1 = count1 +1;
	}
	cout<<count1<<endl;
	fin1.close();
	ifstream fin1("DBSCAN-output/gamma_file");
	for(Int_t i= 0; i< count1; i++){
		fin1>>sigma_x>>sigma_y>>ncellCPV>>ncellPRE>>ADC_CPV>>ADC_PRE;
		//cout<<x_CPV<<"\t"<<y_CPV<<"\t"<<sigma_xCPV<<"\t"<<sigma_yCPV<<"\t"<<energyCPV<<"\t"<<ncellCPV<<endl;
		ts->Fill();
	}
	fin1.close();
	ifstream fin2("DBSCAN-output/PiMinus_file");
	while(fin2>>sigma_x>>sigma_y>>ncellCPV>>ncellPRE>>ADC_CPV>>ADC_PRE){
		count2 = count2+1;
	}
	cout<<count2<<endl;
	fin2.close();
	ifstream fin2("DBSCAN-output/PiMinus_file");
	for(Int_t i= 0; i< count2; i++){
		fin2>>sigma_x>>sigma_y>>ncellCPV>>ncellPRE>>ADC_CPV>>ADC_PRE;
		tb->Fill();
	}
	fin2.close();
	ts->Write();
	tb->Write();
/*delete ts;
delete tb;*/
   //in.close();
	f->cd();
	//f->Write();
	f->Close();
}

 
