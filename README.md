Free Neuro-Fuzzy Library
========================

Neuro-fuzzy is an implementation of fuzzy tools for data analysis:
* data modifiers,
* clustering algorithms,
* fuzzy systems, 
* neuro-fuzzy systems.

The project is implemented in the C++ language (at least C++11 standard).
 
There are 5 examples of usage of the library.

Run `make 1` to run the 1st example, `make 2` – the 2nd example, and finally `make 5` to run the 5th example.

Run `make doxygen` to produce a Doxygen documentation and UML class diagrams for the project.

__Citation request__ If you use this library please cite [^nfl]

## Examples

### make 1   
This example presents modifiers of data:
1. normalisation
2. standardisation
3. marginalisation of incomplete data items
4. imputation of missing data with a constant
5. imputation of missing data with averages of the attributes
6. imputation of missing data with medians of the attributes
5. imputation of missing data with averages of 3 nearest neighbours
6. imputation of missing data with medians of 3 nearest neighbours
7. imputation of missing data with values from 3 nearest neighbours and then the imputed data set standardized
8. a series of data modifiers: imputer with values from knn (k == 3) + standardiser, imputer with constant value, normaliser, standardiser, average imputer, imputer with constant value + normaliser, average imputer + standardiser
9. imputer with constant value + normaliser + average imputer + standardiser


### make 2
This example presents clustering algorithms:
1. fcm
1. possibilistic fcm
1. conditional fcm
1. subspace fcm
1. fubi (fuzzy biclustering)
1. fcom
1. dbscan


### make 3
This example presents clustering algorithms for incomplete datasets:
1. rfcm
2. rfcom
3. rsfcm

### make 4
This example presents a fuzzy system. 

### make 5
This example presents neuro-fuzzy systems for
1. classification 
	1. MA
	2. TSK
	3. ANNBFIS
	4. subspace ANNBFIS
	5. FuBi ANNBFIS
1. regression:
	1. MA
	2. TSK
	3. ANNBFIS
	4. subspace ANNBFIS
	5. FuBi ANNBFIS
	6. prototype TSK
	7. prototype ANNBFIS
 
------------
[^nfl]: 
```
@inproceedings{id:Siminski2019NFL,
	address = "Cham",
	author = "Krzysztof Siminski",
	booktitle = "Beyond Databases, Architectures and Structures. Paving the Road to Smart Data Processing and Analysis",
	doi = "10.1007/978-3-030-19093-4_11",
	editor = "Stanisław Kozielski and Dariusz Mrozek and Paweł Kasprowski and Bożena Małysiak-Mrozek and Daniel Kostrzewa",
	isbn = "978-3-030-19093-4",
	pages = "139–150",
	publisher = "Springer International Publishing",
	title = "{NFL} – Free Library for Fuzzy and Neuro-Fuzzy Systems",
	year = "2019"
}
```
 

