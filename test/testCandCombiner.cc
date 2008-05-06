// $Id: testCandCombiner.cc,v 1.4 2008/03/18 12:51:55 wmtan Exp $
#include <cppunit/extensions/HelperMacros.h>
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "PhysicsTools/CandUtils/interface/CandCombiner.h"
#include "PhysicsTools/Utilities/interface/AnySelector.h"
#include "DataFormats/Common/test/TestHandle.h"
#include <iostream>
using namespace reco;

class testCandCombiner : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(testCandCombiner);
  CPPUNIT_TEST(checkAll);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp() {}
  void tearDown() {}
  void checkAll(); 
};

CPPUNIT_TEST_SUITE_REGISTRATION(testCandCombiner);

void testCandCombiner::checkAll() {
  using namespace std;
  using namespace edm;
  typedef vector<LeafCandidate> LeafCandidateCollection;
  LeafCandidateCollection c;
  edm::TestHandle<LeafCandidateCollection> hd(&c, ProductID(1));
  RefProd<LeafCandidateCollection> cands(hd);
  c.push_back(LeafCandidate(+1, math::XYZTLorentzVector(1, 0, 0, 1)));
  c.push_back(LeafCandidate(-1, math::XYZTLorentzVector(0, 1, 0, 1)));
  CandCombiner<AnySelector> combiner1(+1, -1);
  auto_ptr<CompositeCandidateCollection> cc1 = combiner1.combine(cands);
  CPPUNIT_ASSERT(cc1->size() == 1);
  CandCombiner<AnySelector> combiner2;
  auto_ptr<CompositeCandidateCollection> cc2 = combiner2.combine(cands);
  CPPUNIT_ASSERT(cc2->size() == 1);
  c.push_back(LeafCandidate(+1, math::XYZTLorentzVector(0, 0, 1, 1)));
  auto_ptr<CompositeCandidateCollection> cc3 = combiner1.combine(cands);
  CPPUNIT_ASSERT(cc3->size() == 2);
  auto_ptr<CompositeCandidateCollection> cc4 = combiner2.combine(cands);
  CPPUNIT_ASSERT(cc4->size() == 3);
}
