/** @file */

#include <memory>
#include <vector>
#include <string>

#include "../partitions/dbscan.h"
#include "../metrics/metric.h"
#include "../metrics/metric-euclidean.h"

#include "../service/debug.h"


ksi::dbscan::dbscan()
	: _metric_object(ksi::metric_euclidean().clone())  
{
}

ksi::dbscan::dbscan(const double epsilon, const int minPoints, const ksi::metric &metric_object)
	: _metric_object(metric_object.clone())
{
	this->_epsilon = epsilon;
	this->_minPoints = minPoints;
}

ksi::partition ksi::dbscan::doPartition(const ksi::dataset &ds)
{
	try
	{
		// cluster
		int C = -1;

		std::size_t dsSize = ds.getNumberOfData();

		// partition matrix
		std::vector<std::vector<double>> mU;

		std::vector<DatumState> datumStates(dsSize, UNDEFINED);

		for (std::size_t i = 0; i < dsSize; ++i)
		{
			if (datumStates[i] != UNDEFINED)
				continue;

			auto neighborsIndices = findNeighborsIndices(i, ds);
			auto neighborsSize = neighborsIndices.size();

			if (neighborsSize < this->_minPoints)
			{
				datumStates[i] = NOISE;
				continue;
			}

			++C;
			mU.push_back(std::vector<double>(dsSize, 0.0));
			// cluster membership
			mU[C][i] = 1.0;
			datumStates[i] = CLUSTER_MEMBER;

			for (std::size_t j = 0; j < neighborsSize; ++j)
			{
				auto neighborIndex = neighborsIndices[j];

				if (datumStates[neighborIndex] == NOISE)
				{
					mU[C][neighborIndex] = 1.0;
					datumStates[neighborIndex] = CLUSTER_MEMBER;
				}
				if (datumStates[neighborIndex] != UNDEFINED)
					continue;

				mU[C][neighborIndex] = 1.0;
				datumStates[neighborIndex] = CLUSTER_MEMBER;

				auto expandedNeighborsIndices = findNeighborsIndices(neighborIndex, ds);
				auto expandedNeighborsSize = expandedNeighborsIndices.size();

				if (expandedNeighborsSize >= this->_minPoints)
				{
					// concatenate
					neighborsIndices.insert(
						neighborsIndices.end(),
						expandedNeighborsIndices.begin(),
						expandedNeighborsIndices.end());
					neighborsSize += expandedNeighborsSize;
				}
			}
		}

		ksi::partition part;
		part.setPartitionMatrix(mU);
		return part;
	}
	CATCH
}

std::vector<std::size_t> ksi::dbscan::findNeighborsIndices(const std::size_t index, const ksi::dataset &ds)
{
	try 
	{
        std::vector<std::size_t> neighbors;
		std::size_t dsSize = ds.getNumberOfData();
		const ksi::datum *datum = ds.getDatum(index);

		for (std::size_t i = 0; i < dsSize; i++)
		{
			auto datum_ = ds.getDatum(i);

			if (this->_metric_object->calculateDistance(*datum, *datum_) <= this->_epsilon)
				neighbors.push_back(i);
		}
        return neighbors;
    }
	CATCH;
}

ksi::partitioner *ksi::dbscan::clone() const
{
	return new dbscan(*this);
}

std::string ksi::dbscan::getAbbreviation() const
{
	return std::string("dbscan");
}

ksi::dbscan::~dbscan()
{
}
