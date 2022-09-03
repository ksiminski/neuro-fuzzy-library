/** @file */

#ifndef GRANULAR_DBSCAN_H
#define GRANULAR_DBSCAN_H

#include <memory>
#include <vector>

#include "../partitions/partitioner.h"
#include "../tnorms/t-norm.h"
#include "../snorms/s-norm.h"
#include "../descriptors/descriptor.h"
#include "../descriptors/descriptor-triangular.h"

namespace ksi
{

    /** The class implements fuzzy DBSCAN clustering algorithm.
        @date 2022-03-11*/
    class granular_dbscan : virtual public partitioner
    {
    protected:
        /** Radius of a neighborhood */
        double _epsilon = -1;

        /** Minimum sum of points' membership values required to form a dense region */
        double _minPoints = -1;

        /** Maximum aggregated membership value allowed to consider the point as being a new core point */
        double _xi = -1;

        /** Minimum membership value required to consider the point as being core point's neighbour */
        double _psi = -1;

        /** Fuzzy clustering algorithm implementation */
        std::shared_ptr<partitioner> _fuzzyficationAlgorihm;

        /** S-norm */
        std::shared_ptr<s_norm> _snorm;

        /** T-norm */
        std::shared_ptr<t_norm> _tnorm;

    public:
        granular_dbscan();

        granular_dbscan(
            const double epsilon,
            const double minPoints,
            const double mi1,
            const double mi2,
            const partitioner &fuzzyficationAlgorihm,
            const s_norm &snorm,
            const t_norm &tnorm);

        granular_dbscan (const granular_dbscan &obj); 
    
        granular_dbscan & operator = (const granular_dbscan & obj);

        partition doPartition(const dataset &ds);

        std::vector<std::vector<std::shared_ptr<descriptor>>> prepareFuzzyData(const dataset &ds, std::shared_ptr<partitioner> algorithm);

        std::size_t findMaxMembIndex(const std::size_t datasetSize, const std::vector<double> &memberships, const double mi2, const std::vector<bool> &processed);

        /** */
        std::vector<double> findNeighboursMemberships(const std::vector<std::vector<std::shared_ptr<descriptor>>> &ds, const std::vector<std::shared_ptr<descriptor>> &granule);

        const descriptor_triangular calculateDistance(
            const std::shared_ptr<descriptor> &firstDescriptor,
            const std::shared_ptr<descriptor> &secondDescriptor);

        const double areaPercentageInSpace(const double epsilon, const descriptor_triangular &triangle);

        virtual partitioner *clone() const;
        virtual ~granular_dbscan();

        /** @return an abbreviation of a method */
        virtual std::string getAbbreviation() const;
    };
}
#endif
