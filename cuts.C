//***************************************************************************************
//
//		Read the analysis root file and apply standard cuts and outputs a root file
//
//***************************************************************************************

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <iostream>
#include <TCanvas.h>
#include <TBrowser.h>
#include <vector>
#include <stdio.h>      // For sprintf
#include <TStyle.h>
#include <TGaxis.h>
#include <TRandom.h>
#include <TMath.h>
#include <TROOT.h>
#include <TText.h>
#include <TPaveText.h>
	
void cuts(){
	
	TFile *f = new TFile("AnalysisResults.root");

	//TFile *f = new TFile(Form("public_train_%d.root",dataset));
	if (!f || !f->IsOpen()) {cerr<<"Either the file is already open or the program can't find the given file!!\n"; return 1;}

	TTree *t1 = (TTree*)f->Get("PWGLFExtractV0_PP/fTree");
	if (!t1) {cerr<<"Seems like a wrong tree address!\n"; return 1;}
	

	// Defining Branch Variables

	Float_t fTreeVariableChi2V0, fTreeVariableDcaV0Daughters, fTreeVariableDcaV0ToPrimVertex, fTreeVariableDcaPosToPrimVertex,
	 		fTreeVariableDcaNegToPrimVertex, fTreeVariableV0Radius, fTreeVariablePt, fTreeVariableRapK0Short,fTreeVariableRapLambda, 
			fTreeVariableInvMassK0s, fTreeVariableInvMassLambda, fTreeVariableInvMassAntiLambda, fTreeVariableV0CosineOfPointingAngle, 
			fTreeVariableAlphaV0, fTreeVariablePtArmV0, fTreeVariableLeastRatioCrossedRowsOverFindable, fTreeVariableDistOverTotMom, 
			fTreeVariableNSigmasPosProton, fTreeVariableNSigmasPosPion, fTreeVariableNSigmasNegProton, fTreeVariableNSigmasNegPion, 
			fTreeVariableNegEta, fTreeVariablePosEta, fTreeVariablePVx, fTreeVariablePVy, fTreeVariablePVz, fTreeVariableV0x, 
			fTreeVariableV0y, fTreeVariableV0z, fTreeVariableV0Px, fTreeVariableV0Py, fTreeVariableV0Pz;

	Int_t 	fTreeVariableLeastNbrCrossedRows, fTreeVariableMultiplicity, fTreeVariableMultiplicityV0A, fTreeVariableMultiplicityZNA, 
			fTreeVariableMultiplicityTRK, fTreeVariableMultiplicitySPD, fTreeVariableRunNumber;

	ULong64_t fTreeVariableEventNumber, fTreeVariableNegTrackStatus, fTreeVariablePosTrackStatus;


	//Setting Branch Addresses

	t1->SetBranchAddress("fTreeVariableChi2V0",&fTreeVariableChi2V0);
    t1->SetBranchAddress("fTreeVariableDcaV0Daughters",&fTreeVariableDcaV0Daughters);
    t1->SetBranchAddress("fTreeVariableDcaV0ToPrimVertex",&fTreeVariableDcaV0ToPrimVertex);
	t1->SetBranchAddress("fTreeVariableDcaPosToPrimVertex",&fTreeVariableDcaPosToPrimVertex);
	t1->SetBranchAddress("fTreeVariableDcaNegToPrimVertex",&fTreeVariableDcaNegToPrimVertex);
	t1->SetBranchAddress("fTreeVariableV0Radius",&fTreeVariableV0Radius);
	t1->SetBranchAddress("fTreeVariablePt",&fTreeVariablePt);
	t1->SetBranchAddress("fTreeVariableRapK0Short",&fTreeVariableRapK0Short);
  	t1->SetBranchAddress("fTreeVariableRapLambda",&fTreeVariableRapLambda);
   	t1->SetBranchAddress("fTreeVariableInvMassK0s",&fTreeVariableInvMassK0s);
	t1->SetBranchAddress("fTreeVariableInvMassLambda",&fTreeVariableInvMassLambda);
	t1->SetBranchAddress("fTreeVariableInvMassAntiLambda",&fTreeVariableInvMassAntiLambda);
	t1->SetBranchAddress("fTreeVariableV0CosineOfPointingAngle",&fTreeVariableV0CosineOfPointingAngle);
	t1->SetBranchAddress("fTreeVariableAlphaV0",&fTreeVariableAlphaV0);
	t1->SetBranchAddress("fTreeVariablePtArmV0",&fTreeVariablePtArmV0);
    t1->SetBranchAddress("fTreeVariableLeastNbrCrossedRows",&fTreeVariableLeastNbrCrossedRows);
    t1->SetBranchAddress("fTreeVariableLeastRatioCrossedRowsOverFindable",&fTreeVariableLeastRatioCrossedRowsOverFindable);
//-----------MULTIPLICITY-INFO--------------------
    t1->SetBranchAddress("fTreeVariableMultiplicity",&fTreeVariableMultiplicity);
    t1->SetBranchAddress("fTreeVariableMultiplicityV0A",&fTreeVariableMultiplicityV0A);
    t1->SetBranchAddress("fTreeVariableMultiplicityZNA",&fTreeVariableMultiplicityZNA);
    t1->SetBranchAddress("fTreeVariableMultiplicityTRK",&fTreeVariableMultiplicityTRK);
    t1->SetBranchAddress("fTreeVariableMultiplicitySPD",&fTreeVariableMultiplicitySPD);
//------------------------------------------------
    t1->SetBranchAddress("fTreeVariableDistOverTotMom",&fTreeVariableDistOverTotMom);
    t1->SetBranchAddress("fTreeVariableNSigmasPosProton",&fTreeVariableNSigmasPosProton);
    t1->SetBranchAddress("fTreeVariableNSigmasPosPion",&fTreeVariableNSigmasPosPion);
    t1->SetBranchAddress("fTreeVariableNSigmasNegProton",&fTreeVariableNSigmasNegProton);
    t1->SetBranchAddress("fTreeVariableNSigmasNegPion",&fTreeVariableNSigmasNegPion);
    t1->SetBranchAddress("fTreeVariableNegEta",&fTreeVariableNegEta);
    t1->SetBranchAddress("fTreeVariablePosEta",&fTreeVariablePosEta);
    t1->SetBranchAddress("fTreeVariableRunNumber",&fTreeVariableRunNumber);
    t1->SetBranchAddress("fTreeVariableEventNumber",&fTreeVariableEventNumber);

    t1->SetBranchAddress("fTreeVariablePVx",&fTreeVariablePVx);
    t1->SetBranchAddress("fTreeVariablePVy",&fTreeVariablePVy);
    t1->SetBranchAddress("fTreeVariablePVz",&fTreeVariablePVz);

    t1->SetBranchAddress("fTreeVariableV0x",&fTreeVariableV0x);
    t1->SetBranchAddress("fTreeVariableV0y",&fTreeVariableV0y);
    t1->SetBranchAddress("fTreeVariableV0z",&fTreeVariableV0z);

    t1->SetBranchAddress("fTreeVariableV0Px",&fTreeVariableV0Px);
    t1->SetBranchAddress("fTreeVariableV0Py",&fTreeVariableV0Py);
    t1->SetBranchAddress("fTreeVariableV0Pz",&fTreeVariableV0Pz);

    t1->SetBranchAddress("fTreeVariableNegTrackStatus",&fTreeVariableNegTrackStatus);
    t1->SetBranchAddress("fTreeVariablePosTrackStatus",&fTreeVariablePosTrackStatus);
	


	t1->SetBranchStatus("*",1);
	// t1->SetBranchStatus("fTreeVariableChi2V0",0);
	



// ------------------------------------------ Write tree with cuts---------------------------------------------------

	TFile *f2 = new TFile("AnalysisResultsWithCuts.root","RECREATE");
	TTree* t2 = new TTree("fCutsTree","a signal Tree with simple variables");


	Float_t fCutsTreeVariableChi2V0, fCutsTreeVariableDcaV0Daughters, fCutsTreeVariableDcaV0ToPrimVertex, fCutsTreeVariableDcaPosToPrimVertex,
	 		fCutsTreeVariableDcaNegToPrimVertex, fCutsTreeVariableV0Radius, fCutsTreeVariablePt, fCutsTreeVariableRapK0Short,fCutsTreeVariableRapLambda, 
			fCutsTreeVariableInvMassK0s, fCutsTreeVariableInvMassLambda, fCutsTreeVariableInvMassAntiLambda, fCutsTreeVariableV0CosineOfPointingAngle, 
			fCutsTreeVariableAlphaV0, fCutsTreeVariablePtArmV0, fCutsTreeVariableLeastRatioCrossedRowsOverFindable, fCutsTreeVariableDistOverTotMom, 
			fCutsTreeVariableNSigmasPosProton, fCutsTreeVariableNSigmasPosPion, fCutsTreeVariableNSigmasNegProton, fCutsTreeVariableNSigmasNegPion, 
			fCutsTreeVariableNegEta, fCutsTreeVariablePosEta, fCutsTreeVariablePVx, fCutsTreeVariablePVy, fCutsTreeVariablePVz, fCutsTreeVariableV0x, 
			fCutsTreeVariableV0y, fCutsTreeVariableV0z, fCutsTreeVariableV0Px, fCutsTreeVariableV0Py, fCutsTreeVariableV0Pz;

	Int_t 	fCutsTreeVariableLeastNbrCrossedRows, fCutsTreeVariableMultiplicity, fCutsTreeVariableMultiplicityV0A, fCutsTreeVariableMultiplicityZNA,
			fCutsTreeVariableMultiplicityTRK, fCutsTreeVariableMultiplicitySPD, fCutsTreeVariableRunNumber;

	Long64_t fCutsTreeVariableEventNumber, fCutsTreeVariableNegTrackStatus, fCutsTreeVariablePosTrackStatus;


	//Setting Branch Addresses

	/* 1*/  t2->Branch("fCutsTreeVariableChi2V0",&fCutsTreeVariableChi2V0,"fCutsTreeVariableChi2V0/F");
    /* 2*/  t2->Branch("fCutsTreeVariableDcaV0Daughters",&fCutsTreeVariableDcaV0Daughters,"fCutsTreeVariableDcaV0Daughters/F");
    /* 2*/  t2->Branch("fCutsTreeVariableDcaV0ToPrimVertex",&fCutsTreeVariableDcaV0ToPrimVertex,"fCutsTreeVariableDcaV0ToPrimVertex/F");
    /* 3*/	t2->Branch("fCutsTreeVariableDcaPosToPrimVertex",&fCutsTreeVariableDcaPosToPrimVertex,"fCutsTreeVariableDcaPosToPrimVertex/F");
    /* 4*/	t2->Branch("fCutsTreeVariableDcaNegToPrimVertex",&fCutsTreeVariableDcaNegToPrimVertex,"fCutsTreeVariableDcaNegToPrimVertex/F");
    /* 5*/	t2->Branch("fCutsTreeVariableV0Radius",&fCutsTreeVariableV0Radius,"fCutsTreeVariableV0Radius/F");
    /* 6*/	t2->Branch("fCutsTreeVariablePt",&fCutsTreeVariablePt,"fCutsTreeVariablePt/F");
    /* 7*/	t2->Branch("fCutsTreeVariableRapK0Short",&fCutsTreeVariableRapK0Short,"fCutsTreeVariableRapK0Short/F");
    /* 8*/	t2->Branch("fCutsTreeVariableRapLambda",&fCutsTreeVariableRapLambda,"fCutsTreeVariableRapLambda/F");
    /* 9*/	t2->Branch("fCutsTreeVariableInvMassK0s",&fCutsTreeVariableInvMassK0s,"fCutsTreeVariableInvMassK0s/F");
    /*10*/	t2->Branch("fCutsTreeVariableInvMassLambda",&fCutsTreeVariableInvMassLambda,"fCutsTreeVariableInvMassLambda/F");
    /*11*/	t2->Branch("fCutsTreeVariableInvMassAntiLambda",&fCutsTreeVariableInvMassAntiLambda,"fCutsTreeVariableInvMassAntiLambda/F");
    /*12*/	t2->Branch("fCutsTreeVariableV0CosineOfPointingAngle",&fCutsTreeVariableV0CosineOfPointingAngle,"fCutsTreeVariableV0CosineOfPointingAngle/F");
    /*13*/	t2->Branch("fCutsTreeVariableAlphaV0",&fCutsTreeVariableAlphaV0,"fCutsTreeVariableAlphaV0/F");
    /*14*/	t2->Branch("fCutsTreeVariablePtArmV0",&fCutsTreeVariablePtArmV0,"fCutsTreeVariablePtArmV0/F");
    /*15*/	t2->Branch("fCutsTreeVariableLeastNbrCrossedRows",&fCutsTreeVariableLeastNbrCrossedRows,"fCutsTreeVariableLeastNbrCrossedRows/I");
    /*16*/	t2->Branch("fCutsTreeVariableLeastRatioCrossedRowsOverFindable",&fCutsTreeVariableLeastRatioCrossedRowsOverFindable,"fCutsTreeVariableLeastRatioCrossedRowsOverFindable/F");
//-----------MULTIPLICITY-INFO--------------------
    /*17*/	t2->Branch("fCutsTreeVariableMultiplicity",&fCutsTreeVariableMultiplicity,"fCutsTreeVariableMultiplicity/I");
    /*17*/	t2->Branch("fCutsTreeVariableMultiplicityV0A",&fCutsTreeVariableMultiplicityV0A,"fCutsTreeVariableMultiplicityV0A/I");
    /*17*/	t2->Branch("fCutsTreeVariableMultiplicityZNA",&fCutsTreeVariableMultiplicityZNA,"fCutsTreeVariableMultiplicityZNA/I");
    /*17*/	t2->Branch("fCutsTreeVariableMultiplicityTRK",&fCutsTreeVariableMultiplicityTRK,"fCutsTreeVariableMultiplicityTRK/I");
    /*17*/	t2->Branch("fCutsTreeVariableMultiplicitySPD",&fCutsTreeVariableMultiplicitySPD,"fCutsTreeVariableMultiplicitySPD/I");
//------------------------------------------------
    /*18*/	t2->Branch("fCutsTreeVariableDistOverTotMom",&fCutsTreeVariableDistOverTotMom,"fCutsTreeVariableDistOverTotMom/F");
    /*19*/	t2->Branch("fCutsTreeVariableNSigmasPosProton",&fCutsTreeVariableNSigmasPosProton,"fCutsTreeVariableNSigmasPosProton/F");
    /*20*/	t2->Branch("fCutsTreeVariableNSigmasPosPion",&fCutsTreeVariableNSigmasPosPion,"fCutsTreeVariableNSigmasPosPion/F");
    /*21*/	t2->Branch("fCutsTreeVariableNSigmasNegProton",&fCutsTreeVariableNSigmasNegProton,"fCutsTreeVariableNSigmasNegProton/F");
    /*22*/	t2->Branch("fCutsTreeVariableNSigmasNegPion",&fCutsTreeVariableNSigmasNegPion,"fCutsTreeVariableNSigmasNegPion/F");
    /*23*/	t2->Branch("fCutsTreeVariableNegEta",&fCutsTreeVariableNegEta,"fCutsTreeVariableNegEta/F");
    /*24*/	t2->Branch("fCutsTreeVariablePosEta",&fCutsTreeVariablePosEta,"fCutsTreeVariablePosEta/F");
    /*25*/	t2->Branch("fCutsTreeVariableRunNumber",&fCutsTreeVariableRunNumber,"fCutsTreeVariableRunNumber/I");
    /*26*/	t2->Branch("fCutsTreeVariableEventNumber",&fCutsTreeVariableEventNumber,"fCutsTreeVariableEventNumber/l");

    t2->Branch("fCutsTreeVariablePVx",&fCutsTreeVariablePVx,"fCutsTreeVariablePVx/F");
    t2->Branch("fCutsTreeVariablePVy",&fCutsTreeVariablePVy,"fCutsTreeVariablePVy/F");
    t2->Branch("fCutsTreeVariablePVz",&fCutsTreeVariablePVz,"fCutsTreeVariablePVz/F");

    t2->Branch("fCutsTreeVariableV0x",&fCutsTreeVariableV0x,"fCutsTreeVariableV0x/F");
    t2->Branch("fCutsTreeVariableV0y",&fCutsTreeVariableV0y,"fCutsTreeVariableV0y/F");
    t2->Branch("fCutsTreeVariableV0z",&fCutsTreeVariableV0z,"fCutsTreeVariableV0z/F");

    t2->Branch("fCutsTreeVariableV0Px",&fCutsTreeVariableV0Px,"fCutsTreeVariableV0Px/F");
    t2->Branch("fCutsTreeVariableV0Py",&fCutsTreeVariableV0Py,"fCutsTreeVariableV0Py/F");
    t2->Branch("fCutsTreeVariableV0Pz",&fCutsTreeVariableV0Pz,"fCutsTreeVariableV0Pz/F");

    t2->Branch("fCutsTreeVariableNegTrackStatus",&fCutsTreeVariableNegTrackStatus,"fCutsTreeVariableNegTrackStatus/l");
    t2->Branch("fCutsTreeVariablePosTrackStatus",&fCutsTreeVariablePosTrackStatus,"fCutsTreeVariablePosTrackStatus/l");

// ---------------------------------- Define Histograms ------------------------------------------------------

    TH1F* h0 = new TH1F("NoCuts", "NoCuts", 400, 0.25, 0.65);
    TH1F* h1 = new TH1F("Cut1", "Cut1", 400, 0.25, 0.65);
    TH1F* h2 = new TH1F("Cut2", "Cut2", 400, 0.25, 0.65);
    TH1F* h3 = new TH1F("Cut3", "Cut3", 400, 0.25, 0.65);
    TH1F* h4 = new TH1F("Cut4", "Cut4", 400, 0.25, 0.65);
    TH1F* h5 = new TH1F("Cut5", "Cut5", 400, 0.25, 0.65);


// ---------------------------------- Apply Cuts -------------------------------------------------------------
    Int_t xyz = 0;
    Double_t nentries = (Int_t)t1->GetEntries();
	cout<<"Total number of entries : "<<nentries<<endl;
	
	for(double i = 0; i<nentries/1000; i++){
	

		int flag1, flag2, flag3, flag4, flag5, flag6 = 0;

		t1->GetEntry(i);

		// ----------------------------- New tree = Old tree ----------------------------------------------

		fCutsTreeVariableChi2V0	=	fTreeVariableChi2V0;
		fCutsTreeVariableDcaV0Daughters	=	fTreeVariableDcaV0Daughters;
		fCutsTreeVariableDcaV0ToPrimVertex	=	fTreeVariableDcaV0ToPrimVertex;
		fCutsTreeVariableDcaPosToPrimVertex	=	fTreeVariableDcaPosToPrimVertex;
		fCutsTreeVariableDcaNegToPrimVertex	=	fTreeVariableDcaNegToPrimVertex;
		fCutsTreeVariableV0Radius	=	fTreeVariableV0Radius;
		fCutsTreeVariablePt	=	fTreeVariablePt;
		fCutsTreeVariableRapK0Short	=	fTreeVariableRapK0Short;
		fCutsTreeVariableRapLambda	=	fTreeVariableRapLambda;
		fCutsTreeVariableInvMassK0s	=	fTreeVariableInvMassK0s;
		fCutsTreeVariableInvMassLambda	=	fTreeVariableInvMassLambda;
		fCutsTreeVariableInvMassAntiLambda	=	fTreeVariableInvMassAntiLambda;
		fCutsTreeVariableV0CosineOfPointingAngle	=	fTreeVariableV0CosineOfPointingAngle;
		fCutsTreeVariableAlphaV0	=	fTreeVariableAlphaV0;
		fCutsTreeVariablePtArmV0	=	fTreeVariablePtArmV0;
		fCutsTreeVariableLeastNbrCrossedRows	=	fTreeVariableLeastNbrCrossedRows;
		fCutsTreeVariableLeastRatioCrossedRowsOverFindable	=	fTreeVariableLeastRatioCrossedRowsOverFindable;
		fCutsTreeVariableMultiplicity	=	fTreeVariableMultiplicity;
		fCutsTreeVariableMultiplicityV0A	=	fTreeVariableMultiplicityV0A;
		fCutsTreeVariableMultiplicityZNA	=	fTreeVariableMultiplicityZNA;
		fCutsTreeVariableMultiplicityTRK	=	fTreeVariableMultiplicityTRK;
		fCutsTreeVariableMultiplicitySPD	=	fTreeVariableMultiplicitySPD;
		fCutsTreeVariableDistOverTotMom	=	fTreeVariableDistOverTotMom;
		fCutsTreeVariableNSigmasPosProton	=	fTreeVariableNSigmasPosProton;
		fCutsTreeVariableNSigmasPosPion	=	fTreeVariableNSigmasPosPion;
		fCutsTreeVariableNSigmasNegProton	=	fTreeVariableNSigmasNegProton;
		fCutsTreeVariableNSigmasNegPion	=	fTreeVariableNSigmasNegPion;
		fCutsTreeVariableNegEta	=	fTreeVariableNegEta;
		fCutsTreeVariablePosEta	=	fTreeVariablePosEta;
		fCutsTreeVariableRunNumber	=	fTreeVariableRunNumber;
		fCutsTreeVariableEventNumber	=	fTreeVariableEventNumber;
		fCutsTreeVariablePVx	=	fTreeVariablePVx;
		fCutsTreeVariablePVy	=	fTreeVariablePVy;
		fCutsTreeVariablePVz	=	fTreeVariablePVz;
		fCutsTreeVariableV0x	=	fTreeVariableV0x;
		fCutsTreeVariableV0y	=	fTreeVariableV0y;
		fCutsTreeVariableV0z	=	fTreeVariableV0z;
		fCutsTreeVariableV0Px	=	fTreeVariableV0Px;
		fCutsTreeVariableV0Py	=	fTreeVariableV0Py;
		fCutsTreeVariableV0Pz	=	fTreeVariableV0Pz;
		fCutsTreeVariableNegTrackStatus	=	fTreeVariableNegTrackStatus;
		fCutsTreeVariablePosTrackStatus	=	fTreeVariablePosTrackStatus;


		h0->Fill(fCutsTreeVariableInvMassK0s);

/*
		// V0 2D decay radius > 0.5 cm
	
		double Radius = 0;
		Radius = sqrt(pow(fTreeVariableV0x - fTreeVariablePVx,2) + pow(fTreeVariableV0y - fTreeVariablePVy,2));
		
		if(Radius < 0.5){
			//flag1++;
			continue;
		}
*/

		//Inv. Mass Rejection window of Lambda and Anti-Lambda --------------------------- CUT 1

		double LambdaMass = 1.115683; // Masses are in GeV/c2
		double AntiLambdaMass = 1.115683;
		
		if(fabs(fCutsTreeVariableInvMassLambda - LambdaMass) < 0.005 || fabs(fCutsTreeVariableInvMassAntiLambda - AntiLambdaMass) < 0.005){
			flag1 = 1;
			xyz++;
			//continue;
		}

		else{
			h1->Fill(fCutsTreeVariableInvMassK0s);
		}


		// DCA of V0 daughter track to prim. vertex > 0.06 cm --------------------------- CUT 2

		if(fTreeVariableDcaPosToPrimVertex < 0.06 && fTreeVariableDcaNegToPrimVertex < 0.06){
			flag2 = 1;
			//continue;
		}

		else{
			h2->Fill(fCutsTreeVariableInvMassK0s);
		}

		// DCA between V0 daughter tracks < 1 sigma --------------------------- CUT 3

		if(fTreeVariableDcaV0Daughters > 1){
			flag3 = 1;
			//continue;
		}

		else{
			h3->Fill(fCutsTreeVariableInvMassK0s);
		}

		// Cosine of V0 Pointing Angle (K0s) > 0.97 --------------------------- CUT 4

		if(fTreeVariableV0CosineOfPointingAngle < 0.97){
			flag4 = 1;
			//continue;
		}

		else{
			h4->Fill(fCutsTreeVariableInvMassK0s);
		}
/*
		// Proper Lifetime (mL/p) (Ks) < 20 cm
		// Time in lab frame / gamma factor
		// v/c = sqrt(p/p+mc)

		double momentum = sqrt(pow(fCutsTreeVariableV0Px,2) + pow(fCutsTreeVariableV0Py,2) + pow(fCutsTreeVariableV0Pz,2));
		double SpeedOfLight = 300000000.0;
		double mass = 497614000; // mass in eV/c2
		double mass2 = fCutsTreeVariableInvMassK0s;

		double beta = sqrt((momentum)/(momentum + mass*SpeedOfLight));
		
		double gamma = 1/sqrt(1 - pow(beta,2));

		double DistInLabFrame = sqrt(pow(fTreeVariableV0x - fTreeVariablePVx,2) + pow(fTreeVariableV0y - fTreeVariablePVy,2) + pow(fTreeVariableV0z - fTreeVariablePVz,2));
		double speed = beta*SpeedOfLight;

		double TimeInLabFrame = DistInLabFrame/speed;

		double ProperLifetime = TimeInLabFrame/gamma;

		if(ProperLifetime > 20){
			flag5++;
			continue;
		}
*/
		if(flag1 + flag2 + flag3 + flag4 == 0){
			continue;
		}		

		else{
			t2->Fill();	
		}
		

	}

	cout<<"No. of entries after cuts : "<<t2->GetEntries()<<endl;
	cout<<"Flag 1 : "<<flag1<<"\t"<<"Flag 2 : "<<flag2<<"\t"<<"Flag 3 : "<<flag3<<"\t"<<"Flag 4 : "<<flag4<<"\t"<<"Flag 5 : "<<flag5<<"\t"<<endl;
	cout<<endl<<endl<<"xyz : "<<xyz<<endl;

	TCanvas* white = new TCanvas("histpad", "histpad");
	white->Divide(2,2);
	white->cd(1);
	h1->SetFillColor(kBlue);
	h1->Draw();
	h0->SetFillColor(kRed);
	h0->Draw("same");
	
	white->cd(2);
	h2->Draw();
	h0->SetFillColor(kRed);
	h0->Draw("same");

	white->cd(3);
	h3->Draw(); 
	h0->SetFillColor(kRed);
	h0->Draw("same");

	white->cd(4);
	h0->SetFillColor(kWhite);
	h0->Draw();
	
	h4->SetFillColor(kRed);
	h4->Draw("same");
	

/*	

	// Store histograms in the root file
	// Make directories in a ROOT file (https://root.cern.ch/root/html/tutorials/io/dirs.C.html)
	// Also see (https://root.cern.ch/root/html/tutorials/tree/htest.C.html)

	TH1F h1("hgaus","histo from a gaussian",100,-3,3);
	h1.FillRandom("gaus",10000);
	h1.Write();
*/

// ----------------------------------------Final steps-------------------------------------------------

    t2->Write();
    f2->cd();
//    f2->close();

}