// $Id: testCandCombiner.cc,v 1.2 2007/06/18 18:33:47 llista Exp $
#include <cppunit/extensions/HelperMacros.h>
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "PhysicsTools/CandUtils/interface/CandCombiner.h"
#include "PhysicsTools/Utilities/interface/AnySelector.h"
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

namespace testcandcombiner {
  template<class T>
  struct TestHandle {
    TestHandle(const edm::ProductID& iId, const T* iProd) : id_(iId), prod_(iProd) {}
    const edm::ProductID& id() const { return id_;}
    const T* product() const { return prod_;}
  private:
    edm::ProductID id_;
    const T* prod_;
  };
}

CPPUNIT_TEST_SUITE_REGISTRATION(testCandCombiner);

void testCandCombiner::checkAll() {
  using namespace testcandcombiner;
  using namespace std;
  using namespace edm;
  CandidateCollection c;
  TestHandle<CandidateCollection> hd(ProductID(1), &c);
  CandidateRefProd cands( hd );
  auto_ptr<Candidate> c1( new LeafCandidate( +1, math::XYZTLorentzVector( 1, 0, 0, 1 ) ) );
  auto_ptr<Candidate> c2( new LeafCandidate( -1, math::XYZTLorentzVector( 0, 1, 0, 1 ) ) );
  c.push_back( c1 );
  c.push_back( c2 );
  CandCombiner<CandidateCollection, AnySelector> combiner1( +1, -1 );
  auto_ptr<CandidateCollection> cc1 = combiner1.combine( cands );
  CPPUNIT_ASSERT( cc1->size() == 1 );
  CandCombiner<CandidateCollection, AnySelector> combiner2;
  auto_ptr<CandidateCollection> cc2 = combiner2.combine( cands );
  CPPUNIT_ASSERT( cc2->size() == 1 );
  auto_ptr<Candidate> c3( new LeafCandidate( +1, math::XYZTLorentzVector( 0, 0, 1, 1 ) ) );
  c.push_back( c3 );
  auto_ptr<CandidateCollection> cc3 = combiner1.combine( cands );
  CPPUNIT_ASSERT( cc3->size() == 2 );
  auto_ptr<CandidateCollection> cc4 = combiner2.combine( cands );
  CPPUNIT_ASSERT( cc4->size() == 3 );
}
