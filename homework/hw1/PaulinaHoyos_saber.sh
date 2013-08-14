wget http://www.finiterank.com/saber/2011.csv
wget https://raw.github.com/forero/ComputationalPhysicsUniandes/master/hands_on/unix/columnas_2011.csv.txt
awk -F "\"*,\"*" '{print $5}' 2011.csv | grep SI | wc -l
awk -F "\"*,\"*" '{print $5}' 2011.csv | grep NO | wc -l
awk -F "\"*,\"*" '{print $5 "  " $8}' 2011.csv | grep NO | grep A  | wc -l
awk -F "\"*,\"*" '{print $5 "  " $8}' 2011.csv | grep NO | grep B  | wc -l
awk -F "\"*,\"*" '{print $5 "  " $8}' 2011.csv | grep SI | grep B | wc -l
