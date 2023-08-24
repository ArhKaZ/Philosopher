#!/bin/bash

# Tableau de séries d'arguments à tester
series_arguments=(
    "1 800 200 200 10"
    "2 405 200 200 10" "2 404 200 200 10" "2 403 200 200 10" "2 402 200 200 10" "2 401 200 200 10"
    "3 605 200 200 10" "3 604 200 200 10" "3 603 200 200 10" "3 602 200 200 10" "3 601 200 200 10"
    "4 405 200 200 10" "4 404 200 200 10" "4 403 200 200 10" "4 402 200 200 10" "4 401 200 200 10"
    "5 605 200 200 10" "5 604 200 200 10" "5 603 200 200 10" "5 602 200 200 10" "5 601 200 200 10"
    "10 405 200 200 10" "10 404 200 200 10" "10 403 200 200 10" "10 402 200 200 10" "10 401 200 200 10"
    "100 415 200 200 10" "100 414 200 200 10" "100 413 200 200 10" "100 412 200 200 10" "100 411 200 200 10"
    "101 615 200 200 10" "101 614 200 200 10" "101 613 200 200 10" "101 612 200 200 10" "101 611 200 200 10"
)

# Nombre de fois à tester chaque série d'arguments
nombre_tests=5

# Nom du dossier de stockage des fichiers de sortie
output_directory="output_tests"

# Créer le dossier de stockage s'il n'existe pas
mkdir -p "$output_directory"

# Fonction pour exécuter le programme, vérifier le résultat et enregistrer la sortie dans un fichier
run_and_check() {
    local arg="$1"
    local test_number="$2"
    local output=$(./philo $arg)  # Exécute le programme et capture la sortie
    local last_line=$(echo "$output" | tail -n 1)  # Récupère la dernière ligne de la sortie

    if echo "$output" | grep -q "died"; then
        echo -en "./philo $arg : \e[31mDIED\e[0m"
    else
        echo -en "./philo $arg : \e[32mPASSED\e[0m"
    fi

    echo " - $last_line"
    echo "$output" > "${output_directory}/out_${arg// /_}_test_${test_number}.txt"  # Enregistre la sortie dans le fichier
}

# Boucle pour tester chaque série d'arguments
for series in "${series_arguments[@]}"; do
    echo "===== Test de la série d'arguments : $series ====="
    for arg in "${series[@]}"; do
        for ((i = 1; i <= nombre_tests; i++)); do
            run_and_check "$arg" "$i"
        done
    done
done

#(
#"1 800 200 200 10"
#"2 405 200 200 10"
#"2 404 200 200 10"
#"2 403 200 200 10"
#"2 402 200 200 10"
#"2 401 200 200 10"
#"3 605 200 200 10"
#"3 604 200 200 10"
#"3 603 200 200 10"
#"3 602 200 200 10"
#"3 601 200 200 10"
#"4 405 200 200 10"
#"4 404 200 200 10"
#"4 403 200 200 10"
#"4 402 200 200 10"
#"4 401 200 200 10"
#"5 605 200 200 10"
#"5 604 200 200 10"
#"5 603 200 200 10"
#"5 602 200 200 10"
#"5 601 200 200 10"
#"10 405 200 200 10"
#"10 404 200 200 10"
#"10 403 200 200 10"
#"10 402 200 200 10"
#"10 401 200 200 10"
#"100 415 200 200 10"
#"100 414 200 200 10"
#"100 413 200 200 10"
#"100 412 200 200 10"
#"100 411 200 200 10"
#"101 615 200 200 10"
#"101 614 200 200 10"
#"101 613 200 200 10"
#"101 612 200 200 10"
#"101 611 200 200 10"
#)

##!/bin/bash
#
## Tableau de séries d'arguments à tester
#series_arguments=(
#    "1 800 200 200 10"
#    "2 405 200 200 10" "2 404 200 200 10" "2 403 200 200 10" "2 402 200 200 10" "2 401 200 200 10"
#    "3 605 200 200 10" "3 604 200 200 10" "3 603 200 200 10" "3 602 200 200 10" "3 601 200 200 10"
#    "4 405 200 200 10" "4 404 200 200 10" "4 403 200 200 10" "4 402 200 200 10" "4 401 200 200 10"
#    "5 605 200 200 10" "5 604 200 200 10" "5 603 200 200 10" "5 602 200 200 10" "5 601 200 200 10"
#    "10 405 200 200 10" "10 404 200 200 10" "10 403 200 200 10" "10 402 200 200 10" "10 401 200 200 10"
#    "100 415 200 200 10" "100 414 200 200 10" "100 413 200 200 10" "100 412 200 200 10" "100 411 200 200 10"
#    "101 615 200 200 10" "101 614 200 200 10" "101 613 200 200 10" "101 612 200 200 10" "101 611 200 200 10"
#)
#
## Nombre de fois à tester chaque série d'arguments
#nombre_tests=5
#
## Fonction pour exécuter le programme et vérifier le résultat
#run_and_check() {
#    local arg="$1"
#    local output=$(./philo $arg)  # Exécute le programme et capture la sortie
#
#    if echo "$output" | grep -q "died"; then
#        echo "Test avec l'argument \"$arg\" : FAILED (contient le mot \"died\")"
#    else
#        echo "Test avec l'argument \"$arg\" : PASSED"
#    fi
#}
#
## Boucle pour tester chaque série d'arguments
#for series in "${series_arguments[@]}"; do
#    echo "===== Test de la série d'arguments : $series ====="
#    for arg in "${series[@]}"; do
#        for ((i = 1; i <= nombre_tests; i++)); do
#            run_and_check "$arg"
#        done
#    done
#done
#
