#!/bin/bash

# Jezeli istnieje juz plik makefile, to go skopiuj do makefile-old
if [ -e makefile ] ; then mv makefile makefile-old ; fi 

shopt -s extglob 
find . -type f -name "*.cpp" -or -name "*.c" | awk '
  BEGIN  {
             printf("\n");
             printf("############################################\n");
             printf("# Prosty generator plikow makefile dla g++ #\n");
             printf("# Simple generator of makefiles for g++    #\n");
             printf("#          Krzysztof Siminski, 2023        #\n");
             printf("############################################\n");
             printf("\n");
             printf("# [PL] OPCJE:\n");
             printf("# [EN] OPTIONS:\n");
             printf("\n");
             printf("compiler=g++\n");
             printf("standard=-std=c++23\n");
             printf("\n");
             printf("# [PL] optymalizacja [EN] optimisation\n");
             printf("optRelease=-O3\n");
             printf("optDebug=\n");
             printf("\n");
             printf("errors=-pedantic-errors\n");
             printf("\n");
             printf("release=\n");
             printf("#debug=-g\n");
             printf("# [PL] opcja -pg dla profilowania:\n");
             printf("# [EN] -pg option for profiling:\n");
             printf("debug=-pg\n");
             printf("\n");
             printf("#parallel=-fopenmp\n");
             printf("parallel=\n");
             printf("\n");
             printf("release_folder=_release\n");
             printf("debug_folder=_debug\n");
             printf("\n");
             printf("#sanitizer=-fsanitize=address\n");
             printf("#libasan=-static-libasan\n");
             printf("sanitizer=\n");
             printf("libasan=\n");
             printf("\n");
             printf("#############################\n");
             printf("\n");
             printf(".PHONY : clean $(debug_folder) $(release_folder)\n");
             printf("\n");
             printf("# [PL] opcje uruchomienia projektu:\n");
             printf("# [EN] project run options:\n");
             printf("\n");
             
             compilation_debug = "$(compiler) $(standard) $(debug) $(optyDebug) $(parallel) $(errors) $(sanitizer) -c -o $@ $^";
             compilation_release = "$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -c -o $@ $^";
            
             linking_debug = "$(compiler) $(standard) $(debug) $(optDebug) $(parallel) $(errors) $(sanitizer) $(libasan) -o $@ $^";
             linking_release = "$(compiler) $(standard) $(release) $(optRelease) $(parallel) $(errors) -o $@ $^";
             
             printf("release : $(release_folder) $(release_folder)/main\n");
             printf("\t./$(release_folder)/main\n");
             printf("\n");
             printf("debug : $(debug_folder) $(debug_folder)/main\n");
             printf("\tvalgrind --leak-check=yes ./$(debug_folder)/main\n");
             printf("#\t./$(debug_folder)/main\n");
             printf("\n");
             printf("# [PL] profilowanie [EN] profiling\n");
             printf("gprof : $(debug_folder) $(debug_folder)/main\n");
             printf("\t./$(debug_folder)/main\n");
             printf("\tgprof ./$(debug_folder)/main gmon.out\n");
             printf("\trm gmon.out\n");
             printf("\n");
             printf("# [PL] utworzenie folderow:\n");
             printf("# [EN] create directories:\n");
             printf("\n");
             printf("$(release_folder) : \n");
             printf("\tmkdir -p $(release_folder)\n");
             printf("$(debug_folder) : \n");
             printf("\tmkdir -p $(debug_folder)\n");
             printf("\n");
             printf("# [PL] kompilacja zrodel:\n");
             printf("# [EN] source compilation:\n");
             printf("\n");
             
             #i = systime();
         }

 
         {  
             zrodlo = $1;
             sub(/\.\//, "", zrodlo);
             obiekt = zrodlo;
             sub(/\//, "-", obiekt);
             split(zrodlo, nazwa_zrodlo, ".");
             split(obiekt, nazwa_obiekt, ".");
             printf("$(release_folder)/%s.o : %s.%s\n", nazwa_obiekt[1], nazwa_zrodlo[1], nazwa_zrodlo[2]); 
             printf("\t%s\n", compilation_release);
             printf("$(debug_folder)/%s.o : %s.%s\n", nazwa_obiekt[1], nazwa_zrodlo[1], nazwa_zrodlo[2]); 
             printf("\t%s\n", compilation_debug);
             
             # pliki[i++] = nazwa_obiekt[1];
             # printf("%d ", i);
             pliki[nazwa_obiekt[1]] = nazwa_obiekt[1];
         } 
     
 END     {
             printf("\n");
             printf("# [PL] linkowanie:\n");
             printf("# [EN] linking:\n");
             printf("\n");
             
             printf ("$(release_folder)/main : \\\n");
             for (i in pliki)
                printf ("$(release_folder)/%s.o \\\n", pliki[i]);
             printf("\n");
             printf("\t%s\n", linking_release);
             printf("\n");
             printf ("$(debug_folder)/main : \\\n");
             for (i in pliki)
                printf ("$(debug_folder)/%s.o \\\n", pliki[i]);
             printf("\n");
             printf("\t%s\n", linking_debug);
             printf("\n");
          
             printf("# [PL] usuniecie plikow skompilowanych:\n");
             printf("# [EN] remove compiled files:\n");

             printf("\n");
             printf("clean : \n");
             printf("\tif [ -d $(debug_folder)      ] ; then rm -r $(debug_folder)   ; fi\n");
	     printf("\tif [ -d $(release_folder)    ] ; then rm -r $(release_folder) ; fi;\n");
             printf("\n");
             printf("\n");
             
             i = 0;
             minutes[i++] = 5;
             minutes[i++] = 10;
             minutes[i++] = 30;
             minutes[i++] = 60;
             
             for (m in minutes)
             {
                czas = minutes[m];
                printf ("%d-minutes:\n", czas);
                printf ("\tfind $(release_folder)/ -maxdepth 1 -type f -mmin -%d -delete\n", czas);
                printf ("\tfind $(debug_folder)/ -maxdepth 1 -type f -mmin -%d -delete\n", czas);
                printf ("\n");
             } 
             
             i = 0;
             days[i++] = 1;
             for (m in days)
             {
                czas = days[m];
                printf ("%d-days:\n", czas);
                printf ("\tfind $(release_folder)/ -maxdepth 1 -type f -mtime -%d -delete\n", czas);
                printf ("\tfind $(debug_folder)/ -maxdepth 1 -type f -mtime -%d -delete\n", czas);
                printf ("\n");
             } 
 
	          printf ("doxygen:\n");
	          printf ("\tdoxygen doxyfile\n");
	          printf ("\n");
             
         }     
     
'  > makefile


