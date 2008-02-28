#include "PhysicsTools/StarterKit/interface/HistoMuon.h"
//#include "DataFormats/MuonReco/interface/MuonEnergy.h"

#include <iostream>
#include <sstream>

using pat::HistoMuon;
using namespace std;

// Constructor:


HistoMuon::HistoMuon(std::string dir,
		   double pt1, double pt2, double m1, double m2)
  : HistoGroup<Muon>( dir, "Muon", "mu", pt1, pt2, m1, m2)
{
  addHisto( h_trackIso_ =
	    new PhysVarHisto( "muTrackIso", "Muon Track Isolation", 20, 0, 10, currDir_, "", "vD" )
	   );

  addHisto( h_caloIso_  =
	    new PhysVarHisto( "muCaloIso",  "Muon Calo Isolation",  20, 0, 10, currDir_, "", "vD" )
	    );

  addHisto( h_leptonID_ =
            new PhysVarHisto( "muLeptonID", "Muon Lepton ID",       20, 0, 1, currDir_, "", "vD" )
            );

  addHisto( h_calCompat_ =
            new PhysVarHisto( "muCaloCompat", "Muon Calorimetry Compatability", 100, 0, 1, currDir_, "", "vD" )
            );

  addHisto( h_nChambers_ =
            new PhysVarHisto( "muNChamber", "Muon # of Chambers", 51, -0.5, 50.5, currDir_, "", "vD" )
            );

  addHisto( h_caloE_ =
            new PhysVarHisto( "muCaloE", "Muon Calorimeter Energy", 50, 0, 50, currDir_, "", "vD" )
            );
  addHisto( h_type_ =
            new PhysVarHisto( "muType", "Muon Type", 65, -0.5, 64.5, currDir_, "", "vD" )
            );
}



void HistoMuon::fill( const Muon *muon, uint iMu )
{

  // First fill common 4-vector histograms

  HistoGroup<Muon>::fill( muon, iMu);

  // fill relevant muon histograms
  h_trackIso_->fill( muon->trackIso(), iMu );
  h_caloIso_ ->fill( muon->caloIso() , iMu );
  h_leptonID_->fill( muon->leptonID(), iMu );

  const reco::Muon* recoMuon = muon->originalObject();
  h_calCompat_->fill( recoMuon->getCaloCompatibility(), iMu );
  h_nChambers_->fill( recoMuon->numberOfChambers(), iMu );
  h_type_->fill( recoMuon->getType(), iMu );

  reco::MuonEnergy muEnergy = recoMuon->getCalEnergy();

  h_caloE_->fill( muEnergy.em+muEnergy.had+muEnergy.ho, iMu );

}

void HistoMuon::fillCollection( const std::vector<Muon> & coll )
{

  HistoGroup<Muon>::fillCollection( coll );

  h_size_->fill( coll.size() );     //! Save the size of the collection.

  std::vector<Muon>::const_iterator
    iobj = coll.begin(),
    iend = coll.end();

  uint i = 1;              //! Fortran-style indexing
  for ( ; iobj != iend; ++iobj, ++i ) {
    fill( &*iobj, i);      //! &*iobj dereferences to the pointer to a PHYS_OBJ*
  }
}


void HistoMuon::clearVec()
{
  HistoGroup<Muon>::clearVec();

  h_trackIso_->clearVec();
  h_caloIso_->clearVec();
  h_leptonID_->clearVec();
}
