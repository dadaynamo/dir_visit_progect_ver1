# dir_visit_progect_ver1
Progetto per università di Pisa UNIPI . Applicazione in c e bash per la visita di una path tree di cartelle e file in modalità BFS e funzione di calcolo per i singoli file con estensione .dat

Si consideri una cartella con al suo interno files ed altre cartelle contenenti, tra gli altri, files con estensione “.dat”. Tali file sono file testuali che contengono numeri interi o decimali, uno per riga, eventualmente separati da righe vuote. I numeri possono essere preceduti o seguiti da spazi vuoti e/o caratteri di tabulazione. Per ogni file “.dat” vogliamo calcolare la media aritmetica e la deviazione standard dei numeri in esso contenuti.

output richiesto
n avg std file
--------------------------------------------------------------------------
dir: .
3 3.00 .81 prova1.dat
1 1.00 0 prova2.dat
dir: ./provadir
8 178.59 402.10 provadir.dat
dir: ./provadir/provadir2
5 32.00 3.08 provadir2-2.dat
7 30.71 29.81 provadir2-1.dat
dir: ./provadir/provadir1
13 4.61 2.55 provadir1.dat
dir: ./provadir/provadir2/provadir3
7 30.71 29.81 provadir3-3.dat
13 18.92 10.57 provadir3-1.dat
6 50.83 67.58 provadir3-2.dat

Dove ‘n’ è il totale dei numeri validi nel file considerati per il calcolo, ‘avg’ è la media aritmetica, ‘std’ è la deviazione standard, e ‘file’ è il nome del file considerato. Nel Riquadro1 è mostrato il contenuto del file provadir.dat contenuto nella directory provadir, avente n=8 righe valide (su un totale di 11), una media aritmetica pari a avg=178.59 ed una deviazione standard pari a std=402.10. Nel Riquadro2 vengono riportati i caratteri presenti nel file provadir.dat ottenuti con il comando od.


Si chiede di realizzare uno script Bash in grado di fare il calcolo e fornire un output come descritto
precedentemente e un analogo programma scritto in C che operi esattamente come lo script e che produca
lo stesso output. Lo script Bash non può far uso dei comandi “sed” ed “awk”. Il programma C deve utilizzare
chiamate POSIX per la lettura dei metadati dei file e della directory dir.

Il comando make se lanciato senza argomenti, deve compilare il programma C (senza warnings né errori). Il
codice C che non compila non verrà valutato. Il Makefile deve avere almeno i seguenti target fittizi (PHONY):
test1 e test2. Il primo target (test1) manda in esecuzione lo script Bash su una delle directory di test fornite.
Il secondo target fittizio (test2) manda in esecuzione il programma C su una delle directory di test fornite. Il
codice deve girare correttamente sulla macchina del corso (laboratorio2.di.unipi.it). Il codice che non esegue
sulla macchina di laboratorio non verrà valutato.
