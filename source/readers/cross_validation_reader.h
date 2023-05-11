/** @file */


#ifndef CROSS_VALIDATION_READER_H
#define CROSS_VALIDATION_READER_H

#include <filesystem>
#include <memory>
#include <vector>

#include "../readers/reader.h"


namespace ksi
{
	class cross_validation_reader
	{

		public:
			cross_validation_reader ();
			cross_validation_reader (const std::filesystem::path & path, const ksi::reader & reader);
			cross_validation_reader (const cross_validation_reader & wzor);
			cross_validation_reader (cross_validation_reader && wzor);
			cross_validation_reader & operator= (const cross_validation_reader & wzor);
			cross_validation_reader & operator= (cross_validation_reader && wzor);
			virtual ~cross_validation_reader ();

    protected:
        std::pair<ksi::dataset, ksi::dataset> split_data(const std::size_t current);
   		protected:
			std::filesystem::path _path;
			std::shared_ptr<ksi::reader> _pReader = nullptr;
            std::vector<std::string> _datasetFiles;
            std::vector<ksi::dataset> _datasets; 

            // ITERATOR
		public:
            
			struct iterator
			{
                
            protected: 
            public:
                std::size_t aktualny = 0; 
                std::pair<ksi::dataset, ksi::dataset> _traintest;
                bool end = false;
                cross_validation_reader * _p = nullptr;
                
				public:
					//iterator ();
					iterator ();
					iterator& operator++ ();
					iterator& operator++ (int);
					bool operator!= (const iterator & p);
					std::pair<ksi::dataset, ksi::dataset> operator * ();
                    std::pair<ksi::dataset, ksi::dataset> * operator->();
                    friend iterator begin();
			};

			iterator begin();
			iterator end();

	};
}


#endif
