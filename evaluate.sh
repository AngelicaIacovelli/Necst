printf "Starting shortest path evalutation\n"
N_nodes=("1000" "2000" "4000" "8000" "16000" "32000" "64000" "128000")
Density=('5' '10' '15' '20' '25' '30' '35' '40' '45' '50' '55' '60' '65' '70' '75' '80' '85' '90' '95' '100')
Seeds=("42" "420" "13" "135")
((i= ${#N_nodes[@]}*${#Density[@]}*${#Seeds[@]}))
((j=1))

for nodes in "1000" "2000" "4000" "8000" "16000" "32000" "64000" "128000"; do
    for density in '5' '10' '15' '20' '25' '30' '35' '40' '45' '50' '55' '60' '65' '70' '75' '80' '85' '90' '95' '100'; do
        for seeds in "42" "420" "13" "135"; do
            printf "\nTest $j/$i\n"
            printf "\nNum_nodes = $nodes\nDensity = $density\nSeed = $seeds\n\n"
            ./exeDef $nodes $density $seeds &> results/N$nodes.D$density.S$seeds.log
            ((j+=1))
            printf "\nDone\n"
        done
    done
done

