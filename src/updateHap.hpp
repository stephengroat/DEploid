/*
 * pfDeconv is used for deconvoluting Plasmodium falciparum genome from
 * mix-infected patient sample.
 *
 * Copyright (C) 2016, Sha (Joe) Zhu, Jacob Almagro and Prof. Gil McVean
 *
 * This file is part of pfDeconv.
 *
 * scrm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <vector>
#include <iostream>
#include "utility.hpp"
#include "panel.hpp"
#include "mersenne_twister.hpp"
#include "global.h"

#ifndef HAP
#define HAP

using namespace std;


class UpdateHap{
#ifdef UNITTEST
  friend class TestUpdateSingleHap;
#endif
  friend class McmcMachinery;
  friend class UpdateSingleHap;
  friend class UpdatePairHap;

    UpdateHap();
    UpdateHap( vector <double> &refCount,
               vector <double> &altCount,
               vector <double> &plaf,
               vector <double> &expectedWsaf,
               vector <double> &proportion,
               vector < vector <double> > &haplotypes,
               MersenneTwister* rg,
               size_t segmentStartIndex,
               size_t nLoci,
               Panel* panel );
    virtual ~UpdateHap();

    Panel* panel_;
    double missCopyProb_;
    MersenneTwister* recombRg_;
    MersenneTwister* recombLevel2Rg_;
    MersenneTwister* missCopyRg_;

    size_t strainIndex_;
    size_t kStrain_;
    size_t nPanel_;
    vector <double> newLLK;

    size_t segmentStartIndex_;
    size_t nLoci_;

    vector < vector <double> > emission_;

    // Methods
    virtual void calcExpectedWsaf( vector <double> & expectedWsaf, vector <double> &proportion, vector < vector <double> > &haplotypes);
    virtual void calcHapLLKs( vector <double> &refCount, vector <double> &altCount);
    virtual void buildEmission( double missCopyProb );
    // calcFwdProbs() differ for class UpdateSingleHap and UpdatePairHap
    //virtual void calcFwdProbs();
    virtual void samplePaths();
    virtual void addMissCopying( double missCopyProb );
    virtual void updateLLK();
    virtual void sampleHapIndependently(vector <double> &plaf);
};


class UpdateSingleHap : public UpdateHap{
#ifdef UNITTEST
  friend class TestUpdateSingleHap;
#endif
 friend class McmcMachinery;
  public:
    UpdateSingleHap ();
    UpdateSingleHap( vector <double> &refCount,
                      vector <double> &altCount,
                      vector <double> &plaf,
                      vector <double> &expectedWsaf,
                      vector <double> &proportion,
                      vector < vector <double> > &haplotypes,
                      MersenneTwister* rg,
                      size_t segmentStartIndex,
                      size_t nLoci,
                      Panel* panel, double missCopyProb,
                      size_t strainIndex );
    ~UpdateSingleHap();

  private:
    vector < vector <double> > fwdProbs_;

    size_t strainIndex_;
    vector <double> expectedWsaf0_;
    vector <double> expectedWsaf1_;
    vector <double> llk0_;
    vector <double> llk1_;

    vector <double> path_;
    vector <double> hap_;

    // Methods
    void calcExpectedWsaf( vector <double> & expectedWsaf, vector <double> &proportion, vector < vector <double> > &haplotypes);
    void calcHapLLKs( vector <double> &refCount, vector <double> &altCount);
    void buildEmission( double missCopyProb );
    void buildEmissionBasicVersion( double missCopyProb );
    void calcFwdProbs();
    void samplePaths();
    void addMissCopying( double missCopyProb );
    void sampleHapIndependently(vector <double> &plaf);
    void updateLLK();
};


class UpdatePairHap : public UpdateHap{
#ifdef UNITTEST
 friend class TestUpdatePairHap;
#endif
 friend class McmcMachinery;
  public:
     UpdatePairHap();
     UpdatePairHap( vector <double> &refCount,
                      vector <double> &altCount,
                      vector <double> &plaf,
                      vector <double> &expectedWsaf,
                      vector <double> &proportion,
                      vector < vector <double> > &haplotypes,
                      MersenneTwister* rg,
                      size_t segmentStartIndex,
                      size_t nLoci,
                      Panel* panel, double missCopyProb, bool forbidCopyFromSame,
                      size_t strainIndex1,
                      size_t strainIndex2 );
    ~UpdatePairHap();

  private:
    vector< vector < vector <double> > > fwdProbs_;

    size_t strainIndex1_;
    size_t strainIndex2_;

    vector <double> expectedWsaf00_;
    vector <double> expectedWsaf01_;
    vector <double> expectedWsaf10_;
    vector <double> expectedWsaf11_;
    vector <double> llk00_;
    vector <double> llk01_;
    vector <double> llk10_;
    vector <double> llk11_;
    vector <double> path1_;
    vector <double> path2_;
    vector <double> hap1_;
    vector <double> hap2_;

    // Methods
    void calcExpectedWsaf( vector <double> & expectedWsaf, vector <double> &proportion, vector < vector <double> > &haplotypes);
    void calcHapLLKs( vector <double> &refCount, vector <double> &altCount);
    void buildEmission( double missCopyProb );
    void calcFwdProbs( bool forbidCopyFromSame );
    void samplePaths();
    void addMissCopying( double missCopyProb );
    void sampleHapIndependently(vector <double> &plaf);
    void updateLLK();

    // Own methods
    vector <double> computeRowMarginalDist( vector < vector < double > > & probDist );
    vector <double> computeColMarginalDist( vector < vector < double > > & probDist );
    vector <size_t> sampleMatrixIndex( vector < vector < double > > &probDist );
};

#endif
