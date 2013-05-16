#!/bin/bash

tempFile="/tmp/testMonoThread"

# Execution du programme
# et redirection de ses sorties vers un fichier temporaire
./MonoThread &> $tempFile

nbLines=`wc -l $tempFile`
nbDebugLines=`grep -i "^[0-9]" $tempFile | wc -l`
nbDebugErrorLines=`grep -i "^[0-9].*(error\|erreur\|fail)" $tempFile | wc -l`
nbErrorLines=`grep -i "^[^0-9]" $tempFile | wc -l`
nbThreads=`cut -d ' '  -f 1 $tempFile | grep -e "^[0-9]" | sort -ur | wc -l`

echo "<<<< "`date`
echo "Lignes affichées : $nbDebugLines"
echo "Errors ou warnings : $nbErrorLines"
echo "Debugs d'erreur : $nbDebugErrorLines"
echo "Threads : $nbThreads"
echo "Nombre de lignes par thread :"

for idThread in `cut -d ' '  -f 1 $tempFile | grep -e "^[0-9]" | sort -ur`
do
	nbThreadLines=`grep "^$idThread" $tempFile | wc -l`
	echo " $idThread : $nbThreadLines lignes"
	sed -n "s/^$idThread \(.*\)/\1/p" $tempFile | nl
done

echo ">>>>"

# Découpe toutes les lignes en colonnes séparées par des espaces et n'en affiche que la première
#cut -d ' '  -f 1 test.txt 

# Idem mais n'affiche que celles débutant par un numéro de thread
#cut -d ' '  -f 1 test.txt | grep -e "^[0-9]"

# Affiche les numéros des threads du programme
#cut -d ' '  -f 1 test.txt | grep -e "^[0-9]" | sort | uniq

# N'affiche que les debugs du thread numéro 304068900
#grep 3040689008 test.txt 
