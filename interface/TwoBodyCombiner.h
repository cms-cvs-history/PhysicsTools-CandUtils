#ifndef CandUtils_TwoBodyCombiner_h
#define CandUtils_TwoBodyCombiner_h
/** \class TwoBodyCombiner
 *
 * Performs all possible combination of candidate pairs,
 * selects the combinations via a specified CandSelector,
 * with the possibility to check the composite candidate
 * electric charge. The algorithm also checks that the
 * paired candidates do not overlap.
 * 
 * If the same input collection is passed twice, the 
 * algorithm avoids double counting the candidate pairs
 *
 * The composite candidate kinematics is set up 
 * adding the two daughters four-momenta
 *
 * \author Luca Lista, INFN
 *
 * \version $Revision: 1.13 $
 *
 * $Id: TwoBodyCombiner.h,v 1.13 2006/08/04 11:56:38 llista Exp $
 *
 */
#include "DataFormats/Candidate/interface/OverlapChecker.h"
#include "PhysicsTools/CandUtils/interface/CandSelector.h"
#include "PhysicsTools/CandUtils/interface/AddFourMomenta.h"
#include "PhysicsTools/Parser/interface/SingleObjectSelector.h"

class TwoBodyCombiner {
public:
  /// constructor from a selector, specifying optionally to check for charge
  TwoBodyCombiner( const reco::parser::SelectorPtr &, 
		   bool checkCharge, int charge = 0 );
  /// return all selected candidate pairs
  std::auto_ptr<reco::CandidateCollection> 
  combine( const reco::CandidateCollection *, const reco::CandidateCollection * );

protected:
  /// verify that the two candidate don't overlap and check charge
  bool preselect( const reco::Candidate &, const reco::Candidate & ) const;
  /// returns a composite candidate combined from two daughters
  reco::Candidate * combine( const reco::Candidate &, const reco::Candidate & );
  /// flag to specify the checking of electric charge
  bool checkCharge_;
  /// electric charge of the composite
  int charge_;
  /// utility to setup composite candidate kinematics from daughters
  AddFourMomenta addp4_;
  /// utility to check candidate daughters overlap
  OverlapChecker overlap_;
  /// candidate selector
  SingleObjectSelector<reco::Candidate> select_;
};

#endif
