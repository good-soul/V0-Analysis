// the code to submit jobs for K0 analysis on the grid
class AliAnalysisGrid;
class AliAnalysisAlien;

void Load()
{
	gSystem->SetIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS -I$ALICE_PHYSICS/include -I$ALICE_ROOT/ITS -I$ALICE_ROOT/TPC -I$ALICE_ROOT/CONTAINERS -I$ALICE_ROOT/STEER/STEER -I$ALICE_ROOT/STEER/STEERBase -I$ALICE_ROOT/STEER/ESD -I$ALICE_ROOT/STEER/AOD -I$ALICE_PHYSICS/PWG/Tools -I$ALICE_PHYSICS/PWGLF/STRANGENESS  -I$ALICE_PHYSICS/PWGLF/STRANGENESS/LambdaK0PbPb -I$ALICE_ROOT/TRD -I$ALICE_ROOT/macros -I$ALICE_ROOT/ANALYSIS -g");   
    gSystem->Load("libCore");
    gSystem->Load("libGeom");
    gSystem->Load("libVMC");
    gSystem->Load("libPhysics");
    gSystem->Load("libTree");
    gSystem->Load("libMinuit");
    gSystem->Load("libSTEERBase");
    gSystem->Load("libESD");
    gSystem->Load("libAOD");
    gSystem->Load("libANALYSIS");
    gSystem->Load("libOADB");
    gSystem->Load("libANALYSISalice");
    gSystem->Load("libGui");
    gSystem->Load("libRAWDatabase");
    gSystem->Load("libCDB");
    gSystem->Load("libSTEER");
    gSystem->Load("libTRDbase");
    gSystem->Load("libPWGTRD"); 
}

void RunAnalysisKaon()
{
    const Bool_t readAOD = 1;
	Load();
    TString 	   trainName    =  "PWGLF";
    TString 	   analysisMode =  "grid"; // "local", "grid"
    TString 	   pluginmode   =  "terminate"; // "full", "test" "terminate"
    TString 	   inputMode    =  "list"; // "list", "xml", or "dataset"
	Long64_t   	   nentries     =   123567890, firstentry=0;
    Bool_t   useAlienPlugin     =   kTRUE;
    Bool_t useParFiles=kFALSE;
    TBenchmark benchmark;
    benchmark.Start("AliAnalysisTaskBackground");

    gSystem->AddIncludePath(Form("-I\"%s/include\" -I\"%s/include\"", gSystem->ExpandPathName("$ALICE_ROOT"),gSystem->ExpandPathName("$ALICE_PHYSICS")));
    gROOT->ProcessLine(Form(".include %s/include %s/include", gSystem->ExpandPathName("$ALICE_ROOT"), gSystem->ExpandPathName("$ALICE_PHYSICS")));



    TString testfileslistWithPlugin =  "files.txt";

    if(analysisMode=="grid") TGrid::Connect("alien://") ;    //  Create an AliRunTagCuts and an AliEventTagCuts Object

    if(useAlienPlugin)
     {
	    AliAnalysisGrid *alienHandler = CreateAlienHandler(pluginmode,useParFiles,testfileslistWithPlugin);
	    if(!alienHandler) return;
     }

    TChain *chainAOD = 0;
    TString dataset; // for proof

     AliAnalysisManager *mgr = new AliAnalysisManager("My Manager","My Manager"); // create the analysis manager object
     mgr->SetDebugLevel(10);
    if(useAlienPlugin) mgr->SetGridHandler(alienHandler);

    // Input
    AliESDInputHandler *inputHandler = new AliESDInputHandler("handler","handler for D2H");
    mgr->SetInputEventHandler(inputHandler);

    //---AliPIDResponse--------------------------------------------------------
  gROOT->LoadMacro("./AddTaskPIDResponse.C");
  Bool_t isMC=kFALSE; // kTRUE in case of MC
  AddTaskPIDResponse(isMC); 
  //-------------------------------------------------------------------------

  gROOT->LoadMacro("./AddTaskPhysicsSelection.C");
  //Arguments: this is MC, yes; Reject Background, yes; Don't necessarily compute BG
AliPhysicsSelectionTask* physSelTask = AddTaskPhysicsSelection();
  //physSelTask->SetAnalyzeMC();


  //---AliCentrality---------------------------------------------------------
  // load task itself
  gROOT->LoadMacro("./AddTaskCentrality.C");
  // create centrality task, add to manager
  AliCentralitySelectionTask* centralityTask = AddTaskCentrality();
  //-------------------------------------------------------------------------




    //gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
    AliAnalysisTaskSE *setuptask = AddTaskPIDResponse(kFALSE,kTRUE);

    gROOT->LoadMacro("./AliAnalysisTaskExtractV0.cxx++g");
    gROOT->LoadMacro("./AddTaskExtractV0.C");
    AliAnalysisTaskExtractV0* task =  AddTaskExtractV0();

    task->SetpAVertexSelection(kTRUE);

    if(!mgr->InitAnalysis()) return;
    mgr->PrintStatus();

    if(analysisMode=="grid" && !useAlienPlugin) analysisMode="local";
    if(analysisMode!="proof")  mgr->StartAnalysis(analysisMode.Data(),chainAOD,nentries,firstentry);
    else    mgr->StartAnalysis(analysisMode.Data(),dataset.Data(),nentries,firstentry);

    return;
}


