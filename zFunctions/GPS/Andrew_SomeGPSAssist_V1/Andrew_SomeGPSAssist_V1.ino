
String  buffer_str; //Declare string buffer
String useful_str_buffer ; //read code to see how this is useful :)

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);

}

void loop() {
  //buffer_str.reserve(200); //Just allocate memory for flight software stuff
  if (Serial.available()){ //if there is new data in serial 
    buffer_str = ""; //Clear old data off buffer_str

    for (int i=0;i<=200;++i){
      buffer_str += (char)Serial.read(); //read 200 new char from the GPS and add it to buffer_str
    }// NOTE: Because 200 characters are read from the serial the "$GPRMC" statement, has to be there in the string at least twice.

    int index = buffer_str.indexOf ("$GPRMC"); //Search for where the "$GPRMC" is in the string
    //https://www.arduino.cc/en/Reference/StringIndexOf

    if (index == -1){
      Serial.println ("$GPRMC not found in buffer_str...You may choose to increase buffer_str size to increase probability");
     //if index is -1, then "$GPRMC" wasn't found: either search GPS data again or use previous data or increase buffer size
    }
    else
    //Here is where we actually read the GPS data from buffer_str
    {
    int k = index + strlen("$GPRMC");//This is the position in the string where the useful gps data starts from
    while (buffer_str.charAt(k) != '$'|| k<=100) //While we do not reach the new GPS line,'$' or k<=100 (so we don't get stuck in this while loop)
    useful_str_buffer  += buffer_str.charAt(k); //add string to the useful part
    
    if (buffer_str.charAt(k) == ',') { //if we finish reading a value, since values are seperated by ','
	float GPS_whatever_data = useful_str_buffer.toFloat(); //Store GPS data in float or whatever
        Serial.println (GPS_whatever_data);  //Serial Print your data to verify
	//I recommend you make an array buffer which you then later pass to your GPS struct
        useful_str_buffer = ""; //Clear useful_str_buffer  for new entry
	}
    ++k;
    }

}

}
