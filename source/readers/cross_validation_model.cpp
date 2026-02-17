/** @file */

#include "cross_validation_model.h"

ksi::cross_validation_model::cross_validation_model(ksi::reader& source_reader)
{
    pReader = std::shared_ptr<ksi::reader>(source_reader.clone());
}

ksi::cross_validation_model::cross_validation_model(const cross_validation_model& other)
{
    pReader = std::shared_ptr<ksi::reader>(other.pReader->clone());
    std::lock_guard<std::mutex> lock(other.datasets_mutex);
    datasets = other.datasets;
}

ksi::cross_validation_model::cross_validation_model(cross_validation_model&& other) noexcept
	: pReader(std::move(other.pReader))
{
    std::lock_guard<std::mutex> lock(other.datasets_mutex);
    datasets = std::move(other.datasets);
}

ksi::cross_validation_model& ksi::cross_validation_model::operator=(const cross_validation_model& other)
{
    if (this != &other)
    {
        pReader = std::shared_ptr<ksi::reader>(other.pReader->clone());
        std::lock_guard<std::mutex> lock(other.datasets_mutex);
        datasets = other.datasets;
    }
    return *this;
}

ksi::cross_validation_model& ksi::cross_validation_model::operator=(cross_validation_model&& other) noexcept
{
    if (this != &other)
    {
        pReader = std::move(other.pReader);
        std::lock_guard<std::mutex> lock(other.datasets_mutex);
        datasets = std::move(other.datasets);
    }
    return *this;
}
