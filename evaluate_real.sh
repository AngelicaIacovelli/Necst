printf "Starting shortest path evalutation on real graphs\n"
Graphs=("facebook_combined.csv" "twitter_combined.csv")
Graph_Types=("U" "D")
Separators=("," ",")
Seeds=("42" "420" "13" "135")
((i=${#Graphs[@]}*${#Seeds[@]}))
((j=1))

for k in ${!Graphs[@]}; do
    for seed in ${Seeds[@]}; do
        printf "\nTest $j/$i\n"
        printf "\nGraph = ${Graphs[$k]}\nType = ${Graph_Types[$k]}\nSeed = $seed\n\n"
        ./exeDefReal ${Graphs[$k]} $seed ${Graph_Types[$k]} ${Separators[$k]} &> results_real/${Graphs[$k]}.$seed.log
        ((j+=1))
        printf "\nDone\n"
    done
done

