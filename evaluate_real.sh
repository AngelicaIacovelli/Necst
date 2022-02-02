printf "Starting shortest path evalutation on real graphs\n"
Graphs=("facebook_combined.csv" "grafo2.csv")
Seeds=("42" "420" "13" "135")
((i= ${#Graphs[@]}*${#Seeds[@]}))
((j=1))

for graph in "facebook_combined.csv" "grafo2.csv"; do
    for seeds in "42" "420" "13" "135"; do
            printf "\nTest $j/$i\n"
            printf "\nGraph = $graph\nSeed = $seeds\n\n"
            ./exeDefReal $graph $seeds &> results_real/$graph.$seeds.log
            ((j+=1))
            printf "\nDone\n"
    done
done

