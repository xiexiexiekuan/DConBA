#ifndef BEST_SCORE_CALCULATOR_H
#define	BEST_SCORE_CALCULATOR_H

#include "typedefs.h"
#include "score_cache.h"

namespace bestscorecalculators {
    
    class BestScoreCalculator {
        
    public:
        virtual float getScore(varset &pars) = 0;
        virtual float getScore(int index) = 0;
        virtual varset &getParents(int index) = 0;
        virtual varset &getParents() = 0;
        virtual void initialize(const scoring::ScoreCache &scoreCache) = 0;
        virtual int size() = 0;
        virtual void print() = 0;
    };
    
}


#endif	/* BEST_SCORE_CALCULATOR_H */