//_______________________________| CreateAlienHandler |________________________________
AliAnalysisGrid* CreateAlienHandler(TString pluginmode="test",Bool_t useParFiles=kFALSE, TString testfileslistWithPlugin="")
{
    AliAnalysisAlien *plugin = new AliAnalysisAlien();
    plugin->SetRunMode(pluginmode.Data());
    plugin->SetUser("jvora");  
    plugin->SetAliPhysicsVersion("vAN-20160402-1");
    plugin->SetAPIVersion("V1.1x");
    //plugin->SetAliROOTVersion("v5-34-30");  // select any set of aliroot and aliphysics versions among the version available on alimonitor site
    //plugin->SetAliPhysicsVersion("master"); 
    plugin->SetNtestFiles(1);    // this works only in the test mode, number 1 specifies the number of files to run analysis on  
   // gROOT->LoadMacro("AddGoodRuns.C");					// ask Neelima for the goodruns.C file
    plugin->SetGridDataDir("/alice/data/2013/LHC13b");  // set the directory corresponding to your analysis data/alice/data/2013/LHC13b/000195483/ESDs/pass2/13000195483000.100

    plugin->SetDataPattern("*/ESDs/pass2/*/AliESDs.root"); // change the details according to your data
    plugin->SetRunPrefix("000");   // "000" for real data and "" for MC data
    plugin->AddRunNumber("195483");
//	plugin->AddRunNumber("");  this part is not required if we have the addgoodruns.C file
    plugin->SetGridWorkingDir("v0");  // Define alien work directory where all files will be copied. Relative to alien $HOME.
    plugin->SetExecutable("myanalysis.sh");		   // Name of executable
    plugin->SetGridOutputDir("output"); 		   // Declare alien output directory. Relative to working directory.
 /* Declare the analysis source files names separated by blancs. To be compiled runtime
     using ACLiC on the worker nodes.  */
    plugin->SetAnalysisSource("AliAnalysisTaskExtractV0.cxx");   
    // Declare all libraries (other than the default ones for the framework.
    plugin->SetAdditionalLibs(" AliAnalysisTaskExtractV0.h AliAnalysisTaskExtractV0.cxx"); // add the requied .so library given in the analysis note
 
    if(useParFiles)
     {
        plugin->EnablePackage("STEERBase.par");
        plugin->EnablePackage("AOD.par");
        plugin->EnablePackage("ANALYSIS.par");
        plugin->EnablePackage("OADB.par");
        plugin->EnablePackage("ANALYSISalice.par");        
    }

    plugin->SetKeepLogs(kTRUE);
    plugin->SetDefaultOutputs(kTRUE);
    // merging via jdl            ask if this is required
    //plugin->SetMergeViaJDL(kTRUE);
    plugin->SetMergeViaJDL(kFALSE); //uncomment this line after merging via JDL has been completed to donwload the result to present folder
    //plugin->SetOneStageMerging(kTRUE);
    //plugin->SetMaxMergeStages(2);
    plugin->SetFileForTestMode(testfileslistWithPlugin.Data());
    plugin->SetTTL(10000);
    plugin->SetAnalysisMacro("AnalysisLFkaon.C");	       // Optionally set a name for the generated analysis macro (default MyAnalysis.C)
    return plugin;
}
