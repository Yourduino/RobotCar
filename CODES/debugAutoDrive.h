void autoDrive()
{
  //  static unsigned long prevMillis = 0l;
  //  unsigned long currentMillis = millis();
  
  //it has already declared prevMillis before entering this function

  unsigned long currentMillis = 0L;

  int firstInterval = 1500;
  int secondInterval = 3000;
  int thirdInterval = 4500;
  int fourthInterval = 6000;
  int fifthInterval = 7500;
  
  /***********flags for the millis state  ------------------------------ 1
  // state_a = false;
  // state_b = false;
  // state_c = false;
  // state_d = false;
  // state_e = false;
  // state_f = false;
  // state_g = false;
  ********************/
  
  /*************maybe create flags for the servo states -------------------------- 3
  // lookingLeft = false
  // lookingRight = false
  // lookingAhead = false
  *******************/
  
  /*************maybe create flags for the state of the robots movement declare these variables when the autoDrive state is entered ---------------------- 4
  // movingForward = false
  // movingBackward = false
  // movingLeft = false
  // movingRight =  false
  
  /*************positions of servo
  // lookLeft
  // lookRight
  // lookAhead
  *****************/
  
  /************flags for the distance readings ------------------------------- 2
    // condition_a = false
	// condition_b = false
	// condition_c = false
   ***************/	

  float dist1 = 0.0;
  float dist2 = 0.0;
  float dist3 = 0.0;
  float dist4 = 0.0;
  
  dist1 = obstacle();
  
  if (dist1 < thresholdDist) //if read distance is less than the thresholdDist. Set a flag here that becomes true if this condition is met
  {
	  condition_a = true;
	  state_a = false;
      state_b = false;
      state_c = false;
      state_d = false;
      state_e = false;
      state_f = false;
      state_g = false;
  }
  
  if (condition_a == true) // if the first read distance is < thresholdDist
  {
	  //now the other conditions
	  //first thing is to stop and immediately look left
	  Stop();
	  servo.write(leftDirection)   
	  
	  //for 
	  // look left here. After this, it immediately leaves the loop, then reads dist1 again and if this is > thresholdDist,
	  // it would leave this looking left and execute the else statement 
	  // hence, we need to find a way to keep it here till all the other functions are executed
	  // write functions to check time and then set flags, then use these flags to make decisions 
	  
  }
  
  if (currentMillis - prevMillis < firstInterval) // remains true from t0 ---> t1
  {
	   state_a = true;
	   state_b = false;
	   state_c = false;
	   state_d = false;
       state_e = false;
       state_f = false;
       state_g = false;
  }
  
  if (currentMillis - prevMillis > firstInterval && currentMillis - prevMillis < secondInterval) // remains true from t1 ---> t2
  {
	   state_a = false;
	   state_b = true;
	   state_c = false;
	   state_d = false;
       state_e = false;
       state_f = false;
       state_g = false;
  }	  

  if (currentMillis prevMillis > secondInterval && currentMillis - prevMillis < thirdInterval) // remains true for t2 ---> t3
  {
	   state_a = false;
	   state_b = false;
	   state_c = true;
	   state_d = false;
       state_e = false;
       state_f = false;
       state_g = false;
  }	   
  
  if (currentMillis - prevMillis > thirdInterval && currentMillis - prevMillis < fourthInterval) // remains true for t3 ---> t4
  {
	   state_a = false;
	   state_b = false;
	   state_c = false;
	   state_d = true;
       state_e = false;
       state_f = false;
       state_g = false;
  }	 
  
  if (currentMillis - prevMillis > fourthInterval && currentMillis - prevMillis < fifthInterval)
  {
	   state_a = false;
	   state_b = false;
	   state_c = false;
	   state_d = false;
       state_e = true;
       state_f = false;
       state_g = false;
  }
  
  if (currentMillis - prevMillis > fifthInterval)
  {
	   state_a = false;
	   state_b = false;
	   state_c = false;
	   state_d = false;
       state_e = false;
       state_f = true;
       state_g = false;
	   prevMillis = currentMillis;
  }
  
  if (state_a && lookingLeft == false)
  {
	  servo.write(lookLeft);
	  // for debugging
	  Serial.println("LOOKED LEFT....");
	  lookingLeft = true;
	  lookRight = false;
	  lookingAhead = false;
  }
  
  if (state_b)
  {
	  dist2 = obstacle()
	  //for debugging
	  Serial.println("STOPPED HERE TO READ LEFT DISTANCE");
  }
  
  if (dist2 < thresholdDist)
  {
	  condition_b = true
  }
  
  if (dist2 > thresholdDist)
  {
	  condition_b = false;
  }
  
  if (state_c && lookingRight == false)
  {
	  servo.write(lookRight);
	  
	  //for debugging
	  Serial.println("LOOKED RIGHT......");
	  lookingRightRight = true;
	  lookingLeft = false;
	  lookingAhead = false;
  }
  
  if (state_d)
  {
	  dist3 = obstacle();
	  
	  //for debugging
	  Serial.println("STOPPED HERE TO READ RIGHT DISTANCE");
  }
  
  if  (dist3 < thresholdDist)
  {
	  condition_c = true;
  }
  
  if (dist3 > thresholdDist)
  {
	  condition_c = false;
  }
  
  if (state_e && lookingAhead == false)
  {
	  servo.write(lookAhead);
	  
	  //for debugging
	  Serial.println("LOOKED AHEAD HERE...........");
  }
  
  if (state_f) //means it has completed it's  cycle
  {
	  prevMillis = currentMillis;
	  
	  //for debugging
	  Serial.println("COMPLETE CYCLE!");
  }
  
  if (condition_a) //means forward distance is less than threshold 
  {
	  //check other  states (a-f)
  }
  
  if (condition_b) // means left distance is less than threshold
  {
	  //check other states (a-f)
  }
  
  if (condition_c) // means right distance is less than threshold
  {
	  //check other states (a-f)
  }
  
	  
	  
  
  
  
  else //  if te first distance is > than the thresholdDist
  {
	  //Test other flags  and keep moving forward_iterator
	  
	  servo.write(lookAhead);
	  front();
	  prevMillis = currentMillis;  ///-----------------------------not quite sure if this should be here
	  
	  //reset all the states to DEFAULT where ROBOT is movingForward and lookingAhead 
	  condition_a = false;
	  condition_b = false;
	  condition_c = false;
	  state_a = false;
	  state_b = false;
      state_c = false;
	  state_d = true;
      state_e = false;
      state_f = false;
      state_g = false;
	  lookingAhead = true;
	  lookingLeft = false;
	  lookingRight = false;
	  movingForward = true;
	  movingBackward = false;
	  movingLeft = false;
	  movingRight = false;
	  

  }
  
  

  
}//END 