// Copyright © 2015, Battelle National Biodefense Institute (BNBI);
// all rights reserved. Authored by: Brian Ondov, Todd Treangen,
// Sergey Koren, and Adam Phillippy
//
// See the LICENSE.txt file included with this software for license information.

#ifndef INCLUDED_CommandDistance
#define INCLUDED_CommandDistance

#include "Command.h"
#include "Sketch.h"

class CommandDistance : public Command
{
public:
    
    struct CompareInput
    {
        CompareInput(const Sketch & sketchRefNew, Sketch * sketchQueryNew, const std::string fileNew, const Sketch::Parameters & parametersNew, double maxDistanceNew, double maxPValueNew)
            :
            sketchRef(sketchRefNew),
            sketchQuery(sketchQueryNew),
            file(fileNew),
            parameters(parametersNew),
            maxDistance(maxDistanceNew),
            maxPValue(maxPValueNew)
            {}
        
        const Sketch & sketchRef;
        Sketch * sketchQuery;
        std::string nameRef;
        const std::string file;
        const Sketch::Parameters & parameters;
        double maxDistance;
        double maxPValue;
    };
    
    struct CompareOutput
    {
        CompareOutput(const Sketch & sketchRefNew, Sketch * sketchQueryNew)
            :
            sketchRef(sketchRefNew),
            sketchQuery(sketchQueryNew)
        {}
        
        ~CompareOutput()
        {
            delete sketchQuery;
        }
        
        struct PairOutput
        {
            uint64_t numer;
            uint64_t denom;
            double distance;
            double pValue;
            bool pass;
        };
        
        const Sketch & sketchRef;
        Sketch * sketchQuery;
        
        std::vector<PairOutput> pairs;
    };
    
    CommandDistance();
    
    int run() const; // override
    
private:
    
    void writeOutput(CompareOutput * output, bool table) const;
};

CommandDistance::CompareOutput * compare(CommandDistance::CompareInput * data);
void compareSketches(CommandDistance::CompareOutput::PairOutput & output, const Sketch::Reference & refRef, const Sketch::Reference & refQry, uint64_t sketchSize, int kmerSize, double kmerSpace, double maxDistance, double maxPValue);
double pValue(uint64_t x, uint64_t lengthRef, uint64_t lengthQuery, double kmerSpace, uint64_t sketchSize);

#endif
