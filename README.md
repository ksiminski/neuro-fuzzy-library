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
1. subspace fcm   (__Citation request__ If you use this library please cite [^subspace])
1. fubi (fuzzy biclustering)  (__Citation request__ If you use this library please cite [^fubi])
1. fcom
1. dbscan


### make 3
This example presents clustering algorithms for incomplete datasets:
1. rfcm   (__Citation request__ If you use this library please cite [^rfcm])   
2. rfcom  (__Citation request__ If you use this library please cite [^rfcom])
3. rsfcm  (__Citation request__ If you use this library please cite [^rsfcm])

### make 4
This example presents a fuzzy system. 

### make 5
This example presents neuro-fuzzy systems for
1. classification 
	1. MA
	2. TSK
	3. ANNBFIS
	4. subspace ANNBFIS   (__Citation request__ If you use this library please cite [^subspace])
	5. FuBi ANNBFIS       (__Citation request__ If you use this library please cite [^fubi])
1. regression:
	1. MA
	2. TSK
	3. ANNBFIS
	4. subspace ANNBFIS   (__Citation request__ If you use this library please cite [^subspace])
	5. FuBi ANNBFIS       (__Citation request__ If you use this library please cite [^fubi])
	6. prototype TSK      (__Citation request__ If you use this library please cite [^prototype])
	7. prototype ANNBFIS  (__Citation request__ If you use this library please cite [^prototype]) 
 
------------

[^nfl]: Krzysztof Siminski, NFL -- Free Library for Fuzzy and Neuro-Fuzzy Systems, [in] Beyond Databases, Architectures and Structures. Paving the Road to Smart Data Processing and Analysis (Stanisław Kozielski, Dariusz Mrozek, Paweł Kasprowski, Bożena Małysiak-Mrozek, Daniel Kostrzewa, eds.), Springer International Publishing, 2019, pp. 139-150. 


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
 
[^rfcm]: Krzysztof Simiński, Clustering with missing values, [in] Fundamenta Informaticae, 2013, volume 123, number 3, pp. 331-350.
```
@ARTICLE{id:Siminski2013Clustering,
      author = {Krzysztof Siminski},
      title = {Clustering with missing values},
      journal = {Fundamenta Informaticae},
      year = {2013},
      volume = {123},
      pages = {331-350},
      number = {3},
}
```

[^rfcom]: Krzysztof Siminski, Robust subspace neuro-fuzzy system with data ordering, [in] Neurocomputing, 2017, volume 238, pp. 33-43
```
@article{id:Siminski2017Robust,
	year = {2017},
	author = {Krzysztof Siminski},
	journal = {Neurocomputing},
	pages = {33-43},
	volume = {238},
	title = {Robust subspace neuro-fuzzy system with data ordering},
	doi = {10.1016/j.neucom.2017.01.034},
}
```

[^rsfcm]: Krzysztof Simiński, Rough fuzzy subspace clustering for data with missing values, Computing & Informatics, 2014, volume 33, number 1, pp. 131-153. 
```
@article{id:Siminski2014Rough,
  title={Rough fuzzy subspace clustering for data with missing values},
  author={Siminski, Krzysztof},
  journal={Computing \& Informatics},
  volume={33},
  number={1},
  year={2014},
  pages={131--153},
} 
``` 

[^subspace]: Krzysztof Siminski, Neuro-fuzzy system with weighted attributes, [in] Soft Computing, 2014, volume 18, number 2, pp. 285-297. doi: 10.1007/s00500-013-1057-z

```
ARTICLE{id:Siminski2014Neuro,
      author = {Krzysztof Siminski},
      title = {Neuro-fuzzy system with weighted attributes},
      journal = {Soft Computing},
      volume = {18}, 
      number = {2}, 
      pages = {285--297}, 
      year = {2014},
      doi = {10.1007/s00500-013-1057-z},
}
```

[^fubi]: Krzysztof Siminski, FuBiNFS – fuzzy biclustering neuro-fuzzy system, [in] Fuzzy Sets and Systems, 2022, volume 438, pp. 84–106

```
@article{id:Siminski2021FuBiNFS,
	author = "Krzysztof Siminski",
	doi = "10.1016/j.fss.2021.07.009",
	issn = "0165-0114",
	journal = "Fuzzy Sets and Systems",
	keywords = "Neuro-fuzzy system; Biclustering; Subspace clustering; Subspace neuro-fuzzy system; Attribute weights",
	title = "{FuBiNFS} – fuzzy biclustering neuro-fuzzy system",
	url = "https://www.sciencedirect.com/science/article/pii/S0165011421002499",
	year = "2021"
}
```

[^protoTSK]: Krzysztof Siminski, Prototype based granular neuro-fuzzy system for regression task, [in] Fuzzy Sets and Systems, 2022.
```
@article{id:Siminski2022Prototype,
	author = "Krzysztof Siminski",
	doi = "10.1016/j.fss.2022.03.001",
	issn = "0165-0114",
	journal = "Fuzzy Sets and Systems",
	keywords = "Prototype; Granular computing; Neuro-fuzzy system; Regression",
	title = "Prototype based granular neuro-fuzzy system for regression task",
	url = "https://www.sciencedirect.com/science/article/pii/S0165011422000963",
	year = "2022"
}
```


