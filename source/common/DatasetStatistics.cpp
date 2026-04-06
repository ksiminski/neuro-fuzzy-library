#include "DatasetStatistics.h"

#include "../service/debug.h"

void ksi::DatasetStatistics::addDescriptor(const ksi::DescriptorStatistics& descriptorStat)
{
	descriptorsStatistics.push_back(descriptorStat);
}

size_t ksi::DatasetStatistics::getNumberOfDescriptors() const
{
	return descriptorsStatistics.size();
}

ksi::DescriptorStatistics ksi::DatasetStatistics::getDescriptorStatistics(const size_t index) const
{
	try
	{
		if (index >= 0 && index < descriptorsStatistics.size()) {
			return descriptorsStatistics[index];
		}
		else {
			throw std::out_of_range("Invalid index");
		}
	}
	CATCH;
}

