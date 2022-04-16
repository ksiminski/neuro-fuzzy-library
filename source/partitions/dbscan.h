/** @file */

#ifndef DBSCAN_H
#define DBSCAN_H

#include <memory>
#include <vector>
#include <string>

#include "../partitions/partitioner.h"
#include "../metrics/metric.h"

namespace ksi
{
	enum DatumState
	{
		UNDEFINED,
		NOISE,
		CLUSTER_MEMBER
	};

	/** The class implements DBSCAN clustering algorithm.
	 * @author Dawid Suchy
	 * @date 2021-07-27
	 */
	class dbscan : virtual public partitioner
	{
	protected:
		/** Radius of a neighborhood */
		double _epsilon = -1;

		/** Minimum number of points required to form a dense region */
		int _minPoints = -1;

		std::shared_ptr<metric> _metric_object;

	public:
		dbscan();

		dbscan(const double epsilon, const int minPoints, const metric &metric_object);

		/** The method executes DBSCAN clustering algorithm.
		 * @param ds dataset to cluster
		 * @return partition into clusters
		 */
		partition doPartition(const dataset &ds);

		/** The method finds density-based neighbors of a data point
		 * @param index index of a datum to find neighbors for
		 * @param ds dataset
		 * @return vector of indices of neighbors
		 */
		std::vector<std::size_t> findNeighborsIndices(const std::size_t index, const dataset &ds);

		virtual partitioner *clone() const;
		virtual ~dbscan();

		/** @return an abbreviation of a method */
		virtual std::string getAbbreviation() const;
	};
}
#endif
