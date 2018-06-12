import FWCore.ParameterSet.Config as cms

from DQMOffline.Trigger.ObjMonitor_cfi import hltobjmonitoring

# HLT_
HMesonGammamonitoring = hltobjmonitoring.clone()
HMesonGammamonitoring.FolderName = cms.string('HLT/Higgs/HMesonGamma/')
HMesonGammamonitoring.numGenericTriggerEventPSet.hltInputTag   = cms.InputTag( "TriggerResults","","HLT" )
HMesonGammamonitoring.numGenericTriggerEventPSet.hltPaths = cms.vstring("HLT_Photon35_TwoProngs35_v*")
#HMesonGammamonitoring.metSelection = cms.string("")
HMesonGammamonitoring.phoSelection = cms.string("pt > 35 && abs(eta)<2.1 && hadTowOverEm<0.1 && full5x5_r9>0.9 && chargedHadronIso<1.295 && neutralHadronIso < 5.931+0.0163*pt+0.000014*pt*pt && photonIso < 6.641+0.0034*pt")
HMesonGammamonitoring.trkSelection = cms.string("pt > 5 && quality('highPurity')")
HMesonGammamonitoring.nphotons = cms.int32(1)
HMesonGammamonitoring.nmesons = cms.int32(1)
#HMesonGammamonitoring.metSelection = cms.string("pt>150")

hmesongammamonitoring = cms.Sequence(
    HMesonGammamonitoring
)

