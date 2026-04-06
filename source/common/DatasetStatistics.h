/** @file */

#ifndef DATASETSTATISTICS_H
#define DATASETSTATISTICS_H

#include <stdexcept>
#include <vector>

#include "../descriptors/DescriptorStatistics.h"

namespace ksi
{
	class DatasetStatistics
	{
	private:
		std::vector<ksi::DescriptorStatistics> descriptorsStatistics; ///< vector of dataset descriptors

	public:
		/**
		 * The method adds DescriptorStatistics to the dataset.
		 *
		 * @param descriptorStat The object of DescriptorStatistics
		 * @date 2023-10-28
		 * @author Konrad Wnuk
		 */
		void addDescriptor(const ksi::DescriptorStatistics& descriptorStat);

		/**
		 * The method gets the number of descriptors stored in the dataset.
		 *
		 * @return The number of descriptors in the dataset
		 * @date 2023-10-28
		 * @author Konrad Wnuk
		 */
		size_t getNumberOfDescriptors() const;

		/**
		 * The method gets the DescriptorStatistics at index in the dataset.
		 *
		 * @param index The index of the DescriptorStatistics to retrieve
		 * @return Reference to the selected DescriptorStatistics
		 * @date 2023-10-28
		 * @author Konrad Wnuk
		 */
		ksi::DescriptorStatistics getDescriptorStatistics(const size_t index) const;
	};
}

#endif