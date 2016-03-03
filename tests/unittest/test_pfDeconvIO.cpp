#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../../src/pfDeconvIO.hpp"

class TestIO : public CppUnit::TestCase {

    CPPUNIT_TEST_SUITE( TestIO );
    CPPUNIT_TEST( testMainConstructor );
    CPPUNIT_TEST( testNotEnoughArg );
    CPPUNIT_TEST( testWrongType );
    CPPUNIT_TEST( testFileNameMissing );
    CPPUNIT_TEST( testInvalidInputFile );
    CPPUNIT_TEST( testUnknowArg );
    CPPUNIT_TEST( testExtractRefAltPlaf );
    CPPUNIT_TEST_SUITE_END();

  private:
    PfDeconvIO* input_;

  public:
    void setUp() {
        this->input_ = new PfDeconvIO( "labStrains/labStrains_first100_PLAF.txt",
                                       "labStrains/PG0390_first100ref.txt",
                                       "labStrains/PG0390_first100alt.txt",
                                       (size_t)5);
        }

    void tearDown() {
        delete input_;
    }

    void testMainConstructor() {
        char *argv[] = { "./pfDeconv" };
        CPPUNIT_ASSERT_NO_THROW ( PfDeconvIO pars(1, argv) );
        PfDeconvIO pars(1, argv);
        CPPUNIT_ASSERT_EQUAL((size_t)0, pars.argv_.size());
        CPPUNIT_ASSERT_EQUAL( true, pars.help());
        char *argv1[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-o", "tmp1" };
        CPPUNIT_ASSERT_NO_THROW ( PfDeconvIO pars1(11, argv1) );
    }

    void testNotEnoughArg(){
        char *argv1[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-o" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(10, argv1), NotEnoughArg );

        char *argv2[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-seed"};
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(10, argv2), NotEnoughArg );

        char *argv3[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-p"};
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(10, argv3), NotEnoughArg );

        char *argv4[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-k"};
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(10, argv4), NotEnoughArg );

        char *argv5[] = { "./pfDeconv",
                         "-ref",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(8, argv5), NotEnoughArg );

        char *argv6[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(8, argv6), NotEnoughArg );

        char *argv7[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf",
                         "-panel", "labStrains/lab_first100_Panel.txt" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(8, argv7), NotEnoughArg );

        char *argv8[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(8, argv8), NotEnoughArg );
    }


    void testWrongType(){
        char *argv2[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-seed", "asdf"};
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(10, argv2), NotEnoughArg );

        char *argv3[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-p", "asdf"};
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(10, argv3), NotEnoughArg );

        char *argv4[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-k", "asdf"};
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(10, argv4), NotEnoughArg );
    }


    void testFileNameMissing(){
        char *argv1[] = { "./pfDeconv",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-o", "tmp1" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(9, argv1), FileNameMissing );

        char *argv2[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-o", "tmp1" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(9, argv2), FileNameMissing );

        char *argv3[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-o", "tmp1" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(9, argv3), FileNameMissing );

        char *argv4[] = { "./pfDeconv",
                         "-ref", "labStrains/PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-o", "tmp1" };
        CPPUNIT_ASSERT_THROW ( PfDeconvIO pars(9, argv4), FileNameMissing );
    }


    void testInvalidInputFile(){
        char *argv[] = { "./pfDeconv",
                         "-ref", "PG0390_first100ref.txt",
                         "-alt", "labStrains/PG0390_first100alt.txt",
                         "-plaf", "labStrains/labStrains_first100_PLAF.txt",
                         "-panel", "labStrains/lab_first100_Panel.txt",
                         "-o", "tmp1" };
        CPPUNIT_ASSERT_THROW( PfDeconvIO pars(11, argv), InvalidInputFile );
    }


    void testUnknowArg(){
        char *argv[] = { "./pfDeconv", "-unknow"};
        CPPUNIT_ASSERT_THROW( PfDeconvIO pars(2, argv), UnknowArg );
    }


    void testExtractRefAltPlaf(){
        CPPUNIT_ASSERT_EQUAL((size_t)100, this->input_->nLoci_);
        //"Pf3D7_01_v3"	93157	0.0190612159917058
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0190612159917058, this->input_->plaf_[0], 0.000000000001);
        //"Pf3D7_01_v3"	93157	85
        CPPUNIT_ASSERT_EQUAL(85.0, this->input_->refCount_[0]);
        //"Pf3D7_01_v3"	93157	0
        CPPUNIT_ASSERT_EQUAL(0.0, this->input_->altCount_[0]);

        //"Pf3D7_01_v3"	95518	0.687463394087723
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.687463394087723, this->input_->plaf_[4], 0.000000000001);
        //"Pf3D7_01_v3"	95518	156
        CPPUNIT_ASSERT_EQUAL(156.0, this->input_->refCount_[4]);
        //"Pf3D7_01_v3"	95518	46
        CPPUNIT_ASSERT_EQUAL(46.0, this->input_->altCount_[4]);

        //"Pf3D7_01_v3"	113396	0.0207016179419847
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0207016179419847, this->input_->plaf_[20], 0.000000000001);
        //"Pf3D7_01_v3"	113396	177
        CPPUNIT_ASSERT_EQUAL(177.0, this->input_->refCount_[20]);
        //"Pf3D7_01_v3"	113396	0
        CPPUNIT_ASSERT_EQUAL(0.0, this->input_->altCount_[20]);

        //"Pf3D7_01_v3"	180270	0.426732645350475
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.426732645350475, this->input_->plaf_[99], 0.000000000001);
        //"Pf3D7_01_v3"	180270	199
        CPPUNIT_ASSERT_EQUAL(199.0, this->input_->refCount_[99]);
        //"Pf3D7_01_v3"	180270	0
        CPPUNIT_ASSERT_EQUAL(0.0, this->input_->altCount_[99]);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestIO );
