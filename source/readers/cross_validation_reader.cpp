

#include <filesystem>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "../readers/cross_validation_reader.h"
#include "../readers/reader.h"



ksi::cross_validation_reader::cross_validation_reader ()
{
}

ksi::cross_validation_reader::cross_validation_reader (const std::filesystem::path & path, const ksi::reader & reader)
{
	_path = path;
    _pReader = reader.clone();
    
    // trzeba bedzie odczytac wszystkie pliki w folderze
    for (auto const & element : std::filesystem::directory_iterator{path}) 
    {
        if (not element.is_directory())
            _datasetFiles.push_back(element.path().string());
    }
    
    // trzeba odczytac wszystkie dane z plikow
    for (const std::string & s : _datasetFiles)
    {
//         std::cout << s << std::endl;
        auto ds = _pReader->read(s);
        _datasets.push_back(ds);
    }
}

std::pair<ksi::dataset, ksi::dataset> ksi::cross_validation_reader::split_data(const std::size_t current)
{
    ksi::dataset train, test;
    if (current < _datasets.size())
    {
        test = _datasets[current]; 
        
        for (std::size_t i = 0; i < _datasets.size(); i++)
        {
            if (i != current)
                train += _datasets[i];
        }
    }
    return {train, test};
}


ksi::cross_validation_reader::iterator::iterator()
{
   
}


ksi::cross_validation_reader::iterator ksi::cross_validation_reader::begin()
{
    ksi::cross_validation_reader::iterator it;
    it._traintest = split_data(0);
    it._p = this; 
    return it;
}

std::pair<ksi::dataset, ksi::dataset> ksi::cross_validation_reader::iterator::operator*()
{
    return _traintest;
}

std::pair<ksi::dataset, ksi::dataset> * ksi::cross_validation_reader::iterator::operator->()
{
    return & _traintest;
}


ksi::cross_validation_reader::iterator & ksi::cross_validation_reader::iterator::operator++()
{
    aktualny++;
//     debug(aktualny);
//     debug(_p->_datasets.size());
    if (aktualny < _p->_datasets.size())
    {
        _traintest = _p->split_data(aktualny);
    }
    else 
        end = true;
    return *this;
}

ksi::cross_validation_reader::iterator & ksi::cross_validation_reader::iterator::operator++(int)
{
    this->operator++();
    return *this;
}

ksi::cross_validation_reader::iterator ksi::cross_validation_reader::end()
{
    ksi::cross_validation_reader::iterator it;
    it.end = true;
    return it;
}

bool ksi::cross_validation_reader::iterator::operator!=(const ksi::cross_validation_reader::iterator& p)
{
//     debug(this->aktualny);
//     debug(p.aktualny);
    return this->end != p.end;
}


ksi::cross_validation_reader::~cross_validation_reader ()
{
	// delete what is to delete

}

ksi::cross_validation_reader::cross_validation_reader (const ksi::cross_validation_reader & wzor)
{
	// copy what is to copy

}

ksi::cross_validation_reader & ksi::cross_validation_reader::operator= (const ksi::cross_validation_reader & wzor)
{
	if (this == & wzor)
		return *this;


	// remove what is to remove

	// allocate what is to allocate

	return *this;
}

ksi::cross_validation_reader::cross_validation_reader (ksi::cross_validation_reader && wzor)
{
	// swap what is to swap

}

ksi::cross_validation_reader & ksi::cross_validation_reader::operator= (ksi::cross_validation_reader && wzor)
{
	if (this == & wzor)
		return *this;


	// swap what is to swap

	return *this;
}



