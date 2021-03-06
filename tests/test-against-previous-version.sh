#!/bin/bash
previousVersion="0.5-beta"
previousVersionTag=v${previousVersion}
wget --no-check-certificate https://github.com/mcveanlab/DEploid/archive/${previousVersionTag}.tar.gz -o /dev/null
tar -xf ${previousVersionTag}.tar.gz
cd DEploid-${previousVersion}; ./bootstrap; make; cd ..

jobBrief="classic"

sameFlags="-exclude data/testData/labStrains.test.exclude.txt -plaf data/testData/labStrains.test.PLAF.txt -panel data/testData/labStrains.test.panel.txt -seed 1 -ref data/testData/PG0390-C.test.ref -alt data/testData/PG0390-C.test.alt -vcfOut -k 2 -sigma 2"
./dEploid ${sameFlags} -o current
./DEploid-${previousVersion}/dEploid ${sameFlags} -o previous

diff current.${jobBrief}.prop previous.prop
if [ $? -ne 0 ]; then
  echo ""
  echo "Proportion unequal"
  exit 1
fi


echo ${PWD}


sameFlags="-exclude data/testData/labStrains.test.exclude.txt -plaf data/testData/labStrains.test.PLAF.txt -noPanel -ibd -seed 1 -ref data/testData/PG0390-C.test.ref -alt data/testData/PG0390-C.test.alt -vcfOut -k 2 -sigma 2 -ibdSigma 0.1"
./dEploid ${sameFlags} -o current
./DEploid-${previousVersion}/dEploid ${sameFlags} -o previous

diff current.${jobBrief}.prop previous.prop
if [ $? -ne 0 ]; then
  echo ""
  echo "Proportion unequal"
  exit 1
fi


echo ${PWD}
rm -r "${previousVersionTag}".tar.gz DEploid-${previousVersion} current* previous*
