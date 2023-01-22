# Mitkadem-1-project
Nir's and Tzlil's project - Ex4

## For cloning our project you need to do this following steps:<br />
1.Enter the terminal.<br />
2.Open a folder in your computer (In example call her "gitFolder').<br />
3.Open the folder.<br />
4.Do right click "open in terminal".<br />
5.Write in the termninal "git clone https://github.com/tzlilshkuri/ex4.git".<br />
6.Write in the termninal "cd Ex4".<br />
7.Use the instruction written below in the terminal to run the program.<br />

Compile line - `make`

Run line for opening server - `./server.out File Port` <br />
`File` - path to file <br />
Run line for opening client - `./client Ip Port` <br />
`Ip` - the ip of the server <br />
`Port` - the port that the clinet and the server comunicate. <br />

##### What is the make?
In the Makefile we write which parts of a program need to be compile. <br />
After writing the make we can run the program in this part we make two ".out" files <br />
(Example at the end of the README). <br />
`g++` - the compiler. <br />
`FileName.cpp` - all the cpp files names we want to compile togther. <br />
`-std=c++11` - the vertion of the language. <br />
`-o server.out` - changing the output name to server.out 

## Description-
### ex1
In this part of our project we show 5 diffrent ways to calculate distances between two vectors.
How we do it - We scan 2 two vectors, each vector represants by line and in each line there are numbers that separate by space.
We split the numbers and enter them to a vector after we check that the numbers are valid numbers that saprate by one space, every 
exception from this format will drag an error and exit the program with a message that the tell me "invalid vector". We check also that 
the vectors are in the same size if not exit the program with message "invalid vector". After that we print the 5 diffrent types of ways
we can calculate distance - Euclidean, Manhattan, Chebyshev, Canberra and Minkowski the result will print line by line if the result is 
an integer we print the result with addition of .0 for example if the result is 4 we will print 4.0 otherwise we will print up to the sixth
digit after the decimal. We understand that Minkowski is a generalization of both Euclidean and Manhattan distances because
Minkowski needs to get an p that he is an integer to get the result for the calculation and if we want to calculate Euclidean distance 
this p should be 2 and if we want to calculate Manhattan distance this p should be 1. We choose to calculate Minkowski distance with 
p equals to 2. In Canberra distance when we have coordinate 0 in the same spot in both vectors we sand message "Nan" because this 
calculation is imposibale.
Example of insert two vectors and the results:


<img width="140" alt="mitk" src="https://user-images.githubusercontent.com/118110474/203577037-575cc245-4931-478c-b0c7-913e8f351427.PNG">

### ex2
In this part we need to implement the KNN algoritam that classifies types of flowers. <br />
The user enters values that contain characteristics of a particular flower, number (K neighbors) and a method for calculating the distance <br />
(AUC, MAN, CHB, CAN or MIN).
We need to calculate the distance between our flower and the other flowers by a calculation method that the user has chosen. <br />
After we hava all the distance we choose the K flowers that are closest to our flower, we check what type of every flower and than we classify our type of flower and return it to the user.
#### Explation about our classes:
##### Flower Class-
In this class we create "Flower". This struct contains 3 field: <br />
m_attributes = The characteristics of the flower. <br />
m_type = The type of the flower. <br />
m_distance = The distance betweeen the flower to the flower we get from the user. <br />
In addition, there are several functions in the class: <br />
1. Getters and Setters of the flower characteristic. <br />

2. Two function that return Bool in order to define how flowers should be sorted (In our case according to the distance from the flower we received from the user). <br />

3. updateType function- This function take the flower we recieved from the user and finally determines the type of flower according to its K closest neighbors. <br /> We using map that contains all the flowers type in order to in order to find the type of flower that appears the most times. This is also our type of flower
that we return to the user.



<img width="260" alt="רררר" src="https://user-images.githubusercontent.com/118110474/206921959-653a549e-2e1e-4dba-860d-a1db3936f838.PNG">




##### Graden Class-
This class a two function:
The first one is "calcDiss"- We check which calculation method we received from the user, take every vector we have, cacaluting is disntance accroding to the
method and return his type. <br />
The second one is "getKSmallest" - This function first scanning all the vectors and using calcDiss to return their type and set the diastance to every flower.
After we have all the distances we using our sort function and than take the K closest neighbors (by puting them in the vector of type flower).

<img width="260" alt="אאא" src="https://user-images.githubusercontent.com/118110474/206921860-b130381b-5b41-4ce6-a633-f3842a3704a2.PNG">




##### myFileReader Class-
In this class we scan every line in the excel file- every line is actually a flower.
All the lines we scan is part of our garden, namely each line is a flower. Important notes: <br />
1. If the file is empty- the user will get an error. <br />
2. If the file contains some empty lines- it's ok we just skip them. <br />
3. If the files doesn't exist- the user will get an error. <br />
4. If the file is not an excel file-  the user will get an error. <br />
5. If there are lines in different size-  the user will get an error. <br />

##### BuildVector-
This class scan the vectors and check that each of them is correct, if not we return empty vector and that will be a sign for us that's an error occured.

##### Distance-
This class contains all five types of distances: "MAN", "AUC", "MIN", "CHB" and "CAN". but we write only 3 becouse one of the is gnerelization of the 2 we did'nt write

##### Main-
After the user enter his input we create a Garden, Open new Flowers, update their types, find the K nearest neighbors and print the type of the flower to the user. <br />

Example of insert input and the result (his type):

<img width="550" alt="mobax" src="https://user-images.githubusercontent.com/118110474/207869441-d5b9dbda-75e7-4c70-a405-d1b94d28187c.PNG">

### ex3
<img width="300" alt="ex3" src="https://user-images.githubusercontent.com/118110474/209481445-85807f04-064e-4335-ac9b-880f48d9dbe9.PNG">


In this part we need to implement a server that is divided into 2 parts: Server side and Client side.
The user enters 3 values that contain: vector, method for calculating the distance (AUC, MAN, CHB, CAN or MIN) and number (K neighbors). <br />
The output is the type of the vector.

#### Explation about our classes:
##### Server Class-
In this class we open the server. <br />
The server get file(CSV file with classified items) and port number (which will be used when we open the socket).
There are several functions in the class: <br />
1. createMess- return the type of the vector or error in case the vector is not valid.  <br />
2. load- loading the CSV file and open the socket.  <br />
3. recAndSend- receiving messages from the client and sending a reply endlessly.   <br />
4. Distructor- in order to close the socket.    <br />

Example of open the Server side:<br />
<img width="550" alt="s2" src="https://user-images.githubusercontent.com/118110474/209808317-ac2484ff-47e2-4e81-8d51-1e549ea5f461.PNG">


##### Client Class-
In this class we open the client side. <br />
The client get ip and port number (which will be used when we open the socket).
There are several functions in the class: <br />
1. openSocket- open new socket.   <br />
2. isValidFields- check if the field distance and K neighbors is valid. <br />
3. sendMessage- sending a message to the server. <br />
4. activateClient- Sending a vector to the server in order to receive its classification endlessly. <br />
5. Distructor- in order to close the socket.    <br />

Example of open the Client side:<br />
<img width="484" alt="s1" src="https://user-images.githubusercontent.com/118110474/209807922-3b113084-fd80-4a9b-ad36-10e1cf804769.PNG">


##### mainServer-
In the main we activate the server side. <br/>
We also check that the number of arguments and the arguments themselves are valid.<br/>
The server run endlessly.

##### mainClient-
In the main we activate the client side. <br/>
We also check that the number of arguments and the arguments themselves are valid.<br/>
After we start the client side will run endlessly (and return the vector type) until the user enters "-1" and then we close only the client side.

Example of client input:<br />
<img width="450" alt="חלק 2" src="https://user-images.githubusercontent.com/118110474/209807738-fd6807d5-3473-4979-9bfb-f8396dde903e.PNG">


### ex4
<img width="250" alt="menu" src="https://user-images.githubusercontent.com/118110474/213927487-fd363aac-84e4-41a5-aa29-b4b9f6c19fb3.PNG">

In this part we need to implement a server that is divided into 2 parts: Server side and Client side. <br/>
Every user have a menu with 6 options : <br/>
`1. upload an unclassified csv data` - In this option the client upload two files- classified and unclassified.<br />
`2. algorithm settings` - In this option the client can change the matrics calculation and the k nearest neighbors the helo us classified every flour (or anything else).  <br />
`3. classify data` - In this option we classify the unclisiffied file we recive in option 1 .<br />
`4. display results` - In this option we display the results of the classificition we made in option 3. <br />
`5. download results` -In this option  <br />
`8. exit` - In this option the client exit from the server(the server still stay open) <br />

#### Explation about our classes: <br />

##### Command Class- <br />

##### Upload Class- <br />

##### Settings Class- <br />

##### Update Class- <br />

##### PrintAll Class- <br />

##### Downloads Class- <br />

##### CLI Class- <br />

##### DefultIO Class- <br />

##### FiloIO Class- <br />

##### SOCKETIO Class- <br />

##### StandrdIO Class- <br />

#### Photos: <br />

##### make-
<img width="761" alt="make" src="https://user-images.githubusercontent.com/118110474/213927465-83d216a1-3c2c-4b6b-9ca7-86ddea67325c.PNG">


##### Open Server-
<img width="280" alt="server" src="https://user-images.githubusercontent.com/118110474/213927472-4214178f-36ae-4766-a865-0a0e89f39ad2.PNG">


##### Open Client-
<img width="350" alt="client" src="https://user-images.githubusercontent.com/118110474/213927480-d823fa71-082d-4ec7-bc39-132adb0a46a3.PNG">

##### menu-
<img width="398" alt="mm" src="https://user-images.githubusercontent.com/118110474/213927890-889de7c0-48ba-4e46-befd-522df2119871.PNG">


##### Option 1-
<img width="450" alt="1" src="https://user-images.githubusercontent.com/118110474/213927493-be6feb74-0255-4665-bbdf-4d6d2488a9f2.PNG">

##### Option 2-
<img width="450" alt="rr" src="https://user-images.githubusercontent.com/118110474/213927715-8701c638-41c3-40f4-8527-e091bd96acf4.PNG">


<img width="550" alt="e2" src="https://user-images.githubusercontent.com/118110474/213927513-e2728a51-5f0b-47b7-a7ea-96f73f7e3ec6.PNG">

##### Option 3- Just update.

##### Option 4-
<img width="218" alt="4" src="https://user-images.githubusercontent.com/118110474/213927537-50c3628c-1aba-4527-bc18-6ea98ffd017f.PNG">


##### Option 5-
<img width="200" alt="dd" src="https://user-images.githubusercontent.com/118110474/213927541-426a238e-76cf-4909-ac25-0a08c0045a76.PNG">

