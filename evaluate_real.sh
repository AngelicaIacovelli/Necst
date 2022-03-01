printf "Starting shortest path evalutation on real graphs\n"
Graphs=("facebook_combined.csv") # "twitter_combined.csv")
Separators=("," ",")
Graph_Types=("U" "D")
Seeds=("42" "420" "13" "135")
DataStruct=("L" "M" "C")
((i=${#Graphs[@]}*${#Seeds[@]}*${#DataStruct[@]}))
((j=1))

for k in ${!Graphs[@]}; do
    for seed in ${Seeds[@]}; do
        for datastruct in ${DataStruct[@]}; do
            printf "\nTest $j/$i\n"
            printf "\nGraph = ${Graphs[$k]}\nType = ${Graph_Types[$k]}\nSeed = $seed\nDataStruct = $datastruct\n\n"
            ./exeDefReal ${Graphs[$k]} ${Separators[$k]} ${Graph_Types[$k]} $datastruct $seed &> results_real/${Graphs[$k]}.$datastruct.$seed.log
            ((j+=1))
            printf "\nDone\n"
        done
    done
done

