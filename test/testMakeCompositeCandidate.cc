// $Id: testThrust.cc,v 1.5 2006/02/28 11:20:22 llista Exp $
#include <cppunit/extensions/HelperMacros.h>
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "PhysicsTools/CandUtils/interface/makeCompositeCandidate.h"
#include "PhysicsTools/CandUtils/interface/AddFourMomenta.h"
using namespace reco;
using namespace std;

namespace test {
  class DummyCandidate : public reco::LeafCandidate {
  public:
    DummyCandidate( const LorentzVector & p, Charge q = 0 ) : reco::LeafCandidate( q, p ) { }
    virtual DummyCandidate * clone() const { return new DummyCandidate( * this ); }
  };
}

class testMakeCompositeCandidate : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(testMakeCompositeCandidate);
  CPPUNIT_TEST(checkAll);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp() {}
  void tearDown() {}
  void checkAll(); 
};

CPPUNIT_TEST_SUITE_REGISTRATION(testMakeCompositeCandidate);

void testMakeCompositeCandidate::checkAll() {

  reco::Particle::LorentzVector p1( 1.0, 2.0, 3.0, 4.0 ), p2( 1.5, 2.5, 3.5, 4.5 );
  reco::Particle::Charge q1( 1 ), q2( -1 );
  test::DummyCandidate t1( p1, q1 );
  test::DummyCandidate t2( p2, q2 );

  auto_ptr<Candidate> cmp = makeCompositeCandidate( t1, t2 )[ AddFourMomenta() ];  
  CPPUNIT_ASSERT( cmp->numberOfDaughters() == 2 );
  const reco::Candidate * d[ 2 ];
  d[ 0 ] = cmp->daughter( 0 );
  d[ 1 ] = cmp->daughter( 1 );
  CPPUNIT_ASSERT( d[ 0 ]->charge() == q1 );
  CPPUNIT_ASSERT( d[ 0 ]->p4() == p1 );
  CPPUNIT_ASSERT( d[ 1 ]->charge() == q2 );
  CPPUNIT_ASSERT( d[ 1 ]->p4() == p2 );  

  auto_ptr<Candidate> cmp3 = makeCompositeCandidate( t1, t2, t1 )[ AddFourMomenta() ];  
  auto_ptr<Candidate> cmp4 = makeCompositeCandidate( t1, t2, t1, t2 )[ AddFourMomenta() ];  
}
