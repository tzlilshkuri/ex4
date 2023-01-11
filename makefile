compile:
	g++ -o server.out mainServer.cpp BuildVector.cpp Distance.cpp Flower.cpp Garden.cpp KnnClient.cpp KnnServer.cpp MyFileReader.cpp -std=c++11
	g++ -o client.out mainClient.cpp BuildVector.cpp Distance.cpp Flower.cpp Garden.cpp KnnClient.cpp KnnServer.cpp MyFileReader.cpp -std=c++11