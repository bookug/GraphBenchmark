if [ -d "./query/" ]
then
    rm ./query/*
fi
make clean
make
./run.exe ring data/delaunay_prev.txt query_requirement/ring_query_requirement.txt
