compile:
	g++ -o server.out mainServer.cpp BuildVector.cpp Distance.cpp Flower.cpp Garden.cpp KnnClient.cpp KnnServer.cpp MyFileReader.cpp CLI.cpp Settings.cpp SocketIO.cpp -std=c++11 -lpthread
	g++ -o client.out mainClient.cpp BuildVector.cpp Distance.cpp Flower.cpp Garden.cpp KnnClient.cpp KnnServer.cpp MyFileReader.cpp CLI.cpp Settings.cpp SocketIO.cpp -std=c++11 -lpthread