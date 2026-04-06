/** @file */

#ifndef CROSS_VALIDATION_MODEL_H
#define CROSS_VALIDATION_MODEL_H

#include "reader.h"

#include <filesystem>
#include <memory>
#include <vector>
#include <mutex>

namespace ksi
{
    /**
     * @class cross_validation_model
     * An abstract class representing the base class for the cross-validation models.
     *
     * @date   2024-05-30
     * @author Konrad Wnuk
     */
    class cross_validation_model : public reader
    {
    protected:
        /** Pointer to a reader object which is used to read datasets */
        std::shared_ptr<reader> pReader = nullptr;

        /** Vector of datasets holds the subsets of the dataset */
        std::vector<dataset> datasets;

        /** Mutex for synchronizing access to datasets */
        mutable std::mutex datasets_mutex; 

    public:
        /**
         * Constructor for cross_validation_model.
         *
         * @param source_reader The reader object to initialize the pReader with.
         * @date 2024-06-04
         * @author Konrad Wnuk
         */
        cross_validation_model(reader& source_reader);

        /**
         * Copy constructor.
         *
         * @param other The cross_validation object to copy.
         * @date 2024-06-08
         * @author Konrad Wnuk
         */
        cross_validation_model(const cross_validation_model& other);

        /**
        * Move constructor.
        *
        * @param other The cross_validation object to move.
        * @date 2024-06-08
        * @author Konrad Wnuk
        */
        cross_validation_model(cross_validation_model&& other) noexcept;

        /**
         * Copy assignment operator.
         *
         * @param other The cross_validation object to copy.
         * @return Reference to the copied cross_validation object.
         * @date 2024-06-08
         * @author Konrad Wnuk
         */
        cross_validation_model& operator=(const cross_validation_model& other);

        /**
         * Move assignment operator.
         *
         * @param other The cross_validation object to move.
         * @return Reference to the moved cross_validation object.
         * @date 2024-06-08
         * @author Konrad Wnuk
         */
        cross_validation_model& operator=(cross_validation_model&& other) noexcept;

        /**
         * Virtual destructor for cross_validation_model.
         */
        virtual ~cross_validation_model() = default;

        /**
         * Splits the data into a specified number of subsets.
         *
         * @param base_dataset The dataset to be split.
         * @param n The number of subsets to split the data into. Default is 10.
         * @date 2024-05-30
         * @author Konrad Wnuk
         */
        virtual void split(const dataset & base_dataset, const unsigned int n = 10) = 0;
        
        /**
		 * Saves the data to a specified directory.
		 *
		 * @param directory The directory where the data will be saved.
		 * @param filename The base name for the files to be saved. Default is "dataset".
		 * @param extension The file extension for the files to be saved. Default is ".data".
		 * @param overwrite Flag to control whether to overwrite the existing files. Default is false.
		 * @date 2024-06-30
		 * @author Konrad Wnuk
		 */
        virtual void save(const std::filesystem::path& directory, const std::filesystem::path& filename = "dataset", const std::filesystem::path& extension = ".data", const bool overwrite = false) const = 0;

        /**
         * Reads data from a specified file.
         *
         * @param file_directory The path of the file to read the data from.
         * @return A dataset containing the data read from the file.
         * @date 2024-05-30
         * @author Konrad Wnuk
         */
        virtual dataset read_file(const std::filesystem::path& file_directory) = 0;

        /**
		 * Reads data from a specified directory.
		 *
		 * @param directory The directory to read the data from.
		 * @param file_regex_pattern The pattern to match the files. Defaults to ".*\\.data$".
		 * @date 2024-05-30
		 * @author Konrad Wnuk
		 */
        virtual void read_directory(const std::filesystem::path& directory, const std::string& file_regex_pattern = ".*\\.data$") = 0;

        /**
         * Reads data from a file and splits it into subsets.
         *
         * @param file_path The path of the file to read the data from.
         * @param n The number of subsets to split the data into.
         * @date 2024-06-14
         * @author Konrad Wnuk
         */
        virtual void read_and_split_file(const std::filesystem::path& file_path, const unsigned int n = 10) = 0;
    };
}

#endif
