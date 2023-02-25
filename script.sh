#! /bin/bash

# funzione per prelievo dati da file dat
function export_data {
#variabili local
local sum=0
local count=0
local avg=0.0
local r=0
local dev=0.0
local dev_pot=0.0
local s_dev_pot=0.0
local deviaziones=0.0
#echo "siamo dentro la funzione export_data"
#echo $(basename $1)
#echo "________________________________________________________________________"

#/*****************

	#calcolo media dei numeri nel file
	while read -r riga; do
		if [[ -n "$riga" ]] && [[ $riga =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
 			#echo "$riga"
			sum=$(echo "$sum + $riga" | bc)
			count=$((count+1))
		fi
	done < $1
	#echo "count è $count"
	#calcolo media
	if [ $count != 0 ]; then
		avg=$(echo "scale=2; $sum / $count" | bc)
	else
	avg=0
	fi

	#calcolo dev standard
	# count
	# media
if  (( $count > 0 )); then
	#echo "ciao count: $count"
	while read -r riga; do
		if [[ -n "$riga" ]]; then
			dev=$(echo "$riga - $avg" | bc)
			dev_pot=$(echo "$dev * $dev" | bc)
			s_dev_pot=$(echo "$s_dev_pot + $dev_pot" | bc)
			#echo "dev: $dev  dev_pot: $dev_pot  s_dev_pot: $s_dev_pot"
		fi
	done < $1

	deviaziones=$(echo "scale=2; sqrt($s_dev_pot / ($count))" | bc)
else
	deviaziones=0
fi

#echo "deviazione standard: $deviaziones"
#stampaggio riga
echo "$count		$avg		$deviaziones		$(basename $file)"

#echo "la somma dei numeri è $sum"
#echo "il numero di numeri è $count"
#echo "la media è $avg"
#*****************/
}



function visita() {


local q=("$1")



until (( ${#q[@]} == 0 )); do

	local d=${q[0]}
	q=("${q[@]:1}")

	echo "dir: $d"

	for file in "$d/"*; do
		if [[ -d "$file" ]]; then
			#visita "$file"
			q+=("$file")
		fi
	done

	for file in "$d/"*; do
		if [[ -f "$file" ]] && [[ "$file" == *.dat ]]; then
			export_data $file
		fi
	done

done
}


#programma inizia qui in basso con stampa tabella dinamica
echo "n		avg		std		file"
echo "________________________________________________________________________"

if [ $# -lt 1 ]; then
	echo "Warning: lo script non ha nessun parametro in ingresso. Di default il parametro sarà . (cartella corrente)"
	exit 1
else
	stringa=$1
	if [[ "${stringa: -1}" = "/" ]]; then
	stringa="${stringa::-1}"
	fi
	visita $stringa
fi


#ricerca file per file .dat e creazione valori
#find . -type f -name "*.dat" > file_list.txt | while read file; do

	#leggi il contenuto del file corrente

#	dir=$(dirname $file)
#	echo "dir. $dir"
#	export_data $file
#done





echo "________________________________________________________________________"
#fine stampaggio tabella
