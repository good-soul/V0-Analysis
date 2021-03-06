AliAnalysisTaskExtractV0 *AddTaskExtractV0( Bool_t lSwitchIsNuclear      = kTRUE, 
                                            Bool_t lSwitchINT7           = kTRUE,
                                            Bool_t lSwitchUseOnTheFly    = kFALSE,
                                            Bool_t lSwitchTakeAllTracks  = kFALSE, 
                                            const TString lMasterJobSessionFlag = "")
{
// Creates, configures and attaches to the train a cascades check task.
   // Get the pointer to the existing analysis manager via the static access method.
   //==============================================================================
   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if (!mgr) {
      ::Error("AddTaskExtractV0", "No analysis manager to connect to.");
      return NULL;
   }   

   // Check the analysis type using the event handlers connected to the analysis manager.
   //==============================================================================
   if (!mgr->GetInputEventHandler()) {
      ::Error("AddTaskExtractV0", "This task requires an input event handler");
      return NULL;
   }   
   TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"

   // Create and configure the task
	 AliAnalysisTaskExtractV0 *taskv0extract = new AliAnalysisTaskExtractV0("taskv0extract");

   //Configuration
   taskv0extract -> SetIsNuclear     ( lSwitchIsNuclear     );
   taskv0extract -> SetINT7Trigger   ( lSwitchINT7          );
   taskv0extract -> SetUseOnTheFly   ( lSwitchUseOnTheFly   );
   taskv0extract -> SetTakeAllTracks ( lSwitchTakeAllTracks );

   mgr->AddTask(taskv0extract);

   TString outputFileName = AliAnalysisManager::GetCommonFileName();
   
   outputFileName += ":PWGLFExtractV0";
   //if (lCollidingSystems) outputFileName += "_AA_";
   outputFileName += "_PP";
   if (mgr->GetMCtruthEventHandler()) outputFileName += "_MC";
   if (lSwitchUseOnTheFly==kTRUE) outputFileName += "_OnTheFly";
   //if(lMasterJobSessionFlag.Length()) outputFileName += lMasterJobSessionFlag.Data();
   
   Printf("Set OutputFileName : \n %s\n", outputFileName.Data() );

   AliAnalysisDataContainer *coutputList = mgr->CreateContainer("clistV0",
							     TList::Class(),
							     AliAnalysisManager::kOutputContainer,
							     outputFileName );
   AliAnalysisDataContainer *coutputTree = mgr->CreateContainer("cTree",
							     TTree::Class(),
							     AliAnalysisManager::kOutputContainer,
							     outputFileName );
   
   //This one you should merge in file-resident ways...
   coutputTree->SetSpecialOutput();

   mgr->ConnectInput( taskv0extract, 0, mgr->GetCommonInputContainer());
   mgr->ConnectOutput(taskv0extract, 1, coutputList);
   mgr->ConnectOutput(taskv0extract, 2, coutputTree);
   
   return taskv0extract;
}   
